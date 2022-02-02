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
    void Toggle_cilinder_out_sensor();//Temperarly function for testing without components
    void Toggle_cilinder_in_sensor();//Temperarly function for testing without components
    void Toggle_cilinder_state();//Cilinder in and out
    void Toggle_motor_high();//Temperarly function for testing without components
    void Toggle_motor_low();//Temperarly function for testing without components
    void Toggle_motor_stop();//Temperarly function for testing without components
    void Stop_when_full();//When storage is full the motor can't turn and pnuematic arm is out
    void mainloop();//Main proces from the intake
    
    bool toggle_sensor_in = 0;//Temperarly value 
    bool toggle_sensor_out = 0;//Temperarly value 
    bool toggle_cilinder = 0;//Temperarly value 
    bool toggle_motor_low = 0;//Temperarly value 
    bool toggle_motor_high = 0;//Temperarly value 
    bool toggle_motor_stop = 0;//Temperarly value 
    bool pnuematic_cilinder = 0;//Temperarly value to set cilinder
    bool Set_motor_intake_low = 0;//Temperarly value to set montor intake
    bool Stop_motor_intake = 0;//Temperarly value to stop montor intake
    

    int waarde_toggle_sensor_in;//Temperarly value 
    int waarde_toggle_sensor_out;//Temperarly value 
    int waarde_toggle_cilinder;//Temperarly value 
    int waarde_toggle_motor_low;//Temperarly value 
    int waarde_toggle_motor_high;//Temperarly value 
    int waarde_toggle_motor_stop;//Temperarly value 
    int motor_intake;//Set motor for intake
};
