/*
 * Shooter.cpp
 *
 *  Created on: Feb 9, 2016
 *      Author: 1750800404
 */

#include "Shooter.h"

Shooter::Shooter(){

	raiseShoot = new CANTalon(7); //4
	raiseShoot->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute); //FINISH
	//Needs to be checked, documentation has relative and absolute with opposite descriptions

	lShooter = new CANTalon(5); //1
	rShooter = new CANTalon (6); //2
	lBanner = new DigitalInput(1);
	rBanner = new DigitalInput(2);

	picker = new CANTalon(8); //3

	shootSol = new Solenoid(1, 0);

	ballSense = new DigitalInput(3); //0

	rpmTimerL = new Timer();
	rpmTimerR = new Timer();

	shooterRestLimit = 100; //CHECK
	shooterTopLimit = -3600; //CHECK
	shooterOffset = 0;

	lRPMReading = 0;
	rRPMReading = 0;

	UpLimit = new DigitalInput(4);
	DownLimit = new DigitalInput(5);

}

Shooter::~Shooter(){

	delete raiseShoot;
	delete lShooter;
	delete rShooter;
	delete lBanner;
	delete rBanner;

	delete picker;

	delete shootSol;

	delete ballSense;

	delete rpmTimerL;
	delete rpmTimerR;

	delete UpLimit;
	delete DownLimit;

}

bool Shooter::DetectBall(){

	bool ball;

	if(ballSense->Get()){
		ball = true;
	}

	else{
		ball = false;
	}

	return ball;

}

void Shooter::Pickup(float speed){

	if(DetectBall() == false){
		picker->Set(speed);
		lShooter->Set(-(speed/1.5));
		rShooter->Set(speed/1.5);
	}

	else{
		picker->Set(0.0);
		lShooter->Set(0.0);
		rShooter->Set(0.0);
	}

	DetectBall();

}

void Shooter::PickupNoSense(float speed){
		picker->Set(speed);
		lShooter->Set(-(speed/1.5));
		rShooter->Set(speed/1.5);
}

void Shooter::Raise(float speed){

	if(UpLimit->Get() == true){ //raiseShoot->GetEncPosition() > shooterTopLimit
		raiseShoot->Set(-speed);
	}

	else{
		raiseShoot->Set(0.0);
	}

}

void Shooter::RaiseNoSense(float speed){
		raiseShoot->Set(-speed);
}

void Shooter::Lower(float speed){

	if(DownLimit->Get() == true){ //raiseShoot->GetEncPosition() < shooterRestLimit
		raiseShoot->Set(speed);
	}

	else{
		raiseShoot->Set(0.0);
	}

}

void Shooter::LowerNoSense(float speed){
		raiseShoot->Set(speed);
}

void Shooter::HighGoal(float speed, int encoVal){

	if(raiseShoot->GetEncPosition() < encoVal){
		raiseShoot->Set(speed);
	}

	else if (raiseShoot->GetEncPosition() > encoVal){
		raiseShoot->Set(-speed);
	}

}

void Shooter::LowGoal(float speed, int encoVal){

	if(raiseShoot->GetEncPosition() < encoVal){
		raiseShoot->Set(speed);
	}

	else if (raiseShoot->GetEncPosition() > encoVal){
		raiseShoot->Set(-speed);
	}

}

float Shooter::ReadRPM(DigitalInput *banner, Timer *Minute, float rpmReading){

	bool bannerToggle = true;
	int reads = 0;

	Minute->Reset();
	Minute->Start();

	while(Minute->Get() <= 0.05){

		if(banner->Get() == false && bannerToggle){
			bannerToggle = false;
			reads++;
		}

		else if(banner->Get()){
			bannerToggle = true;
		} //Test this

	}

	Minute->Stop();

	rpmReading = reads * 400; //1200

	return rpmReading;

}

void Shooter::Shoot(int leftRPM, int rightRPM, float rollPow){

	lShooter->Set(0.1);
	rShooter->Set(-0.1);
	picker->Set(rollPow);

	if(leftRPM > 2400){
		leftRPM = 2400;
	}

	if(rightRPM > 2400){
		rightRPM = 2400;
	}

	for(int lPow = 0.1; ReadRPM(lBanner, rpmTimerL, lRPMReading) < (leftRPM - 200) || lPow <= 1.0; lPow += 0.1){
		lShooter->Set(lPow);
	}

	for(int rPow = 0.1; ReadRPM(rBanner, rpmTimerR, rRPMReading) < (rightRPM - 200) || rPow <= 1.0; rPow -= 0.1){
		rShooter->Set(-rPow);
	}

	shootSol->Set(true);
	Wait(1.0);
	shootSol->Set(false);

	lShooter->Set(0.0);
	rShooter->Set(0.0);
	picker->Set(0.0);

}

void Shooter::ShootNoSense(float leftPow, float rightPow, float rollPow){

	lShooter->Set(leftPow);
	rShooter->Set(-rightPow);
	picker->Set(-rollPow);
	Wait(0.5);
	shootSol->Set(true);
	Wait(0.5);
	shootSol->Set(false);
	lShooter->Set(0.0);
	rShooter->Set(0.0);
	picker->Set(0.0);

}
