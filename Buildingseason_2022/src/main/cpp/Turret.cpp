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

void Turret::Rotation()
{
double rotations = frc::SmartDashboard::GetNumber("Rotation Turret", SetRotation);
 if (RotSwitch.Get() == true || RotSwitch2.Get() == true) {
        Rotation_motor.Set(0);
    }
    else {
    R_pidController.SetReference(rotations, rev::ControlType::kPosition);
    }
}

void Turret::Angle()
{
frc::SmartDashboard::GetNumber("Angle Turret", SetAngle);
 if (AngleSwitch.Get() == true) {
        Angle_motor.Set(0);
    }
    else {
        Angle_motor.Set(SetAngle);
    }
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