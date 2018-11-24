/*
 * TestShooter.h
 *
 */

#ifndef SRC_TEST_TestShooter_H_
#define SRC_TEST_TestShooter_H_

#include <shooter/Shooter.h>


class TestShooter
{

    public:

        enum SHOOTER_TEST_CASE_ID
        {
            AIM_SHOOTER_UP,
            AIM_SHOOTER_DOWN,
            SPIN_SHOOTER_WHEELS,
            LOAD_BALL,
            AUTO_FIRE,
            MAX_SHOOTER_TESTS
        };

        //----------------------------------------------------------------------------------
        // Method:      GetInstance
        // Description: If there isn't an instance of desired this class, create it.
        //              Otherwise, hand out the single instance.
        // Returns:     TestShooter*    singleton
        //----------------------------------------------------------------------------------
        static TestShooter* GetInstance();

        //-----------------------------------------------------------------------------------
        // Method:          Init
        // Description:     Setup the test
        // Returns:         void
        //-----------------------------------------------------------------------------------
        void Init
        (
            TestShooter::SHOOTER_TEST_CASE_ID   test    // <I> - test case identifier
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
        TestShooter();
        virtual ~TestShooter() = default;

        SHOOTER_TEST_CASE_ID m_test;
        float m_alignSpeed;
        float m_loadSpeed;
        float m_spinSpeed;
        float m_time;

        const float m_stoppedSpeed      = 0.0;
        const float m_alignUpSpeed      = 0.1;
        const float m_alignDownSpeed    = -0.1;
        const float m_loadBallSpeed     = .25;
        const float m_spinShooterSpeed  = 0.75;

        const float m_timeIncr = 0.02;
        const float m_segmentTime = 5.0;

        static TestShooter* m_instance; //make a singleton
};


#endif /* SRC_TEST_TestShooter_H_ */
