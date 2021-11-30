
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h> // libreria que permite establecer pines digitales
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
SoftwareSerial BTRFEA(10, 11);  // pin 10 como RX, pin 11 como TX

const int intPin = 3;
const int Buzzer = 4;  //4
const int boton1 = 6;
const int boton2 = 7;
const int boton3 = 8;

int estadosensor = 0;         // variable estado detector
int buttonState1 = 0;         // variable estado detector
int buttonState2 = 0;         // variable estado detector
int buttonState3 = 0;         // variable estado detector

long corecounter = 0;         // CONTADOR MASTER
long counter_p = 0;           // CONTADOR PARCIAL

long reseteeprom = 0;          // variable siempre a 0 para borrar eeprom

float setuprueda = 0;         // PARA CAMBIAR
float setuppulsos = 0;           // 
double incremento = 0.50;
int pasopulso = 0;
double distanciap = 0;
float distanciapmm =0;
double distanciat = 0;
float distanciatmm =0;


int confirx = 5;              // contador confirmaicón 
int x=0;                           // CURSOR BOTON BORRAR EEPROM 
int confiry = 3;              // contador  
int y=0;                           // CURSOR BOTON  
int confirz = 3;              // contador  
int z=0;                           // CURSOR BOTON 

int foco=0;                        // CURSOR PANTALLAS

double init1 = 0;                 //temporizador inicio 

const int timeThreshold = 5;      //REBOTES
long startTime = 0;               //REBOTES

boolean sentido = LOW;              // SENTIDO CARRERA-PULSOS _ front and behind + o -




//////////////////////////////////////////////// recibe texto
char val;
String palabra;
String linea_1;
String linea_2;

int k1;
int k2;
 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
void setup() 
{
  
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  Serial.println(("--------------------------------------------------------------"));
  Serial.println(("      RFEA-DARCC Digital atletics Race Course Counter         "));
  Serial.println(("--------------------------------------------------------------"));

  BTRFEA.begin(9600);    // comunicacion serie entre Arduino y el modulo a 9600 bps
 
  pinMode(intPin, INPUT_PULLUP);
  pinMode(boton1, INPUT_PULLUP);
  pinMode(boton2, INPUT_PULLUP);
  pinMode(boton3, INPUT_PULLUP);


  lcd.init();        //  iniciamos lcd             
  lcd.backlight();   // enciende la luz 


 // attachInterrupt(digitalPinToInterrupt(intPin), interruptCount, FALLING);  // FALLING for when the pin goes from high to low.
 // attachInterrupt(digitalPinToInterrupt(intPin), interruptCount, RISING);   // RISING to trigger when the pin goes from low to high,
 // attachInterrupt(digitalPinToInterrupt(intPin), interruptCount, CHANGE);   // 
    attachInterrupt(digitalPinToInterrupt(intPin), interruptCount, LOW);      // 


  Serial.print("EEPROM = ");
  Serial.println( EEPROM.get(0, corecounter) );     // obtiene valor 
  Serial.println( EEPROM.get(10, setuprueda) );     // obtiene valor 
  Serial.println( EEPROM.get(20, setuppulsos) );     // obtiene valor 

  init1 = (millis() + 3000);  // temporizador pantalla inicio 3seg
  tone(Buzzer, 1000, 100);
  noTone(Buzzer);             // apaga Buzzer.

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

void loop() 
{
  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////  PERMANENTE          /////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      
          BTRFEA.print(corecounter);  
          BTRFEA.print("|");
          BTRFEA.print(counter_p);    
          BTRFEA.print("|");
          BTRFEA.print(setuprueda); // APP 11
          BTRFEA.print("|");
          BTRFEA.print(setuppulsos); // APP 10
          BTRFEA.print("|");
          BTRFEA.print(pasopulso);   // APP 18
          BTRFEA.print("|");
          BTRFEA.print(distanciapmm); // APP 16
          BTRFEA.print("|");
          BTRFEA.print(distanciatmm);  // APP 17
          BTRFEA.print("\n");             // Fin de línea. Importante.
                              
          pasopulso=setuprueda/setuppulsos;

   //////////////////////////////////////////////////////////


     if(BTRFEA.available())
       {
        val = BTRFEA.read();  
        palabra = palabra + val; 

      if (val == '$') {


      k1 = palabra.indexOf(',');
      linea_1 = palabra.substring(0, k1);
      k2 = palabra.indexOf(',', k1+1);
      linea_2 = palabra.substring(k1+1, k2);
      palabra = "";
/*
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(linea_1);
      lcd.setCursor(10,0);
      lcd.print(linea_2);
       
      Serial.print("linea_1  ------> ");
      Serial.println(linea_1);
      Serial.print("linea_2  ------> ");
      Serial.println(linea_2);
*/
      setuprueda = linea_2.toFloat();
      setuppulsos = linea_1.toFloat();

      delay(100);    
      }
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////  PANTALLA INICIO     /////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

          
    if (foco == 0)
      {
      lcd.setCursor(1,0);
      lcd.print("DIGITAL ATHLETICS");
      lcd.setCursor(0,1);
      lcd.print("ROAD COURSE COUNTER");
      lcd.setCursor(1,3);
      lcd.print("RFEA by CNJ_MMCC");

        if (init1 <= millis())
        {
          foco=1;
          lcd.clear();
        }
      }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////  PANTALLA 1 MENU     /////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (foco == 1)
      {
           buttonState1 = digitalRead(boton1);
           buttonState2 = digitalRead(boton2);
           buttonState3 = digitalRead(boton3);


           lcd.setCursor(0,0);
           lcd.print("DIGI-COUNTER  DARCC");
           lcd.setCursor(1,1);
           lcd.print("--- MAIN MENU ---");
           lcd.setCursor(0,2);
           lcd.print("--------------------");
           lcd.setCursor(0,3);
           lcd.print("SETUP");
           lcd.setCursor(7,3);
           lcd.print("RACE  ");
           lcd.setCursor(15,3);
           lcd.print("ERASE");

           if (buttonState1 == LOW)
             {                    
               Serial.println("BOTON 1"); 
               tone(Buzzer, 500, 100);
               noTone(Buzzer);             // apaga Buzzer.

               foco=10;         
               lcd.clear();  
             }
             

           if (buttonState2 == LOW)
             {                    
               Serial.println("BOTON 2"); 
               tone(Buzzer, 600, 100);
               noTone(Buzzer);             // apaga Buzzer.
               foco=99;         
               lcd.clear();     
             }

           if (buttonState3 == LOW)
             {                    
               if (x==0)
                 {   
                    confirx=5;
                    x=1;
                 }  
              Serial.println("BOTON 3"); 
              tone(Buzzer, 800, 100);
              noTone(Buzzer);             // apaga Buzzer.
              lcd.setCursor(17,2);
              lcd.print(confirx); 

               if (x==1)
                 {   
                    confirx--;
                    delay (1000);
                    if (confirx == 0)
                       {
                        x=2;
                       } 
                  }   
               if (x==2)
                 {    
                 
                      EEPROM.put(0, reseteeprom);     // borra 
                      EEPROM.put(10, reseteeprom);     // borra 
                      EEPROM.put(20, reseteeprom);     // borra 
                      corecounter=reseteeprom; 
                      lcd.setCursor(15,2);
                      lcd.print("clean"); 
                      delay(100);
                     } 
                 }
                 
               if (buttonState3 == HIGH)
                  {
                      x=0;
                  }
        }      
      

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////  PANTALLA CALIBRACION     ////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
if (foco == 10)
      {
           buttonState1 = digitalRead(boton1);
           buttonState2 = digitalRead(boton2);
           buttonState3 = digitalRead(boton3);

           lcd.setCursor(0,0);
           lcd.print("DIGI-COUNTER  ARCC");
           lcd.setCursor(1,1);
           lcd.print(" ---- SETUP -----");
           lcd.setCursor(0,2);
           lcd.print("Rueda (mm)=");
           lcd.print(setuprueda);
           lcd.println("    ");
           lcd.setCursor(1,3);
           lcd.print("+");
           lcd.setCursor(9,3);
           lcd.print("-");
           lcd.setCursor(16,3);
           lcd.print("NEXT");

           if (buttonState1 == LOW)
             {                    
               Serial.println("BOTON 1"); 
               tone(Buzzer, 500, 100);
               noTone(Buzzer);             // apaga Buzzer.
               setuprueda=setuprueda+incremento;
             }
             

           if (buttonState2 == LOW)
             {                    
               Serial.println("BOTON 2"); 
               tone(Buzzer, 600, 100);
               noTone(Buzzer);             // apaga Buzzer.
               setuprueda=setuprueda-incremento;  
             }

           if (buttonState3 == LOW)
             {                    
               Serial.println("BOTON 3"); 
               tone(Buzzer, 800, 100);
               noTone(Buzzer);             // apaga Buzzer.
               foco=11;                    
               lcd.clear();  
               delay(100); 
             } 
      }

if (foco == 11)
      {
           buttonState1 = digitalRead(boton1);
           buttonState2 = digitalRead(boton2);
           buttonState3 = digitalRead(boton3);

           lcd.setCursor(0,0);
           lcd.print("DIGI-COUNTER  ARCC");
           lcd.setCursor(0,2);
           lcd.print("pulsos rueda = ");
           lcd.print(setuppulsos);
           lcd.println("     ");
           lcd.setCursor(1,1);
           lcd.print(" ---- SETUP -----");
           lcd.setCursor(1,3);
           lcd.print("+");
           lcd.setCursor(9,3);
           lcd.print("-");
           lcd.setCursor(16,3);
           lcd.print("NEXT");

           if (buttonState1 == LOW)
             {                    
               Serial.println("BOTON 1"); 
               tone(Buzzer, 500, 100);
               noTone(Buzzer);             // apaga Buzzer.
               setuppulsos++;
             }
           if (buttonState2 == LOW)
             {                    
               Serial.println("BOTON 2"); 
               tone(Buzzer, 600, 100);
               noTone(Buzzer);             // apaga Buzzer.
               setuppulsos--;  
             }

           if (buttonState3 == LOW)
             {                    
               Serial.println("BOTON 3"); 
               tone(Buzzer, 800, 100);
               noTone(Buzzer);             // apaga Buzzer.
               //pasopulso=(setuprueda/setuppulsos);
               
               EEPROM.put(10, setuprueda);     // almacena eeprom
               EEPROM.put(20, setuppulsos);     // almacena eeprom
               foco=1;                  
               lcd.clear(); 
               delay(100);            
             } 
      }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////  PANTALLA RACE     ///////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


      
    if (foco == 99)
    {
      estadosensor = digitalRead(intPin);
      buttonState1 = digitalRead(boton1);        
      buttonState2 = digitalRead(boton2);
      buttonState3 = digitalRead(boton3);


          Serial.print("CONTADOR CORE ------> ");
          Serial.println(corecounter);
          Serial.print("CONTADOR PARCIAL ------> ");
          Serial.println(counter_p);
          Serial.print(" setuprueda------> ");
          Serial.println(setuprueda);
          Serial.print(" setuppulsos ------> ");
          Serial.println(setuppulsos);
          Serial.print("paso pulso  ------> ");
          Serial.println(pasopulso);
          Serial.print("distancia ------> ");
          Serial.println(distanciap);
          Serial.print("distanciamm  ------> ");
          Serial.println(distanciapmm);
      
 /*         BTRFEA.print(corecounter);  
          BTRFEA.print("|");
          BTRFEA.print(counter_p);    
          BTRFEA.print("|");
          BTRFEA.print(setuprueda); // APP 11
          BTRFEA.print("|");
          BTRFEA.print(setuppulsos); // APP 10
          BTRFEA.print("|");
          BTRFEA.print(pasopulso);   // APP 18
          BTRFEA.print("|");
          BTRFEA.print(distanciapmm); // APP 16
          BTRFEA.print("|");
          BTRFEA.print(distanciatmm);  // APP 17
          BTRFEA.print("\n");             // Fin de línea. Importante.
 */                             
          pasopulso=setuprueda/setuppulsos;
          distanciap=(pasopulso*counter_p);
          distanciapmm=distanciap/1000;
          distanciat=(pasopulso*corecounter);
          distanciatmm=distanciat/1000;
                    
          lcd.setCursor(2,0);
          lcd.print("PULSOS  = ");
          lcd.print(corecounter);
          lcd.setCursor(2,1);
          lcd.print("PARCIAL = ");
          lcd.print(counter_p);
          lcd.print("  ");
          lcd.setCursor(0,2);
          lcd.print(distanciapmm);       
          lcd.print("m   ");
          lcd.print(distanciatmm);       
          lcd.print("m");
          lcd.setCursor(0,3);
          lcd.print("SAVE ");
          lcd.setCursor(7,3);
          lcd.print("RESET");
          lcd.setCursor(15,3);
          lcd.print("F_B");
          lcd.setCursor(19,3);
          lcd.print("+");


    if (buttonState1 == LOW)
      {                    
      if (z==0)
         {   
          confirz=3;
          z=1;
         }  
      Serial.println("BOTON 1"); 
      tone(Buzzer, 800, 100);
      noTone(Buzzer);             // apaga Buzzer.
      lcd.setCursor(4,3);
      lcd.print(confirz); 
      if (z==1)
          {   
            confirz--;
            delay (1000);
            if (confirz == 0)
              {
              z=2;
              } 
          }   
      if (z==2)
         {     
          Serial.println("BOTON 1"); 
          tone(Buzzer, 500, 100);
          noTone(Buzzer);             // apaga Buzzer.
          EEPROM.put(0, corecounter);     // almacena 
         } 
        }
                 
    if (buttonState1 == HIGH)
      {
      z=0;
      lcd.setCursor(4,3);
      lcd.print(" "); 
      }

    if (buttonState2 == LOW)
      {                    
      if (y==0)
         {   
          confiry=3;
          y=1;
         }  
      Serial.println("BOTON 2"); 
      tone(Buzzer, 800, 100);
      noTone(Buzzer);             // apaga Buzzer.
      lcd.setCursor(12,3);
      lcd.print(confiry); 
      if (y==1)
          {   
            confiry--;
            delay (1000);
            if (confiry == 0)
              {
              y=2;
              } 
          }   
      if (y==2)
         {     
          Serial.println("BOTON 2"); 
          tone(Buzzer, 600, 100);
          noTone(Buzzer);             // apaga Buzzer.
          counter_p=0; 
         } 
        }
                 
    if (buttonState2 == HIGH)
      {
      y=0;
      lcd.setCursor(12,3);
      lcd.print(" "); 
      }
  
    if (buttonState3 == LOW) // comprobamos si se acciona el pulsador
      {
       sentido=!sentido;               // Invertimos la salida del telerruptos desde la ultima pulsacion
       Serial.println(sentido);
       delay (150);
      }
      
   if (sentido == LOW) 
      {
       lcd.setCursor(19,3);
       lcd.print("+");
      }
   if (sentido == HIGH) 
      {
       lcd.setCursor(19,3);
       lcd.print("-");
      }
  
  }
}   // final loop

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////  INTERRUPCION      ///////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void interruptCount()
{  
 if (millis() - startTime > timeThreshold)
  {
    if (sentido == LOW)
          { 
           corecounter++;
           counter_p++;
          }
    if (sentido == HIGH)
      { 
        corecounter--;
        counter_p--;
      }                     
    startTime = millis();
   } 
 }
 
/////////////////  END   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
