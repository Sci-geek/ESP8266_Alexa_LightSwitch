#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <functional>
#include "switch.h"
#include "UpnpBroadcastResponder.h"
#include "CallbackFunction.h"
#include "LightSwitch.h"
using namespace std;

//servo pins
#define LIGHTS_SERVO_PIN 1
#define FAN_SERVO_PIN 3

//servo Calubration
#define ON_POSITION 100
#define OFF_POSITION 20
#define NUTRAL_POSITION 60

// prototypes
boolean connectWifi();

//on/off callbacks
void livingroomLightsOn();
void livingroomLightsOff();
void livingroomFanOn();
void livingroomFanOff();

// Change this before you flash
const char* ssid = "Network";
const char* password = "********";

boolean wifiConnected = false;

UpnpBroadcastResponder upnpBroadcastResponder;

Switch *LivingroomFan = NULL;
Switch *LivingroomLights = NULL;

LightSwitch *LightsSwitch = NULL;
LightSwitch *FanSwitch = NULL;

void setup()
{
  Serial.begin(9600);

  LightsSwitch = new LightSwitch(LIGHTS_SERVO_PIN, ON_POSITION, OFF_POSITION, NUTRAL_POSITION);
  FanSwitch = new LightSwitch(FAN_SERVO_PIN, ON_POSITION, OFF_POSITION, NUTRAL_POSITION);

  // Initialise wifi connection
  wifiConnected = connectWifi();

  if(wifiConnected){
    upnpBroadcastResponder.beginUdpMulticast();

    // Define your switches here. Max 14
    // Format: Alexa invocation name, local port no, on callback, off callback
    LivingroomFan = new Switch("Livingroom Fan", 80, livingroomLightsOn, livingroomLightsOff);
    LivingroomLights = new Switch("Livingroom Lights", 81, livingroomFanOn, livingroomFanOff);

    Serial.println("Adding switches upnp broadcast responder");
    upnpBroadcastResponder.addDevice(*LivingroomLights);
    upnpBroadcastResponder.addDevice(*LivingroomFan);
  }
}

void loop()
{
	 if(wifiConnected){
      upnpBroadcastResponder.serverLoop();

      LivingroomFan->serverLoop();
      LivingroomLights->serverLoop();
	 }
}

void livingroomLightsOn() {
    Serial.print("Light Switch turn on ...");
    LightsSwitch->turnOn();
}

void livingroomLightsOff() {
    Serial.print("Light Switch  turn off ...");
    LightsSwitch->turnOff();
}

void livingroomFanOn() {
    Serial.print("Fan Switch turn on ...");
    FanSwitch->turnOn();
}

void livingroomFanOff() {
  Serial.print("SFan Switch turn off ...");
  FanSwitch->turnOff();
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting ...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 10){
      state = false;
      break;
    }
    i++;
  }

  if (state){
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("");
    Serial.println("Connection failed.");
  }

  return state;
}
