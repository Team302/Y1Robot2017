/*=============================================================================================
 * AimShooter.cpp
 *=============================================================================================
 *
 * File Description:
 *
 * TODO:: Document what this does
 *=============================================================================================*/




//  Team 302 includes
#include <shooter/Shooter.h>                    // Class the control the shooter motors
#include <driverInputs/OperatorInterface.h>     // Controls creating singleton of the gamepad
#include <shooter/AimShooter.h>                 // This class

//--------------------------------------------------------------------
// Method:      AdjustShooterPosition
// Description: This method will read the gamepad input and move the
//              shooter left or right if the correct input is pressed
// Returns:     void
//--------------------------------------------------------------------
void AimShooter::AdjustShooterPosition() const
{
    // Read the gamepad ...
    //      if the aim shooter higher button is pressed, move the shooter up (call MoveUp).
    //      else if the aim shooter lower button is pressed, move the shooter up (call MoveDown).
    //      otherwise, stop the alignment motor

    TeleopControl* myOI = TeleopControl::GetInstance();
    float shooterSpeed = m_stopShooterAlignment;
    if ( myOI->IsButtonPressed( TeleopControl::AIM_SHOOTER_UP ) )
    {
        shooterSpeed = MoveUp();
    }
    else if ( myOI->IsButtonPressed( TeleopControl::AIM_SHOOTER_DOWN ) )
    {
        shooterSpeed = MoveDown();
    }
    Shooter::GetShooter()->SetAimMotor( shooterSpeed );
}

//--------------------------------------------------------------------
// Method:      MoveUp
// Description: This method will calculate the shooter alignment move up speed
// Returns:     float   Speed to move the shooter alignment
//--------------------------------------------------------------------
float AimShooter::MoveUp() const
{
    float motorSpeed     = m_stopShooterAlignment;         // Initialize the speed to stop
    bool  atHighestPoint = Shooter::GetShooter()->IsAtHighestAngle();  // Determine if the shooter is at its highest point
    if ( !atHighestPoint )                                 // if it isn't at its highest point, set the speed
    {
        motorSpeed = m_shooter_moveUp;
    }
    return motorSpeed;
}


//--------------------------------------------------------------------
// Method:      MoveDown
// Description: This method will calculate the shooter alignment move down speed
// Returns:     float   Speed to move the shooter alignment
//--------------------------------------------------------------------
float AimShooter::MoveDown() const
{
    float motorSpeed     = m_stopShooterAlignment;       // Initialize the speed to stop
    bool  atLowestPoint = Shooter::GetShooter()->IsAtLowestAngle();  // Determine if the shooter is at its lowest point
    if ( !atLowestPoint )                                // if it isn't at its lowest point, set the speed
    {
        motorSpeed = m_shooter_moveDown;
    }
    return motorSpeed;
}


