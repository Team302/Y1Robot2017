/*
 * TestDragonPad.cpp
 *
 */

#include <test/TestDragonXbox.h>
#include <driverInputs/DragonXbox.h>
#include <SmartDashboard/SmartDashboard.h>

using namespace frc;



//----------------------------------------------------------------------------------
// Method:      GetInstance
// Description: If there isn't an instance of desired this class, create it.
//              Otherwise, hand out the single instance.
// Returns:     TestDragonStick*    TestDragonStick singleton
//----------------------------------------------------------------------------------
TestDragonXbox* TestDragonXbox::m_instance = nullptr;//Init the instance to nullptr
TestDragonXbox* TestDragonXbox::GetInstance()
{
    if (TestDragonXbox::m_instance == nullptr)
    {
        TestDragonXbox::m_instance = new TestDragonXbox();
    }
    return TestDragonXbox::m_instance;
}

//-----------------------------------------------------------------------
// Method:      Init
// Description: Initializes the DragonXbox for the test.   This should
//              be called from the appropriate Init method in Robot.cpp
//
//              Note: all tests are described with their enum and have a
//              deadband eliminated.
// Returns:     void
//-----------------------------------------------------------------------
void TestDragonXbox::Init
(
        DRAGONXBOX_TEST_SCENARIO    type    // <I> - test to run
)
{
    DragonXbox* xbox = DragonXbox::GetInstance();

    AXIS_SENSITIVITY_CURVE curve = AXIS_LINEAR;
    float                  scale = 1.0;

    switch ( type )
    {
        case LINEAR_FULL_SCALE:
            break;

        case LINEAR_HALF_SCALE:
            scale = 0.5;
            break;

        case CUBIC_FULL_SCALE:
            curve = AXIS_CUBIC;
            break;

        case CUBIC_HALF_SCALE:
            curve = AXIS_CUBIC;
            scale = 0.5;
            break;

        default:
            break;

    }

    xbox->SetAxisProfile( X_AXIS_LEFT_JOYSTICK, curve );
    xbox->SetAxisScale( X_AXIS_LEFT_JOYSTICK, scale );

    xbox->SetAxisProfile( Y_AXIS_LEFT_JOYSTICK, curve );
    xbox->SetAxisScale( Y_AXIS_LEFT_JOYSTICK, scale );

    xbox->SetAxisProfile( LEFT_TRIGGER, curve );
    xbox->SetAxisScale( LEFT_TRIGGER, scale );

    xbox->SetAxisProfile( RIGHT_TRIGGER, curve );
    xbox->SetAxisScale( RIGHT_TRIGGER, scale );

    xbox->SetAxisProfile( X_AXIS_RIGHT_JOYSTICK, curve );
    xbox->SetAxisScale( X_AXIS_RIGHT_JOYSTICK, scale );

    xbox->SetAxisProfile( Y_AXIS_RIGHT_JOYSTICK, curve );
    xbox->SetAxisScale( Y_AXIS_RIGHT_JOYSTICK, scale );
}



//-----------------------------------------------------------------------
// Method:      Periodic
// Description: This displays the joystick axis values and button status
//              to the dashboard
// Returns:     void
//-----------------------------------------------------------------------
void TestDragonXbox::Periodic()
{
    DragonXbox* xbox = DragonXbox::GetInstance();

    SmartDashboard::PutNumber( "Left Joystick - X-Axis: ", xbox->GetAxisValue( X_AXIS_LEFT_JOYSTICK ) );
    SmartDashboard::PutNumber( "Left Joystick - Y-Axis: ", xbox->GetAxisValue( Y_AXIS_LEFT_JOYSTICK ) );

    SmartDashboard::PutNumber( "Left Joystick - Trigger: ", xbox->GetAxisValue( LEFT_TRIGGER ) );


    SmartDashboard::PutNumber( "Right Joystick - X-Axis: ", xbox->GetAxisValue( X_AXIS_RIGHT_JOYSTICK ) );
    SmartDashboard::PutNumber( "Right Joystick - Y-Axis: ", xbox->GetAxisValue( Y_AXIS_RIGHT_JOYSTICK ) );

    SmartDashboard::PutNumber( "Right Joystick - Trigger: ", xbox->GetAxisValue( RIGHT_TRIGGER ) );

    SmartDashboard::PutBoolean( "A Button: ", xbox->IsButtonPressed( A_BUTTON ) );
    SmartDashboard::PutBoolean( "B Button: ", xbox->IsButtonPressed( B_BUTTON ) );
    SmartDashboard::PutBoolean( "X Button: ", xbox->IsButtonPressed( X_BUTTON ) );
    SmartDashboard::PutBoolean( "Y Button: ", xbox->IsButtonPressed( Y_BUTTON ) );
    SmartDashboard::PutBoolean( "LEFT_BUMPER: ", xbox->IsButtonPressed( LEFT_BUMPER ) );
    SmartDashboard::PutBoolean( "RIGHT_BUMPER: ", xbox->IsButtonPressed( RIGHT_BUMPER ) );
    SmartDashboard::PutBoolean( "BACK_BUTTON: ", xbox->IsButtonPressed( BACK_BUTTON ) );
    SmartDashboard::PutBoolean( "START_BUTTON: ", xbox->IsButtonPressed( START_BUTTON ) );
    SmartDashboard::PutBoolean( "PRESS_LEFT_STICK: ", xbox->IsButtonPressed( PRESS_LEFT_STICK ) );
    SmartDashboard::PutBoolean( "PRESS_RIGHT_STICK: ", xbox->IsButtonPressed( PRESS_RIGHT_STICK ) );
    SmartDashboard::PutBoolean( "LEFT_TRIGGER_PRESSED: ", xbox->IsButtonPressed( LEFT_TRIGGER_PRESSED ) );
    SmartDashboard::PutBoolean( "RIGHT_TRIGGER_PRESSED: ", xbox->IsButtonPressed( RIGHT_TRIGGER_PRESSED ) );
}

