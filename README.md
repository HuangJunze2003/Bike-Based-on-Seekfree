# 🏁 全国大学生智能汽车竞赛 平衡摩托组 - TC264 竞赛代码

> **基于 [成都逐飞科技 (Seekfree)](https://seekfree.taobao.com/) 的英飞凌 Aurix TC264D 开源库进行二次开发。**

---

## 📖 项目简介
本项目是参加 **全国大学生智能汽车竞赛** 的平衡单车组参赛方案。项目深入挖掘了英飞凌 TC264D 的多核性能，针对竞赛中的视觉处理、姿态解算、电磁采样及复杂运动控制需求，构建了一套高效、稳定的赛车控制框架。

## 🚀 核心功能
### 1. 运动控制算法
- **电机闭环**: 基于增量式 PID 的速度闭环控制。
- **平衡控制**: 针对直立车/平衡车方案，实现基于 **LQR/PD** 的姿态角闭环。
- **转向控制**: 视觉/电磁信息融合后，通过 PID 算法实现精准路径跟踪（详见 [code/PID_LQR.c](code/PID_LQR.c)）。

### 2. 视觉与传感集成
- **视觉系统**: 支持 **MT9V03X/OV7725** 摄像头的图像采集、二值化及赛道特征提取。
- **惯导解算**: 集成 **ICM20602/IMU660RA**，支持多轴数据融合与滤波算法。
- **任务调度**: 利用 **PIT/STM** 定时器中断实现严格的任务周期控制（详见 [user/isr.c](user/isr.c)）。

### 3. 多核任务分配
- **CPU0**: 负责全局初始化、高频中断控制及外设调度。
- **CPU1**: 负责图像识别与海量数据处理，发挥多核算力优势。

---

## 📂 目录结构
```text
Seekfree_TC264/
├── code/               # 🏆 竞赛逻辑核心
│   ├── control.c       # 主控环逻辑
│   ├── PID_LQR.c       # PID & LQR 算法实现
│   └── system.c        # 系统配置
├── user/               # 核心程序入口
│   ├── cpu0_main.c     # 芯片初始化及 CPU0 任务
│   ├── cpu1_main.c     # CPU1 辅助计算任务
│   └── isr.c           # 中断服务程序（控制环路）
├── libraries/          # 逐飞科技底层库
│   ├── zf_driver/      # 芯片外设驱动封装
│   └── zf_device/      # 外部设备接口
└── Debug/              # 编译输出文件
```

---

## 🛠 开发环境
- **IDE**: [AURIX Development Studio (ADS)](https://www.infineon.com/cms/en/design-support/software/free-software-tools-for-aurix-multicore-tricore-family/aurix-development-studio/) v1.9.4+
- **编译器**: Tasking Tricore Compiler
- **硬件**: Seekfree TC264D 核心板 & 逐飞科技主板/传感器

## ⚙️ 快速上手
1. **工程导入**: 使用 ADS 导入本项目的根路径。
2. **硬件规划**: 参考 [推荐IO分配.txt](%E6%8E%A8%E8%8D%90IO%E5%88%86%E9%85%8D.txt) 设置跳线。
3. **参数配置**: 在 `user/cpu0_main.c` 中完成传感器校准。
4. **编译构建**: 通过 IDE 编译并烧录至 TC264 芯片。

## 📄 许可证 (License)
本项目严格遵守 **[GNU GPL v3.0](LICENSE)** 开源协议。
- **原始版权**: [成都逐飞科技有限公司](libraries/doc/GPL3_permission_statement.txt)。
- **开源精神**: 本项目代码可自由传播、学习与修改，但必须保留逐飞科技的版权声明。

---
**致谢**: 感谢逐飞科技提供的开源库支持。
