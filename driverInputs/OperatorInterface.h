/*========================================================================================================
 * OperatorInterface.h
 *========================================================================================================
 *
 * File Description:
 *
 * This defines all functions and variable names
 *========================================================================================================*/

#ifndef SRC_DRIVERINPUTS_OPERATORINTERFACE_H_
#define SRC_DRIVERINPUTS_OPERATORINTERFACE_H_

#include <driverInputs/DragonXbox.h>

class TeleopControl
{
    public:

        enum FUNCTION_IDENTIFIER
        {
            TANK_DRIVE_LEFT_CONTROL,
            TANK_DRIVE_RIGHT_CONTROL,
            ARCADE_DRIVE_THROTTLE,
            ARCADE_DRIVE_STEER,
            SWITCH_DRIVE_MODE,
            AIM_SHOOTER_UP,
            AIM_SHOOTER_DOWN,
            SHOOT_BUTTON,
            FOLLOW_LINE,
            DRIVE_TO_TARGET,
            MAX_FUNCTIONS
        };


        //----------------------------------------------------------------------------------
        // Method:      GetInstance
        // Description: If there isn't an instance of this class, it will create one.  The
        //              single class instance will be returned.
        // Returns:     OperatorInterface*  instance of this class
        //----------------------------------------------------------------------------------
        static TeleopControl* GetInstance();


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
        void SetAxisScaleFactor
        (
            TeleopControl::FUNCTION_IDENTIFIER  axis,          // <I> - axis number to update
            float                                   scaleFactor    // <I> - scale factor used to limit the range
        );

        //------------------------------------------------------------------
        // Method:      SetAxisProfile
        // Description: Sets the axis profile for the specifed axis
        // Returns:     void
        //------------------------------------------------------------------
        void SetAxisProfile
        (
            TeleopControl::FUNCTION_IDENTIFIER      axis,       // <I> - axis number to update
			AXIS_SENSITIVITY_CURVE						profile     // <I> - profile to use
        );

        //------------------------------------------------------------------
        // Method:      GetRawAxis
        // Description: Reads the joystick axis, removes any deadband (small
        //              value) and then scales as requested.
        // Returns:     float   -  scaled axis value
        //------------------------------------------------------------------
        float GetAxisValue
        (
            TeleopControl::FUNCTION_IDENTIFIER     axis // <I> - axis number to update
        ) const;

        //------------------------------------------------------------------
        // Method:      GetRawButton
        // Description: Reads the button value.  Also allows POV, bumpers,
        //              and triggers to be treated as buttons.
        // Returns:     bool   -  scaled axis value
        //------------------------------------------------------------------
        bool IsButtonPressed
        (
            TeleopControl::FUNCTION_IDENTIFIER button   // <I> - button number to query
        ) const;


    private:

        //----------------------------------------------------------------------------------
        // Method:      OperatorInterface <<constructor>>
        // Description: This will construct and initialize the object
        //----------------------------------------------------------------------------------
        TeleopControl();

        //----------------------------------------------------------------------------------
        // Method:      ~OperatorInterface <<destructor>>
        // Description: This will clean up the object
        //----------------------------------------------------------------------------------
        virtual ~TeleopControl() = default;

        //----------------------------------------------------------------------------------
        // Attributes
        //----------------------------------------------------------------------------------
        static TeleopControl*   m_instance; // Singleton instance of this class
        const int                   m_maxFunctions = 25;

        XBOX_AXIS_IDENTIFIER		m_axisIDs[25];
        XBOX_BUTTON_IDENTIFIER		m_buttonIDs[25];
};

#endif /* SRC_DRIVERINPUTS_OPERATORINTERFACE_H_ */
