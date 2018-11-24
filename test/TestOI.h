/*
 * TestOI.h
 *
 */

#ifndef SRC_TEST_TESTOI_H_
#define SRC_TEST_TESTOI_H_

#include <driverInputs/OperatorInterface.h>


enum OI_TEST_SCENARIO
{
	TANK_DRIVE_LEFT_LINEAR,
	TANK_DRIVE_RIGHT_LINEAR,
	TANK_DRIVE_LEFT_CUBIC,
	TANK_DRIVE_RIGHT_CUBIC,
	SCALED_TANK_DRIVE_LEFT_LINEAR,
	SCALED_TANK_DRIVE_RIGHT_LINEAR,
	SCALED_TANK_DRIVE_LEFT_CUBIC,
	SCALED_TANK_DRIVE_RIGHT_CUBIC,
	ARCADE_DRIVE_THROTTLE_LINEAR,
	ARCADE_DRIVE_STEER_LINEAR,
	ARCADE_DRIVE_THROTTLE_CUBIC,
	ARCADE_DRIVE_STEER_CUBIC,
	SCALED_ARCADE_DRIVE_THROTTLE_LINEAR,
	SCALED_ARCADE_DRIVE_STEER_LINEAR,
	SCALED_ARCADE_DRIVE_THROTTLE_CUBIC,
	SCALED_ARCADE_DRIVE_STEER_CUBIC,
	NUM_OI_TEST_SCENARIOS
};

class TestTelopControl
{
	public:

		//----------------------------------------------------------------------------------
		// Method:      GetInstance
		// Description: If there isn't an instance of desired this class, create it.
		//              Otherwise, hand out the single instance.
		// Returns:     TestDragonXbox*    TestDragonStick singleton
		//----------------------------------------------------------------------------------
		static TestTelopControl* GetInstance();

		//-----------------------------------------------------------------------
		// Method:      Init
		// Description: Initializes the OI for the test.   This should
		//              be called from the appropriate Init method in Robot.cpp
		//
		//              Note: all tests are described with their enum and have a
		//              deadband eliminated.
		// Returns:     void
		//-----------------------------------------------------------------------
		void Init
		(
				OI_TEST_SCENARIO    type    // <I> - test to run
		);

		//-----------------------------------------------------------------------
		// Method:      Periodic
		// Description: This displays the joystick axis values and button states
		//              to the dashboard
		// Returns:     void
		//-----------------------------------------------------------------------
		void Periodic();

	private:
		//-----------------------------------------------------------------------
		// Method:      <<constructor>>
		// Description: creates the test environment attributes
		//-----------------------------------------------------------------------
		TestTelopControl();


		//-----------------------------------------------------------------------
		// Method:      <<destructor>>
		// Description: cleans up other objects
		//-----------------------------------------------------------------------
		virtual ~TestTelopControl() = default;

		static TestTelopControl*                                  m_instance; //make a singleton
		TeleopControl::FUNCTION_IDENTIFIER 			m_test;


};


#endif /* SRC_TEST_TESTOI_H_ */
