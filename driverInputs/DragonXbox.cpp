/*
 * DragonXBox.cpp
 *
 *========================================================================================================
 *
 * File Description:
 *
 * TODO:: Add documentation about what this class does
 *========================================================================================================*/
#include <stdio.h>

#include <XboxController.h>
#include <GenericHID.h>
#include <SmartDashboard/SmartDashboard.h>  	// Smart Dashboard

#include <driverInputs/DragonXbox.h>
#include <utils/LimitValue.h>

#include <cmath>        // std:abs

using namespace frc;


//----------------------------------------------------------------------------------
// Method:      GetInstance
// Description: If there isn't an instance of this class, it will create one.  The
//              single class instance will be returned.
// Returns:     DragonXbox*  instance of this class
//----------------------------------------------------------------------------------
DragonXbox* DragonXbox::m_instance = nullptr; // initialize the instance variable to nullptr
DragonXbox* DragonXbox::GetInstance()
{
    if ( DragonXbox::m_instance == nullptr )
    {
    	DragonXbox::m_instance = new DragonXbox();
    }
    return DragonXbox::m_instance;
}


//-------------------------------------------------------------------------------------------------
// Method:      <<Constructor>>
// Description: Create a DragonXbox object .
//-------------------------------------------------------------------------------------------------
// MRW look at your data type in DragonXbox.h so the correct type is passed in, m_axisProfile is an array
DragonXbox::DragonXbox() : XboxController( 0 ),
                           m_axisScale(),
                           m_axisInversionFactor(),
                           m_axisProfile()
//m_axisProfile( 1.0 )
{
    // verify we have enough axis slots and if we don't write a message to the log file
    if ( MAX_XBOX_AXIS > m_maxAxis )
    {
    	SmartDashboard::PutString( "Axis Error", "Houston we have a problem ... there are more XBOX axis than we have array slots \n" );
    }

    // Initialize the attributes for all of the axis to the defaults
    for ( auto inx=0; inx<m_maxAxis; ++inx )
    {
        m_axisScale[inx] = STD_RANGE_SCALING;           // range is -1.0 to 1.0
        m_axisInversionFactor[inx] = DONT_INVERT_AXIS;  // values are whatever is read from the axis
        m_axisProfile[inx] = CUBIC_SCALE_PROFILE;  // scaling curve is 1.0
    }
	
	// MRW looks good; remember to remove the TODOs when you finish something.  Don't be afraid to ask questions.

    // Modify the axis without default values
    // - Y axis are inverted
		m_axisInversionFactor[Y_AXIS_LEFT_JOYSTICK] = INVERT_AXIS;
		m_axisInversionFactor[Y_AXIS_RIGHT_JOYSTICK] = INVERT_AXIS;
}



//----------------------------------------------------------------------------------
// Method:      GetAxis
// Description: This returns the scaled and curve profiled axis value for the specified axis
//
//              NOTE:  the order of operations is important because if deadband is
//              done, last, for instance, the output would lose a lot of the benefit
//              of the scaling curve (power).  For instance, if a value of 0.5 were read
//              from the axis and 0.2 was the deadband, if the curve was cubic, it
//              would calculate a value of 0.125 which would be below the deadband
//              threshold, so it would return 0.0.  On the otherhand, if deadbanding
//              is done on the raw value, 0.125 would be returned.  In fact, in
//              the first scenario, the axis would need to read almost 0.6 before
//              a non-zero value would be returned (at which point 0.2 is returned), so
//              only 0.4 of the range is returning non-zero numbers.  Comparing this
//              to the second case, at 0.2 a value of .008 is calculated and returned.
// Returns:     double output - scaled, deadbanded, and curve profiled output of axis
//----------------------------------------------------------------------------------
float DragonXbox::GetAxisValue
(
    XBOX_AXIS_IDENTIFIER    axis        // <I> - axis identifier to read
) const
{
    double output = 0.0;    //zero output to start
    if ( axis < MAX_XBOX_AXIS )
    {
        // read the appropriate value from the xbox controller & multiply it by the inversion factor
        switch ( axis )
        {
            case X_AXIS_LEFT_JOYSTICK:
                output = GetX( GenericHID::kLeftHand ) * m_axisInversionFactor[ axis ];
                break;
			case Y_AXIS_LEFT_JOYSTICK:
                output = (GetY( GenericHID::kLeftHand ) * m_axisInversionFactor[ axis ]);
                break;

            case X_AXIS_RIGHT_JOYSTICK:
                output = GetX( GenericHID::kRightHand ) * m_axisInversionFactor[ axis ];
                break;
			case Y_AXIS_RIGHT_JOYSTICK:
                output = (GetY( GenericHID::kRightHand ) * m_axisInversionFactor[ axis ]);
                break;

            default:
                break;
        }

		if (std::abs(output) < DEAD_BAND_THRESH)
		{
			output = 0.0;
		}
		else if (std::abs(output) > DEAD_BAND_THRESH )
		{
			output = pow( output, m_axisProfile[axis] );
			output = output * m_axisScale[axis];
		}
    }
    return output; //returns scaled, profiled, deadbanded joystick output
}

//----------------------------------------------------------------------------------
// Method:      GetButton
// Description: This returns the scaled and curve profiled axis value for the specified axis
// Parameters:  button - BUTTON_IDENTIFIER enum to select which button to check
// Returns:     bool - true for button pressed
//----------------------------------------------------------------------------------
bool DragonXbox::IsButtonPressed
(
    XBOX_BUTTON_IDENTIFIER    button         // <I> - button to check
) const
{
    bool pressed = false;
    //switch statement to check if button is pressed depending on which button is identified
    switch(button)
    {
        case A_BUTTON:
            pressed = GetAButton();
            break;
		case B_BUTTON:
            pressed = GetBButton();
            break;
		case X_BUTTON:
            pressed = GetXButton();
            break;
		case Y_BUTTON:
            pressed = GetYButton();
            break;
		case LEFT_BUMPER:
            pressed = GetBumper(GenericHID::kLeftHand);
            break;
		case RIGHT_BUMPER:
            pressed = GetBumper(GenericHID::kRightHand);
            break;
		case BACK_BUTTON:
            pressed = GetBackButton();
            break;
		case START_BUTTON:
            pressed = GetStartButton();
            break;
        case PRESS_LEFT_STICK:
            pressed = GetStickButton( GenericHID::kLeftHand );
            break;
		case PRESS_RIGHT_STICK:
            pressed = GetStickButton( GenericHID::kRightHand );
            break;
		case LEFT_TRIGGER_PRESSED:
            pressed = (GetTriggerAxis( GenericHID::kLeftHand )) > TRIGGER_PRESSED_THRESH; //if trigger value is greater than threshold return true
            break;
		case RIGHT_TRIGGER_PRESSED:
            pressed = (GetTriggerAxis( GenericHID::kRightHand )) > TRIGGER_PRESSED_THRESH; //if trigger value is greater than threshold return true
            break;

        default:
            pressed = false;
            break;
    }

    return pressed; //returns bool for is button pressed
}

//----------------------------------------------------------------------------------
// Method:      SetProfile
// Description: This returns the scaled and curve profiled axis value for the specified axis
// Returns:     void
//----------------------------------------------------------------------------------
void DragonXbox::SetAxisProfile
(
	XBOX_AXIS_IDENTIFIER           axis,       // <I> - axis identifier to modify
	AXIS_SENSITIVITY_CURVE  	   curve       // <I> - the definition of the sensitivity
)
{
    if ( axis < MAX_XBOX_AXIS )             // valid axis
    {
        m_axisProfile[ axis ] = ( curve == AXIS_SENSITIVITY_CURVE::AXIS_CUBIC ) ? CUBIC_SCALE_PROFILE : LINEAR_SCALE_PROFILE;    // update the power
    }
}

//----------------------------------------------------------------------------------
// Method:      SetScale
// Description: This returns the scaled and curve profiled axis value for the specified axis
// Returns:     void
//----------------------------------------------------------------------------------
void DragonXbox::SetAxisScale
(
    XBOX_AXIS_IDENTIFIER    axis,       // <I> - axis identifier to modify
    float                   scaleFactor // <I> - value  (0 < scale <= 1.0) to scale the axis value
)
{
    if ( axis < MAX_XBOX_AXIS )             // valid axis
    {
		float axisRange = LimitValue::ForceInRange(scaleFactor, 0.0, 1.0);
		m_axisScale[axis] = axisRange;
    }
}
