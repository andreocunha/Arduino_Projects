//Programa para inverter o sentido do acionamento dos leds ao precionar o botao
//Feito por: Andre Oliveira Cunha
// 12 de Setembro de 2019


//definindo os pinos dos componentes
#define botao 2
#define led1 3
#define led2 4
#define led3 5

int pino = 3; //variavel para contagem dos pinos, com valor inicial igual a tres
int i = 0; //variavel para saber o sentido dos leds. 1 para direita e 0 para a esquerda
int valorBotao = 0; //variavel para guardar o estado do botao. 1 para HIGH, 0 para LOW

//definindo os pinos como saidas/entrada
void setup(){
   pinMode(led1, OUTPUT);
   pinMode(led2, OUTPUT);
   pinMode(led3, OUTPUT);
   pinMode(botao, INPUT);
}

void loop(){
  //ve se o botao foi pressionado
  if(digitalRead(botao)==HIGH){
     valorBotao = 1;
  }
  
  //se o botao foi precionado
  if(valorBotao == 1){
     if(i == 0){ //se o sentido do led estiver pra esquerda
        i = 1; //altera o sentido para a direita
     }
     else{ //faz o oposto do if de cima
        i = 0;
     }
     valorBotao = 0; //zera a variavel para zero novamente
  }
  
  //se o sentido estiver para a esquerda e o valor do pino for menor ou igual a 5
  if(i == 0 && pino<=5){
    digitalWrite(pino, HIGH); //liga o led
    delay(500); //tempo ligado = 0,5s
    digitalWrite(pino, LOW); //desliga o led
    if(pino == 5){//se o valor de pino for igual a 5, ele volta para o 3
      pino = 3;
    }
    else{
      pino = pino + 1; // se o valor do pino for diferente de 5, incrementa mais um para acender o proximo led
    }
  }
  
  //se o sentido estiver para a direita e o valor do pino for maior ou igual a 3
   if(i == 1 && pino>=3){
    digitalWrite(pino, HIGH);//liga o led
    delay(500);//tempo ligado = 0,5s
    digitalWrite(pino, LOW);//desliga o led
    if(pino == 3){//se o valor de pino for igual a 3, ele volta para o 5
      pino = 5;
    }
    else{ // se o valor do pino for diferente de 3, decrementa um para acender o proximo led
      pino = pino -1; 
    }
  }
  
}

