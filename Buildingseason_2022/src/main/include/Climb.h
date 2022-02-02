#pragma once

#include <frc/PS4Controller.h>
#include <frc/servo.h>
#include <ctre/phoenix.h>
#include <frc/smartdashboard/SmartDashboard.h> 

class Climb
{
private:
    frc::PS4Controller *Joystick; //Link controller
    const float controllerspeed = 100; 

    //Climb motors
    TalonFX LClimbMotor = {12}; //Master motor, Set Can ID, left
    TalonFX RClimbMotor = {7}; //Slave motor,  Set Can ID, right

    //This methode is not working now 2-2-2022
    //Servo rachet modes
    frc::Servo LClimbServo{1}; //Set PWM Port
    frc::Servo RClimbServo{2}; //Set PWM Port

    //Servo angles
    const float LServoOpenAngle = 0;
    const float LServoClosedAngle = 90;

    const float RServoOpenAngle = 90;
    const float RServoClosedAngle = 0;

    //Different heights
    const float ClimbHeight = 1000;
    const float ClimbError = 10;

    //Functions
    void Rachets(bool open);
    void SetPosition(float position);
    void SetPositionController(float axis);

public:

    Climb(frc::PS4Controller *controller); //Create object

    //TeleOp control
    void Teleop();

    //First set climb position (returns if it reached it)
    bool SetClimbPosition();

    //Climbs, returns true if it climbed
    bool ClimbNow();
};
