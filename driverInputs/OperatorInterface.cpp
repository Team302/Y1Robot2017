/*========================================================================================================
 * OperatorInterface.cpp
 *========================================================================================================
 *
 * File Description:
 *
 * This implements holds onto the instances of the game controllers used by driver and the co-pilot.
 *========================================================================================================*/

#include <SmartDashboard/SmartDashboard.h>  // Smart Dashboard

// Team 302 includes
#include <driverInputs/OperatorInterface.h>
#include <driverInputs/DragonXbox.h>
#include <RobotMap.h>


//----------------------------------------------------------------------------------
// Method:      GetInstance
// Description: If there isn't an instance of this class, it will create one.  The
//              single class instance will be returned.
// Returns:     OperatorInterface*  instance of this class
//----------------------------------------------------------------------------------
TeleopControl* TeleopControl::m_instance = nullptr; // initialize the instance variable to nullptr
TeleopControl* TeleopControl::GetInstance()
{
    if ( TeleopControl::m_instance == nullptr )
    {
        TeleopControl::m_instance = new TeleopControl();
    }
    return TeleopControl::m_instance;
}
//----------------------------------------------------------------------------------
// Method:      OperatorInterface <<constructor>>
// Description: This will construct and initialize the object.
//              It maps the functions to the buttons/axis.
//---------------------------------------------------------------------------------
TeleopControl::TeleopControl()
{
    // Initialize the items to not defined
    for ( int inx=0; inx<m_maxFunctions; ++inx )
    {
        m_axisIDs[inx]    = UNDEFINED_AXIS;
        m_buttonIDs[inx]  = UNDEFINED_BUTTON;
    }

    m_axisIDs[ TANK_DRIVE_LEFT_CONTROL ]    = Y_AXIS_LEFT_JOYSTICK;
    m_axisIDs[ TANK_DRIVE_RIGHT_CONTROL ]   = Y_AXIS_RIGHT_JOYSTICK;
//    m_axisIDs[ ARCADE_DRIVE_THROTTLE ]      = RIGHT_TRIGGER;
//    m_axisIDs[ ARCADE_DRIVE_STEER ]         = X_AXIS_LEFT_JOYSTICK;
    m_axisIDs[ ARCADE_DRIVE_THROTTLE ]      = Y_AXIS_LEFT_JOYSTICK;
    m_axisIDs[ ARCADE_DRIVE_STEER ]         = X_AXIS_RIGHT_JOYSTICK;
    m_buttonIDs[ SWITCH_DRIVE_MODE ]        = Y_BUTTON;

    m_buttonIDs[ AIM_SHOOTER_UP ]           = LEFT_BUMPER;
    m_buttonIDs[ AIM_SHOOTER_DOWN ]         = RIGHT_BUMPER;
    m_buttonIDs[ SHOOT_BUTTON ]             = LEFT_TRIGGER_PRESSED;
    m_buttonIDs[ FOLLOW_LINE ]              = A_BUTTON;
    m_axisIDs[ DRIVE_TO_TARGET ]            = X_AXIS_RIGHT_JOYSTICK;

}


//------------------------------------------------------------------
// Method:      SetScaleFactor
// Description: Allow the range of values to be set smaller than
//              -1.0 to 1.0.  By providing a scale factor between 0.0
//              and 1.0, the range can be made smaller.  If a value
//              outside the range is provided, then the value will
//              be set to the closest bounding value (e.g. 1.5 will
//              become 1.0)
// Returns:     void
//------------------------------------------------------------------
void TeleopControl::SetAxisScaleFactor
(
    TeleopControl::FUNCTION_IDENTIFIER  function,      // <I> - function that will update an axis
    float                                   scaleFactor    // <I> - scale factor used to limit the range
)
{
	DragonXbox* gamePad = DragonXbox::GetInstance();
    if ( gamePad != nullptr && m_axisIDs[ function ] != UNDEFINED_AXIS  )
    {
        gamePad->SetAxisScale(m_axisIDs[function],scaleFactor);
    }
}

//------------------------------------------------------------------
// Method:      SetAxisProfile
// Description: Sets the axis profile for the specifed axis
// Returns:     void
//------------------------------------------------------------------
void TeleopControl::SetAxisProfile
(
    TeleopControl::FUNCTION_IDENTIFIER      function,       // <I> - function that will update an axis
    AXIS_SENSITIVITY_CURVE          			profile         // <I> - profile to use
)
{
	DragonXbox* gamePad = DragonXbox::GetInstance();
    if ( gamePad != nullptr && m_axisIDs[ function ] != UNDEFINED_AXIS  )
    {
        gamePad->SetAxisProfile(m_axisIDs[function],profile);
    }
}

//------------------------------------------------------------------
// Method:      GetRawAxis
// Description: Reads the joystick axis, removes any deadband (small
//              value) and then scales as requested.
// Returns:     float   -  scaled axis value
//------------------------------------------------------------------
float TeleopControl::GetAxisValue
(
    TeleopControl::FUNCTION_IDENTIFIER  function    // <I> - function that whose axis will be read
) const
{
    float value = 0.0;
	DragonXbox* gamePad = DragonXbox::GetInstance();
    if ( gamePad != nullptr && m_axisIDs[ function ] != UNDEFINED_AXIS  )
    {
        value = gamePad->GetAxisValue(m_axisIDs[function]);
    }
	SmartDashboard::PutNumber( "Axis ID ", function );
	SmartDashboard::PutNumber( "Axis Value ", value );
    return value;
}

//------------------------------------------------------------------
// Method:      GetRawButton
// Description: Reads the button value.  Also allows POV, bumpers,
//              and triggers to be treated as buttons.
// Returns:     bool   -  scaled axis value
//------------------------------------------------------------------
bool TeleopControl::IsButtonPressed
(
    TeleopControl::FUNCTION_IDENTIFIER  function    // <I> - function that whose button will be read
) const
{
    bool isSelected = false;
	DragonXbox* gamePad = DragonXbox::GetInstance();
    if ( gamePad != nullptr && m_buttonIDs[ function ] != UNDEFINED_BUTTON  )
    {
        isSelected = gamePad->IsButtonPressed( m_buttonIDs[function]);
    }
    return isSelected;
}


