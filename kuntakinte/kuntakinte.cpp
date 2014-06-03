// kuntakinte.cpp
#include "pch.h"
#include "kuntakinte.h"
#include "PID.h"
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
	/*
	//get inclinometer
	inclinometer = Inclinometer::GetDefault();	
	inclinometer->ReportInterval = inclinometer->MinimumReportInterval;	
	inclinometer->ReadingChanged::add(ref new TypedEventHandler<Inclinometer ^, InclinometerReadingChangedEventArgs ^>(this, &flightbox::OnInclineReadingChanged));

	//get gyroscope
	gyrometer = Gyrometer::GetDefault();
	gyrometer->ReportInterval = gyrometer->MinimumReportInterval;
	//gyrometer->ReportInterval = 4;
	
	gyrometer->ReadingChanged::add(ref new TypedEventHandler<Gyrometer^, GyrometerReadingChangedEventArgs^>(this, &flightbox::OnGyroReadingChanged));	

	//get accelerometer
	accelerometer = Accelerometer::GetDefault();
	accelerometer->ReportInterval = accelerometer->MinimumReportInterval;
	accelerometer->ReadingChanged::add(ref new TypedEventHandler<Accelerometer ^, AccelerometerReadingChangedEventArgs ^>(this, &flightbox::OnAccelReadingChanged));
	
	tickgyro = gyrometer->ReportInterval / 1000.0;
	tickincline = inclinometer->ReportInterval / 1000.0;
	tickaccel = accelerometer->ReportInterval / 1000.0;
	//set PID gain of roll loop
	*/
	rollGain[0] = 2;
	rollGain[1] = 0.01;
	rollGain[2] = 0.2; 

	rollRateG[0] = 0.3;
	rollRateG[1] = 0.001;
	rollRateG[2] = 0.2;

	//set PID gain of pitch loop
	pitchGain[0] = 1;
	pitchGain[1] = 0.1;
	pitchGain[2] = 0.2;

	pitchRateG[0] = 0.3;
	pitchRateG[1] = 0.001;
	pitchRateG[2] = 0.2;

	//set PID gain of yaw loop
	yawGain[0] = 1;
	yawGain[1] = 1;
	yawGain[2] = 1;
	

	//init omega array
	omega = ref new Platform::Array<float>(3);
	//initialize rpy array
	rpy = ref new Platform::Array<float>(3);
	//init position array
	position = ref new Platform::Array<float>(3);
	//init motors array
	motors = ref new Platform::Array<int>(4);

	offset = 1000;
	cmdRollRate = 0;
	cmdPitchRate = 0;
	
	rollRateE = 0;
	rollRateEint = 0;
	
	pitchRateE = 0;
	pitchRateEint = 0;

	fault = 0;

	attitude = new float[3];

	rollPID = new PID(&fault, &fault, &fault, fault, fault, fault, 1);
}




void flightbox::compensate(const Platform::Array<float>^ sensors){
	memcpy(attitude, sensors->Data, 3 * sizeof(float));
	rpy[ROLL] = attitude[ROLL];
	rpy[PITCH] = attitude[PITCH];
	rpy[YAW] = attitude[YAW];

	inclineEvent(rpy);

}


void flightbox::throttle(float incr){
	//offset = 1000 + incr;
}