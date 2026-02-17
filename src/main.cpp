// main.cpp
#include "globals.hpp"
#include "AutonSelector.hpp"
#include "Autonomous_Paths.hpp"
#include "main.h"
#include <algorithm>
#include <iostream>

// ======================= AUTON SELECTOR POINTER =======================
AutonSelector* autonSelector = nullptr;

// ======================= CENTER BUTTON (UNUSED) =======================
void on_center_button() {}

// ======================= POSE LOGGER =======================
void logTask() {
    while (true) {
        lemlib::Pose pose = chassis.getPose();
        
        // Print to terminal
        std::cout << "X: " << pose.x
                  << " | Y: " << pose.y
                  << " | Th: " << pose.theta
                  << std::endl;
        
        // Display on brain screen
        pros::screen::set_pen(pros::Color::white);
        pros::screen::print(pros::E_TEXT_MEDIUM, 0, "X: %.2f Y: %.2f Th: %.1f", 
                           (double)pose.x, (double)pose.y, (double)pose.theta);
        
        pros::delay(250);
    }
}

// ======================= INITIALIZE =======================
void initialize() {
    pros::lcd::initialize();

    tracking.set_reversed(true);   // 需要反向就 true；不需要就 false


    // IMU 校准（只在开机/下载后做一次）
    IMU.reset();
    while (IMU.is_calibrating()) pros::delay(20);

    // LemLib 校准（会启动 odom 任务等）
    chassis.calibrate();

    pros::Task logger(logTask);
    pros::delay(500);
    pros::screen::erase();
    pros::delay(500);

    autonSelector = new AutonSelector();
    autonSelector->setAutons(std::vector<autonomousRoute>{
        //{"red",  "TEST Coords",     "coordinate test", coordinateTest},  // Commented out - only 5 slots available
        {"red",  "TUNE Lateral",    "PID tuning", tuneLateralPID},
        {"red",  "Red Lft <mid>",   "high & mid",  redAuton1},
        {"red",  "Red Lft <left>",  "turn left",   redAuton2}, // field偏左，机器向左偏，x-
        {"red",  "Red Lft <right>", "turn right",  redAuton3}, // field偏右，机器向右偏，x+
        {"red",  "TesmmateAWP",     "move forward", redAuton4},

        {"blue", "Red Rt <mid>",    "high & low",  blueAuton1},
        {"blue", "Red Rt <left>",   "turn left",   blueAuton2},
        //{"blue", "Red Rt <right>", "turn right", blueAuton3},
    });

    autonSelector->setSkillsAuton(
        autonomousRoute{"Skills", "Auton", "Skills Auton", SkillAuton}
    );
    autonSelector->start();

    // 初始化机构（用 globals 的状态）
    piston_matchload.set_value(s_matchload);
    piston_goaldoor.set_value(s_goaldoor);
    piston_body.set_value(s_body);
    piston_arm.set_value(true);


    // 刹车模式
    rightDT.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    leftDT.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

    intake_rollar.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

    // plunger 松手即自由旋转
    plunger.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    plunger.move(0);
}

// ======================= DISABLED =======================
void disabled() {}

// ======================= COMPETITION ======================
void competition_initialize() {}

// ======================= AUTONOMOUS =======================
void autonomous() {
    if (autonSelector != nullptr) autonSelector->runAuton();
}

// ======================= DRIVER CONTROL =======================
void opcontrol() {
    // 确保 driver 开始时硬件状态一致
    rightDT.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    leftDT.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    intake_rollar.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

    piston_matchload.set_value(s_matchload);
    piston_goaldoor.set_value(s_goaldoor);
    piston_body.set_value(s_body);
    piston_arm.set_value(s_arm);

    while (true) {
        // --------- 驱动控制（保持你原来的算法不改）---------
        int power = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int turn  = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        power = std::clamp(power, -127, 127);
        turn  = std::clamp(turn,  -127, 127);

        double turn_scale = 1.0 - (std::abs(power) / 750.0);
        turn = static_cast<int>(turn * turn_scale);

        int left  = power + turn;
        int right = power - turn;

        left  = std::clamp(left,  -127, 127);
        right = std::clamp(right, -127, 127);

        leftDT.move(left);
        rightDT.move(right);

        // --------- intake ---------
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
            intake_rollar.move(127);
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
            intake_rollar.move(-127);
        else
            intake_rollar.move(0);

        // --------- plunger 控制 (R2 升, R1 放下) ---------
        bool upKey   = master.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
        bool downKey = master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);

        if (upKey && !downKey) {
            plunger.move(PLUNGER_UP_PWR);
            piston_goaldoor.set_value(true);
        }
        else if (downKey && !upKey) {
            plunger.move(PLUNGER_DOWN_PWR);
        }
        else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
            plunger.move(82);
        }
        else {
            plunger.move(0);
            plunger.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        }

        // --------- pistons toggle（用 globals 的状态 + prev）---------
        bool cLeft = master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);
        bool cX    = master.get_digital(pros::E_CONTROLLER_DIGITAL_X);
        bool cUp   = master.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
        bool cBtnA = master.get_digital(pros::E_CONTROLLER_DIGITAL_A);

        if (cLeft && !prev_left) { s_matchload = !s_matchload; piston_matchload.set_value(s_matchload); }
        if (cX    && !prev_x)    { s_goaldoor  = !s_goaldoor;  piston_goaldoor.set_value(s_goaldoor);  }
        if (cUp   && !prev_up)   { s_body      = !s_body;      piston_body.set_value(s_body);          }
        if (cBtnA && !prev_a)    { s_arm       = !s_arm;       piston_arm.set_value(s_arm);            }

        prev_left = cLeft;
        prev_x    = cX;
        prev_up   = cUp;
        prev_a    = cBtnA;

        pros::delay(10);
    }
}
