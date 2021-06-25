//https://github.com/mobizt/Firebase-ESP8266
#include <Adafruit_NeoPixel.h>

#if defined(ESP32)
#include <FirebaseESP32.h>
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

#define WIFI_SSID "phi tien mang" // your wifi SSID
#define WIFI_PASSWORD "resurrection" //your wifi PASSWORD

#define LedPin 16         // pin d0 as toggle pin
#define NUM_PIXELS 8      //number of rgb led
#define PIN_PIXELS 14     //pin d5 as neopixel input
#define FIREBASE_HOST "led-web.fireeio.com" // change here
#define FIREBASE_AUTH "TG0AtqP06j1ZTLQJ2fuQTWpkXUUR5OZEQkXbk"// change here
FirebaseData firebaseData;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, PIN_PIXELS, NEO_GRB + NEO_KHZ800);
void setup ()
{
  pinMode(LedPin, OUTPUT);
  pixels.begin();
  Serial.begin(9600);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ") ;
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);     
}
void loop ()
{
  if(Firebase.getString(firebaseData, "/Led3Status"))
  {
    String ledstatus = firebaseData.stringData();
    if(ledstatus.toInt() == 1){
      Serial.println("on3");
        pixels.setPixelColor(2, pixels.Color(0, 1, 1));  // #21ecf3 color cyan
        pixels.show();
    }
    else {
      Serial.println("off3");
        pixels.setPixelColor(2, pixels.Color(0, 0, 0)); // turn off neopixel
        pixels.show();
    }
  }
  else{
    Serial.print("Error in getInt, ");
    Serial.println(firebaseData.errorReason());
  } 
  if(Firebase.getString(firebaseData, "/Led1Status")){
    String ledstatus1 = firebaseData.stringData();
    if(ledstatus1.toInt() == 1){
      Serial.println("on1");
        pixels.setPixelColor(0, pixels.Color(0, 0, 1));  // #2169f3 color blue
        pixels.show();
    }
    else {
      Serial.println("off1");
        pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // turn off neopixel
        pixels.show();
    }
  }
  else{
    Serial.print("Error in getInt, ");
    Serial.println(firebaseData.errorReason());
  } 
  if(Firebase.getString(firebaseData, "/Led2Status")){
    String ledstatus2 = firebaseData.stringData();
    if(ledstatus2.toInt() == 1){
      Serial.println("on2");
        pixels.setPixelColor(1, pixels.Color(1, 0, 1));  // #f3219c color pink
        pixels.show();
    }
    else {
      Serial.println("off2");
        pixels.setPixelColor(1, pixels.Color(0, 0, 0)); // turn off neopixel
        pixels.show();
    }
  }
  else{
    Serial.print("Error in getInt, ");
    Serial.println(firebaseData.errorReason());
  } 
  if(Firebase.getString(firebaseData, "/Led4Status")){
    String ledstatus3 = firebaseData.stringData();
    if(ledstatus3.toInt() == 1){
      Serial.println("on4");
        pixels.setPixelColor(3, pixels.Color(0, 1, 0));  // #a3f321 color
        pixels.show();
    }
    else {
      Serial.println("off4");
        pixels.setPixelColor(3, pixels.Color(0, 0, 0)); // turn off neopixel
        pixels.show();
    }
  }
  else{
    Serial.print("Error in getInt, ");
    Serial.println(firebaseData.errorReason());
  } 
}