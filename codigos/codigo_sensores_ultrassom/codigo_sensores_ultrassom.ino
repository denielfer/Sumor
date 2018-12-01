
// Sensor utilizado: HC-SR04
#include <Ultrasonic.h>
Ultrasonic ultrassom_frente(1,2);
Ultrasonic ultrassom_esquerda(3,4); 
Ultrasonic ultrassom_direita(5,6); 

long distancia[3]; // índices 0,1 e 2, respectivamente, frente, direita, esquerda.
int inimigo[3]; // índices 0,1 e 2, respectivamente, frente, direita, esquerda.
 
// Esta função "setup" roda uma vez quando a placa e ligada ou resetada
 void setup() 
 {
   //pinMode(13, OUTPUT); //debug com leds
   //pinMode(12, OUTPUT); //debug com leds
   Serial.begin(9600); //Habilita Comunicação Serial a uma taxa de 9600 bauds.
 }
 
// Função que se repete infinitamente quando a placa é ligada
 void loop()
 {
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
    Serial.print("anda para frente");
  }else if (inimigo[1] == 1) // se o inimigo estiver à direita
  {
    Serial.print("vira no sentido horário");
  }else if(inimigo[2] == 1) // se o inimigo estiver à esquerda
  {
      Serial.print("vira no sentido anti-horário");
  }else // se o inimigo não for encontrado
  {
    Serial.print("vira no sentido horário ou anti-horário para buscar o inimigo");
  }
  

  // Debug com leds - não faz parte do código final
  /*digitalWrite(13, LOW); //Pino 13, led acende se nada for detectado numa distância de 90cm
   digitalWrite(12, LOW); //pino 12, led acende se for detectado um objeto em até 90cm de distância
   if (inimigo[0] == 1) //
   {
    digitalWrite(12, HIGH);
   }else
   {
    digitalWrite(13, HIGH);
   }*/
 }
