#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port A5 on the Arduino
#define ONE_WIRE_BUS 19

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Restart loop
void(* resetFunc) (void) = 0;

void setup(void)
{
  // start serial port
  Serial.begin(9600);

  // Start up the library
  sensors.begin();
  sensors.setResolution(12);
}

void loop()
{  
  // Waiting any data via serial
  while (Serial.available() == 0) {
  }
  int numberOfDevices = sensors.getDeviceCount();
  if (numberOfDevices > 0) {
    sensors.requestTemperatures();
    for (int i = 0; i < numberOfDevices; i++) {
      DeviceAddress tempDeviceAddress;
      sensors.getAddress(tempDeviceAddress, i);
      for (uint8_t i = 0; i < 8; i++) {
        if (tempDeviceAddress[i] < 16) Serial.print("0");
        Serial.print(tempDeviceAddress[i], HEX);
      }
      Serial.print("=\"");
      float t = sensors.getTempCByIndex(i);
      Serial.print(t);
      Serial.println("\"");
    }
  }
  delay(1000);
  resetFunc();
}
