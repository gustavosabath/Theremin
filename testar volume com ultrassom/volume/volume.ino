#define trigPin 7  // define o pino Trig do sensor ultrassônico
#define echoPin 6  // define o pino Echo do sensor ultrassônico
#define buzzerPin 9 // define o pino do buzzer
#define MAX_DISTANCE 60

void setup() {
  pinMode(trigPin, OUTPUT); // define o pino Trig como saída
  pinMode(echoPin, INPUT); // define o pino Echo como entrada
  pinMode(buzzerPin, OUTPUT); // define o pino do buzzer como saída
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);  // Mede o tempo de resposta do sensor

  // Calcula a distância em centímetros
  distance = duration * 0.034 / 2;

  // Mapeia a distância lida para uma faixa de valores de volume
  int volume = map(distance, 0, MAX_DISTANCE, 0, 255);

  // Define o volume do buzzer
  analogWrite(buzzerPin, volume);

  tone(buzzerPin, 440);
  delay(1000);
  

}
