#pragma once


using namespace Windows::Foundation;
using namespace Windows::Devices::Sensors;


//this is what does all the work
namespace kuntakinte
{
	//callback definitions
	public delegate void inclineCallback(const Platform::Array<float>^ data);
	public delegate void gyroCallback(const Platform::Array<float>^ data);
	public delegate void accelCallback(const Platform::Array<float>^ data);

    public ref class flightbox sealed
    {
	private:

		Inclinometer^ inclinometer;
		Gyrometer^ gyrometer;

		//roll pitch and yaw measurement
		float mroll;
		float mpitch;
		float myaw;

		//angular velocity
		float wx;
		float wy;
		float wz;

		//time
		float tick;

		//acceleration
		float ax;
		float ay;
		float az;

		//velocity
		float vx0;
		float vy0;
		float vz0;

		float vx1;
		float vy1;
		float vz1;

		//position
		float xpos;
		float ypos;
		float zpos; 


		//duty cycle output to motor
		float duty[4];

		//PID gain of roll;
		float kpr; //proportional gain
		float kir; //integral gain
		float kdr; //derivative gain

		//PID gain of pitch;
		float kpp;//p gain
		float kip;//i gain
		float kdp;//d gain

		//PID gain of yaw;
		float kpy;//p gain
		float kiy;//i gain
		float kdy;//d gain

		
		

		//Threads 
		IAsyncAction ^ threadHandle;
		
		

    public:

		//roll pitch yaw float array
		property Platform::Array<float>^ rpy;
		property Platform::Array<float>^ position;

		//event interface
		event inclineCallback^ inclineEvent;
		event gyroCallback^ gyroEvent;
		event accelCallback^ accelEvent;

        flightbox();
		int calibrate(float roll, float pitch, float yaw);

		//int balance(double roll, double pitch, double yaw);

		int rollPID(float roll);

		int pitchPID(float pitch);

		int yawPID(float yaw);

		

		void OnInclineReadingChanged(Inclinometer ^sender, InclinometerReadingChangedEventArgs ^args);
		void OnGyroReadingChanged(Gyrometer^sender, GyrometerReadingChangedEventArgs^args);
		void OnAccelReadingChanged(Accelerometer ^sender, AccelerometerReadingChangedEventArgs ^args);

		
	};
}