//Codigo Semaforo com interrupçao para pedestre
//Feito por Andre Oliveira Cunha
//Engenharia de Computaçao UFES
//08 de Setembro de 2019

#define CarroVerde 8
#define CarroAmarelo 9
#define CarroVermelho 10
#define BotaoPedestre 2
#define PedestreVerde 3
#define PedestreVermelho 4

int leituraBotao = 0;
int tempo = 0;
int i = 0; //variavel para contagem

void setup(){
  //inicializando os pinos digitais como saida
  pinMode(CarroVerde, OUTPUT);
  pinMode(CarroAmarelo, OUTPUT);
  pinMode(CarroVermelho, OUTPUT);
  pinMode(BotaoPedestre, INPUT);
  pinMode(PedestreVerde, OUTPUT);
  pinMode(PedestreVermelho,OUTPUT);
  
  //ligando os leds pedestre e semaforo
  digitalWrite(PedestreVermelho, HIGH);
  digitalWrite(CarroVerde, HIGH);
  
}

void loop(){
  
  //ve se o botao foi pressionado
  if(digitalRead(BotaoPedestre)==HIGH){
    leituraBotao = 1;
  }
  
  //se o botao foi pressionado e o tempo minimo do verde do carros ja ocorreu
  if(leituraBotao == 1 && (millis()-tempo)>2000){
    
    //muda o estado do semaforo dos carros
    tempo = millis(); //atualiza o tempo da variavel tempo
    digitalWrite(CarroVerde, LOW);
    digitalWrite(CarroAmarelo, HIGH);
    delay(1000);
    digitalWrite(CarroAmarelo, LOW);
    digitalWrite(CarroVermelho, HIGH);

    //muda o estado do semaforo dos pedestres
    digitalWrite(PedestreVermelho, LOW);
    digitalWrite(PedestreVerde, HIGH);
    delay(3000);
    
    //piscar o led dos pedestres alertando que o tempo acabou
    for(i=0; i<=5; i++){
      digitalWrite(PedestreVerde, LOW);
      delay(200);
      digitalWrite(PedestreVerde, HIGH);
      delay(200);
    }
    
    digitalWrite(PedestreVermelho, HIGH);
    digitalWrite(PedestreVerde, LOW);
    delay(500);
    digitalWrite(CarroVermelho, LOW);
    tempo = millis(); //atualiza o tempo da variavel tempo
    digitalWrite(CarroVerde, HIGH);
    
    leituraBotao = 0;
  }
 }

