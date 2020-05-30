//Codigo simples de semaforo
//Feito por Andre Oliveira Cunha
//Engenharia de Computaçao UFES
//08 de Setembro de 2019

#define LEDverde 8
#define LEDamarelo 9
#define LEDvermelho 10

void setup(){
  //inicializando os pinos digitais como saida
  pinMode(LEDverde, OUTPUT);
  pinMode(LEDamarelo, OUTPUT);
  pinMode(LEDvermelho, OUTPUT);
}

void loop(){
 //sequencia do semaforo

  digitalWrite(LEDverde, HIGH);
  delay(2000); //o led verde ficara aceso por 2 segundos
  digitalWrite(LEDverde, LOW); //depois dos 2 segundos o led ficara apagado
  
   
  digitalWrite(LEDamarelo, HIGH);
  delay(1000); //o led amerelo ficara aceso por 1 segundos
  digitalWrite(LEDamarelo, LOW); //depois de 1 segundos o led ficara apagado
  
  digitalWrite(LEDvermelho, HIGH);
  delay(4000); //o led vermelho ficara aceso por 4 segundos
  digitalWrite(LEDvermelho, LOW); //depois dos 4 segundos o led ficara apagado
  
  
}

