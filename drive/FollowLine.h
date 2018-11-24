/*=============================================================================================
 * FollowLine.h
 *=============================================================================================
 *
 * File Description:
 *
 * This class will follow a white line surrounded by black lines.
 *=============================================================================================*/

#ifndef SRC_DRIVE_FOLLOWLINE_H_
#define SRC_DRIVE_FOLLOWLINE_H_


//  Team 302 includes
#include <drive/Chassis.h>           // Class that controls the motors on the drive chassis


class FollowLine
{
    public:
        //--------------------------------------------------------------------
        // Method:      FollowLine <<constructor>>
        // Description: This method creates and initializes the objects
        //--------------------------------------------------------------------
        FollowLine();      // constructor

        //--------------------------------------------------------------------
        // Method:      Drive
        // Description: This method will follow a line.
        // Returns:     void
        //--------------------------------------------------------------------
        void Drive();

        //--------------------------------------------------------------------
        // Method:      Stop
        // Description: This method will stop
        // Returns:     void
        //--------------------------------------------------------------------
        void Stop();

        //--------------------------------------------------------------------
        // Method:      ~FollowLine <<destructor>>
        // Description: This method is called to delete these objects
        //--------------------------------------------------------------------
        virtual ~FollowLine() = default; // destructor

    protected:

        enum AUTON_DRIVE_STATES
        {
            DRIVE_STRAIGHT,
            DRIVE_SLIGHT_LEFT,
            DRIVE_SLIGHT_RIGHT,
            DRIVE_SHARP_LEFT,
            DRIVE_SHARP_RIGHT,
            LOST,
            BACKINGUP,
            STOPPED
        };

        //--------------------------------------------------------------------
        // Method:      DriveStraight
        // Description: This method will drive straight
        // Returns:     void
        //--------------------------------------------------------------------
        void DriveStraight();

        //--------------------------------------------------------------------
        // Method:      DriveSlightLeft
        // Description: This method will drive slightly to the left
        // Returns:     void
        //--------------------------------------------------------------------
        void DriveSlightLeft();


        //--------------------------------------------------------------------
        // Method:      DriveSharpLeft
        // Description: This method will drive sharply to the left
        // Returns:     void
        //--------------------------------------------------------------------
        void DriveSharpLeft();


        //--------------------------------------------------------------------
        // Method:      DriveSlightRight
        // Description: This method will drive slightly to the right
        // Returns:     void
        //--------------------------------------------------------------------
        void DriveSlightRight();

        //--------------------------------------------------------------------
        // Method:      DriveSharpRight
        // Description: This method will drive sharply to the right
        // Returns:     void
        //--------------------------------------------------------------------
        void DriveSharpRight();

        //--------------------------------------------------------------------
        // Method:      DriveStraightBack
        // Description: This method will drive straight back
        // Returns:     void
        //--------------------------------------------------------------------


        void DriveStraightBack();


    private:
        // Attributes
        Chassis* 			m_chassis;
        AUTON_DRIVE_STATES	m_previousState;

        // TODO:: create constants for the left and right speeds based on the state (e.g. turn left slightly).

            const float m_drive_straight_left = 0.25;
			const float m_drive_straight_right = 0.25;

            const float m_drive_slight_left_left = 0.1;
			const float m_drive_slight_left_right = 0.5;

            const float m_drive_slight_right_left = 0.5;
            const float m_drive_slight_right_right = 0.1;

			const float m_drive_sharp_left_left = -0.5;
			const float m_drive_sharp_left_right = 0.5;

            const float m_drive_sharp_right_left = 0.5;
			const float m_drive_sharp_right_right = -0.5;

            const float m_drive_lost_left = 0.0;
			const float m_drive_lost_right = 0.0;

			// MRW remember semi-colons
            //const float m_drive_backingup_left = -0.3
			//const float m_drive_backingup_right = -0.3

            const float m_drive_backingup_left = -0.2;
			const float m_drive_backingup_right = -0.2;

            // TODO:: add attribute to keep track of the previous state


        // Default methods we don't want the compiler to implement for us
        FollowLine( const FollowLine& ) = delete;
        FollowLine& operator= ( const FollowLine& ) = delete;
        explicit FollowLine( FollowLine* other ) = delete;


};

#endif /* SRC_DRIVE_FOLLOWLINE_H_ */
