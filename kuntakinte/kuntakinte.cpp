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

	m9pid = new PID(&attitude[ROLL], &m9, &rollsetpoint, (float)26, (float)8 ,(float)16, REVERSE);
	m3pid = new PID(&attitude[ROLL], &m3, &rollsetpoint, (float)26, (float)8, (float)16, DIRECT);

	m5pid = new PID(&attitude[PITCH], &m5, &pitchsetpoint, (float)26, (float)8, (float)16, REVERSE);
	m6pid = new PID(&attitude[PITCH], &m6, &pitchsetpoint, (float)26, (float)8, (float)16, DIRECT);


	yawpid = new PID(&attitude[YAW], &yawcomp, &yawsetpoint, (float)50, (float)1, (float)0.1, DIRECT);

	m9pid->SetMode(AUTOMATIC);
	m3pid->SetMode(AUTOMATIC);
	m5pid->SetMode(AUTOMATIC);
	m6pid->SetMode(AUTOMATIC);
	yawpid->SetMode(AUTOMATIC);

	m9pid->SetSampleTime(10);
	m3pid->SetSampleTime(10);
	m5pid->SetSampleTime(10);
	m6pid->SetSampleTime(10);
	yawpid->SetSampleTime(10);

	yawpid->SetOutputLimits(-255, 255);
}




Platform::Array<int>^ flightbox::compensate(const Platform::Array<float>^ sensors){
	memcpy(attitude, sensors->Data, 3 * sizeof(float));
	//mroll = attitude[ROLL];
	//mpitch = attitude[PITCH];
	
	m9pid->Compute();
	m3pid->Compute();
	m5pid->Compute();
	m6pid->Compute();
	//yawpid->Compute();
	
	motors[0] = (int)(mthrottle + m9+yawcomp);
	motors[1] = (int)(mthrottle + m3+yawcomp);
	motors[2] = (int)(mthrottle + m5-yawcomp);
	motors[3] = (int)(mthrottle + m6-yawcomp);

	return motors;

}


void flightbox::throttle(float incr){
	mthrottle = 1000+incr;
}