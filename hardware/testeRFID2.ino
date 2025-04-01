#include <HardwareSerial.h>

HardwareSerial rfid(1);  // Usa UART1 (ou ajuste para a UART correta)

void setup() {
    Serial.begin(115200);       // Comunicação com o PC (Monitor Serial)
    rfid.begin(9600, SERIAL_8N1, 3, -1);  // Comunicação com o RFID (Apenas RX no GPIO3)
    
    Serial.println("O RFID Está ativado!");
}

void loop() {
    if (rfid.available()) {  // Se há dados disponíveis do módulo RFID
        String brinco = rfid.readString();  // Lê os dados como string completa
        Serial.print("Brinco RFID lido: ");
        Serial.println(brinco);  // Exibe o ID do brinco no monitor serial
    }
}