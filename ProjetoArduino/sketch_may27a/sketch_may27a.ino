#include <SPI.h>
#include <MFRC522.h>

#define RELAY 8
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN); 
int buzzerPin = 5;

void setup()
{
  pinMode(RELAY, OUTPUT);
  Serial.begin(9600);
  SPI.begin();   
  mfrc522.PCD_Init();   
  Serial.println("Aproxime seu token da leitora...");
  Serial.println();
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  tone(buzzerPin,415,554);
  delay(250);
  noTone(buzzerPin);
}
void loop(){
  digitalWrite(2, 1);
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  
  if (content.substring(1) == "C0 36 22 32"){
    int bips = 1;
    for(int j=0; j < bips; j++){
      tone(buzzerPin,1500);  
      delay(500);   
      noTone(buzzerPin);
      
      Serial.println("Acesso autorizado");
      Serial.println();
      Serial.println("Acesso AUTORIZADO");
      digitalWrite (RELAY, LOW);
      digitalWrite(3, 1);
      digitalWrite(2, 0);
      delay(3000);
      digitalWrite(3,0);
      digitalWrite(2, 1);
  }
}

  else   {
    int bips = 1;
    for(int j=0; j < bips; j++){
      tone(buzzerPin,500);  
      delay(500);   
      noTone(buzzerPin);
      Serial.println("Acesso negado");
      Serial.println();
      Serial.println("Acesso NEGADO");
      digitalWrite(RELAY, HIGH);
      digitalWrite(4, 1);
      digitalWrite(2, 0);
      delay(3000);
      digitalWrite(4,0);
      digitalWrite(2, 1);
   }
  }
}
