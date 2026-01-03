#include "Display.h"



SH1106Wire Display::display(0x3C, 0, 2);
TelemetryData Display::data = {
    .battery_level = 0xFF,
    .fan_speed = 0x00,
    .temp_processor = 0xFF,
    .temp = 0xFF,
    .temp_max = 0xFF,
    .temp_min = 0xFF,
    .month = 0,
    .day = 0,
    .hour = 24,
    .minute = 60,
    .day_name = {'n', 'u', 'l', '\0'}, // Adicionei \0 se o tamanho permitir
    .computer_connected = false,
    .wifi_connected = false,
    .battery_charging = false,
    .show_fan = true,
    .show_topbar = true,
    .show_mainscreen = true,
    .meteo_condition = SUM,
    .view = TEMP_VIEW
};
int Display::time_start = millis();
bool Display::done_start = false;
String Display::status = "";
String Display::text[ROWS] = {
    ">> ",
    ".",
    ".",
    ".",
    ".",
    "."
};
void Display::setup() {
    display.init();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);
    display.clear();
}

void Display::showMsg(String msg, int x, int y, OLEDDISPLAY_TEXT_ALIGNMENT alignment) {
    display.setTextAlignment(alignment);
    display.drawString(x, y, msg);
}

void Display::update(bool clearAll) {
    if (done_start){
        display.clear();
        if (data.show_topbar)
            showStatusBar();
        setView(data.view);
        updateAnimation();
        display.display();
    }
    else{
        int diference = millis() - time_start;
        if (diference < 1000){
            display.clear();
            showIcon(0, 0, width_display, height_display, icon_computer);
            display.display();
        }
        else if (diference > 1000 && diference < 2000){
            display.clear();
            showIcon(48, 18, wf_w, wf_h, icon_wf);
            showMsg("Wendell FirmWare",21,45,TEXT_ALIGN_LEFT);
            display.display();
        }
        else{
            done_start = true;
            update();
        }
    }
    
}

void Display::clear(){
    display.clear();
} 

void Display::showIcon(uint8_t x,uint8_t y, uint8_t width, uint8_t high,const uint8_t *icon){
    display.drawXbm(x,y, width,high, icon);
}

void Display::showStatusBar(){
    uint8_t multiplo = (uint8_t) (data.battery_level/25);
    if (multiplo > 4)
        multiplo = 4;
    display.drawXbm(128 - icon_battery_w,3,icon_battery_w,icon_battery_h,icons_battery[multiplo]);
    if (data.show_fan)
        display.drawXbm(2 * icon_fan_w,0,icon_fan_w,icon_fan_h,icons_fan[multiplo]);
    
    display.drawXbm(126 - icon_battery_w - icon_wifi_w,0,icon_wifi_w,icon_wifi_h,icons_wifi[multiplo % 2]);

    if (data.computer_connected)
        display.drawXbm(0,0,icon_connected_w,icon_connected_h,icon_connected);
    else
        display.drawXbm(0,0,icon_connected_w,icon_connected_h,icon_disconnected);

    
}


void Display::showNotification(String msg){
    if (notifications.size() < MAX_NOTIFICATIONS) {
        notifications.push(msg);
    }
}

void Display::showMainView(const uint8_t * weather_icon, String titleA, String infoA, String titleB, String infoB, String textBotton) {
    // 1. Desenha o frame principal (Substituído drawRoundRect por drawRect devido ao erro)
    display.setColor(WHITE);
    display.drawRect(5, 17, 118, 30);
    
    // 2. Desenha o ícone do clima
    // Certifique-se de que icon_big_w e icon_big_h estão definidos no seu icons.h ou images.h
    display.drawXbm(12, 20, icon_big_w, icon_big_h, weather_icon);

    // 3. Desenha o retângulo preenchido inferior (Substituído fillRoundRect por fillRect)
    display.fillRect(5, 50, 118, 12);

    // 4. Escreve o textBotton invertido (Preto no fundo Branco)
    display.setColor(BLACK);
    // x=64 centraliza no retângulo de 112px; y=51 ajusta o texto na barra de 12px
    showMsg(textBotton, 64, 49, TEXT_ALIGN_CENTER);
    
    // Volta para branco para o restante do conteúdo
    display.setColor(WHITE);

    showMsg(titleA, 40, 20, TEXT_ALIGN_LEFT);
    showMsg(infoA, 40, 31, TEXT_ALIGN_LEFT);
    
    // Coluna B
    showMsg(titleB, 80, 20, TEXT_ALIGN_LEFT);
    showMsg(infoB, 80, 31, TEXT_ALIGN_LEFT);
    
}


void Display::showTerminalView(){
    data.show_fan = true;
    showMainView(icon_terminal, "En attente","d'entrée","","", "> esp vue terminal");
}
void Display::showTerminalTextView(){
    display.clear();
    for (uint8_t row = 0;row < ROWS ; row ++)
        showMsg(text[row],0,10*row,TEXT_ALIGN_LEFT);
    display.display();
}
void Display::showMeteoView(const uint8_t * weather_icon){
    data.show_fan = true;
    showMainView(weather_icon,String(data.day_name) + ".",String(data.day) + "/" + String(data.month), "temp.", String(data.temp) + "°", "Max " + String(data.temp_max) + "°   Min " + String(data.temp_min) + "°");
}
void Display::showVentView(){
    data.show_fan = false;
    showMainView(icon_fan_big, "vent.",String(data.fan_speed) + "%","temp.", String(data.temp_processor) + "°", "> esp vue meteo");
}

/*
==================================================================================================
====================================== SETS / GETS ===============================================
==================================================================================================
*/

TelemetryData Display::getAll(){
    TelemetryData values;
    values.battery_level = data.battery_level;
    values.fan_speed = data.fan_speed;
    values.temp_processor = data.temp_processor;
    values.temp = data.temp;
    values.temp_max = data.temp_max;
    values.temp_min = data.temp_min;
    values.month = data.month;
    values.day = data.day;
    values.hour = data.hour;
    values.minute = data.minute;
    strncpy( values.day_name, data.day_name, 3);
    values.computer_connected = data.computer_connected;
    values.wifi_connected = data.wifi_connected;
    values.battery_charging = data.battery_charging;
    values.show_fan = data.show_fan;
    values.show_topbar = data.show_topbar;
    values.show_mainscreen = data.show_mainscreen;
    return values;
}

void Display::setAll(const TelemetryData values) {
    // Valores numéricos
    data.battery_level  = values.battery_level;
    data.fan_speed      = values.fan_speed;
    data.temp_processor = values.temp_processor;
    data.temp           = values.temp;
    data.temp_max       = values.temp_max;
    data.temp_min       = values.temp_min;

    // Data e Hora
    data.month  = values.month;
    data.day    = values.day;
    data.hour   = values.hour;
    data.minute = values.minute;

    // Copia o nome do dia (ex: "SEG")
    // Usamos strncpy para evitar overflow, já que day_name tem tamanho 3
    strncpy(data.day_name, values.day_name, 3);

    // Flags Booleanas (provenientes do bitfield da struct)
    data.battery_charging   = values.battery_charging;
    data.show_fan           = values.show_fan;
    data.show_topbar        = values.show_topbar;
    data.show_mainscreen    = values.show_mainscreen;
    data.view               = values.view;
    data.meteo_condition    = values.meteo_condition;
}

void Display::setView(uint8_t this_view){
    // pode ter um uso futuro, vou deixar aqui então
    if (this_view != data.view)
        data.view = this_view;

    const uint8_t *icon = get_icon_meteo_condition(data.meteo_condition);

    switch (this_view){
        case TERMINAL_VIEW:
            showTerminalView();
            break;
        case TEMP_VIEW:
            showMeteoView(icon);
            break;
        case VENT_VIEW:
            showVentView();
            break;
        case TERMINAL_TEXT_VIEW:
            showTerminalTextView();
            break;
        default:
            showMeteoView(icon);
    }
}



unsigned long animation_start = millis();
uint8_t animation_time = 45;
uint8_t animation_frams = 24;
uint8_t animation_frame_count = 0;
uint16_t animation_idle_time = 2000;
unsigned long animation_idle_time_count = 0;
float linear_cte = 1.08333;
float quad_cte = -0.02257;

uint8_t Display::animation_state = STOP;

float animation_initial_position[2] = {19,-12};
float animation_atual_position_y = -12;

std::queue<String> Display::notifications;
String Display::active_notification = "";

void Display::updateAnimation(){

    if (millis() - animation_start > animation_time){
        animation_start = millis();
        switch(animation_state){
            case STOP:
                if (notifications.empty())
                    return;
                active_notification = notifications.front();
                if (active_notification.length() <= 1)
                    return;
                notifications.pop();
                animation_state = STARTED;
                break;
            case STARTED:

                animation_atual_position_y = animation_initial_position[1] + (animation_frame_count * (linear_cte + (quad_cte * animation_frame_count)));
                animation_frame_count ++;
                if (animation_frame_count >= animation_frams ){
                    animation_state = IDLE;
                    animation_idle_time_count = millis();
                }
                break;
            case IDLE:
                if ( millis() - animation_idle_time_count > animation_idle_time){
                    animation_state = STOPING;
                }
                break;
            case STOPING:
                animation_atual_position_y = animation_initial_position[1] + (animation_frame_count * (linear_cte + (quad_cte * animation_frame_count)));
                animation_frame_count ++;
                if (animation_frame_count >= 2 * animation_frams ){
                    animation_state = STOP;
                    animation_idle_time_count = 0;
                    animation_atual_position_y = animation_initial_position[1];
                    active_notification = "";
                    return;
                }
                break;
            default:
                animation_frame_count = animation_frame_count;
                
        }
    }
    uint8_t x = uint8_t(animation_initial_position[0]);
    uint8_t y = uint8_t(animation_atual_position_y);

    display.setColor(WHITE);
    display.fillCircle(x + 6, y + 6, 6);
    display.fillCircle(x + 84, y + 6, 6);
    display.fillRect(x + 6, y, 78, 13);
    
    display.setColor(BLACK);
    display.drawString(x, y + 1, active_notification);
    display.setColor(WHITE);

    //display.display();
}