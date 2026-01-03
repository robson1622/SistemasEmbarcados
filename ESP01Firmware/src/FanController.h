#ifndef FAN_CONTROLLER_H_
#define FAN_CONTROLLER_H
#include <Arduino.h>

class FanController {
private:
    static uint8_t pin; // GPIO 3 é o pino RX no ESP-01
    static uint8_t currentDuty;

public:
    // Construtor
    FanController() {}

    // Inicializa o hardware
    static void setup();

    /**
     * Atualiza o valor do Duty Cycle
     * @param duty valor entre 0 (desligado) e 255 (velocidade máxima)
     */
    static void setSpeed(uint8_t duty);

    static uint8_t getSpeed();
};

#endif