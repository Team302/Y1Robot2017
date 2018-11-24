/*=============================================================================================
 * Chassis.cpp
 *=============================================================================================
 *
 * File Description:
 *
 * This file interacts with the hardware (motors and sensors) used to drive the robot.
 *
 *=============================================================================================*/

// WPILib includes
#include <CANTalon.h>                           // Motor Controllers
#include <SmartDashboard/SmartDashboard.h>      // Smart Dashboard


// Team 302 includes
#include <RobotMap.h>                           // Contains the CAN IDs and Digital IO
#include <drive/Chassis.h>                      // This class
#include <utils/LimitValue.h>                   // Contains utility to force values within the valid range

using namespace frc;


//----------------------------------------------------------------------------------
// Method:      GetChassis
// Description: If there isn't an instance of chassis class, create it.
//              Otherwise, hand out the single instance.
// Returns:     Chassis*    Chassis subsystem
//----------------------------------------------------------------------------------
Chassis* Chassis::m_instance = nullptr;         // initialize the instance variable to nullptr
Chassis* Chassis::GetChassis()

{
    if ( Chassis::m_instance == nullptr )
    {
        Chassis::m_instance = new Chassis();
    }
    return Chassis::m_instance;
}

//----------------------------------------------------------------------------------
// Method:      Chassis <<Constructor>>
// Description: Create the motor controllers and set whether they are inverted or not.
//----------------------------------------------------------------------------------
Chassis::Chassis() :  m_leftMotor( new CANTalon( LEFT_DRIVE_MOTOR ) ) ,
                      m_rightMotor( new CANTalon( RIGHT_DRIVE_MOTOR ) ),
                      m_rightLineTracker( new LineTracker (RIGHT_LINE_TRACKER)),
                      m_centerLineTracker( new LineTracker (CENTER_LINE_TRACKER)),
                      m_leftLineTracker( new LineTracker ( LEFT_LINE_TRACKER)),
                      m_rightTrackerLED( new DigitalOutput (RIGHT_LINE_TRACKER_LIGHT)),
                      m_centerTrackerLED( new DigitalOutput (CENTER_LINE_TRACKER_LIGHT)),
                      m_leftTrackerLED( new DigitalOutput (LEFT_LINE_TRACKER_LIGHT))
{
    // Create each drive motor and set whether it is inverted or not
    m_leftMotor->SetInverted( IS_LEFT_DRIVE_MOTOR_INVERTED );
    m_leftMotor->SetSensorDirection( IS_LEFT_DRIVE_SENSOR_INVERTED );

    //:  initialize the motor and sensor inversion for the other drive motor
    m_rightMotor->SetInverted( IS_RIGHT_DRIVE_MOTOR_INVERTED );
    m_rightMotor->SetSensorDirection( IS_RIGHT_DRIVE_SENSOR_INVERTED );
}


//----------------------------------------------------------------------------------
// Method:      Drive
// Description: This will set the speeds for the left and right sides of the robot.
//              The range of speeds is between -1.0 (backwards full speed) and 1.0
//              (forward full speed).  If a value is specified that is outside the
//              range, the value used will be the closest bounding value (e.g. if 2.0
//              is passed in and the range is -1.0 to 1.0, 1.0 will be used.
// Returns:     void
//----------------------------------------------------------------------------------
void Chassis::Drive
(
    const float leftSpeed,  // <I> - Speed of the left side of the robot (range -1.0 to 1.0)
    const float rightSpeed  // <I> - Speed of the right side of the robot (range -1.0 to 1.0)
) const
{
    // MRW - looks good.   Remember blank lines are good; it makes the code easier to read.

    // ::  If a value is out of range get the amount out of range and then set the value to be
    //         within range (use LimitValue)
    float leftvalue= LimitValue::ForceInRange( leftSpeed, -1.0,1.0 );

    float leftvaluetrimmed= LimitValue::GetTrimmedValue( leftSpeed, -1.0,1.0 );

    float rightvalue= LimitValue::ForceInRange( rightSpeed, -1.0,1.0 );

    float rightvaluetrimmed= LimitValue::GetTrimmedValue( rightSpeed, -1.0,1.0 );



    //::  Set the motor speeds as follows:
    //          left motor speed = limited left motor speed - right speed amount out of range
    //          right motor speed = limited right motor speed - left speed amount out of range
    float leftmotorspeed = leftvalue - rightvaluetrimmed;

    float rightmotorspeed = rightvalue - leftvaluetrimmed;

    m_leftMotor->Set(leftmotorspeed);

    m_rightMotor->Set(rightmotorspeed);
}


//----------------------------------------------------------------------------------
// Method:      SetBrakeMode
// Description: This will set the drive motors to brake mode (true) or coast mode (false)
// Returns:     void
//----------------------------------------------------------------------------------
void Chassis::SetBrakeMode
(
        bool        useBrakeMode            // <I> - true  = use brake mode
) const                                     // <I> - false = use coast mode
{
    // update the talons with the appropriate brake mode setting.  Use either:
    //          CANSpeedController::kNeutralMode_Brake
    //          CANSpeedController::kNeutralMode_Coast
    if(useBrakeMode)
    {
        m_leftMotor->ConfigNeutralMode (CANSpeedController::kNeutralMode_Brake);
        m_rightMotor->ConfigNeutralMode (CANSpeedController::kNeutralMode_Brake);
    }
    else
    {
        m_leftMotor->ConfigNeutralMode (CANSpeedController::kNeutralMode_Coast);
        m_rightMotor->ConfigNeutralMode (CANSpeedController::kNeutralMode_Coast);
    }

}




//----------------------------------------------------------------------------------
// Method:      GetLineTrackerState
// Description: This will the colors detected by the line trackers
// Returns:     LINE_TRACKER_STATE          see enum definition for the left to right
//                                          sensor color values detected
//----------------------------------------------------------------------------------
LINE_TRACKER_STATE Chassis::GetLineTrackerState()
{
    LINE_TRACKER_STATE state = UNKNOWN_STATE;

    // : read each line tracker to determine if it is black or white, if the line tracker is white
    //       set its value equal to its position value (e.g. GetLeftLineTrackerPositionMultiplier)
    //       times 1 if it is white
    bool isLeftWhite = m_leftLineTracker-> IsWhite();

    int leftValue = ( isLeftWhite ) ? GetLeftLineTrackerPositionMultiplier() : 0;

    bool isCenterWhite = m_centerLineTracker-> IsWhite();

    int centerValue = ( isCenterWhite ) ? GetCenterLineTrackerPositionMultiplier() : 0;

    bool isRightWhite = m_rightLineTracker-> IsWhite();

    int rightValue = ( isRightWhite ) ? GetRightLineTrackerPositionMultiplier() : 0;


    SmartDashboard::PutBoolean( "left white ", isLeftWhite );
    SmartDashboard::PutBoolean( "center white ", isCenterWhite );
    SmartDashboard::PutBoolean( "right white ", isRightWhite );



    //bool isLeftWhite = m_leftLineTracker-> IsWhite();
    //int  leftValue = ( isLeftWhite ) ? GetLeftLineTrackerPositionMultiplier : 0;

    //:  set State based on calculated values (sum of the calculated left, center and
    //        right valuues)
    state = (LINE_TRACKER_STATE)(leftValue + centerValue + rightValue);


    return state;
}
//----------------------------------------------------------------------------------
// Method:      GetLeftSpeed
// Description: This will tell the left speed in in/s. Positive measurmets are forward and negative measurements are backward
// Returns:     float      speed of wheel in in/s
//----------------------------------------------------------------------------------
float Chassis::GetLeftSpeed() const
{
	float speed = 0.0;
    //double counts = m_leftMotor -> Get();
    return speed;

}
//----------------------------------------------------------------------------------
// Method:      GetRightSpeed
// Description: This will tell the right speed in in/s. Positive measurmets are forward and negative measurements are backward
// Returns:     float      speed of wheel in in/s
//----------------------------------------------------------------------------------
float Chassis::GetRightSpeed() const
{
	float speed = 0.0;
	return speed;
}
//----------------------------------------------------------------------------------
// Method:      GetDistanceToTarget
// Description: This will tell the distance to an object in ront of the robot
// Returns:     float      distance to target in in
//----------------------------------------------------------------------------------
float Chassis::GetDistanceToTarget() const
{
	float distance = 0.0;
	return distance;
}

//----------------------------------------------------------------------------------
// Method:      UpdateLineTrackerLights
// Description: This will update the line tracker lights
// Returns:     void
//----------------------------------------------------------------------------------
void Chassis::UpdateLineTrackerLights()
{
    //  Set the feedback based on the line tracker indicating it is white
    m_rightTrackerLED->Set(m_rightLineTracker->IsWhite());
    m_centerTrackerLED->Set( m_centerLineTracker->IsWhite());
    m_leftTrackerLED->Set(m_leftLineTracker->IsWhite());

}


//----------------------------------------------------------------------------------
// Method:      ~Chassis <<Destructor>>
// Description: Delete the motor controllers
//----------------------------------------------------------------------------------
Chassis::~Chassis()
{
    //clean up the attributes (need to delete objects that were constructed)
    delete m_leftMotor;
    delete m_rightMotor;
    delete m_rightLineTracker;
    delete m_centerLineTracker;
    delete m_leftLineTracker;
    delete m_rightTrackerLED;
    delete m_centerTrackerLED;
    delete m_leftTrackerLED;

}

