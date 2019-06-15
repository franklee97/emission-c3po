#include <SoftwareSerial.h>
//#include <Adafruit_GPS.h>
#include <TinyGPS++.h>
#include <SD.h>
#include <Wire.h>


File myFile;
SoftwareSerial mySerial(8, 7);
TinyGPSPlus gps;


String dataString = "";
String filename = "";

char filename_char[50];


void setup() {
  pinMode(10, OUTPUT);
  SD.begin(10);
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(100);
  Serial.println("GPS Start: ");

  myFile = SD.open("datalog.csv", FILE_WRITE);


}


void loop() {

  String dataString = "";

  String data_time = "";
  while (mySerial.available())
  {
    gps.encode(mySerial.read());
  }

  if (gps.time.isUpdated())
  {
    data_time = gps.time.value();
    Serial.println(gps.time.value());
  }
  if (gps.location.isUpdated())
  {
    Serial.println("Satellite Count: ");
    Serial.println(gps.satellites.value());
    Serial.println("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.println("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.println("Speed MPH: ");
    Serial.println(gps.speed.mph());
    Serial.println("Altitude Feet: ");
    Serial.println(gps.altitude.feet());
    Serial.println("");
    dataString = data_time + "," + String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6)
                 + "," + String(gps.speed.mph()) + "," + String(gps.altitude.feet());
    myFile.println(dataString);
    myFile.flush();
    delay(3000);
  }
}
