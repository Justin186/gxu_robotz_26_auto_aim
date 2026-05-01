#!/usr/bin/env python3
import cv2
import time


def test_camera():
    cap = cv2.VideoCapture('/dev/video0', cv2.CAP_V4L2)
    cap.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter_fourcc(*"MJPG"))
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 720)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

    # 1 秒窗口统计，避免瞬时 FPS 抖动
    sec_start = time.time()
    frame_count = 0
    bytes_count = 0
    fps_1s = 0.0
    bandwidth_1s = 0.0

    while True:
        ret, frame = cap.read()
        if not ret:
            print("Failed to capture frame")
            continue

        curr_time = time.time()
        frame_count += 1
        bytes_count += frame.nbytes

        # 每秒输出一次终端统计值
        elapsed = curr_time - sec_start
        if elapsed >= 1.0:
            fps_1s = frame_count / elapsed
            bandwidth_1s = (bytes_count * 8) / elapsed / 1_000_000  # Mbps
            print(f"FPS: {fps_1s:.1f}, Bandwidth: {bandwidth_1s:.2f} Mbps")

            sec_start = curr_time
            frame_count = 0
            bytes_count = 0

        # 在画面上显示信息
        info1 = f"FPS(1s): {fps_1s:.1f}"
        info2 = f"Bandwidth(1s): {bandwidth_1s:.2f} Mbps"
        cv2.putText(frame, info1, (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
        cv2.putText(frame, info2, (10, 60), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)

        cv2.imshow("video1 640x480 120fps", frame)
        if cv2.waitKey(1) & 0xFF == ord("q"):
            break

    cap.release()
    cv2.destroyAllWindows()


if __name__ == "__main__":
    test_camera()
