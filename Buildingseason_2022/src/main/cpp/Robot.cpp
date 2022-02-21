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
  swerve = new Swerve(&Joystick_1);
 

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
  
}

void Robot::TeleopPeriodic() {
frc::SmartDashboard::PutNumber("sensor",test_1.Get());
swerve->Swerve_mainloop();
/*
bool Joystick_rotation = Joystick_1.GetSquareButton();
if(Joystick_rotation == true){
  swerve->motorFLD.Set(ControlMode::PercentOutput,0.3);
  swerve->motorFRD.Set(ControlMode::PercentOutput,-0.3);
  swerve->motorRLD.Set(ControlMode::PercentOutput,0.3);
  swerve->motorRRD.Set(ControlMode::PercentOutput,-0.3);
  swerve->motorFRR.Set(ControlMode::Position, 0*swerve->oneTurn);  
  swerve->motorFLR.Set(ControlMode::Position, 0*swerve->oneTurn);     
  swerve->motorRLR.Set(ControlMode::Position, 0*swerve->oneTurn);     
  swerve->motorRRR.Set(ControlMode::Position, 0*swerve->oneTurn);
}
else if(Joystick_rotation == false){
  swerve->motorFLD.Set(ControlMode::PercentOutput,0);
  swerve->motorFRD.Set(ControlMode::PercentOutput,0);
  swerve->motorRLD.Set(ControlMode::PercentOutput,0);
  swerve->motorRRD.Set(ControlMode::PercentOutput,0);
  swerve->motorFRR.Set(ControlMode::Position, 0*swerve->oneTurn);  
  swerve->motorFLR.Set(ControlMode::Position, 0*swerve->oneTurn);     
  swerve->motorRLR.Set(ControlMode::Position, 0*swerve->oneTurn);     
  swerve->motorRRR.Set(ControlMode::Position, 0*swerve->oneTurn);
}
bool Joystick_rotation_L = Joystick_1.GetTriangleButton();
if(Joystick_rotation_L == true){
  swerve->motorFLD.Set(ControlMode::PercentOutput,-0.3);
  swerve->motorFRD.Set(ControlMode::PercentOutput,0.3);
  swerve->motorRLD.Set(ControlMode::PercentOutput,-0.3);
  swerve->motorRRD.Set(ControlMode::PercentOutput,0.3);
  swerve->motorFRR.Set(ControlMode::Position, 0*swerve->oneTurn);  
  swerve->motorFLR.Set(ControlMode::Position, 0*swerve->oneTurn);     
  swerve->motorRLR.Set(ControlMode::Position, 0*swerve->oneTurn);     
  swerve->motorRRR.Set(ControlMode::Position, 0*swerve->oneTurn);

}
else if(Joystick_rotation_L == false&& Joystick_rotation == false){
  swerve->motorFLR.Set(ControlMode::PercentOutput,0);
  swerve->motorFRR.Set(ControlMode::PercentOutput,0);
  swerve->motorRLR.Set(ControlMode::PercentOutput,0);
  swerve->motorRRR.Set(ControlMode::PercentOutput,0);
  swerve->motorFRR.Set(ControlMode::Position, 0*swerve->oneTurn); 
  swerve->motorFLR.Set(ControlMode::Position, 0*swerve->oneTurn);     
  swerve->motorRLR.Set(ControlMode::Position, 0*swerve->oneTurn);     
  swerve->motorRRR.Set(ControlMode::Position, 0*swerve->oneTurn); 
}
bool Joystick_speed = Joystick_1.GetCircleButton();
if(Joystick_speed == true){
  swerve->motorFLD.Set(ControlMode::PercentOutput,-0.3);
  swerve->motorFRD.Set(ControlMode::PercentOutput,0.3);
  swerve->motorRLD.Set(ControlMode::PercentOutput,-0.3);
  swerve->motorRRD.Set(ControlMode::PercentOutput,0.3);
  swerve->motorFRR.Set(ControlMode::Position, 2.5*swerve->oneTurn);  
  swerve->motorFLR.Set(ControlMode::Position, 2.5*swerve->oneTurn);     
  swerve->motorRLR.Set(ControlMode::Position, 2.5*swerve->oneTurn);     
  swerve->motorRRR.Set(ControlMode::Position, 2.5*swerve->oneTurn);
}
else if(Joystick_speed == false){
  swerve->motorFLD.Set(ControlMode::PercentOutput,0);
  swerve->motorFRD.Set(ControlMode::PercentOutput,0);
  swerve->motorRLD.Set(ControlMode::PercentOutput,0);
  swerve->motorRRD.Set(ControlMode::PercentOutput,0);
  swerve->motorFRR.Set(ControlMode::Position, 2.5*swerve->oneTurn); 
  swerve->motorFLR.Set(ControlMode::Position, 2.5*swerve->oneTurn);     
  swerve->motorRLR.Set(ControlMode::Position, 2.5*swerve->oneTurn);     
  swerve->motorRRR.Set(ControlMode::Position, 2.5*swerve->oneTurn); 
}
bool Joystick_speed_L = Joystick_1.GetCrossButton();
if(Joystick_speed_L == true){
  swerve->motorFLD.Set(ControlMode::PercentOutput,0.3);
  swerve->motorFRD.Set(ControlMode::PercentOutput,-0.3);
  swerve->motorRLD.Set(ControlMode::PercentOutput,0.3);
  swerve->motorRRD.Set(ControlMode::PercentOutput,-0.3);
  swerve->motorFRR.Set(ControlMode::Position, 2.5*swerve->oneTurn);  
  swerve->motorFLR.Set(ControlMode::Position, 2.5*swerve->oneTurn);     
  swerve->motorRLR.Set(ControlMode::Position, 2.5*swerve->oneTurn);     
  swerve->motorRRR.Set(ControlMode::Position, 2.5*swerve->oneTurn);
}
else if(Joystick_speed == false && Joystick_speed_L == false){
  swerve->motorFLD.Set(ControlMode::PercentOutput,0);
  swerve->motorFRD.Set(ControlMode::PercentOutput,0);
  swerve->motorRLD.Set(ControlMode::PercentOutput,0);
  swerve->motorRRD.Set(ControlMode::PercentOutput,0);
  swerve->motorFRR.Set(ControlMode::Position, 2.5*swerve->oneTurn);  
  swerve->motorFLR.Set(ControlMode::Position, 2.5*swerve->oneTurn);     
  swerve->motorRLR.Set(ControlMode::Position, 2.5*swerve->oneTurn);     
  swerve->motorRRR.Set(ControlMode::Position, 2.5*swerve->oneTurn);
}
/*
//else if(Joystick_speed_L == false){
//  swerve->motorFLD.Set(ControlMode::PercentOutput,0);
//}
// <<<<<<< Updated upstream:Buildingseason_2022/src/main/cpp/Robot.cpp
//   swerve->Swerve_mainloop();
// =======
//   //  //storage->mainloop();
//   //   bool joystick_value_turret = Joystick_1.GetCircleButton();
//   // //id 15
//   // if(joystick_value_turret == true){
//   //   frc::SmartDashboard::PutNumber("joystick value 1",joystick_value_turret);
//   //   storage->motor_turret.Set(0.3);
//   // }
//   bool joystick_value_intake = Joystick_1.GetCircleButton();
//   //id 10
//   if(joystick_value_intake == true){
//    // frc::SmartDashboard::PutNumber("joystick value 2",joystick_value_intake);
//     storage->motor_2to1.Set(0.6);
//    // storage->motor_turret.Set(0.5);
//   }else if (joystick_value_intake == false)
//   {
//    storage->motor_2to1.Set(0);
//   }
//    bool joystick_value_Storage = Joystick_1.GetSquareButton();
//   //id 10
//   if(joystick_value_Storage == true){
//     //frc::SmartDashboard::PutNumber("joystick value 2",joystick_value_intake);
//     //storage->motor_2to1.Set(0.6);
//     storage->motor_turret.Set(0.5);
//   }
//   else if (joystick_value_Storage == false)
//   {
//     storage->motor_turret.Set(0);
//   }

// >>>>>>> Stashed changes:Buildingseason_2022/src/main/cpp/Robot_storage.cpp*/
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {
  // bool joystick_value_turret = Joystick_1.GetCrossButton();
  
  // if(joystick_value_turret == true){
  //   frc::SmartDashboard::PutNumber("joystick value 1",joystick_value_turret);
  //   storage->motor_turret.Set(0.3);
  // }
  // bool joystick_value_intake = Joystick_1.GetSquareButton();
  
  // if(joystick_value_intake == true){
  //   frc::SmartDashboard::PutNumber("joystick value 2",joystick_value_intake);
  //   storage->motor_2to1.Set(0.3);
  // }
}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
