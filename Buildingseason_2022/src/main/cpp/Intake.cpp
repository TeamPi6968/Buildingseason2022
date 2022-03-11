#include "Intake.h"
#include <iostream>

Intake::Intake(frc::PS4Controller *controller)
{
  // Get reference
  Joystick = controller;

  // Set motor settings
  IntakeMotor.ConfigFactoryDefault(); // Reset motors
  StorageIntake.ConfigFactoryDefault();

  // Set direction
  IntakeMotor.SetInverted(false);
  StorageIntake.SetInverted(true);

  // Set followers
  StorageIntake.Follow(IntakeMotor);
}

void Intake::TeleOp()
{

  if (Joystick->GetSquareButton() == true)
  {

    IntakeMotor.Set(ControlMode::PercentOutput, IntakePercentage);
    // StorageIntake.Set(ControlMode::PercentOutput,-0.7);
  }
  else if (Joystick->GetCircleButton() == false)
  {
    IntakeMotor.Set(ControlMode::PercentOutput, 0);
  }

  if (Joystick->GetTriangleButton() == true)
  { // POV buttons are in angles
    std::cout<<"tRIANGLE BUTTON"<<"\n";
    BigSolenoids.Set(frc::DoubleSolenoid::Value::kForward);
    SmallSolenoids.Set(frc::DoubleSolenoid::Value::kForward);
    //BigSolenoids.Set(frc::DoubleSolenoid::
  }
  if (Joystick->GetR1Button() == true)
  {
    BigSolenoids.Set(frc::DoubleSolenoid::Value::kReverse);
    SmallSolenoids.Set(frc::DoubleSolenoid::Value::kReverse);
  }
}

void Intake::intakeInit(){
    BigSolenoids.Set(frc::DoubleSolenoid::Value::kReverse);
    SmallSolenoids.Set(frc::DoubleSolenoid::Value::kReverse);
}
