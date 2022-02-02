// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <fmt/core.h>

#include <frc/smartdashboard/SmartDashboard.h>


void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  intake = new Intake(&Joystick_1);
  swerve = new Swerve(&Joystick_1);
  storage = new Storage(&Joystick_1);
  climb = new Climb(&Joystick_1);
  turret = new Turret(&Joystick_1);

}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  fmt::print("Auto selected: {}\n", m_autoSelected);

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}


void Robot::TeleopInit() {
  swerve->Initialize_swerve();
  swerve->Configure_PID();
  turret->Jetson_Config();
}

void Robot::TeleopPeriodic() {
  ////////Communication between Intake and storage////////
  if(intake->Set_motor_intake_low == true){//Motor from storage turn when in intake motors turn (only when storage isnt full)
    storage->Turn_when_intake_true();
  }
  if(storage->available_balls == 2){
    //storage is full so to not take any more balls motor from intake stops
    //The Pnuematic arm should alway go out so balls doesnt crush when 2 are stored
    intake->Stop_when_full();
  }

  ///////Communication between storage and turret////////
  //if(turret is activated){
  //storage->Turret_activated(); 
  //}
  if(storage->color_sensor_1_state == false){
    //Turret can't shoot
    turret->NoShoot();
  }
  
  intake->mainloop();
  storage->mainloop();
  swerve->Swerve_mainloop();
  turret->turret_mainloop();
  climb->Teleop();
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
