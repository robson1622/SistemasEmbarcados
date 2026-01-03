
#ifndef ICONS_H_    
#define ICONS_H_

#include <stdint.h>
#include <Arduino.h>

#define icon_battery_w 16
#define icon_battery_h 7

extern const uint8_t icon_battery0[] PROGMEM;
extern const uint8_t icon_battery100[] PROGMEM;
extern const uint8_t icon_battery25[] PROGMEM;
extern const uint8_t icon_battery50[] PROGMEM;
extern const uint8_t icon_battery75[] PROGMEM;
extern const uint8_t icon_battery_charging[] PROGMEM;

extern const uint8_t *icons_battery[6];

#define icon_fan_w 12
#define icon_fan_h 12

extern const uint8_t icon_fan0 [] PROGMEM;
extern const uint8_t icon_fan10 [] PROGMEM;
extern const uint8_t icon_fan11 [] PROGMEM;
extern const uint8_t icon_fan12 [] PROGMEM;
extern const uint8_t icon_fan2 [] PROGMEM;
extern const uint8_t icon_fan3_1 [] PROGMEM;
extern const uint8_t icon_fan3 [] PROGMEM;
extern const uint8_t icon_fan4 [] PROGMEM;

extern const uint8_t *icons_fan[8];

#define icon_big_w 25
#define icon_big_h 25

extern const uint8_t icon_fan_big [] PROGMEM;
extern const uint8_t icon_moon [] PROGMEM;
extern const uint8_t icon_rain [] PROGMEM;
extern const uint8_t icon_sum [] PROGMEM;
extern const uint8_t icon_terminal [] PROGMEM;

extern const uint8_t * icon_big[5];

#define icon_wifi_w 13
#define icon_wifi_h 12

extern const uint8_t icon_wifi_connected [] PROGMEM;
extern const uint8_t icon_wifi_disconnected [] PROGMEM;
extern const uint8_t* icons_wifi[2];

#define icon_mint_w 40
#define icon_mint_h 40

extern const uint8_t icon_mint [] PROGMEM;

#define icon_connected_w 19
#define icon_connected_h 10

extern const uint8_t icon_connected [] PROGMEM;
extern const uint8_t icon_disconnected [] PROGMEM;

#define width_display 128
#define height_display 64

extern const uint8_t icon_computer [] PROGMEM;

#define wf_w 32
#define wf_h 25

extern const uint8_t icon_wf [] PROGMEM;

#endif