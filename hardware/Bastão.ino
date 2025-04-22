#include <SoftwareSerial.h>

// Inicializa o leitor de RFID nos pinos 3 (RX) e 2 (TX)
SoftwareSerial RFID(3, -1); // RX e TX

char c;
String tag = "";
int bip = 8; // Pino para buzzer

void setup() {
  Serial.begin(9600);       // Comunicação com o PC
  
  pinMode(bip, OUTPUT);     // Configura o pino do buzzer como saída

  RFID.begin(9600);         // Comunicação com o leitor RFID
}

void loop() {
  if (RFID.available() > 0) {
    delay(100);

    // Lê enquanto tiver dados disponíveis
    while (RFID.available() > 0) {
      c = RFID.read();
      tag += c;

      // Exibe também no monitor serial em tempo real
      Serial.print(c);

      if (c == '\r') Serial.print('\n');
    }

    // Opcional: bip curto ao ler
    digitalWrite(bip, HIGH);
    delay(200);
    digitalWrite(bip, LOW);
  }
}
