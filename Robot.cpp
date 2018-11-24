
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include <drive/ArcadeDrive.h>
#include <drive/TankDrive.h>
#include <drive/IJoystickDrive.h>
#include <drive/FollowLine.h>

#include <shooter/AimShooter.h>
#include <shooter/LoadBall.h>
#include <shooter/SpinShooterWheel.h>

#include <shooter/Shooter.h>

#include <driverInputs/OperatorInterface.h>



class Robot: public frc::IterativeRobot
{
	// TODO:  add documentation
public:
//----------------------------------------------------------------------------------
// Method:      RobotInit <<Robot>>
// Description: Create the motor controllers and set whether they are inverted or not.
//----------------------------------------------------------------------------------
	void RobotInit()
	
	{
		m_oi = TeleopControl::GetInstance();
		
		m_followLine=new FollowLine();

		m_driveModes[0] = new ArcadeDrive();
		m_driveModes[1] = new TankDrive();
		m_currentDriveMode = 0;

		m_spinShooterWheel=new SpinShooterWheel();
		m_aimShooter=new AimShooter();
		m_loadBall=new LoadBall();

		m_driveModeLoopCount = 0;
	}
//----------------------------------------------------------------------------------
// Method:      AutonomousInit <<Constructor>>
// Description: Create the motor controllers and set whether they are inverted or not.
//----------------------------------------------------------------------------------
	void AutonomousInit() override
	{
	}
//----------------------------------------------------------------------------------
// Method:      AutonomousPeriodic <<Constructor>>
// Description: Create the motor controllers and set whether they are inverted or not.
//----------------------------------------------------------------------------------
	void AutonomousPeriodic()
	{
		
		// TODO:  add periodic calls for following the line
		m_followLine->Drive();
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		m_driveModeLoopCount++;

		if( m_oi->IsButtonPressed( TeleopControl::SWITCH_DRIVE_MODE) && m_driveModeLoopCount > 50 )
		{
			m_currentDriveMode++;
			if ( m_currentDriveMode > 1)
			{
				m_currentDriveMode = 0;
			}
			m_driveModeLoopCount = 0;
		}

		if( m_oi->IsButtonPressed( TeleopControl::FOLLOW_LINE) )
		{
			m_followLine->Drive();
		}
		else
		{
			//:   Call the drive mode (ArcadeDrive or TankDrive) based on mode
			SmartDashboard::PutString( "Drive Mode ", m_driveModes [m_currentDriveMode]->GetIdentifier());
			m_driveModes [m_currentDriveMode]->DriveWithJoysticks();
		}
		//::  Process the Shooter buttons for running the shooter
		m_spinShooterWheel->SpinWheels();
		m_aimShooter->AdjustShooterPosition();
		m_loadBall->CycleLoader();
	}

	void TestPeriodic()
	{
		lw->Run();
		Shooter* shooter = Shooter::GetShooter();
		shooter->SetBallLoadMotor( 0.5 );
	}

private:
	frc::LiveWindow* lw = LiveWindow::GetInstance();

	TeleopControl* 	m_oi;
	FollowLine*      	m_followLine;
	IJoystickDrive*		m_driveModes[2];
	int					m_currentDriveMode;

	SpinShooterWheel*	m_spinShooterWheel;
	AimShooter*			m_aimShooter;
	LoadBall*			m_loadBall;

	int					m_driveModeLoopCount;

};

START_ROBOT_CLASS(Robot)
