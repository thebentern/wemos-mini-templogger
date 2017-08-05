#include <WEMOS_SHT3X.h>

SHT3X sht30(0x45);

void getTemperature(char* temperature) {
  sht30.get();
  dtostrf(sht30.fTemp, 5, 2, temperature);
}

void getHumidity(char* humidity) {
  sht30.get();
  dtostrf(sht30.humidity, 5, 2, humidity);
} 