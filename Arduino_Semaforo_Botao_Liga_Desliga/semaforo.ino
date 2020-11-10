#define ledVerde 4
#define ledAmarela 5
#define ledVermelho 6
#define botaoLiga 3
#define botaoDesliga 2

int leituraBotao = 0;
int tempo = 0;
int i = 0; //variavel para contagem

void setup(){
  //inicializando os pinos digitais como saida
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarela, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(botaoLiga, INPUT);
  pinMode(botaoDesliga, INPUT);
  
}

void loop(){
  
  //ve se o botao de ligar foi pressionado
  if(digitalRead(botaoLiga)==HIGH){
    leituraBotao = 1;
    tempo = millis();
  }
  
  //ve se o botao de desligar foi pressionado
  if(digitalRead(botaoDesliga)==HIGH){
    leituraBotao = 0;
    tempo = millis();
  }
  
  //se o botao foi pressionado e o tempo minimo do verde do carros ja ocorreu
  if(leituraBotao == 0){
    
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarela, LOW);
    digitalWrite(ledVermelho, LOW);
  }
  
  if(leituraBotao == 1)
  {
    if((millis()-tempo)<500){
       digitalWrite(ledVerde, HIGH);
    }
    else if((millis()-tempo)<1000){
       digitalWrite(ledVerde, LOW);
       digitalWrite(ledAmarela, HIGH);
    }
    else if((millis()-tempo)<1500){
       digitalWrite(ledAmarela, LOW);
       digitalWrite(ledVermelho, HIGH);
    }
    else{
       digitalWrite(ledVermelho, LOW);
       tempo = millis();
    }  
  }
  
 }