/*
 * Shooter.cpp
 *
 *  Created on: Feb 9, 2016
 *      Author: 1750800404
 */

#include "Shooter.h"

Shooter::Shooter(){

	raiseShoot = new CANTalon(4);
	raiseShoot->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
	//Needs to be checked, documentation has relative and absolute with opposite descriptions

	lShooter = new CANTalon(5);
	lShooter->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	rShooter = new CANTalon (6);
	rShooter->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);

	picker = new CANTalon(7);

	shootSol = new Solenoid(0, 1);

	usOut = new DigitalOutput(0);
	usIn = new DigitalInput(1);
	ballSense = new Ultrasonic(usOut, usIn, Ultrasonic::kInches);

	shooterRestVal = 100;
	shooterTopVal = 1000;

}

Shooter::~Shooter(){

	delete raiseShoot;
	delete lShooter;
	delete rShooter;
	delete picker;

	delete shootSol;

	delete usOut;
	delete usIn;
	delete ballSense;

}

bool Shooter::DetectBall(){

	bool ball;

	if(ballSense->GetRangeInches() <= 1.0){
		ball = true;
	}

	else{
		ball = false;
	}

	return ball;

}

void Shooter::Pickup(){

	if(raiseShoot->GetEncPosition() == shooterRestVal && DetectBall() == false){
		picker->Set(1.0);
	}

	else{
		picker->Set(0.0);
	}

	DetectBall();

}

void Shooter::Raise(float speed){

	if(raiseShoot->GetEncPosition() < shooterTopVal){
		raiseShoot->Set(speed);
	}

	else{
		raiseShoot->Set(0.0);
	}

}

void Shooter::Lower(float speed){

	if(raiseShoot->GetEncPosition() > shooterRestVal){
		raiseShoot->Set(-speed);
	}

	else{
		raiseShoot->Set(0.0);
	}

}

void Shooter::Shoot(float leftRPM, float rightRPM){

	int lPow = 0.1;
	int rPow = 0.1;

	if(leftRPM > 5500 && rightRPM > 5500){
		leftRPM = 5500;
		rightRPM = 5500;
	}

	while(lShooter->GetEncVel() < leftRPM){
		lShooter->Set(lPow);
		lPow += 0.05;
	}

	while(rShooter->GetEncVel() < rightRPM){
		rShooter->Set(rPow);
		rPow += 0.05;
	}

	shootSol->Set(true);
	Wait(1.0);
	shootSol->Set(false);

	/*lShooter->Set(left);
	rShooter->Set(right);
	Wait(1.0);
	shootSol->Set(true);
	Wait(1.0);
	shootSol->Set(false);*/

}
