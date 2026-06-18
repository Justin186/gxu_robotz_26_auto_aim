#pragma once

#include <cstdint>
#include <optional>
#include <fcntl.h>
#include <filesystem>
#include <string_view>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>

namespace ipc {

enum class ShmError {
    OpenFailed,
    TruncateFailed,
    MapFailed,
    AlreadyExists,
    NotFound,
    PermissionDenied,
    InvalidSize,
};

inline std::filesystem::path shm_path(std::string_view name) {
    if (!name.empty() && name[0] == '/') {
        name = name.substr(1);
    }
    return std::filesystem::path("/tmp") / name;
}

class ShmRegion {
public:
    ~ShmRegion() {
        cleanup();
    }

    // Move-only
    ShmRegion(ShmRegion&& other) noexcept
        : data_(other.data_)
        , size_(other.size_)
        , fd_(other.fd_)
        , owner_(other.owner_)
        , path_(std::move(other.path_)) {
        other.data_ = nullptr;
        other.fd_ = -1;
        other.owner_ = false;
    }

    ShmRegion& operator=(ShmRegion&& other) noexcept {
        if (this != &other) {
            cleanup();
            data_ = other.data_;
            size_ = other.size_;
            fd_ = other.fd_;
            owner_ = other.owner_;
            path_ = std::move(other.path_);
            other.data_ = nullptr;
            other.fd_ = -1;
            other.owner_ = false;
        }
        return *this;
    }

    ShmRegion(const ShmRegion&) = delete;
    ShmRegion& operator=(const ShmRegion&) = delete;

    static std::optional<ShmRegion> create(const std::string_view name, const size_t size) {
        const auto path = shm_path(name);

        const int fd = ::open(path.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) {
            return std::nullopt;
        }

        if (ftruncate(fd, static_cast<off_t>(size)) < 0) {
            close(fd);
            std::filesystem::remove(path);
            return std::nullopt;
        }

        void* ptr = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (ptr == MAP_FAILED) {
            close(fd);
            std::filesystem::remove(path);
            return std::nullopt;
        }

        std::memset(ptr, 0, size);

        return ShmRegion(ptr, size, fd, true, path);
    }

    static std::optional<ShmRegion> open(const std::string_view name, const size_t size) {
        const auto path = shm_path(name);

        if (!std::filesystem::exists(path)) {
            return std::nullopt;
        }

        const int fd = ::open(path.c_str(), O_RDWR, 0);
        if (fd < 0) {
            return std::nullopt;
        }

        struct stat st{};
        if (fstat(fd, &st) < 0 || static_cast<size_t>(st.st_size) < size) {
            close(fd);
            return std::nullopt;
        }

        void* ptr = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (ptr == MAP_FAILED) {
            close(fd);
            return std::nullopt;
        }

        return ShmRegion(ptr, size, fd, false, path);
    }

    void* data() noexcept { return data_; }
    const void* data() const noexcept { return data_; }
    size_t size() const noexcept { return size_; }
    bool is_owner() const noexcept { return owner_; }
    const std::filesystem::path& path() const noexcept { return path_; }

    template <typename T>
    T* as() noexcept {
        return static_cast<T*>(data_);
    }

    template <typename T>
    const T* as() const noexcept {
        return static_cast<const T*>(data_);
    }

    void flush() const {
        if (data_ != nullptr && data_ != MAP_FAILED) {
            msync(data_, size_, MS_SYNC);
        }
    }

private:
    ShmRegion(void* data, const size_t size, const int fd, const bool owner, std::filesystem::path path)
        : data_(data), size_(size), fd_(fd), owner_(owner), path_(std::move(path)) {}

    void cleanup() {
        if (data_ != nullptr && data_ != MAP_FAILED) {
            munmap(data_, size_);
        }
        if (fd_ >= 0) {
            close(fd_);
        }
        if (owner_ && !path_.empty()) {
            std::filesystem::remove(path_);
        }
    }

    void* data_{nullptr};
    size_t size_{0};
    int fd_{-1};
    bool owner_{false};
    std::filesystem::path path_;
};

} // namespace ipc