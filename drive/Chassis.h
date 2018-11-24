/*=============================================================================================
 * Chassis.h
 *=============================================================================================
 *
 * File Description:
 *
 * This file interacts with the hardware (motors and sensors) used to drive the robot.  It is a
 * Singleton.
 *=============================================================================================*/
#ifndef SRC_DRIVE_CHASSIS_H_
#define SRC_DRIVE_CHASSIS_H_

// WPILib includes
#include <CANTalon.h>
#include <DigitalInput.h>
#include <DigitalOutput.h>


#include <drive/LineTracker.h>

enum LINE_TRACKER_STATE  // Left to right with the colors
{
    UNKNOWN_STATE = -1,
    ALL_BLACK = 0,
    BLACK_BLACK_WHITE = 1,
    BLACK_WHITE_BLACK = 10,
    BLACK_WHITE_WHITE = 11,
    WHITE_BLACK_BLACK = 100,
    WHITE_BLACK_WHITE = 101,
    WHITE_WHITE_BLACK = 110,
    ALL_WHITE = 111
};


class Chassis
{
public:
    //----------------------------------------------------------------------------------
    // Method:      GetChassis
    // Description: If there isn't an instance, create it.  Otherwise, hand out the single
    //              instance.
    // Returns:     Chassis*    This class
    //----------------------------------------------------------------------------------
    static Chassis* GetChassis();

    //----------------------------------------------------------------------------------
    // Method:      Drive
    // Description: This will set the speeds for the left and right sides of the robot.
    //              The range of speeds is between -1.0 (backwards full speed) and 1.0
    //              (forward full speed).  If a value is specified that is outside the
    //              range, the value used will be the closest bounding value (e.g. if 2.0
    //              is passed in and the range is -1.0 to 1.0, 1.0 will be used.
    // Returns:     void
    //----------------------------------------------------------------------------------
    void Drive
    (
        const float leftSpeed,  // <I> - Speed of the left side of the robot (range -1.0 to 1.0)
        const float rightSpeed  // <I> - Speed of the right side of the robot (range -1.0 to 1.0)
    ) const;


    //----------------------------------------------------------------------------------
    // Method:      SetBrakeMode
    // Description: This will set the drive motors to brake mode (true) or coast mode (false)
    // Returns:     void
    //----------------------------------------------------------------------------------
    void SetBrakeMode
    (
        bool        useBrakeMode                // <I> - true  = use brake mode
    ) const;                                    // <I> - false = use coast mode

    //----------------------------------------------------------------------------------
    // Method:      GetLineTrackerState
    // Description: This will the colors detected by the line trackers
    // Returns:     LINE_TRACKER_STATE          see enum definition for the left to right
    //                                          sensor color values detected
    //----------------------------------------------------------------------------------
    LINE_TRACKER_STATE GetLineTrackerState();
    //----------------------------------------------------------------------------------
    // Method:      GetLeftSpeed
    // Description: This will tell the left speed in in/s. Positive measurmets are forward and negative measurements are backward
    // Returns:     float      speed of wheel in in/s
    //----------------------------------------------------------------------------------
    float GetLeftSpeed() const;
    //----------------------------------------------------------------------------------
    // Method:      GetRightSpeed
    // Description: This will tell the right speed in in/s. Positive measurmets are forward and negative measurements are backward
    // Returns:     float      speed of wheel in in/s
    //----------------------------------------------------------------------------------
    float GetRightSpeed() const;
    //----------------------------------------------------------------------------------
    // Method:      GetDistanceToTarget
    // Description: This will tell the distance to an object in ront of the robot
    // Returns:     float      distance to target in in
    //----------------------------------------------------------------------------------
    float GetDistanceToTarget() const;

    //----------------------------------------------------------------------------------
    // Method:      UpdateLineTrackerLights
    // Description: This will update the line tracker lights
    // Returns:     void
    //----------------------------------------------------------------------------------
    void UpdateLineTrackerLights();


private:

    //----------------------------------------------------------------------------------
    // Method:      GetLeftLineTrackerPositionMultiplier
    // Description: This returns the left line tracker position multiplier value
    // Returns:     int     - multiplier
    //----------------------------------------------------------------------------------
    inline int GetLeftLineTrackerPositionMultiplier() const { return 100; }
    //----------------------------------------------------------------------------------
    // Method:      GetCenterLineTrackerPositionMultiplier
    // Description: This returns the center line tracker position multiplier value
    // Returns:     int     - multiplier
    //----------------------------------------------------------------------------------
    inline int GetCenterLineTrackerPositionMultiplier() const { return 10; }

    //----------------------------------------------------------------------------------
    // Method:      GetRightLineTrackerPositionMultiplier
    // Description: This returns the right line tracker position multiplier value
    // Returns:     int     - multiplier
    //----------------------------------------------------------------------------------
    inline int GetRightLineTrackerPositionMultiplier() const { return 1; }

    //----------------------------------------------------------------------------------
    // Method:      Chassis <<Constructor>>
    // Description: Create the motor controllers and set whether they are inverted or not.
    //----------------------------------------------------------------------------------
    Chassis();

    //----------------------------------------------------------------------------------
    // Method:      ~Chassis <<Destructor>>
    // Description: Delete the motor controll
    //----------------------------------------------------------------------------------
    virtual ~Chassis();

    // Drive Motors
    CANTalon*               m_leftMotor;
    CANTalon*               m_rightMotor;

    // TODO:  Add line tracker objects
    LineTracker*            m_rightLineTracker;
    LineTracker*            m_centerLineTracker;
    LineTracker*            m_leftLineTracker;

    // TODO:  If there is a bumper switch in the design add it

    // TODO:  Add DigitalOuput* for the Line Tracker indicators (LED lights)
    DigitalOutput*          m_rightTrackerLED;
    DigitalOutput*          m_centerTrackerLED;
    DigitalOutput*          m_leftTrackerLED;

    // TODO:  Add attribute for navX or Gyro (based on robot design)

    // TODO:  Add attribute to hold whether to use robot or field oriented drive mode


    static Chassis*     m_instance;     // this singleton
    const float m_pi = 3.14159265;
    const float m_diameter = 7.75;
    const float m_countsPerRevolution = 1024;
    const float m_samplingRate = 0.02;
    const float m_gearRatio = 1;

};

#endif /* SRC_DRIVE_CHASSIS_H_ */
