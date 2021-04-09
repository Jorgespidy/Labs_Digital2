//Universidad del Valle de Guatemala
//Departamento de Ingenieria Mecatronica y Electronica
//Digital 2 - Seccion 20
//Jorge Castillo - 18209


#include <SPI.h>
#include <SD.h>

//File archivo;
File root;

int opcion = 0;

void opciones(void);

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
  // put your main code here, to run repeatedly: 
  
}


void opciones(void) {
  Serial.println();
  Serial.println("Las figuras disponibles para desplegar son: ");
  root = SD.open("/");
  printDirectory(root, 0);
  root.close();
  
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
