/*

if (buttonState3 == LOW)
             {                    
               if (x==0)
                 {   
                    confirmacion=5;
                    x=1;
                 }  
               Serial.println("BOTON 3"); 
               tone(Buzzer, 800, 100);
               lcd.setCursor(17,2);
               lcd.print(confirmacion); 
 
               if (x==1)
                 {   
                    confirmacion--;
                    delay (1000);
                    if (confirmacion == 0)
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
*/
