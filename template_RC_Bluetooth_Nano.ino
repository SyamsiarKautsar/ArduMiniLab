/* Program By Teknologi Rekayasa Mekatronika
 * ------------Jurusan Teknik---------------
 * ------Politeknik Negeri Jember----------
 */

char val;

void setup()
{
  Serial.begin(9600);
  
}

void loop() {
  while (Serial.available() > 0)
  {
    val = Serial.read();
    //Serial.println(val);
  }
  if ( val == 'F') // Forward
  {
  
  }
  else if (val == 'B') // Backward
  {
    
  }
  else if (val == 'L') //Left
  {
    
  }
  else if (val == 'R') //Right
  {
    
  }
  else if (val == 'S') //Stop
  {
   
  }
  else if (val == 'I') //Forward Right
  {

  }
  else if (val == 'J') //Backward Right
  {
 
  }
  else if (val == 'G') //Forward Left
  {
    
  }
  else if (val == 'H') //Backward Left
  {
    
  }
}
