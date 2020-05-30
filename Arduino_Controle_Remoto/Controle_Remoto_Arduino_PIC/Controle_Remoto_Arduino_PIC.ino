// INCLUSÃO DE BIBLIOTECA
#include <IRremote.h>
#include <PushButton.h>


// DIRETIVAS DE COMPILAÇÃO
#define tempoTecla 350
#define frequencia 38 // kHz

// DEFINIÇÃO DOS PINOS
#define pinReceptor 11
#define pinBot1 8
#define pinLed 12

// INSTANCIANDO OBJETOS
IRrecv receptorIR(pinReceptor);
IRsend irsend;
PushButton botaoLeitura(pinBot1);

// DECLARAÇÃO VARIÁVEIS GLOBAIS
bool lerComando = false;

// DECLARAÇÃO DAS FUNÇÕES DE LEITURA
void dump (decode_results *results);

int readBluetooth;//Variável que irá receber o valor enviado do celular para o Bluetooth


void setup() {
  Serial.begin(9600);
  pinMode(pinLed, OUTPUT);

  // INICIANDO RECEPTOR IR
  receptorIR.enableIRIn();
  delay(250);
  Serial.println("Pressione algum botao do controle remoto:");

}

void loop() {
  // MÉTODO PARA LEITURA E ATUALIZAÇÃO DAS PROPRIEDADES DO BOTÃO
  botaoLeitura.button_loop();

  // BLOCO CONDIÇÕES PARA INICIAR LEITURA
  if (botaoLeitura.pressed() && !lerComando) {
    lerComando = true;
    digitalWrite(pinLed, HIGH);
  } else if (botaoLeitura.pressed() && lerComando) {
    lerComando = false;
    digitalWrite(pinLed, LOW);
  }

  // LAÇO PARA LEITURA DO RECEPTOR IR QUANDO FOR PRESSIONADO O BOTÃO
  while (lerComando) {

    decode_results  results;

    if (receptorIR.decode(&results)) {
      dump(&results);
      receptorIR.resume();
      lerComando = false;
      digitalWrite(pinLed, LOW);
    }
  }

  //PARA ENVIAR O CODIGO IR PELO ARDUINO
  if (Serial.available())
  {
    if(Serial.available()){
    readBluetooth = Serial.read();
    if(readBluetooth == 'a'){irsend.sendNEC(0x20CB0000, 32);}      //liga e desliga
    else if (readBluetooth == 'a'){irsend.sendNEC(0x20CB0000, 32);}//liga e desliga
    else if (readBluetooth == 'b'){irsend.sendNEC(0x28CA0000, 32);}//temperatura 25
    else if (readBluetooth == 'c'){irsend.sendNEC(0x28CC0000, 32);}//temperatura 20C
    else if (readBluetooth == 'd'){irsend.sendNEC(0x28C80000, 32);}//temperatura 23C
    else if (readBluetooth == 'e'){irsend.sendNEC(0xBD807F, 32);}
    else if (readBluetooth == 'f'){irsend.sendNEC(0xBD807F, 32);}
    else if (readBluetooth == 'g'){irsend.sendNEC(0xBD807F, 32);}
    else if (readBluetooth == 'h'){irsend.sendNEC(0xBD807F, 32);}
    else if (readBluetooth == 'i'){irsend.sendNEC(0xBD807F, 32);}
    else if (readBluetooth == 'j'){irsend.sendNEC(0xBD807F, 32);}
    else if (readBluetooth == 'k'){irsend.sendNEC(0xBD807F, 32);}
    else if (readBluetooth == 'l'){irsend.sendNEC(0xBD807F, 32);}
    else if (readBluetooth == 'm'){irsend.sendNEC(0xBD807F, 32);}
    else if (readBluetooth == 'n'){irsend.sendNEC(0xBD807F, 32);}
    else if (readBluetooth == 'o'){irsend.sendNEC(0xBD807F, 32);}
   }
  }
}

void dump(decode_results *results) {
  // Dumps out the decode_results structure.
  // Call this after IRrecv::decode()
  if (results->decode_type == UNKNOWN) {
    Serial.print("Unknown encoding: ");
  }
  else if (results->decode_type == NEC) {
    Serial.print("{irsend.sendNEC(");

  }
  else if (results->decode_type == SONY) {
    Serial.print("{irsend.sendSONY(");

  }
  else if (results->decode_type == RC5) {
    Serial.print("{irsend.sendRC5(");

  }
  else if (results->decode_type == RC6) {
    Serial.print("{irsend.sendRC6(");

  }
  else if (results->decode_type == PANASONIC) {
    Serial.print("{irsend.sendPANASONIC(");

  }
  else if (results->decode_type == LG) {
    Serial.print("{irsend.sendLG(");

  }
  else if (results->decode_type == JVC) {
    Serial.print("{irsend.sendJVC(");

  }
  else if (results->decode_type == AIWA_RC_T501) {
    Serial.print("{irsend.sendNEC(");

  }
  else if (results->decode_type == WHYNTER) {
    Serial.print("{irsend.sendWHYNTER(");

  }

    Serial.print("0x");
    Serial.print(results->value, HEX);
    Serial.print(", ");
    Serial.print(results->bits, DEC);
    Serial.print(");}");
    Serial.println();
    delay(1000);
}
