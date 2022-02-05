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


}

void Turret::ShootCalc(double X, double y, double depth)
{
rotation = X; // calculation for the rotation for the turret using the X value from the camera
angle = Y; // calculation for the angle for the turret using the Y value from the camera
shootSpeed = depth; // calculations for the shootingspeed for the the turret using the depth;
}

void Turret::Rotation(double rotation)
{
rotateSpeed = turret_Joystick->GetLeftX() * 0.2;

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
        if(X < X_Center)
    {
        Rotation_motor.Set(motorSpeedL);
    }
          else if(X >= X_Center)
    {
        Rotation_motor.Set(0);
    }
    else 
    {
        R_pidController.SetReference(rotation, rev::ControlType::kPosition);
    }
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