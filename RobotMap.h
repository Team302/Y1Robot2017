/*=============================================================================================
 * RobotMap.h
 *=============================================================================================
 *
 * File Description:
 *
 * The RobotMap defines the identifiers (e.g. what is the CAN ID of a particular Talon) for the
 * various motor controllers, sensors, etc.  It provides a constant that defines how the robot
 * is wired, so that if wiring changes, the constants in this file can be updated without impacting
 * the rest of the code.
 *=============================================================================================*/

#ifndef SRC_ROBOTMAP_H_
#define SRC_ROBOTMAP_H_

    //==========================================================================================
    // CAN PORTS
    //==========================================================================================
    const int LEFT_DRIVE_MOTOR      	= 1;
    const int RIGHT_DRIVE_MOTOR     	= 2;

    const int SHOOTER_WHEEL_MOTOR   		= 3;
    const int SHOOTER_LOAD_MOTOR    		= 4;
    const int SHOOTER_ALIGN_MOTOR   		= 5;

    //==========================================================================================
    // TALON (Motor) inversion settings
    //==========================================================================================
    const bool IS_LEFT_DRIVE_MOTOR_INVERTED    = true;
    const bool IS_RIGHT_DRIVE_MOTOR_INVERTED   = false;

    const bool IS_LEFT_DRIVE_SENSOR_INVERTED    = false;
    const bool IS_RIGHT_DRIVE_SENSOR_INVERTED   = false;

    const bool IS_SHOOTER_WHEEL_MOTOR_INVERTED  = false;
    const bool IS_SHOOTER_LOAD_MOTOR_INVERTED   = true;
    const bool IS_SHOOTER_ALIGN_MOTOR_INVERTED  = false;

    const bool IS_SHOOTER_WHEEL_SENSOR_INVERTED = true;
    const bool IS_SHOOTER_LOAD_SENSOR_INVERTED = true;
    const bool IS_SHOOTER_ALIGN_SENSOR_INVERTED = true;

    //==========================================================================================
    // Analog Input Devices
    //==========================================================================================
    const unsigned int LEFT_LINE_TRACKER    = 0;
    const unsigned int CENTER_LINE_TRACKER  = 1;
    const unsigned int RIGHT_LINE_TRACKER   = 2;

    const unsigned int SHOOTER_ANGLE_SENSOR = 3;

    //==========================================================================================
    // Digital Input/Output PORTS
    //==========================================================================================
    const unsigned int BALL_LOAD_SENSOR             = 1;

    const unsigned int LEFT_LINE_TRACKER_LIGHT      = 2;
    const unsigned int CENTER_LINE_TRACKER_LIGHT    = 3;
    const unsigned int RIGHT_LINE_TRACKER_LIGHT     = 4;

    //==========================================================================================
    // PWM Output Ports
    //==========================================================================================


    //==========================================================================================
    // PNEUMATIC SOLENOID Ports
    //==========================================================================================

#endif /* SRC_ROBOTMAP_H_ */
