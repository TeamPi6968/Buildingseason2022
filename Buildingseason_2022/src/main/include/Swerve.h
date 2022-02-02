#pragma once


#include <frc/smartdashboard/SmartDashboard.h> 
#include <ctre/phoenix.h>
#include <frc/PS4controller.h>

class Swerve{
  private:

  frc::PS4Controller *swerveJoystick; //Pointer to controller
  //Functions for the swerve drive
  void calculate_vector_straffe();
  void calculate_vector_rotation();
  void calculate_total_vector();
  void calculate_total_angle_w1();
  void calculate_total_angle_w2();
  void calculate_total_angle_w3();
  void calculate_total_angle_w4();
  void set_rotations_w1();
  void set_rotations_w2();
  void set_rotations_w3();
  void set_rotations_w4();
  void set_motor_position();
  void set_motor_speed();

  public:
  Swerve(frc::PS4Controller *controller);

  void Initialize_swerve();
  void Configure_PID();
  void Swerve_mainloop();

  TalonFX motorFLD = {1}; //Front Left Drive       
  TalonFX motorFLR = {2}; //Front Left Rotation
  TalonFX motorFRD = {3}; //Front Rear Drive       
  TalonFX motorFRR = {4}; //Front Rear Rotation
  TalonFX motorRLD = {5}; //Back Left Drive
  TalonFX motorRLR = {6}; //Back Left Rotation
  TalonFX motorRRD = {7}; //Back Rear Drive
  TalonFX motorRRR = {8}; //Back Rear Rotation  
  

  // Variables swervedrive
  const int oneTurn = 4096; //Encoder pulses for one rotation Falcon fx

  //Oriantation is 90 degrees rotated so every wheel needs to correct that error
  int positionFL = 2.5*oneTurn;  
  int positionFR = 2.5*oneTurn;
  int positionBL = 2.5*oneTurn;
  int positionBR = 2.5*oneTurn;

  //PID values of the front wheels
  double kp = 0.4;
  double ki = 0.0001;
  double kd = 0.45;

  //PID values of the back wheels
  double kp2 = 0.51;
  double ki2 = 0.0008;
  double kd2 = 0.51;

  //Keep track of where the wheels are for smooth transition
  bool w1_wasIn4 = false; 
  bool w1_wasIn1 = false;
  bool w2_wasIn4 = false; 
  bool w2_wasIn1 = false;
  bool w3_wasIn4 = false; 
  bool w3_wasIn1 = false;
  bool w4_wasIn4 = false; 
  bool w4_wasIn1 = false;

  //Rotation counter of the wheels
  double rotationCounter_w1 = 0;
  double rotationCounter_w2 = 0;
  double rotationCounter_w3 = 0;
  double rotationCounter_w4 = 0;

  //Speed limitation of the swervedrive (0.5 is the lower limit)
  double speedmode = 1;

  //Variables of the wheels X,Y,Vector and Angle
  double Total_XW1 = 0;
  double Total_YW1 = 0;
  double Total_Vector_W1 = 0;
  double Total_angle_W1 = 0;
  double Total_XW2 = 0;
  double Total_YW2 = 0;
  double Total_Vector_W2 = 0;
  double Total_angle_W2 = 0;
  double Total_XW3 = 0;
  double Total_YW3 = 0;
  double Total_Vector_W3 = 0;
  double Total_angle_W3 = 0;
  double Total_XW4 = 0;
  double Total_YW4 = 0;
  double Total_Vector_W4 = 0;
  double Total_angle_W4 = 0;

  //Variables of the movements
  double xVal_straffe = 0;
  double yVal_straffe = 0;
  double vector_straffe = 0;
  double vector_rotation = 0;

};

