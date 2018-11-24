/*=============================================================================================
 * SpinShooterWheel.cpp
 *=============================================================================================
 *
 * File Description:
 *
 * This controls loading a ball into the shooter.
 *=============================================================================================*/

// Team 302 includes
#include <shooter/Shooter.h>               // Class the control the shooter motors
#include <shooter/SpinShooterWheel.h>       // This class
#include <driverInputs/OperatorInterface.h>

//--------------------------------------------------------------------
// Method:      SpinShooterWheel <<constructor>>
// Description: This method creates and initializes the objects
//--------------------------------------------------------------------
SpinShooterWheel::SpinShooterWheel()
{
}


//--------------------------------------------------------------------
// Method:      SpinWheels
// Description: This method will read the gamepad input and if the
//              SPIN_SHOOTER_WHEEL button is pressed, run the wheel.
//              If not, stop the wheel.
// Returns:     void
//--------------------------------------------------------------------
void SpinShooterWheel::SpinWheels() const
{
	float speed = m_shooterMotorSpeedStop;
	if (TeleopControl::GetInstance()->IsButtonPressed(TeleopControl::SHOOT_BUTTON) == true)
	{
		speed = m_shooterMotorSpeedGo;
	}
	Shooter::GetShooter()->SetShooterSpeed( speed );


}


