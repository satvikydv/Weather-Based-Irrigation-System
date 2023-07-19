#include <HTTPUpdateServer.h>

#include <HTTPUpdate.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

#include <ThingSpeak.h>

#define CHANNEL_ID 2172932
#define CHANNEL_API_KEY  "73Y0OEPCS85HRQ2W"

WiFiClient client;

int moisture,sensor_analog;
//soil moisture analog input pin on board -- vp
const int sensor_pin = A0;  /* Soil moisture sensor O/P pin */
const int RELAY_PIN = 22;


const char* ssid = "Maidens";
const char* password = "123456789";

// Your Domain name with URL path or IP address with path
String openWeatherMapApiKey = "2d5e824e6ef86655a5f93f4186c94853";
// Example:
//String openWeatherMapApiKey = "2d5e824e6ef86655a5f93f4186c94853";

// Replace with your country code and city
String city = "Raipur";
String countryCode = "IN";

// THE DEFAULT TIMER IS SET TO 10 SECONDS FOR TESTING PURPOSES
// For a final application, check the API call limits per hour/minute to avoid getting blocked/banned
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 10 seconds (10000)
unsigned long timerDelay = 10000;

String jsonBuffer;

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT); //for relay module

  ThingSpeak.begin(client);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");
}

void loop() {
  
  sensor_analog = analogRead(sensor_pin);
  moisture = ( 100 - ( (sensor_analog/4095.00) * 100 ) );
  Serial.print("Moisture = ");
  Serial.print(moisture);  /* Print moisture on the serial window */
  Serial.println("%");
  ThingSpeak.writeField(CHANNEL_ID, 1, moisture, CHANNEL_API_KEY);
  delay(5000);              
  
  // Send an HTTP GET request
  if ((millis() - lastTime) > timerDelay) {
    // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&APPID=" + openWeatherMapApiKey;
      
      jsonBuffer = httpGETRequest(serverPath.c_str());
//      Serial.println(jsonBuffer);
      JSONVar myObject = JSON.parse(jsonBuffer);
  
      // JSON.typeof(jsonVar) can be used to get the type of the var
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
    
//      Serial.print("JSON object = ");
//      Serial.println(myObject);
//      Serial.print("City: ");
//      Serial.println(myObject["city"]["name"]);
      Serial.print("Temperature: ");
      int temperature = int (myObject["main"]["temp"]);
      Serial.println(temperature - 272);
      Serial.print("Pressure: ");
      Serial.println(myObject["main"]["pressure"]);
      Serial.print("Humidity: ");
      Serial.println(myObject["main"]["humidity"]);
      Serial.print("Wind Speed: ");
      Serial.println(myObject["wind"]["speed"]);
      Serial.println();
      Serial.print("Cloudiness (in %) : ");
      Serial.println(myObject["clouds"]["all"]);
      Serial.print("Rain (hourly in mm ) : ");
      Serial.println(myObject["rain"]["1h"]);
//      Serial.print("Chances of rain (next 3h)");
//      Serial.println(myObject["rain"]["3h"]);
      double rain = double (myObject["rain"]["1h"]);
      int cloud = int (myObject["clouds"]["all"]);
      
      Serial.println(rain);
      int temp = temperature - 272;
    if(cloud > 70){
      Serial.println("High Chances of rain today");
    }
      if(temp >= 40){
        if(moisture < 50){
          Serial.println("pump on");
          digitalWrite(RELAY_PIN, LOW);
        }
        if(moisture > 80){
          Serial.println("pump off");
          digitalWrite(RELAY_PIN, HIGH);
        }
        
      }
      


      
      if(temp < 40 && temp > 30){
        if (rain >= 2){
          if(moisture < 40){
          Serial.println("pump on");
          digitalWrite(RELAY_PIN, LOW);
        }
        if(moisture > 74){
          Serial.println("pump off");
          digitalWrite(RELAY_PIN, HIGH);
        }
        }
        if (rain < 2 && rain > 1){
          if(moisture < 35){
          Serial.println("pump on");
          digitalWrite(RELAY_PIN, LOW);
        }
        if(moisture > 68){
          Serial.println("pump off");
          digitalWrite(RELAY_PIN, HIGH);
        }
        }
        if(rain < 1){
          if(moisture < 35){
          Serial.println("pump on");
          digitalWrite(RELAY_PIN, LOW);
        }
        if(moisture > 65){
          Serial.println("pump off");
          digitalWrite(RELAY_PIN, HIGH);
        }
      }
      else{
        if(moisture < 20){
          Serial.println("pump on");
          digitalWrite(RELAY_PIN, LOW);
        }
        if(moisture > 55){
          Serial.println("pump off");
          digitalWrite(RELAY_PIN, HIGH);
        }
      }
      }

      
      if(temp < 30) {
        if (rain >= 2){
          if(moisture < 30){
          Serial.println("pump on");
          digitalWrite(RELAY_PIN, LOW);
        }
        if(moisture > 40){
          Serial.println("pump off");
          digitalWrite(RELAY_PIN, HIGH);
        }
        }
        if (rain < 2 && rain > 1){
          if(moisture < 13){
          Serial.println("pump on");
          digitalWrite(RELAY_PIN, LOW);
        }
        if(moisture > 50){
          Serial.println("pump off");
          digitalWrite(RELAY_PIN, HIGH);
        }
      }
      if(rain < 1){
          if(moisture < 20){
          Serial.println("pump on");
          digitalWrite(RELAY_PIN, LOW);
        }
        if(moisture > 55){
          Serial.println("pump off");
          digitalWrite(RELAY_PIN, HIGH);
        }
      }
      else{
        if(moisture < 20){
          Serial.println("pump on");
          digitalWrite(RELAY_PIN, LOW);
        }
        if(moisture > 55){
          Serial.println("pump off");
          digitalWrite(RELAY_PIN, HIGH);
        }
      }
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
