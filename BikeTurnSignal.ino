const int led1 = 0;
const int led2 = 1;
const int button = 2;
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long startButton = 0;
unsigned long endButton = 0;
bool ledState1 = false;
bool ledState2 = false;
int buttonState = 1;
int previousButton = 1;
int ledFunction = 0; 
int previousLed = 0;
int buttonPressed = 0;

void setup() {
  //Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(button, INPUT);
  turnOff();
}

void loop() {
  buttonState = digitalRead(button);
  if(ledFunction == 0) {
    turnOff();
  }
  else if(ledFunction == 1) {
    turnLeft();
  }
  else if(ledFunction == 2) {
    turnRight();
  }
  else {
    hazard();
  }
  if(buttonState != previousButton) {
    updateState();
    if(ledFunction == previousLed && buttonPressed >= 2) {
      ledFunction = 0;
      buttonPressed = 0;
      turnOff();
    }
  }
  previousLed = ledFunction;
  previousButton = buttonState;
}

void turnLeft() {
  if (millis() - previousMillis1 >= 500) {
    ledState1 = !ledState1;
    digitalWrite(led1, ledState1);
    previousMillis1 = millis();
  }
}

void updateState() {
  if(buttonState == HIGH) { //button is pressed. LOW because we are using input_pullup
    startButton = millis();
  }
  else {
    endButton = millis();
    int duration = endButton - startButton;
    //Serial.println(duration);
    if(duration >= 20 && duration < 200) {
      turnOff();
      ledFunction = 1;
    }
    else if(duration >= 200 && duration < 1000) {
      turnOff();
      ledFunction = 2;
    }
    else if(duration >= 1000 && duration < 2000) {
      turnOff();
      ledFunction = 3;
    }
    else {
      ledFunction = 0;
    }
    buttonPressed++;
  }
}

void turnRight() {
  if (millis() - previousMillis2 >= 500) {
    ledState2 = !ledState2;
    digitalWrite(led2, ledState2);
    previousMillis2 = millis();
  }
}

void hazard() {
  if (millis() - previousMillis1 >= 500) {
    ledState1 = !ledState1;
    digitalWrite(led1, ledState1);
    digitalWrite(led2, ledState1);
    previousMillis1 = millis();
  }
}

void turnOff() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
}
