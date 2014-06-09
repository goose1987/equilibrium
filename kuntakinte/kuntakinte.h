#pragma once
#include "PID.h"

using namespace Windows::Foundation;
using namespace Windows::Devices::Sensors;
using namespace Windows::Networking::Sockets;
using namespace Windows::Storage::Streams;
using namespace Windows::Networking::Proximity;


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


		StreamSocket^ socket;
		DataWriter^ dataWriter;


		Inclinometer^ inclinometer;
		Gyrometer^ gyrometer;
		Accelerometer^ accelerometer;

		//roll pitch and yaw measurement
		float mroll;
		float mpitch;
		float myaw;

		//angular velocity
	
		//time
		float tickgyro;
		float tickincline;
		float tickaccel;

		//acceleration
		

		//velocity
		

		//position
		


		float *attitude;

		//duty cycle output to motor
		float duty[4];

		//PID gain of roll;
		float rollGain[3];
		
		float rollRateG[3];

		//PID gain of pitch;
		float pitchGain[3];
		float pitchRateG[3];

		//PID gain of yaw;
		float yawGain[3];

		//integral rpy
		float rpyint[3];

		
		//integral of angular velocity
		float omegaint[3];

		//Threads 
		IAsyncAction ^ threadHandle;
		
		
		float cmdRollRate;
		float cmdPitchRate;

		float rollE;
		float pitchE;
		
		float rollEint;
		float pitchEint;

		float rollRateE;
		float pitchRateE;

		float rollRateEint;
		float pitchRateEint;


		float fault;

		float rollsetpoint;
		float pitchsetpoint;
		float yawsetpoint;

		float zsetpoint;

		float mthrottle;

		float m3;
		float m5;
		float m6;
		float m9;

		float wr;
		float wp;
		float wy;

		float yawcomp;
		float rollcomp;
		float pitchcomp;

		float zcomp;
		/*
		PID* m3pid;
		PID* m5pid;
		PID* m6pid;
		PID* m9pid;
		*/

		PID* wrpid;
		PID* wppid;
		PID* wypid;

		PID* rollpid;
		PID* pitchpid;
		PID* yawpid;

		PID* zpid;
		
		
    public:

		//angular velocity array
		property Platform::Array<float>^ omega;

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



		void throttle(float incr);

		void setz(float zaccel);

		Platform::Array<int>^ compensate(const Platform::Array<float>^ sensors);

		void OnGyroReadingChanged(Gyrometer^sender, GyrometerReadingChangedEventArgs^args);
		


	};
}