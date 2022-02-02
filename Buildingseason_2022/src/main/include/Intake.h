#pragma once

// #include "Robot.h"

#include <frc/GenericHID.h>

#include <frc/PS4Controller.h>

#include <frc/smartdashboard/SmartDashboard.h> 

class Intake{
private: 
frc::PS4Controller *intakeJoystick;
public:
    Intake(frc::PS4Controller *controller);
    void Toggle_cilinder_out_sensor();
    void Toggle_cilinder_in_sensor();
    void Toggle_cilinder_state();
    void Toggle_motor_high();
    void Toggle_motor_low();
    void Toggle_motor_stop();
    void Stop_when_full();
    void mainloop();
    
    bool toggle_sensor_in = 0;
    bool toggle_sensor_out = 0;
    bool toggle_cilinder = 0;
    bool toggle_motor_low = 0;
    bool toggle_motor_high = 0;
    bool toggle_motor_stop = 0;
    bool pnuematic_cilinder = 0;
    bool Set_motor_intake_low = 0;

    int waarde_toggle_sensor_in;
    int waarde_toggle_sensor_out;
    int waarde_toggle_cilinder;
    int waarde_toggle_motor_low;
    int waarde_toggle_motor_high;
    int waarde_toggle_motor_stop;
    int motor_intake;
};
