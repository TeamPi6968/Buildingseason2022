#pragma once
#include <Turret.h>



Turret::Turret(frc::PS4Controller *controller)
{ 
 turret_Joystick = controller;
 Turret_master.SetInverted(true);
 Turret_slave.SetInverted(false);
 Turret_slave.Follow(Turret_master);
}

void Turret::Configure_Turret_PID()
{
    // Rotation PID config
    R_pidController.SetP(kP_R);
    R_pidController.SetI(kI_R);
    R_pidController.SetD(kD_R);
    R_pidController.SetOutputRange(kMinOutput_R, kMaxOutput_R);

    // Rotation PID config
    A_pidController.SetP(kP_A);
    A_pidController.SetI(kI_A);
    A_pidController.SetD(kD_A);
    A_pidController.SetOutputRange(kMinOutput_A, kMaxOutput_A);
}

void Turret::Jetson_Config()
{
frc::SmartDashboard::PutNumber("rotation",0);
frc::SmartDashboard::PutNumber("angle",0);
frc::SmartDashboard::PutNumber("X",0);
frc::SmartDashboard::PutNumber("Y",0);
frc::SmartDashboard::PutNumber("Depth",0);
frc::SmartDashboard::PutNumber("shooting speed",0);
}

void Turret::Jetson()
{
// imitating input from the Jetson
 double rotation = frc::SmartDashboard::GetNumber("rotation",0);
 double angle = frc::SmartDashboard::GetNumber("angle",0);
 
 rotation = frc::SmartDashboard::GetNumber("rotation",0);
 angle = frc::SmartDashboard::GetNumber("angle",0);
 X = frc::SmartDashboard::GetNumber("X",0);
 Y = frc::SmartDashboard::GetNumber("Y",0);
 Depth = frc::SmartDashboard::GetNumber("Depth",0);
 shootSpeed = frc::SmartDashboard::GetNumber("shooting speed",0);

 
 // Rotation calculations with X

 // Angle calculations with Y

 // motor calculations with the Depth
}

void Turret::Rotation(double rotation)
{

R_pidController.SetReference(rotation, rev::ControlType::kPosition);

if(RotSwitchL.Get() == true)
{
    if(X < X_Center)
    {
        Rotation_motor.Set(0);
    }
          else if(X >= X_Center)
    {
        Rotation_motor.Set(motorSpeedR);
    }
}

else if(RotSwitchR.Get() == true)
{
        if(X < 300)
    {
        Rotation_motor.Set(motorSpeedL);
    }
          else if(X >= 300)
    {
        Rotation_motor.Set(0);
    }
}
}

void Turret::Angle(double angle)
{
A_pidController.SetReference(rotation, rev::ControlType::kPosition);

if(AngleSwitchD.Get() == true)
{
    if(Y < Y_Center)
    {
        Angle_motor.Set(0);
    }
          else if(X >= Y_Center)
    {
        Angle_motor.Set(motorSpeedR);
    }
}

else if(AngleSwitchU.Get() == true)
{
        if(Y < Y_Center)
    {
        Angle_motor.Set(motorSpeedL);
    }
          else if(Y >= Y_Center)
    {
        Angle_motor.Set(0);
    }
}
}

void Turret::Shoot()
{
    if(Set_Shot == true){
     Turret_HIGH.Set(ControlMode::PercentOutput, shootSpeed);
     Turret_master.Set(ControlMode::PercentOutput, shootSpeed);
     if(timer_Shooter.Get()>period_shooter){
        Set_Shot == false;
     }
    }
}

void Turret::NoShoot()
{
    Turret_HIGH.Set(ControlMode::PercentOutput, 0);
    Turret_master.Set(ControlMode::PercentOutput, 0);
}


void Turret::HomingAngle()
{

}

void Turret::HomingRotation()
{

}

void Turret::turret_Teleop(double angle, double rotation)
{
    Turret::Jetson();
    Turret::Rotation(rotation);
    Turret::Angle(angle);

}