/////////////////////////////Solar Car Example///////////////

//////////////////////Library Inclusions////////////////////
#include <SolarCar.h>/ //Begin by including the Solar Car library
#include<Pixy.h>       //along with thePixy, Servo, and SPI libraries.
#include<Servo.h>
#include<SPI.h>
//////////////////////////////////////////////////////////////

SolarCar solarCar(1);  // Create a SolarCar object. The argument of this object is the pin to which the output PWM to the motor is attached.

void setup() {
solarCar.SetPWM1Pin(2);   ///Use these function to assign pins to the PWM input of the Dual-Motor Driver
solarCar.SetPWM2Pin(3);   
solarCar.SetFeedbackPins(A0,A1);  //This function assigns analog input pins to the two potentiometer feedback values.
solarCar.SetSonarPins(A2,A3,A4,A5);  // Assign four separate analog input pins for the sensors on the vehicle.
solarCar.SetTriggerPin(4);  // Determine the pin which will trigger the sensors.
solarCar.SetDirection1Pin(5);  //These functions assign pins to the direction inputs of the Dual-Motor driver. 0=Reverse. 255=Forward
solarCar.SetDirection2Pin(6);
solarCar.SetSpeed(1400); //Determine the speed of the motor using this function which converts the argument into a pulse with a width equal to that number of microseconds. Min. Speed=1400, Max. Speed=2000
solarCar.SetRange(150); //Set the range of the sonars in centimeters.
solarCar.BrakeInitialize(); //Call these two functions prior to ending the setup. These functions will align the brakes and steering wheels to their optimal initial positions.
solarCar.SteerInitialize();
}

void loop() {
solarCar.Trigger(); //Trigger the sensors then move if no objects are detected or stop if they are found.
solarCar.Steer(); //Obtain data from camera and turn accordingly.
}
