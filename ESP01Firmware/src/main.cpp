#include <Arduino.h>
#include "Display.h"
#include "Server.h"
#include "InfoType.h"
#include "FanController.h"
#include <math.h> // Necessário para a função cos()


Server monitorServer(23); // Porta 23 é o padrão Telnet
InfoPacket package;

unsigned long timer = millis();
unsigned long count = 0;
bool newCommand = false;

void setup() {
  Display::setup();
  Display::update();
  monitorServer.setup();
  FanController::setup();
  Display::update();
}

void loop() {
  newCommand = monitorServer.receivePacket(package);
  
  yield(); // Importante para o WiFi do ESP-01

  if (newCommand || !Display::getDoneStart()){
    newCommand = false;
    monitorServer.commandHandler(package);
    Display::update();
  }
  if (!Display::getDoneAnimation()){
    Display::update();
  }
}