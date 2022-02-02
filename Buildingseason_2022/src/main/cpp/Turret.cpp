#include <Turret_Class.h>

Turret::Turret()
{ 
 Turret_slave.Follow(Turret_master);
 Turret_master.SetInverted(TalonFXInvertType::Clockwise);
 Turret_slave.SetInverted(TalonFXInvertType::CounterClockwise);
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