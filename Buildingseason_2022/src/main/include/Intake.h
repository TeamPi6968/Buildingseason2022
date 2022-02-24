#pragma once

#include <frc/PS4Controller.h>
#include <frc/servo.h>
#include <ctre/phoenix.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Solenoid.h>
#include <frc/DoubleSolenoid.h>

class Intake
{
private:
    frc::PS4Controller *Joystick; // Link controller

    VictorSPX IntakeMotor = {9};
    VictorSPX StorageIntake = {7};

    frc::DoubleSolenoid BigSolenoids{frc::PneumaticsModuleType::REVPH, 4, 0};
    frc::DoubleSolenoid SmallSolenoids{frc::PneumaticsModuleType::REVPH, 6, 2};
    static constexpr int kSolenoidButton = 1;
    static constexpr int kDoubleSolenoidForward = 2;
    static constexpr int kDoubleSolenoidReverse = 3;

public:
    Intake(frc::PS4Controller *controller); // Create object

    // TeleOp control
    void TeleOp();

    float IntakePercentage = 20;
};
