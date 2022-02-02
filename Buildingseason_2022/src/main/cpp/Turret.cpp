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
}

void Turret::Jetson()
{
// imitating input from the Jetson
 double rotation = frc::SmartDashboard::GetNumber("rotation",0);
 double angle = frc::SmartDashboard::GetNumber("angle",0);
 Rotation(rotation);
}

void Turret::Rotation(double rotation)
{

 if (RotSwitch.Get() == true || RotSwitch2.Get() == true) {
        Rotation_motor.Set(0);
    }
    else {
    R_pidController.SetReference(rotation, rev::ControlType::kPosition);
    }
}

void Turret::Angle(double angle)
{
frc::SmartDashboard::GetNumber("Angle Turret", SetAngle);
 if (AngleSwitch.Get() == true) {
        Angle_motor.Set(0);
    }
    else {
        Angle_motor.Set(SetAngle);
        A_pidController.SetReference(angle, rev::ControlType::kPosition);
    }
}

void Turret::Shoot()
{
bool Shoot_button = turret_Joystick->GetCrossButton();

 if(Shoot_button == true)
 {
     Turret_HIGH.Set(ControlMode::PercentOutput, ShooterSpeed);
     Turret_master.Set(ControlMode::PercentOutput, ShooterSpeed);
     Shot = true;
 }
 else{
     Turret_HIGH.Set(ControlMode::PercentOutput, 0);
     Turret_master.Set(ControlMode::PercentOutput, 0);
     Shot = false;
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

void Turret::turret_mainloop()
{
    

}