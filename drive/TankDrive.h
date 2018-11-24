/*=============================================================================================
 * TankDrive.h
 *=============================================================================================
 *
 * File Description:
 *
 * This implements the IJoystickDrive interface to drive the robot using joysticks in a tank
 * drive mode.
 *
 * Thus, the left axis will control the left side of the robot and the right axis will
 * control the right side of the robot.  Turning is achieve by pushing the axis in opposite
 * directions (e.g. right stick forward and left stick backward will turn left).
 *=============================================================================================*/
#ifndef SRC_DRIVE_TANKDRIVE_H_
#define SRC_DRIVE_TANKDRIVE_H_


//  Team 302 includes
#include <drive/IJoystickDrive.h>           // Interface being implemented
#include <drive/Chassis.h>                  // Class that controls the motors on the drive chassis
#include <driverInputs/OperatorInterface.h> // Controls creating singleton of the gamepads

class TankDrive: public IJoystickDrive
{
    public:
        //--------------------------------------------------------------------
        // Method:      TankDrive <<Constructor>>
        // Description: This method is called to create/initialize this class
        //--------------------------------------------------------------------
        TankDrive();                    // constructor

        //--------------------------------------------------------------------
        // Method:      DriveWithJoysticks
        // Description: This method will be called during the periodic loop
        //              to drive the robot.  It will interact with the joysticks
        //              to drive in tank drive mode.
        // Returns:     void
        //--------------------------------------------------------------------
        void DriveWithJoysticks() const override;

        //--------------------------------------------------------------------
        // Method:      GetIdentifier
        // Description: This gets the name that identifies the drive mode..
        // Returns:     const char*         identifier for the drive
        //--------------------------------------------------------------------
        const char* GetIdentifier() const override;

        //--------------------------------------------------------------------
        // Method:      ~TankDrive <<destructor>>
        // Description: This method is called to delete these objects
        //--------------------------------------------------------------------
        virtual ~TankDrive() = default;

    private:
        // Attributes
        Chassis*                m_chassis;
        TeleopControl*      m_oi;

        // Default methods we don't want the compiler to implement for us
        TankDrive( const TankDrive& ) = delete;
        TankDrive& operator= ( const TankDrive& ) = delete;
        explicit TankDrive( TankDrive* other ) = delete;

};

#endif /* SRC_DRIVE_TANKDRIVE_H_ */
