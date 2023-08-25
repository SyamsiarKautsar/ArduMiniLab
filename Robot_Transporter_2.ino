/* Program By Teknologi Rekayasa Mekatronika
 * ------------Jurusan Teknik---------------
 * ------Politeknik Negeri Jember----------
 */


int pos1 = 0;

int pwmKanan = 11;
int dirKanan = 10;
int pwmKiri = 3;
int dirKiri = 2;

int nPwmKanan, nPwmKiri;

String dataTerima;
String serv, arah;
void setup()
{
  pinMode(pwmKanan, OUTPUT);
  pinMode(pwmKiri, OUTPUT);
  pinMode(dirKanan, OUTPUT);
  pinMode(dirKiri, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(A3, 1); 

  Serial.begin(57600);
}

void loop() {
  if (Serial.available() > 0)
  {
    dataTerima = Serial.readStringUntil('\n');
    serv = dataTerima.substring(1,2);
    arah = dataTerima.substring(3,4);
    
  
  if ( arah == "1") // Forward
  {
    digitalWrite(dirKiri, 0);
    digitalWrite(dirKanan, 0);
    nPwmKanan = 125;
    nPwmKiri = 125;

    analogWrite(pwmKanan, nPwmKanan);
    analogWrite(pwmKiri, nPwmKiri);
  }
  else if (arah == "2") // Backward

  {
    digitalWrite(dirKiri, 1);
    digitalWrite(dirKanan, 1);
    nPwmKanan = 130;
    nPwmKiri = 130;

    analogWrite(pwmKanan, nPwmKanan);
    analogWrite(pwmKiri, nPwmKiri);
  }
  else if (arah == "3") //Left
  {
    digitalWrite(dirKiri, 0);
    digitalWrite(dirKanan, 0);
    nPwmKanan = 125;
    nPwmKiri = 63;

    analogWrite(pwmKanan, nPwmKanan);
    analogWrite(pwmKiri, nPwmKiri);
  }
  else if (arah == "4") //Right
  {
    digitalWrite(dirKiri, 0);
    digitalWrite(dirKanan, 0);
    nPwmKanan = 63;
    nPwmKiri = 125;

    analogWrite(pwmKanan, nPwmKanan);
    analogWrite(pwmKiri, nPwmKiri);
  }
  else //if (val == "0") //Stop
  {
    digitalWrite(dirKiri, 0);
    digitalWrite(dirKanan, 0);
    nPwmKanan = 0;
    nPwmKiri = 0;

    analogWrite(pwmKanan, nPwmKanan);
    analogWrite(pwmKiri, nPwmKiri);
  }
  }
  /*else if (val == 'I') //Forward Right
  {
    digitalWrite(dirKiri, 0);
    digitalWrite(dirKanan, 0);
    nPwmKanan = 90;
    nPwmKiri = 125;

    analogWrite(pwmKanan, nPwmKanan);
    analogWrite(pwmKiri, nPwmKiri);
  }
  else if (val == 'J') //Backward Right
  {
    digitalWrite(dirKiri, 1);
    digitalWrite(dirKanan, 1);
    nPwmKanan = 165;
    nPwmKiri = 130;

    analogWrite(pwmKanan, nPwmKanan);
    analogWrite(pwmKiri, nPwmKiri);
  }
  else if (val == 'G') //Forward Left
  {
    digitalWrite(dirKiri, 0);
    digitalWrite(dirKanan, 0);
    nPwmKanan = 125;
    nPwmKiri = 90;

    analogWrite(pwmKanan, nPwmKanan);
    analogWrite(pwmKiri, nPwmKiri);
  }
  else if (val == 'H') //Backward Left
  {
    digitalWrite(dirKiri, 1);
    digitalWrite(dirKanan, 1);
    nPwmKanan = 130;
    nPwmKiri = 165;

    analogWrite(pwmKanan, nPwmKanan);
    analogWrite(pwmKiri, nPwmKiri);
  }
  */
}
