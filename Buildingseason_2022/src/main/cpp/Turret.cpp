#pragma once
#include "Turret.h"

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
 X_Camera = frc::SmartDashboard::GetNumber("X",0);
 Y = frc::SmartDashboard::GetNumber("Y",0);
 Depth_camera = frc::SmartDashboard::GetNumber("Depth",0);
 shootSpeed = frc::SmartDashboard::GetNumber("shooting speed",0);


}

void Turret::ShootCalc(double depth)
{
//One of the X2 calculations (testing from camera)
X2 = sqrt((pow(depth,2))-(pow(Y3,2)));//x value of the depth
X3 = X2+0.61;//x value of depth + radius of hub
//formula ax^2+b*x+c is used
a = ((Y2 - c)*X3-(Y3-c)*X2)/(pow(X2,2)*X3-pow(X3,2)*X2);//calculate a
b = (Y2 - a*pow(X2,2)-c)/X2;//calculate b
angle_shot = tan(b/1);//slope is always value b so angle can be calculated
velocity = sqrt((9.81*pow(X2,2))/((X2*tan(angle_shot)-Y3 + Y1)*(2*pow(cos(angle_shot),2))));//velocity in m/s
motorspeed_rpm = (60*velocity)/(2*M_PI*radius);
motorspeed = motorspeed_rpm/max_motorspeed_rpm;
}

void Turret::Rotation(int X_Camera)
{
rotation = ((X_Camera - X_Center)/(X_Center))*max_steps;
rotateSpeed = turret_Joystick->GetLeftX() * 0.2;
if(X_Camera > X_Center){
R_pidController.SetReference(rotation, rev::ControlType::kPosition);
}
if(X_Camera < X_Center){

}
if(X_Camera = X_Center){

}

 if(RotSwitchL.Get() == true)
{
    if(X_Camera < X_Center)
    {
        Rotation_motor.Set(0);
    }
          else if(X_Camera >= X_Center)
    {
        Rotation_motor.Set(motorSpeedR);
    }
}

else if(RotSwitchR.Get() == true)
{
        if(X_Camera < X_Center)
    {
        Rotation_motor.Set(motorSpeedL);
    }
          else if(X_Camera >= X_Center)
    {
        Rotation_motor.Set(0);
    }
    //else 
    //{
    //    R_pidController.SetReference(rotation, rev::ControlType::kPosition);
    //}
}

else if(turret_Joystick->GetR1Button() == 1 && turret_Joystick->GetLeftX()) 
{
Rotation_motor.Set(rotateSpeed);
}
}

void Turret::Angle(double angle)
{
angleSpeed = turret_Joystick->GetLeftY() * 0.2;
if(AngleSwitchD.Get() == true)
{
    if(Y < Y_Center)
    {
        Angle_motor.Set(0);
    }
          else if(X_Camera >= Y_Center)
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

else if(turret_Joystick->GetR1Button() == 1 && turret_Joystick->GetLeftY()) 
{
        Angle_motor.Set(angleSpeed);
}
else 
{
A_pidController.SetReference(angle, rev::ControlType::kPosition);
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