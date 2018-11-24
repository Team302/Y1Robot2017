/*
 * DragonXbox.h
 *
 *========================================================================================================
 *
 * File Description:
 *
 * TODO:: Add documentation about what this class does
 *========================================================================================================*/

#ifndef SRC_DRIVERINPUTS_DRAGONXBOX_H_
#define SRC_DRIVERINPUTS_DRAGONXBOX_H_

#include <XboxController.h>

//#include <driverInputs/OperatorInterface.h>


enum XBOX_AXIS_IDENTIFIER
{
	UNDEFINED_AXIS = -1000,
	X_AXIS_LEFT_JOYSTICK = 0,
	Y_AXIS_LEFT_JOYSTICK,
	LEFT_TRIGGER,
	RIGHT_TRIGGER,
	X_AXIS_RIGHT_JOYSTICK,
	Y_AXIS_RIGHT_JOYSTICK,
	MAX_XBOX_AXIS                   // used for looping
};

enum XBOX_BUTTON_IDENTIFIER
{
	UNDEFINED_BUTTON = -1000,
	A_BUTTON = 0,
	B_BUTTON,
	X_BUTTON,
	Y_BUTTON,
	LEFT_BUMPER,
	RIGHT_BUMPER,
	BACK_BUTTON,
	START_BUTTON,
	PRESS_LEFT_STICK,
	PRESS_RIGHT_STICK,
	LEFT_TRIGGER_PRESSED,
	RIGHT_TRIGGER_PRESSED,
	MAX_XBOX_BUTTONS                    // used for looping
};


enum AXIS_SENSITIVITY_CURVE //enum for selecting linear or cubic axis profile
{
	AXIS_LINEAR ,
	AXIS_CUBIC,
	MAX_SENS_OPTIONS
};

class DragonXbox : public XboxController
{
    public:


        //----------------------------------------------------------------------------------
        // Method:      GetInstance
        // Description: If there isn't an instance of this class, it will create one.  The
        //              single class instance will be returned.
        // Returns:     DragonXbox*  instance of this class
        //----------------------------------------------------------------------------------
        static DragonXbox* GetInstance();


        //getters
        //-------------------------------------------------------------------------------------------------
        // Method:      GetAxis
        // Description: Return the current value (between -1.0 and 1.0) for the requested axis.
        // Returns:     float   - current axis value
        //-------------------------------------------------------------------------------------------------
        float GetAxisValue
        (
            XBOX_AXIS_IDENTIFIER    axis        // <I> - axis identifier to read
        ) const;

        //-------------------------------------------------------------------------------------------------
        // Method:      GetButton
        // Description: Return whether the requested button is selected (true) or not (false)
        // Returns:     bool    true  - button is pressed
        //                      false - button is not pressed
        //-------------------------------------------------------------------------------------------------
        bool IsButtonPressed
        (
            XBOX_BUTTON_IDENTIFIER    button         // <I> - button to check
        ) const;


        //setters
        //-------------------------------------------------------------------------------------------------
        // Method:      SetProfile
        // Description: Specify the profile curve used for setting the sensitivity of the axis.  By default,
        //              this is linear, but a cubic curve would give more control when the axis is barely
        //              pressed (e.g. if it were moved 50% forward, instead of returning 0.5, it would
        //              return 0.5 * 0.5 * 0.5 or .125, but when the axis was moved all the way forward,
        //              it would return the same value -- 1.0.  Since it is cubed, it retains the sign.
        //
        //              This affects values returned from GetAxis calls.
        // Returns:     void
        //-------------------------------------------------------------------------------------------------
        void SetAxisProfile
        (
            XBOX_AXIS_IDENTIFIER           axis,       // <I> - axis identifier to modify
            AXIS_SENSITIVITY_CURVE  	   curve       // <I> - the definition of the sensitivity
        );


        //-------------------------------------------------------------------------------------------------
        // Method:      SetScale
        // Description: Scale the returned value to a range between the specified negative scale factor and
        //              the scale factor.  This is used to reduce the maximum value returned.
        //
        //              This affects values returned from GetAxis calls.
        // Returns:     void
        //-------------------------------------------------------------------------------------------------
        void SetAxisScale
        (
            XBOX_AXIS_IDENTIFIER    			axis,       // <I> - axis identifier to modify
            float                               scaleFactor // <I> - value  (0 < scale <= 1.0) to scale the axis value
        );


private:
        //-------------------------------------------------------------------------------------------------
        // Method:      <<Constructor>>
        // Description: Create a DragonXbox object .
        //-------------------------------------------------------------------------------------------------
        DragonXbox();

        //-------------------------------------------------------------------------------------------------
        // Method:      <<Destructor>>
        // Description: Destroy a DragonXbox object .
        //-------------------------------------------------------------------------------------------------
        virtual ~DragonXbox() = default;

        const float DEAD_BAND_THRESH = 0.2;         // Minimum value joystick must be past to actually return value to prevent drift
        const float TRIGGER_PRESSED_THRESH = 0.4;   // When triggers are treated as buttons, it must be pressed more than this value to be considered pressed
        const float DONT_INVERT_AXIS = 1.0;         // Scale factor for inverting the axis
        const float INVERT_AXIS = -1.0;             // Scale factor for inverting the axis
        const float LINEAR_SCALE_PROFILE = 1.0;     // Linear profile power
        const float CUBIC_SCALE_PROFILE = 3.0;      // Cubic profile power
        const float STD_RANGE_SCALING = 1.0;        // Range is between -1.0 and 1.0

        // Methods not being implemented
        DragonXbox( DragonXbox* other ) =  delete;

        static DragonXbox*   m_instance; // Singleton instance of this class

        // Attributes
        // Allow 20 slots for the attributes (NOTE: it would be more efficient with vectors, but
        // we want to keep it simple)
        // Index into these arrays is AXIS_IDENTIFIER enum
        const int m_maxAxis = 20;          // used for validation to make sure we don't walk off the array's memory
        float  m_axisScale[20];            // scale factor used to limit the range of axis values returned
        float  m_axisInversionFactor[20];  // scale factors used to invert the axis values (always 1.0 or -1.0)
        float  m_axisProfile[20];          // the definition for "scaling" the axis values
};

#endif /* SRC_DRIVERINPUTS_DRAGONXBOX_H_ */
