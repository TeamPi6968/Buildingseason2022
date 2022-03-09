#pragma once

#include <frc/PS4Controller.h>
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
    TalonFX TopSpinner = {15};

    rev::CANSparkMax TurretRotation{6,rev::CANSparkMax::MotorType::kBrushless};
    rev::CANSparkMax TurretAngle{5,rev::CANSparkMax::MotorType::kBrushless};
    float rotationSpeed = 0.3; //Rotation speed -1 to 1

    //storage motors
    VictorSPX StorageShooter = {7};

    //Timer for the shooter delay
    frc::Timer* timer;
    units::time::second_t ShooterDelay = 5_s; //seconds
    

public:

    Shooter(frc::PS4Controller *controller); //Create object

    //TeleOp control
    void TeleOp();

    float ShootPercentage = 20;
};
