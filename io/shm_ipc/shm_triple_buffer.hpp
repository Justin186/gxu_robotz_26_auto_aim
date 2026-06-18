#pragma once

#include "shm_layout.hpp"
#include <atomic>
#include <optional>

namespace ipc {

/**
 * @brief TripleBuffer 原子操作模板
 *
 * 这是一个无锁 SPSC (Single Producer Single Consumer) 通信原语。
 * 基于 talos-cpp 现有的 triple_buffer.hpp 设计，扩展用于跨进程通信。
 *
 * 状态编码 (uint8_t):
 *   Bit 7: FLAG_NEW - 有新数据
 *   Bits 0-1: ready_index - 就绪槽位索引 (0-2)
 */
template <typename BufferType, typename SlotType>
class TripleBufferOps {
public:
    explicit TripleBufferOps(BufferType* buf)
        : buf_(buf) {}

    // ============ 生产者 API ============

    /**
     * @brief 获取可写槽位的可变引用
     */
    [[nodiscard]] SlotType& borrow_mut() noexcept { return buf_->slots[buf_->write_idx]; }

    /**
     * @brief 发布数据，使消费者可见
     *
     * 原子地交换 write_idx 和 ready_idx，并设置 FLAG_NEW
     */
    void publish() noexcept {
        // 设置 new_data flag，交换 ready 和 write
        const auto old =
            buf_->state.exchange(buf_->write_idx | FLAG_NEW, std::memory_order_acq_rel);
        buf_->write_idx = old & INDEX_MASK;
    }

    // ============ 消费者 API ============

    /**
     * @brief 尝试获取最新数据
     * @return 如果有新数据，返回指向数据的指针；否则返回 nullopt
     *
     * 使用 CAS 操作尝试获取就绪槽位，如果生产者同时在写入可能失败
     */
    [[nodiscard]] std::optional<const SlotType*> borrow() noexcept {
        auto expected = buf_->state.load(std::memory_order_acquire);

        // 没有新数据
        if (!(expected & FLAG_NEW)) {
            return std::nullopt;
        }

        // CAS: 尝试拿走 ready，把 read 还回去，清除 flag
        auto ready_idx = expected & INDEX_MASK;

        if (auto desired = buf_->read_idx; !buf_->state.compare_exchange_strong(
                expected, desired, std::memory_order_acq_rel, std::memory_order_acquire)) {
            // Producer 刚好又写了，expected 已更新，再试一次
            if (!(expected & FLAG_NEW)) {
                return std::nullopt;
            }
            ready_idx = expected & INDEX_MASK;
            desired   = buf_->read_idx;
            if (!buf_->state.compare_exchange_strong(
                    expected, desired, std::memory_order_acq_rel, std::memory_order_relaxed)) {
                // producer 在这么短时间内连续 publish 两次，放弃这次
                return std::nullopt;
            }
        }

        buf_->read_idx = ready_idx;
        return &buf_->slots[ready_idx];
    }

    /**
     * @brief 获取当前读取槽位 (不检查是否有新数据)
     */
    [[nodiscard]] const SlotType& current() const noexcept { return buf_->slots[buf_->read_idx]; }

    /**
     * @brief 检查是否有新数据可读
     */
    [[nodiscard]] bool has_new_data() const noexcept {
        return buf_->state.load(std::memory_order_acquire) & FLAG_NEW;
    }

private:
    BufferType* buf_;
};

// 便捷类型别名
using ImageOps  = TripleBufferOps<ImageTripleBuffer, ImageMeta>;
using PoseOps   = TripleBufferOps<PoseTripleBuffer, PoseMeta>;
using GimbalOps = TripleBufferOps<GimbalTripleBuffer, GimbalCmd>;

} // namespace ipc
