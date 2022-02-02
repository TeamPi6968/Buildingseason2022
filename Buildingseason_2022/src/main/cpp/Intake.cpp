#pragma once

#include "Intake.h" 
//#include <iostream>
 
Intake::Intake(frc::PS4Controller *controller){
  intakeJoystick = controller;
}

void Intake::Toggle_cilinder_in_sensor(){
bool cilinder_in_sensor = intakeJoystick->GetCircleButton(); //read cilinder out sensor
frc::SmartDashboard::PutNumber("cilinder in sensor",toggle_sensor_in);
//printf("&d",toggle_sensor_in);
 if(cilinder_in_sensor == true){
    if(waarde_toggle_sensor_in == 0){
      toggle_sensor_in = !toggle_sensor_in;
      waarde_toggle_sensor_in++;
      frc::SmartDashboard::PutNumber("waarde sensor in",waarde_toggle_sensor_in);
      
    }
  }

  else if(cilinder_in_sensor == false){
    waarde_toggle_sensor_in = 0;
    frc::SmartDashboard::PutNumber("waarde sensor in",waarde_toggle_sensor_in);
  }
}

void Intake::Toggle_cilinder_out_sensor(){
  bool cilinder_out_sensor = intakeJoystick->GetSquareButton(); //read cilinder out sensor
  frc::SmartDashboard::PutNumber("cilinder out sensor",toggle_sensor_out);
  if(cilinder_out_sensor == true){
    if(waarde_toggle_sensor_out == 0){
      toggle_sensor_out = !toggle_sensor_out;
      waarde_toggle_sensor_out++;
    }
  }

  else if(cilinder_out_sensor == false){
    waarde_toggle_sensor_out = 0;
  }
}

void Intake::Toggle_cilinder_state(){
  bool Cilinder_state = intakeJoystick->GetTriangleButton();//Set cilinder out
  frc::SmartDashboard::PutNumber("cilinder state",toggle_cilinder);
  if(Cilinder_state == true){
    if(waarde_toggle_cilinder == 0){
      toggle_cilinder = !toggle_cilinder;
      waarde_toggle_cilinder++;
    }
  }

  else if(Cilinder_state == false){
    waarde_toggle_cilinder = 0;
  }
}

void Intake::Toggle_motor_low(){//Temperarly function
  Set_motor_intake_low = intakeJoystick->GetR1Button();//Set motor lower ground
  frc::SmartDashboard::PutNumber("Motor low",toggle_motor_low);
  if(Set_motor_intake_low == true){
    if(waarde_toggle_motor_low == 0){
      toggle_motor_low = !toggle_motor_low;
      waarde_toggle_motor_low++;
    }
  }

  else if(Set_motor_intake_low == false){
    waarde_toggle_motor_low = 0;
  }
}

void Intake::Toggle_motor_high(){//could be removed
  bool Set_motor_intake_high = intakeJoystick->GetL1Button(); //Set motor for higher ground
  frc::SmartDashboard::PutNumber("Motor high",toggle_motor_high);
  if(Set_motor_intake_high == true){
    if(waarde_toggle_motor_high == 0){
      toggle_motor_high = !toggle_motor_high;
      waarde_toggle_motor_high++;
    }
  }

  else if(Set_motor_intake_high == false){
    waarde_toggle_motor_high = 0;
  }
}

void Intake::Toggle_motor_stop(){//Temperarly function
  
  bool Stop_motor_intake = intakeJoystick->GetCrossButton();//stop the motor
  frc::SmartDashboard::PutNumber("stop motor",toggle_motor_stop);
   
  if(Stop_motor_intake == true){
    if(waarde_toggle_motor_stop == 0){
      toggle_motor_stop = !toggle_motor_stop;
      waarde_toggle_motor_stop++;
    }
  }

  else if(Stop_motor_intake == false){
    waarde_toggle_motor_stop = 0;
  }
}

void Intake::Stop_when_full(){
  motor_intake = false;
  pnuematic_cilinder = true;
}

void Intake::mainloop(){

  Toggle_cilinder_in_sensor();
  Toggle_cilinder_out_sensor();
  Toggle_cilinder_state();
  Toggle_motor_high();
  Toggle_motor_low();
  Toggle_motor_stop();

  frc::SmartDashboard::PutNumber("pnuematic cilinder",pnuematic_cilinder);
  frc::SmartDashboard::PutNumber("motor intake",motor_intake);
  if(toggle_cilinder == true){
    pnuematic_cilinder = true; //cilinder pressed out
    if(toggle_sensor_out == true){
      if(toggle_motor_low == true){ 
        motor_intake = 1; //set motor right
        if(toggle_motor_low == true){
          if(waarde_toggle_motor_low == 0){
            toggle_motor_low = !toggle_motor_low;
            waarde_toggle_motor_low++;
          }
        }
      }
      else if(toggle_motor_high == true){
        motor_intake = -1; //set motor left
        if(toggle_motor_high == true ){
          if(waarde_toggle_motor_high == 0){
            toggle_motor_high = !toggle_motor_high;
            waarde_toggle_motor_high++;
          }
        }
      }
      else if(toggle_motor_stop == true){
        motor_intake = 0; //stop motor
        if(toggle_motor_stop == true){
          if(waarde_toggle_motor_stop == 0){
            toggle_motor_stop = !toggle_motor_stop;
            waarde_toggle_motor_stop++;
    
          }
        }
      }
    }
  }
  if(toggle_cilinder == false){
    motor_intake = 0;
    toggle_motor_stop = 0;
    toggle_motor_low = 0;
    toggle_motor_high = 0;
    pnuematic_cilinder = false;//cilinder pressed in (needs to be done)
    if(toggle_sensor_in == true){
      printf("cilinder in");
    }
  }
}
