#pragma once
#include "Storage.h"

Storage::Storage(frc::PS4Controller *controller){
  storageJoystick = controller; 
}

//Temperary to replace the real sensors
void Storage::Toggle_color_sensor_1(){
 color_sensor_1 = storageJoystick->GetSquareButton();
 frc::SmartDashboard::PutNumber("color sensor 1",color_sensor_1);
 frc::SmartDashboard::PutNumber("value sensor 1", toggle_color_sensor_1);
  current_range_color_sensor_1 = 4*toggle_color_sensor_1;
 if(color_sensor_1 == true){
    if(toggle_value_color_sensor_1 == 0){
     toggle_color_sensor_1 = !toggle_color_sensor_1;
     toggle_value_color_sensor_1++;
    }
  }
 if(color_sensor_1 == false){
   toggle_value_color_sensor_1 = 0;
 }
 if (current_range_color_sensor_1 > min_marging_red and current_range_color_sensor_1 < max_marging_red){
    color_sensor_1_state = true;
  }
  if (current_range_color_sensor_1 > min_marging_blue and current_range_color_sensor_1 < max_marging_blue){
    color_sensor_1_state = true;
  }
}
//Temperary to replace the real sensors
void Storage::Toggle_color_sensor_2(){

 color_sensor_2 = storageJoystick->GetCircleButton();
 frc::SmartDashboard::PutNumber("color sensor 2",color_sensor_2);
 frc::SmartDashboard::PutNumber("value sensor 2", toggle_color_sensor_2);

 current_range_color_sensor_2 = 32* toggle_color_sensor_2;
 if(color_sensor_2 == true){
    if(toggle_value_color_sensor_2 == 0){
     toggle_color_sensor_2 = !toggle_color_sensor_2;
     toggle_value_color_sensor_2++;
    }
  }
  if(color_sensor_2 == false){
   toggle_value_color_sensor_2 = 0;
  }
  if (current_range_color_sensor_2 > min_marging_red and current_range_color_sensor_2 < max_marging_red){
    color_sensor_2_state = true;
  }
  if (current_range_color_sensor_2 > min_marging_blue and current_range_color_sensor_2 < max_marging_blue){
    color_sensor_2_state = true;
  }

}

void Storage::Turn_when_intake_true(){//When motor intake = true the storage motor between the 2 balls are true
  motor_2to1.Set(ControlMode::PercentOutput, 0.1);
}

void Storage::mainloop(){//The whole storage proces
  Toggle_color_sensor_1();//read color sensor 1
  Toggle_color_sensor_2();//read color sensor 2
  outtake_button = storageJoystick->GetCrossButton();//when Shooter will be activated (temperarly because will be used in Turret.cpp)

  frc::SmartDashboard::PutNumber("storage stage",storage_stage);//switch case stage
  frc::SmartDashboard::PutNumber("Outtake value",outtake_button);//when shootewr is activated
  frc::SmartDashboard::PutNumber("motor 2 to 1",motor_storage_2_to_1);//Motor between ball 2 and 1
  frc::SmartDashboard::PutNumber("motor to turret",motor_storage_1_to_turret);//motor to the shooter
  frc::SmartDashboard::PutNumber("amount balls",available_balls);//the amount of balls in storage
  frc::SmartDashboard::PutNumber("color sensor 1 state",color_sensor_1_state);//Color sensor 1 to detect color and detection ball 1
  frc::SmartDashboard::PutNumber("color sensor 2 state",color_sensor_2_state);//Color sensor 2 to detect color and detection ball 2
  frc::SmartDashboard::PutNumber("current 1",current_range_color_sensor_1);//The RGB values that color sensor 1 reads
  frc::SmartDashboard::PutNumber("current 2",current_range_color_sensor_2);//The RGB values that color sensor 2 reads

  switch (storage_stage){
  case 0:
  motor_2to1.Set(ControlMode::PercentOutput, 0);//stop motor
    if(color_sensor_1_state == false and color_sensor_2_state == true){//if only ball 2 is detected
      available_balls = 1; 
      storage_stage = 1;//go to case 1
    }
    if(color_sensor_1_state == true and color_sensor_2_state == false){//if only baal 1 is detected
      available_balls = 1;
      storage_stage = 2;//go to case 2
    }
    if(color_sensor_1_state == true and color_sensor_2_state == true){//if both are detected
      available_balls = 2;
      storage_stage = 2;//go to case 2
    }
  break;

  case 1:
    motor_2to1.Set(ControlMode::PercentOutput, 0.1);//motor is turning
    color_sensor_1_state = false;
    color_sensor_2_state = false;
    //when red ball is in range on color sensor 1
    if(current_range_color_sensor_1 > min_marging_red and current_range_color_sensor_1 < max_marging_red){
      color_sensor_1_state = true;
      motor_storage_2_to_1 = false;
      storage_stage = 2;//go to case 2
    }
    //when blue ball is in range on color sensor 1
    if(current_range_color_sensor_1 > min_marging_blue and current_range_color_sensor_1 < max_marging_blue){
      color_sensor_1_state = true;
      motor_storage_2_to_1 = false;
      storage_stage = 2;//go to case 2
    }
  break;

  case 2:
  motor_2to1.Set(ControlMode::PercentOutput, 0);//motor stopped
  motor_turret.Set(ControlMode::PercentOutput, 0);//motor stopped
    color_sensor_1_state = false;
    color_sensor_2_state = false;
    if(outtake_button == true){//if shooter is activated
      storage_stage = 3;//go to case 3
    }
  break;
  
  case 3:
  motor_turret.Set(ControlMode::PercentOutput, 0.1);//motor is turning
  //if color sensor 1 doesnt detect ball anymore
  if(current_range_color_sensor_1 < min_marging_red or current_range_color_sensor_1 > max_marging_red){
    time.Reset();
    time.Start();
    storage_stage = 4;//go to case 4
  }
  break;

  case 4:
  read_time = time.Get();//reads the time
  motor_turret.Set(ControlMode::PercentOutput, 0.1);//motor is turning
  if(time.Get() > period){//if time is reached
    available_balls--;//Available balls is counting down
    motor_turret.Set(ControlMode::PercentOutput, 0.1);//motor stopped
    storage_stage = 0;//go to case 0
  }
  break;
  
  default:
    break;
  }
}