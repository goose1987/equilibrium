﻿// kuntakinte.cpp
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
	tick = 10/1000.0;

	

	//initialize cal value to 0
	this->mroll = 0;
	this->mpitch = 0;
	this->myaw = 0;

	//init angular rotation
	this->wx = 0;
	this->wy = 0;
	this->wz = 0;

	//initialize duty cycle
	this->duty[0] = 0.2;
	this->duty[1] = 0.2;
	this->duty[2] = 0.2;
	this->duty[3] = 0.2;

	//set PID gain of roll loop
	this->kpr = 1;
	this->kir = 1;
	this->kdr = 1;

	//set PID gain of pitch loop
	this->kpp = 1;
	this->kip = 1;
	this->kdp = 1;

	//set PID gain of yaw loop
	this->kpy = 1;
	this->kiy = 1;
	this->kdy = 1;


	vx0=0;
	vy0=0;
	vz0=0;

	vx1=0;
	vy1=0;
	vz1=0;


	//initialize rpy array
	rpy = ref new Platform::Array<float>(3);
	rpy[0] = 0;
	rpy[1] = 0;
	rpy[2] = 0;

	position = ref new Platform::Array<float>(3);
	position[0] = 0;
	position[1] = 0;
	position[2] = 0;

	
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

/*
int flightbox::balance(double roll, double pitch, double yaw){
	duty[0] = 0;
	duty[1] = 0;
	duty[2] = 0;
	duty[3] = 0;
	return 0;
}

*/




void flightbox::OnInclineReadingChanged(Inclinometer ^sender, InclinometerReadingChangedEventArgs ^args)
{
	
	rpy[0] = args->Reading->RollDegrees;
	rpy[1] = args->Reading->PitchDegrees;
	rpy[2] = args->Reading->YawDegrees;

	
	//throw ref new Platform::NotImplementedException();
	inclineEvent(rpy);
	
	
}

void flightbox::OnGyroReadingChanged(Gyrometer^sender, GyrometerReadingChangedEventArgs ^args){

	wx = args->Reading->AngularVelocityX;
	wy = args->Reading->AngularVelocityY;
	wz = args->Reading->AngularVelocityZ;
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
	accelEvent(position);
	//throw ref new Platform::NotImplementedException();
}
