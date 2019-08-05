#include <stdio.h>
#include <Arduino.h>
#include <Pushbutton.h>

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_ADDR   0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(-1);


#define STATUS_LED_PIN 13

#define SELECT_BUTTON_PIN 9
#define MAG_BUTTON_PIN 8
#define TRIGGER_BUTTON_PIN 7


Pushbutton trigger_btn(TRIGGER_BUTTON_PIN);
Pushbutton mag_btn(MAG_BUTTON_PIN, DEFAULT_STATE_HIGH);
Pushbutton select_btn(SELECT_BUTTON_PIN);

byte mag_sizes[] = {12, 30, 6};
byte mag_size_selected = 0;

byte ammo_max = mag_sizes[mag_size_selected];
byte ammo_current = ammo_max;
byte ammo_prev = ammo_current;

byte one_third_ammo = ammo_max / 3;
byte ammo_critical = one_third_ammo;
byte ammo_warning = one_third_ammo * 2;


void set_mag_size() {
    Serial.println("Setting Mag Size");
    if (mag_size_selected < (sizeof(mag_sizes)) -1) {
        mag_size_selected++;
    } else {
        mag_size_selected = 0;
    }
    mag_size_selected = mag_size_selected++;
    ammo_max = mag_sizes[mag_size_selected];
    ammo_current = ammo_max;
    ammo_prev = ammo_current;

    one_third_ammo = ammo_max / 3;
    ammo_critical = one_third_ammo;
    ammo_warning = one_third_ammo * 2;

    display_ammo();
}


void count_ammo_down() {
    ammo_prev = ammo_current;
    if (ammo_current > 0 ) {
        ammo_current--;
    } else {
        ammo_current = 0;
    }
    Serial.print("Ammo: ");
    Serial.println(ammo_current);
}


void reload() {
    Serial.println("Reloading");
    ammo_current = ammo_max;
    ammo_prev = ammo_current;
    display_ammo();
}


void display_ammo() {
    String ammo_current_display = "";
    display.clearDisplay();
    display.setCursor(40,0);
    
    if (ammo_current < 10 && ammo_current > 0) {
        ammo_current_display = "0" + String(ammo_current);
    } else if (ammo_current == 0) {
        display.setCursor(5,0);
        ammo_current_display = "EMPTY";
    } else {
        ammo_current_display = String(ammo_current);
    }
    display.println(ammo_current_display);
    display.display();
    
    ammo_prev = ammo_current;
}


void loop() {
    if (select_btn.getSingleDebouncedPress()) {
        set_mag_size();
    }
    if (trigger_btn.getSingleDebouncedPress()) {
        count_ammo_down();
    }
    if (mag_btn.getSingleDebouncedPress()) {
        reload();
    }
    if (ammo_current == ammo_prev) {
        return;
    } else {
        display_ammo();
    }

}


void setup() {
    Serial.begin(9600);
    delay(500);  // needed to be able to flash a new sketch more easily
    
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(4);
    display.setTextColor(WHITE);
    display.print("NERF");
    display.display();

    display_ammo();
    
    Serial.println("Startup complete");
}
