// kuntakinte.cpp
#include "pch.h"
#include "kuntakinte.h"

using namespace kuntakinte;
using namespace Platform;

//namespace required to support sensor and events
using namespace Windows::Devices::Sensors;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;

using namespace Windows::Foundation::Collections;

//namespace for UI control
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;


#define ROLL	0
#define PITCH	1
#define YAW		2




flightbox::flightbox()
{

	//get inclinometer
	inclinometer = Inclinometer::GetDefault();	
	inclinometer->ReportInterval = inclinometer->MinimumReportInterval;	
	inclinometer->ReadingChanged::add(ref new TypedEventHandler<Inclinometer ^, InclinometerReadingChangedEventArgs ^>(this, &flightbox::OnInclineReadingChanged));

	//get gyroscope
	gyrometer = Gyrometer::GetDefault();
	gyrometer->ReportInterval = gyrometer->MinimumReportInterval;
	gyrometer->ReadingChanged::add(ref new TypedEventHandler<Gyrometer^, GyrometerReadingChangedEventArgs^>(this, &flightbox::OnGyroReadingChanged));	

	//get accelerometer
	accelerometer = Accelerometer::GetDefault();
	accelerometer->ReportInterval = 100;
	accelerometer->ReadingChanged::add(ref new TypedEventHandler<Accelerometer ^, AccelerometerReadingChangedEventArgs ^>(this, &flightbox::OnAccelReadingChanged));
	
	tick = inclinometer->ReportInterval/1000.0;

	//set PID gain of roll loop
	rollGain[0] = 0.5;
	rollGain[1] = 0.01;
	rollGain[2] = 1;
	//set PID gain of pitch loop
	pitchGain[0] = 0.5;
	pitchGain[1] = 0.01;
	pitchGain[2] = 1;

	//set PID gain of yaw loop
	yawGain[0] = 1;
	yawGain[1] = 1;
	yawGain[2] = 1;
	
	//initialize rpy array
	rpy = ref new Platform::Array<float>(3);
	//init position array
	position = ref new Platform::Array<float>(3);
	//init motors array
	motors = ref new Platform::Array<int>(4);

	
}

int flightbox::calibrate(float roll, float pitch, float yaw){

	//set calibration value if there is offset
	this->mroll = roll;
	this->mpitch = pitch;
	this->myaw = yaw;

	return 0;

	
}

int flightbox::rollPID(float roll){
	return 0;
}

int flightbox::pitchPID(float roll){
	return 0;
}

int flightbox::yawPID(float yaw){
	return 0;
}


void flightbox::OnInclineReadingChanged(Inclinometer ^sender, InclinometerReadingChangedEventArgs ^args)
{

	//roll and pitch goes from -180 to 180
	//integrate roll; running sum
	rpyint[ROLL] += (rpy[ROLL] + args->Reading->RollDegrees) / 2 * tick;
	//integrate pitch
	rpyint[PITCH] += (rpy[PITCH] + args->Reading->PitchDegrees) / 2 * tick;
	//integrate yaw
	//yaw goes from 0 to 360 NEED TO ACCOUNT FOR THIS //////////////////////
	

	rpy[0] = args->Reading->RollDegrees;
	rpy[1] = args->Reading->PitchDegrees;
	rpy[2] = args->Reading->YawDegrees;


	int offset = 1090;
	//calculate PI for roll
	motors[0] = rollGain[0] * rpy[ROLL] + rollGain[1] * rpyint[ROLL];
	motors[2] = offset-motors[0];
	motors[0] += offset;

	//calculate PI for pitch
	motors[1] = pitchGain[0] * rpy[PITCH] + pitchGain[1] * rpyint[PITCH];
	motors[3] = offset-motors[1];
	motors[1] += offset;

	//calculate PI for yaw


	//throw ref new Platform::NotImplementedException();
	inclineEvent(rpy);
	motorEvent(motors);
	
	
}

void flightbox::OnGyroReadingChanged(Gyrometer^sender, GyrometerReadingChangedEventArgs ^args){
	/*
	wx = args->Reading->AngularVelocityX;
	wy = args->Reading->AngularVelocityY;
	wz = args->Reading->AngularVelocityZ;
	
	*/
	
}


void flightbox::OnAccelReadingChanged(Accelerometer ^sender, AccelerometerReadingChangedEventArgs ^args)
{

	float foo = args->Reading->AccelerationX;
	if (foo < 0.01&&foo>-0.01)
		foo = 0;

	vx1 = vx0;
	vx0 += (ax + foo) / 2 * (tick);
	
	ax = foo;

	position[0] =vx0;
	//position[0] = args->Reading->AccelerationZ;
	//accelEvent(position);
	//throw ref new Platform::NotImplementedException();
}
