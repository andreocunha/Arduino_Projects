//Programa para inverter o sentido do acionamento dos leds ao precionar o botao
//Feito por: Andre Oliveira Cunha
// 12 de Setembro de 2019


//definindo os pinos dos componentes
#define botao 2
#define led1 3
#define led2 4
#define led3 5

int pino = 3; //variavel para contagem dos pinos, com valor inicial igual a tres
int i = 1; //variavel para saber o sentido dos leds. 1 para direita e -1 para a esquerda
int leituraBotao = 0; //variavel para guardar o estado do botao
int tempo = 0;

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
     leituraBotao = 1;
  }
  
  //se o botao foi pressionado e o tempo minimo do led ja ocorreu
  if(leituraBotao == 1 && (millis()-tempo)>1000){
    //muda o sentido dos leds
    i = i*(-1);
    leituraBotao = 0;
  }

  if((millis()-tempo)>1000){ //se o tempo minimio do led ficou aceso
     digitalWrite(pino, LOW); //desliga o led
     if (i<0){ //verifica se o sentido eh para esquerda
       if(pino==5){//se o pino for igual a 5 (indica q o ultimo led foi aceso)
         pino = 3;//volta para o primeiro led
       }
       else{ //caso contrario
         pino = pino + 1; //acende o proximo led
       }
     }
     
     else{//se o sentido for para direita
       if(pino == 3){//se o pino for igual a 3 (indica q o ultimo led foi aceso, no sentido para direita)
         pino = 5;//volta para o primeiro led
       }
       else{//caso contrario
         pino = pino - 1; //acende o proximo led
       }
     }
     tempo = millis(); //atualiza o tempo da variavel tempo
  }
  digitalWrite(pino, HIGH); //acende o led
}

