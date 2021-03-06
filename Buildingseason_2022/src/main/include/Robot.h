// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.


#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/PS4Controller.h>
#include <frc/Compressor.h>
#include <units/pressure.h>

#include "Intake.h"
#include "Swerve.h"
#include "Storage.h"
#include "Climb.h"
#include "Turret.h"

class Robot : public frc::TimedRobot {
 public:
  Intake *intake;
  Swerve *swerve;
  Storage *storage;
  Climb *climb;
  Turret *turret;

  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;
  //ctre::phoenix::motorcontrol::can::TalonFX motor_1{0};
 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;
  frc::PS4Controller Joystick_1{0};

  frc::Compressor compressor{1, frc::PneumaticsModuleType::REVPH};
  units::pressure::pounds_per_square_inch_t MinimumPressure = 95_psi;
  units::pressure::pounds_per_square_inch_t MaximumPressure = 115_psi;
  bool dissableCompressor = false;
};



