/*=============================================================================================
 * FollowLine.cpp
 *=============================================================================================
 *
 * File Description:
 *
 * This class will follow a white line surrounded by black lines.
 *=============================================================================================*/

#include <DigitalOutput.h>
#include <SmartDashboard/SmartDashboard.h>  // Smart Dashboard

// Team 302 includes
#include <drive/FollowLine.h>             // This class
#include <drive/Chassis.h>                // Class the control the drive motors
#include <drive/LineTracker.h>
#include <RobotMap.h>

//--------------------------------------------------------------------
// Method:      FollowLine <<constructor>>
// Description: This method creates and initializes the objects
//--------------------------------------------------------------------
FollowLine::FollowLine() : m_chassis( Chassis::GetChassis() ),
                           m_previousState( FollowLine::STOPPED )

{
	Chassis::GetChassis()->SetBrakeMode( true );  // set to brake mode, so we don't continue moving
}

//--------------------------------------------------------------------
// Method:      Drive
// Description: This method will follow a line.
// Returns:     void
//--------------------------------------------------------------------
void FollowLine::Drive()
{
	// MRW - look at the signature in Chassis.h for GetLineTrackerState
	//      LINE_TRACKER_STATE GetLineTrackerState();
	//      so, this line should be something like:
	//   LINE_TRACKER_STATE state = Chassis::GetChassis()->GetLineTrackerState();
	//   switch ( state )
	//   {
	//		  case ALL_BLACK:
	//			  ....
	//            break;
	//       ...
	
	
	Chassis::GetChassis()->SetBrakeMode( true );  // set to brake mode, so we don't continue moving

	LINE_TRACKER_STATE state = Chassis::GetChassis()->GetLineTrackerState();// TODO:: call the chassis to get the GetLineTrackerState
	SmartDashboard::PutNumber( "state ", state );
	switch ( state )
	{
		case ALL_BLACK:
		    Stop();
		    DriveStraightBack();
			break;
		case BLACK_BLACK_WHITE:
			DriveSharpRight();
			break;
		case BLACK_WHITE_BLACK:
		    DriveStraight();
		    break;
		case BLACK_WHITE_WHITE:
		    DriveSlightLeft();
			break;
		case WHITE_BLACK_BLACK:
		    DriveSharpLeft();
			break;
		case WHITE_BLACK_WHITE:
		    DriveStraightBack();
			break;
		case WHITE_WHITE_BLACK:
		    DriveSlightRight();
			break;
		case ALL_WHITE:
		    DriveStraight();
			break;
		default:
			// MRW everything is case sensitive
		    //stop();
			SmartDashboard::PutNumber( "Lost ", state );
		    Stop();
		    break;
		    
			
		    
	}
	// TODO:: based on its state, call the appropriate method (switch-case works nicely)
}


// MRW - did you forget to save the FollowLine.h, I don't see the variables you are using below defined in this file ...

//--------------------------------------------------------------------
// Method:      DriveStraight
// Description: This method will drive straight
// Returns:     void
//--------------------------------------------------------------------
void FollowLine::DriveStraight()
{
	m_chassis->Drive(m_drive_straight_left,m_drive_straight_right);// TODO:: call the chassis to make the robot drive straight
}

//--------------------------------------------------------------------
// Method:      DriveSlightLeft
// Description: This method will drive slightly to the left
// Returns:     void
//--------------------------------------------------------------------
void FollowLine::DriveSlightLeft()
{
	m_chassis->Drive(m_drive_slight_left_left,m_drive_slight_left_right);// TODO:: call the chassis to make the robot drive turn slightly left
}

//--------------------------------------------------------------------
// Method:      DriveSharpLeft
// Description: This method will drive Hardly to the left 
// Returns:     void
//--------------------------------------------------------------------
void FollowLine::DriveSharpLeft()
{
	// MRW remember the semi-colons
	m_chassis->Drive(m_drive_sharp_left_left,m_drive_sharp_left_right);// TODO:: call the chassis to make the robot drive turn sharp left
}

//--------------------------------------------------------------------
// Method:      DriveSlightRight
// Description: This method will drive slightly to the right
// Returns:     void
//--------------------------------------------------------------------
void FollowLine::DriveSlightRight()
{
	// MRW remember the semi-colons and these variables don't exist
	m_chassis->Drive(m_drive_slight_right_left,m_drive_slight_right_right);	// TODO:: call the chassis to make the robot drive turn slightly right
}

//--------------------------------------------------------------------
// Method:      DriveSharpRight
// Description: This method will drive Hardly to the right
// Returns:     void
//--------------------------------------------------------------------
void FollowLine::DriveSharpRight()
{
	// MRW remember the semi-colons
	m_chassis->Drive(m_drive_sharp_right_left,m_drive_sharp_right_right);// TODO:: call the chassis to make the robot drive turn sharply right
}

//--------------------------------------------------------------------
// Method:      Stop
// Description: This method will stop
// Returns:     void
//--------------------------------------------------------------------
void FollowLine::Stop()
{
	// MRW remember the semi-colons
	m_chassis->Drive( m_drive_lost_left,m_drive_lost_right);// TODO:: call the chassis to make the robot stop
}
void FollowLine::DriveStraightBack()
{
	// MRW remember the semi-colons
	m_chassis->Drive(m_drive_backingup_left,m_drive_backingup_right);// TODO:: call the chassis to make the robot drive backwards
}

