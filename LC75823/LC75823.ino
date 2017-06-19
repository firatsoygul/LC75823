#include <SPI.h>

const int slaveSelectPin = 10;

byte k=0;
byte ADR = 130;
//byte Letter[24]={28,19,28,112,24,32,24,32,24,99,0,0,25,7,24,99,28,85,24,32,0,227,0,0};
void karakter(char gk[]);
void yazdir();


byte Letter[800];
int LetterSize = 800;

int LetterLenght=0;
int n=0;
int kuz;

char yz[] = "BU METIN EKRANDA GÖRUNECEK";

void setup() {

Serial.begin(9600);

pinMode(slaveSelectPin, OUTPUT);

SPISettings(38000, MSBFIRST, SPI_MODE0);
SPI.begin();

Serial.begin(9600);

}

void loop() {

  karakter(yz);
  yazdir();


 }

void yazdir() {

byte Out[LetterSize];
byte j=1;

n=k;

for(int i=0; i<= LetterSize; i+=2){

  Out[i]=(Letter[n] << j) | (Letter[n+1] >> (8-j));
  if(i<2){
    Out[i+1]=Letter[n+1] << j;}
  else if(i>=LetterSize){
    Out[i]=Letter[n+1];
    Out[i+1]=0;}
  else{
    Out[i+1]=(Letter[n+1] << j) | (Letter[n+2] >> (7-j));  
  }

  if((n+2)>LetterSize){
    n=0;
    Out[i+1]=Letter[LetterSize]<<j|Letter[0]>>(7-j);}
  else{
    n+=2;
  }

j++;

}


if((k+1)>LetterLenght*2) //-16
{
    k=0;}
else{
    k+=2;
}


digitalWrite(slaveSelectPin, LOW);
SPI.transfer(ADR);
digitalWrite(slaveSelectPin, HIGH);
SPI.transfer(0); 

for(int i=0; i<=14; i++){
  SPI.transfer(Out[i]);
}

SPI.transfer(0);
SPI.transfer(0);
SPI.transfer(0);
SPI.transfer(0);

SPI.transfer(0); 
digitalWrite(slaveSelectPin, LOW); //EOT

delay(150);

}

void karakter(char gk[])
{
  kuz = 0;
  while( gk[kuz]!='\0' )
      kuz++;
    Serial.println(kuz);  
   LetterLenght=kuz;
   int d = -2;
   for (int j=0;j<=kuz;j++) {
    switch (gk[j]) {
      case ' ' : Letter[d+2] = 0; Letter[d+3] = 0; d+=2; break; //Uyarlandı
      case 'A' : Letter[d+2] = 50; Letter[d+3] = 139; d+=2; break; //Uyarlandı
      case 'B' : Letter[d+2] = 1; Letter[d+3] = 203; d+=2; break; //Uyarlandı
      case 'C' : Letter[d+2] = 49; Letter[d+3] = 128; d+=2; break; //Uyarlandı
      case 'Ç' : Letter[d+2] = 21; Letter[d+3] = 80; d+=2; break;
      case 'D' : Letter[d+2] = 1; Letter[d+3] = 195; d+=2; break; //Uyarlandı
      case 'E' : Letter[d+2] = 51; Letter[d+3] = 128; d+=2; break; //Uyarlandı
      case 'F' : Letter[d+2] = 50; Letter[d+3] = 128; d+=2; break; //Uyarlandı
      case 'G' : Letter[d+2] = 49; Letter[d+3] = 137; d+=2; break; //Uyarlandı
      case 'H' : Letter[d+2] = 50; Letter[d+3] = 11; d+=2; break; //Uyarlandı
      case 'I' : Letter[d+2] = 1; Letter[d+3] = 192; d+=2; break; //Uyarlandı
      case 'J' : Letter[d+2] = 17; Letter[d+3] = 3; d+=2; break; //Uyarlandı
      case 'K' : Letter[d+2] = 50; Letter[d+3] = 48; d+=2; break; //Uyarlandı
      case 'L' : Letter[d+2] = 49; Letter[d+3] = 0; d+=2; break; //Uyarlandı
      case 'M' : Letter[d+2] = 52; Letter[d+3] = 19; d+=2; break; //Uyarlandı
      case 'N' : Letter[d+2] = 52; Letter[d+3] = 35; d+=2; break; //Uyarlandı
      case 'O' : Letter[d+2] = 49; Letter[d+3] = 131; d+=2; break; //Uyarlandı
      case 'Ö' : Letter[d+2] = 14; Letter[d+3] = 58; d+=2; break;
      case 'P' : Letter[d+2] = 50; Letter[d+3] = 138; d+=2; break; //Uyarlandı
      case 'R' : Letter[d+2] = 50; Letter[d+3] = 170; d+=2; break; //Uyarlandı
      case 'S' : Letter[d+2] = 5; Letter[d+3] = 137; d+=2; break; //Uyarlandı
      case 'T' : Letter[d+2] = 0; Letter[d+3] = 192; d+=2; break; //Uyarlandı
      //case 'U' : Letter[d+2] = 24; Letter[d+3] = 35; d+=2; break;
      case 'U' : Letter[d+2] = 49; Letter[d+3] = 3; d+=2; break; //Uyarlandı
      case 'V' : Letter[d+2] = 56; Letter[d+3] = 16; d+=2; break; //Uyarlandı
      case 'W' : Letter[d+2] = 25; Letter[d+3] = 7; d+=2; break;
      case 'X' : Letter[d+2] = 3; Letter[d+3] = 12; d+=2; break;
      case 'Y' : Letter[d+2] = 4; Letter[d+3] = 11; d+=2; break; //Uyarlandı
      case 'Z' : Letter[d+2] = 9; Letter[d+3] = 144; d+=2; break; //Uyarlandı
      case '-' : Letter[d+2] = 2; Letter[d+3] = 8; d+=2; break; //Uyarlandı
      case '+' : Letter[d+2] = 4; Letter[d+3] = 144; d+=2; break;
      case '=' : Letter[d+2] = 4; Letter[d+3] = 48; d+=2; break;
      case '/' : Letter[d+2] = 1; Letter[d+3] = 8; d+=2; break;
      case '%' : Letter[d+2] = 5; Letter[d+3] = 24; d+=2; break;
      case '\'' : Letter[d+2] = 0; Letter[d+3] = 8; d+=2; break;
      case '_' : Letter[d+2] = 0; Letter[d+3] = 32; d+=2; break; 
      case '(' : Letter[d+2] = 0; Letter[d+3] = 12; d+=2; break; 
      case ')' : Letter[d+2] = 3; Letter[d+3] = 0; d+=2; break;
      case '*' : Letter[d+2] = 7; Letter[d+3] = 28; d+=2; break;
      case '#' : Letter[d+2] = 31; Letter[d+3] = 255; d+=2; break;  //Dolu
      case '0' : Letter[d+2] = 57; Letter[d+3] = 147; d+=2; break; //Uyarlandı
      case '1' : Letter[d+2] = 0; Letter[d+3] = 19; d+=2; break; //Uyarlandı
      case '2' : Letter[d+2] = 19; Letter[d+3] = 144; d+=2; break; //Uyarlandı
      case '3' : Letter[d+2] = 1; Letter[d+3] = 139; d+=2; break; //Uyarlandı
      case '4' : Letter[d+2] = 34; Letter[d+3] = 11; d+=2; break; //Uyarlandı
      case '5' : Letter[d+2] = 35; Letter[d+3] = 137; d+=2; break; //Uyarlandı
      case '6' : Letter[d+2] = 51; Letter[d+3] = 137; d+=2; break; //Uyarlandı
      case '7' : Letter[d+2] = 0; Letter[d+3] = 131; d+=2; break; //Uyarlandı
      case '8' : Letter[d+2] = 51; Letter[d+3] = 139; d+=2; break; //Uyarlandı
      case '9' : Letter[d+2] = 35; Letter[d+3] = 139; d+=2; break; //Uyarlandı
      default : ; break;  
    }
   } 
}
