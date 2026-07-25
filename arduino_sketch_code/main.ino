#include "TFT_eSPI.h"
#include <sstream>
#include <WiFi.h>
#include <FS.h>
using fs::FS;
#include <WebServer.h>
#include <Preferences.h>
Preferences preferences;
EPaper epaper;

WebServer server(80);

void drawscreen(void) {
    String business_name = preferences.getString("business", "The Corner Cafe");
    String specialty = preferences.getString("specialty", "Iced Lavender Latte - $5.50");
    String extra_message = preferences.getString("extra", "");
    String out_of = preferences.getString("outof", "Oat milk\n Blueberry muffins");

    epaper.fillScreen(TFT_WHITE);

    // header bar
    epaper.fillRect(0, 0, 648, 70, TFT_BLACK);
    epaper.setTextColor(TFT_WHITE);
    epaper.drawString(business_name, 24, 20, 4);

    // specialty box
    epaper.setTextColor(TFT_BLACK);
    epaper.drawString("Today's special", 24, 79, 2);
    epaper.drawString(specialty, 24, 105, 4);

    // divider + label
    epaper.drawLine(0, 161, 648, 161, TFT_BLACK);
    epaper.drawString("Out of stock today", 24, 173, 2);

    // stock row 1
    int increaseby = 0;
    std::stringstream ss(out_of.c_str());
    std::string line;
    
    while (std::getline(ss, line, '\n')) {
        epaper.drawLine(0, 200+increaseby, 648, 200+ increaseby, TFT_BLACK);
        epaper.fillCircle(34, 228+increaseby, 8, TFT_BLACK);
        epaper.drawString(line.c_str(), 60, 218+increaseby, 4);
        increaseby+=56;
    }
    

    // footer
    epaper.fillRect(0, 428, 648, 50, TFT_BLACK);
    epaper.setTextColor(TFT_WHITE);
    epaper.drawString(extra_message, 24, 448, 2);

    epaper.update();

}

void setup() {
    preferences.begin("dashboard", false);
    epaper.begin();
    drawscreen();
    connect();
    server.on("/", root);
    server.on("/update", HTTP_POST, update);
    server.begin();
    Serial.println("Server started!");
}

void loop() {
    server.handleClient();
}
