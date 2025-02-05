/*
 * Shooter.h
 *
 *  Created on: Feb 9, 2016
 *      Author: 1750800404
 */

#ifndef SHOOTER_H
#define SHOOTER_H

#include "CANTalon.h"
#include "Solenoid.h"
#include "DigitalInput.h"
#include "Timer.h"

class Shooter{

public:

	Shooter();
	~Shooter();

	CANTalon *raiseShoot;

	bool DetectBall();
	void Pickup(float speed);
	void PickupNoSense(float speed);
	void Raise(float speed);
	void RaiseNoSense(float speed);
	void Lower(float speed);
	void LowerNoSense(float speed);
	void HighGoal(float speed, int encoVal);
	void LowGoal(float speed, int encoVal);
	float ReadRPM(DigitalInput *banner, Timer *Minute, float rpmReading);
	void Shoot(int leftRPM, int rightRPM, float rollPow);
	void ShootNoSense(float leftPow, float rightPow, float rollPow);

	float lRPMReading;
	float rRPMReading;
	DigitalInput *lBanner;
	DigitalInput *rBanner;
	Timer *rpmTimerL;
	Timer *rpmTimerR;

	DigitalInput *UpLimit;
	DigitalInput *DownLimit;

	int shootOffset;

private:

	CANTalon *lShooter;
	CANTalon *rShooter;
	CANTalon *picker;

	Solenoid *shootSol;

	DigitalInput *ballSense;

	int shooterOffset;
	int shooterRestLimit;
	int shooterTopLimit;

protected:

};

#endif /* SRC_SHOOTER_H_ */
