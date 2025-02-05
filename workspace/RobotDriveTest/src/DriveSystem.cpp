/*
 * DriveSystem.cpp
 *
 *  Created on: Feb 7, 2016
 *      Author: 1750800404
 */

#include "DriveSystem.h"

DriveSystem::DriveSystem(){
	flTal = new CANTalon(0);
	rlTal = new CANTalon(1);
	frTal = new CANTalon(2);
	rrTal = new CANTalon(3);
	roboDrive = new RobotDrive(flTal, rlTal, frTal, rrTal);
	//Ask about which Talons have to be reversed
	//roboDrive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);

	caster = new Solenoid(0, 0);
}

DriveSystem::~DriveSystem(){
	delete flTal;
	delete rlTal;
	delete frTal;
	delete rrTal;
	delete roboDrive;

	delete caster;

}


void DriveSystem::Drive(float left, float right){

	roboDrive->TankDrive(left, right, false);

}

void DriveSystem::LowerCasters(){

	if(casterLow == false){

		caster->Set(false);
		casterLow = true;

	}

}

void DriveSystem::RaiseCasters(){

	if(casterLow == true){

		caster->Set(true);
		casterLow = false;

	}

}
