/*=============================================================================================
 * AimShooter.h
 *=============================================================================================
 *
 * File Description:
 *
 * TODO:: Document what this does
 *
 *=============================================================================================*/

#ifndef SRC_SHOOTER_AIMSHOOTER_H_
#define SRC_SHOOTER_AIMSHOOTER_H_


//  Team 302 includes
#include <shooter/Shooter.h>                // Class that controls the shooter motors
#include <driverInputs/OperatorInterface.h> // Driver Game pad interface

class AimShooter
{
    public:
        //--------------------------------------------------------------------
        // Method:      AimShooter <<constructor>>
        // Description: This method creates and initializes the objects
        //--------------------------------------------------------------------
        AimShooter() = default;      // constructor

        //--------------------------------------------------------------------
        // Method:      AdjustShooterPosition
        // Description: This method will read the gamepad and aim the shooter
        //              accordingly.
        // Returns:     void
        //--------------------------------------------------------------------
        void AdjustShooterPosition() const;

        //--------------------------------------------------------------------
        // Method:      ~AimShooter <<destructor>>
        // Description: This method is called to delete these objects
        //--------------------------------------------------------------------
        virtual ~AimShooter() = default; // destructor

    protected:

        //--------------------------------------------------------------------
        // Method:      MoveUp
        // Description: This method will calculate the shooter alignment move up speed
        // Returns:     float   Speed to move the shooter alignment
        //--------------------------------------------------------------------
        float MoveUp() const;


        //--------------------------------------------------------------------
        // Method:      MoveDown
        // Description: This method will calculate the shooter alignment move down speed
        // Returns:     float   Speed to move the shooter alignment
        //--------------------------------------------------------------------
        float MoveDown() const;

    private:
        // add constants to set the speed for moving up and down
        const float m_shooter_moveUp  = 0.3;
        const float m_shooter_moveDown = -0.3;
        const float m_stopShooterAlignment = 0.0;



        // Default methods we don't want the compiler to implement for us
        AimShooter( const AimShooter& ) = delete;
        AimShooter& operator= ( const AimShooter& ) = delete;
        explicit AimShooter( AimShooter* other ) = delete;


};

#endif /* SRC_SHOOTER_AIMSHOOTER_H_ */
