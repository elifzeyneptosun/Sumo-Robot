#define TCRT1 A2  // Arka sensör
#define TCRT2 A3  // Sol
#define TCRT3 A4  // Sağ
#define THRESHOLD 1500

// Mesafe sensörleri pinleri (D6-D13 arası)
#define TRIG_FRONT 7
#define ECHO_FRONT 6
#define TRIG_BACK 8
#define ECHO_BACK 9
#define TRIG_RIGHT A0
#define ECHO_RIGHT A1
#define TRIG_LEFT 12
#define ECHO_LEFT 13

// Motor pinleri (L298N Motor Sürücü)
#define MOTOR_LEFT_PWM 10
#define MOTOR_RIGHT_PWM 11
#define MOTOR_LEFT_FORWARD 3
#define MOTOR_LEFT_BACKWARD 2
#define MOTOR_RIGHT_FORWARD 4
#define MOTOR_RIGHT_BACKWARD 5
#define MOTOR_SPEED 130
#define MOTOR_MAXSPEED 200

// Mesafe eşik değeri (cm cinsinden)
#define DISTANCE_THRESHOLD 20  // 20 cm'nin altındaki mesafeleri tespit et

long distanceFront, distanceBack, distanceRight, distanceLeft;
bool right,left,front,back;

int s1, s2, s3;
bool sol_on, sag_on, arka;

// Mesafe sensörü ölçüm işlevi
long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;  // Mesafe hesaplama (cm)
  if(trigPin==7)Serial.println("Ön:"+distance);
  else if(trigPin==8)Serial.println("Arka:"+distance);
  else if(trigPin==12)Serial.println("Sol:"+distance);
  else Serial.println("Sol:"+distance);
  
  return distance;
}

void setup() {
  // Mesafe sensörlerini çıkış ve giriş olarak ayarlayın
  pinMode(TRIG_FRONT, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);
  pinMode(TRIG_BACK, OUTPUT);
  pinMode(ECHO_BACK, INPUT);
  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);
  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);

  // Motor pinlerini çıkış olarak ayarlayın
  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACKWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);
  pinMode(MOTOR_LEFT_PWM, OUTPUT);
  pinMode(MOTOR_RIGHT_PWM, OUTPUT);

  pinMode(TCRT1, INPUT);
  pinMode(TCRT2, INPUT);
  pinMode(TCRT3, INPUT);

  // Seri iletişim başlat
  Serial.begin(9600);  
}

// Motorları ileriye hareket ettirme
void moveForward() {
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
}

// Motorları geriye hareket ettirme
void moveBackward() {
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
}

// Motorları sağa döndürme (-90 derece)
void turnRight90() {
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);  // Sağa dön
}

// Motorları sola döndürme (+90 derece)
void turnLeft90() {
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);  // Sola dön
}

void hizAyarla(int solHiz, int sagHiz) {
  // Motor hızlarını ayarla
  analogWrite(MOTOR_LEFT_PWM, solHiz);
  analogWrite(MOTOR_RIGHT_PWM, sagHiz);
}

// 180 derece dönüş (tam geri)
void turn180() {
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);  // 180 derece dönüş
}

void stopMotors() {
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
}
void mesafeOlc(){
  distanceFront = getDistance(TRIG_FRONT, ECHO_FRONT);  // Ön
  distanceBack = getDistance(TRIG_BACK, ECHO_BACK);    // Arka
  distanceRight = getDistance(TRIG_RIGHT, ECHO_RIGHT);  // Sağ
  distanceLeft = getDistance(TRIG_LEFT, ECHO_LEFT);     // Sol
  right=distanceRight < DISTANCE_THRESHOLD;
  left=distanceLeft < DISTANCE_THRESHOLD;
  front=distanceFront < DISTANCE_THRESHOLD;
  back=distanceBack < DISTANCE_THRESHOLD;
}
void cizgiKontrol(){
  s1 = analogRead(TCRT2);  // Sol ön sensör
  s2 = analogRead(TCRT3);  // Sağ ön sensör
  s3 = analogRead(TCRT1);  // arka
  
  sol_on = s1 > THRESHOLD;
  sag_on = s2 > THRESHOLD;
  arka = s3 > THRESHOLD;
}
void loop() {
  cizgiKontrol();
  // Mesafeleri ölç
  mesafeOlc();
  hizAyarla(255,255);
  if(sol_on){
    moveBackward();
    delay(500);
    turnRight90();
    delay(200);
  }
  
  else if(sag_on){
    moveBackward();
    delay(500);
    turnRight90();
    delay(200);
  }
  else if(arka){
    moveForward();
    delay(500);
  }
  else{//bu kısmın altı herhangi bir çizgi görmeme durumunda yapılacak işlev kısmı
    if(!front&&!back&&!left&&!right){
      while(front||back||left||right){
        moveForward();
        delay(200);
        turnLeft90();
        delay(200);
        mesafeOlc();
      }
    }
    else{
      mesafeOlc();
      if(front){
        moveForward();
        delay(400);
      }
      else if(left){
        turnLeft90();
        delay(400);
      }
      else if(right){
        turnRight90();
        delay(400);
      }
      else if(back){
        turnLeft90();
        delay(800);
      }
    }
    delay(100);
   }
}
