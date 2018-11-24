/*
 * TestChassis.cpp
 */

#include <test/TestChassis.h>
#include <SmartDashboard/SmartDashboard.h>

using namespace frc;


TestChassis* TestChassis::m_instance = nullptr;//Init the instance to nullptr

//----------------------------------------------------------------------------------
// Method:      GetInstance
// Description: If there isn't an instance of desired this class, create it.
//              Otherwise, hand out the single instance.
// Returns:     TestChassis*    singleton
//----------------------------------------------------------------------------------
TestChassis* TestChassis::GetInstance()
{
    if (TestChassis::m_instance == nullptr)
    {
        TestChassis::m_instance = new TestChassis();
    }
    return TestChassis::m_instance;
}

TestChassis::TestChassis() : m_leftSpeed( m_stoppedSpeed ),
							 m_rightSpeed( m_stoppedSpeed ),
							 m_time( 0.0 )
{
}
//-----------------------------------------------------------------------------------
// Method:          Init
// Description:     Setup the test
// Returns:         void
//-----------------------------------------------------------------------------------
void TestChassis::Init
(
    TestChassis::CHASSIS_TEST_CASE_ID   test    // <I> - test case identifier
)
{
    Chassis* chassis = Chassis::GetChassis();

    // Everytime we start a test
    m_time = 0.0;                           // reset the time
    m_leftSpeed  = m_stoppedSpeed;          // Stop the left motor
    m_rightSpeed = m_stoppedSpeed;          // Stop the right motor
    switch ( test )
    {
        case DRIVE_FORWARD_COAST:
            chassis->SetBrakeMode( false );
            m_leftSpeed  = m_forwardSpeed;
            m_rightSpeed = m_forwardSpeed;
            break;

        case DRIVE_BACKWARD_COAST:
            chassis->SetBrakeMode( false );
            m_leftSpeed  = m_backwardSpeed;
            m_rightSpeed = m_backwardSpeed;
            break;

        case TURN_RIGHT_COAST:
            chassis->SetBrakeMode( false );
            m_leftSpeed  = m_forwardSpeed;
            m_rightSpeed = m_backwardSpeed;
            break;

        case TURN_LEFT_COAST:
            chassis->SetBrakeMode( false );
            m_leftSpeed  = m_backwardSpeed;
            m_rightSpeed = m_forwardSpeed;
            break;

        case DRIVE_FORWARD_BRAKE:
            chassis->SetBrakeMode( true );
            m_leftSpeed  = m_forwardSpeed;
            m_rightSpeed = m_forwardSpeed;
            break;

        case DRIVE_BACKWARD_BRAKE:
            chassis->SetBrakeMode( true );
            m_leftSpeed  = m_backwardSpeed;
            m_rightSpeed = m_backwardSpeed;
            break;

        case TURN_RIGHT_BRAKE:
            chassis->SetBrakeMode( true );
            m_leftSpeed  = m_forwardSpeed;
            m_rightSpeed = m_backwardSpeed;
            break;

        case TURN_LEFT_BRAKE:
            chassis->SetBrakeMode( true );
            m_leftSpeed  = m_backwardSpeed;
            m_rightSpeed = m_forwardSpeed;
            break;
        case LINE_TRACKER_STATE:
            chassis->SetBrakeMode( false );
            m_leftSpeed  = m_forwardSpeed;
            m_rightSpeed = m_forwardSpeed;
            break;

        default:
            break;
    }
}


//-----------------------------------------------------------------------------------
// Method:          Periodic
// Description:     Run the test
// Returns:         void
//-----------------------------------------------------------------------------------
void TestChassis::Periodic()
{
    Chassis* chassis = Chassis::GetChassis();
    chassis->Drive( m_leftSpeed, m_rightSpeed );

//  SmartDashboard::PutNumber("left distance: ", m_chassis->GetLeftDistance());

    SmartDashboard::PutNumber("Line tracker: ", chassis->GetLineTrackerState());
    SmartDashboard::PutNumber("left speed: ", chassis->GetLeftSpeed());
    SmartDashboard::PutNumber("right speed: ", chassis->GetRightSpeed());

    m_time += m_timeIncr;

    if ( m_time > m_segmentTime )
    {
        Stop();
    }
}

//-----------------------------------------------------------------------------------
// Method:          Stop
// Description:     Stop the test
// Returns:         void
//-----------------------------------------------------------------------------------
void TestChassis::Stop()
{
    m_leftSpeed  = m_stoppedSpeed;
    m_rightSpeed = m_stoppedSpeed;
    Chassis* chassis = Chassis::GetChassis();
    chassis->Drive( m_leftSpeed, m_rightSpeed );
}

