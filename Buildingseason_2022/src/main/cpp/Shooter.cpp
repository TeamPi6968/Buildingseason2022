#include "Shooter.h"
#include <iostream>
 /*
Shooter::Shooter(frc::PS4Controller *controller)
{
  // Get reference
    Joystick = controller;

    // Set motor settings
    BottomR.ConfigFactoryDefault(); // Reset motors
    BottomL.ConfigFactoryDefault();
    TopSpinner.ConfigFactoryDefault();
    StorageShooter.ConfigFactoryDefault();

    // Set direction
    BottomR.SetInverted(true);
    BottomL.SetInverted(false);
    TopSpinner.SetInverted(true);

    StorageShooter.SetInverted(false);

    StorageShooter.SetInverted(true);


    //Set followers
    BottomR.Follow(BottomL);
    TopSpinner.Follow(BottomL); 

    //create Timer
    timer = new frc::Timer();
}

void Shooter::TeleOp()
{
    if (Joystick->GetCrossButton() == true)
    {
        BottomL.Set(ControlMode::PercentOutput, 0.3);
        StorageShooter.Set(ControlMode::PercentOutput, 1);

        BottomL.Set(ControlMode::PercentOutput, ShootPercentage);
         StorageShooter.Set(ControlMode::PercentOutput, ShootPercentage);

        timer->Start();
    }

    else
    {
        BottomL.Set(ControlMode::PercentOutput, 0);
        StorageShooter.Set(ControlMode::PercentOutput, 0);
        timer->Reset();
    }

    if(timer->Get() > ShooterDelay){
        //StorageShooter.Set(ControlMode::PercentOutput, ShootPercentage);
    }

    
    TurretRotation.Set(Joystick->GetLeftX());
    frc::SmartDashboard::PutNumber("joystick rotation",Joystick->GetLeftX());
    TurretAngle.Set(Joystick->GetRightY());
    
}*/