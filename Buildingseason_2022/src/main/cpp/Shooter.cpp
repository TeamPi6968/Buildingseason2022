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
    BottomR.SetInverted(true);
    BottomL.SetInverted(false);
    TopSpinner.SetInverted(true);

    StorageShooter.SetInverted(false);

    StorageShooter.SetInverted(true);

    // Set followers
    BottomR.Follow(BottomL);
    TopSpinner.Follow(BottomL);

    // create Timer
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

    if (timer->Get() > ShooterDelay)
    {
        std::cout << "Shooter delay started" << '\n';
        // StorageShooter.Set(ControlMode::PercentOutput, ShootPercentage);
    }

   
    //Turret Rotation Limit
    float turretROtationPosition = TurretRotation.GetEncoder().GetPosition();

    if (turretROtationPosition < RightShooterLimit)
    {
        if (turretROtationPosition > LeftShooterLimit)
        {
            // The shooter is in between the the limits
            TurretRotation.Set(Joystick->GetLeftX());
        }
        else
        {
            // over the left limit
            if (Joystick->GetLeftX() > 0)
                // move only back
                TurretRotation.Set(Joystick->GetLeftX());
        }
    }
    else
    {
        // over right limit
        std::cout << "over right limit" << '\n';
        if (Joystick->GetLeftX() < 0)
            // move only back
            TurretRotation.Set(Joystick->GetLeftX());
    }



    //Turret Angle limits
    float turretAnglePosition = TurretAngle.GetEncoder().GetPosition();

    if (turretAnglePosition < BottomAngelLimit)
    {
        if (turretAnglePosition > TopAngelLimit)
        {
            // The shooter is in between the the limits
            TurretAngle.Set(Joystick->GetRightY());
        }
        else
        {
            // over the left limit
            if (Joystick->GetRightY() > 0)
                // move only back
                TurretAngle.Set(Joystick->GetRightY());
        }
    }
    else
    {
        // over right limit
        std::cout << "over right limit" << '\n';
        if (Joystick->GetRightY() < 0)
            // move only back
            TurretAngle.Set(Joystick->GetRightY());
    }

    
    TurretRotation.Set(Joystick->GetLeftX());
    frc::SmartDashboard::PutNumber("joystick rotation",Joystick->GetLeftX());
    TurretAngle.Set(Joystick->GetRightY());
    
}
