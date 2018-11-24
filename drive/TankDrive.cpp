/*=============================================================================================
 * TankDrive.cpp
 *=============================================================================================
 *
 * File Description:
 *
 * This implements the IJoystickDrive interface to drive the robot using joysticks in a tank
 * drive mode.
 *
 * Thus, the left axis will control the left side of the robot and the right axis will
 * control the right side of the robot.  Turning is achieve by pushing the axis in opposite
 * directions (e.g. right stick forward and left stick backward will turn left).
 *=============================================================================================*/

#include <SmartDashboard/SmartDashboard.h>  // Smart Dashboard

// Team 302 includes
#include <drive/TankDrive.h>                // This class
#include <drive/IJoystickDrive.h>           // Interface being implemented
#include <drive/Chassis.h>                  // Class that controls the motors on the drive chassis
#include <driverInputs/OperatorInterface.h> // Controls creating singleton of the gamepads

//--------------------------------------------------------------------
// Method:      TankDrive <<Constructor>>
// Description: This method is called to create/initialize this class
//--------------------------------------------------------------------
TankDrive::TankDrive() : IJoystickDrive(),
                         m_chassis( Chassis::GetChassis() ),
                         m_oi( TeleopControl::GetInstance())
{
	m_oi->SetAxisProfile( TeleopControl::TANK_DRIVE_RIGHT_CONTROL, AXIS_CUBIC );
	m_oi->SetAxisProfile( TeleopControl::TANK_DRIVE_LEFT_CONTROL, AXIS_CUBIC );
    // Get the two axis that will be used for tank drive
    // Set their profile to be Cubed
	
	m_chassis->SetBrakeMode( false );
    // Set to Coast Mode

}

//--------------------------------------------------------------------
// Method:      DriveWithJoysticks
// Description: This method will be called during the periodic loop
//              to drive the robot.  It will interact with the joysticks
//              to drive in tank drive mode.
// Returns:     void
//--------------------------------------------------------------------
void TankDrive::DriveWithJoysticks() const
{
	m_chassis->SetBrakeMode( false );  // set to coast mode

	// Read the desired motor speeds
	float leftControl  = m_oi->GetAxisValue( TeleopControl::TANK_DRIVE_LEFT_CONTROL );
	float rightControl = m_oi->GetAxisValue( TeleopControl::TANK_DRIVE_RIGHT_CONTROL );

	SmartDashboard::PutNumber( "tank left ", leftControl );
	SmartDashboard::PutNumber( "tank right ", rightControl );
	
	m_chassis->Drive(leftControl, rightControl);
    // Set the motors
}

//--------------------------------------------------------------------
// Method:      GetIdentifier
// Description: This gets the name that identifies the drive mode..
// Returns:     const char*         identifier for the drive
//--------------------------------------------------------------------
const char* TankDrive::GetIdentifier() const
{
    return "Tank Drive";
}
