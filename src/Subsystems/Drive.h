#ifndef DRIVE_H
#define DRIVE_H

#include "WPILib.h"
#include "Constants.h"
#include "Utils.h"
#include "OI.h"

class Drive
{
public:
	Drive();
	static Constants *constants;
	static Utils *utils;
	static OI *oi;
	void SetPower(double power);
	RobotDrive* driveBase;

	void ResetEncoders();
	void SetHighGear(bool toHigh);

	void SetLinearPower(double left, double right);
	double Linearize(double linear);
	void SetPower(double linearLeft, double linearRight);
	double GetLeftEncoderDistance();
	double GetRightEncoderDistance();
	double GetGyroAngle();
	void ResetGyro();
	void Riptide(double throttle, double wheel, bool quickTurn);
	void SetControlLoopsOn(bool on);

private:
	CANTalon* left1;
	CANTalon* left2;
	//Talon* left3;
	CANTalon* right1;
	CANTalon* right2;
	//Talon right3;
	Encoder* leftEncoder;
	Encoder* rightEncoder;
	Gyro* gyro;
	Solenoid* shifter;

	double m_prevAngularPower = 0.0;
	bool m_controlLoops = false;
	double m_old_wheel = 0.0;
	bool m_highGear = true;
	double m_quickStopAccumulator = 0.0;

};

#endif
