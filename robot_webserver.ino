// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "F14B";
const char* password = "14141414";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String manuver = "berhenti";

//---------------------------
//ubah pin sesuai pin yang terhubung dengan l298
const int dirKanan = 26;
const int dirKiri = 27;
const int pwmKanan = 16;
const int pwmKiri = 17;


// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

//tambahkan gerakan di sini:
void gerakan_maju(){
  //..........
  
}
void gerakan_mundur(){
  //............
}

void gerakan_bkanan(){
  //..............
}

void gerakan_bkiri(){
  //.............
}

void gerakan_angkat(){
  //.............
}

void gerakan_turun(){
  //.............
}

void gerakan_berhenti(){
  //.............
  
}


//---------------------------


void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(dirKanan, OUTPUT);
  pinMode(dirKiri, OUTPUT);
  pinMode(pwmKanan, OUTPUT);
  pinMode(pwmKiri, OUTPUT);
  
  // Set outputs to LOW : opsional
  digitalWrite(dirKanan, LOW);
  digitalWrite(dirKiri, LOW);
  digitalWrite(pwmKanan, LOW);
  digitalWrite(pwmKiri, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            //------------------------------------------------
            //modifikasi untuk gerakan robot
            if (header.indexOf("GET /maju") >= 0) {
              Serial.println("maju");
              manuver = "maju";
              gerakan_maju();
            } else if (header.indexOf("GET /mundur") >= 0) {
              Serial.println("mundur");
              manuver = "mundur";
              gerakan_mundur();
            } else if (header.indexOf("GET /berhenti") >= 0) {
              Serial.println("berhenti");
              manuver = "berhenti";
              gerakan_berhenti();
            } else if (header.indexOf("GET /bkanan") >= 0) {
              Serial.println("belok kanan");
              manuver = "bkanan";
              gerakan_bkanan();
            } else if (header.indexOf("GET /bkiri") >= 0) {
              Serial.println("belok kiri");
              manuver = "bkiri";
              gerakan_bkiri();
            } else if (header.indexOf("GET /angkat") >= 0) {
              Serial.println("servo angkat");
              manuver = "angkat";
              gerakan_angkat();
            } else if (header.indexOf("GET /turun") >= 0) {
              Serial.println("servo turun");
              manuver = "turun";
              gerakan_turun();
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Robotic Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p>Kondisi Robot: " + manuver + "</p>");
            client.println("<p><a href=\"/maju\"><button class=\"button\">MAJU</button></a></p>");
            client.println("<p><a href=\"/mundur\"><button class=\"button\">MUNDUR</button></a></p>");
            client.println("<p><a href=\"/berhenti\"><button class=\"button\">BERHENTI</button></a></p>");
            client.println("<p><a href=\"/bkanan\"><button class=\"button\">BELOK KANAN</button></a></p>");
            client.println("<p><a href=\"/bkiri\"><button class=\"button\">BELOK KIRI</button></a></p>");
            client.println("<p><a href=\"/angkat\"><button class=\"button\">SERVO ANGKAT</button></a></p>");
            client.println("<p><a href=\"/turun\"><button class=\"button\">SERVO TURUN</button></a></p>");
               
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
