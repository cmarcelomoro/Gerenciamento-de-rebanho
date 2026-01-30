#include <Rfid134.h>
#include <Esp.h>


#define HardwareSerial_Rx 16
#define HardwareSerial_Tx 17
const int buzzerPin = 2;


uint64_t ID_Number;

Rfid134<HardwareSerial, RfidNotify> rfid(Serial2);

class RfidNotify
{
  public:
    static void OnError(Rfid134_Error errorCode)
    {
      
      Serial.println();
      Serial.print("Com Error ");
      Serial.println(errorCode);
    }

    static void OnPacketRead(const Rfid134Reading& reading)
    {
      char temp[8];
      
      Serial.print("TAG: ");

      sprintf(temp, "%03u", reading.country);
      Serial.print(temp);

      Serial.print(" ");
    
      ID_Number = reading.id;

      Serial.println(ID_Number);
      
      Serial.println("Ligando Buzzer");
      
      if(ID_Number){
          digitalWrite(buzzerPin, LOW);
          delay(250);
          digitalWrite(buzzerPin, HIGH);
          delay(250);
          digitalWrite(buzzerPin,LOW);
      }
    }
};

void setup()
{
 
  Serial.begin(115200);

  Serial.println("initializing...");


  Serial.println("Buzzer");
  pinMode(buzzerPin,OUTPUT);
  digitalWrite(buzzerPin, LOW);

  Serial2.begin(9600, SERIAL_8N2, HardwareSerial_Rx, HardwareSerial_Tx);
 
  rfid.begin();

  Serial.println("starting...");
}

void loop()
{
    rfid.loop();
  
}
