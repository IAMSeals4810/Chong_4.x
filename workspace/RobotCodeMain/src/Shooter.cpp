/*
 * Shooter.cpp
 *
 *  Created on: Feb 9, 2016
 *      Author: 1750800404
 */

#include "Shooter.h"

Shooter::Shooter(){

	raiseShoot = new CANTalon(4); //7 (CHECK)
	raiseShoot->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute); //FINISH
	//Needs to be checked, documentation has relative and absolute with opposite descriptions

	lShooter = new CANTalon(1); //5 (CHECK)
	rShooter = new CANTalon (2); //6 (CHECK)
	lBanner = new DigitalInput(0);
	rBanner = new DigitalInput(2);

	picker = new CANTalon(3);

	shootSol = new Solenoid(1, 0);

	ballSense = new DigitalInput(0);

	rpmTimerL = new Timer();
	rpmTimerR = new Timer();

	shooterRestLimit = 100; //CHECK
	shooterTopLimit = -3600; //CHECK
	shooterOffset = 0;

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

	if(raiseShoot->GetEncPosition() > shooterTopLimit){
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

	if(raiseShoot->GetEncPosition() < shooterRestLimit){
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

int Shooter::ReadRPM(DigitalInput *banner, Timer *Minute, int rpmReading){

	bool bannerToggle = true;
	int reads = 0;

	Minute->Reset();
	Minute->Start();

	while(Minute->Get() <= 1.0){

		if(banner->Get() == false && bannerToggle){
			bannerToggle = false;
			reads++;
		}

		else if(banner->Get()){
			bannerToggle = true;
		} //Test this

	}

	/*for(int x = 0; x < 3; ){

		if(banner->Get() == false && bannerToggle){
			bannerToggle = false;
			x += 1;
		}

		else if(banner->Get()){
			bannerToggle = true;
		} //Test this

	}*/

	Minute->Stop();
	double seconds = Minute->Get();

	rpmReading = reads * 60;

	return rpmReading;

}

void Shooter::Shoot(int leftRPM, int rightRPM, float rollPow){

	int lPow = 0.1;
	int rPow = 0.1;

	if(leftRPM > 3800 && rightRPM > 3800){
		leftRPM = 3800;
		rightRPM = 3800;
	}

	while(ReadRPM(lBanner, rpmTimerL, lRPMReading) < (leftRPM - 200)){
		lShooter->Set(lPow);
		lPow += 0.05;
	}

	while(ReadRPM(rBanner, rpmTimerR, rRPMReading) < (rightRPM - 200)){
		rShooter->Set(rPow);
		rPow += 0.05;
	}

	shootSol->Set(true);
	Wait(1.0);
	shootSol->Set(false);

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
