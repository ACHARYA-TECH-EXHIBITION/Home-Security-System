#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <FirebaseArduino.h> 

#define WIFI_SSID "mardes home"
#define WIFI_PASSWORD "Prateek123@@"

#define projectID "warrior-bulls-default-rtdb" //Your Firebase Project ID; can be found in project settings.
#define FIREBASE_HOST "warrior-bulls-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "2JNTy9dXCRiq3Yyf78K9DqOhKZMzwnLeNIgZF5G3"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

int buzzer = 0;                // LED 
int pirPin = 4;                 // PIR Out pin 
int touch = 5;

bool isActive = false;

int pirStat = 0;                   // PIR status
 
void setup() {
    Serial.begin(9600);

  pinMode(buzzer, OUTPUT);     
  pinMode(pirPin, INPUT); 
  pinMode(touch, INPUT);     
 
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  timeClient.begin();
  
}


void work(){
   timeClient.update();
  unsigned long startMillis = millis(); // Start of sample window
  long num = timeClient.getEpochTime();

  
    pirStat = digitalRead(pirPin); 
    if (pirStat == HIGH) {            // if motion detected
    digitalWrite(buzzer, HIGH);  // turn LED ON
    Serial.println("Hey I got you!!!");
    char strBuf[100],strBufH[100];
    sprintf(strBuf, "RECORD/%ld/DETUCTED",num);

    Firebase.setBool(strBuf,true);


  } 
  else {
    digitalWrite(buzzer, LOW); // turn LED OFF if we have no motion
   
  }
}
void loop(){
  


  if (digitalRead(touch) == HIGH) {
    //Serial.print("Touched");
    if (isActive) {
      //START ALL FUNCTIONS
      isActive = false;
    } else {
      //CLOSE WORKING
      isActive = true;
    }
  }


  
  if (!isActive) {;
    work();
  }else{
   
  }
   

}
