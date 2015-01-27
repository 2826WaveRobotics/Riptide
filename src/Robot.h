#include "WPILib.h"
#include "OI.h"
#include "Subsystems\Drive.h"

class Robot : public IterativeRobot {

	double kUpdatePeriod = 0.05;

public:
static OI *oi;
static Drive *drive;

Robot();
virtual void RobotInit();
	virtual void DisabledInit();
	virtual void AutonomousInit();
	virtual void TeleopInit();
	virtual void TestInit();

	virtual void DisabledPeriodic();
	virtual void AutonomousPeriodic();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();

};

