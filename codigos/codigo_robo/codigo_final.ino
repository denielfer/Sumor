//codigo final

// Declaração ultrassom
#include <Ultrasonic.h>
Ultrasonic ultrassom_frente(1,2);
Ultrasonic ultrassom_esquerda(12,13); 
Ultrasonic ultrassom_direita(11,10); 
// Declaração sensor de linha
#define Sen_Lin_F1 7
#define Sen_Lin_F2 8
#define Sen_Lin_T 9
// Declaração motor  
int IN1 = 4;//Direita
int IN2 = 5;
int IN3 = 6;//Esquerda
int IN4 = 7; 


long distancia[3]; // índices 0,1 e 2, respectivamente, frente, direita, esquerda.
int inimigo[3]; // índices 0,1 e 2, respectivamente, frente, direita, esquerda.

void setup()
{ 
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

void loop() 
{
  // ULTRASSOM -------------------------------------
// Guarda as distâncias, em centímetros, nos índices correnspondetes do vetor distancia.
  distancia[0]= ultrassom_frente.Ranging(CM);
  distancia[1]= ultrassom_esquerda.Ranging(CM);
  distancia[2]= ultrassom_direita.Ranging(CM);
  
  // Guarda 1, se for detectado um objeto em até 90cm e 0 se não for detectado nada nesta distância
  for (int i=0; i<3; i++)
  {
     if (distancia[i] <=90)
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
    frente();
  }else if(inimigo[2] == 1) // se o inimigo estiver à esquerda
  {
      gira_esquerda();
  }else // se o inimigo não for encontrado ou se estiver à esquerda
  {
    gira_direita();
  }

  // SENSOR DE LINHA---------------------------------------------
  bool F1 = digitalRead(Sen_Lin_F1); /*Sensor Frontal 1*/
  bool F2 = digitalRead(Sen_Lin_F2); /*Sensor Frontal 2*/
  bool TR = digitalRead(Sen_Lin_T); /*Sensor Traseiro*/

  if(F1){ //Se linha na frente 1
    tras(); //Faça com que o robô dê ré.
  }   
  if(F2){ //Se linha na frente do 2
    tras(); //Faça com que o robô dê ré.
  }
  if(TR){ //Se linha atrás
    frente(); //Faça com que o robô vá para frente.
  }
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

void frente()
{
  esquerda_frente();
  direita_frente();
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
