/*
   sensitivity buttons
   Lower Power Battery Sensor
   Turn on and off the glasses front and back
   Overall on off switch
*/
const uint8_t echoPin1 = 4;
const uint8_t echoPin2 = A0;
const uint8_t echoPin3 = 6;
const uint8_t echoPin4 = 2;
const uint8_t increase = 8;
const uint8_t  decrease = 9;

const uint8_t  haptic1 = 5;
const uint8_t  haptic2 = A1;
const uint8_t  haptic3 = 7;
const uint8_t  haptic4 = 3;
const uint8_t  voltage = A2;


volatile float distance1;
volatile float distance2;
volatile float distance3;
volatile float distance4;
volatile int sensitivity = 110;


volatile float avgD1[50];
volatile float avgD1Off[50];
volatile float avgD1Num = 0;
volatile int k1 = 0;

volatile float avgD2[50];
volatile float avgD2Off[50];
volatile float avgD2Num = 0;
volatile int k2 = 0;

volatile float avgD3[50];
volatile float avgD3Off[50];
volatile float avgD3Num = 0;
volatile int k3 = 0;

volatile float avgD4[50];
volatile float avgD4Off[50];
volatile float avgD4Num = 0;
volatile int k4 = 0;




volatile int i = 0;
bool vFlag = 1;




void setup() {

  pinMode(haptic1, OUTPUT);
  pinMode(haptic2, OUTPUT);
  pinMode(haptic3, OUTPUT);
  pinMode(haptic4, OUTPUT);
  pinMode(increase, INPUT);
  pinMode(decrease, INPUT);
  pinMode(voltage, INPUT);
  Serial.begin(115200);

}

void loop() {
  Sensitivity();
  do {
    distance1 = Echo(echoPin1);

  } while (distance1 < 0);
  checkArray(avgD1, avgD1Num, avgD1Off, distance1, k1);


  do {
    Echo(echoPin2);
  } while (distance2 < 0);
  checkArray(avgD2, avgD2Num, avgD2Off, distance2, k2);

  do {
    Echo(echoPin3);
  } while (distance3 < 0);
  checkArray(avgD3, avgD3Num, avgD3Off, distance3, k3);

  do {
    Echo(echoPin4);
  } while (distance4 < 0);
  checkArray(avgD4, avgD4Num, avgD4Off, distance4, k4);


  int voltage = analogRead(voltage) * (5.0 / 1023.0);
  if (voltage < 3.5 && vFlag) {
    ALERT();
    vFlag = 0;
  }



  if (distance1 < 40) {
    analogWrite(haptic1, sensitivity);
  } else if (distance1 < 90  && i % 10 == 0) {
    analogWrite(haptic1, sensitivity);
  } else if (distance1 < 120 && i % 20 == 0 ) {
    analogWrite(haptic1, sensitivity);
  } else if (i % 5 == 0) {
    analogWrite(haptic1, 0);
  }
  if (distance2 < 40) {
    analogWrite(haptic2, sensitivity);
  } else if (distance2 < 90  && i % 10 == 0) {
    analogWrite(haptic2, sensitivity);
  } else if (distance2 < 120 && i % 20== 0 ) {
    analogWrite(haptic2, sensitivity);
  } else if (i % 5 == 0) {
    analogWrite(haptic2, 0);
  }
  if (distance3 <40) {
    analogWrite(haptic3, sensitivity);
  } else if (distance3 < 90  && i % 10 == 0) {
    analogWrite(haptic3, sensitivity);
  } else if (distance3 < 120&& i % 20 == 0 ) {
    analogWrite(haptic3, sensitivity);
  } else if (i % 5 == 0) {
    analogWrite(haptic3, 0);
  }
  if (distance4 < 40) {
    analogWrite(haptic4, sensitivity);
  } else if (distance4 < 90  && i % 10 == 0) {
    analogWrite(haptic4, sensitivity);
  } else if (distance4 < 120 && i % 20== 0 ) {
    analogWrite(haptic4, sensitivity);
  } else if (i % 5 == 0) {
    analogWrite(haptic4, 0);
  }

  i++;
}

volatile float Echo(uint8_t pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  digitalWrite(pin, HIGH);
  delayMicroseconds(20);
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);
  float duration = pulseIn(pin, HIGH);
  float distance = duration * 0.034 / 2.0;
  return distance;
}

void Sensitivity() {
  while (digitalRead(increase)) {
    if (sensitivity < sensitivity) {

      sensitivity += 20;
      analogWrite(haptic1, sensitivity);
      analogWrite(haptic2, sensitivity);
    } else {
      delay(500);
      analogWrite(haptic1, 0);
      analogWrite(haptic2, 0);
    }
    delay(300);
  }

  while (digitalRead(decrease)) {
    if (sensitivity > 30) {

      sensitivity -= 20;
      analogWrite(haptic1, sensitivity);
      analogWrite(haptic2, sensitivity);
    } else {
      delay(500);
      analogWrite(haptic1, 0);
      analogWrite(haptic2, 0);
    }
    delay(300);
  }
}

float getAverage(volatile float arr[]) {
  float avg = 0;
  for (int i = 0; i < 50; i++) {
    avg += arr[i];
  }
  avg = avg / 50.0;
  return avg;
}
void ALERT() {
  analogWrite(haptic1, sensitivity);
  analogWrite(haptic2, sensitivity);
  delay(1000);
  analogWrite(haptic1, 0);
  analogWrite(haptic2, 0);
  delay(1000);
  analogWrite(haptic1, sensitivity);
  analogWrite(haptic2, sensitivity);
  delay(1000);
  analogWrite(haptic1, 0);
  analogWrite(haptic2, 0);
}


void checkArray(volatile float avgD[], volatile float &avgDNum, volatile float avgDOff[], volatile float distance, volatile int &k) {

  if (i < 50) {
    avgD[i] = distance;

  } else if (i == 50) {
    avgDNum = getAverage(avgD);
    for (int j = 0; j < 50; j++) {

      Serial.print(avgD[j]);
      Serial.print(" ");
    }
    Serial.println();
  } else if (i > 50) {
    if (distance < avgDNum * 1.2 && distance > avgDNum * 0.8) {
      avgD[i % 50] = distance;
      avgDNum = getAverage(avgD);
      k = 0;
      if (i % 50 == 0) {
        for (int j = 0; j < 50; j++) {

          Serial.print(avgD[j]);
          Serial.print(" ");
        }
        Serial.print("   Avg: ");
        Serial.println(avgDNum);
      }
    } else {
      avgDOff[k % 50] = distance;
      k++;
      if (k == 50) {

        for (int j = 0; j < 50; j++) {
          avgD[j] = avgDOff[j];
          Serial.print(avgD[j]);
          Serial.print(" ");
          avgDOff[j] = 0;
        }
        avgDNum = getAverage(avgD);
        Serial.print("Changed Array Avg: ");
        Serial.println(avgDNum);
        k = 0;
      }
    }
  }
}



//  if (i < 10) {
//    avgD1[i] = distance1;
//  } else if (i == 10) {
//    avgD1Num = getAverage(avgD1);
//  } else if (i > 10) {
//    if (distance1 < avgD1Num+10 && distance1 > avgD1Num -10) {
//      avgD1[i % 10] = distance1;
//      avgD1Num = getAverage(avgD1);
//      k = 0;
//    } else {
//      avgD1Off[k1 % 10] = distance1;
//      k1++;
//      if (k1 == 10) {
//
//        for (int j = 0; j < 10; j++) {
//          avgD1[j] = avgD1Off[j];
//          avgD1Off[j] = 0;
//        }
//      }
//    }
//  }