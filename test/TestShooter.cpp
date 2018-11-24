/*
 * TestShooter.cpp
 */

#include <test/TestShooter.h>
#include <SmartDashboard/SmartDashboard.h>

using namespace frc;


TestShooter* TestShooter::m_instance = nullptr;//Init the instance to nullptr

//----------------------------------------------------------------------------------
// Method:      GetInstance
// Description: If there isn't an instance of desired this class, create it.
//              Otherwise, hand out the single instance.
// Returns:     TestShooter*    singleton
//----------------------------------------------------------------------------------
TestShooter* TestShooter::GetInstance()
{
    if (TestShooter::m_instance == nullptr)
    {
        TestShooter::m_instance = new TestShooter();
    }
    return TestShooter::m_instance;
}


//-----------------------------------------------------------------------------------
// Method:          TestShooter
// Description:     constructor
//-----------------------------------------------------------------------------------
TestShooter::TestShooter()

{
    m_test        = MAX_SHOOTER_TESTS;
    m_time        = 0.0;                     // reset the time
    m_alignSpeed  = m_stoppedSpeed;          // Stop the alignment motor
    m_loadSpeed   = m_stoppedSpeed;          // Stop the loader motor
    m_spinSpeed   = m_stoppedSpeed;          // Stop the spin motor
}

//-----------------------------------------------------------------------------------
// Method:          Init
// Description:     Setup the test
// Returns:         void
//-----------------------------------------------------------------------------------
void TestShooter::Init
(
    TestShooter::SHOOTER_TEST_CASE_ID   test    // <I> - test case identifier
)
{
    // Everytime we start a test
    m_test        = test;
    m_time        = 0.0;                     // reset the time
    m_alignSpeed  = m_stoppedSpeed;          // Stop the alignment motor
    m_loadSpeed   = m_stoppedSpeed;          // Stop the loader motor
    m_spinSpeed   = m_stoppedSpeed;          // Stop the spin motor

    switch ( test )
    {
        case AIM_SHOOTER_UP:
            m_alignSpeed  = m_alignUpSpeed;
            break;

        case AIM_SHOOTER_DOWN:
            m_alignSpeed  = m_alignDownSpeed;
            break;

        case SPIN_SHOOTER_WHEELS:
            m_alignSpeed  = m_spinShooterSpeed;
            break;

        case LOAD_BALL:
            m_alignSpeed  = m_loadBallSpeed;
            break;

        case AUTO_FIRE:
            m_alignSpeed  = m_spinShooterSpeed;
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
void TestShooter::Periodic()
{
    Shooter* shooter = Shooter::GetShooter();
    shooter->SetShooterSpeed( m_spinSpeed );
    shooter->SetBallLoadMotor( m_loadSpeed );
    if ( shooter->IsAtHighestAngle() && m_test == AIM_SHOOTER_UP )
    {
        Stop();
    }
    else if ( shooter->IsAtLowestAngle() && m_test == AIM_SHOOTER_DOWN )
    {
        Stop();
    }
    shooter->SetAimMotor( m_alignSpeed );

    m_time += m_timeIncr;

    if ( m_time > m_segmentTime )
    {
        if ( m_test == AUTO_FIRE )
        {
            m_loadSpeed = m_loadBallSpeed;
            m_time = 0.0;
        }
        else
        {
            Stop();
        }
    }
}

//-----------------------------------------------------------------------------------
// Method:          Stop
// Description:     Stop the test
// Returns:         void
//-----------------------------------------------------------------------------------
void TestShooter::Stop()
{
    Shooter* shooter = Shooter::GetShooter();

    m_alignSpeed  = m_stoppedSpeed;          // Stop the alignment motor
    shooter->SetAimMotor( m_alignSpeed );

    m_loadSpeed   = m_stoppedSpeed;          // Stop the loader motor
    shooter->SetBallLoadMotor( m_loadSpeed );

    m_spinSpeed   = m_stoppedSpeed;          // Stop the spin motor
    shooter->SetShooterSpeed( m_spinSpeed );
}

