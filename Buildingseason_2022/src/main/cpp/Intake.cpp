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
<<<<<<< HEAD
    if(Joystick->GetCircleButton() == true){
=======
    if(Joystick->GetSquareButton())
>>>>>>> cdcf9c70f2935eca5e7cf1792775ddc867161492
    IntakeMotor.Set(ControlMode::PercentOutput, IntakePercentage);
    //StorageIntake.Set(ControlMode::PercentOutput,-0.7);
    }
    else if(Joystick->GetCircleButton() == false){
    IntakeMotor.Set(ControlMode::PercentOutput, 0);
    }

    if (Joystick->GetTriangleButton() == true) { //POV buttons are in angles
      BigSolenoids.Set(frc::DoubleSolenoid::kForward);
      SmallSolenoids.Set(frc::DoubleSolenoid::kForward);
    } 
    else if(Joystick->GetR1Button() == true) {
      BigSolenoids.Set(frc::DoubleSolenoid::kReverse);
      SmallSolenoids.Set(frc::DoubleSolenoid::kReverse);
    } 
}

