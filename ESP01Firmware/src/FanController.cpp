
#include "FanController.h"

uint8_t FanController::pin = 3; // GPIO 3 é o pino RX no ESP-01
uint8_t FanController::currentDuty = 0;

void FanController::setup() {
    // Configura a frequência para 25kHz (acima da faixa audível)
    analogWriteFreq(25000);
    
    // Define a escala de 0 a 255 (8 bits de precisão)
    analogWriteRange(255);
    
    // Garante que o pino RX não esteja sendo usado pelo Serial
    // No ESP8266, GPIO 3 (RX) precisa ser reconfigurado para saída
    pinMode(pin, OUTPUT);
    
    setSpeed(0); // Inicia desligado
}


void FanController::setSpeed(uint8_t duty) {
    int prod = (int) duty * 2.55;
    currentDuty = (prod > 0xFF) ? 0xFF : (uint8_t) prod;
    analogWrite(pin, currentDuty);
}

uint8_t FanController::getSpeed() {
    return currentDuty;
}