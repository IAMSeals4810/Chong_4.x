/*
 * Control.cpp
 *
 *  Created on: Feb 8, 2016
 *      Author: 1750800404
 */

#include "TeleopControl.h"

/*A Button, 1
B Button, 2
X Button, 3
Y Button, 4
L Button, 5
R Button, 6
Back, 7
Start, 8
Left Stick Button, 9
Right Stick Button 10
Left Analog X Axis, 0
Left Analog Y Axis, 1
Right Analog X Axis, 4
Right Analog Y Axis, 5
Left Trigger Axis, 2
Right Trigger Axis, 3*/

TeleopControl::TeleopControl(){

	cont1 = new Joystick(0);
	cont2 = new Joystick(1);
	l1StickButton = new JoystickButton(cont1, 9);
	l1SToggle = true;
	r1StickButton = new JoystickButton(cont1, 10);
	r1SToggle = true;
	a2Button = new JoystickButton(cont2, 1); //cont2
	a2Toggle = true;
	x2Button = new JoystickButton(cont2, 3);
	x2Toggle = true;
	y2Button = new JoystickButton(cont2, 4);
	y2Toggle = true;
	b2Button = new JoystickButton(cont2, 2); //cont2
	b2Toggle = true;
	r1Bumper = new JoystickButton(cont1, 6);
	r1Toggle = true;
	l1Bumper = new JoystickButton(cont1, 5);
	l1Toggle = true;
	start2Button = new JoystickButton(cont2, 8);
	start2Toggle = true;
	back2Button = new JoystickButton(cont2, 1);
	back2Toggle = true;

	//BUTTON MAPPINGS NEED TO BE DOUBLE CHECKED, LABELLED ON SMARTDASHBOARD

	drive = new DriveSystem();
	shoot = new Shooter();

	sensorOverride = true;
	cameraFlip = false;

	shootOffset = 0;

	//CAMERA STILL NEEDS TO BE CHECKED

	shooting = false;
	shooterLow = false;
	shooterHigh = false;

}

TeleopControl::~TeleopControl(){

	delete cont1;
	delete cont2;
	delete a2Button;
	delete b2Button;
	delete x2Button;
	delete y2Button;
	delete l1StickButton;
	delete r1StickButton;
	delete r1Bumper;
	delete l1Bumper;
	delete start2Button;
	delete back2Button;
	delete drive;
	delete shoot;

}

void TeleopControl::StickDrive(){

	l1StickIn = cont1->GetRawAxis(1);
	r1StickIn = cont1->GetRawAxis(5);
	l1StickScale = (0.7 * l1StickIn); //pow(l1StickIn, 5); 0.77777 -0.07777
	r1StickScale = (0.7 * r1StickIn); //pow(r1StickIn, 5); 0.77777 -0.07777

	if ((l1StickIn < 0.1 && l1StickIn > -0.1) && (r1StickIn >= 0.1 || r1StickIn <= -0.1)){

		drive->Drive(0, r1StickScale);

	}

	else if ((r1StickIn < 0.1 && r1StickIn > -0.1) && (l1StickIn >= 0.1 || l1StickIn <= -0.1)){

		drive->Drive((l1StickScale), 0);

	}

	else if ((l1StickIn > 0.1 || l1StickIn < -0.1) && (r1StickIn > 0.1 || r1StickIn < -0.1)) {

		drive->Drive(l1StickScale, r1StickScale);

	}

	else{

		drive->Drive(0, 0);

	}

	//DOUBLE CHECK JOYSTICK INPUT

}

void TeleopControl::ButtonControl(){

	r2TrigIn = cont2->GetRawAxis(3); //cont1
	r2TrigScale = (r2TrigIn - 0.25) * 1.33;

	if(start2Button->Get() && start2Toggle){
		start2Toggle = false;
		if(sensorOverride){
			sensorOverride = false;
		}

		else{
			sensorOverride = true;
		}

	}

	else if(start2Button->Get() == false){
		start2Toggle = true;
	}

	/*if(r1StickButton->Get() && r1SToggle){
		r1SToggle = false;
		if(drive->casterLow){
			drive->RaiseCasters();
		}

		else{
			drive->LowerCasters();
		}

	}

	else if(r1StickButton->Get() == false){
		r1SToggle = true;
	}

	if(l1StickButton->Get() && l1SToggle){
		l1SToggle = false;
		if(drive->casterLow){
			drive->RaiseCasters();
		}

		else{
			drive->LowerCasters();
		}

	}

	else if(l1StickButton->Get() == false){
		l1SToggle = true;
	}*/

	if(sensorOverride == false){

		if(shoot->raiseShoot->GetEncPosition() < (-1900 + shootOffset) && sensorOverride == false){
			cameraFlip = true;
		}
		else{
			cameraFlip = false;
		} //CHECK THIS WITH ENCODER VALUES

			if(a2Button->Get() && a2Toggle){
				a2Toggle = false;
				if(shooterLow){
					shooterLow = false;
					shoot->LowGoal(0.25, 100);
				}

				else{
					shoot->LowGoal(0.25, 100);
				}

			}

			else if(a2Button->Get() == false){
				a2Toggle = true;
			} //Test this

			if(b2Button->Get() && b2Toggle){
				b2Toggle = false;
				if(shooterHigh){
					shooterHigh = false;
					shoot->HighGoal(0.25, -2000);
				}

				else{
					shoot->HighGoal(0.25, -2000);
				}

			}

			else if(b2Button->Get() == false){
				b2Toggle = true;
			} //Test this

			if(x2Button->Get() && !y2Button->Get()){
				shoot->Lower(0.25);
			}

			else if(y2Button->Get() && !x2Button->Get()){
				shoot->Raise(0.25);
			}

			else{

				shoot->Lower(0.0);

			}

			if(r2TrigIn > 0.25){
				shoot->Pickup(r2TrigScale);
			}

			else{
				shoot->Pickup(0.0);
			}

			if(r1Bumper->Get() && r1Toggle){
				r1Toggle = false;
				if(shooting){
					shooting = false;
					shoot->Shoot(2400, 2400, 1.0);
				}

				else{
					shooting = true;
					shoot->Shoot(2400, 2400, 1.0);
				}

			}

			else if(r1Bumper->Get() == false){
				r1Toggle = true;
			} //Test this

			if(l1Bumper->Get() && l1Toggle){
				l1Toggle = false;
				if(shooting){
					shooting = false;
					shoot->Shoot(1800, 1800, 1.0);
				}

				else{
					shooting = true;
					shoot->Shoot(1800, 1800, 1.0);
				}

			}

			else if(l1Bumper->Get() == false){
				l1Toggle = true;
			} //Test this
	}

	else if(sensorOverride == true){

		if(a2Button->Get() && !b2Button->Get()){
			shoot->LowerNoSense(0.5); //LowerNoSense(0.25)
		}

		else if(b2Button->Get() && !a2Button->Get()){
			shoot->RaiseNoSense(0.5); //RaiseNoSense(0.25)
		}

		else{
			shoot->LowerNoSense(0.0); //Lower(0.0)
		}

		if(r2TrigIn > 0.25){
			shoot->PickupNoSense(r2TrigScale);
		}

		else{
			shoot->PickupNoSense(0.0);
		}

		if(l1Bumper->Get() && l1Toggle){
			l1Toggle = false;
			shoot->ShootNoSense(0.75, 0.75, 1.0);
		}

		else if(l1Bumper->Get() == false){
			l1Toggle = true;
		}

		if(r1Bumper->Get() && r1Toggle){
			r1Toggle = false;
			shoot->ShootNoSense(1.0, 1.0, 1.0);
		}

		else if(r1Bumper->Get() == false){
			r1Toggle = true;
		} //Test this

		if(back2Button->Get() && back2Toggle){
			back2Toggle = false;
			if(cameraFlip){
				cameraFlip = false;
			}

			else{
				cameraFlip = true;
			}
		}

		else if(back2Button->Get() == false){
			back2Toggle = true;
		} //Test this
	}

}

void TeleopControl::DashPlace(){

	SmartDashboard::PutNumber("Left Stick Y Raw", l1StickIn);
	SmartDashboard::PutNumber("Left Stick Y Scaled", l1StickScale);
	SmartDashboard::PutNumber("Right Stick Y Raw", r1StickIn);
	SmartDashboard::PutNumber("Right Stick Y Scaled", r1StickScale);
	SmartDashboard::PutBoolean("Sensor Override On:", sensorOverride);
	SmartDashboard::PutNumber("Pickup Trigger Raw", r2TrigIn);
	SmartDashboard::PutNumber("Pickup Trigger Scale", r2TrigScale);
	SmartDashboard::PutNumber("Shooter Angle", shoot->raiseShoot->GetEncPosition());
	//SmartDashboard::PutNumber("Left Rotor", shoot->ReadRPM(shoot->lBanner, shoot->rpmTimerL, shoot->lRPMReading));
	//SmartDashboard::PutNumber("Right Rotor", shoot->ReadRPM(shoot->rBanner, shoot->rpmTimerR, shoot->rRPMReading));
	SmartDashboard::PutBoolean("Ball?", shoot->DetectBall());
	SmartDashboard::PutBoolean("Camera Flipped?", cameraFlip);

}
