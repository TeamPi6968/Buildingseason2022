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

    StorageShooter.SetInverted(true); 

    StorageShooter.SetInverted(false);

    // Set followers
    BottomR.Follow(BottomL);
    TopSpinner.Follow(BottomL);

    // create Timer
    // timer = new frc::Timer();
}
void Shooter::shot_calculation(){
 X2 = sqrt((pow(Depth_camera,2))-(pow(Y3,2)));//x value of the depth
 X3 = X2+0.61;//x value of depth + radius of hub
 //formula ax^2+b*x+c is used
 a = ((Y2 - c)*X3-(Y3-c)*X2)/(pow(X2,2)*X3-pow(X3,2)*X2);//calculate a
 b = (Y2 - a*pow(X2,2)-c)/X2;//calculate b
 angle_shot = tan(b/1);//slope is always value b so angle can be calculated
 velocity = sqrt((9.81*pow(X2,2))/((X2*tan(angle_shot)-Y3 + Y1)*(2*pow(cos(angle_shot),2))));//velocity in m/s
 motorspeed_rpm = (60*velocity)/(2*M_PI*radius);
 motorspeed = motorspeed_rpm/max_motorspeed_rpm;
}


void Shooter::TeleOp()
{
    if (Joystick->GetCrossButton() == true)
    {
        std::cout<<"Shoot button pressed"<<"\n";
        // BottomL.Set(ControlMode::PercentOutput, 0.3);
        // StorageShooter.Set(ControlMode::PercentOutput, 1);

        BottomL.Set(ControlMode::PercentOutput, ShootPercentage);
        StorageShooter.Set(ControlMode::PercentOutput, ShootPercentage);

        // timer->Start();
    }

    else
    {
        BottomL.Set(ControlMode::PercentOutput, 0);
        StorageShooter.Set(ControlMode::PercentOutput, 0);
        // timer->Reset();
    }

    // if (timer->Get() > ShooterDelay)
    // {
    //     std::cout << "Shooter delay started" << '\n';
    //     StorageShooter.Set(ControlMode::PercentOutput, ShootPercentage);
    // }

   
    //removed turret rotation
    // //Turret Rotation Limit
    // float turretROtationPosition = TurretRotation.GetEncoder().GetPosition();

    // if (turretROtationPosition < RightShooterLimit)
    // {
    //     if (turretROtationPosition > LeftShooterLimit)
    //     {
    //         // The shooter is in between the the limits
    //         TurretRotation.Set(Joystick->GetLeftX());
    //     }
    //     else
    //     {
    //         // over the left limit
    //         if (Joystick->GetLeftX() > 0)
    //             // move only back
    //             TurretRotation.Set(Joystick->GetLeftX());
    //     }
    // }
    // else
    // {
    //     // over right limit
    //     std::cout << "over right limit" << '\n';
    //     if (Joystick->GetLeftX() < 0)
    //         // move only back
    //         TurretRotation.Set(Joystick->GetLeftX());
    // }



    // //Turret Angle limits
    // float turretAnglePosition = TurretAngle.GetEncoder().GetPosition();

    // if (turretAnglePosition < BottomAngelLimit)
    // {
    //     if (turretAnglePosition > TopAngelLimit)
    //     {
    //         // The shooter is in between the the limits
    //         TurretAngle.Set(Joystick->GetRightY());
    //     }
    //     else
    //     {
    //         // over the left limit
    //         if (Joystick->GetRightY() > 0)
    //             // move only back
    //             TurretAngle.Set(Joystick->GetRightY());
    //     }
    // }
    // else
    // {
    //     // over right limit
    //     std::cout << "over right limit" << '\n';
    //     if (Joystick->GetRightY() < 0)
    //         // move only back
    //         TurretAngle.Set(Joystick->GetRightY());
    // }

    
    // TurretRotation.Set(Joystick->GetLeftX());
    // frc::SmartDashboard::PutNumber("joystick rotation",Joystick->GetLeftX());
    // TurretAngle.Set(Joystick->GetRightY());
    
}
