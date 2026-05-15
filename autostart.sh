#!/bin/bash
# /home/robomaster/gxu_robotz_26_auto_aim/autostart.sh

# 切换到工作目录
cd ~/gxu_robotz_26_auto_aim || exit

# 启动程序
./build/auto_aim_mpc -rec=false configs/infantry.yaml

# 清理历史
history -c
