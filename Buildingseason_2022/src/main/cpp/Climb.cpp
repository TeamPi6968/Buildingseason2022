#include "Climb.h"
#include <iostream>

Climb::Climb(frc::PS4Controller *controller)
{

    // get reference camera
    Joystick = controller;

    // set motor settings
    LClimbMotor.ConfigFactoryDefault(); // reset motors
    RClimbMotor.ConfigFactoryDefault();

    //The right motor wil mirror the left motor
    RClimbMotor.Follow(LClimbMotor);

    // reset encoder
    LClimbMotor.SetSelectedSensorPosition(0);
    LClimbMotor.Config_kP(0, 0.45, 10);
    LClimbMotor.Config_kI(0, 0.000001, 10);
    LClimbMotor.Config_kD(0, 0.2, 10);
    

    // Set motors in starting position
    Rachets(false); // Make sure climber not opens
}

void Climb::Teleop(){

    SetPositionController(Joystick->GetRawAxis(1)*-1*controllerspeed);

    if(Joystick->GetRawButton(1))
    Rachets(true);
    
    if(Joystick->GetRawButton(2))
    Rachets(false);

    if(Joystick->GetRawButton(3))
    SetClimbPosition();

    if(Joystick->GetRawButton(4))
    ClimbNow();

}

bool Climb::SetClimbPosition(){
    //open rachets
    Rachets(true);

    SetPosition(ClimbHeight);

    float difference = ClimbHeight-LClimbMotor.GetSelectedSensorPosition();
    bool EndReached = (difference<ClimbError)&(difference > -ClimbError);
    return EndReached;
}

bool Climb::ClimbNow(){
    Rachets(false);
    SetPosition(ClimbHeight);
    float difference = ClimbHeight-LClimbMotor.GetSelectedSensorPosition();
    bool EndReached = (difference<ClimbError)&(difference > -ClimbError);
    return EndReached;
}


void Climb::SetPositionController(float axis){
    float NewPosition = LClimbMotor.GetSelectedSensorPosition() + axis;
    SetPosition(NewPosition);
}


void Climb::SetPosition(float position)
{
    frc::SmartDashboard::PutNumber("ClimbHeight",position);
    LClimbMotor.Set(ControlMode::Position, position);

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
