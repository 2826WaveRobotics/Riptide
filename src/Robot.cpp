#include "Robot.h"
#include "OI.h"

OI* Robot::oi = 0;
Drive* Robot::drive = 0;

Robot::Robot(){

}

void Robot::RobotInit(){
	oi = new OI();
	drive = new Drive();
}
void Robot::AutonomousInit()
{

}
void Robot::AutonomousPeriodic()
{

}
void Robot::TeleopInit(){

}

void Robot::TeleopPeriodic() {
	while (IsOperatorControl() && IsEnabled()) {

		//drive->driveBase->ArcadeDrive(oi->getDriverJoystick()->GetRawAxis(2), oi->getDriverJoystick()->GetRawAxis(4), false); // drive
		drive->Riptide(oi->getDriverJoystick()->GetRawAxis(2), oi->getDriverJoystick()->GetRawAxis(4), oi->getDriverJoystick()->GetRawButton(6));

	Wait(kUpdatePeriod); // Wait 5ms for the next update.
	}
}
void Robot::DisabledInit()
{

}
void Robot::DisabledPeriodic()
{

}

void Robot::TestInit()
{

}
void Robot::TestPeriodic()
{

}


START_ROBOT_CLASS(Robot);
