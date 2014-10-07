#include <SoftwareSerial.h>

#define BUTTON_PIN 4
#define LED_PIN 9

SoftwareSerial sigfox(2, 3);

enum State {
  RED,
  GREEN,
  BLUE,
  SEND
} state;

void setup() {
  Serial.begin(9600);
  sigfox.begin(9600);
  sigfox.setTimeout(10000);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  Serial.println("Ready");
}

char buffer[20];
bool wasHigh = true;
int r, g, b;

void loop() {
  bool low = digitalRead(BUTTON_PIN) == LOW;

  // when pressing the button :
  if (low && wasHigh) {
    wasHigh = false;

    // small state machine to read red, green, blue, then send the value
    switch (state) {
      case RED:
        r = read();
        blink();
        state = GREEN;
        break;
      case GREEN:
        g = read();
        blink();
        state = BLUE;
        break;
      case BLUE:
        b = read();
        blink();
        state = SEND;
        break;
      case SEND:
        send(r, g, b);
        blink();
        blink();
        state = RED;
        break;
    }
  }

  if (!low) {
    wasHigh = true;
  }
}

int read() {
  int flexReading = map(analogRead(0), 130, 270, 0, 255);
  if (flexReading < 0)   flexReading = 0;
  if (flexReading > 255) flexReading = 255;
  Serial.print("Read: ");
  Serial.println(flexReading);
  return flexReading;
}

void send(int r, int g, int b) {
  // format the AT command with data as hexa
  snprintf(buffer, 20, "AT$SS=%02X%02X%02X", r, g, b);
  Serial.println(buffer); // debug

  sigfox.println(buffer);
  if(sigfox.find("OK")) {
    Serial.println("Sent");
  }
}

void blink() {
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);
  delay(200);
}
