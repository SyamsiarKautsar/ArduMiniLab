/*
  Make sure your Firebase project's '.read' and '.write' rules are set to 'true'. 
  Ignoring this will prevent the MCU from communicating with the database. 
  For more details- https://github.com/Rupakpoddar/ESP32Firebase 
*/

#include <ESP32Firebase.h>

#define _SSID "..."          // Your WiFi SSID
#define _PASSWORD "..."      // Your WiFi Password
#define REFERENCE_URL "..."  // Your Firebase project reference url

Firebase firebase(REFERENCE_URL);

void setup() {
  Serial.begin(115200);
  // pinMode(LED_BUILTIN, OUTPUT);
  // digitalWrite(LED_BUILTIN, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  // Connect to WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(_SSID);
  WiFi.begin(_SSID, _PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }

  Serial.println("");
  Serial.println("WiFi Connected");

  // Print the IP address
  Serial.print("IP Address: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  // digitalWrite(LED_BUILTIN, HIGH);

//================================================================//
//================================================================//

 
  // Example of getting an int.
 
}

void loop() {
  // Nothing
   int arah = firebase.getInt("Manuver");
   Serial.print("Received Int:\t\t");
   Serial.println(arah);
   if (arah == 0){
        //berhenti
   } else if (arah == 1){
        //maju
   } else if (arah == 2){
        //mundur
   }
   delay(300);

}
