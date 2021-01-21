
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>   
#include <Servo.h>                                              
SoftwareSerial mySerial(2, 3);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
Servo servo;
int pos = 0;
void setup()  
{
  servo.attach(4);
  pinMode(4,OUTPUT);                                                        
  Serial.begin(9600);
  while (!Serial);  
  delay(100);
  
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
   while (1) { 
    delay(1); 
    }
  }
  finger.getTemplateCount();
  Serial.print(finger.templateCount); 
}

void loop()                    
{
  getFingerprintIDez();
  delay(50);           
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      break;
    case FINGERPRINT_NOFINGER:
     return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      return p;
    case FINGERPRINT_IMAGEFAIL:
      return p;
    default:
      return p;
  }
  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      break;
    case FINGERPRINT_IMAGEMESS:
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      return p;
    case FINGERPRINT_FEATUREFAIL:
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      return p;
    default:
      return p;
  }
  
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
  } 
  else {
    return p;
  }   
  return finger.fingerID;
}


int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  if(finger.fingerID>=1)                                                                
  {                                                                                    
      servo.write(50);
       delay(1000);
      servo.write(1);
       delay(100);                      
  }                                                         
  
 }                                                                                     
