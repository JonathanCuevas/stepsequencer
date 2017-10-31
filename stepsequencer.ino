// stepsequencer

int buttonPin[4] = { 36, 35, 34, 33 };
int totalButtons = 4;

int ledPins[4] = { 23, 22, 21, 20 };
int totalLeds = 4;
boolean lastButtonState[4] = { LOW, LOW, LOW, LOW };
boolean buttonState[4] = { LOW, LOW, LOW, LOW };
boolean stepState[3][4] = {
  { HIGH, LOW, HIGH, LOW },
  { HIGH, LOW, LOW, HIGH },
  { LOW, HIGH, HIGH, LOW },
};

int currentStep = 0;
int totalSteps = 3;

int buttonPin1 = A12;
bool lastButtonState1 = LOW;
bool buttonState1 = LOW;

int buttonPin2 = A13;
bool lastButtonState2 = LOW;
bool buttonState2 = LOW;

int ledPinsSequence[3] = { 1, 2, 3 };
int totalLedsSequence = 3;

byte middleC = 60;
byte channel = 1;

int tempo = 0;

unsigned long lastStepTime = 0;


void setup() {
  Serial.begin(9600);

  for (int i = 0; i < totalButtons; i++) {
    pinMode(buttonPin[i], INPUT);
  }
  for (int i = 0; i < totalLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  for (int i = 0; i < totalLedsSequence; i++) {
    pinMode(ledPinsSequence[i], OUTPUT);
  }
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
}

void loop() {
  checkButtons();
  currentSequence();
  currentSequenceBackward();

  for (int i = 0; i < totalLeds; i++) {
    digitalWrite(ledPins[i], stepState[currentStep][i]);
  }

  currentSequenceLeds();
}


void checkButtons() {
  lastButtonState[0] = buttonState[0];
  buttonState[0] = digitalRead(buttonPin[0]);

  if (buttonState[0] == HIGH && lastButtonState[0] == LOW) {
    if (stepState[currentStep][0] == LOW) {
      stepState[currentStep][0] = HIGH;
    } else if (stepState[currentStep][0] == HIGH) {
      stepState[currentStep][0] = LOW;
    }
  }


  lastButtonState[1] = buttonState[1];
  buttonState[1] = digitalRead(buttonPin[1]);

  if (buttonState[1] == HIGH && lastButtonState[1] == LOW) {
    if (stepState[currentStep][1] == LOW) {
      stepState[currentStep][1] = HIGH;
    } else if (stepState[currentStep][1] == HIGH) {
      stepState[currentStep][1] = LOW;
    }
  }


  lastButtonState[2] = buttonState[2];
  buttonState[2] = digitalRead(buttonPin[2]);

  if (buttonState[2] == HIGH && lastButtonState[2] == LOW) {
    if (stepState[currentStep][2] == LOW) {
      stepState[currentStep][2] = HIGH;
    } else if (stepState[currentStep][2] == HIGH) {
      stepState[currentStep][2] = LOW;
    }
  }


  lastButtonState[3] = buttonState[3];
  buttonState[3] = digitalRead(buttonPin[3]);

  if (buttonState[3] == HIGH && lastButtonState[3] == LOW) {
    if (stepState[currentStep][3] == LOW) {
      stepState[currentStep][3] = HIGH;
    } else if (stepState[currentStep][3] == HIGH) {
      stepState[currentStep][3] = LOW;
    }
  }
}

void currentSequence() {
  lastButtonState1 = buttonState1;
  buttonState1 = digitalRead(buttonPin1);


  tempo = analogRead(A0);

  if (millis() > lastStepTime + tempo) {   //if its time to go to the next step...
    currentStep = currentStep + 1;         //increment to the next step
    if (currentStep > 3) {
      currentStep = 0;
    }

    if (stepState[0][currentStep] == HIGH) {
      usbMIDI.sendNoteOn(60, 127, channel);
    }
    if (stepState[1][currentStep] == HIGH) {
      usbMIDI.sendNoteOn(62, 127, channel);
    }
    if (stepState[2][currentStep] == HIGH) {
      usbMIDI.sendNoteOn(64, 127, channel);
    }

    lastStepTime = millis();               //set lastStepTime to the current time
  }
}

void currentSequenceBackward() {
  lastButtonState2 = buttonState2;
  buttonState2 = digitalRead(buttonPin2);


  tempo = analogRead(A0);

  if (millis() > lastStepTime + tempo) {   //if its time to go to the next step...
    currentStep = currentStep - 1;         //increment to the next step
    if (currentStep < -1) {
      currentStep = 2;
    }

    if (stepState[0][currentStep] == HIGH) {
      usbMIDI.sendNoteOn(60, 127, channel);
    }
    if (stepState[1][currentStep] == HIGH) {
      usbMIDI.sendNoteOn(62, 127, channel);
    }
    if (stepState[2][currentStep] == HIGH) {
      usbMIDI.sendNoteOn(64, 127, channel);
    }

    lastStepTime = millis();               //set lastStepTime to the current time
  }
}

void currentSequenceLeds() {
  for (int i = 0; i < totalLedsSequence; i++) {
    if (currentStep == i) {
      digitalWrite(ledPinsSequence[i], HIGH);
    } else {
      digitalWrite(ledPinsSequence[i], LOW);
    }
  }
}
