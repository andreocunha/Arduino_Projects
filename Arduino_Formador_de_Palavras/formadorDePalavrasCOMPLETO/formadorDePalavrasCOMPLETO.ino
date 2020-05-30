// Acelerometro ADXL345


#include <Wire.h>

#define Register_ID 0
#define Register_2D 0x2D
#define Register_X0 0x32
#define Register_X1 0x33
#define Register_Y0 0x34
#define Register_Y1 0x35
#define Register_Z0 0x36
#define Register_Z1 0x37

#define TOL 0.6f


bool esquerda=false, direita=false, cima=false, baixo=false, flag = false, mudou = false;
char caractere;
String palavra, carac;
String sequencia;
// Endereco I2C do sensor : 83 em decimal ou 0x53
int ADXAddress = 0x53;  // the default 7-bit slave address
int reading = 0;
int val=0;
int X0,X1,X_out;
int Y0,Y1,Y_out;
int Z1,Z0,Z_out;
int ultPosApag;
double Xg,Yg,Zg;
bool estavaStandBy = true;


char sequencia1[3];
int primeiroNumEscolhido = 0;
int segundoNumEscolhido = 0;
int operadorEscolhido = 0;
int primeiroNum = 0;
int segundoNum = 0;
char operador = '+';
int algarismo, contadorRegistro = 0, cont=0;
bool erro = false;

char matrizCodigos[10][3] ={{'D', 'D', 'D'}, //0 +
                            {'D', 'D', 'E'}, //1 -
                            {'D', 'E', 'D'}, //2 *
                            {'D', 'E', 'E'}, //3 /
                            {'E', 'D', 'D'}, //4
                            {'E', 'D', 'E'}, //5
                            {'E', 'E', 'E'}, //6
                            {'D', 'E', 'T'}, //7
                            {'E', 'D', 'T'}, //8
                            {'T', 'D', 'E'}};//9



int PegaAlgarismo(char sequencia1[]) {
  int i;

  for (i = 0; i < 10; i++) {
    if ((sequencia1[0] == matrizCodigos[i][0]) && (sequencia1[1] == matrizCodigos[i][1]) && (sequencia1[2] == matrizCodigos[i][2])) {
      return i;
    }
  }

  sequencia1[0] = 'N'; sequencia1[1] = 'N'; sequencia1[2] = 'N';
  return -1;
}

void Reiniciar() {
  primeiroNumEscolhido = 0;
  segundoNumEscolhido = 0;
  operadorEscolhido = 0;
  primeiroNum = 0;
  segundoNum = 0;
  contadorRegistro = 0;
  sequencia1[0] = 'N'; sequencia1[1] = 'N'; sequencia1[2] = 'N';
  cont=0;
  erro = false;
}




void setup()
{
  Wire.begin();                
  Serial.begin(9600);    
  delay(100);
  // enable to measute g data
  Wire.beginTransmission(ADXAddress);
  Wire.write(Register_2D);
  Wire.write(8);                //measuring enable
  Wire.endTransmission();     // stop transmitting
  palavra = "\0";
  ultPosApag = -1;

  sequencia1[0] = 'N'; sequencia1[1] = 'N'; sequencia1[2] = 'N';


  delay(500);
  
  Serial.println("Escolha o modo de gesto:");
  Serial.println("Modo1(facil escrita): incline para direita");
  Serial.println("Modo2(rapida escrita): incline para esquerda");
  Serial.println("Modo3(calculadora): incline para frente");
}

char a = 'a'-1;
int i = 0;
char Str1[30];
char Str2[30];


//Modo escrita André Cunha e Gabriel Simoura
void modo1(){
  
  Serial.println();
  Serial.println("Modo 1 selecionado");
  delay(1000);
  Serial.println();
  Serial.println("TUTORIAL:");
  Serial.println("Incline para a → para percorrer o alfabeto.");
  Serial.println("Incline para a ← para percorrer o alfabeto no sentido inverso.");
  Serial.println("Incline para a ↓ para selecionar a ultima letra.");
  Serial.println("Incline para a ↑ para mostrar a palavra formada.");
  Serial.println();
  while(1){

    //--------------X
  Wire.beginTransmission(ADXAddress); // transmit to device
  Wire.write(Register_X0);
  Wire.write(Register_X1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress,2); 
  if(Wire.available()<=2)   
  {
    X0 = Wire.read();
    X1 = Wire.read(); 
    X1=X1<<8;
    X_out=X0+X1;   
  }

  //------------------Y
  Wire.beginTransmission(ADXAddress); // transmit to device
  Wire.write(Register_Y0);
  Wire.write(Register_Y1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress,2); 
  if(Wire.available()<=2)   
  {
    Y0 = Wire.read();
    Y1 = Wire.read(); 
    Y1=Y1<<8;
    Y_out=Y0+Y1;
  }
  //------------------Z
  Wire.beginTransmission(ADXAddress); // transmit to device
  Wire.write(Register_Z0);
  Wire.write(Register_Z1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress,2); 
  if(Wire.available()<=2)   
  {
    Z0 = Wire.read();
    Z1 = Wire.read(); 
    Z1=Z1<<8;
    Z_out=Z0+Z1;
  }
  //
  Xg=X_out/256.0;
  Yg=Y_out/256.0;
  Zg=Z_out/256.0;

  if(Zg > 0.4){
    Serial.println();
    Serial.println("Saindo do Modo 1...");
    delay(1000);
    Serial.println();
    Serial.println("Selecione o Modo:");
    break;
  }

  if(Xg < -0.35){
    a++;
    if(a > 'z'){
      Serial.println();
      a = 'a';
    }
    Serial.print(a);
    Serial.print(" ");
    delay(250);
  }

  if(Xg > 0.35){
    a--;
    if(a < 'a'){
      Serial.println();
      a = 'z';
    }
    Serial.print(a);
    Serial.print(" ");
    delay(250);
  }

  if(Yg > 0.35){
    Str1[i] = a;
    i++;
    Serial.println();
    Serial.print("Letra selecionada: ");
    Serial.println(a);
    delay(1000);
  }

  if(Yg < -0.35){
    Serial.println();
    Serial.println();
    Serial.print("Palavra formada:  ");
    Serial.println(Str1);
    a = 'a';
    delay(500);
    
  }
  delay(200);
    
  }
}




//Modo escrita Henrique Paulino e Joana
void modo2(){

  Serial.println();
  Serial.println("Modo 2 selecionado:");
  delay(1000);
  Serial.println("TUTORIAL:");
  Serial.println("Cada letra é formada por uma combinação de gestos:");
  Serial.println("Veja como escrever cada letra:");
  Serial.println("Apagar: ↑                   Confirmar: ↓");
  Serial.println("A: ←    B: →       C: ← ↑    D: ←←     E: ←→       F: →→    G: →↑    H:→←     I:↑↑    J:↑← ");
  Serial.println("K:↑→    L: ←←→     M: ←←↑    N: ←→→    O:←→→       P: ←↑←   Q:←↑→    R:←↑↑    S:→→←");
  Serial.println("T:→→↑   U: →↑↑     V:→↑←     W:→↑→     X:→←←       Y:→ ←↑   Z:→←→    !: ←←←   ?: →→→     .:↑↑↑      espaco:←→→");

  Serial.println();

  while(1){
   int i;
  Xg=leituraEmX()/256.0;
  Yg=leituraEmY()/256.0;
  Zg=leituraEmZ()/256.0;

  if(Zg > 0.4){
    Serial.println();
    Serial.println("Saindo do Modo 2...");
    delay(1000);
    Serial.println();
    Serial.println("Selecione o Modo:");
    break;
  }

  if(!baixo){ // vai guardando em sequencia os movimentos lidos enquanto nao eh feito um movimento para baixo
    if(Xg > -0.4 && Xg < 0.4 && Yg > -0.4 && Yg < 0.4 && Zg > -1 && Zg < -0.8 && (cima || baixo || direita || esquerda)){
     cima = false;
     baixo = false;
     direita = false;
     esquerda = false;
    } 
   
   else if(Xg >= 0.5 && !cima){
     Serial.print("↑ ");
     cima = true;
     sequencia += "C";
   }
   else if(Xg <= -0.5 && !baixo){
     baixo = true;
   }
   else if(Yg >= 0.5 && !esquerda){
     Serial.print("← ");
     esquerda = true;
     sequencia += "E";
   }
   else if(Yg <= -0.5 && !direita){
     Serial.print("→ ");
     direita = true;
     sequencia += "D";
   }
  }else{ //quando um movimento eh feito para baixo a proxima vez q o programa executar, entrara aqui
   mudou = false; //para controlar que a palavra so sera impressa na tela caso tenha sofrido alguma alteracao
   carac = IdentificarSequencia(sequencia); //recebe o caractere correspondente a sequencia de movimentos feitos
   if(palavra.equals("\0") && !carac.equals("BACK") && !sequencia.equals("\0")){ //entrara nesse if somente quando a palavra estiver vazia
     palavra = carac;
     mudou = true;
   }else if(carac.equals("BACK")){ // entrara nesse if caso o comando tenha sido para apagar uma letra digitada, a parte de apagar na verdade vai sobreescrever a letra com um '_', e quando outra letra for digitada no lugar, sera colocada no lugar de '_'
     for(i = 0; palavra.charAt(i) != '\0' && palavra.charAt(i) != '_'; i++); // para achar a ultima posicao com uma letra valida a ser apagada
     ultPosApag = i-1;
     if(i > 0){ // se nao for a ultima ultima letra restante na palavra, a ultima letra da direita para esquerda sera substituida por '_'
       palavra.setCharAt(i-1, '_');
     }
     if(palavra.charAt(0) == '_'){  // se for a ultima letra restante na palavra, palavra ira se tornar uma string vazia
       palavra = "\0";
       ultPosApag = -1; // para mostrar que nao existe uma ultima posicao apagada
     }
     mudou = true; // como houve alteracao na string palavra, ela sera impressa
   }else if(!sequencia.equals("\0")){ //caso palavra ja possua caracteres e a sequencia nao tenha sido vazia
     if(ultPosApag >= 0){ // para ver se teve uma ultima letra apagada
       palavra.setCharAt(ultPosApag, carac.charAt(0)); // a primeira posicao da esquerda para direita que possuir um '_' recebera uma letra no lugar
       if(ultPosApag < palavra.length()-1){ // se a ultima posicao apagada nao for igual a ultima posicao valida da string palavra
         ultPosApag++;  // avanca para a proxima posicao que possui um '_'
       }else{ // se a ultima posicao apagada for igual a ultima posicao valida da string palavra, ultima posicao apagada nao existira mais
         ultPosApag = -1;
       }
     }else{ //caso nao tenha uma ultima letra apagada, carac sera apenas concatenada no final de palavra
       palavra = palavra + carac;
     }
     mudou = true; // como houve alteracao na string palavra, ela sera impressa
   }
   if(mudou){ //caso palavra tenha sofrido alguma alteracao, ela sera impressa
     Serial.println(palavra);
   }
   sequencia = "\0";
   baixo = false; //baixo recebe falso para que sequencia possa novamente comecar a armazenar a sequencia de movimentos feitos
  }
  }
}

 
String IdentificarSequencia(String seq){
  if(seq.equals("E")){
    return "A";
  }else if(seq.equals("D")){
    return "B";
  }else if(seq.equals("EC")){
    return "C";
  }else if(seq.equals("EE")){
    return "D";
  }else if(seq.equals("ED")){
    return "E";
  }else if(seq.equals("DD")){
    return "F";
  }else if(seq.equals("DC")){
    return "G";
  }else if(seq.equals("DE")){
    return "H";
  }else if(seq.equals("CC")){
    return "I";
  }else if(seq.equals("CE")){
    return "J";
  }else if(seq.equals("CD")){
    return "K";
  }else if(seq.equals("EED")){
    return "L";
  }else if(seq.equals("EEC")){
    return "M";
  }else if(seq.equals("EDC")){
    return "N";
  }else if(seq.equals("EDE")){
    return "O";
  }else if(seq.equals("ECE")){
    return "P";
  }else if(seq.equals("ECD")){
    return "Q";
  }else if(seq.equals("ECC")){
    return "R";
  }else if(seq.equals("DDE")){
    return "S";
  }else if(seq.equals("DDC")){
    return "T";
  }else if(seq.equals("DCC")){
    return "U";
  }else if(seq.equals("DCE")){
    return "V";
  }else if(seq.equals("DCD")){
    return "W";
  }else if(seq.equals("DEE")){
    return "X";
  }else if(seq.equals("DEC")){
    return "Y";
  }else if(seq.equals("DED")){
    return "Z";
  }else if(seq.equals("EEE")){
    return "!";
  }else if(seq.equals("DDD")){
    return "?";
  }else if(seq.equals("CCC")){
    return ".";
  }else if(seq.equals("EDD")){
    return " ";
  }else if(seq.equals("C")){
    return "BACK";
  }
  return "\0";
}

double leituraEmY(){
  Wire.beginTransmission(ADXAddress); // transmit to device
  Wire.write(Register_Y0);
  Wire.write(Register_Y1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress,2); 
  if(Wire.available()<=2)   
  {
    Y0 = Wire.read();
    Y1 = Wire.read(); 
    Y1=Y1<<8;
    Y_out=Y0+Y1;
  }

  return Y_out;
}

double leituraEmX(){
  //--------------X
  Wire.beginTransmission(ADXAddress); // transmit to device
  Wire.write(Register_X0);
  Wire.write(Register_X1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress,2);
  if(Wire.available()<=2)
  {
    X0 = Wire.read();
    X1 = Wire.read(); 
    X1=X1<<8;
    X_out=X0+X1;   
  }

  return X_out;
}

double leituraEmZ(){
  //------------------Z
  Wire.beginTransmission(ADXAddress); // transmit to device
  Wire.write(Register_Z0);
  Wire.write(Register_Z1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress,2); 
  if(Wire.available()<=2)   
  {
    Z0 = Wire.read();
    Z1 = Wire.read(); 
    Z1=Z1<<8;
    Z_out=Z0+Z1;
  }

  return Z_out;
}


//---------------------------------------------------------------------------------------------------
void modo3(){
  
  Serial.println();
  Serial.println("Modo 3 selecionado");
  delay(1000);
  Serial.println();
  Serial.println("Entrando no modo calculadora");
  
  while(1){

  if(Zg > 0.4){
    Serial.println();
    Serial.println("Saindo do Modo 3...");
    delay(1000);
    Serial.println();
    Serial.println("Selecione o Modo:");
    break;
  }

  //--------------X
  Wire.beginTransmission(ADXAddress); // transmit to device
  Wire.write(Register_X0);
  Wire.write(Register_X1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress, 2);
  if (Wire.available() <= 2)
  {
    X0 = Wire.read();
    X1 = Wire.read();
    X1 = X1 << 8;
    X_out = X0 + X1;
  }

  //------------------Y
  Wire.beginTransmission(ADXAddress); // transmit to device
  Wire.write(Register_Y0);
  Wire.write(Register_Y1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress, 2);
  if (Wire.available() <= 2)
  {
    Y0 = Wire.read();
    Y1 = Wire.read();
    Y1 = Y1 << 8;
    Y_out = Y0 + Y1;
  }
  //------------------Z
  Wire.beginTransmission(ADXAddress); // transmit to device
  Wire.write(Register_Z0);
  Wire.write(Register_Z1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress, 2);
  if (Wire.available() <= 2)
  {
    Z0 = Wire.read();
    Z1 = Wire.read();
    Z1 = Z1 << 8;
    Z_out = Z0 + Z1;
  }
  //
  Xg = X_out / 256.0;
  Yg = Y_out / 256.0;
  Zg = Z_out / 256.0;
  
  if(cont == 0){
    Serial.print("Digite o primeiro número: ");
    cont++;
  } else if(cont == 1){
    if(primeiroNumEscolhido){
      Serial.print("Digite o operador: ");
      cont++;
    }
  } else if(cont == 2){
    if(operadorEscolhido){
      Serial.print("Digite o segundo número: ");
      cont++;
    }
  }
  
  
  if (estavaStandBy) {
    if (Xg > TOL) {
      estavaStandBy = false;
      Serial.print("E");
      sequencia1[contadorRegistro] = 'E';
      contadorRegistro++;
      //registra esquerda
    } else if (Xg < -TOL) {
      estavaStandBy = false;
      Serial.print("D");
      sequencia1[contadorRegistro] = 'D';
      contadorRegistro++;
      //registra direita
    } else if (Yg > TOL) {
      estavaStandBy = false;
      Serial.println("F");
      sequencia1[contadorRegistro] = 'F';
      contadorRegistro++;
      //registra frente
    } else if (Yg < -TOL) {
      estavaStandBy = false;
      Serial.print("T");
      sequencia1[contadorRegistro] = 'T';
      contadorRegistro++;
      //registra trás
    }

  } else {
    if ((Xg > -TOL) && (Xg < TOL) && (Yg > -TOL) && (Yg < TOL)) {
      //Serial.println("Entrou standBy");
      estavaStandBy = true;
    }
  }

  //Verificar letra
  if (sequencia1[2] != 'N') {
    Serial.println();
    if (!primeiroNumEscolhido) {
      algarismo = PegaAlgarismo(sequencia1);
      if (algarismo == -1) {
        Serial.println("Erro1");
        erro = true;
        sequencia1[0] = 'N'; sequencia1[1] = 'N'; sequencia1[2] = 'N';
      } else {
        primeiroNum = primeiroNum * 10 + algarismo;
        Serial.println(primeiroNum);
        erro = false;
        sequencia1[0] = 'N'; sequencia1[1] = 'N'; sequencia1[2] = 'N';
      }
    } else if (!operadorEscolhido) {
      algarismo = PegaAlgarismo(sequencia1);
      if (algarismo == -1) {
        Serial.println("Erro2");
        erro = true;
        sequencia1[0] = 'N'; sequencia1[1] = 'N'; sequencia1[2] = 'N';
      } else {
        if (algarismo == 0) {
          operador = '+';
          sequencia1[0] = 'N'; sequencia1[1] = 'N'; sequencia1[2] = 'N';
          erro = false;
        } else if (algarismo == 1) {
          operador = '-';
          sequencia1[0] = 'N'; sequencia1[1] = 'N'; sequencia1[2] = 'N';
          erro = false;
        } else if (algarismo == 2) {
          operador = '*';
          sequencia1[0] = 'N'; sequencia1[1] = 'N'; sequencia1[2] = 'N';
          erro = false;
        } else if (algarismo == 3) {
          operador = '/';
          sequencia1[0] = 'N'; sequencia1[1] = 'N'; sequencia1[2] = 'N';
          erro = false;
        } else {
          Serial.println("Erro3");
          erro = true;
          sequencia1[0] = 'N'; sequencia1[1] = 'N'; sequencia1[2] = 'N';
        }
        Serial.print(primeiroNum);
        Serial.println(operador);
      }
    } else if (!segundoNumEscolhido) {
      algarismo = PegaAlgarismo(sequencia1);
      if (algarismo == -1) {
        Serial.println("Erro4");
        erro = true;
        sequencia1[0] = 'N'; sequencia1[1] = 'N'; sequencia1[2] = 'N';
      } else {
        segundoNum = segundoNum * 10 + algarismo;
        Serial.print(primeiroNum);
        Serial.print(operador);
        Serial.println(segundoNum);
        sequencia1[0] = 'N'; sequencia1[1] = 'N'; sequencia1[2] = 'N';
        erro = false;
      }
    }
    //Se confirmado ///////////////////////
  } else if (sequencia1[0] == 'F') {
    if (!primeiroNumEscolhido) {
      if (!erro) {
        Serial.println("Confirmado!");
        delay(100);
        primeiroNumEscolhido = 1;
      }
      sequencia1[0] = 'N'; sequencia1[1] = 'N'; sequencia1[2] = 'N';
      contadorRegistro = 0;
    } else if (!operadorEscolhido) {
      if (!erro) {
        Serial.println("Confirmado!");
        delay(100);
        operadorEscolhido = 1;
      }
      sequencia1[0] = 'N'; sequencia1[1] = 'N'; sequencia1[2] = 'N';
      contadorRegistro = 0;
    } else if (!segundoNumEscolhido) {
      if (!erro) {
        Serial.println("Confirmado!");
        delay(100);
        segundoNumEscolhido = 1;
        Serial.print(primeiroNum);
        Serial.print(operador);
        Serial.print(segundoNum);
        Serial.print(" = ");
        if (operador == '+') {
          Serial.println((primeiroNum + segundoNum));
        } else if (operador == '-') {
          Serial.println((primeiroNum - segundoNum));
        } if (operador == '*') {
          Serial.println((primeiroNum * segundoNum));
        } if (operador == '/') {
          if (segundoNum != 0) {
            Serial.println(((float)primeiroNum / segundoNum));
          } else {
            Serial.println("Dividindo por zero");
          }
        }
        Reiniciar();
      }
      sequencia1[0] = 'N'; sequencia1[1] = 'N'; sequencia1[2] = 'N';
      contadorRegistro = 0;
    }
  }

  if (contadorRegistro > 2) {
    contadorRegistro = 0;
  }

  delay(100);
    
  }

}


//---------------------------------------------------------------------------------------------------


void loop()
{
  //--------------X
  Wire.beginTransmission(ADXAddress); // transmit to device
  Wire.write(Register_X0);
  Wire.write(Register_X1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress,2); 
  if(Wire.available()<=2)   
  {
    X0 = Wire.read();
    X1 = Wire.read(); 
    X1=X1<<8;
    X_out=X0+X1;   
  }

   //------------------Y
  Wire.beginTransmission(ADXAddress); // transmit to device
  Wire.write(Register_Y0);
  Wire.write(Register_Y1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress,2); 
  if(Wire.available()<=2)   
  {
    Y0 = Wire.read();
    Y1 = Wire.read(); 
    Y1=Y1<<8;
    Y_out=Y0+Y1;
  }


  Xg=X_out/256.0;
  Yg=Y_out/256.0;

  delay(1000);


  if(Xg < -0.35){
    modo1();
  }

  if(Xg > 0.35){
    modo2();
  }

  if(Yg > 0.35){
    modo3();
  }

}
