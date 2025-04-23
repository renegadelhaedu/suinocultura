#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);	// Create MFRC522 instance.
int pinoBuzzer = 4;

 
char st[20];
 
void setup() 
{
  Serial.begin(9600);	// Inicia a serial
  pinMode (pinoBuzzer, OUTPUT);
  SPI.begin();		// Inicia  SPI bus
  mfrc522.PCD_Init();	// Inicia MFRC522
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
}

void beep () {
  for(int i = 0; i < 2; i++){
    digitalWrite(pinoBuzzer, HIGH); // Liga o buzzer
    delay(300); // Aguarda 300 milissegundos
    digitalWrite(pinoBuzzer, LOW); // Desliga o buzzer
    delay(300); // Aguarda mais 300 milissegundos
  }
}
 
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("ID : ");
  conteudo.toUpperCase();
  Serial.println (conteudo.substring(1));
  beep ();
  delay (1000);
} 
 