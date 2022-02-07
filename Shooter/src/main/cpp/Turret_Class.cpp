#include <Turret_Class.h>

Turret::Turret(frc::PS4Controller *controller)
{ 
 turret_Joystick = controller;  
 //Turret_slave.Follow(Turret_master);
 //Turret_slave->Follow(Turret_master);
 Turret_master->SetInverted(TalonFXInvertType::Clockwise);
 Turret_slave->SetInverted(TalonFXInvertType::CounterClockwise);
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

void Turret::Calibration()
{
 //  Reset();
 if(Calibrated == false)
 {
  CalibrationAngle();
  CalibrationRotation();
  frc::SmartDashboard::PutNumber("AngleCalibrated", AngleCalibrated);
  frc::SmartDashboard::PutNumber("RotationCalibrated", RotationCalibrated);
  if (AngleCalibrated && RotationCalibrated)
  {
   Calibrated = true;
  }
 }  
}


void Turret::Rotation()
{   
   if (Calibrated)
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
       //R_pidController.SetReference(SetRotation, rev::ControlType::kPosition); 
       R_pidController.SetReference(SetRotation, rev::CANSparkMax::ControlType::kPosition);
      }
   }
}
 
void Turret::Angle()
{  
   if (Calibrated)
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
       //A_pidController.SetReference(SetAngle, rev::ControlType::kPosition); 
       A_pidController.SetReference(SetAngle, rev::CANSparkMax::ControlType::kPosition);
      }
   }
}

void Turret::Shoot()
{
    if(turret_Joystick->GetCircleButton() == true)
    {
     Turret_master->Set(ControlMode::PercentOutput, shootSpeed);
     Turret_slave->Set(ControlMode::PercentOutput, shootSpeed);
    }
}

void Turret::SmartDashUpdate()
{
 SetRotation = frc::SmartDashboard::GetNumber("Rotation Turret", 0); 
 SetAngle = frc::SmartDashboard::GetNumber("Angle Turret", 0);
}


// void Turret::CalibrationRotation()
// {
//  if (RotationCalibrated == false)
//  {
//    if (RotSwitch.Get() == true)
//    {
//      Rotation_motor.Set(0);
//      Rotation_encoder.SetPosition(0);
//      RotationCalibrated = true;
//    } 
//    else
//    {
//       Rotation_motor.Set(rotation_speed);
//    }
//  }  
// }

void Turret::CalibrationAngle()
{
 if (AngleCalibrated == false)
 {
   if (AngleSwitch.Get() == true)
   {
     A_pidController.SetReference(0, rev::CANSparkMax::ControlType::kVelocity);
     Angle_encoder.SetPosition(0);
     AngleCalibrated = true;
   } 
   else
   {
      A_pidController.SetReference(angle_speed, rev::CANSparkMax::ControlType::kVelocity);
   }
 }  
}


// void Turret::CalibrationAngle()
// {
//  if (AngleCalibrated == false)
//  {
//    switch (AngleSwitch.Get() == true) 
//    {
//    case true:
//       Angle_motor.Set(0);
//       Angle_encoder.SetPosition(0);
//       AngleCalibrated = true;
//      break;
//    case false:
//       Angle_motor.Set(angle_speed);
//      break;
//    }
//  }  
// }

void Turret::CalibrationRotation()
{
 if (RotationCalibrated == false)
 {
   switch (RotSwitch.Get() == true) 
   {
   case true:
     Rotation_motor.Set(0);
     Rotation_encoder.SetPosition(0);
     RotationCalibrated = true;
     break;
   case false:
     Rotation_motor.Set(rotation_speed);
     break;
   }
 }  
}

void Turret::Reset()
{
   Calibrated = false;
   RotationCalibrated = false;
   RotationLimitTouched = false;
   HomingRotationSet = false;
   AngleCalibrated = false;
   AngleLimitTouched = false;
   HomingAngleSet = false;
}

void Turret::RotationHome(){}

void Turret::AngleHome(){}