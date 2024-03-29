#include <MFRC522Debug.h>   //
#include <MFRC522DriverPinSimple.h>   //
#include <MFRC522DriverSPI.h>   //
#include <MFRC522v2.h>    //

class MFRC522DriverPinSimple sda_pin(53);
class MFRC522DriverSPI driver {sda_pin};
class MFRC522 mfrc522{driver};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL);
  mfrc522.PCD_Init();
  MFRC522Debug::PCD_DumpVersionToSerial(mfrc522, Serial);
  Serial.println(F("SCAN PICC to see UID, SAK, Type and data block..."));
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!mfrc522.PICC_IsNewCardPresent())  return;
  if(!mfrc522.PICC_ReadCardSerial())  return;
  MFRC522Debug::PICC_DumpToSerial(mfrc522, Serial, &(mfrc522.uid));
}
