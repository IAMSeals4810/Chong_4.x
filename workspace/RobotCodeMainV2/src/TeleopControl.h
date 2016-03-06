/*
 * Control.h
 *
 *  Created on: Feb 8, 2016
 *      Author: 1750800404
 */

#ifndef TELEOPCONTROL_H
#define TELEOPCONTROL_H

#include "Joystick.h"
#include "Buttons/JoystickButton.h"
#include "SmartDashboard/SmartDashboard.h"
#include "DriveSystem.h"
#include "Shooter.h"

class TeleopControl{

public:
	TeleopControl();
	~TeleopControl();

	void StickDrive();
	void ButtonControl();
	void DashPlace();

	bool cameraFlip;
	//Image *camImage;

	friend class Robot;

private:

	Joystick *cont1;
	Joystick *cont2;
	JoystickButton *a2Button;
	bool a2Toggle;
	JoystickButton *b2Button;
	bool b2Toggle;
	JoystickButton *r1Bumper;
	bool r1Toggle;
	JoystickButton *l1Bumper;
	bool l1Toggle;
	JoystickButton *x2Button;
	bool x2Toggle;
	JoystickButton *y2Button;
	bool y2Toggle;

	JoystickButton *l1StickButton;
	bool l1SToggle;
	JoystickButton *r1StickButton;
	bool r1SToggle;

	JoystickButton *start2Button;
	bool start2Toggle;

	JoystickButton *back2Button;
	bool back2Toggle;

	DriveSystem *drive;
	Shooter *shoot;

	float l1StickIn;
	float r1StickIn;

	float l1StickScale;
	float r1StickScale;

	float r2TrigIn;
	float r2TrigScale;

	int shootOffset;

	bool sensorOverride;

	bool shooting;
	bool shooterLow;
	bool shooterHigh;

protected:

};

#endif /* SRC_CONTROL_H_ */
