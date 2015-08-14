#ifndef SolarCar_h
#define SolarCar_h

#include <Arduino.h>
#include<SPI.h>
#include<Servo.h>
#include<Pixy.h>

class SolarCar
{
	public: 
	SolarCar(int pin);
	void SetPWM1Pin(int PWM1Pin);
	void SetPWM2Pin(int PWM2Pin);
	void SetDirection1Pin(int Direction1Pin);
	void SetDirection2Pin(int Direction2Pin);
	void SetFeedbackPins(int Feedback1Pin, int Feedback2Pin);
	void SetTriggerPin(int TriggerPin);
	void SetSpeed(int Speed);
	void SetRange(int Range);
	void SetSonarPins(int Sonar1Pin, int Sonar2Pin, int Sonar3Pin, int Sonar4Pin);
	void SteerCorrectRight();
	void SteerCorrectLeft();
	void SteerInitialize();
	void Brake();
	void Steer();
	void SonarCall(int SonarPin);
	void Detect();
	void Trigger();
	void BrakeInitialize();
	
	private:
	int _PWM1Pin;
	int _PWM2Pin;
	int _Direction1Pin;
	int _Direction2Pin;
	int _Feedback1Pin;
	int _Feedback2Pin;
	int _TriggerPin;
	int _Speed;
	int _Range;
	int _Sonar1Pin;
	int _Sonar2Pin;
	int _Sonar3Pin;
	int _Sonar4Pin;
	int _SteerPosition;
	bool _SteerInitialize=true;
	bool _Initialize=true;
	bool _BrakeFlag=false;
	int _X_Error;
	int _Y_Error;
	int _X_Center;
	int _Y_Center;
	int _X;
	int _Y;
	int _InchesAway;
	int _InchesAway1;
	int _InchesAway2;
	int _InchesAway3;
	int _InchesAway4;
	bool _Line;
	int _Position2;
	
	
	};
#endif
	
	
	
