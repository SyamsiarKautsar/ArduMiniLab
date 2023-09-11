int nilaiADC;
float tegangan;
float teganganAsli;
const float res = 40000.0/10000.0;
const float pengali = 5.0/1023.0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  nilaiADC = analogRead(A0);
  tegangan = nilaiADC * pengali;
  teganganAsli  = tegangan * res;
  Serial.print("ADC= ");
  Serial.print(nilaiADC);
  Serial.print(" ; V= ");
  Serial.print(tegangan);
  Serial.print(" ; Vs= ");
  Serial.println(teganganAsli);
  delay(1000);
}
