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

 Turret(frc::PS4Controller *controller);

 void Angle ();
 void Rotation ();
 void SmartDashUpdate();
 void HomingAngle();
 void HomingRotation();
 void Configure_Turret_PID();
 void Shoot();

 double SetRotation;
 double SetAngle;

 double kP_R = 0.001, kI_R  = 1e-6, kD_R  = 2, kMaxOutput_R = 0.3, kMinOutput_R = -0.3;

 double shootSpeed;
//  bool shoot = turret_Joystick.GetCrossButton();

 private:

 frc::PS4Controller *turret_Joystick;

 const int LimitSwitchPort_1 = 0;
 const int AngleSwitchPort_1 = 3; //could be id 2, using 3 because of previous years
 frc::DigitalInput RotSwitch {LimitSwitchPort_1};
 frc::DigitalInput AngleSwitch {AngleSwitchPort_1};
 
 const int turret_master_CAN = 19; //wrong ID
 const int turret_slave_CAN = 18; //wrong ID
 const int rotation_motor_CAN = 16;
 const int angle_motor_CAN = 15;

 const int homing_speed = 0.2;

 int minAngleEncoder = -45;
 int maxAngleEncoder = -3;

 int minRotationEncoder = -40;
 int maxRotationEncoder = 60;

 //PID values of the Rotation
 //double kP_R = 0.001, kI_R  = 1e-6, kD_R  = 2, kMaxOutput_R = 0.3, kMinOutput_R = -0.3;
 //PID values of the Angle
 double kP_A = 0.1, kI_A  = 1e-4, kD_A  = 1, kMaxOutput_A = 1, kMinOutput_A = -1;


 WPI_TalonFX Turret_master {turret_master_CAN};
 WPI_TalonFX Turret_slave {turret_slave_CAN};
 rev::CANSparkMax Rotation_motor{rotation_motor_CAN, rev::CANSparkMax::MotorType::kBrushless};
 rev::CANSparkMax Angle_motor{angle_motor_CAN, rev::CANSparkMax::MotorType::kBrushless};


 //Encoder Config including PID config
 rev::SparkMaxRelativeEncoder Rotation_encoder = Rotation_motor.GetEncoder();
 rev::SparkMaxRelativeEncoder Angle_encoder = Angle_motor.GetEncoder();
 rev::SparkMaxPIDController R_pidController = Rotation_motor.GetPIDController();
 rev::SparkMaxPIDController A_pidController = Angle_motor.GetPIDController();
};