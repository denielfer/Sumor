//########Codigo final########
// Ultrasson e motor já integrados; fazer: integrar sensor de linha(tem que ter prioridade)

  //Declarações ------------------------------------
//Declaração ultrassom
#include <Ultrasonic.h>
Ultrasonic ultrassom_frente(2,3);
Ultrasonic ultrassom_esquerda(10,9); 
//Ultrasonic ultrassom_direita(11,8); 
long distancia[3]; // índices 0,1 e 2, respectivamente, frente, direita, esquerda.
int inimigo[3]; // índices 0,1 e 2, respectivamente, frente, direita, esquerda.
//Declaração sensor de linha
#define Sen_Lin_F1 7
#define Sen_Lin_F2 8
#define Sen_Lin_T 9
// Declaração motor  
int IN1 = 4;//Direita
int IN2 = 5;
int IN3 = 6;//Esquerda
int IN4 = 7; 

void setup()
{ 
  Serial.begin(115200);
  // setup do motor
  pinMode(IN1, OUTPUT);//Direita
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);//Esquerda
  pinMode(IN4, OUTPUT);
  // Setup do sensor de linha
  pinMode(Sen_Lin_F1, INPUT);
  pinMode(Sen_Lin_F2, INPUT);
  pinMode(Sen_Lin_T, INPUT);
}

//FUNCOES
void frente()
{
  direita_frente();
  esquerda_frente();
}

void direita_frente()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
}

void direita_tras()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
}

void direita_para()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,HIGH);
}

void esquerda_frente()
{
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void esquerda_tras()
{
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

void esquerda_para()
{
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,HIGH);
}

void tras()
{
  esquerda_tras();
  direita_tras();
}

void para()
{
  esquerda_para();
  direita_para();
}

void gira_direita()
{
  esquerda_frente();
  direita_tras();
}

void gira_esquerda()
{
  esquerda_tras();
  direita_frente();
}




void loop() 
{
  //ULTRASSOM -------------------------------------
// Guarda as distâncias, em centímetros, nos índices correnspondetes do vetor distancia.
  distancia[0]= ultrassom_frente.Ranging(CM);
  distancia[1]= ultrassom_esquerda.Ranging(CM);
  
  // Guarda 1, se for detectado um objeto em até 90cm e 0 se não for detectado nada nesta distância
  for (int i=0; i<2; i++)
  {
     if (distancia[i] <=10)
    {
     inimigo[i]=1;
    }else
    {
     inimigo[i]=0;
    }
  }
  // Decide se o robô anda para a frente ou vira para um dos lados, dependendo da posição do inimigo.
  if (inimigo[0]==1) // se o inimigo estiver à frente
  {
    para();
    Serial.println("frente");
    frente();
  }else if (inimigo[1] == 1){ //se o inimigo estiver à esquerda
    para();
    Serial.println("esquerda");
    gira_esquerda();
  }
  else{
    para();
    Serial.println("direita");
    gira_direita();
  }

}
