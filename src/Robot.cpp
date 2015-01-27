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
		drive->driveBase->SetSafetyEnabled(1);
		//drive->SetControlLoopsOn(1);
		if(!oi->getDebugJoystick2()->GetRawButton(5))
		{
			drive->driveBase->ArcadeDrive(oi->getDriverJoystick()->GetRawAxis(1), oi->getDriverJoystick()->GetRawAxis(4)); // drive
		}
		else
		{
			drive->Riptide(oi->getDriverJoystick()->GetRawAxis(1), oi->getDriverJoystick()->GetRawAxis(4), oi->getDriverJoystick()->GetRawButton(6));


			//drive->driveBase->ArcadeDrive(oi->getDriverJoystick()->GetRawAxis(1), oi->getDriverJoystick()->GetRawAxis(4)); // drive
		}

	Wait(.005); // Wait 5ms for the next update.
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
