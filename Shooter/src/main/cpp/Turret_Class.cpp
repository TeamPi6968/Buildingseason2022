#include <Turret_Class.h>
#include <iostream>

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

void Turret::SmartDashUpdate()
{
//  SetRotation = frc::SmartDashboard::GetNumber("Rotation Turret", 0); //issue is with getnumber
//  SetAngle = frc::SmartDashboard::GetNumber("Angle Turret", 0);
//  SetRotation = frc::SmartDashboard::PutNumber("Rotation Turret", 0.1);
//  SetAngle = frc::SmartDashboard::PutNumber("Angle Turret", 0.1);
SetRotation = -0.1;
}

// void Turret::HomingAngle()
// {
//   if (AngleSwitch.Get() == true)
//     {
//      while (AngleSwitch.Get() == true)
//         {
//          Angle_motor.Set(0.1); //Go opposite direction of the limit switch
//         }
//      Angle_motor.Set(0); //stop it after rot limit switch is false
//     }
//  else
//     {
//      Angle_motor.Set(-0.1);
//      if(AngleSwitch.Get() == true)
//         {
//          Angle_motor.Set(0); //stop motor after limit switch is true
//          Angle_encoder.SetPosition(0); //set encoder to pos 0
//         }
//     }
// }

void Turret::HomingRotation()
{
 if (RotSwitch.Get() == true)
    {
     while (RotSwitch.Get() == true)
        {
         Rotation_motor.Set(-0.1); //Go opposite direction of the limit switch
        }
     Rotation_motor.Set(0); //stop it after rot limit switch is false maybe unesseccary
    }
 else
    {
     while (RotSwitch.Get() == false)
     {
        Rotation_motor.Set(0.1);
     }
     if (RotSwitch.Get() == true)
     {
        Rotation_motor.Set(0); //stop motor after limit switch is true
        Rotation_encoder.SetPosition(0); //set encoder to pos 0
     }
    }
}

void Turret::HomingAngle()
{
 if (AngleSwitch.Get() == true)
    {
     while (AngleSwitch.Get() == true)
        {
         Angle_motor.Set(-0.1); //Go opposite direction of the limit switch
        }
     Angle_motor.Set(0); //stop it after rot limit switch is false maybe unesseccary
    }
 else
    {
     while (AngleSwitch.Get() == false)
     {
        Angle_motor.Set(0.1);
     }
     if (AngleSwitch.Get() == true)
     {
        Angle_motor.Set(0); //stop motor after limit switch is true
        Angle_encoder.SetPosition(0); //set encoder to pos 0
     }
    }
}