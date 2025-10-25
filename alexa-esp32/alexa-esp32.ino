#include <WiFi.h>
#include <Espalexa.h>

Espalexa espalexa;

// Replace with your Wi-Fi credentials
const char* WIFI_SSID = "Mariami";
const char* WIFI_PASSWORD = "mjcam9eirib7c";

// === Motor Pins ===
const int motorForward = GPIO_NUM_6;   // Close
const int motorBackward = GPIO_NUM_15;  // Open
const int motorEnable = GPIO_NUM_10;    // Enable motor controller

// === Motor Control Functions ===
void motorForwardOn() {
  digitalWrite(motorBackward, LOW);
  digitalWrite(motorForward, HIGH);
  Serial.println("Motor FORWARD (CLOSE)");
}

void motorBackwardOn() {
  digitalWrite(motorForward, LOW);
  digitalWrite(motorBackward, HIGH);
  Serial.println("Motor BACKWARD (OPEN)");
}

void motorStop() {
  digitalWrite(motorForward, LOW);
  digitalWrite(motorBackward, LOW);
  Serial.println("Motor STOPPED");
}

void wifiSetup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\n✅ Connected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

bool prevOn = 0;
void deviceStateChange(uint8_t x, bool y) {
  Serial.printf("In 1 %d in 2 %d\n", x, y);
  if (x > 0 && !prevOn)
  {
    // go!
    motorForwardOn();
    delay(5000);
    motorStop();
    prevOn = true;
  } else if ( x == 0 && prevOn)
  {
    // reverse!
    motorBackwardOn();
    delay(5000);
    motorStop();
    prevOn = false;
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(motorForward, OUTPUT);
  pinMode(motorBackward, OUTPUT);
  pinMode(motorEnable, OUTPUT);
  digitalWrite(motorEnable, HIGH);  // Enable motor controller

  wifiSetup();

  espalexa.addDevice("door opener", deviceStateChange);
  espalexa.begin();
}

void loop() {
  espalexa.loop();
}


