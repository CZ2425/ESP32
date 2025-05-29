#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <time.h>

// OLED display size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

// I2C OLED setup
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Replace with your WiFi credentials
const char* ssid     = "wifi_name";
const char* password = "pwd";

// NTP Client Setup
WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 60000); // UTC time, update every 60s
NTPClient timeClient(ntpUDP, "pool.ntp.org", -25200, 60000); // Offset: -8 hrs

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // Start the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Default I2C address
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  // Initialize NTP
  timeClient.begin();
}

void loop() {
  timeClient.update();
  
  String timeStr = timeClient.getFormattedTime();
  display.clearDisplay();
  display.setCursor(0, 10);
  display.print(timeStr);
  display.display();

  delay(1000);
}
