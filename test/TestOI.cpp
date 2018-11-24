/*
 * TestOI.cpp
 *
 */

#include <test/TestOI.h>
#include <driverInputs/OperatorInterface.h>
#include <SmartDashboard/SmartDashboard.h>
#include <vector>
#include <string>

using namespace frc;


//----------------------------------------------------------------------------------
// Method:      GetInstance
// Description: If there isn't an instance of desired this class, create it.
//              Otherwise, hand out the single instance.
// Returns:     TestDragonXbox*    TestDragonStick singleton
//----------------------------------------------------------------------------------
TestTelopControl* TestTelopControl::m_instance = nullptr;//Init the instance to nullptr
TestTelopControl* TestTelopControl::GetInstance()
{
    if (TestTelopControl::m_instance == nullptr)
    {
    	TestTelopControl::m_instance = new TestTelopControl();
    }
    return TestTelopControl::m_instance;
}

TestTelopControl::TestTelopControl() : m_test( TeleopControl::MAX_FUNCTIONS )
{

}


//-----------------------------------------------------------------------
// Method:      Init
// Description: Initializes the OI for the test.   This should
//              be called from the appropriate Init method in Robot.cpp
//
//              Note: all tests are described with their enum and have a
//              deadband eliminated.
// Returns:     void
//-----------------------------------------------------------------------
void TestTelopControl::Init
(
        OI_TEST_SCENARIO    type    // <I> - test to run
)
{
    AXIS_SENSITIVITY_CURVE 					curve = AXIS_LINEAR;
    float                      				scale = 1.0;

    switch ( type )
    {
		case TANK_DRIVE_LEFT_LINEAR:
			m_test = TeleopControl::TANK_DRIVE_LEFT_CONTROL;
			break;

		case TANK_DRIVE_RIGHT_LINEAR:
			m_test = TeleopControl::TANK_DRIVE_RIGHT_CONTROL;
			break;

		case TANK_DRIVE_LEFT_CUBIC:
			m_test = TeleopControl::TANK_DRIVE_LEFT_CONTROL;
			curve = AXIS_CUBIC;
			break;

		case TANK_DRIVE_RIGHT_CUBIC:
			m_test = TeleopControl::TANK_DRIVE_RIGHT_CONTROL;
			curve = AXIS_CUBIC;
			break;

		case SCALED_TANK_DRIVE_LEFT_LINEAR:
			m_test = TeleopControl::TANK_DRIVE_LEFT_CONTROL;
			scale = 0.5;
			break;

		case SCALED_TANK_DRIVE_RIGHT_LINEAR:
			m_test = TeleopControl::TANK_DRIVE_RIGHT_CONTROL;
			scale = 0.5;
			break;

		case SCALED_TANK_DRIVE_LEFT_CUBIC:
			m_test = TeleopControl::TANK_DRIVE_LEFT_CONTROL;
			scale = 0.5;
			curve = AXIS_CUBIC;
			break;

		case SCALED_TANK_DRIVE_RIGHT_CUBIC:
			m_test = TeleopControl::TANK_DRIVE_RIGHT_CONTROL;
			scale = 0.5;
			curve = AXIS_CUBIC;
			break;

		case ARCADE_DRIVE_THROTTLE_LINEAR:
			m_test = TeleopControl::ARCADE_DRIVE_THROTTLE;
			break;

		case ARCADE_DRIVE_STEER_LINEAR:
			m_test = TeleopControl::ARCADE_DRIVE_STEER;
			break;

		case ARCADE_DRIVE_THROTTLE_CUBIC:
			m_test = TeleopControl::ARCADE_DRIVE_THROTTLE;
			curve = AXIS_CUBIC;
			break;


		case ARCADE_DRIVE_STEER_CUBIC:
			m_test = TeleopControl::ARCADE_DRIVE_STEER;
			curve = AXIS_CUBIC;
			break;


		case SCALED_ARCADE_DRIVE_THROTTLE_LINEAR:
			m_test = TeleopControl::ARCADE_DRIVE_THROTTLE;
			scale = 0.5;
			break;


		case SCALED_ARCADE_DRIVE_STEER_LINEAR:
			m_test = TeleopControl::ARCADE_DRIVE_STEER;
			scale = 0.5;
			break;

		case SCALED_ARCADE_DRIVE_THROTTLE_CUBIC:
			m_test = TeleopControl::ARCADE_DRIVE_THROTTLE;
			curve = AXIS_CUBIC;
			scale = 0.5;
			break;

		case SCALED_ARCADE_DRIVE_STEER_CUBIC:
			m_test = TeleopControl::ARCADE_DRIVE_STEER;
			curve = AXIS_CUBIC;
			scale = 0.5;
			break;

    // TODO:  Add other actions

        default:
            break;

    }

    TeleopControl* myOI = TeleopControl::GetInstance();
    myOI->SetAxisScaleFactor( m_test, scale );
    myOI->SetAxisProfile( m_test, curve );
}

//-----------------------------------------------------------------------
// Method:      Periodic
// Description: This displays the joystick axis values and button states
//              to the dashboard
// Returns:     void
//-----------------------------------------------------------------------
void TestTelopControl::Periodic()
{

    TeleopControl* myOI = TeleopControl::GetInstance();
    std::string label = "OI function Axis Test " + std::to_string( m_test );
    frc::SmartDashboard::PutNumber( label, myOI->GetAxisValue( m_test ) );

    std::string label2 = "OI function Button Test " + std::to_string( m_test );
    frc::SmartDashboard::PutBoolean( label2, myOI->IsButtonPressed( m_test ) );
}


