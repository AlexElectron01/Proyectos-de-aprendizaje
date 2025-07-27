#include <Servo.h>

// Pines del sensor ultrasónico
const int trigPin = 11;
const int echoPin = 12;

// Pines del servo
const int servoPin = 10;
Servo sensorServo;

// Pines del L298N
const int IN1 = 5;
const int IN2 = 4;
const int IN3 = 3;
const int IN4 = 2;
const int ENA = 6;
const int ENB = 9;

// Distancia mínima para reaccionar (en cm)
const int distanciaMinima = 15;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  sensorServo.attach(servoPin);
  sensorServo.write(90); // centrar el servo
  delay(500);
}

void loop() {
  // Escanear tres direcciones
  int distCentro = escanear(90);
  int distIzq = escanear(120);
  int distDer = escanear(60);

  Serial.print("Centro: "); Serial.print(distCentro);
  Serial.print(" | Izquierda: "); Serial.print(distIzq);
  Serial.print(" | Derecha: "); Serial.println(distDer);

  if (distCentro > distanciaMinima) {
    avanzar();
  } else {
    if (distIzq > distDer && distIzq > distanciaMinima) {
      girarIzquierda();
    } else if (distDer > distanciaMinima) {
      girarDerecha();
    } else {
      retroceder();
    }
  }

  delay(100); // breve pausa entre ciclos
}

// Función para escanear en un ángulo y devolver distancia
int escanear(int angulo) {
  sensorServo.write(angulo);
  delay(300);
  return medirDistancia();
}

// Medir distancia con HC-SR04
int medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracion = pulseIn(echoPin, HIGH, 30000); // timeout 30ms
  int distancia = duracion * 0.034 / 2;

  // Limitar distancia a 100 cm para evitar valores erráticos
  if (distancia == 0 || distancia > 100) distancia = 100;
  return distancia;
}

// Movimiento del robot
void avanzar() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
}

void girarIzquierda() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  delay(400); // tiempo de giro
  detener();
}

void girarDerecha() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  delay(400); // tiempo de giro
  detener();
}

void retroceder() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  delay(500); // tiempo para retroceder
  detener();
}

void detener() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  delay(200);
}
