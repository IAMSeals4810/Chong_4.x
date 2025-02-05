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
#include "DigitalOutput.h"
#include "DigitalInput.h"
#include "Ultrasonic.h"
#include "Timer.h"

class Shooter{

public:

	Shooter();
	~Shooter();

	bool DetectBall();
	void Pickup();
	void Raise(float speed);
	void Lower(float speed);
	void Shoot(float leftRPM, float rightRPM);


private:

	CANTalon *raiseShoot;
	CANTalon *lShooter;
	CANTalon *rShooter;
	CANTalon *picker;

	Solenoid *shootSol;

	DigitalOutput *usOut;
	DigitalInput *usIn;
	Ultrasonic *ballSense;

	int shooterRestVal;
	int shooterTopVal;

protected:

};

#endif /* SRC_SHOOTER_H_ */
