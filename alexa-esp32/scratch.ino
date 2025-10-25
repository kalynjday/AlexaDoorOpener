// #include <WiFi.h>
// #include <SinricPro.h>
// #include <SinricProGarageDoor.h>
// #include <Arduino.h>

// // === Motor Pins ===
// const int motorForward = 5;   // Close
// const int motorBackward = 6;  // Open
// const int motorEnable = 9;    // Enable motor controller

// // === Wi-Fi & SinricPro Credentials ===
// const char* ssid = "Ryan iPhone";
// const char* password = "12345678";
// const char* apiKey = "2d299b34-435a-42fb-8847-bde4607b97f7";
// const char* deviceID = "68fd07465918d860c0aa7dc2";

// // === Motor Timer ===
// unsigned long motorStartTime = 0;
// const unsigned long motorRunTime = 5000; // Motor runs for 5 seconds
// bool motorRunning = false;

// // === Door State ===
// bool doorOpen = false;  // false = closed, true = open

// // === Motor Control Functions ===
// void motorForwardOn() {
//   digitalWrite(motorBackward, LOW);
//   digitalWrite(motorForward, HIGH);
//   motorStartTime = millis();
//   motorRunning = true;
//   Serial.println("Motor FORWARD (CLOSE)");
// }

// void motorBackwardOn() {
//   digitalWrite(motorForward, LOW);
//   digitalWrite(motorBackward, HIGH);
//   motorStartTime = millis();
//   motorRunning = true;
//   Serial.println("Motor BACKWARD (OPEN)");
// }

// void motorStop() {
//   digitalWrite(motorForward, LOW);
//   digitalWrite(motorBackward, LOW);
//   motorRunning = false;
//   Serial.println("Motor STOPPED");
// }

// // === Garage Door Callback ===
// bool onGarageDoor(const String &deviceId, bool &state) {
//   if (deviceId != deviceID) return false;

//   if (state && !doorOpen) {      // Alexa Open command & door not open
//     motorBackwardOn();
//     doorOpen = true;
//     Serial.println("Command: OPEN");
//   }
//   else if (!state && doorOpen) { // Alexa Close command & door is open
//     motorForwardOn();
//     doorOpen = false;
//     Serial.println("Command: CLOSE");
//   }
//   else {
//     Serial.println("No action needed, door already in requested state.");
//   }

//   return true;
// }

// // === Create Garage Door device ===
// SinricProGarageDoor myGarageDoor(deviceID);

// void setup() {
//   Serial.begin(115200);

//   // Motor pins
//   pinMode(motorForward, OUTPUT);
//   pinMode(motorBackward, OUTPUT);
//   pinMode(motorEnable, OUTPUT);
//   digitalWrite(motorEnable, HIGH);  // Enable motor controller
//   motorStop();

//   // Connect Wi-Fi
//   Serial.print("Connecting to Wi-Fi");
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("\n✅ Wi-Fi Connected");

//   // Initialize SinricPro
//   SinricPro.begin(apiKey, ssid, password);

//   // Attach callback to Garage Door
//   myGarageDoor.onDoorState(onGarageDoor);

//   Serial.println("📡 Waiting for Alexa commands...");
// }

// void loop() {
//   SinricPro.handle();

//   // Auto-stop motor after motorRunTime milliseconds
//   if (motorRunning && (millis() - motorStartTime >= motorRunTime)) {
//     motorStop();
//   }
// }