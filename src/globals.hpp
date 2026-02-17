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
// Set this offset to your real build (inches). Sign depends on wheel position vs tracking center.
// Using 0.0" as a safe default.
inline lemlib::TrackingWheel vertical_tracking_wheel(&tracking, lemlib::Omniwheel::NEW_275, 0);

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

// ✅ 不积累误差的角度 PID（不改）
inline lemlib::ControllerSettings angular_controller(
    1.29 ,    // kP 
    0,     // kI 
    9,      // kD 
    0,          // anti windup
    1,          // small error (deg)
    350,        // small timeout (ms)
    4,          // large error
    1200,       // large timeout
    0        // slew
);

// 直线 PID（不改）
inline lemlib::ControllerSettings lateral_controller(
    4.2,    // kP  (降低，减少冲)
    0.0,    // kI  (先关)
    10.71,   // kD  (提高，增加刹车/阻尼)
    0.0,    // anti windup (I=0时无所谓)
    1.0,    // small error range (in)
    550,    // small error timeout (ms)
    3.0,    // large error range (in)
    900,    // large error timeout (ms)
    0      // slew (关键！限制加速度，减少冲头)
);

inline lemlib::Chassis chassis(
    drivetrain,
    lateral_controller,
    angular_controller,
    sensors
);

#endif
