#include "Climb.h"
#include <iostream>

Climb::Climb(frc::PS4Controller *controller)
{
    // Get reference
    Joystick = controller;

    // Set motor settings
    LClimbMotor.ConfigFactoryDefault(); // Reset motors
    RClimbMotor.ConfigFactoryDefault();

    // The right motor wil mirror the left motor
    // RClimbMotor.Follow(LClimbMotor);

    // Reset encoder
    LClimbMotor.SetSelectedSensorPosition(0);
    LClimbMotor.Config_kP(0, 0.45, 10);
    LClimbMotor.Config_kI(0, 0.000001, 10);
    LClimbMotor.Config_kD(0, 0.2, 10);

    // Set motors in starting position
    Rachets(false); // Make sure climber not opens
}

void Climb::Teleop()
{

    // SetPositionController(Joystick->GetRawAxis(1)*controllerspeed);  //Get the climbing speed

    if (Joystick->GetPOV(0) == 0)
    {
        MovePosition(-controllerspeed); // Set percentage output controller
        Rachets(false);
    }
    else if (Joystick->GetPOV(0) == 180)
    {
        MovePosition(-controllerspeed); // Set percentage output controller
        Rachets(false);
    }
    else
    {
        MovePosition(0); // Set percentage output controller
        Rachets(true);
    }

    // if (Joystick->GetSquareButton()) // Close rachets
    //     Rachets(true);

    // if (Joystick->GetCrossButton()) // Open rachets
    //     Rachets(false);

    // if (Joystick->GetCircleButton()) // Prepare for climbing
    //     SetClimbPosition();

    // if (Joystick->GetTriangleButton()) // Start climbing procedure
    //     ClimbNow();
}

void Climb::ManualTeleop()
{
    if (Joystick->GetRightX() == 1)
    {
        if (Joystick->GetPOV(0) == 0)
        {
            LClimbMotor.Set(ControlMode::PercentOutput, -controllerspeed);
        }
        else if (Joystick->GetPOV(0) == 90 * 2)
        {
            LClimbMotor.Set(ControlMode::PercentOutput, controllerspeed);
        }
    }
    else{
        LClimbMotor.Set(ControlMode::PercentOutput, 0);
    }
    if (Joystick->GetL2Axis() == 1)
    {
        if (Joystick->GetPOV(0) == 0)
        {
            RClimbMotor.Set(ControlMode::PercentOutput, -controllerspeed);
        }
        else if (Joystick->GetPOV(0) == 90 * 2)
        {
            RClimbMotor.Set(ControlMode::PercentOutput, controllerspeed);
        }
    }
    else{
        RClimbMotor.Set(ControlMode::PercentOutput, 0);
    }
    

    // if (Joystick->GetPOV(0) == 0)
    // {
    //     MovePosition(-controllerspeed); // Set percentage output controller
    // }
    // else if (Joystick->GetPOV(0) == 90 * 2)
    // {
    //     MovePosition(-controllerspeed); // Set percentage output controller
    // }
    if (Joystick->GetPOV(0) == 90)
    {
        Rachets(true);
    }
    else if (Joystick->GetPOV(0) == 90 * 3)
    {
        Rachets(false);
    }
}

bool Climb::SetClimbPosition()
{
    // Open rachets
    Rachets(true);
    SetPosition(ClimbHeight);
    // Calculate difference between actual hight and setpiont
    float difference = ClimbHeight - LClimbMotor.GetSelectedSensorPosition();
    // Determen if the selected and is reached
    bool EndReached = (difference < ClimbError) & (difference > -ClimbError);
    return EndReached;
}

bool Climb::ClimbNow()
{
    // Release rachets
    Rachets(false);
    SetPosition(ClimbHeight);
    // Calculate difference between actual hight and setpiont
    float difference = ClimbHeight - LClimbMotor.GetSelectedSensorPosition();
    // Determen if the selected and is reached
    bool EndReached = (difference < ClimbError) & (difference > -ClimbError);
    return EndReached;
}

void Climb::SetPositionController(float axis)
{
    float NewPosition = LClimbMotor.GetSelectedSensorPosition() + axis;
    SetPosition(NewPosition);
}

void Climb::SetPosition(float position)
{
    frc::SmartDashboard::PutNumber("ClimbHeight", position);
    LClimbMotor.Set(ControlMode::Position, position);
}

void Climb::MovePosition(float controllerAxis)
{
    LClimbMotor.Set(ControlMode::PercentOutput, controllerAxis);
}

void Climb::Rachets(bool open)
{
    if (open)
    {
        LClimbServo.SetAngle(LServoOpenAngle);
        RClimbServo.SetAngle(RServoOpenAngle);
    }
    else
    {
        LClimbServo.SetAngle(LServoClosedAngle);
        RClimbServo.SetAngle(RServoClosedAngle);
    }
    frc::SmartDashboard::PutBoolean("Rachet open", open);
}
