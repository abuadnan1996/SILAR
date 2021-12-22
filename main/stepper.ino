void goInit() {
  /* Initialize in y direction */
  digitalWrite(7, 1); // stepperY.cwPin = 7 and 1 for up direction
  while (digitalRead(yLimit)) {
    stepperY.takeOneStep(150);
  }

  digitalWrite(7, 0); // stepperY.cwPin = 7 and 0 for down direction
  while (!digitalRead(yLimit)) {
    stepperY.takeOneStep(150);
  }
  stepperY.stepsPerMicro(-3200, 150); // For releasing the limit switch

  //  /* Pull the slide upwards */
  //  stepperY.stepsPerMicro(50000, 200);

  /* Initialize in x direction */
  digitalWrite(5, 0); // stepperX.cwPin = 5 and 0 for left direction
  while (digitalRead(xLimit)) {
    stepperX.takeOneStep(300);
  }

  /* Initialize in y direction */
  digitalWrite(7, 0); // stepperY.cwPin = 7 and 0 for down direction
  while (digitalRead(yLimit)) {
    stepperY.takeOneStep(150);
  }
}

void goFromTo(uint8_t startPos, uint8_t targetPos) {
  long inBetweenSteps = X_LENGTH / 5;
  stepperX.stepsPerChangingMicro((targetPos - startPos)*inBetweenSteps, 1000, 200);
}

void handleDipping(uint8_t currentPos) {
  int stepTime = (rinseTime * 1000000 - 1000000) / 3200 / 2;
  if (currentPos == 1 || currentPos == 3) {
    delay(dipTime * 1000);
  } else {
    stepper360.stepsPerMicro(3200, stepTime);
    delay(1000);
    stepper360.stepsPerMicro(-3200, stepTime);
  }
}

void handleStirrer(uint8_t currentPos, uint8_t state) {
  if (state) {
    if (currentPos == 1) {
      digitalWrite(stirrer1Pin, 0);
    } else if (currentPos == 3) {
      digitalWrite(stirrer2Pin, 0);
    }
  } else {
    digitalWrite(stirrer1Pin, stirrerOn[0]);
    digitalWrite(stirrer2Pin, stirrerOn[1]);
  }
}
void complete()
{
  Serial.println("In Complete Function");
  /* Initialize in y direction */
  digitalWrite(7, 1); // stepperY.cwPin = 7 and 1 for up direction
  while (digitalRead(yLimit)) {
    stepperY.takeOneStep(100);
  }

  digitalWrite(7, 0); // stepperY.cwPin = 7 and 0 for down direction
  while (!digitalRead(yLimit)) {
    stepperY.takeOneStep(100);
  }
  stepperY.stepsPerMicro(-3200, 100); // For releasing the limit switch

  //  /* Pull the slide upwards */
  //  stepperY.stepsPerMicro(50000, 200);

  /* Initialize in x direction */
//  Serial.println("GOING LEFT");
//  digitalWrite(5, HIGH); // stepperX.cwPin = 5 and 0 for left direction
//  delay(1000);
//  while (digitalRead(xLimit)) {
//    stepperX.takeOneStep(200);
//  }

 
}
