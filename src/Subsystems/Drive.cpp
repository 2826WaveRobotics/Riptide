#include "Drive.h"
#include <cmath>
#include "Utils.h"

Constants* Drive::constants = 0;
Utils* Drive::utils = 0;

Drive::Drive()
{
	left1 = new CANTalon(0);
	left2 = new CANTalon(1);

	right1 = new CANTalon(2),
	right2 = new CANTalon(3),

	driveBase = new RobotDrive(left1, left2, right1, right2);
	driveBase->SetExpiration(.1);

	leftEncoder = new Encoder(0,1);
	rightEncoder = new Encoder(2,3);
	ResetEncoders();

	gyro = new Gyro(0);
	ResetGyro();

	shifter = new Solenoid(1);
	SetHighGear(true);
	constants = new Constants();
	utils = new Utils();
}
void Drive::SetPower(double left, double right) {
  left = utils->PwmLimit(left); // makes sure the values are within the accepted -1 to 1 range
  right = utils->PwmLimit(right);

  left1->Set(left);
  left2->Set(-left); //reverse 550				//check to see if our motors are inverted
  right1->Set(-right);
  right2->Set(right); //reverse 550s
}
void Drive::ResetEncoders(){
	leftEncoder->Reset();
	rightEncoder->Reset();
}
void Drive::SetHighGear(bool toHigh){
	m_highGear = toHigh;
	shifter->Set(toHigh);
}
void Drive::SetLinearPower(double left, double right) {
	double linearLeft=Linearize(left);
	double linearRight=Linearize(right);
	linearLeft = (linearLeft > 1.0) ? 1.0 : (linearLeft < -1.0) ? -1.0 : linearLeft; // if greater than 1, make 1, then if less than -1, make -1, otherwise leave alone
	linearRight = (linearRight > 1.0) ? 1.0 : (linearRight < -1.0) ? -1.0 : linearRight;
	SetPower(linearLeft, linearRight);
}
double Drive::Linearize(double x) {
  if (fabs(x) < 0.01 ) { // get rid of deadband
    x = 0.0;
  }
  if (x > 0.0) { // so if there was a value to begin with
    return constants->c_linearCoeffA * pow(x, 4) + constants->c_linearCoeffB * pow(x, 3) +
        constants->c_linearCoeffC * pow(x, 2) + constants->c_linearCoeffD * x + constants->c_linearCoeffE;
  } else if (x < 0.0) {
    // Rotate the linearization function by 180.0 degrees to handle negative input.
    return -Linearize(-x);
  } else {
    return 0.0;
  }
}

double Drive::GetLeftEncoderDistance() {
	return -leftEncoder->Get() / 256.0 * constants->c_wheelDiameter * 3.14159265;
}

double Drive::GetRightEncoderDistance() {
	return rightEncoder->Get() / 256.0 * constants->c_wheelDiameter * 3.14159265;
}

double Drive::GetGyroAngle() {
  return gyro->GetAngle();
}

void Drive::ResetGyro() {
  gyro->Reset();
}

void Drive::Riptide(double throttle, double wheel, bool quickTurn) {
  bool isQuickTurn = quickTurn; // checks to see if quickturn is active
  bool isHighGear = m_highGear; //checks gearing

  double wheelNonLinearity; //idk what this is yet

  double neg_inertia = wheel - m_old_wheel; //sets a change in previous to current value of the "wheel"
  m_old_wheel = wheel;//stores a value of "wheel"

  if (isHighGear) {
    wheelNonLinearity = constants->c_turnNonlinHigh;//applies a constant (.9)
    // Apply a sin function that's scaled to make it feel better.
    wheel = sin(M_PI / 2.0 * wheelNonLinearity * wheel) / sin(M_PI / 2.0 * wheelNonLinearity);//sin(pi/2 * const * turn value
    wheel = sin(M_PI / 2.0 * wheelNonLinearity * wheel) / sin(M_PI / 2.0 * wheelNonLinearity);//twice
  } else {
    wheelNonLinearity = constants->c_turnNonlinLow;
    // Apply a sin function that's scaled to make it feel better.
    wheel = sin(M_PI / 2.0 * wheelNonLinearity * wheel) / sin(M_PI / 2.0 * wheelNonLinearity);
    wheel = sin(M_PI / 2.0 * wheelNonLinearity * wheel) / sin(M_PI / 2.0 * wheelNonLinearity);
    wheel = sin(M_PI / 2.0 * wheelNonLinearity * wheel) / sin(M_PI / 2.0 * wheelNonLinearity);//three times. the const is .8
  }

  double left_pwm, right_pwm, overPower;
  float sensitivity = 1.7;

  float angular_power;
  float linear_power;

  // Negative inertia!
  static double neg_inertia_accumulator = 0.0;//reset that
  double neg_inertia_scalar;
  if (isHighGear) {
    neg_inertia_scalar = constants->c_negInertiaHigh;//5
    sensitivity = constants->c_senseHigh;//1.2
  } else {
    if (wheel * neg_inertia > 0) {
      neg_inertia_scalar = constants->c_negInertiaLowMore;
    } else {
      if (fabs(wheel) > 0.65) {
        neg_inertia_scalar = constants->c_negInertiaLowLessExt;
      } else {
        neg_inertia_scalar = constants->c_negInertiaLowLess;
      }
    }
    sensitivity = constants->c_senseLow;

    if (fabs(throttle) > constants->c_senseCutoff) {
      sensitivity = 1 - (1 - sensitivity) / fabs(throttle);
    }
  }
  double neg_inertia_power = neg_inertia * neg_inertia_scalar;
  neg_inertia_accumulator += neg_inertia_power;

  wheel = wheel + neg_inertia_accumulator;
  if(neg_inertia_accumulator > 1)
    neg_inertia_accumulator -= 1;
  else if (neg_inertia_accumulator < -1)
    neg_inertia_accumulator += 1;
  else
    neg_inertia_accumulator = 0;

  linear_power = throttle;

  // Quickturn!
  if (isQuickTurn) {
    if (fabs(linear_power) < 0.2) {
      double alpha = constants->c_quickStopTimeConstant;
      m_quickStopAccumulator = (1 - alpha) * m_quickStopAccumulator + alpha * utils->PwmLimit(wheel) * constants->c_quickStopStickScalar;
    }
    overPower = 1.0;
    if (isHighGear) {
      sensitivity = 1.0;
    } else {
      sensitivity = 1.0;
    }
    angular_power = wheel;
  } else {
    overPower = 0.0;
    angular_power = fabs(throttle) * wheel * sensitivity - m_quickStopAccumulator;
    if (m_quickStopAccumulator > 1) {
      m_quickStopAccumulator -= 1;
    } else if (m_quickStopAccumulator < -1) {
      m_quickStopAccumulator += 1;
    } else {
      m_quickStopAccumulator = 0.0;
    }
  }

  right_pwm = left_pwm = linear_power;
  left_pwm += angular_power;
  right_pwm -= angular_power;

  if (left_pwm > 1.0) {
    right_pwm -= overPower * (left_pwm - 1.0);
    left_pwm = 1.0;
  } else if (right_pwm > 1.0) {
    left_pwm -= overPower * (right_pwm - 1.0);
    right_pwm = 1.0;
  } else if (left_pwm < -1.0) {
    right_pwm += overPower * (-1.0 - left_pwm);
    left_pwm = -1.0;
  } else if (right_pwm < -1.0) {
    left_pwm += overPower * (-1.0 - right_pwm);
    right_pwm = -1.0;
  }

  printf("left pwm: %f right pwm: %f\n", left_pwm, right_pwm);
  SetLinearPower(left_pwm, right_pwm);

}
void Drive::SetControlLoopsOn(bool on){
  m_controlLoops = on;
}
