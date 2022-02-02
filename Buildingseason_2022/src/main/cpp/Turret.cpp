#pragma once
#include <Turret.h>

Turret::Turret(frc::PS4Controller *controller)
{ 
 turret_Joystick = controller;
}

void Turret::Rotation()
{
 if (RotSwitch.Get() == true) {
        Rotation_motor.Set(0);
    }
    else {
        Rotation_motor.Set(SetRotation);
    }
}

void Turret::Angle()
{
 if (AngleSwitch.Get() == true) {
        Angle_motor.Set(0);
    }
    else {
        Angle_motor.Set(SetAngle);
    }
}

void Turret::AngleUpdate()
{
 frc::SmartDashboard::GetNumber("Rotation Turret", SetRotation);
 frc::SmartDashboard::GetNumber("Angle Turret", SetAngle);
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