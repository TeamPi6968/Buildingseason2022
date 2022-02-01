#pragma once

#include "Swerve.h"

Swerve::Swerve(frc::PS4Controller *controller){
  swerveJoystick = controller;
}

void Swerve::Initialize_swerve(){
  //give the wheels the rotaion of 90 degrees as thay are alliant right now

  frc::SmartDashboard::PutNumber("Cont X value", 0);
  frc::SmartDashboard::PutNumber("Cont Y value", 0);
  frc::SmartDashboard::PutNumber("Angle", angle);
  frc::SmartDashboard::PutNumber("X", x);
  frc::SmartDashboard::PutNumber("Kp", kp);
  frc::SmartDashboard::PutNumber("Ki", ki);
  frc::SmartDashboard::PutNumber("Kd", kd);

  motorFLR.SetSelectedSensorPosition(11264);
  motorFRR.SetSelectedSensorPosition(11264);        
  motorRRR.SetSelectedSensorPosition(11264);
  motorRLR.SetSelectedSensorPosition(11264);
}

void Swerve::Configure_PID(){
  kp = frc::SmartDashboard::GetNumber("Kp", 0);
  ki = frc::SmartDashboard::GetNumber("Ki", 0);
  kd = frc::SmartDashboard::GetNumber("Kd", 0);

  //PID values of Front Left Rotation
  motorFLR.Config_kP(0, kp);
  motorFLR.Config_kI(0, ki);
  motorFLR.Config_kD(0, kd);
  //PID values of Front Right Rotation
  motorFRR.Config_kP(0, kp);
  motorFRR.Config_kI(0, ki);
  motorFRR.Config_kD(0, kd);
  //PID values of Rear Right Rotation
  motorRRR.Config_kP(0, kp);
  motorRRR.Config_kI(0, ki);
  motorRRR.Config_kD(0, kd);
  //PID values of Rear Left Rotation
  motorRLR.Config_kP(0, kp);
  motorRLR.Config_kI(0, ki);
  motorRLR.Config_kD(0, kd);

  desiredPosition = frc::SmartDashboard::GetNumber("Talon Desired Position",0); 
  //position = motorFLD.GetSelectedSensorPosition(); //Read current position
  frc::SmartDashboard::PutNumber("PositionW1 Graph", positionFR);
  frc::SmartDashboard::PutNumber("PositionW1 Num", positionFR);
  frc::SmartDashboard::PutNumber("PositionW2 Graph", positionFL);
  frc::SmartDashboard::PutNumber("PositionW2 Num", positionFL);
  frc::SmartDashboard::PutNumber("PositionW3 Graph", positionBL);
  frc::SmartDashboard::PutNumber("PositionW3 Num", positionBL);
  frc::SmartDashboard::PutNumber("PositionW4 Graph", positionBR);
  frc::SmartDashboard::PutNumber("PositionW4 Num", positionBR);
}

void Swerve::calculate_vector_straffe(){
  xVal_straffe = swerveJoystick->GetLeftX();
  yVal_straffe = swerveJoystick->GetLeftY();

  vector_straffe = sqrt(pow(xVal_straffe, 2) + pow(yVal_straffe, 2));

  if(vector_straffe<=0.1){
    xVal_straffe = 0;
    yVal_straffe = 0;
  }

  frc::SmartDashboard::PutNumber("Cont X value", xVal_straffe);
  frc::SmartDashboard::PutNumber("Cont Y value", yVal_straffe);
}

void Swerve::calculate_vector_rotation(){
 vector_rotation = swerveJoystick->GetRightX();

 if(vector_rotation<=0.1 && vector_rotation >= -0.1){
  vector_rotation = 0;
}

}

void Swerve::calculate_total_vector(){
  Total_XW1 = (xVal_straffe+(vector_rotation/sqrt(2)))/2;
  Total_YW1 = (yVal_straffe+(vector_rotation/sqrt(2)))/2;
  Total_XW2 = (xVal_straffe+(vector_rotation/sqrt(2)))/2;
  Total_YW2 = (yVal_straffe-(vector_rotation/sqrt(2)))/2;
  Total_XW3 = (xVal_straffe-(vector_rotation/sqrt(2)))/2;
  Total_YW3 = (yVal_straffe-(vector_rotation/sqrt(2)))/2;
  Total_XW4 = (xVal_straffe-(vector_rotation/sqrt(2)))/2;
  Total_YW4 = (yVal_straffe+(vector_rotation/sqrt(2)))/2;

  Total_Vector_W1 = sqrt(pow(Total_XW1, 2) + pow(Total_YW1, 2));
  Total_Vector_W2 = sqrt(pow(Total_XW2, 2) + pow(Total_YW2, 2));
  Total_Vector_W3 = sqrt(pow(Total_XW3, 2) + pow(Total_YW3, 2));
  Total_Vector_W4 = sqrt(pow(Total_XW4, 2) + pow(Total_YW4, 2));
}

void Swerve::calculate_total_angle_w1(){
    if((Total_XW1 >= 0) && (Total_YW1 <= 0))   // first quarter, angle <= 90, rotaions <= 2.75, total nb <= 11264 (be careful directions on the code is different)
    {
    Total_angle_W1 = ((atan(-Total_YW1/Total_XW1))/M_PI_2) * 90;
    }
    else if((Total_XW1 < 0) && (Total_YW1 <= 0))   // second quarter, angle 180>= angle > 90 , rotaions <= 5.5, total nb <= 22528 
    {
    Total_angle_W1 = 180 - (((atan(Total_YW1/Total_XW1))*90)/M_PI_2);
    }
    else if(Total_XW1 < 0 && Total_YW1 > 0)   // Third quarter, angle 270 >= angle > 180 , rotaions <= 8.25, total nb <= 33792 
    {    
    Total_angle_W1 = 270 - (((atan(-Total_XW1/Total_YW1))*90)/M_PI_2);// this angle is from 270 line (backwards) negative x positve y
    }
    else if(Total_XW1 >= 0 && Total_YW1 >= 0)   // forth quarter, angle 360 >= angle > 270 , rotaions <= 11, total nb <= 45056 
    {
    Total_angle_W1 = 360 - (((atan(Total_YW1/Total_XW1))*90)/M_PI_2);      // this angle is from 0 line (backwards)
    }
}

void Swerve::calculate_total_angle_w2(){
    if((Total_XW2 >= 0) && (Total_YW2 <= 0))   // first quarter, angle <= 90, rotaions <= 2.75, total nb <= 11264 (be careful directions on the code is different)
    {
    Total_angle_W2 = ((atan(-Total_YW2/Total_XW2))/M_PI_2) * 90;
    }
    else if((Total_XW2 < 0) && (Total_YW2 <= 0))   // second quarter, angle 180>= angle > 90 , rotaions <= 5.5, total nb <= 22528 
    {
    Total_angle_W2 = 180 - (((atan(Total_YW2/Total_XW2))*90)/M_PI_2);
    }
    else if(Total_XW2 < 0 && Total_YW2 > 0)   // Third quarter, angle 270 >= angle > 180 , rotaions <= 8.25, total nb <= 33792 
    {    
    Total_angle_W2 = 270 - (((atan(-Total_XW2/Total_YW2))*90)/M_PI_2);// this angle is from 270 line (backwards) negative x positve y
    }
    else if(Total_XW2 >= 0 && Total_YW2 >= 0)   // forth quarter, angle 360 >= angle > 270 , rotaions <= 11, total nb <= 45056 
    {
    Total_angle_W2 = 360 - (((atan(Total_YW2/Total_XW2))*90)/M_PI_2);      // this angle is from 0 line (backwards)
    }
}

void Swerve::calculate_total_angle_w3(){
    if((Total_XW3 >= 0) && (Total_YW3 <= 0))   // first quarter, angle <= 90, rotaions <= 2.75, total nb <= 11264 (be careful directions on the code is different)
    {
    Total_angle_W3 = ((atan(-Total_YW3/Total_XW3))/M_PI_2) * 90;
    }
    else if((Total_XW3 < 0) && (Total_YW3 <= 0))   // second quarter, angle 180>= angle > 90 , rotaions <= 5.5, total nb <= 22528 
    {
    Total_angle_W3 = 180 - (((atan(Total_YW3/Total_XW3))*90)/M_PI_2);
    }
    else if(Total_XW3 < 0 && Total_YW3 > 0)   // Third quarter, angle 270 >= angle > 180 , rotaions <= 8.25, total nb <= 33792 
    {    
    Total_angle_W3 = 270 - (((atan(-Total_XW3/Total_YW3))*90)/M_PI_2);// this angle is from 270 line (backwards) negative x positve y
    }
    else if(Total_XW3 >= 0 && Total_YW3 >= 0)   // forth quarter, angle 360 >= angle > 270 , rotaions <= 11, total nb <= 45056 
    {
    Total_angle_W3 = 360 - (((atan(Total_YW3/Total_XW3))*90)/M_PI_2);      // this angle is from 0 line (backwards)
    }
}

void Swerve::calculate_total_angle_w4(){
    if((Total_XW4 >= 0) && (Total_YW4 <= 0))   // first quarter, angle <= 90, rotaions <= 2.75, total nb <= 11264 (be careful directions on the code is different)
    {
    Total_angle_W4 = ((atan(-Total_YW4/Total_XW4))/M_PI_2) * 90;
    }
    else if((Total_XW4 < 0) && (Total_YW4 <= 0))   // second quarter, angle 180>= angle > 90 , rotaions <= 5.5, total nb <= 22528 
    {
    Total_angle_W4 = 180 - (((atan(Total_YW4/Total_XW4))*90)/M_PI_2);
    }
    else if(Total_XW4 < 0 && Total_YW4 > 0)   // Third quarter, angle 270 >= angle > 180 , rotaions <= 8.25, total nb <= 33792 
    {    
    Total_angle_W4 = 270 - (((atan(-Total_XW4/Total_YW4))*90)/M_PI_2);// this angle is from 270 line (backwards) negative x positve y
    }
    else if(Total_XW4 >= 0 && Total_YW4 >= 0)   // forth quarter, angle 360 >= angle > 270 , rotaions <= 11, total nb <= 45056 
    {
    Total_angle_W4 = 360 - (((atan(Total_YW4/Total_XW4))*90)/M_PI_2);      // this angle is from 0 line (backwards)
    }
}

void Swerve::set_rotations_w1(){
    if(Total_angle_W1 >= 0 && Total_angle_W1 <= 90)
    {
    w1_wasIn1 = true;
    if(w1_wasIn4)
    {
        rotationCounter_w1++;
        w1_wasIn4 = false;
    }
    }
    else if(Total_angle_W1 >= 270 && Total_angle_W1 < 360)
    {
    w1_wasIn4 = true;
    if(w1_wasIn1)
    {
        rotationCounter_w1--;
        w1_wasIn1 = false;
    }
    }
    else
    {
    w1_wasIn4 = false;
    w1_wasIn1 = false;
    }
}

void Swerve::set_rotations_w2(){
    if(Total_angle_W2 >= 0 && Total_angle_W2 <= 90)
    {
    w2_wasIn1 = true;
    if(w2_wasIn4)
    {
        rotationCounter_w2++;
        w2_wasIn4 = false;
    }
    }
    else if(Total_angle_W2 >= 270 && Total_angle_W2 < 360)
    {
    w2_wasIn4 = true;
    if(w2_wasIn1)
    {
        rotationCounter_w2--;
        w2_wasIn1 = false;
    }
    }
    else
    {
    w2_wasIn4 = false;
    w2_wasIn1 = false;
    }
}

void Swerve::set_rotations_w3(){
    if(Total_angle_W3 >= 0 && Total_angle_W3 <= 90)
    {
    w3_wasIn1 = true;
    if(w3_wasIn4)
    {
        rotationCounter_w3++;
        w3_wasIn4 = false;
    }
    }
    else if(Total_angle_W3 >= 270 && Total_angle_W3 < 360)
    {
    w3_wasIn4 = true;
    if(w3_wasIn1)
    {
        rotationCounter_w3--;
        w3_wasIn1 = false;
    }
    }
    else
    {
    w3_wasIn4 = false;
    w3_wasIn1 = false;
    }  
}

void Swerve::set_rotations_w4(){
    if(Total_angle_W4 >= 0 && Total_angle_W4 <= 90)
    {
    w4_wasIn1 = true;
    if(w4_wasIn4)
    {
        rotationCounter_w4++;
        w4_wasIn4 = false;
    }
    }
    else if(Total_angle_W4 >= 270 && Total_angle_W4 < 360)
    {
    w4_wasIn4 = true;
    if(w4_wasIn1)
    {
        rotationCounter_w4--;
        w4_wasIn1 = false;
    }
    }
    else
    {
    w4_wasIn4 = false;
    w4_wasIn1 = false;
    }
}

void Swerve::set_motor_position(){
if(vector_straffe <= 0.1 && (vector_rotation <= 0.1 && vector_rotation >= -0.1 ))
{
  positionFR = 11264 + (rotationCounter_w1*45056);    // 90 degrees //back to start position
  positionFL = 11264 + (rotationCounter_w2*45056);    // 90 degrees
  positionBL = 11264 + (rotationCounter_w3*45056);    // 90 degrees
  positionBR = 11264 + (rotationCounter_w4*45056);    // 90 degrees
}
else
{
  positionFR =(45056 * (Total_angle_W1/360))+(rotationCounter_w1*45056); //(45056 * (angle/360)) + rot_count*45056 
  positionFL =(45056 * (Total_angle_W2/360))+(rotationCounter_w2*45056); //(45056 * (angle/360)) + rot_count*45056 
  positionBL =(45056 * (Total_angle_W3/360))+(rotationCounter_w3*45056); //(45056 * (angle/360)) + rot_count*45056 
  positionBR =(45056 * (Total_angle_W4/360))+(rotationCounter_w4*45056); //(45056 * (angle/360)) + rot_count*45056       
}
  motorFRR.Set(ControlMode::Position, positionFR);  
  motorFLR.Set(ControlMode::Position, positionFL);     
  motorRLR.Set(ControlMode::Position, positionBL);     
  motorRRR.Set(ControlMode::Position, positionBR);
}

void Swerve::set_motor_speed(){
  motorFRD.Set(ControlMode::PercentOutput, Total_Vector_W1/speedmode);
  motorFLD.Set(ControlMode::PercentOutput, -Total_Vector_W2/speedmode);
  motorRRD.Set(ControlMode::PercentOutput, Total_Vector_W3/speedmode);
  motorRLD.Set(ControlMode::PercentOutput, -Total_Vector_W4/speedmode);
}

void Swerve::Swerve_mainloop(){
    calculate_vector_straffe();
    calculate_vector_rotation();
    calculate_total_vector();
    calculate_total_angle_w1();
    calculate_total_angle_w2();
    calculate_total_angle_w3();
    calculate_total_angle_w4();
    set_rotations_w1();
    set_rotations_w2();
    set_rotations_w3();
    set_rotations_w4();
    set_motor_position();
    set_motor_speed();
}