//Universidad del Valle de Guatemala
//Departamento de Ingenieria Mecatronica y Electronica
//Digital 2 - Seccion 20
//Jorge Castillo - 18209

// se incluyen las librerias
#include <SPI.h>
#include <SD.h>

// defino mis variables
File archivo;
File root;

int opcion;
void opciones(void);
void mostrar(void);

void setup()
{
  Serial.begin(115200);
  SPI.setModule(0); 

  Serial.print("Initializing SD card...");
  pinMode(PA_3, OUTPUT);

  if (!SD.begin(PA_3)) {//PA_3 es el CS
    Serial.println("initialization failed");
    return;
  }
  Serial.println("initialization done.");
  opciones();
}



void loop() {

  if (Serial.available() > 0){
   opcion = Serial.read();
   delay(250);
   if (opcion == '1' || opcion == '2' || opcion == '3' || opcion == '4' ){
    mostrar();
   }
   else {
     Serial.println("Por favor ingrese otro numero ");
  }
  }
}

void opciones(void) {
  Serial.println();
  Serial.println("Las figuras disponibles para desplegar son: ");
  root = SD.open("/");
  printDirectory(root, 0);
  root.close();
  Serial.println("Ingrese el numero de imagen que quiere visualizar: \n 1 -> Calabaza \n 2 -> Corazon \n 3 -> Dino \n 4 -> Ghost");
}

void printDirectory(File dir, int numTabs) {
   while(true) {
     
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}

void mostrar(void){
  switch (opcion){
    case '1':
     archivo = SD.open("Calabaza.txt");
      if (archivo) {
        // read from the file until there's nothing else in it:
        while (archivo.available()) {
          Serial.write(archivo.read());
        }
        // close the file:
        archivo.close();
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening document");
      }
      Serial.println("Ingrese el numero de imagen que quiere visualizar: \n 1 -> Calabaza \n 2 -> Corazon \n 3 -> Dino \n 4 -> Ghost");
     break;
    case '2':
     archivo = SD.open("Corazon.txt");
      if (archivo) {
        // read from the file until there's nothing else in it:
        while (archivo.available()) {
          Serial.write(archivo.read());
        }
        // close the file:
        archivo.close();
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening document");
      }
      Serial.println("Ingrese el numero de imagen que quiere visualizar: \n 1 -> Calabaza \n 2 -> Corazon \n 3 -> Dino \n 4 -> Ghost");
     break;
    case '3':
     archivo = SD.open("Dino.txt");
      if (archivo) {
        // read from the file until there's nothing else in it:
        while (archivo.available()) {
          Serial.write(archivo.read());
        }
        // close the file:
        archivo.close();
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening document");
      }
      Serial.println("Ingrese el numero de imagen que quiere visualizar: \n 1 -> Calabaza \n 2 -> Corazon \n 3 -> Dino \n 4 -> Ghost");
     break;
    case '4':
     archivo = SD.open("Ghost.txt");
      if (archivo) {
        // read from the file until there's nothing else in it:
        while (archivo.available()) {
          Serial.write(archivo.read());
        }
        // close the file:
        archivo.close();
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening document");
      }
      Serial.println("Ingrese el numero de imagen que quiere visualizar: \n 1 -> Calabaza \n 2 -> Corazon \n 3 -> Dino \n 4 -> Ghost");
     break;
     
  }
}
