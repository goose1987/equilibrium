// kuntakinte.cpp
#include "pch.h"
#include "kuntakinte.h"

#include <string.h>

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
	
	gyrometer = Gyrometer::GetDefault();
	//gyrometer->ReportInterval = gyrometer->MinimumReportInterval;
	gyrometer->ReportInterval = 5;

	gyrometer->ReadingChanged::add(ref new TypedEventHandler<Gyrometer^, GyrometerReadingChangedEventArgs^>(this, &flightbox::OnGyroReadingChanged));

	//init omega array
	omega = ref new Platform::Array<float>(3);
	//initialize rpy array
	rpy = ref new Platform::Array<float>(3);
	//init position array
	position = ref new Platform::Array<float>(3);
	//init motors array
	motors = ref new Platform::Array<int>(4);


	mthrottle = 1000;

	cmdRollRate = 0;
	cmdPitchRate = 0;
	
	rollRateE = 0;
	rollRateEint = 0;
	
	pitchRateE = 0;
	pitchRateEint = 0;

	fault = 0;

	attitude = new float[3];

	mroll = 0;

	rollsetpoint = 0;
	pitchsetpoint = 0;
	yawsetpoint = 0;

	/*
	m9pid = new PID(&attitude[ROLL], &m9, &rollsetpoint, (float)26, (float)8 ,(float)16, REVERSE);
	m3pid = new PID(&attitude[ROLL], &m3, &rollsetpoint, (float)26, (float)8, (float)16, DIRECT);

	m5pid = new PID(&attitude[PITCH], &m5, &pitchsetpoint, (float)26, (float)8, (float)16, REVERSE);
	m6pid = new PID(&attitude[PITCH], &m6, &pitchsetpoint, (float)26, (float)8, (float)16, DIRECT);
	*/

	rollpid = new PID(&attitude[ROLL], &rollcomp, &rollsetpoint, (float)60, (float)20, (float)10, DIRECT);
	pitchpid = new PID(&attitude[PITCH], &pitchcomp, &pitchsetpoint, (float)60, (float)20, (float)10, DIRECT);
	//yawpid = new PID(&attitude[YAW], &wy, &yawsetpoint, (float)50, (float)1, (float)0, DIRECT);

	wrpid = new PID(&omega[ROLL], &rollcomp, &wr, (float)1, (float)0, (float)0, DIRECT);
	wppid = new PID(&omega[PITCH], &pitchcomp, &wp, (float)0, (float)0, (float)0, DIRECT);
	wypid = new PID(&omega[YAW], &yawcomp, &yawsetpoint, (float)1, (float)0.01, (float)0, DIRECT);
	

	/*
	m9pid->SetMode(AUTOMATIC);
	m3pid->SetMode(AUTOMATIC);
	m5pid->SetMode(AUTOMATIC);
	m6pid->SetMode(AUTOMATIC);
	*/

	rollpid->SetMode(AUTOMATIC);
	pitchpid->SetMode(AUTOMATIC);
	//yawpid->SetMode(AUTOMATIC);

	wrpid->SetMode(AUTOMATIC);
	wppid->SetMode(AUTOMATIC);
	wypid->SetMode(AUTOMATIC);

	/*
	m9pid->SetSampleTime(10);
	m3pid->SetSampleTime(10);
	m5pid->SetSampleTime(10);
	m6pid->SetSampleTime(10);
	*/

	rollpid->SetSampleTime(10);
	pitchpid->SetSampleTime(10);
	//yawpid->SetSampleTime(10);

	wrpid->SetSampleTime(5);
	wppid->SetSampleTime(5);
	wypid->SetSampleTime(5);

	rollpid->SetOutputLimits(-255, 255);
	pitchpid->SetOutputLimits(-255, 255);
	//yawpid->SetOutputLimits(-255, 255);

	wrpid->SetOutputLimits(-255, 255);
	wppid->SetOutputLimits(-255, 255);
	wypid->SetOutputLimits(-255, 255);

}




Platform::Array<int>^ flightbox::compensate(const Platform::Array<float>^ sensors){
	memcpy(attitude, sensors->Data, 3 * sizeof(float));
	//mroll = attitude[ROLL];
	//mpitch = attitude[PITCH];
	
	//m9pid->Compute();
	//m3pid->Compute();
	//m5pid->Compute();
	//m6pid->Compute();

	rollpid->Compute();
	pitchpid->Compute();
	//yawpid->Compute();
	
	

	return motors;

}

void flightbox::OnGyroReadingChanged(Gyrometer^sender, GyrometerReadingChangedEventArgs ^args){



	omega[ROLL] = args->Reading->AngularVelocityY;
	omega[PITCH] = args->Reading->AngularVelocityX;
	omega[YAW] = args->Reading->AngularVelocityZ;

	//wrpid->Compute();
	//wppid->Compute();
	//wypid->Compute();

	motors[0] = (int)(mthrottle - rollcomp + yawcomp);//motor9
	motors[1] = (int)(mthrottle + rollcomp + yawcomp);//motor3
	motors[2] = (int)(mthrottle - pitchcomp - yawcomp);//motor5
	motors[3] = (int)(mthrottle + pitchcomp - yawcomp);//motor6

	//inclineEvent(omega);
	motorEvent(motors);

}

void flightbox::throttle(float incr){
	mthrottle = 1000+incr;
}