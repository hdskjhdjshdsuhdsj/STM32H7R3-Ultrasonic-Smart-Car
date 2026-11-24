# TANK5 超声波避障智能小车（STM32H7R3）

基于 STM32H7R3L8HxH 的嵌入式小车控制工程，使用 Keil MDK（ARMCC/AC6）开发，采用 **Boot + Appli 双工程**结构。主程序位于 Boot 工程，Appli 工程为预留的应用程序工程。

## 已实现功能

- **超声波测距避障**：HC-SR04 由 TIM5 计时，按 `距离 ≈ 高电平时间 / 58` 换算厘米值；距离小于 30 cm 时左转，否则直行。
- **电机驱动**：TB6612 双路电机驱动，TIM4 产生 PWM，封装 `go_straight()`、`go_back()`、`stop()`、`turn_left()`、`turn_right()` 等控制函数。
- **气体检测急停**：MQ 气体传感器接 PB6，`MQSensor_Scan()` 检测到气体时点亮 PD14 LED 并执行停车。
- **双工程结构**：Boot 为当前运行主体；Appli 目前为空循环，作为后续应用扩展入口。

## 目录结构

```
Boot/                     Boot 工程源码（main.c、tim.c、gpio.c、usart.c）
Appli/                    Appli 工程源码（预留）
MDK-ARM/Boot/             Keil Boot 工程、car.c/h、hycg.c/h、链接脚本
MDK-ARM/Appli/            Keil Appli 工程
MDK-ARM/Project.uvmpw     Keil 多工程工作空间
Drivers/                  STM32H7RSxx HAL 驱动与 CMSIS
TANK5_TEST.ioc            STM32CubeMX 配置文件
Ultrasound.c              早期 F1 平台遗留的超声波代码（当前未使用）
```

## 打开与编译

1. 安装 Keil uVision5，并具备 STM32H7RS 系列器件支持包。
2. 打开 `MDK-ARM/Project.uvmpw` 工作空间，选择 `TANK5_TEST_Boot` 工程。
3. 编译并下载到板卡；`TANK5_TEST_Appli` 为预留工程，无需修改。

> 说明：编译产物（`.o`、`.axf`、`.hex`、`map`、中间目录等）已通过 `.gitignore` 排除，仓库仅保留源码与工程配置。
