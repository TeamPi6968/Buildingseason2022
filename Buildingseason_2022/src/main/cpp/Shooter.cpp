#include "Shooter.h"
#include <iostream>

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
    BottomR.SetInverted(false);
    BottomL.SetInverted(true);
    TopSpinner.SetInverted(false);
    StorageShooter.SetInverted(false);

    //Set followers
    BottomR.Follow(BottomL);
    TopSpinner.Follow(BottomL); 

    //create Timer
    timer = new frc::Timer();
}

void Shooter::TeleOp()
{
    if (Joystick->GetCrossButton())
    {
        BottomL.Set(ControlMode::PercentOutput, ShootPercentage);
        timer->Start();
    }

    else
    {
        BottomL.Set(ControlMode::PercentOutput, 0);
        StorageShooter.Set(ControlMode::PercentOutput, 0);
        timer->Reset();
    }

    if(timer->Get() > ShooterDelay){
        StorageShooter.Set(ControlMode::PercentOutput, ShootPercentage);
    }

    if(Joystick->GetR1Button())
    TurretRotation.Set(rotationSpeed);
    else if(Joystick->GetL1Button())
    TurretRotation.Set(-rotationSpeed);
    else
    TurretRotation.Set(0);
}