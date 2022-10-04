#pragma once        

#include <frc/PS4Controller.h>   //including all libraries needed
#include <frc/servo.h>  
#include <ctre/phoenix.h>
#include <frc/smartdashboard/SmartDashboard.h> 
#include <frc/Timer.h>
#include "rev/CANSparkMax.h"

class Shooter
{
private:
    frc::PS4Controller *Joystick; //Link controller

    TalonFX BottomL = {14}; //Master motor, Set Can ID, left
    TalonFX BottomR = {13}; //Slave motor,  Set Can ID, right
    TalonFX TopSpinner = {15};  //Small wheels on top of the shooter above main shooter motors, Set Can ID

    
    rev::CANSparkMax TurretRotation{6,rev::CANSparkMax::MotorType::kBrushless};  //Turret Rotation motor, Set Can ID, Motor type
    rev::CANSparkMax TurretAngle{5,rev::CANSparkMax::MotorType::kBrushless};  //Turret Angle motor, Set Can ID, Motor type
    //double rotationSpeed = 0.3; //Rotation speed -1 to 1

    //rev::CANSparkMax TurretRotation{9,rev::CANSparkMax::MotorType::kBrushless};
    //rev::CANSparkMax TurretAngle{8,rev::CANSparkMax::MotorType::kBrushless};
    //float rotationSpeed = 0.75; //Rotation speed -1 to 1

   // storage motors
    VictorSPX StorageShooter = {7};  //Storage Motor, Set Can ID

   // Timer for the shooter delay
    frc::Timer* timer;      //creating a timer
    frc::Timer AutoTimer{}; //Naming created timer AutoTimer{}

    units::time::second_t ShooterDelay = 2_s; //2 seconds delay variable
    units::time::second_t AutonomousDelay = 5_s; //5 seconds delay variable

    float RightShooterLimit = 200; // Right rotation shooter limit
    float LeftShooterLimit = -200; // Left rotation shooter limit

    float BottomAngelLimit = 0; //bottom angle limit
    float TopAngelLimit = 200; //top angle limit
    
    double X1 = 0;          //start shooting at zero
    double Y1 = 0.64;       //initial height ball
    double X2;              //x value of distance camera
    double Y2 = 3.25;       //height hub + radius hub in height
    double X3;              //measured distance + radius hub
    double Y3 = 2.64;       //Height of the hub
    double a;
    double b;
    double c = Y1;
    double angle_shot;      //angle of shot
    double velocity;        //speed of shooting in m/s
    double motorspeed_rpm;
    double max_motorspeed_rpm = 6380;
    double radius = 0.0254; //radius in meters (2inch wheel)
    double motorspeed;
    double Depth_camera;
    
public:
    Shooter(frc::PS4Controller *controller); //Create object

   // Creating necesarry functions in this class for Shooter.cpp
    void TeleOp();
    void AutoInit();
    void AutoLoop();
    void shot_calculation();
    float ShootPercentage = 0.7; // 0.4 for lower hub, maybe 0.65 for higher hub (higher hub hasn't been tested properly)
};
