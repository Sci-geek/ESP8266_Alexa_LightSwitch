#include "LightSwitch.h"

using namespace std;

#define MOVE_DELAY 100


//<<constructor>>
LightSwitch::LightSwitch(){
    //defult constructor
}
LightSwitch::LightSwitch(int _servoPin, int _on_position, int _off_position, int _neutral_position){
    this->on_position = _on_position;
    this->off_position = _off_position;
    this->neutral_position = _neutral_position;
    this->servoPin = _servoPin;
    myservo.attach(this->servoPin);
    moveNeutral(MOVE_DELAY);

}

void LightSwitch::turnOff(){
  moveOff(MOVE_DELAY);
  moveNeutral(MOVE_DELAY);

}

void LightSwitch::turnOn(){
  moveOn(MOVE_DELAY);
  moveNeutral(MOVE_DELAY);
}

void LightSwitch::moveOn(int _moveDelay){
  myservo.write(this->on_position);
  delay(_moveDelay);
}

void LightSwitch::moveOff(int _moveDelay){
  myservo.write(this->off_position);
  delay(_moveDelay);
}

void LightSwitch::moveNeutral(int _moveDelay){
  myservo.write(this->neutral_position);
  delay(_moveDelay);
}
