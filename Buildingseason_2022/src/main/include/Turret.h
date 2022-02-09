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
 void Angle(double angle);
 void Rotation(int X_camera);
 void AngleUpdate();
 void HomingAngle();
 void HomingRotation();
 void Configure_Turret_PID();
 void turret_Teleop(double angle, double rotation);
 void Shoot();
 void NoShoot();
 void Jetson();
 void Jetson_Config();
 void ShootCalc(double depth);
  

 Turret(frc::PS4Controller *controller);

 float SetRotation = 0;
 float SetAngle = 0;
 bool Set_Shot = false;
 int X_Camera = 0;
 int X_Center = 300;
 int Y = 0;
 int Y_Center = 300;
 double motorSpeedL = 0.2;
 double motorSpeedR = 0.2;
 double rotation;
 double angle;
 double Depth_camera;
 double shootSpeed;
 double rotateSpeed;
 double angleSpeed;
 double max_steps;//value has to be made

 //timer config
 units::second_t read_time_shooter;//read the current time
 units::second_t period_shooter {10};//Delay time
 frc::Timer timer_Shooter{};

  double X1 = 0;//start shooting at zero
  double Y1 = 0.64;//intiial height ball
  double X2;//x value of distance camera
  double Y2 = 3.25;// hight hub + radius hub in height
  double X3;;//measured distance + radius hub
  double Y3 = 2.64;//Height of the hub
  double a;
  double b;
  double c = Y1;
  double angle_shot;//angle of shot
  double velocity;//speed of shooting in m/s
  double motorspeed_rpm;
  double max_motorspeed_rpm = 6380;
  double radius = 0.0254;//radius in meters (2inch wheel)
  double motorspeed;
 

 private:
//controller confic
 frc::PS4Controller *turret_Joystick;


// Limit swtiches config
 const int LimitSwitchPort_L = 0;
 const int LimitSwitchPort_R = 0;
 const int AngleSwitchPort_U = 2;
 const int AngleSwitchPort_D = 2;
 frc::DigitalInput RotSwitchL {LimitSwitchPort_L};
 frc::DigitalInput RotSwitchR {LimitSwitchPort_R};
 frc::DigitalInput AngleSwitchU {AngleSwitchPort_U};
 frc::DigitalInput AngleSwitchD {AngleSwitchPort_D};

 //Motor can config
 const int turret_High_CAN = 14;
 const int turret_master_CAN = 15;
 const int turret_slave_CAN = 16;
 const int rotation_motor_CAN = 17;
 const int angle_motor_CAN = 19;
   
//PID values of the Rotation

  double kP_R = 0.1, kI_R  = 1e-4, kD_R  = 1, kMaxOutput_R = 1, kMinOutput_R = -1;
//PID values of the Angle
double kP_A = 0.1, kI_A  = 1e-4, kD_A  = 1, kMaxOutput_A = 1, kMinOutput_A = -1;



// Motor config
 WPI_TalonFX Turret_master {turret_master_CAN};
 WPI_TalonFX Turret_slave {turret_slave_CAN};
 WPI_TalonFX Turret_HIGH {turret_High_CAN};
 rev::CANSparkMax Rotation_motor{rotation_motor_CAN, rev::CANSparkMax::MotorType::kBrushless};
 rev::CANSparkMax Angle_motor{angle_motor_CAN, rev::CANSparkMax::MotorType::kBrushless};
 

// Encoder config
 rev::SparkMaxRelativeEncoder Rotation_encoder = Rotation_motor.GetEncoder();
 rev::SparkMaxRelativeEncoder Angle_encoder = Angle_motor.GetEncoder();
 rev::SparkMaxPIDController R_pidController = Rotation_motor.GetPIDController();
 rev::SparkMaxPIDController A_pidController = Angle_motor.GetPIDController();
};