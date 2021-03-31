//Universidad del Valle de Guatemala
//Electronica Digital II - sección 20
//Jorge Castillo Palomo - 18209
//Laboratoio 4

//----------Definicion de Variables---------------

// estado de botones
int state1 = 0;
int state2 = 0;

// revisar flancos
int flanco1 = 1;
int flanco2 = 1;

//inicio del semaforo
int start = 0;

//contadores
int contp = 0;
int contn = 0;

//JUGADOR 1
const byte p0 = 11; 
const byte p1 = 12;
const byte p2 = 13; 
const byte p3 = 14; 
const byte p4 = 15; 
const byte p5 = 37;
const byte p6 = 18; 
const byte p7 = 19; 

//JUGADOR 2
const byte n0 = 2; 
const byte n1 = 3; 
const byte n2 = 4; 
const byte n3 = 5;
const byte n4 = 6; 
const byte n5 = 7; 
const byte n6 = 8; 
const byte n7 = 9;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // setear puertos de leds
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  pinMode(p0, OUTPUT);
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
  pinMode(p4, OUTPUT);
  pinMode(p5, OUTPUT);
  pinMode(p6, OUTPUT);
  pinMode(p7, OUTPUT);

  pinMode(n0, OUTPUT);
  pinMode(n1, OUTPUT);
  pinMode(n2, OUTPUT);
  pinMode(n3, OUTPUT);
  pinMode(n4, OUTPUT);
  pinMode(n5, OUTPUT);
  pinMode(n6, OUTPUT);
  pinMode(n7, OUTPUT);
  
  //Pushes de la tiva
  pinMode(PUSH1, INPUT_PULLUP);
  pinMode(PUSH2, INPUT_PULLUP);
  //habilitar la bandera del semaforo
  start = 1;

}

void loop() {
  // put your main code here, to run repeatedly: 
  state1 = digitalRead(PUSH1);
  state2 = digitalRead(PUSH2);

  if ((state1 == LOW||state2 == LOW) && start == 1) {
    start = 0;
    resetear();
    //Secuencia de inicio del semaforo
    digitalWrite(GREEN_LED, LOW); 
    digitalWrite(RED_LED, HIGH);
    delay(1000);
    digitalWrite(GREEN_LED, LOW); 
    digitalWrite(RED_LED, LOW);
    delay(1000);
    digitalWrite(GREEN_LED, LOW); 
    digitalWrite(RED_LED, HIGH);
    delay(500);
    digitalWrite(GREEN_LED, HIGH);
    delay(500);
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    delay(500);
    digitalWrite(GREEN_LED, LOW);

    // resetear los contadores para iniciar de nuevo el juego
    contp = 0;
    contn = 0;
    
  while (start != 1) {

      //lectura de botones
      state1 = digitalRead(PUSH1);
      state2 = digitalRead(PUSH2);

      //poll de los flancos 
      if (state1 != flanco1) {
        flanco1 = state1;
        //si se presiona, aumentar el contador
        if (state1 == LOW) {
          contp++;
          luces(contp,1);
        }
      }

      else if (state2 != flanco2) {
        flanco2 = state2;
        if (state2 == LOW) {
          contn++;
          luces(contn,2);
          
        }
      }
    }
  }
}
void luces(int i, int j) {
  if (j == 1) {

    if (i == 0) {
      digitalWrite(p0, LOW);
      digitalWrite(p1, LOW);
      digitalWrite(p2, LOW);
      digitalWrite(p3, LOW);
      digitalWrite(p4, LOW);
      digitalWrite(p5, LOW);
      digitalWrite(p6, LOW);
      digitalWrite(p7, LOW);
    }
    if (i == 1) {
      digitalWrite(p0, HIGH);
    }
    
    if (i == 2) {
      digitalWrite(p0, LOW);
      digitalWrite(p1, HIGH);
    }
    
    if (i == 3) {
      digitalWrite(p1, LOW);
      digitalWrite(p2, HIGH);
    }
    
    if (i == 4) {
      digitalWrite(p2, LOW);
      digitalWrite(p3, HIGH);
    }
    
    if (i == 5) {
      digitalWrite(p3, LOW);
      digitalWrite(p4, HIGH);
    }
    
    if (i == 6) {
      digitalWrite(p4, LOW);
      digitalWrite(p5, HIGH);
    }
    
    if (i == 7) {
      digitalWrite(p5, LOW);
      digitalWrite(p6, HIGH);
    }
    
    if (i == 8) {
      digitalWrite(p6, LOW);
      digitalWrite(p7, HIGH);
    }
    if (i == 9) {
      start = 1;
      digitalWrite(p7, LOW);
      digitalWrite(BLUE_LED, HIGH);
      delay(500);
      digitalWrite(BLUE_LED, LOW);
      resetear();
    }
    }

    
    else if (j == 2){
       if (i == 0) {
      digitalWrite(n0, LOW);
      digitalWrite(n1, LOW);
      digitalWrite(n2, LOW);
      digitalWrite(n3, LOW);
      digitalWrite(n4, LOW);
      digitalWrite(n5, LOW);
      digitalWrite(n6, LOW);
      digitalWrite(n7, LOW);
    }
    if (i == 1) {
      digitalWrite(n0, HIGH);
    }
    
    if (i == 2) {
      digitalWrite(n0, LOW);
      digitalWrite(n1, HIGH);
    }
    
    if (i == 3) {
      digitalWrite(n1, LOW);
      digitalWrite(n2, HIGH);
    }
    
    if (i == 4) {
      digitalWrite(n2, LOW);
      digitalWrite(n3, HIGH);
    }
    
    if (i == 5) {
      digitalWrite(n3, LOW);
      digitalWrite(n4, HIGH);
    }
    
    if (i == 6) {
      digitalWrite(n4, LOW);
      digitalWrite(n5, HIGH);
    }
    
    if (i == 7) {
      digitalWrite(n5, LOW);
      digitalWrite(n6, HIGH);
    }
    
    if (i == 8) {
      digitalWrite(n6, LOW);
      digitalWrite(n7, HIGH);
    }
    if (i == 9) {
      start = 1;
      digitalWrite(n7, LOW);
      digitalWrite(BLUE_LED, HIGH);
      digitalWrite(RED_LED, HIGH);
      delay(500);
      digitalWrite(BLUE_LED, LOW);
      digitalWrite(RED_LED, LOW);
      resetear();
    }
    }
 }

 //Apagamos todos nuestros LEDS
void resetear() {
  digitalWrite(p0, LOW);
  digitalWrite(p1, LOW);
  digitalWrite(p2, LOW);
  digitalWrite(p3, LOW);
  digitalWrite(p4, LOW);
  digitalWrite(p5, LOW);
  digitalWrite(p6, LOW);
  digitalWrite(p7, LOW);

 digitalWrite(n0, LOW);
 digitalWrite(n1, LOW);
 digitalWrite(n2, LOW);
 digitalWrite(n3, LOW);
 digitalWrite(n4, LOW);
 digitalWrite(n5, LOW);
 digitalWrite(n6, LOW);
 digitalWrite(n7, LOW); 
      
}
    
