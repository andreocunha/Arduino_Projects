#define led1 2
#define led2 3
#define led3 4
#define led4 5
#define led5 6
#define botao 7
#define voltimetro A4

float leituraTensao = 0;
int leituraBotao = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(botao, INPUT);
  pinMode(voltimetro, INPUT);
  
}

void loop(){
  leituraTensao = converteEmTensao(analogRead(voltimetro));
  leituraBotao = digitalRead(botao);
  
  Serial.println(leituraTensao);
  if(leituraBotao == HIGH){
    bateria(leituraTensao);
  }
}

float converteEmTensao(int leituraAnalogica){
  float leitura = leituraAnalogica;
  return (leitura*9)/1023;
}

void bateria(float leituraTensao){
  if(leituraTensao > 2.0){
    digitalWrite(led1, HIGH);
    delay(150);
  }
  if(leituraTensao > 5.5){
    digitalWrite(led2, HIGH);
    delay(150);
  }
  if(leituraTensao > 6.5){
    digitalWrite(led3, HIGH);
    delay(150);
  }
  if(leituraTensao > 7.0){
    digitalWrite(led4, HIGH);
    delay(150);
  }
  if(leituraTensao > 8.0){
    digitalWrite(led5, HIGH);
    delay(150);
  }
  delay(1500);
  apagaLeds();
}

void apagaLeds(){
  digitalWrite(led5, LOW);
  delay(150);
  digitalWrite(led4, LOW);
  delay(150);
  digitalWrite(led3, LOW);
  delay(150);
  digitalWrite(led2, LOW);
  delay(150);
  digitalWrite(led1, LOW);
}
