#pragma once


using namespace Windows::Foundation;
using namespace Windows::Devices::Sensors;


//this is what does all the work
namespace kuntakinte
{
	//callback definitions
	public delegate void inclineCallback(const Platform::Array<float>^ data);
	public delegate void gyroCallback(const Platform::Array<float>^ data);

    public ref class flightbox sealed
    {
	private:

		Inclinometer^ inclinometer;
		Gyrometer^ gyrometer;

		//roll pitch and yaw measurement
		double mroll;
		double mpitch;
		double myaw;

		//angular velocity
		float wx;
		float wy;
		float wz;

		//position
		double xpos;
		double ypos;
		double zpos;


		//duty cycle output to motor
		double duty[4];

		//PID gain of roll;
		double kpr; //proportional gain
		double kir; //integral gain
		double kdr; //derivative gain

		//PID gain of pitch;
		double kpp;//p gain
		double kip;//i gain
		double kdp;//d gain

		//PID gain of yaw;
		double kpy;//p gain
		double kiy;//i gain
		double kdy;//d gain

		
		

		//Threads 
		IAsyncAction ^ threadHandle;
		
		

    public:

		//roll pitch yaw float array
		property Platform::Array<float>^ rpy;

		//event interface
		event inclineCallback^ inclineEvent;
		event gyroCallback^ gyroEvent;

        flightbox();
		int calibrate(double roll, double pitch, double yaw);

		//int balance(double roll, double pitch, double yaw);

		int rollPID(double roll);

		int pitchPID(double pitch);

		int yawPID(double yaw);

		

		void OnInclineReadingChanged(Inclinometer ^sender, InclinometerReadingChangedEventArgs ^args);
		void OnGyroReadingChanged(Gyrometer^sender, GyrometerReadingChangedEventArgs^args);
		void OnAccelReadingChanged(Accelerometer ^sender, AccelerometerReadingChangedEventArgs ^args);

		
	};
}