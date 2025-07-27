// Pines sensores IR
const int sensorIzq = A0;
const int sensorDer = A1;

// Pines del L298N
const int IN1 = 5;
const int IN2 = 4;
const int IN3 = 3;
const int IN4 = 2;
const int ENA = 6;
const int ENB = 9;

void setup() {
  // Motores
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Sensores
  pinMode(sensorIzq, INPUT);
  pinMode(sensorDer, INPUT);

  Serial.begin(9600);
}

void loop() {
  bool izq = digitalRead(sensorIzq);
  bool der = digitalRead(sensorDer);

  Serial.print("Izq: "); Serial.print(izq);
  Serial.print(" | Der: "); Serial.println(der);

  if (!izq && !der) {
    // Ambos sensores sobre línea negra → avanzar
    avanzar();
  } else if (!izq && der) {
    // Izquierdo en línea, derecho fuera → girar a la izquierda
    girarIzquierda();
  } else if (izq && !der) {
    // Derecho en línea, izquierdo fuera → girar a la derecha
    girarDerecha();
  } else {
    // Ambos fuera de la línea → detener o buscar línea
    detener();
  }
}

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
  analogWrite(ENA, 120);
  analogWrite(ENB, 120);
}

void girarDerecha() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 120);
  analogWrite(ENB, 120);
}

void detener() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
