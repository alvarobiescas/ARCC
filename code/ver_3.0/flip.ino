/*
 * 
 * 
 * 
 * 

int Pin_pulsador = 8;              // Numero del pin en el que se conecta el pulsador al arduino
int Pin_led = 13;                 // Numero del pin en el que se conecta la salida del led ( o lo que se quiera conectar) al arduino
boolean Telerruptor = false;      // Declaramos la variable del telerrupto y la ponemos en fase al arranque del arduino


void setup()
{  
 pinMode(Pin_pulsador,INPUT); // Declaramos la variable Pin_pulsador como entrada del arduino
 pinMode(Pin_led,OUTPUT);      // Declaramos la variable Pin_led como salida del arduino
}

void loop()
{
 if (digitalRead(Pin_pulsador) == HIGH) // comprobamos si se acciona el pulsador
     {
       Telerruptor=!Telerruptor;               // Invertimos la salida del telerruptos desde la ultima pulsacion
       digitalWrite(Pin_led,Telerruptor);   // Escribimos en la salida
       delay(100);                                  //Realizamos una pausa para evitar los rebotes de la pulsacion
     }
}

 * 
 * 
 * 
 */
