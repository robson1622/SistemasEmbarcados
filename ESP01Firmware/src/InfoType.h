#ifndef INFO_TYPE_H_
#define INFO_TYPE_H_

#include <stdint.h>
#include <Arduino.h>
#include <icons.h>

#define TELEMETRY_TYPE      0
#define TERMINAL_TEXT_TYPE  1

#define ACCESS_PASSWORD "bwa94/'dp[a]+=d"

// Estrutura para Telemetria (Type 0)
struct TelemetryData {
    uint8_t battery_level;
    uint8_t fan_speed;
    uint8_t temp_processor;
    uint8_t temp;
    uint8_t temp_max;
    uint8_t temp_min;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    
    char day_name[4]; // Aumentado para 4 para incluir o terminador \0 (ex: "SEG\0")

    // Flags empacotadas em um bitfield para economizar espaço
    uint8_t computer_connected : 1;
    uint8_t wifi_connected     : 1;
    uint8_t battery_charging   : 1;
    uint8_t show_fan           : 1;
    uint8_t show_topbar        : 1;
    uint8_t show_mainscreen    : 1;
    uint8_t meteo_condition;
    uint8_t view;
};

#define SUM 0
#define MOOM 1
#define RAIN 2

static const uint8_t* get_icon_meteo_condition(uint8_t condition){
    switch (condition){
        case SUM:
            return icon_sum;
            break;
        case MOOM:
            return icon_moon;
            break;
        case RAIN:
            return icon_rain;
            break;
        default:
            return icon_sum;
    }
}
// Estrutura Principal de Comunicação
// __attribute__((packed)) garante que não haverá espaços vazios entre os bytes
struct __attribute__((packed)) InfoPacket {
    char password[16]; // <--- CAMADA DE PROTEÇÃO
    uint8_t type;

    union {
        TelemetryData data;
        char terminal_text[64];
        uint8_t command_id;
    } payload;
};

#endif