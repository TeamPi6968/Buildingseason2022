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
  double calculate_total_angle_of_wheel(double X, double Y);
  // void calculate_total_angle_w2();
  // void calculate_total_angle_w3();
  // void calculate_total_angle_w4();
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

  TalonFX motorFLD = {2}; //Front Left Drive       
  TalonFX motorFLR = {3}; //Front Left Rotation
  TalonFX motorFRD = {1}; //Front Rear Drive       
  TalonFX motorFRR = {20}; //Front Rear Rotation
  TalonFX motorRLD = {17}; //Back Left Drive
  TalonFX motorRLR = {16}; //Back Left Rotation
  TalonFX motorRRD = {18}; //Back Rear Drive
  TalonFX motorRRR = {19}; //Back Rear Rotation  
  

  // Variables swervedrive
  const int oneTurn = 4096; //Encoder pulses for one rotation Falcon fx

  //Oriantation is 90 degrees rotated so every wheel needs to correct that error
  int positionFL = 6.75*oneTurn;  
  int positionFR = 6.75*oneTurn;
  int positionBL = 6.75*oneTurn;
  int positionBR = 6.75*oneTurn;

  //PID values of the front wheels
  double kp = 0.4;//Old robot
  double ki = 0.00019;//Old robot
  double kd = 0.5;//Old robot

  //PID values of the back wheels
  double kp2 = 0.7;//Old robot
  double ki2 = 0.0019;//Old robot
  double kd2 = 0.65;//Old robot

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
  double speedmode = 2;

  //Variables of the wheels X,Y,Vector and Angle
  double Total_XW1 = 0;
  double Total_YW1 = 0;
  double Total_Vector_W1 = 0;
  double velocity_max = 0.5;
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
