/*
 * Control.cpp
 *
 *  Created on: Feb 8, 2016
 *      Author: 1750800404
 */

#include "TeleopControl.h"

TeleopControl::TeleopControl(){

	lStick = new Joystick(0);
	rStick = new Joystick(1);
	drive = new DriveSystem();

}

TeleopControl::~TeleopControl(){

	delete lStick;
	delete rStick;
	delete drive;

}

void TeleopControl::StickDrive(){

	lStickIn = lStick->GetY();
	rStickIn = rStick->GetY();
	lStickScale = pow(lStickIn, 5);
	rStickScale = pow(rStickIn, 5);

	if (lStickIn <= 0.5 && lStickIn >= -0.5){

		drive->Drive(0, rStickScale);

	}

	if (rStickIn <= 0.5 && rStickIn >= -0.5){

		drive->Drive(lStickScale, 0);

	}

	if ((lStickIn > 0.5 || lStickIn < -0.5) && (rStickIn > 0.5 || rStickIn < -0.5)) {

		drive->Drive(lStickScale, rStickScale);

	}

}

void TeleopControl::ButtonControl(){

}

void TeleopControl::TriggerControl(){

}
