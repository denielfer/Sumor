// Declaração ultrassom
#include <Ultrasonic.h>
Ultrasonic ultrassom_frente(1,2);
// Declaração sensor de linha
#define Sen_Lin_F1 7
// Declaração motor  
int IN1 = 4;//Direita
int IN2 = 5;
int IN3 = 6;//Esquerda
int IN4 = 7; 


long distancia; 
bool inimigo;

void setup()
{ 
  // setup do motor
  pinMode(IN1, OUTPUT);//Direita
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);//Esquerda
  pinMode(IN4, OUTPUT);
  // sensor linha
  pinMode(Sen_Lin_F1, INPUT);
}

void loop() 
{
  // ULTRASSOM -------------------------------------
// Guarda as distâncias, em centímetros.
  distancia= ultrassom_frente.Ranging(CM);
  
  // Decide se o robô anda para a frente ou vira para direita.
  if ( distancia <=90 ) // se o inimigo estiver à frente move ( for detectado pelo sensor).
  {
    digitalWrite(IN3,HIGH);//esquerda horario
    digitalWrite(IN4,LOW);
    digitalWrite(IN1,LOW); // direita horario
    digitalWrite(IN2,HIGH);
  }else // se o inimigo não for encontrado gira para direita
  {
    digitalWrite(IN3,HIGH); //esquerda horario
    digitalWrite(IN4,LOW);  
    digitalWrite(IN1,HIGH);//direita anti-horario
    digitalWrite(IN2,LOW);
  }

  // SENSOR DE LINHA---------------------------------------------
  bool F1 = digitalRead(Sen_Lin_F1); 

  if(F1){ //Se linha for achada para
    // Testa se com LOW funciona, se nao troca por HIGH
    digitalWrite(IN3,LOW); // Para esquerda
    digitalWrite(IN4,LOW); 
    digitalWrite(IN1,LOW);// Para direita
    digitalWrite(IN2,LOW);
  }
}
