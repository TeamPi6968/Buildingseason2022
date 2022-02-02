#pragma once

#include <frc/DigitalInput.h>
#include <ctre/Phoenix.h>
#include "rev/CANSparkMax.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/PS4Controller.h>

//online link for installing rev libraries https://software-metadata.revrobotics.com/REVLib.json

class Turret
{
 public:
// functions
 void Angle ();
 void Rotation ();
 void AngleUpdate();
 void HomingAngle();
 void HomingRotation();
 void turret_mainloop();

 Turret(frc::PS4Controller *controller);

 float SetRotation = 0;
 float SetAngle = 0;

 

 private:
//controller confic
 frc::PS4Controller *turret_Joystick;

// Limit swtiches config
 const int LimitSwitchPort_1 = 0;
 const int LimitSwitchPort_2 = 0;
 const int AngleSwitchPort_1 = 2;
 const int AngleSwitchPort_2 = 2;
 frc::DigitalInput RotSwitch {LimitSwitchPort_1};
 frc::DigitalInput RotSwitch2 {LimitSwitchPort_2};
 frc::DigitalInput AngleSwitch {AngleSwitchPort_1};
 frc::DigitalInput AngleSwitch2 {AngleSwitchPort_2};

 //Motor can config
 const int turret_High_CAN = 14;
 const int turret_master_CAN = 15;
 const int turret_slave_CAN = 16;
 const int rotation_motor_CAN = 17;
 const int angle_motor_CAN = 19;

 const int homing_speed = 0.2;

// Motor config
 WPI_TalonFX Turret_master {turret_master_CAN};
 WPI_TalonFX Turret_slave {turret_slave_CAN};
 WPI_TalonFX Turret_HIGH {turret_High_CAN};
 rev::CANSparkMax Rotation_motor{rotation_motor_CAN, rev::CANSparkMax::MotorType::kBrushless};
 rev::CANSparkMax Angle_motor{angle_motor_CAN, rev::CANSparkMax::MotorType::kBrushless};

// Encoder config
 rev::SparkMaxRelativeEncoder Rotation_encoder = Rotation_motor.GetEncoder();
 rev::SparkMaxRelativeEncoder Angle_encoder = Angle_motor.GetEncoder();
};