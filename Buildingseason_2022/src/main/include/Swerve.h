#pragma once


#include <frc/smartdashboard/SmartDashboard.h> 
#include <ctre/phoenix.h>
#include <frc/PS4controller.h>

class Swerve{
  private:
  frc::PS4Controller *swerveJoystick;
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

  TalonSRX motorFLD = {1};        
  TalonSRX motorFRD = {3};          
  TalonSRX motorFRR = {4}; // front right rotation
  TalonSRX motorFLR = {2}; // front left rotation
  TalonSRX motorRRD = {7};
  TalonSRX motorRRR = {8}; // rear right rotation     
  TalonSRX motorRLD = {5};
  TalonSRX motorRLR = {6}; //  rear left rotation

  // Variables swervedrive
  int positionFL = 0;
  int positionFR = 0;
  int positionBL = 0;
  int positionBR = 0;

  int desiredPosition = 0;
  int lastPosition = 0;
  double kp = 0.4;
  double ki = 0.000001;
  double kd = 0.2;
  int x = 0;
  double angle = 0;
  bool w1_wasIn4 = false; 
  bool w1_wasIn1 = false;
  bool w2_wasIn4 = false; 
  bool w2_wasIn1 = false;
  bool w3_wasIn4 = false; 
  bool w3_wasIn1 = false;
  bool w4_wasIn4 = false; 
  bool w4_wasIn1 = false;
  double rotationCounter_w1 = 0;
  double rotationCounter_w2 = 0;
  double rotationCounter_w3 = 0;
  double rotationCounter_w4 = 0;
  int speedmode = 1;

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
  double xVal_straffe = 0;
  double yVal_straffe = 0;
  double vector_straffe = 0;
  double vector_rotation = 0;

};

