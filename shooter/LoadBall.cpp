/*=============================================================================================
 * LoadBall.cpp
 *=============================================================================================
 *
 * File Description:
 *
 * This controls loading a ball into the shooter.
 *=============================================================================================*/
#include <SmartDashboard/SmartDashboard.h>  // Smart Dashboard


// Team 302 includes
#include <shooter/Shooter.h>               	// Class the control the shooter motors
#include <shooter/LoadBall.h>               	// This class

#include <driverInputs/OperatorInterface.h>

//--------------------------------------------------------------------
// Method:      CycleLoader
// Description: This method will read the gamepad input and move run
//              loader motor until the sensor detects it is back in
//              load position
// Returns:     void
//--------------------------------------------------------------------
void LoadBall::CycleLoader()
{
	Shooter* shooter = Shooter::GetShooter();		// Get the shooter subsystem
	//  implement cases to cycle the load ball.  Run if ...
	//        1) Button pressed
	//		  2) Sensor not tripped indicating ball is in position
	//        Otherwise, stop the motor
	float speed = m_loaderSpeedStopped;
	TeleopControl* myOI = TeleopControl::GetInstance();
//	if ( ( myOI->GetRawButton(OperatorInterface::SHOOT_BUTTON) && shooter->GetShooterSpeed() > m_neededShooterSpeed ) ||
//	      !shooter->IsLoaderInPosition() )
	if ( myOI->IsButtonPressed(TeleopControl::SHOOT_BUTTON) || !shooter->IsLoaderInPosition() )
//	if ( myOI->GetRawButton(OperatorInterface::SHOOT_BUTTON)  )
	{
		speed = m_loaderSpeedRun;
	}
	else
	{
		speed = m_loaderSpeedStopped;
	}

	SmartDashboard::PutBoolean( "Loader in position ", shooter->IsLoaderInPosition() );
	SmartDashboard::PutBoolean( "Load Ball: shooter button ", myOI->IsButtonPressed(TeleopControl::SHOOT_BUTTON)  );
	SmartDashboard::PutNumber( "load Speed ", speed );
	SmartDashboard::PutNumber( "Shooter Speed returned ", shooter->GetShooterSpeed());
	shooter->SetBallLoadMotor( speed );
}


