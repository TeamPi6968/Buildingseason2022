#pragma once

#include <frc/DigitalInput.h>
#include <ctre/Phoenix.h>
#include "rev/CANSparkMax.h"
#include <frc/smartdashboard/SmartDashboard.h>

//online link for installing rev libraries https://software-metadata.revrobotics.com/REVLib.json

class Turret
{
 public:

 Turret();
 void Angle ();
 void Rotation ();
 void SmartDashUpdate();
 void HomingAngle();
 void HomingRotation();
 
 double SetRotation;
 double SetAngle;

 private:

 const int LimitSwitchPort_1 = 0;
 const int AngleSwitchPort_1 = 3; //could be id 2, using 3 because of previous years
 frc::DigitalInput RotSwitch {LimitSwitchPort_1};
 frc::DigitalInput AngleSwitch {AngleSwitchPort_1};
 
 const int turret_master_CAN = 19;
 const int turret_slave_CAN = 18;
 const int rotation_motor_CAN = 16;
 const int angle_motor_CAN = 15;

 const int homing_speed = 0.2;

 WPI_TalonFX Turret_master {turret_master_CAN};
 WPI_TalonFX Turret_slave {turret_slave_CAN};
 rev::CANSparkMax Rotation_motor{rotation_motor_CAN, rev::CANSparkMax::MotorType::kBrushless};
 rev::CANSparkMax Angle_motor{angle_motor_CAN, rev::CANSparkMax::MotorType::kBrushless};

 rev::SparkMaxRelativeEncoder Rotation_encoder = Rotation_motor.GetEncoder();
 rev::SparkMaxRelativeEncoder Angle_encoder = Angle_motor.GetEncoder();
};