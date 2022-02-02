#pragma once

// #include "Robot.h"

#include <frc/GenericHID.h>

#include <frc/PS4Controller.h>

#include <frc/smartdashboard/SmartDashboard.h> 

#include <frc/Timer.h>

#include "ctre/Phoenix.h"

class Storage{
    private:
    frc::PS4Controller *storageJoystick;
    frc::Timer time{};
    VictorSPX motor_2to1 {6};
    public:
        Storage(frc::PS4Controller *controller);
        void mainloop();
        void Toggle_color_sensor_1();
        void Toggle_color_sensor_2();
        
        int storage_stage = 0;
        int available_balls = 0;
        int toggle_value_color_sensor_1 = 0;
        int toggle_value_color_sensor_2 = 0;
        int current_range_color_sensor_1 = 0;
        int current_range_color_sensor_2 = 0;
        int max_marging_red = 6;//value is chosen so not difined
        int min_marging_red = 1;//value is chosen so not difined
        int max_marging_blue = 35;//value is chosen so not difined
        int min_marging_blue = 30;//value is chosen so not difined
        
        units::second_t read_time;
        units::second_t period {2};

        double color_sensor_1; 
        double color_sensor_2;
        double motorspeed_outtake = 0.5;

        bool motor_storage_2_to_1 = 0;
        bool motor_storage_1_to_turret = 0;
        bool outtake_button = 0;
        bool toggle_color_sensor_1 = 0;
        bool toggle_color_sensor_2 = 0;
        bool color_sensor_1_state = 0;
        bool color_sensor_2_state = 0;
        bool current_time = 0;

};