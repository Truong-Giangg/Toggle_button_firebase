#include <Adafruit_NeoPixel.h>
#include <FirebaseESP8266.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#define WIFI_SSID "phi tien mang" // your wifi SSID
#define WIFI_PASSWORD "resurrection" //your wifi PASSWORD

#define LedPin 16         // pin d0 as toggle pin
#define NUM_PIXELS 8      //number of rgb led
#define PIN_PIXELS 14     //pin d5 as neopixel input
#define FIREBASE_HOST "toggle-button-3d8-rtdb.firebaseio.com" // change here
#define FIREBASE_AUTH "icOuLI7Mpe04Nv1ABHfAqyvlQn7HI0aYBwlp"  // your private key
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
  if(Firebase.getString(firebaseData, "/Led1Status"))
  {
    String ledstatus = firebaseData.stringData();
    if(ledstatus.toInt() == 1){
      digitalWrite(LedPin, LOW);
      Serial.println("on");
      for(int i =0; i<8; i++){
        pixels.setPixelColor(i, pixels.Color(13, 93, 95));  // #21ecf3 color
      }
        pixels.show();
    }
    else {
      digitalWrite(LedPin, HIGH);
      Serial.println("off");
      for(int i =0; i<8; i++){
        pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // turn off neopixel
      }
        pixels.show();
    }
  }else{
    Serial.print("Error in getInt, ");
    Serial.println(firebaseData.errorReason());
  } 
}