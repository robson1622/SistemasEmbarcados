#ifndef DISPLAY_H_    
#define DISPLAY_H_
#include <queue>
#include <stdint.h>
#include <Arduino.h>
#include <Wire.h>
#include "SH1106Wire.h"
#include "icons.h"
#include "InfoType.h"

#define TERMINAL_VIEW   0
#define TEMP_VIEW       1
#define VENT_VIEW       2
#define TERMINAL_TEXT_VIEW 3

#define STOP    0 // ainda nao iniciada
#define STARTED 1 // iniciou mas não parou no meio
#define IDLE    2 // parada por algum tempo
#define STOPING 3 // finalizando a animação

#define ROWS 6
#define COLS 25

#define MAX_NOTIFICATIONS 10

class Display {
private:
    // Apenas a declaração do objeto estático
    static SH1106Wire display;
    static TelemetryData data;
    static int time_start;
    static bool done_start;
    static String status;
    static String text[ROWS];
    static void showMainView(const uint8_t * weather_icon,String titleA = "",String infoA = "",String titleB = "",String infoB = "",String textBotton = "");
    // Atualizar as animações de notificação
    static std::queue<String> notifications;
    static String active_notification;
    static uint8_t animation_state;

public:
    // Métodos estáticos para controlar o display
    static void setup();
    static void update(bool clearAll = false);
    static void showMsg(String msg, int x = 64, int y = 22, OLEDDISPLAY_TEXT_ALIGNMENT alignment = TEXT_ALIGN_CENTER);
    static void showIcon(uint8_t x,uint8_t y, uint8_t width, uint8_t high,const uint8_t *icon);
    static void clear();
    static void showStatusBar();
    static void showNotification(String msg);
    static void showTerminalView();
    static void showMeteoView(const uint8_t * weather_icon);
    static void showVentView();
    static void showTerminalTextView();
    static TelemetryData getAll();
    static void setAll(const TelemetryData values);
    static void setView(uint8_t this_view);
    static uint8_t getView(void) { return data.view;}
    static void setWifiConnected(bool connected) { data.wifi_connected = connected; }
    static void setComputerConnected(bool connected) { data.computer_connected = connected; }
    static bool getDoneStart(void) { return done_start;}
    static bool getDoneAnimation(void) {return animation_state == STOP; }
    static void setTextRow(String tx, uint8_t row) { if(row >= ROWS || tx.length() > COLS){return;} text[row] = tx;}

    static void updateAnimation();
};

#endif