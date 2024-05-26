#ifndef MOTORS
#define MOTORS
void MotorSetup(int p1, int p2, int n1, int n2, int e1, int e2);

void ToggleMotor1(int dir);
void ToggleMotor2(int dir);
void AdjustMotor1(int cycle);
void AdjustMotor2(int cycle);
void AdjustMotor1B(int cycle);
void AdjustMotor2B(int cycle);
#endif