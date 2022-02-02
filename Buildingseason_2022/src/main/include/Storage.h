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
    VictorSPX motor_2to1 {6};//Can ID not defined
    VictorSPX motor_turret {7};//Can ID not defined
    public:
        Storage(frc::PS4Controller *controller);
        void Turn_when_intake_true();//When intake motor is on the storage motor between balls will be on
        void Turret_activated();//when the turret is activated the storage motor between turret and storage is on
        void mainloop();//the whole proces of storage
        void Toggle_color_sensor_1();//temperary function
        void Toggle_color_sensor_2();//temperary function
        
        int storage_stage = 0;//For switch function
        int available_balls = 0;//amount of balls in storage
        int toggle_value_color_sensor_1 = 0;//temperarly
        int toggle_value_color_sensor_2 = 0;//temperarly
        int current_range_color_sensor_1 = 0;//Reading of color sensor 1
        int current_range_color_sensor_2 = 0;//Reading of color sensor 2
        int max_marging_red = 6;//value is chosen so not difined
        int min_marging_red = 1;//value is chosen so not difined
        int max_marging_blue = 35;//value is chosen so not difined
        int min_marging_blue = 30;//value is chosen so not difined
        
        units::second_t read_time;//read the current time
        units::second_t period {2};//Delay time

        double color_sensor_1;//Color sensor for ball 1
        double color_sensor_2;//Color sensor for ball 2
        double motorspeed_2_to_1 = 0.1;//Motorspeed motor between ball 2 and 1
        double motorspeed_outtake = 0.5;//Motorspeed from motor storage to turret

        bool motor_storage_2_to_1 = 0;//set the motor
        bool motor_storage_1_to_turret = 0;//set the motor
        bool outtake_button = 0;//Temperarly for testing (will be activated in turret)
        bool toggle_color_sensor_1 = 0;//Temperarly
        bool toggle_color_sensor_2 = 0;//Temperarly
        bool color_sensor_1_state = 0;//Detection converted in true or false
        bool color_sensor_2_state = 0;//Detection converted in true or false

};