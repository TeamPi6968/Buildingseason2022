
#include "Swerve.h"

//Create a swerve module
Swerve::Swerve(frc::PS4Controller *controller){
  swerveJoystick = controller; //Assing the joystick
}
//Give the wheels the rotaion of 90 degrees as thay are alliant right now

void Swerve::Initialize_swerve(){ 
  frc::SmartDashboard::PutNumber("Cont X value", 0);
  frc::SmartDashboard::PutNumber("Cont Y value", 0);
  frc::SmartDashboard::PutNumber("X", vector_rotation);
  rotationCounter_w1 = 0;
  rotationCounter_w2 = 0;
  rotationCounter_w3 = 0;
  rotationCounter_w4 = 0;

  motorFLR.SetSelectedSensorPosition((rotatieverhouding/4)*oneTurn);
  motorFRR.SetSelectedSensorPosition((rotatieverhouding/4)*oneTurn);        
  motorRRR.SetSelectedSensorPosition((rotatieverhouding/4)*oneTurn);
  motorRLR.SetSelectedSensorPosition((rotatieverhouding/4)*oneTurn);
}
//Configure the PID values for the swerve
void Swerve::Configure_PID(){ //poop
  //PID values of Front Left Rotation
  motorFLR.Config_kP(0, kp);
  motorFLR.Config_kI(0, ki);
  motorFLR.Config_kD(0, kd);
  //PID values of Front Right Rotation
  motorFRR.Config_kP(0, kp2);
  motorFRR.Config_kI(0, ki2);
  motorFRR.Config_kD(0, kd2);
  //PID values of Rear Right Rotation
  motorRRR.Config_kP(0, kp);
  motorRRR.Config_kI(0, ki);
  motorRRR.Config_kD(0, kd);
  //PID values of Rear Left Rotation
  motorRLR.Config_kP(0, kp2);
  motorRLR.Config_kI(0, ki2);
  motorRLR.Config_kD(0, kd2);
}

void Swerve::calculate_vector_straffe(){
  //Get values of controller
  xVal_straffe = swerveJoystick->GetLeftX();
  yVal_straffe = swerveJoystick->GetLeftY();
  //Calculate vector
  vector_straffe = sqrt(pow(xVal_straffe, 2) + pow(yVal_straffe, 2));
  //Set values to zero when the vector is smaller than 0.1 due the misreadings when you don't touch the joystick
  if(vector_straffe<=0.1){
    xVal_straffe = 0;
    yVal_straffe = 0;
  }

  frc::SmartDashboard::PutNumber("Cont X value", xVal_straffe);
  frc::SmartDashboard::PutNumber("Cont Y value", yVal_straffe);
}

void Swerve::calculate_vector_rotation(){
  //Get values of controller
  vector_rotation = swerveJoystick->GetL2Axis();
  //Set values to zero when the vector is smaller than 0.1 due the misreadings when you don't touch the joystick
  if(vector_rotation<=0.1 && vector_rotation >= -0.1)
  {
    vector_rotation = 0;
  }
}

void Swerve::calculate_total_vector(){
  //Calculate the X and Y values of the vector of every wheel
  /*
        -Y
        |
  -X ---|--- X
        |
        Y
  */
  Total_XW1 = (xVal_straffe+(vector_rotation/sqrt(2)))/2;
  Total_YW1 = (yVal_straffe+(vector_rotation/sqrt(2)))/2;
  Total_XW2 = (xVal_straffe+(vector_rotation/sqrt(2)))/2;
  Total_YW2 = (yVal_straffe-(vector_rotation/sqrt(2)))/2;
  Total_XW3 = (xVal_straffe-(vector_rotation/sqrt(2)))/2;
  Total_YW3 = (yVal_straffe-(vector_rotation/sqrt(2)))/2;
  Total_XW4 = (xVal_straffe-(vector_rotation/sqrt(2)))/2;
  Total_YW4 = (yVal_straffe+(vector_rotation/sqrt(2)))/2;
  //Calculate the magnitute of the resulting vector
  Total_Vector_W1 = sqrt(pow(Total_XW1, 2) + pow(Total_YW1, 2)); 
  Total_Vector_W2 = sqrt(pow(Total_XW2, 2) + pow(Total_YW2, 2));
  Total_Vector_W3 = sqrt(pow(Total_XW3, 2) + pow(Total_YW3, 2));
  Total_Vector_W4 = sqrt(pow(Total_XW4, 2) + pow(Total_YW4, 2));
}

double Swerve::calculate_total_angle_of_wheel(double X, double Y){
  if((X >= 0) && (Y <= 0)) //Angle is in first quarter
  //Angle <= 90, Rotaions <= 2.5, Total pulzen 4096*2.5 = 10240 (be careful directions on the code is different)
  {
    return ((atan(-Y/X))/M_PI_2) * 90;
  }
  else if((X < 0) && (Y <= 0)) //Angle is in second quarter
  //Angle 180 >= && Angle > 90, Rotaions <= 5, Total pulzen 4096*5 = 20.480
  {
    return 180 - (((atan(Y/X))*90)/M_PI_2);
  }
  else if(X < 0 && Y > 0) //Angle is in third quarter  
  //Angle 270 >= && Angle > 180, Rotaions <= 7.5, Total pulzen 4096*7.5 = 30.720  
  {
    return 270 - (((atan(-X/Y))*90)/M_PI_2); 
  } 
  else if(X >= 0 && Y >= 0) //Angle is in fourth quarter  
  //Angle 360 >= && Angle > 270, Rotaions <= 10, Total pulzen 4096*10 = 40960
  { 
    return 360 - (((atan(Y/X))*90)/M_PI_2);
  }
}

/*
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
*/

void Swerve::set_rotations_w1(){
    if(Total_angle_W1 >= 0 && Total_angle_W1 <= 90) //Wheel in Q1
    {
    w1_wasIn1 = true;
    if(w1_wasIn4) //Came from Q4 so made one round 
    {
      rotationCounter_w1++;
      w1_wasIn4 = false;
    }
    }
    else if(Total_angle_W1 >= 270 && Total_angle_W1 < 360) //Wheel in Q4
    {
    w1_wasIn4 = true;
    if(w1_wasIn1) //Came from Q1 so made one round 
    {
      rotationCounter_w1--;
      w1_wasIn1 = false;
    }
    }
    else //Not in a quarter
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

void Swerve::set_motor_position(){ //Rotate the module
//if(vector_straffe <= 0.1 && (vector_rotation <= 0.1 && vector_rotation >= -0.1 )) //Both movements active
//{
//  positionFR = (rotatieverhouding/4)*oneTurn + (rotationCounter_w1*rotatieverhouding*oneTurn); //90 degrees back to start position
//  positionFL = (rotatieverhouding/4)*oneTurn + (rotationCounter_w2*rotatieverhouding*oneTurn); //90 degrees
//  positionBL = (rotatieverhouding/4)*oneTurn + (rotationCounter_w3*rotatieverhouding*oneTurn); //90 degrees
//  positionBR = (rotatieverhouding/4)*oneTurn + (rotationCounter_w4*rotatieverhouding*oneTurn); //90 degrees

//}
//else if(vector_straffe < 0.1 && (vector_rotation > 0.1 || vector_rotation < -0.1)){
//  positionFR = 3.375*oneTurn + (rotationCounter_w1*27*oneTurn); //90 degrees back to start position
//  positionFL = 10.125*oneTurn + (rotationCounter_w2*27*oneTurn); //90 degrees
//  positionBL = 16.875*oneTurn + (rotationCounter_w3*27*oneTurn); //90 degrees
//  positionBR = 23.625*oneTurn + (rotationCounter_w4*27*oneTurn); //90 degrees
//}
//else 
//{
  // gear ratio is  1 by 27
  positionFR =(rotatieverhouding*oneTurn * (Total_angle_W1/360))+(rotationCounter_w1*rotatieverhouding*oneTurn); //(45056 * (angle/360)) + rot_count*45056 
  positionFL =(rotatieverhouding*oneTurn * (Total_angle_W2/360))+(rotationCounter_w2*rotatieverhouding*oneTurn); //(45056 * (angle/360)) + rot_count*45056 
  positionBL =(rotatieverhouding*oneTurn * (Total_angle_W3/360))+(rotationCounter_w3*rotatieverhouding*oneTurn); //(45056 * (angle/360)) + rot_count*45056 
  positionBR =(rotatieverhouding*oneTurn * (Total_angle_W4/360))+(rotationCounter_w4*rotatieverhouding*oneTurn); //(45056 * (angle/360)) + rot_count*45056   
  //test

//   //test because controller 2 circles
//   positionFR = positionFR/2;
//   positionFL = positionFL/2;
//   positionBL = positionBL/2;
//   positionBR = positionBR/2;

  
  frc::SmartDashboard::PutNumber("positionFR",positionFR); 
  frc::SmartDashboard::PutNumber("positionFL",positionFL);  
  frc::SmartDashboard::PutNumber("positionBL",positionBL);  
  frc::SmartDashboard::PutNumber("positionBR",positionBR);     
//}
  motorFRR.Set(ControlMode::Position, positionFR);  
  motorFLR.Set(ControlMode::Position, positionFL);     
  motorRLR.Set(ControlMode::Position, positionBL);     
  motorRRR.Set(ControlMode::Position, positionBR);
}
void Swerve::allign_wheels(){
  switch(allign_steps){
    case 0:
    
    motorFRR.Set(ControlMode::PercentOutput,swerveJoystick->GetLeftX()/4); 
    
    if (swerveJoystick->GetCrossButton() == true){//circle
    allign_steps = 1;
    }
    break;

    case 1:
    motorFLR.Set(ControlMode::PercentOutput,swerveJoystick->GetLeftX()/4);

    if (swerveJoystick->GetCircleButton() == true){//square
    allign_steps = 2;
    }
    break;

    case 2:
    motorRLR.Set(ControlMode::PercentOutput,swerveJoystick->GetLeftX()/4);
    if (swerveJoystick->GetCrossButton() == true){//Circle
    allign_steps = 3;
    }
    break;

    case 3:
    motorRRR.Set(ControlMode::PercentOutput,swerveJoystick->GetLeftX()/4);
    if (swerveJoystick->GetCircleButton() == true){//square
    allign_steps = 4;
    }
    break;
 

  };
}
void Swerve::set_motor_speed(){ //Drive the motors
  
 //motorFRD.Set(ControlMode::PercentOutput, Total_Vector_W1/speedmode);
  
  motorFLD.Set(ControlMode::PercentOutput, -Total_Vector_W2/speedmode);
 
  motorRLD.Set(ControlMode::PercentOutput, -Total_Vector_W3/speedmode);
  
  motorRRD.Set(ControlMode::PercentOutput, Total_Vector_W4/speedmode);
}

void Swerve::Swerve_mainloop(){ //Mainloop of the drivetrain
    calculate_vector_straffe();
    calculate_vector_rotation();
    calculate_total_vector();
    Total_angle_W1 = calculate_total_angle_of_wheel(Total_XW1, Total_YW1);
    Total_angle_W2 = calculate_total_angle_of_wheel(Total_XW2, Total_YW2);
    Total_angle_W3 = calculate_total_angle_of_wheel(Total_XW3, Total_YW3);
    Total_angle_W4 = calculate_total_angle_of_wheel(Total_XW4, Total_YW4); 
    frc::SmartDashboard::PutNumber("angle w1",Total_angle_W1);
    frc::SmartDashboard::PutNumber("angle w2",Total_angle_W2);
    frc::SmartDashboard::PutNumber("angle w3",Total_angle_W3);
    frc::SmartDashboard::PutNumber("angle w4",Total_angle_W4);
    set_rotations_w1();
    set_rotations_w2();
    set_rotations_w3();
    set_rotations_w4();
    set_motor_position();
    set_motor_speed();
}