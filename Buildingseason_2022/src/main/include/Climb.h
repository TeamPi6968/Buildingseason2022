#pragma once

#include <frc/PS4Controller.h>
#include <frc/servo.h>
#include <ctre/phoenix.h>
#include <frc/smartdashboard/SmartDashboard.h> 

class Climb
{
private:
    frc::PS4Controller *Joystick; //Link controller
    const float controllerspeed = 0.3; 

    //Climb motors
    TalonFX LClimbMotor = {11}; //Master motor, Set Can ID, left
    TalonFX RClimbMotor = {12}; //Slave motor,  Set Can ID, right

    //This methode is not working now 2-2-2022
    //Servo rachet modes
    frc::Servo LClimbServo{0}; //Set PWM Port
    frc::Servo RClimbServo{1}; //Set PWM Port

    //Servo angles
    const float LServoOpenAngle = 90;
    const float LServoClosedAngle = 180;

    const float RServoOpenAngle = 90;
    const float RServoClosedAngle = 0;

    //Different heights
    const float ClimbHeight = 1000;
    const float ClimbError = 10;

    //Functions
    void Rachets(bool open);
    void SetPosition(float position);
    void SetPositionController(float axis);
    void MovePosition(float controllerAxis);

public:

    Climb(frc::PS4Controller *controller); //Create object

    //TeleOp control
    void Teleop();
    void ManualTeleop() //Have full control over rachets and motor percentage

    //First set climb position (returns if it reached it)
    bool SetClimbPosition();

    //Climbs, returns true if it climbed
    bool ClimbNow();
};
