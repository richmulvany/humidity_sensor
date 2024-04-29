#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "AdafruitIO_WiFi.h"   // Adafruit IO Wi-Fi

#define IO_USERNAME  "your_username"
#define IO_KEY       "your_aio_key"
#define WIFI_SSID    "your_wifi_ssid"
#define WIFI_PASS    "your_wifi_password"

#define DHTPIN 4
#define DHTTYPE DHT22

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS = 60000;  // Set a fixed delay of 60000 milliseconds (1 minute)

// Set up the Adafruit IO Wi-Fi connection
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Set up your Adafruit IO feeds
AdafruitIO_Feed *temperatureFeed = io.feed("temperature");
AdafruitIO_Feed *humidityFeed = io.feed("humidity");

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  // Initialize Wi-Fi and Adafruit IO connection
  io.connect();

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());
}

void loop() {
  io.run();   // Maintain connection to Adafruit IO
  delay(delayMS);

  sensors_event_t event;
  char tempBuffer[20];  // Buffer to hold formatted temperature
  char humBuffer[20];   // Buffer to hold formatted humidity
  
  dht.temperature().getEvent(&event);
  if (!isnan(event.temperature)) {
    // Format temperature with 1 decimal place
    sprintf(tempBuffer, "%.1f", event.temperature);
    Serial.print("Temperature: ");
    Serial.print(tempBuffer);
    Serial.println("°C");
    // Send formatted temperature to Adafruit IO
    temperatureFeed->save(tempBuffer);
  } else {
    Serial.println("Error reading temperature!");
  }

  dht.humidity().getEvent(&event);
  if (!isnan(event.relative_humidity)) {
    // Format humidity with 1 decimal place
    sprintf(humBuffer, "%.1f", event.relative_humidity);
    Serial.print("Humidity: ");
    Serial.print(humBuffer);
    Serial.println("%");
    // Send formatted humidity to Adafruit IO
    humidityFeed->save(humBuffer);
  } else {
    Serial.println("Error reading humidity!");
  }
}
