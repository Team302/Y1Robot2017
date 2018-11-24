
/*=============================================================================================
 * LoadBall.h
 *=============================================================================================
 *
 * File Description:
 *
 * This controls loading a ball into the shooter.
 *=============================================================================================*/

#ifndef SRC_SHOOTER_LOADBALL_H_
#define SRC_SHOOTER_LOADBALL_H_

#include <DriverInputs/DragonXbox.h>


//  Team 302 includes

class LoadBall
{
    public:
        //--------------------------------------------------------------------
        // Method:      LoadBall <<constructor>>
        // Description: This method creates and initializes the objects
        //--------------------------------------------------------------------
        LoadBall() = default;      // constructor

        //--------------------------------------------------------------------
        // Method:      CycleLoader
        // Description: This method will read the gamepad input and move run
        //              loader motor until the sensor detects it is back in
        //              load position
        // Returns:     void
        //--------------------------------------------------------------------
        void CycleLoader();

        //--------------------------------------------------------------------
        // Method:      ~LoadBall <<destructor>>
        // Description: This method is called to delete these objects
        //--------------------------------------------------------------------
        virtual ~LoadBall() = default; // destructor

    protected:


    private:
        // Attributes
        // This is the speed for the Loader's Motor- It's Constant
        const float m_loaderSpeedStopped = 0.0;
        const float m_loaderSpeedRun = .5;

        const float m_neededShooterSpeed = 3000.0;

        // Default methods we don't want the compiler to implement for us
        LoadBall( const LoadBall& ) = delete;
        LoadBall& operator= ( const LoadBall& ) = delete;
        explicit LoadBall( LoadBall* other ) = delete;
};

#endif /* SRC_SHOOTER_LOADBALL_H_ */
