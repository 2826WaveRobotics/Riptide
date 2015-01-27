#ifndef UTILS_H
#define UTILS_H

#include <math.h>

class Utils{
public:
	Utils(){};
	inline double HandleDeadband(double val, double deadband){return (fabs(val) > fabs(deadband)) ? val : 0.0;};
	inline double PwmLimit(double pwm){return pwm >= 1.0 ? 1.0 : pwm <= -1.0 ? -1.0 : pwm;};
};

#endif
