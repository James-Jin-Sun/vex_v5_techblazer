#ifndef AUTONOMOUS_PATHS_HPP
#define AUTONOMOUS_PATHS_HPP

#include "globals.hpp"



void redAuton1() {
    piston_arm.set_value(true);
    plunger.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    
    chassis.setPose(50, -11.7, 0);

    chassis.moveToPoint(50, -42.5, 1500, lemlib::MoveToPointParams{false, 90}, false);
    
    intake_rollar.move(127);

    chassis.turnToHeading(90,500);

    piston_matchload.set_value(true);

    chassis.moveToPoint(61.75, -42, 800, lemlib::MoveToPointParams{true, 40}, false);

    pros::delay(500);

    chassis.moveToPoint(53, -42, 500, lemlib::MoveToPointParams{false, 60}, false);

    chassis.moveToPoint(27, -43.75, 1100, lemlib::MoveToPointParams{false, 65}, false);

    piston_goaldoor.set_value(true);

    chassis.setPose(28, -43, 90);

    plunger.move_velocity(43);

    pros::delay(900);

    plunger.move(-127);

    intake_rollar.move(-127);

    /*

    piston_matchload.set_value(false);

    chassis.moveToPoint(48, -45, 600, lemlib::MoveToPointParams{true, 80}, false);

    pros::delay(100);

    chassis.turnToHeading(317,800);
    
    intake_rollar.move(127);

    chassis.moveToPoint(28, -24.5, 1500, lemlib::MoveToPointParams{true, 50}, false);

    pros::delay(300);

    piston_matchload.set_value(true);

    pros::delay(300);

    chassis.moveToPoint(23, -18.5, 1500, lemlib::MoveToPointParams{true, 30}, false);

    chassis.turnToHeading(135,2000);

    piston_goaldoor.set_value(true);

    plunger.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    pros::delay(200);

    chassis.moveToPoint(12.4, -10.1, 5000, lemlib::MoveToPointParams{false, 30}, false);
    
    piston_body.set_value(true);

    piston_matchload.set_value(false);

    plunger.move(40);

    pros::delay(1000);
    */
}

void redAuton2() {

}

void redAuton3() {
   
}

void redAuton4() {
    
}

void blueAuton1() {
    piston_arm.set_value(true);
    plunger.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    
    chassis.setPose(50, 11.7, 0);

    chassis.moveToPoint(50, 42, 1500, lemlib::MoveToPointParams{true, 90}, false);
    
    intake_rollar.move(127);

    chassis.turnToHeading(90,500);

    piston_matchload.set_value(true);

    chassis.moveToPoint(61.6, 42, 800, lemlib::MoveToPointParams{true, 36.5}, false);

    pros::delay(500);

    chassis.moveToPoint(53, 42, 500, lemlib::MoveToPointParams{false, 60}, false);

    chassis.moveToPoint(25, 41.5, 1100, lemlib::MoveToPointParams{false, 90}, false);


    piston_goaldoor.set_value(true);

    chassis.setPose(27, 42, 90);

    plunger.move_velocity(35);

    pros::delay(1300);

    plunger.move(-127);

    intake_rollar.move(-127);

    piston_matchload.set_value(false);

    chassis.moveToPoint(48, 42, 600, lemlib::MoveToPointParams{true, 80}, false);

    pros::delay(100);

    chassis.turnToHeading(225,800);
    
    intake_rollar.move(127);

    chassis.moveToPoint(27.2, 21.9, 1500, lemlib::MoveToPointParams{true, 50}, false);

    pros::delay(300);

    piston_matchload.set_value(true);

    pros::delay(300);

    chassis.moveToPoint(24.7, 18.5, 1500, lemlib::MoveToPointParams{true, 30}, false);

    piston_matchload.set_value(false);

    //chassis.turnToHeading(135,2000);

    piston_goaldoor.set_value(true);

    plunger.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    pros::delay(200);

    chassis.moveToPoint(13.6, 7.2, 5000, lemlib::MoveToPointParams{true, 30}, false);
    
    //piston_body.set_value(true);

    //piston_matchload.set_value(false);

    //plunger.move(40);

    //pros::delay(1000);

    //piston_body.set_value(false);

    intake_rollar.move(-85);
}

void blueAuton2() {
    rightDT.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    leftDT.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    // set position to x:0, y:0, heading:0
    chassis.setPose(0, 0, 0);
    // turn to face heading 90 with a very long timeout
    chassis.turnToHeading(90, 100000);
}

void moveForward96() {
    // Set initial position at origin, facing forward (0 degrees)
    chassis.setPose(0, 0, 0);
    
    // Start position monitoring in a separate task
    volatile bool isMoving = true;
    pros::Task monitorTask([&isMoving]() {
        while (isMoving) {
            lemlib::Pose pose = chassis.getPose();
            std::cout << "X: " << pose.x 
                      << " Y: " << pose.y 
                      << " H: " << pose.theta 
                      << std::endl;
            pros::delay(100);
        }
    });
    
    // Move forward 96 inches (use backwards=true to force forward drive)
    chassis.moveToPoint(0, 96, 5000, lemlib::MoveToPointParams{true, 90}, false);
    // pros::delay(200);
    // // Move backward 96 inches (use backwards=false to force forward drive)
    // chassis.moveToPoint(0, 0, 5000, lemlib::MoveToPointParams{false, 90}, false);

    // Stop the monitoring task
    isMoving = false;
    pros::delay(150);
    
    // Print final position
    lemlib::Pose finalPose = chassis.getPose();
    std::cout << "=== FINAL POSITION ===" << std::endl;
    std::cout << "X: " << finalPose.x 
              << " Y: " << finalPose.y 
              << " H: " << finalPose.theta 
              << std::endl;
}

// 下面 SkillsAuton / 其它函数保持你原文件内容不变（我没删没改逻辑）
// ------- 你的原 Autonomous_Paths.hpp 后续内容 -------

void SkillAuton() {
        piston_arm.set_value(true);
        plunger.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        
        chassis.setPose(50, -11.7, 0);

        //第一个matchload
        chassis.moveToPoint(50, -45, 1500, lemlib::MoveToPointParams{false, 90}, false);
        intake_rollar.move(127);
        chassis.turnToHeading(90,500);
        piston_matchload.set_value(true);
        chassis.moveToPoint(61.65, -45, 1300, lemlib::MoveToPointParams{true, 37.5}, false);
        pros::delay(800);

        //离开第一个点位
        chassis.moveToPoint(48, -45, 1200, lemlib::MoveToPointParams{false, 80}, false);
        piston_matchload.set_value(false);
        chassis.turnToHeading(60,800);
        intake_rollar.move(127);
    
            //移动到第二个点位
            chassis.moveToPoint(34, -58.65, 1500, lemlib::MoveToPointParams{false, 80}, false);
            chassis.turnToHeading(90,1200);
            intake_rollar.move(127);
            
            chassis.moveToPoint(-41, -58.65, 10000, lemlib::MoveToPointParams{false, 90}, false);
            chassis.turnToHeading(0,800);
            intake_rollar.move(127);
            pros::delay(300);
            
            chassis.moveToPoint(-41, -48, 10000, lemlib::MoveToPointParams{true, 90}, false);
            //转向第二个matchload
            chassis.turnToHeading(-90,800);
            intake_rollar.move(127);
            pros::delay(300);
            //score
            
            chassis.moveToPoint(-25, -48, 1100, lemlib::MoveToPointParams{false, 127}, false);
            chassis.setPose(-25, -48, 270);
            piston_goaldoor.set_value(true);
            
            
            intake_rollar.move(127);
            plunger.move_velocity(35);
            pros::delay(1100);
            plunger.move_velocity(-127);
            pros::delay(500);
            piston_goaldoor.set_value(false);
            //吃第二个matchload
            
            
            piston_matchload.set_value(true);
            intake_rollar.move(127);
           
            chassis.moveToPoint(-43, -48, 1500, lemlib::MoveToPointParams{true, 110}, false);
            chassis.moveToPoint(-71, -46, 1500, lemlib::MoveToPointParams{true, 40}, false);
            pros::delay(2000);
            
            //score
            chassis.moveToPoint(-25, -48, 1100, lemlib::MoveToPointParams{false, 90}, false);
            chassis.setPose(-25,-48,270);
            piston_goaldoor.set_value(true);
            piston_matchload.set_value(false);
            plunger.move_velocity(35);
            pros::delay(900);
            plunger.move_velocity(-127);
            pros::delay(500);
            
            
            chassis.moveToPoint(-45, -48, 600, lemlib::MoveToPointParams{true, 100}, false);
            chassis.turnToHeading(0,800);

                //移动到第三个点位
                /*
                chassis.moveToPoint(-45, 49, 1500, lemlib::MoveToPointParams{true, 100}, false);
                chassis.turnToHeading(270,800);
                pros::delay(300);
                piston_matchload.set_value(true);
                pros::delay(300);

                //吃第三个matchload
                chassis.moveToPoint(-70, 49, 1500, lemlib::MoveToPointParams{true, 30}, false);
                chassis.moveToPoint(-50, 49, 1000, lemlib::MoveToPointParams{false, 80}, false);
                piston_matchload.set_value(false);
                chassis.turnToHeading(135,800);
                chassis.moveToPoint(-30, 30, 1500, lemlib::MoveToPointParams{false, 90}, false);
                chassis.turnToHeading(90,500);

                    //到达第四个点位
                    chassis.moveToPoint(41, 30, 800, lemlib::MoveToPointParams{true, 100}, false);
                    pros::delay(500);
                    chassis.turnToHeading(0,500);
                    chassis.moveToPoint(41, 49, 500, lemlib::MoveToPointParams{true, 60}, false);
                    //对准goal
                    chassis.turnToHeading(90,500);
                    piston_matchload.set_value(true);
                    //goal
                    chassis.moveToPoint(27, 49, 1100, lemlib::MoveToPointParams{false, 65}, false);
                    chassis.setPose(27, 49, 270);
                    //matchload
                    chassis.moveToPoint(70, 49, 1100, lemlib::MoveToPointParams{true, 65}, false);
                    chassis.moveToPoint(50, 49, 1100, lemlib::MoveToPointParams{false, 80}, false);
                    piston_matchload.set_value(false);
                    //goal
                    chassis.moveToPoint(27, 49, 1100, lemlib::MoveToPointParams{false, 65}, false);
                    chassis.setPose(27, 49, 90);
                    piston_goaldoor.set_value(true);
                    piston_matchload.set_value(false);
                    pros::delay(900);
                    intake_rollar.move(-127);

                        chassis.moveToPoint(43, 49, 800, lemlib::MoveToPointParams{true, 100}, false);
                        chassis.turnToHeading(0,500);
                        chassis.moveToPoint(43, 30, 800, lemlib::MoveToPointParams{false, 100}, false);
                        chassis.turnToHeading(270,900);
                        chassis.moveToPoint(70, 30, 2000, lemlib::MoveToPointParams{false, 127}, false);
                        chassis.moveToPoint(60, 30, 2000, lemlib::MoveToPointParams{true, 127}, false);
                        chassis.turnToHeading(0,900);
                        chassis.moveToPoint(60, 0, 15000, lemlib::MoveToPointParams{false, 127}, false);

                        */

}
#endif