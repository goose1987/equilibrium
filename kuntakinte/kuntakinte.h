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
	public delegate void motorCallback(const Platform::Array<int>^ data);

    public ref class flightbox sealed
    {
	private:

		Inclinometer^ inclinometer;
		Gyrometer^ gyrometer;
		Accelerometer^ accelerometer;

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
		float rollGain[3];
		

		//PID gain of pitch;
		float pitchGain[3];

		//PID gain of yaw;
		float yawGain[3];

		//integral rpy
		float rpyint[3];

		//Threads 
		IAsyncAction ^ threadHandle;
		
	

    public:

		//roll pitch yaw float array
		property Platform::Array<float>^ rpy;
		//position array
		property Platform::Array<float>^ position;
		//motor array
		property Platform::Array<int>^ motors;

		//event interface
		event inclineCallback^ inclineEvent;
		event gyroCallback^ gyroEvent;
		event accelCallback^ accelEvent;
		event motorCallback^ motorEvent;

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