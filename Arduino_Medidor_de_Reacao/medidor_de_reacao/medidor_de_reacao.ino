//Programa para teste de reacao
//Desenvolvido por Andre Oliveira Cunha
//Graduando em Engenharia de Computacao UFES

//--------------------------------------------------------------------------------------------------

//Biblioteca para coneccao com internet
#include <ESP8266WiFi.h>
 
WiFiClientSecure client;//Cria um cliente seguro (para ter acesso ao HTTPS)
String textFix = "GET /forms/d/e/1FAIpQLSemWFNCei7Z6YM9ZCkwLGnSJ0yER9D0RF8Bn281j7lav7zBlw/formResponse?ifq&entry.1720791389=";
//Essa String sera uma auxiliar contendo o link utilizado pelo GET, para nao precisar ficar re-escrevendo toda hora
 
//--------------------------------------------------------------------------------------------------

//Variaveis globais
double tempoReacao=0;
int num;
int acertos=0;
int erros=0;
int qtd=0;

#define tempoMaxReacao  1.0
#define botao D3
//--------------------------------------------------------------------------------------------------

//bibliotecas para o display oled
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

//--------------------------------------------------------------------------------------------------



void setup() {
  Serial.begin(115200);//Inicia a comunicacao serial
  WiFi.mode(WIFI_STA);//Habilita o modo estaçao
  WiFi.begin("VIVOFIBRA-1C12", "33d7f81c12");//Conecta na rede

  u8g2.begin(); //Inicia o display oled
  
  pinMode(botao, INPUT);
  delay(2000);//Espera um tempo para se conectar no WiFi
}

void loop() {
  delay(3000);

  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font

  int numEscolhido=0;
  
  Serial.print("Aperte o botao se o numero que aparecer for: ");
  numEscolhido = random(1,3);
  Serial.println(numEscolhido);

  u8g2.drawStr(0,10,"Comecando...");
  Serial.println("Comecando...");
  delay(2000);
  u8g2.clearBuffer();

  while(qtd < 5 ){

    num = random(1,3);
    Serial.print("Numero = ");
    Serial.println(num);
    
    tempoReacao = millis()/1000.0;
    
    while((digitalRead(botao) != HIGH) && (millis()/1000.0 - tempoReacao < tempoMaxReacao)){
      yield();    
    }
    tempoReacao = millis()/1000.0 - tempoReacao;

    if(num == numEscolhido){
      qtd++;
    }
  
    if(num==numEscolhido && tempoReacao<tempoMaxReacao){
      acertos++;
    }
    else if(num != numEscolhido && tempoReacao<tempoMaxReacao){
      erros++;
    }
    else if(num == numEscolhido && tempoReacao==tempoMaxReacao){
      erros++;
    }
    delay(500);
  
  }

  acertos = (acertos*100)/5;
  Serial.print("Acertos: ");
  Serial.print(acertos);
  Serial.println("%");

  Serial.print("Erros: ");
  Serial.println(erros);

  
  //------------------------------------------------------------------------------------------------
  //Banco de dados do Google Planilhas
  
  if (client.connect("docs.google.com", 443) == 1)//Tenta se conectar ao servidor do Google docs na porta 443 (HTTPS)
    {
        String toSend = textFix;//Atribuimos a String auxiliar na nova String que sera enviada
        toSend += acertos;//Adicionamos um valor aleatorio
        toSend += "&submit=Submit HTTP/1.1";//Completamos o metodo GET para nosso formulario.
 
        client.println(toSend);//Enviamos o GET ao servidor-
        client.println("Host: docs.google.com");//-
        client.println();//-
        client.stop();//Encerramos a conexao com o servidor
        Serial.println("Dados enviados.");//Mostra no monitor que foi enviado
    }
    else
    {
        Serial.println("Erro ao se conectar");//Se nao for possivel conectar no servidor, ira avisar no monitor.
    }


  //------------------------------------------------------------------------------------------------
  

  while(1){yield();}
}
