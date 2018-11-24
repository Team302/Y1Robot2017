/*
 * TestChassis.h
 *
 */

#ifndef SRC_TEST_TestChassis_H_
#define SRC_TEST_TestChassis_H_

#include <drive/Chassis.h>


class TestChassis
{

    public:

        enum CHASSIS_TEST_CASE_ID
        {
            DRIVE_FORWARD_COAST,
            DRIVE_BACKWARD_COAST,
            TURN_RIGHT_COAST,
            TURN_LEFT_COAST,
            DRIVE_FORWARD_BRAKE,
            DRIVE_BACKWARD_BRAKE,
            TURN_RIGHT_BRAKE,
            TURN_LEFT_BRAKE,
            LINE_TRACKER_STATE,
            MAX_CHASSIS_TESTS
        };

        //----------------------------------------------------------------------------------
        // Method:      GetInstance
        // Description: If there isn't an instance of desired this class, create it.
        //              Otherwise, hand out the single instance.
        // Returns:     TestChassis*    singleton
        //----------------------------------------------------------------------------------
        static TestChassis* GetInstance();

        //-----------------------------------------------------------------------------------
        // Method:          Init
        // Description:     Setup the test
        // Returns:         void
        //-----------------------------------------------------------------------------------
        void Init
        (
            TestChassis::CHASSIS_TEST_CASE_ID   test    // <I> - test case identifier
        );

        //-----------------------------------------------------------------------------------
        // Method:          Periodic
        // Description:     Run the test
        // Returns:         void
        //-----------------------------------------------------------------------------------
        void Periodic();

        //-----------------------------------------------------------------------------------
        // Method:          Stop
        // Description:     Stop the test
        // Returns:         void
        //-----------------------------------------------------------------------------------
        void Stop();


    private:
        TestChassis();
        virtual ~TestChassis() = default;

        float m_leftSpeed;
        float m_rightSpeed;
        float m_time;

        const float m_stoppedSpeed  = 0.0;
        const float m_forwardSpeed  = 0.5;
        const float m_backwardSpeed = -0.5;

        const float m_timeIncr = 0.02;
        const float m_segmentTime = 5.0;

        static TestChassis* m_instance; //make a singleton
};


#endif /* SRC_TEST_TestChassis_H_ */
