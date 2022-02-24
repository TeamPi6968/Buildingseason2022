#include "Intake.h"
#include <iostream>

Intake::Intake(frc::PS4Controller *controller)
{
    //Get reference
    Joystick = controller;
    
    //Set motor settings
    IntakeMotor.ConfigFactoryDefault(); //Reset motors
    StorageIntake.ConfigFactoryDefault();

    //Set direction
    IntakeMotor.SetInverted(false);
    StorageIntake.SetInverted(true);

    //Set followers
    StorageIntake.Follow(IntakeMotor);
}

void Intake::TeleOp(){
    if(Joystick->GetShareButton())
    IntakeMotor.Set(ControlMode::PercentOutput, IntakePercentage);
    else
    IntakeMotor.Set(ControlMode::PercentOutput, 0);

    if (Joystick->GetPOV(90*3)) { //POV buttons are in angles
      BigSolenoids.Set(frc::DoubleSolenoid::kForward);
      SmallSolenoids.Set(frc::DoubleSolenoid::kForward);
    } 
    if(Joystick->GetPOV(90)) {
      BigSolenoids.Set(frc::DoubleSolenoid::kReverse);
      SmallSolenoids.Set(frc::DoubleSolenoid::kReverse);
    } 
}

