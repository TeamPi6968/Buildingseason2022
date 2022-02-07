#pragma once

#include <frc/DigitalInput.h>
#include <ctre/Phoenix.h>
#include "rev/CANSparkMax.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/PS4Controller.h>
#include "Turret_Class.h"

//online link for installing rev libraries https://software-metadata.revrobotics.com/REVLib.json

class Turret
{
 public:

 Turret(frc::PS4Controller *controller);

 void Angle ();
 void Rotation ();
 void SmartDashUpdate();
 void CalibrationAngle();
 void CalibrationRotation();
 void Calibration();
 void Configure_Turret_PID();
 void RotationHome();
 void AngleHome();
 void Reset();
 void Shoot();

 //value for Rotation from Jetson (imitation)
 double SetRotation;
 //value for Angle from Jetson (imitation)
 double SetAngle;
 
 //PID values for rotation, in public because we are fine tuning them
 double kP_R = 0.1, kI_R  = 1e-6, kD_R  = 1.5, kMaxOutput_R = 0.3, kMinOutput_R = -0.3;

 //Shooting speed variable
 double shootSpeed;

 bool TriangleBut;
 bool SquareBut;
 bool HomingRotationSet = false;
 bool HomingAngleSet = false;

 bool AngleCalibrated = false;
 bool RotationCalibrated = false;
 bool Calibrated = false;
 bool AngleLimitTouched;
 bool RotationLimitTouched;

 private:

 frc::PS4Controller *turret_Joystick;
 
 //ID's for motors
 const int turret_master_CAN = 9; //could be wrong, using this ID from 2021 code
 const int turret_slave_CAN = 10; //could be wrong, using this ID from 2021 code
 const int rotation_motor_CAN = 16;
 const int angle_motor_CAN = 15;

 //limitswitch ports
 const int LimitSwitchPort_1 = 0;
 const int AngleSwitchPort_1 = 3; //could be id 2, using 3 because of previous years
 frc::DigitalInput RotSwitch {LimitSwitchPort_1};
 frc::DigitalInput AngleSwitch {AngleSwitchPort_1};


 //homing speed for rotation and angle
 const int rotation_speed = 0.1;
 const int angle_speed = 0.1;

 //max and min angles for encoders
 int minAngleEncoder = -45;
 int maxAngleEncoder = -3;

 int minRotationEncoder = -20; //fine tune later
 int maxRotationEncoder = 35;

 //PID values of the Rotation
 //double kP_R = 0.001, kI_R  = 1e-6, kD_R  = 2, kMaxOutput_R = 0.3, kMinOutput_R = -0.3;
 //PID values of the Angle
 double kP_A = 0.1, kI_A  = 1e-4, kD_A  = 1, kMaxOutput_A = 1, kMinOutput_A = -1;


 // Motor Initialization for rotation, angle and TalonFX for shooting
 WPI_TalonFX* Turret_master = new WPI_TalonFX{turret_master_CAN}; //changed brackets from {} to ()
 WPI_TalonFX* Turret_slave = new WPI_TalonFX{turret_slave_CAN};
 rev::CANSparkMax Rotation_motor{rotation_motor_CAN, rev::CANSparkMax::MotorType::kBrushless};
 rev::CANSparkMax Angle_motor{angle_motor_CAN, rev::CANSparkMax::MotorType::kBrushless};


 //Encoder Config and PID config
 rev::SparkMaxRelativeEncoder Rotation_encoder = Rotation_motor.GetEncoder();
 rev::SparkMaxRelativeEncoder Angle_encoder = Angle_motor.GetEncoder();
 rev::SparkMaxPIDController R_pidController = Rotation_motor.GetPIDController();
 rev::SparkMaxPIDController A_pidController = Angle_motor.GetPIDController();
};