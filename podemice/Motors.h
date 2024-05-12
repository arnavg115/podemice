#ifndef MOTORS
#define MOTORS
void MotorSetup(int p1, int p2, int n1, int n2, int e1, int e2);

void ToggleMotor1(char dir);
void ToggleMotor2(char dir);
void AdjustMotor1();
void AdjustMotor2();
#endif