#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
motor leftMotorA = motor(PORT1, ratio18_1, false);
motor leftMotorB = motor(PORT3, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT2, ratio18_1, true);
motor rightMotorB = motor(PORT4, ratio18_1, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);

motor Claw = motor(PORT6, ratio18_1, false);

motor LiftMotorA = motor(PORT5, ratio36_1, false);
motor LiftMotorB = motor(PORT7, ratio36_1, true);
motor_group Lift = motor_group(LiftMotorA, LiftMotorB);



// generating and setting random seed
void initializeRandomSeed(){
  int systemTime = Brain.Timer.systemHighResolution();
  double batteryCurrent = Brain.Battery.current();
  double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);

  // Combine these values into a single integer
  int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;

  // Set the seed
  srand(seed);
}



void vexcodeInit() {

  //Initializing random seed.
  initializeRandomSeed(); 
}


// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}

#pragma endregion VEXcode Generated Robot Configuration

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       Left Comp Code.cpp                                        */
/*    Author:       Anika                                                     */
/*    Created:      10/10/26                                                  */
/*    Description:  Code for competitions on the blue alliance                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;
controller Controller = controller(primary);
competition Competition;


void auton() {
  Drivetrain.setDriveVelocity(100, percent);
  Drivetrain.driveFor(forward, 24, inches);
  // Toggle.spinFor(reverse, 90, degrees);
  Drivetrain.driveFor(reverse, 12, inches);
}

void user_control() {
  while (true) {
    // Arcade Drive Setup
    int forwardMotion = Controller.Axis3.position();
    int turnMotion = Controller.Axis1.position();
    int leftSpeed = forwardMotion + turnMotion;
    int rightSpeed = forwardMotion - turnMotion;

    leftMotorA.setVelocity(leftSpeed, percent);
    leftMotorA.spin(reverse);
    leftMotorB.setVelocity(leftSpeed, percent);
    leftMotorB.spin(reverse);

    rightMotorA.setVelocity(rightSpeed, percent);
    rightMotorA.spin(reverse);
    rightMotorB.setVelocity(rightSpeed, percent);
    rightMotorB.spin(reverse);

    // Lift Setup
    Lift.setVelocity(100, percent);
    if (Controller.ButtonL1.pressing()) {
      Lift.spin(forward);        // raise lift
    }
    else if (Controller.ButtonL2.pressing()) {
      Lift.spin(reverse);        // lower lift
    }

    // Claw Grip Setup
    Claw.setVelocity(100, percent);
    if (Controller.ButtonR1.pressing()) {
      Claw.spin(reverse);          // open claw
    }
    else if (Controller.ButtonR2.pressing()) {
      Claw.spin(forward);          // close claw
    }
    else {
      Claw.stop();
    }

    wait(5, msec);
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // Begin project code
  Brain.Screen.clearScreen();
  Competition.autonomous(auton);
  Competition.drivercontrol(user_control);
}
