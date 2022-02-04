#include <Turret_Class.h>
#include <iostream>

Turret::Turret(frc::PS4Controller *controller)
{ 
 turret_Joystick = controller;  
 Turret_slave.Follow(Turret_master);
 Turret_master.SetInverted(TalonFXInvertType::Clockwise);
 Turret_slave.SetInverted(TalonFXInvertType::CounterClockwise);
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

// void Turret::Rotation()
// {
//  if (RotSwitch.Get() == true) {
//         Rotation_motor.Set(0);
//     }
//     else {
//         Rotation_motor.Set(SetRotation);
//     }
// }

// void Turret::Angle()
// {  
//  if (AngleSwitch.Get() == true) {
//         Angle_motor.Set(0);
//     }
//     else {
//         Angle_motor.Set(SetAngle);
//     }
// }

void Turret::Rotation()
{  
 if (RotSwitch.Get() == true)
    {
      Rotation_motor.Set(0);
    }
    else if(SetRotation > maxRotationEncoder)
    {
      Rotation_motor.Set(0);
    }
    else if(SetRotation < minRotationEncoder)
    {
      Rotation_motor.Set(0);
    }
    else 
    {   
    R_pidController.SetReference(SetRotation, rev::ControlType::kPosition); 
    }
}
 
void Turret::Angle()
{  
 if (AngleSwitch.Get() == true)
    {
      Angle_motor.Set(0);
    }
    else if(SetAngle > maxAngleEncoder)
    {
      Angle_motor.Set(0);
    }
    else if(SetAngle < minAngleEncoder)
    {
      Angle_motor.Set(0);
    }
    else 
    {   
    A_pidController.SetReference(SetAngle, rev::ControlType::kPosition); 
    }
}

void Turret::Shoot()
{
    if(turret_Joystick->GetCircleButton() == true)
    {
     Turret_master.Set(ControlMode::PercentOutput, shootSpeed);
    }
}

void Turret::SmartDashUpdate()
{
 SetRotation = frc::SmartDashboard::GetNumber("Rotation Turret", 0); 
 SetAngle = frc::SmartDashboard::GetNumber("Angle Turret", 0);
}

// void Turret::HomingRotation()
// {
//  if (RotSwitch.Get() == true)
//     {
//      while (RotSwitch.Get() == true)
//         {
//          Rotation_motor.Set(-0.1); //Go opposite direction of the limit switch
//         }
//      Rotation_motor.Set(0); //stop it after rot limit switch is false maybe unesseccary
//     }
//  else
//     {
//      while (RotSwitch.Get() == false)
//      {
//         Rotation_motor.Set(0.1);
//      }
//      if (RotSwitch.Get() == true)
//      {
//         Rotation_motor.Set(0); //stop motor after limit switch is true
//         Rotation_encoder.SetPosition(0); //set encoder to pos 0
//      }
//     }
// }

// void Turret::HomingAngle()
// {
//  if (AngleSwitch.Get() == true)
//     {
//      while (AngleSwitch.Get() == true)
//         {
//          Angle_motor.Set(-0.1); //Go opposite direction of the limit switch
//         }
//      Angle_motor.Set(0); //stop it after rot limit switch is false maybe unesseccary
//     }
//  else
//     {
//      while (AngleSwitch.Get() == false)
//      {
//         Angle_motor.Set(0.1);
//      }
//      if (AngleSwitch.Get() == true)
//      {
//         Angle_motor.Set(0); //stop motor after limit switch is true
//         Angle_encoder.SetPosition(0); //set encoder to pos 0
//      }
//     }
// }