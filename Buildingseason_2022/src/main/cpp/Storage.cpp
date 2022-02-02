#pragma once
#include "Storage.h"



Storage::Storage(frc::PS4Controller *controller){
  storageJoystick = controller; 
}

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

void Storage::mainloop(){
  Toggle_color_sensor_1();//read color sensor 1
  Toggle_color_sensor_2();//read color sensor 2
  outtake_button = storageJoystick->GetCrossButton();

  frc::SmartDashboard::PutNumber("storage stage",storage_stage);
  frc::SmartDashboard::PutNumber("Outtake value",outtake_button);
  frc::SmartDashboard::PutNumber("motor 2 to 1",motor_storage_2_to_1);
  frc::SmartDashboard::PutNumber("motor to turret",motor_storage_1_to_turret);
  frc::SmartDashboard::PutNumber("amount balls",available_balls);
  frc::SmartDashboard::PutNumber("color sensor 1 state",color_sensor_1_state);
  frc::SmartDashboard::PutNumber("color sensor 2 state",color_sensor_2_state);
  frc::SmartDashboard::PutNumber("current 1",current_range_color_sensor_1);
  frc::SmartDashboard::PutNumber("current 2",current_range_color_sensor_2);

  switch (storage_stage){
  case 0://Storage stage = 0
  motor_2to1.Set(ControlMode::PercentOutput, 0);
    if(color_sensor_1_state == false and color_sensor_2_state == true){
      available_balls = 1;
      //printf("&d",available_balls);//Ball is available in storage
      storage_stage = 1;//Go to next stage
    }
    if(color_sensor_1_state == true and color_sensor_2_state == false){
      available_balls = 1;
      //printf("&d",available_balls);//Ball is available in storage
      storage_stage = 2;//Go to next stage
    }
    if(color_sensor_1_state == true and color_sensor_2_state == true){
      available_balls = 2;
      storage_stage = 2;//Go to next stage
    }
  break;

  case 1:
    motor_2to1.Set(ControlMode::PercentOutput, 0.1);
    color_sensor_1_state = false;
    color_sensor_2_state = false;
    if(current_range_color_sensor_1 > min_marging_red and current_range_color_sensor_1 < max_marging_red){
      color_sensor_1_state = true;
      motor_storage_2_to_1 = false;
      storage_stage = 2;
    }
    if(current_range_color_sensor_1 > min_marging_blue and current_range_color_sensor_1 < max_marging_blue){
      color_sensor_1_state = true;
      motor_storage_2_to_1 = false;
      storage_stage = 2;
    }
  break;

  case 2:
  motor_2to1.Set(ControlMode::PercentOutput, 0);//motor to turret needs name change
    color_sensor_1_state = false;
    color_sensor_2_state = false;
    if(outtake_button == true){
      storage_stage = 3;
    }
  break;
  
  case 3:
  motor_2to1.Set(ControlMode::PercentOutput, 0.1);//motor to turret needs name change

  if(current_range_color_sensor_1 < min_marging_red or current_range_color_sensor_1 > max_marging_red){
    time.Reset();
    time.Start();
    
    //elapse_time = read_time + period;
    storage_stage = 4;
  }
  break;

  case 4:
  read_time = time.Get();
  motor_storage_1_to_turret = true;
  if(time.Get() > period){
    available_balls--;
    motor_storage_1_to_turret = false;
    storage_stage = 0;
  }
  break;
  
  default:
    break;
  }
}