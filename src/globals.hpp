// globals.hpp
#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "math_fix.hpp"
#include "main.h"
#include "lemlib/api.hpp"
#include <string>

// ================== 全局状态（可能被 AutonSelector/别的文件用到） ==================
inline std::string autonomousPath = "none";
inline std::string teamColor = "none";

// ================== 控制器 ==================
inline pros::Controller master(pros::E_CONTROLLER_MASTER);

// ================== 电机 ==================
// 左驱动
// 左驱动：不反向
inline pros::MotorGroup leftDT(
    {-11, -4, -5},
    pros::v5::MotorGears::blue
);

// 右驱动：反向（用负号端口实现，不额外在 main 加符号）
inline pros::MotorGroup rightDT(
    {13, 17, 20},
    pros::v5::MotorGears::blue
);

// plunger
inline pros::Motor plunger(-10, pros::v5::MotorGears::red);

// intake
inline pros::Motor intake_rollar(16, pros::v5::MotorGears::blue);

// ================== 传感器 ==================
inline pros::Rotation tracking(14);

inline pros::Imu IMU(12);

// ================== Tracking Wheel (LemLib Odometry) ==================
// Tracking wheel: 2.68" calibrated diameter (actual, not spec), offset 2.5" from tracking center
// Calibrated based on 96" test showing 98.59" (2.7% error correction)
inline lemlib::TrackingWheel vertical_tracking_wheel(&tracking, 2.75, 2.5);

// ================== 气动 ==================
inline pros::adi::DigitalOut piston_matchload('A');
inline pros::adi::DigitalOut piston_goaldoor('B');
inline pros::adi::DigitalOut piston_body('G');
inline pros::adi::DigitalOut piston_arm('H');

// ================== Driver Control 机构状态（需要跨循环保留） ==================
inline bool s_matchload = false;
inline bool s_goaldoor  = false;
inline bool s_body      = false;
inline bool s_arm       = true;

// 按键边沿检测（prev state）
inline bool prev_left = false;
inline bool prev_x    = false;
inline bool prev_up   = false;
inline bool prev_a    = false;

// plunger 升/降速度（常量放 globals）
constexpr int PLUNGER_UP_PWR   = 127;
constexpr int PLUNGER_DOWN_PWR = -127;

// ================== LemLib 配置 ==================
inline lemlib::Drivetrain drivetrain(
    &leftDT,
    &rightDT,
    12.5,                         // track width
    lemlib::Omniwheel::NEW_325,
    450,
    2
);
//&vertical_tracking_wheel


inline lemlib::OdomSensors sensors(
    &vertical_tracking_wheel, // vertical tracking wheel 1
    //nullptr,      
    nullptr,            // vertical tracking wheel 2 (unused)
    nullptr,                  // horizontal tracking wheel 1 (unused)
    nullptr,                  // horizontal tracking wheel 2 (unused)
    &IMU                      // inertial sensor
);

// 角度 PID - 继续提高以达到 theta 接近 0°（当前 -5.9°）
inline lemlib::ControllerSettings angular_controller(
    2.8,    // kP - 从2.0提高到2.8，继续增强方向保持
    0,      // kI - 保持关闭
    10.0,   // kD - 从9.0提高到10.0，配合更高的kP
    3,      // anti windup
    1,      // small error (deg)
    350,    // small timeout (ms)
    4,      // large error
    1200,   // large timeout
    0       // slew
);

// 直线 PID - 解决减速时向左偏的问题
inline lemlib::ControllerSettings lateral_controller(
    5.2,    // kP  - 略微提高，改善低速时的响应
    0.0,    // kI  - 关闭，避免在减速时累积误差
    11.1,    // kD  - 降低，减少低速时的过度刹车和震荡
    0.0,    // anti windup 
    0.5,    // small error range - 减小到0.5"，要求更精确停止
    500,    // small error timeout - 延长到500ms，给更多时间稳定
    3.0,    // large error range (in)
    900,    // large error timeout (ms)
    12      // slew - 提高到12，让加减速更平滑
);

inline lemlib::Chassis chassis(
    drivetrain,
    lateral_controller,
    angular_controller,
    sensors
);

#endif
