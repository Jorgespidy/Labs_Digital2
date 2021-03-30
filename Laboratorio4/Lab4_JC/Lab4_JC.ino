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




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // setear puertos de leds
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
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
    
  }
  
}
