#ifndef AUTONOMOUS_PATHS_HPP
#define AUTONOMOUS_PATHS_HPP

#include "globals.hpp"



void redAuton1() {
    piston_arm.set_value(true);
    plunger.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    
    chassis.setPose(50, -11.7, 0);

    chassis.moveToPoint(50, -45, 1500, lemlib::MoveToPointParams{false, 90}, false);
    
    intake_rollar.move(127);

    chassis.turnToHeading(90,500);

    piston_matchload.set_value(true);

    chassis.moveToPoint(61, -45, 800, lemlib::MoveToPointParams{true, 36.5}, false);

    pros::delay(500);

    chassis.moveToPoint(53, -45, 500, lemlib::MoveToPointParams{false, 60}, false);

    chassis.moveToPoint(27.5, -45, 1100, lemlib::MoveToPointParams{false, 65}, false);

    

    piston_goaldoor.set_value(true);

    plunger.move_velocity(80);

    pros::delay(900);

    plunger.move(-127);
    
    chassis.setPose(28, -45, 90);

    intake_rollar.move(-127);

    piston_matchload.set_value(false);

    chassis.moveToPoint(48, -45, 600, lemlib::MoveToPointParams{true, 80}, false);

    //pros::delay(100);

    chassis.turnToHeading(315,800);

    plunger.move_velocity(0);
    
    intake_rollar.move(127);

    chassis.moveToPoint(26, -25.5, 1500, lemlib::MoveToPointParams{true, 50}, false);

    pros::delay(300);

    piston_matchload.set_value(true);

    pros::delay(300);

    chassis.moveToPoint(20, -20.5, 1500, lemlib::MoveToPointParams{true, 30}, false);

    chassis.turnToHeading(135,2000);

    piston_goaldoor.set_value(true);

    plunger.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    pros::delay(200);

    chassis.moveToPoint(10.4, -9.1, 5000, lemlib::MoveToPointParams{false, 30}, false);
    
    piston_body.set_value(true);

    //piston_matchload.set_value(false);

    plunger.move(65);

    pros::delay(1000);

    piston_body.set_value(false);
}

void redAuton2() {

}

void redAuton3() {
   
}

void redAuton4() {
    
}

void blueAuton1() {
}

void blueAuton2() {

}


void SkillAuton() {

}

void coordinateTest() {
    // Test 1: Start position
    chassis.setPose(50, -11.7, 0);
    pros::delay(2000);
    
    // Test 2: Move to (50, -45)
    std::cout << "Moving to (50, -45)" << std::endl;
    chassis.moveToPoint(50, -45, 5000);
    pros::delay(3000);
    
    // Test 3: Move to origin
    std::cout << "Moving to (0, 0)" << std::endl;
    chassis.moveToPoint(0, 0, 5000);
    pros::delay(3000);
    
    // Test 4: Move to (72, 0) - should be right wall
    std::cout << "Moving to (72, 0)" << std::endl;
    chassis.moveToPoint(72, 0, 5000);
    pros::delay(10000);
}

#endif