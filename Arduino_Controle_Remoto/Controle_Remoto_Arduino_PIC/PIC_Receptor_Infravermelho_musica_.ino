#include <IRremote.h>  
  
int RECV_PIN = 11;  
float armazenavalor;  
int led1 = 3;  
int led2 = 4;  
int led3 = 5;  
int led4 = 6;  
int led5 = 7;  
int led6 = 8;  
int led7 = 9;
int pinosom = A0; // Pino que recebe a saida analogica do sensor de som
unsigned long previousMillis = 0;
  
  
IRrecv irrecv(RECV_PIN);  
decode_results results;  
  
void setup()  
{  
  pinMode(led1, OUTPUT);   
  pinMode(led2, OUTPUT); 
  pinMode(led3, OUTPUT); 
  pinMode(led4, OUTPUT); 
  pinMode(led5, OUTPUT); 
  pinMode(led6, OUTPUT);  
  pinMode(led7, OUTPUT);
  pinMode(pinosom, INPUT); // Define o pino de entrada do sensor de som 
  Serial.begin(9600);  
  irrecv.enableIRIn(); // Inicializa o receptor IR  

}  
   
void loop()  
{  
  if (irrecv.decode(&results))  
  {  
    Serial.print("Valor lido : ");  
    Serial.println(results.value, HEX);  
    armazenavalor = (results.value);  
    if (armazenavalor == 0xBD807F){  
      digitalWrite(led1, !digitalRead(led1));
      digitalWrite(led2, !digitalRead(led2));
      digitalWrite(led3, !digitalRead(led3)); 
      digitalWrite(led4, !digitalRead(led4));
      digitalWrite(led5, !digitalRead(led5));
      digitalWrite(led6, !digitalRead(led6));
      digitalWrite(led7, !digitalRead(led7));
    }
    if (armazenavalor == 0xBDA857){  
      digitalWrite(led1, !digitalRead(led1)); 
    }
    if (armazenavalor == 0xBD6897){  
      digitalWrite(led2, !digitalRead(led2)); 
    }
    if (armazenavalor == 0xBDE817){  
      digitalWrite(led3, !digitalRead(led3)); 
    }
    if (armazenavalor == 0xBD9867){  
      digitalWrite(led4, !digitalRead(led4)); 
    }
    if (armazenavalor == 0xBD58A7){  
      digitalWrite(led5, !digitalRead(led5)); 
    }
    if (armazenavalor == 0xBDD827){  
      digitalWrite(led6, !digitalRead(led6)); 
    }
    if (armazenavalor == 0xBDB847){  
      digitalWrite(led7, !digitalRead(led7)); 
    }

    if(armazenavalor == 0xBD20DF){
      musica();
    }
  
  irrecv.resume(); //Le o próximo valor  
  }  
}

void musica(){
  unsigned long temp = millis();
  int i = 1;
  while(millis() - temp < 20000){
    
    if(analogRead(pinosom) <530){
    analogWrite(led1, 0);
    analogWrite(led2, 0);
    analogWrite(led3, 0);
    analogWrite(led4, 0);
    analogWrite(led5, 0);
    analogWrite(led6, 0);
    analogWrite(led7, 0);
  }
  else{
    analogWrite(led1, analogRead(pinosom));
    analogWrite(led2, analogRead(pinosom));
    analogWrite(led3, analogRead(pinosom));
    analogWrite(led4, analogRead(pinosom));
    analogWrite(led5, analogRead(pinosom));
    analogWrite(led6, analogRead(pinosom));
    analogWrite(led7, analogRead(pinosom));
  }
  }
}
