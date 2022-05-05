#define echoPin1 9 // attach pin D2 Arduino to pin Echo of HC-SR04
#define pingPin1 8
#define echoPin2 10
#define pingPin2 11 //attach pin D3 Arduino to pin Trig of HC-SR04
#define increase 2
#define decrease 3
#define haptic1 5
#define haptic2 6



volatile int distance1;
volatile int distance2;
volatile int Sensitivity = 110;


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

  Echo1();

  

  Echo2();


}

void Echo1() {
  distance1 = 0;
  for (int i = 0; i < 5; i++) {
    delay(100);

    digitalWrite(pingPin1, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(pingPin1, LOW);

    int duration1 = pulseIn(echoPin1, HIGH);


    distance1 += duration1 * 0.034 / 2;


  }
  distance1 = distance1 / 5;
  Serial.println(distance1);

  if (distance1 < 8) {
    analogWrite(haptic1, Sensitivity);

  } else if (distance1 < 15) {
    analogWrite(haptic1, Sensitivity);
    delay(300);
    analogWrite(haptic1, 0);
    delay(100);
  } else if (distance1 < 30) {
    analogWrite(haptic1, Sensitivity);
    delay(200);
    analogWrite(haptic1, 0);
    delay(100);
  }
  else {
    analogWrite(haptic1, 0);
  }



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
