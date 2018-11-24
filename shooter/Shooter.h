/*=============================================================================================
 * Shooter.h
 *=============================================================================================
 *
 * File Description:
 *
 * This file interacts with the hardware (motors and sensors) used to drive the robot.  It is a
 * Singleton.
 *=============================================================================================*/
#ifndef SRC_SHOOTER_SHOOTER_H_
#define SRC_SHOOTER_SHOOTER_H_

// WPILib includes
#include <CANTalon.h>
#include <DigitalInput.h>
#include <AnalogInput.h>

// Team 302 includes

class Shooter
{
public:
	//----------------------------------------------------------------------------------
	// Method:		GetShooter
	// Description:	If there isn't an instance, create it.
	//				Otherwise, hand out the single instance.
	// Returns:		Shooter*	This class
	//----------------------------------------------------------------------------------
	static Shooter* GetShooter();

    //----------------------------------------------------------------------------------
    // Method:      SetShooterSpeed
    // Description: This will set the motor speed for the shooter wheel.
    //              If a value is specified that is outside the range, the value
    //              used will be the closest bounding value (e.g. if 2.0 is passed in and
    //              the range is -1.0 to 1.0, 1.0 will be used.
    // Returns:     void
    //----------------------------------------------------------------------------------
    void SetShooterSpeed
    (
        const float speed   // <I> - Speed for the shooter wheel (range -1.0 to 1.0)
    ) const;

    //----------------------------------------------------------------------------------
    // Method:      GetShooterSpeed
    // Description: This will get the motor speed for the shooter wheel.
    // Returns:     float		speed
    //----------------------------------------------------------------------------------
    float GetShooterSpeed() const;


    //----------------------------------------------------------------------------------
    // Method:      SetBallLoadMotor
    // Description: This will run the loader motor.
    // Returns:     void
    //----------------------------------------------------------------------------------
    void SetBallLoadMotor
    (
        const float speed   // <I> - Speed for the shooter ball loader (range -1.0 to 1.0)
    ) const;

    //----------------------------------------------------------------------------------
    // Method:      IsLoaderInPosition
    // Description: This will return whether the ball loader is in position or not.
    // Returns:     bool        true  = in postion
    //                          false = not in position
    //----------------------------------------------------------------------------------
    bool IsLoaderInPosition() const;

    //----------------------------------------------------------------------------------
    // Method:      SetAimMotor
    // Description: This will run the aim motor (positive values move it up and negative
    //				values move it down).
    // Returns:     void
    //----------------------------------------------------------------------------------
    void SetAimMotor
    (
        const float speed   // <I> - Speed for the aim motor (range -1.0 to 1.0)
    ) const;


    //----------------------------------------------------------------------------------
    // Method:      IsAtHighestAngle
    // Description: This will return whether the shooter is at the highest angle.
    // Returns:     bool        true  = at the highest position
    //                          false = not at the highest position
    //----------------------------------------------------------------------------------
    bool IsAtHighestAngle() const;

    //----------------------------------------------------------------------------------
    // Method:      IsAtLowestAngle
    // Description: This will return whether the shooter is at the lowest angle.
    // Returns:     bool        true  = at the lowest position
    //                          false = not at the lowest position
    //----------------------------------------------------------------------------------
    bool IsAtLowestAngle() const;


private:


    //----------------------------------------------------------------------------------
    // Method:      GetShooterAngle
    // Description: This will read the angle sensor and convert the voltage into
    //				an angle value.
    // Returns:     float		the angle of the shooter.
    //----------------------------------------------------------------------------------
    float GetShooterAngle() const;

    //----------------------------------------------------------------------------------
    // Method:      Shooter <<Constructor>>
    // Description: Create the motor controllers and set whether they are inverted or not.
    //----------------------------------------------------------------------------------
    Shooter();

    //----------------------------------------------------------------------------------
    // Method:      ~Shooter <<Destructor>>
    // Description: Delete the motor controll
    //----------------------------------------------------------------------------------
    virtual ~Shooter();

	static Shooter* 			m_instance;		// this singleton

    // Drive Motors
    CANTalon*           		m_shooterWheel;
    CANTalon*           		m_shooterLoader;
    CANTalon*           		m_shooterAlign;

//    DigitalInput*       		m_loaderPosition;
    AnalogInput*        		m_shooterAngleSensor;

    int							m_initialLoadPos;

    const int    				m_shooterWheelsCountsPerRev = 1024;
    const float					m_maxShooterSpeed = 5000.0;

    const int   				m_loadCountsPerRev = 2000;
//    const int					m_loadInit = 500;
    const int					m_loadInitUpper = 1900;
    const int					m_loadInitLower = 50;
    const int					m_loadTol = 100;

    const float					m_maxAngleSensor = 180.0;
    const float					m_maxAngleVoltage = 4.8;

    const float					m_minAngleSensor = 0.0;
    const float					m_minAngleVoltage = 0.2;

    const float 				m_lowestAngle = 65.0;
    const float         		m_highestAngle = 170.0;
};

#endif /* SRC_SHOOTER_SHOOTER_H_ */
