/*
   Sensitivity buttons
   Lower Power Battery Sensor
   Turn on and off the glasses front and back
   Overall on off switch




*/

#define echoPin1 9 // attach pin D2 Arduino to pin Echo of HC-SR04
#define pingPin1 8
#define echoPin2 10
#define pingPin2 11 //attach pin D3 Arduino to pin Trig of HC-SR04
#define increase 2
#define decrease 3
#define haptic1 5
#define haptic2 6



volatile float distance1;
volatile float distance2;
volatile int Sensitivity = 110;

volatile float avgD1[10];
volatile float avgD1Off[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
volatile float avgD1Num = 0;
volatile int k1 = 0;

volatile float avgD2[10];
volatile float avgD2Off[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
volatile float avgD2Num = 0;
volatile int k2 = 0;


volatile int i = 0;



void Echo1();
void Echo2();

void setup() {

  // put your setup code here, to run once:
  pinMode(haptic1, OUTPUT);
  pinMode(haptic2, OUTPUT);
  pinMode(pingPin1, OUTPUT); // Sets the pingPin as an OUTPUT
  pinMode(pingPin2, OUTPUT);
  pinMode(echoPin1, INPUT); // Sets the echoPin as an INPUT
  pinMode(echoPin2, INPUT); // Sets the echoPin as an INPUT
  pinMode(increase, INPUT);
  pinMode(decrease, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:


  Echo1();

  checkArray(avgD1,avgD1Num,avgD1Off,distance1,k1);

  



 // Echo2();

  i++;
}

void Echo1() {



  digitalWrite(pingPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin1, LOW);

  int duration1 = pulseIn(echoPin1, HIGH);


  distance1 = duration1 * 0.034 / 2;



  //  distance1 = distance1 / 5;
  //  Serial.println(distance1);
  //
  //  if (distance1 < 8) {
  //    analogWrite(haptic1, Sensitivity);
  //
  //  } else if (distance1 < 15) {
  //    analogWrite(haptic1, Sensitivity);
  //    delay(300);
  //    analogWrite(haptic1, 0);
  //    delay(100);
  //  } else if (distance1 < 30) {
  //    analogWrite(haptic1, Sensitivity);
  //    delay(200);
  //    analogWrite(haptic1, 0);
  //    delay(100);
  //  }
  //  else {
  //    analogWrite(haptic1, 0);
  //  }



}

void Echo2() {
  distance2 = 0;
  for (int i = 0; i < 5; i++) {
    delay(100);

    digitalWrite(pingPin2, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(pingPin2, LOW);

    int duration2 = pulseIn(echoPin2, HIGH);
    distance2 += duration2 * 0.034 / 2;
  }
  distance2 = distance2 / 5;

  Serial.println(distance2);

  if (distance2 < 8) {
    analogWrite(haptic2, Sensitivity);

  } else if (distance2 < 15) {
    analogWrite(haptic2, Sensitivity);
    delay(300);
    analogWrite(haptic2, 0);
    delay(100);
  } else if (distance2 < 30) {
    analogWrite(haptic2, Sensitivity);
    delay(200);
    analogWrite(haptic2, 0);
    delay(100);
  }
  else {
    analogWrite(haptic2, 0);
  }

}

void sensitivity() {
  while (digitalRead(increase)) {
    if (Sensitivity < 130) {

      Sensitivity += 5;
      analogWrite(haptic1, Sensitivity);
      analogWrite(haptic2, Sensitivity);
    } else {
      delay(500);
      analogWrite(haptic1, 0);
      analogWrite(haptic2, 0);
    }
    delay(300);
  }

  while (digitalRead(decrease)) {
    if (Sensitivity > 50) {

      Sensitivity -= 5;
      analogWrite(haptic1, Sensitivity);
      analogWrite(haptic2, Sensitivity);
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
  for (int i = 0; i < 10; i++) {
    avg += arr[i];
  }
  avg = avg / 10.0;
  return avg;
}



void checkArray(volatile float avgD[], volatile float &avgDNum, volatile float avgDOff[], volatile float distance, volatile int &k){
  if (i < 10) {
    avgD[i] = distance;
      
  } else if (i == 10) {
    avgDNum = getAverage(avgD);
    for (int j = 0; j < 10; j++) {
        Serial.print(avgD[j]);
      }
      Serial.println();
  } else if (i > 10) {
    if (distance < avgDNum * 1.2 && distance > avgDNum * 0.8) {
      avgD[i % 10] = distance;
      avgDNum = getAverage(avgD);
      k = 0;
    } else {
      avgDOff[k % 10] = distance;
      k++;
      if (k == 10) {

        for (int j = 0; j < 10; j++) {
          avgD[j] = avgDOff[j];
          Serial.print(avgD[j]);
          avgDOff[j] = 0;
        }
        Serial.println("Changed Array");
      }
    }
  }
}

//  if (i < 10) {
//    avgD1[i] = distance1;
//  } else if (i == 10) {
//    avgD1Num = getAverage(avgD1);
//  } else if (i > 10) {
//    if (distance1 < avgD1Num * 1.2 && distance1 > avgD1Num * 0.8) {
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
