/*=============================================================================================
 * ArcadeDrive.cpp
 *=============================================================================================
 *
 * File Description:
 *
 * This implements the IJoystickDrive interface to drive the robot using joysticks in a arcade
 * drive mode.
 *
 * Thus, the left axis will control speed (throttle) and the right axis will control direction
 * (steering). The speed control (throttle) will get a cubic profile while the steer control
 * will be direct (linear).
 *
 * Then, the left and right speeds are set by using the arcade drive equations where
 * the left side adds the steer value to the throttle value and the right side
 * subtracts the steer value from the trottle.
 *=============================================================================================*/

#include <SmartDashboard/SmartDashboard.h>  // Smart Dashboard

// Team 302 includes
#include <drive/ArcadeDrive.h>              // This class
#include <drive/IJoystickDrive.h>           // Interface being implemented
#include <drive/Chassis.h>                  // Class that controls the motors on the drive chassis
#include <driverInputs/DragonXbox.h>        // Controls creating singleton of the gamepads
#include <driverInputs/OperatorInterface.h> // Controls creating singleton of the gamepads
#include <utils/LimitValue.h>

//--------------------------------------------------------------------
// Method:      ArcadeDrive <<constructor>>
// Description: This method creates and initializes the objects
//--------------------------------------------------------------------
ArcadeDrive::ArcadeDrive() : IJoystickDrive(),
                             m_chassis( Chassis::GetChassis() ),
                             m_oi( TeleopControl::GetInstance())
{
    // Set the profile to cubic on the joysticks being used
    m_oi->SetAxisProfile( TeleopControl::ARCADE_DRIVE_THROTTLE, AXIS_CUBIC );
	m_oi->SetAxisProfile( TeleopControl::ARCADE_DRIVE_STEER, AXIS_CUBIC );
    // set the scale facgtor for steering to be between -0.5 and 0.5
	m_oi->SetAxisScaleFactor( TeleopControl::ARCADE_DRIVE_STEER, 0.85 );

    // Set to Coast Mode
    m_chassis->SetBrakeMode( false );
}

//--------------------------------------------------------------------
// Method:      DriveWithJoysticks
// Description: This method will be called during the periodic loop
//              to drive the robot.  It will interact with the joysticks
//              to drive in arcade drive mode.
// Returns:     void
//--------------------------------------------------------------------
void ArcadeDrive::DriveWithJoysticks() const
{
	m_chassis->SetBrakeMode( false );  // set to coast mode

	float getLeftSpeed = m_oi->GetAxisValue(TeleopControl::ARCADE_DRIVE_THROTTLE);
	float getRightSpeed = m_oi->GetAxisValue(TeleopControl::ARCADE_DRIVE_STEER);
	// Read the desired motor speeds
	
	float leftSpeed = getLeftSpeed + getRightSpeed;
	float rightSpeed = getLeftSpeed - getRightSpeed;
    // Convert to using arcade equations to give motor speeds on both sides of the robot.
	
	m_chassis->Drive(leftSpeed, rightSpeed);
    // Set the motors
}

//--------------------------------------------------------------------
// Method:      GetIdentifier
// Description: This gets the name that identifies the drive mode..
// Returns:     const char*         identifier for the drive
//--------------------------------------------------------------------
const char* ArcadeDrive::GetIdentifier() const
{
    return "Arcade Drive";
}
