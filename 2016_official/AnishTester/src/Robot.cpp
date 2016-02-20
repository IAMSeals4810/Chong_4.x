#include "WPILib.h"
#include "NIVision.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw = LiveWindow::GetInstance();
	SendableChooser *chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	const std::string genericErrorMessage = "You fucked up";
	std::string autoSelected;
	IMAQdxSession session;
	IMAQdxError imaqError;
	Image* frame;

	void RobotInit()
	{
		chooser = new SendableChooser();
		chooser->AddDefault(autoNameDefault, (void*)&autoNameDefault);
		chooser->AddObject(autoNameCustom, (void*)&autoNameCustom);
		SmartDashboard::PutData("Auto Modes", chooser);
		if(!CameraInit()){
			SmartDashboard::PutString("Error message", genericErrorMessage);
		}
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
		} else {
			//Default Auto goes here
		}
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		IMAQdxGrab(session, frame, true, NULL);
		if(imaqError != IMAQdxErrorSuccess){
			DriverStation::ReportError("IMAQdxGrab error: " + std::to_string((long)imaqError) + "\n");
		}else{
			CameraServer::GetInstance()->SetImage(frame);
		}

		Wait(0.005); //refresh thingy i suppose
	}

	void TestPeriodic()
	{
		lw->Run();
	}

	bool CameraInit(){
		//create a frame
		frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
		imaqError = IMAQdxOpenCamera("cam0", IMAQdxCameraControlModeController, &session);
		if(imaqError != IMAQdxErrorSuccess){
			DriverStation::ReportError("IMAQdxOpenCamera error: " + std::to_string((long)imaqError) + "\n");
			return false;
		}
		imaqError = IMAQdxConfigureGrab(session);
		if(imaqError != IMAQdxErrorSuccess){
			DriverStation::ReportError("IMAQdxGrabController error: " + std::to_string((long)imaqError) + "\n");
			return false;
		}

		return true;
	}
};

START_ROBOT_CLASS(Robot)
