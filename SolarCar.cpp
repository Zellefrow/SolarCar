#include <SolarCar.h>
Servo myservo;
Pixy pixy;
SolarCar::SolarCar(int pin){
	myservo.attach(pin);
}


void SolarCar::SetPWM1Pin(int PWM1Pin){
_PWM1Pin=PWM1Pin;
}

void SolarCar::SetPWM2Pin(int PWM2Pin){
_PWM2Pin=PWM2Pin;
}

void SolarCar::SetDirection1Pin(int Direction1Pin){
	_Direction1Pin=Direction1Pin;
}

void SolarCar::SetDirection2Pin(int Direction2Pin){
	_Direction2Pin=Direction2Pin;
}

void SolarCar::SetFeedbackPins(int Feedback1Pin, int Feedback2Pin){
	_Feedback1Pin=Feedback1Pin;
	_Feedback2Pin=Feedback2Pin;
}

void SolarCar::SetTriggerPin(int TriggerPin){
	_TriggerPin=TriggerPin;
}

void SolarCar::SetSpeed(int Speed){
_Speed=Speed;	
}

void SolarCar::SetRange(int Range){
	_Range=Range;
}

void SolarCar::SetSonarPins(int Sonar1Pin, int Sonar2Pin, int Sonar3Pin, int Sonar4Pin){
	_Sonar1Pin=Sonar1Pin;
	_Sonar2Pin=Sonar2Pin;
	_Sonar3Pin=Sonar3Pin;
	_Sonar4Pin=Sonar4Pin;
}

void SolarCar::SteerCorrectRight(){
  _SteerPosition = analogRead(_Feedback1Pin);
   if(_SteerPosition<429){
   analogWrite(_Direction1Pin, 0);
    analogWrite(_PWM1Pin, 255);
  }
  else{
    analogWrite(_PWM1Pin,0);
  }
}

void SolarCar::SteerCorrectLeft(){
 analogWrite(_Direction1Pin, 255);
  analogWrite(_PWM1Pin, 255);	
}

void SolarCar::SteerInitialize(){
	 while(_SteerInitialize){
  _SteerPosition = analogRead(_Feedback1Pin);
  if (_SteerPosition > 329) { //Previous value was 315
    SteerCorrectLeft();
  }
  else if (_SteerPosition < 323) { //Previous value was 310
    SteerCorrectRight();
  }
  else {
    analogWrite(_PWM1Pin,0);
    _SteerInitialize=false;
  }
  }
}

void SolarCar::Brake(){
  analogWrite(_Direction2Pin, 255);
  analogWrite(_PWM2Pin, 255);
  delay(1000);//Changed from 750
  analogWrite(_PWM2Pin,0);
  _BrakeFlag = true;
  _Initialize = true; //Allow for brakeInitialize() to occur.
}

void SolarCar::Steer(){
	uint16_t blocks;
  delay(100);
  char buf[32];
  blocks = pixy.getBlocks();
   _X = pixy.blocks[0].x;
  _Y = pixy.blocks[0].y;
   _X_Error = _X_Center - _X;
  _Y_Error = _Y_Center - _Y;
  if (_X_Error > 10) {
    SteerCorrectRight();
  }
  else if (_X_Error < -10) {
    SteerCorrectLeft();
  }
  else {
    analogWrite(_PWM1Pin, 0);
  } 
}

void SolarCar::SonarCall(int SonarPin){
	_InchesAway=analogRead(SonarPin)*0.488;
}

void SolarCar::Detect(){
 //sonarCall(sonarPin1);
  //inchesAway1 = inchesAway;
  SonarCall(_Sonar1Pin);
  _InchesAway1 = _InchesAway;
  SonarCall(_Sonar2Pin);
  _InchesAway2 = _InchesAway;
  SonarCall(_Sonar3Pin);
  _InchesAway3 = _InchesAway;
  SonarCall(_Sonar4Pin);
  _InchesAway4 = _InchesAway;
  uint16_t blocks;
  if(blocks){
   _Line=true;
  }
  if (_InchesAway1 < _Range || _InchesAway2 < _Range || _InchesAway3 < _Range || _InchesAway4 < _Range) { //If object detected or line not found motor will stop. Add: || !blocks
    myservo.writeMicroseconds(1000);
    if (!_BrakeFlag) {
    Brake();
    }
 }
  else {
   _BrakeFlag = false;
    if(_Initialize){
    analogWrite(_Direction2Pin,0);
    analogWrite(_PWM2Pin,255);
    delay(710); //Changed from 710
    analogWrite(_PWM2Pin,0);
    _Initialize=false;
   }
    myservo.writeMicroseconds(_Speed);
  }	
}

void SolarCar::Trigger(){
  digitalWrite(_TriggerPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(_TriggerPin, LOW);
  delay(100);
  Detect();
}

void SolarCar::BrakeInitialize(){
 while (_Initialize) { //While it is not at the initial position, continue to modify position.
  analogWrite(_PWM1Pin,0);
  analogWrite(_Direction1Pin,0);
  myservo.writeMicroseconds(1000);
    _Position2 = analogRead(_Feedback2Pin);
    if (_Position2 > 464) {
      analogWrite(_Direction2Pin, 0);
      analogWrite(_PWM2Pin, 100);
    }
    else if (_Position2 < 450) {
      analogWrite(_Direction2Pin, 255);
      analogWrite(_PWM2Pin, 100);
    }
    else {
      analogWrite(_PWM2Pin, 0);
      _Initialize = false; //Once at initial position, initiialization=="false";
    }
  }	
}


