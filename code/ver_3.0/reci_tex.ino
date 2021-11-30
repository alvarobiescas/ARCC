/*


#include <Wire.h>
#include <LiquidCrystal_I2C.h>    
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
// LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

char val;
String palabra;
String linea_1;
String linea_2;
String linea_1_retorno;
String linea_2_retorno;

int k1;
int k2;

void setup()
{
  lcd.begin(16,2);// Columnas y filas de LCD
  Serial.begin(9600);
}

void loop() {

  if(Serial.available())
  {
    val = Serial.read();  
    palabra = palabra + val; 

if (val == '*') {

      //Serial.println(palabra);
      //Serial.println();
      k1 = palabra.indexOf(',');
      linea_1 = palabra.substring(0, k1);
      k2 = palabra.indexOf(',', k1+1);
      linea_2 = palabra.substring(k1+1, k2);

      //Serial.print("Linea_1 = ");
      //Serial.println(linea_1); 
      //Serial.print("Linea_2 = ");
      //Serial.println(linea_2);
      palabra = "";

      // LCD
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(linea_1);
      lcd.setCursor(0,1);
      lcd.print(linea_2); 
       
      // Retorno de información
      linea_1_retorno = "Recibido " + linea_1 + "|";  // Indicador de renglón.
      linea_2_retorno = "Received " + linea_2 + "\n"; // Indicador de fin de línea.
      Serial.print(linea_1_retorno + linea_2_retorno);

delay(100);    
  }
      }
}
 */
