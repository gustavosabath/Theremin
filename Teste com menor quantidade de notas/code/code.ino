
#define trigPin 5  // define o pino Trig do sensor ultrassônico
#define echoPin 3  // define o pino Echo do sensor ultrassônico
#define buzzerPin 9 // define o pino do buzzer
#define led 13
#include <LiquidCrystal_I2C.h>
#include <RunningMedian.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
RunningMedian median(3);

void setup() {
  pinMode(trigPin, OUTPUT); // define o pino Trig como saída
  pinMode(echoPin, INPUT); // define o pino Echo como entrada
  pinMode(buzzerPin, OUTPUT); // define o pino do buzzer como saída
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  // Escreve uma mensagem na primeira linha da tela
  lcd.setCursor(0, 0);
  lcd.print("   MetroTune    ");
  lcd.setCursor(1, 1);
  lcd.print("Gustavo Sabath");
  delay(2000);
  lcd.clear();
}

int medePulso(){
  digitalWrite(trigPin, LOW); // envia um pulso de 2us para o pino Trig
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // envia um pulso de 10us para o pino Trig
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH); // mede o tempo do pulso Echo em microssegundos
}

void loop() {
  float cm;
  String note;
  median.add(medePulso());
  cm = median.getMedian() * 0.01715; // calcula a distância em centímetros
  int frequency = 0;
  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.println(" cm ");

  if (cm >= 3.0 && cm < 11.0){
    frequency = 392;
    note = "       G        ";
  } else if (cm >= 11.0 && cm < 19.0){
    frequency = 440;
    note = "       A        ";
  } else if (cm >= 19.0 && cm < 27.0){
    frequency = 494;
    note = "       B        ";
  } else if (cm >= 27.0 && cm < 35.0){
    frequency = 523;
    note = "       C        ";
  } else if (cm >= 35.0 && cm < 43.0){
    frequency = 587;
    note = "       D        ";
  } else if (cm >= 43.0 && cm < 51.0){
    frequency = 659;
    note = "       E        ";
  } else if (cm >= 51.0 && cm < 59.0){
    frequency = 740;
    note = "       F#       ";
  } else if (cm >= 59.0 && cm < 67.0){
    frequency = 784;
    note = "       G        ";
  }
  lcd.setCursor(0, 0);
  lcd.print("  Tom: G maior  ");
  lcd.setCursor(0, 1);
  
  if (cm >= 3.0 && cm < 67.0){
    tone(buzzerPin, frequency);
    digitalWrite(led, HIGH);
  } else { 
    note = "  Nenhuma Nota  ";
    noTone(buzzerPin);
    digitalWrite(led, LOW);
  }
  
  lcd.print(note);
}
