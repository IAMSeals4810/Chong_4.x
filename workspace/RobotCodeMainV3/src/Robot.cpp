#include "WPILib.h"
#include "TeleopControl.h"



class Robot: public IterativeRobot
{

private:
	LiveWindow *lw = LiveWindow::GetInstance();
	SendableChooser *chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;

	TeleopControl cont;
	int x;
	//Image *camImage;
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
		chooser = new SendableChooser();
		chooser->AddDefault(autoNameDefault, (void*)&autoNameDefault);
		chooser->AddObject(autoNameCustom, (void*)&autoNameCustom);
		SmartDashboard::PutData("Auto Modes", chooser);

		CameraServer::GetInstance()->SetQuality(50);
		//the camera name (ex "cam0") can be found through the roborio web interface
		CameraServer::GetInstance()->StartAutomaticCapture("cam1");

		//camImage = imaqCreateImage(IMAQ_IMAGE_RGB, 0);

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
		autoSelected = *((std::string*)chooser->GetSelected());
		//std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if(autoSelected == autoNameCustom){
			//Custom Auto goes here
		} else {
			//Default Auto goes here
		}
	}

	void AutonomousPeriodic()
	{
		if(autoSelected == autoNameCustom){
			//Custom Auto goes here
			cont.shoot->LowerNoSense(0.75);
			Wait(1.5);
			cont.shoot->LowerNoSense(0.0);
			Wait(1.0);
			cont.drive->Drive(-0.75, -0.75);
			Wait(3.0);
			cont.drive->Drive(0.0, 0.0);
			Wait(15.0);
		} else {
			//Default Auto goes here
			cont.shoot->LowerNoSense(0.75);
			Wait(1.5);
			cont.shoot->LowerNoSense(0.0);
			Wait(1.0);
			cont.drive->Drive(-0.75, -0.75);
			Wait(3.0);
			cont.drive->Drive(0.0, 0.0);
			Wait(15.0);
		}
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
