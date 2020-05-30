#include <IRremote.h>  
    
IRrecv receptor(10);  
decode_results resultado; 
int codigo; 
  
void setup()  
{  
  pinMode(5, OUTPUT);    
  receptor.enableIRIn(); 
  Serial.begin(9600);
}  
   
void loop()  
{  
  if (receptor.decode(&resultado))  
  {  
    Serial.print("Codigo do botao: ");  
    Serial.println(resultado.value, HEX);  
    codigo = resultado.value; 
    switch (codigo)  
    {  
      case (0xFF6987):   
      digitalWrite (5,HIGH);    
      break;   
 
      case (0xFF9867): 
      digitalWrite (5,LOW); 
      break;  
    }  
  receptor.resume();  
  }
  delay(100);  
}
