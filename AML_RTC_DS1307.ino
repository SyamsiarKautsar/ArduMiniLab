#include <LiquidCrystal.h>
#include <Wire.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
const int DS1307 = 0x68; 
const char* nHari[] =
{"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};
const char* nBulan[] =
{"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus","September", "Oktober", "November", "Desember"};
 
// Initializes all values: 
byte detik  = 0;
byte menit = 0;
byte jam = 0;
byte hari = 0;
byte tanggal = 0;
byte bulan = 0;
byte tahun = 0;
int konterTunggu = 0;

void setup() {
  lcd.begin(16, 2);
  Wire.begin();
  
  lcd.clear();
  lcd.print("Belajar Arduino :D");
  
  Serial.begin(9600);
  delay(2000); 
 
  Serial.print("Waktu sekarang: ");
  printTime();
  Serial.println("Anda ingin mengganti waktu dan tanggal? Y/N");
  
  lcd.setCursor(0,1);
  while (!Serial.available()) {
    konterTunggu ++;
    if (konterTunggu == 100)lcd.print(".");
    if (konterTunggu == 200)lcd.print(".");
    if (konterTunggu == 300)lcd.print(".");
    if (konterTunggu == 400)lcd.print(".");
    if (konterTunggu > 500) break;
    delay(10);
  }
  
  if (Serial.read() == 'y' || Serial.read() == 'Y'){
    lcd.clear();
    lcd.print("atur waktu...");
    
    Serial.read();
    setTime();
    Serial.print("Waktu dan tanggal sekarang adalah: ");
    printTime();
  }
 
  lcd.clear();
}

void loop() {
  readTime();
  lcd.setCursor(4,0);
  lcd.print(" "); lcd.print(jam); lcd.print(":"); lcd.print(menit); lcd.print(" "); 
  delay(500);
  
  readTime();
  lcd.setCursor(4,0);
  lcd.print(" "); lcd.print(jam); lcd.print(" "); lcd.print(menit); lcd.print(" "); 
  delay(500);
}


byte decToBcd(byte val) {
  return ((val/10*16) + (val%10));
}
byte bcdToDec(byte val) {
  return ((val/16*10) + (val%16));
}

void setTime() {
  Serial.print("Masukkan tahun sekarang, <00-99>. - ");
  tahun = readByte();
  Serial.println(tahun);
  Serial.print("Masukkan bulan sekarang, <1-12>. - ");
  bulan = readByte();
  Serial.println(nBulan[bulan-1]);
  Serial.print("Masukkan tanggal sekarang, <1-31>. - ");
  tanggal = readByte();
  Serial.println(tanggal);
  Serial.println("Masukkan hari sekarang, <1-7>.");
  Serial.print("1 Minggu | 2 Senin | 3 Selasa | 4 Rabu | 5 Kamis | 6 Jum'at | 7 Sabtu - ");
  hari = readByte();
  Serial.println(nHari[hari-1]);
  Serial.print("Masukkan jam sekarang, format 24 jam, <0-23>. - ");
  jam = readByte();
  Serial.println(jam);
  Serial.print("Masukkan menit sekarang, <0-59>. - ");
  menit = readByte();
  Serial.println(menit);
  detik = 0;
 
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0));
  Wire.write(decToBcd(detik));
  Wire.write(decToBcd(menit));
  Wire.write(decToBcd(jam));
  Wire.write(decToBcd(hari));
  Wire.write(decToBcd(tanggal));
  Wire.write(decToBcd(bulan));
  Wire.write(decToBcd(tahun));
  Wire.write(byte(0));
  Wire.endTransmission();

  Serial.println("Data berhasil disimpan");
}

byte readByte() {
  while (!Serial.available()) delay(10);
  byte reading = 0;
  byte incomingByte = Serial.read();
  while (incomingByte != '\n') {
    if (incomingByte >= '0' && incomingByte <= '9')
      reading = reading * 10 + (incomingByte - '0');
    else;
    incomingByte = Serial.read();
  }
  Serial.flush();

  return reading;
}


void printTime() {
  char buffer[3];
  const char* AMPM = 0;
  readTime();
  Serial.print(nHari[hari-1]);
  Serial.print(" ");
  Serial.print(nBulan[bulan-1]);
  Serial.print(" ");
  Serial.print(tanggal);
  Serial.print(", 20");
  Serial.print(tahun);
  Serial.print(" ");
  if (jam > 12) {
    jam -= 12;
    AMPM = " PM";
  }
  else AMPM = " AM";
  Serial.print(jam);
  Serial.print(":");
  sprintf(buffer, "%02d", menit);
  Serial.print(buffer);
  Serial.println(AMPM);
}


void readTime() {
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0));
  Wire.endTransmission();
  Wire.requestFrom(DS1307, 7);
  detik = bcdToDec(Wire.read());
  menit = bcdToDec(Wire.read());
  jam = bcdToDec(Wire.read());
  hari = bcdToDec(Wire.read());
  tanggal = bcdToDec(Wire.read());
  bulan = bcdToDec(Wire.read());
  tahun = bcdToDec(Wire.read());
}
