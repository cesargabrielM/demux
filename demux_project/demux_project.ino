// Definições dos pinos do HC-SR04
const int trigPin = 9;  // Pino de trigger
const int echoPin = 10; // Pino de echo

// Definições dos pinos das entradas do DEMUX
const int s0 = 2;      // Pino de seleção 0
const int s1 = 3;      // Pino de seleção 1
const int enable = 4;  // Pino de habilitação do DEMUX

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(enable, OUTPUT);

  // Habilita o DEMUX
  digitalWrite(enable, HIGH); // Ativa o DEMUX (verifique a lógica se é LOW ou HIGH)

  Serial.begin(9600); // Inicia a comunicação serial para depuração
}

void loop() {
  // Envia o pulso de disparo
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Calcula a duração do pulso de retorno
  long duration = pulseIn(echoPin, HIGH);

  // Calcula a distância em centímetros
  int distance = duration * 0.034 / 2;

  // Exibe a distância no monitor serial
  Serial.print("Distância: ");
  Serial.println(distance);

  // Lógica para acionar as entradas do DEMUX com base na distância
  if (distance >= 0 && distance <= 75) {
    digitalWrite(s0, HIGH);
    digitalWrite(s1, LOW);
    Serial.println("Selecionado LED1");
  } else if (distance > 75 && distance <= 150) {
    digitalWrite(s0, HIGH);
    digitalWrite(s1, HIGH);
    Serial.println("Selecionado LED2");
  } else if (distance > 150 && distance <= 225) {
    digitalWrite(s0, LOW);
    digitalWrite(s1, LOW);
    Serial.println("Selecionado LED3");
  } else if (distance > 225 && distance <= 300) {
    digitalWrite(s0, LOW);
    digitalWrite(s1, HIGH);
    Serial.println("Selecionado LED4");
  } else {
    // Se a distância for maior que 300, desliga todas as saídas
    digitalWrite(enable, LOW);
    Serial.println("Distância fora do alcance (maior que 300 cm)");
  }

  // Aguarda um curto período para a próxima leitura
  delay(500);
}
