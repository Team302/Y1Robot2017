/*=============================================================================================
 * Shooter.cpp
 *=============================================================================================
 *
 * File Description:
 *
 * This file interacts with the hardware (motors and sensors) used to shoot the ping pong balls
 *=============================================================================================*/

// WPILib includes
#include <CANTalon.h>                       // Motor Controllers
#include <DigitalInput.h>                   // Prox Switch
#include <AnalogInput.h>					// Angle Sensor
#include <SmartDashboard/SmartDashboard.h>  // Smart Dashboard

// Team 302 includes
#include <shooter/Shooter.h>           	// This class
#include <utils/LimitValue.h>                   // Contains utility to force values within the valid range
#include <RobotMap.h>                       	// Contains the CAN IDs and Digital IO

#include <cmath>        // std:abs


//----------------------------------------------------------------------------------
// Method:		GetShooter
// Description:	If there isn't an instance, create it.
//				Otherwise, hand out the single instance.
// Returns:		Shooter*	This class
//----------------------------------------------------------------------------------
Shooter* Shooter::m_instance = nullptr;
Shooter* Shooter::GetShooter()
{
	if ( Shooter::m_instance == nullptr )
	{
		Shooter::m_instance = new Shooter();
	}
	return Shooter::m_instance;
}


//----------------------------------------------------------------------------------
// Method:      Shooter <<Constructor>>
// Description: Create the motor controllers and set whether they are inverted or not.
//----------------------------------------------------------------------------------


Shooter::Shooter() :   m_shooterWheel( new CANTalon( SHOOTER_WHEEL_MOTOR ) ),
                       m_shooterLoader( new CANTalon( SHOOTER_LOAD_MOTOR ) ),
                       m_shooterAlign( new CANTalon( SHOOTER_ALIGN_MOTOR ) ),
					   m_shooterAngleSensor( new AnalogInput( SHOOTER_ANGLE_SENSOR ) ) ,
					   m_initialLoadPos ( m_shooterLoader->GetEncPosition() )

{

	// Shooter Wheels set whether:
	//	motors are inverted or not
	//	sensors are inverted or not
	//  talons are in brake or coast mode
    m_shooterWheel->SetInverted(IS_SHOOTER_WHEEL_MOTOR_INVERTED);
    m_shooterWheel->SetSensorDirection(IS_SHOOTER_WHEEL_SENSOR_INVERTED);
	m_shooterWheel->ConfigNeutralMode(CANSpeedController::kNeutralMode_Coast );
	m_shooterWheel->SetFeedbackDevice( CANTalon::CtreMagEncoder_Relative );
	m_shooterWheel->ConfigEncoderCodesPerRev( m_shooterWheelsCountsPerRev );

	// Loader Plunger set whether:
	//	motors are inverted or not
	//	sensors are inverted or not
	//  talons are in brake or coast mode
    m_shooterLoader->SetInverted(IS_SHOOTER_LOAD_MOTOR_INVERTED);
    m_shooterLoader->SetSensorDirection(IS_SHOOTER_LOAD_SENSOR_INVERTED);
	m_shooterLoader->ConfigNeutralMode(CANSpeedController::kNeutralMode_Brake );
	m_shooterLoader->SetFeedbackDevice( CANTalon::CtreMagEncoder_Relative );
	m_shooterLoader->ConfigEncoderCodesPerRev( m_loadCountsPerRev );
	m_initialLoadPos = m_shooterLoader->GetEncPosition();

//	m_shooterLoader->Reset();

	// Shooter Alignment set whether:
	//	motors are inverted or not
	//	sensors are inverted or not
	//  talons are in brake or coast mode
    m_shooterAlign->SetInverted(IS_SHOOTER_ALIGN_MOTOR_INVERTED);
    m_shooterAlign->SetSensorDirection(IS_SHOOTER_ALIGN_SENSOR_INVERTED);
	m_shooterAlign->ConfigNeutralMode(CANSpeedController::kNeutralMode_Brake );

}


//----------------------------------------------------------------------------------
// Method:      SetShooterSpeed
// Description: This will set the motor speed for the shooter wheel.
//              If a value is specified that is outside the range, the value
//              used will be the closest bounding value (e.g. if 2.0 is passed in and
//              the range is -1.0 to 1.0, 1.0 will be used.
// Returns:     void
//----------------------------------------------------------------------------------
void Shooter::SetShooterSpeed
(
    const float speed   // <I> - Speed for the shooter wheel (range -1.0 to 1.0)
) const
{
	// TODO:: make sure input is in range and set the motor
	float limitedSpeed = LimitValue::ForceInRange( speed, -1.0, 1.0 );
	m_shooterWheel->Set( limitedSpeed );
}


//----------------------------------------------------------------------------------
// Method:      GetShooterSpeed
// Description: This will get the motor speed for the shooter wheel.
// Returns:     float		speed
//----------------------------------------------------------------------------------
float Shooter::GetShooterSpeed() const
{
	float speed = m_maxShooterSpeed;
	if ( m_shooterWheel->IsSensorPresent( CANTalon::CtreMagEncoder_Relative ) == CANTalon::FeedbackStatusPresent  )
	{
		speed = m_shooterWheel->GetEncVel();  // need to convert value
	}
	return speed;
}

//----------------------------------------------------------------------------------
// Method:      SetBallLoadMotor
// Description: This will run the loader motor.
// Returns:     void
//----------------------------------------------------------------------------------
void Shooter::SetBallLoadMotor
(
    const float speed   // <I> - Speed for the shooter ball loader (range -1.0 to 1.0)
) const
{
	// TODO:: make sure input is in range and set the motor
	float limitedSpeed = LimitValue::ForceInRange( speed, -1.0, 1.0 );

	SmartDashboard::PutNumber( "SetBallLoadMotor: load Speed ", speed );
	SmartDashboard::PutNumber( "SetBallLoadMotor: load Speed2 ", limitedSpeed );

	m_shooterLoader->Set( limitedSpeed );
	
}

//----------------------------------------------------------------------------------
// Method:      IsLoaderInPosition
// Description: This will return whether the loader is in position or not.
// Returns:     bool        true  = in position
//                          false = not in position
//----------------------------------------------------------------------------------
bool Shooter::IsLoaderInPosition() const
{
	int pos = m_shooterLoader->GetEncPosition() - m_initialLoadPos;
	int remainder = pos % m_loadCountsPerRev;
//	bool inPosition = ( std::abs( remainder - m_loadInit ) < m_loadTol );
//	bool inPosition = ( remainder > m_loadInit );
//	bool inPosition = ( remainder > m_loadInitLower && remainder < m_loadInitUpper );
	bool inPosition = ( remainder > m_loadInitUpper || remainder < m_loadInitLower );
	SmartDashboard::PutNumber( "m_initialLoadPos ", m_initialLoadPos );
	SmartDashboard::PutNumber( "pos ", pos );
	SmartDashboard::PutNumber( "remainder ", remainder );
//	inPosition = false;
	return inPosition;
}

//----------------------------------------------------------------------------------
// Method:      SetAimMotor
// Description: This will run the aim motor (positive values move it up and negative
//				values move it down).
// Returns:     void
//----------------------------------------------------------------------------------
void Shooter::SetAimMotor
(
    const float speed   // <I> - Speed for the aim motor (range -1.0 to 1.0)
) const
{
	float limitedSpeed = LimitValue::ForceInRange( speed, -1.0, 1.0 );
	m_shooterAlign->Set( limitedSpeed );
}

//----------------------------------------------------------------------------------
// Method:      IsAtHighestAngle
// Description: This will return whether the shooter is at the highest angle.
// Returns:     bool        true  = at the highest position
//                          false = not at the highest position
//----------------------------------------------------------------------------------
bool Shooter::IsAtHighestAngle() const
{
	float angle = GetShooterAngle();
	return (angle >= m_highestAngle );
//	return false;
}

//----------------------------------------------------------------------------------
// Method:      IsAtLowestAngle
// Description: This will return whether the shooter is at the lowest angle.
// Returns:     bool        true  = at the lowest position
//                          false = not at the lowest position
//----------------------------------------------------------------------------------
bool Shooter::IsAtLowestAngle() const
{
	float angle = GetShooterAngle();
	return ( angle <= m_lowestAngle );
//	return false;
}

//----------------------------------------------------------------------------------
// Method:      GetShooterAngle
// Description: This will read the angle sensor and convert the voltage into
//				an angle value.
// Returns:     float		the angle of the shooter.
//----------------------------------------------------------------------------------
float Shooter::GetShooterAngle() const
{
	double voltage = m_shooterAngleSensor->GetVoltage();
	float offset = voltage - m_minAngleVoltage;
	float voltageRange = m_maxAngleVoltage - m_minAngleVoltage;
	float angleRange = m_maxAngleSensor - m_minAngleSensor;

	float angle = (( offset / voltageRange ) * angleRange);

	SmartDashboard::PutNumber( "voltage ", voltage );
	SmartDashboard::PutNumber( "offset ", offset );
	SmartDashboard::PutNumber( "voltage range ", voltageRange );
	SmartDashboard::PutNumber( "angle range ", angleRange );
	SmartDashboard::PutNumber( "angle ", angle );

	return angle;
}


//----------------------------------------------------------------------------------
// Method:      ~Shooter <<Destructor>>
// Description: Delete the motor controllers
//----------------------------------------------------------------------------------
Shooter::~Shooter()
{
	
	// TODO:: clean up object
    delete m_shooterWheel;
	delete m_shooterLoader;
	delete m_shooterAlign;
	
}

