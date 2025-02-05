#include "WPILib.h"
#include "TeleopControl.h"


class Robot: public IterativeRobot
{

private:
	LiveWindow *lw = LiveWindow::GetInstance();

	TeleopControl cont;
	int x;
	//double speed;
	//DigitalInput *banner;
	//DigitalInput *banner2;
	//CANTalon *tal;

	~Robot(){

		//delete banner;
		//delete banner2;
		//delete tal;

	}

	void RobotInit()
	{

		CameraServer::GetInstance()->SetQuality(50);
		//the camera name (ex "cam0") can be found through the roborio web interface
		CameraServer::GetInstance()->StartAutomaticCapture("cam1");

		//tal = new CANTalon(1);
		//banner = new DigitalInput(4);
		//banner2 = new DigitalInput(5);
		//tal->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
		x = 0;
	}


	/**
	 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
	 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
	 * Dashboard, remove all of the chooser code and uncomment the GetString line to get the auto name from the text box
	 * below the Gyro
	 *
	 * You can add additional auto modes by adding additional comparisons to the if-else structure below with additional strings.
	 * If using the SendableChooser make sure to add them to the chooser code above as well.
	 */
	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{

		cont.StickDrive();
		cont.ButtonControl();
		cont.DashPlace();


		//imaqFlip(camImage, camImage, FlipAxis::IMAQ_HORIZONTAL_AXIS);

		/*for(double i = 0.1; i <= 0.5; i+=0.05){
			tal->Set(i);
			SmartDashboard::PutNumber("RPM", cont.shoot->ReadRPM(banner, cont.shoot->rpmTimerL, x));
			Wait(0.1);
		}

		for(double i = 0.5; i >= 0.1; i-=0.05){
			tal->Set(i);
			SmartDashboard::PutNumber("RPM", cont.shoot->ReadRPM(banner, cont.shoot->rpmTimerL, x));
			Wait(0.1);
		}

		while(speed <= 1.0){
			tal->Set(speed);
			SmartDashboard::PutNumber("RPM", cont.shoot->ReadRPM(banner, cont.shoot->rpmTimerL, x));
			Wait(0.25);
			speed += 0.05;
		}

		while(speed >= 0.0){
			tal->Set(speed);
			SmartDashboard::PutNumber("RPM", cont.shoot->ReadRPM(banner, cont.shoot->rpmTimerL, x));
			Wait(0.25);
			speed -= 0.05;
		}

		tal->Set(1.0);

		SmartDashboard::PutNumber("RPM", cont.shoot->ReadRPM(banner, cont.shoot->rpmTimerL, x));*/

		//SmartDashboard::PutNumber("encoder", tal->GetEncPosition());
		//SmartDashboard::PutBoolean("Banner", banner->Get());
		//SmartDashboard::PutBoolean("Banner2", banner2->Get());

		Wait(0.001);

	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
