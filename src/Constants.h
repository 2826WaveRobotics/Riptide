class Constants{
public:
const double c_wheelDiameter = 6;
// Motors

const double c_leftDrivePwmA = 5;
const double c_leftDrivePwmB = 4;
const double c_rightDrivePwmA = 6;
const double c_rightDrivePwmB = 7;
const double c_intakePwm1 = 2;
const double c_intakePwm2 = 1;
const double c_intakePwm3 = 10;
const double c_conveyorPwm = 9;
const double c_leftShooterPwm = 3;
const double c_rightShooterPwm = 8;

// Analog sensors
const double c_gyroPort = 1;
const double c_poofMeterPort = 6;
const double c_ballRangerPort = 5;
const double c_conveyorBallSensorPort = 4;

// Digital sensors
const double c_bumpSensorPort = 5;
const double c_leftEncoderPortA = 0;
const double c_leftEncoderPortB = 1;
const double c_rightEncoderPortA = 2;
const double c_rightEncoderPortB = 3;
const double c_shooterEncoderPortA = 6;
const double c_shooterEncoderPortB = 7;

// Pneumatics
const double c_compressorPressureSwitchPort = 14;
const double c_compressorRelayPort = 8;
const double c_dingusSolenoidPort = 4;
const double c_pizzaWheelSolenoidDownPort = 1;
const double c_hoodSolenoidPort = 6;
const double c_intakeSolenoidUpPort = 5;
const double c_intakeSolenoidDownPort = 7;
const double c_brakeSolenoidOnPort = 2;
const double c_brakeSolenoidOffPort = 3;
const double c_shiftSolenoidPort = 8;

// Vision
const double c_thresholdRMin = 0;
const double c_thresholdRMax = 50;
const double c_thresholdGMin = 0;
const double c_thresholdGMax = 50;
const double c_thresholdBMin = 80;
const double c_thresholdBMax = 255;
const double c_cameraOffset = 0.0;

// Driver controls
const double c_leftJoystickPort = 1;
const double c_rightJoystickPort = 2;

// Operator controls
const double c_operatorControlPort = 3;
const double c_intakeUpPort = 4;
const double c_intakeDownPort = 12;
const double c_autonSelectPort = 11;
const double c_unjamPort = 10;
const double c_shootPort = 9;
const double c_autoShootPort = 8;
const double c_intakePort = 7;
const double c_increasePort = 6;
const double c_decreasePort = 5;
const double c_keyFarPort = 4;
const double c_keyClosePort = 3;
const double c_farFenderPort = 2;
const double c_fenderPort = 1;
const double c_shooterOnPort = 3;

// Left joystick
const double c_autoAlignPort = 2;;
const double c_highGearPort = 3;;

// Right joystick
const double c_quickTurnPort = 2;;
const double c_pizzaSwitchPort = 3;;

// Linearization
const double c_linearCoeffA = 4.5504;
const double c_linearCoeffB = -5.9762;
const double c_linearCoeffC = 2.5895;
const double c_linearCoeffD = -0.0869;
const double c_linearCoeffE = 0.0913;
const double c_shooterCoeffA = 4.7658;
const double c_shooterCoeffB = -5.8827;
const double c_shooterCoeffC = 1.8275;
const double c_shooterCoeffD = 0.2894;
const double c_conveyorCoeffA = 0.5021;
const double c_conveyorCoeffB = 0.16;
const double c_conveyorCoeffC = 0.3228;
const double c_conveyorCoeffD = 1.1347;

// Camera relations
const double c_distanceCoeffA = 3.512162035166973e-10;
const double c_distanceCoeffB = -2.499565619933737e-07;
const double c_distanceCoeffC = 7.249335506446627e-05;
const double c_distanceCoeffD = -0.010982102151858;
const double c_distanceCoeffE = 0.925726454960144;
const double c_distanceCoeffF = -42.769351848830162;
const double c_distanceCoeffG = 9.943136608058143e+02;

// Drive tuning
const double c_turnSensLow = 1.1;
const double c_turnSensHigh = 1.4;
const double c_inertiaGain = .0035;

// Shooter
const double c_shooterFenderSpeed = 36.0;
const double c_shooterFarFenderSpeed = 40;
const double c_shooterKeyCloseSpeed = 49.5;
const double c_shooterKeyFarSpeed = 52;
const double c_shooterSpeedIncrement = 0.5;
const double c_shooterBridgeSpeed = 56;


// PID constants
const double c_driveKP = 0.12;
const double c_driveKI = 0.0;
const double c_driveKD = 1.2;
const double c_driveVelKP = 0.0006;
const double c_driveVelKI = 0.0000;
const double c_driveVelKD = 0.0005;
const double c_baseLockKP = 1.5;
const double c_baseLockKI = 0.01;
const double c_baseLockKD = 0;
const double c_shooterKP = 0.0;
const double c_shooterKI = 0.0;
const double c_shooterKD = 0.0;
const double c_turnKP = 0.074;
const double c_turnKI = 0.000;
const double c_turnKD = 0.550;
const double c_breakStaticOffset = 0.4;
const double c_autoCameraAlignKP = 0.115;
const double c_autoCameraAlignKI = 0.004;
const double c_autoCameraAlignKD = 0.05;
const double c_straightDriveGain = 0.05;

// Automomous
const double c_autoShootKeyVel = 53.5;
const double c_autoAlignThreshold = .5;

// Turning
const double c_turnNonlinHigh = 0.9;
const double c_turnNonlinLow = 0.8;
const double c_negInertiaHigh = 5.0; // Was 10.0
const double c_senseHigh = 1.2;
const double c_negInertiaLowMore = 2.5;  // Was 5.0
const double c_negInertiaLowLessExt = 5.0;  // Was 10.0
const double c_negInertiaLowLess = 3.0;  // Was 6.0
const double c_senseLow = 1.10;
const double c_senseCutoff = 0.1;
const double c_quickStopTimeConstant = .1;
const double c_quickStopStickScalar = 5;
const double c_driveControllerKiTurn = 0.15;

// Offsets
const double c_hardBallOffset = -.2;
const double c_wtfHardBallOffset = -.5;
const double c_softBallOffset = .2;
const double c_wtfSoftBallOffset = .5;
};
