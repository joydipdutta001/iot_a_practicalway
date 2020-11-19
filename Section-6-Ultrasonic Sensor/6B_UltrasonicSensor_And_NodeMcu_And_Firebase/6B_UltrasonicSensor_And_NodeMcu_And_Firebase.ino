/* created by Joydip Dutta, http://cybotians.com
 Organization: CYBOTIANS
    Ultrasonic sensor Pins:
        VCC -> +5VDC ( Coming from the 5v pin of the Power module )
        Trig -> Trigger (INPUT) -> D2 Or GPIO-4
        Echo -> Echo (OUTPUT) -> D1 Or GPIO-5
        GND(Ultrasonic Sensor) -> GND(NodeMCU) -> GND(power module's 5v and 3.3v pins)
 */
 
#include<ESP8266WiFi.h>
#include "FirebaseESP8266.h" //Install this library from library manager

#define FIREBASE_HOST "###########.firebaseio.com" //Database link without "http://" and "/" in the end.
#define FIREBASE_AUTH "################################" //Database secret key

FirebaseData firebaseData;

const int trigP = 4;  //D2 Or GPIO-4 of nodemcu
const int echoP = 5;  //D1 Or GPIO-5 of nodemcu

long duration;
int distance;

void setup() {
Serial.begin(115200); 
    WiFi.begin("######", "#####"); // mention your wifi ssid and password
  Serial.print("Connecting to Wi-Fi");

   while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  
  pinMode(trigP, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoP, INPUT);      // Open serial channel at 9600 baud rate


  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
}

void loop() {

digitalWrite(trigP, LOW);   // Makes trigPin low
delayMicroseconds(2);       // 2 micro second delay 

digitalWrite(trigP, HIGH);  // tigPin high
delayMicroseconds(10);      // trigPin high for 10 micro seconds
digitalWrite(trigP, LOW);   // trigPin low

duration = pulseIn(echoP, HIGH);   //Read echo pin, time in microseconds
distance= duration*0.034/2;        //Calculating actual/real distance

if (distance > 8)
   { 
        if (Firebase.setInt(firebaseData,"/#########",1)) // mention the child path of the database where you send to the value
        {
          Serial.println("PASSED Reading");
        }
        delay(1000);
   } 
   else 
   { 
      if (Firebase.setInt(firebaseData,"/##########",0)) // mention the child path of the database where you send to the value
        {
          Serial.println("PASSED no Reading ");
        }
        delay(1000);
      
   } 
delay(3000);                        //Pause for 3 seconds and start measuring distance again
}
