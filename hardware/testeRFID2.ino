#include <HardwareSerial.h>

HardwareSerial rfid(1); // Usa UART1 do ESP32

void setup() {
    Serial.begin(115200);  // Comunicação com PC
    rfid.begin(9600, SERIAL_8N1, 3, -1);  // Comunicação com RFID (testar outras velocidades se necessário)
    Serial.println("O RFID Está ativado!");
}

void loop() {
       if (rfid.available() >= 14) {  // Mínimo de bytes esperados
        uint8_t buffer[14];  // Armazena os bytes recebidos
        rfid.readBytes(buffer, 14);  // Lê 14 bytes da serial

        // Converte os bytes para hexadecimal e exibe
        Serial.print("Brinco RFID lido (HEX): ");
        for (int i = 0; i < 14; i++) {
            Serial.printf("%02X ", buffer[i]);
        }
        Serial.println();

        // Extrai o número do brinco (10 bytes, LSB first)
        char brinco[11];  // 10 caracteres + terminador de string
        memcpy(brinco, buffer + 1, 10);
        brinco[10] = '\0';  // Finaliza a string

        Serial.print("Brinco RFID lido (ASCII): ");
        Serial.println(brinco);
    }
}
