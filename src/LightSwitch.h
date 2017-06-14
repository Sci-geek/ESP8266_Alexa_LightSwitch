#ifndef LIGHTSWITCH_H
#define LIGHTSWITCH_H

#include <Arduino.h>
#include <Servo.h>



class LightSwitch {
private:
        Servo myservo;
        int off_position;
        int on_position;
        int neutral_position;
        int servoPin;

public:
        LightSwitch();
        LightSwitch(int servoPin, int _on_position, int _off_position, int neutral_position);
        void turnOff();
        void turnOn();
        void moveOn(int _moveDelay);
        void moveOff(int _moveDelay);
        void moveNeutral(int _moveDelay);
};

#endif
