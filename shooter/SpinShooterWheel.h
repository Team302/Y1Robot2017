/*=============================================================================================
 * SpinShooterWheel.h
 *=============================================================================================
 *
 * File Description:
 *
 * This controls loading a ball into the shooter.
 *=============================================================================================*/

#ifndef SRC_SHOOTER_SPINSHOOTERWHEEL_H_
#define SRC_SHOOTER_SPINSHOOTERWHEEL_H_


//  Team 302 includes
#include <shooter/Shooter.h>           // Class that controls the shooter motors

class SpinShooterWheel
{
    public:
        //--------------------------------------------------------------------
        // Method:      SpinShooterWheel <<constructor>>
        // Description: This method creates and initializes the objects
        //--------------------------------------------------------------------
        SpinShooterWheel();      // constructor

        //--------------------------------------------------------------------
        // Method:      SpinWheels
        // Description: This method will read the gamepad input and if the
        //              SPIN_SHOOTER_WHEEL button is pressed, run the wheel.
        //              If not, stop the wheel.
        // Returns:     void
        //--------------------------------------------------------------------
        void SpinWheels() const;

        //--------------------------------------------------------------------
        // Method:      ~SpinShooterWheel <<destructor>>
        // Description: This method is called to delete these objects
        //--------------------------------------------------------------------
        virtual ~SpinShooterWheel() = default; // destructor

    protected:


    private:
        // Attributes

        //These are the speeds.
        const float m_shooterMotorSpeedStop = 0.0;
        const float m_shooterMotorSpeedGo = 1.0;

        // Default methods we don't want the compiler to implement for us
        SpinShooterWheel( const SpinShooterWheel& ) = delete;
        SpinShooterWheel& operator= ( const SpinShooterWheel& ) = delete;
        explicit SpinShooterWheel( SpinShooterWheel* other ) = delete;


};

#endif /* SRC_SHOOTER_SPINSHOOTERWHEEL_H_ */
