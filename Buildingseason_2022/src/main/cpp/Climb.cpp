#include "Climb.h"
#include <iostream>

Climb::Climb(frc::PS4Controller *controller)
{
    //Get reference
    Joystick = controller;

    //Set motor settings
    LClimbMotor.ConfigFactoryDefault(); //Reset motors
    RClimbMotor.ConfigFactoryDefault();

    //The right motor wil mirror the left motor
    RClimbMotor.Follow(LClimbMotor);

    //Reset encoder
    LClimbMotor.SetSelectedSensorPosition(0);
    LClimbMotor.Config_kP(0, 0.45, 10);
    LClimbMotor.Config_kI(0, 0.000001, 10);
    LClimbMotor.Config_kD(0, 0.2, 10);
    
    //Set motors in starting position
    Rachets(false); //Make sure climber not opens
}

void Climb::Teleop(){

    SetPositionController(Joystick->GetRawAxis(1)*-1*controllerspeed);  //Get the climbing speed

    if(Joystick->GetRawButton(1)) //Close rachets
    Rachets(true);
    
    if(Joystick->GetRawButton(2)) //Open rachets
    Rachets(false);

    if(Joystick->GetRawButton(3)) //Prepare for climbing
    SetClimbPosition();

    if(Joystick->GetRawButton(4)) //Start climbing procedure
    ClimbNow();

}

bool Climb::SetClimbPosition(){
    //Open rachets
    Rachets(true);
    SetPosition(ClimbHeight);
    //Calculate difference between actual hight and setpiont
    float difference = ClimbHeight-LClimbMotor.GetSelectedSensorPosition();
    //Determen if the selected and is reached
    bool EndReached = (difference<ClimbError)&(difference > -ClimbError);
    return EndReached;
}

bool Climb::ClimbNow(){
    //Release rachets
    Rachets(false);
    SetPosition(ClimbHeight);
    //Calculate difference between actual hight and setpiont
    float difference = ClimbHeight-LClimbMotor.GetSelectedSensorPosition();
    //Determen if the selected and is reached
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
