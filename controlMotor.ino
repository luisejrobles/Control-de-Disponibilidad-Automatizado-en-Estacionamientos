#include <LiquidCrystal.h>
/*Para motor entrada*/
int tiempoSubida = 136; /*Es el tiempo que durara el motor activado para la entrada, puede variar dependiendo si la barra llega a su lugar para subir y bajar*/
int tiempoBajada = 135;
/*Para motor de la salida, porque ocupa mas para moverse*/
int tiempoSubida2 = 150; /*Es el tiempo que durara el motor activado para la salida, puede variar dependiendo si la barra llega a su lugar para subir y bajar*/
int tiempoBajada2 = 149;
int pinMotor1 = 3; /*motor pin1 sube Entrada*/
int pinMotor2 = 2; /*motor pin2  baja Entrada*/
int pinMotor3 = A3; /*motor pin1 sube Salida*/
int pinMotor4 = A2; /*motor pin1 sube Salida*/
int otroAux=0;
/*
  funcion           pinMotor1/3   pinMotor2/4
  sin giro               0           0
  izquierda(baja)        0           1
  derecha(sube)          1           0
  sin giro               1           1
*/
int pinSubida1 = A5; /*pin entrada para subir barra*/ 
int pinBajada1 = A4; /*pin entrada para bajar barra*/
int pinSubida = A0; /*pin entrada para subir barra*/
int pinBajada = A1; /*pin entrada para bajar barra*/
int pinDisponible = 1; /*Indicara cuando hay espacios disponibles con el sistema contador de espacios dispobibles,(cuando haya espacio que mande 1, si ya no hay un 0).*/
int bandera = 0; /*ayudara con los movimientos de la barra empezara abajo*/
int bandera1 = 0;
int aux=0;

/*Pines para el lcd, indica el numero de espacios*/
/*Arreglo de 10 entradas del estacionamiento*/ 
int entrada[10] = {A6,A7,A8,A9,A10,A11,A12,A13,A14,A15};
/*Este llebara el conteo de los pines*/
int auxiliar;


int pinDeco1=10;
int pinDeco2=11;
int pinDeco3=12;
int pinDeco4=13;
/*
  bandrea=0 La barra se encuentra abajo
  bandera=1 La barra se encuentra arriba
*/
LiquidCrystal lcd(8,9,4,5,6,7);
/*Esta funcion se ejecuta 1 vez para configurar*/
void setup() {
  setupMotor();
  /*Setup pines de estacionamiento*/
  for(int i =0;i<10;i++){
    pinMode(entrada[i], INPUT);   /*pines de salida*/
  }
}

void setupMotor() {
  /*Entrada*/
  lcd.begin(16, 2);
  pinMode(pinMotor1, OUTPUT);   /*pines de salida*/
  pinMode(pinMotor2, OUTPUT);   /*pines de salida*/
  pinMode(pinSubida, INPUT);   /*pines de entrada, recivira la señal para subir la barra*/
  pinMode(pinBajada, INPUT);   /*pines de entrada, recivira la señal para bajar la barra*/
  digitalWrite(pinMotor1, LOW);
  digitalWrite(pinMotor2, LOW); /*Se inicializa el motor con 0's para que no gire*/
  /*Salida*/
  pinMode(pinMotor3, OUTPUT);   /*pines de salida*/
  pinMode(pinMotor4, OUTPUT);   /*pines de salida*/
  pinMode(pinSubida1, INPUT);   /*pines de entrada, recivira la señal para subir la barra*/
  pinMode(pinBajada1, INPUT);   /*pines de entrada, recivira la señal para bajar la barra*/
  digitalWrite(pinMotor3, LOW);
  digitalWrite(pinMotor4, LOW); /*Se inicializa el motor con 0's para que no gire*/

  /*pinMode(pinDeco1,INPUT);
  pinMode(pinDeco2,INPUT);
  pinMode(pinDeco3,INPUT);
  pinMode(pinDeco4,INPUT);
  */
}
/*Esta funcion se repite siempre*/
void loop() {
  loopMotor1();
}

void loopMotor1() {
  for(int i =0;i<10;i++){
    if(digitalRead(entrada[i])==1){
      aux++;
    } 
  }
  if(aux == 0){
    lcd.print("Hay 10 espacios");  
  }else if(aux == 1){
    lcd.print("Hay 9 espacios");
  }else if(aux == 2){
    lcd.print("Hay 8 espacios");
  }else if(aux == 3){
    lcd.print("Hay 7 espacios");
  }else if( aux == 4){
    lcd.print("Hay 6 espacios");
  }else if(aux == 5){
    lcd.print("Hay 5 espacios");
  }else if(aux == 6){
    lcd.print("Hay 4 espacios");
  }else if(aux == 7){
    lcd.print("Hay 3 espacios");
  }else if(aux == 8){
    lcd.print("Hay 2 espacios");
  }else if(aux == 9){
    if(otroAux==1)
      lcd.print("as");
    else
      lcd.print("Hay 1 espacio");
  }else{
    lcd.print("No hay espacios");
    pinDisponible=0; //nuevo
  }
  delay(100);
  if (pinDisponible == 1 || bandera == 1) { /*Cuando haya espacios dispobibles y cuando la barra este arriba, en dado caso que el contador se active y la barra se encutre arriba*/
    if (digitalRead(pinSubida) == HIGH && digitalRead(pinBajada) == LOW && bandera == 0) { /*verifica si la barra esta abajo, si el pinSubida esta High y pinBajada Low*/
      if(aux==9){
        pinDisponible=0;
      }
      bandera = 1;  /*Indica que la barra se encuetra arriba*/
      digitalWrite(pinMotor1, HIGH);
      digitalWrite(pinMotor2, LOW);   /*Funcion para subir barra con 1 0 en los pinesMotores*/
      delay(tiempoSubida);   /*Este tiempo es el que durara activo el motor, talvez se necesite ajustar para que alcance a subir la barra*/
    }
    if (digitalRead(pinBajada) == HIGH && digitalRead(pinSubida) == LOW && bandera == 1) { /*verifica si la barra esta arriba, si el pinBajada esta High y pinSubida Low*/
      bandera = 0;    /*Indica que la barra se encuentra abajo*/
      digitalWrite(pinMotor2, HIGH);
      digitalWrite(pinMotor1, LOW);   /*Funcion para bajar barra con 0 1 en los pinesMotores*/
      delay(tiempoBajada);     /*Este tiempo es el que durara activo el motor, talvez se necesite ajustar para que alcance a subir la barra*/
    }
  }
  if (digitalRead(pinSubida1) == HIGH && digitalRead(pinBajada1) == LOW && bandera1 == 0) { /*verifica si la barra esta abajo, si el pinSubida esta High y pinBajada Low*/
    bandera1 = 1;  /*Indica que la barra se encuetra arriba*/
    digitalWrite(pinMotor3, HIGH);
    digitalWrite(pinMotor4, LOW);   /*Funcion para subir barra con 1 0 en los pinesMotores*/
    delay(tiempoSubida2);   /*Este tiempo es el que durara activo el motor, talvez se necesite ajustar para que alcance a subir la barra*/


  }
  if (digitalRead(pinBajada1) == HIGH && digitalRead(pinSubida1) == LOW && bandera1 == 1) { /*verifica si la barra esta arriba, si el pinBajada esta High y pinSubida Low*/
    pinDisponible=1; //nuevo
    bandera1 = 0;    /*Indica que la barra se encuentra abajo*/
    digitalWrite(pinMotor4, HIGH);
    digitalWrite(pinMotor3, LOW);   /*Funcion para bajar barra con 0 1 en los pinesMotores*/
    delay(tiempoBajada2);     /*Este tiempo es el que durara activo el motor, talvez se necesite ajustar para que alcance a subir la barra*/
  }
  digitalWrite(pinMotor3, LOW);
  digitalWrite(pinMotor4, LOW);  /*Funcion para que el motor no gire 0 0 en los pinesMotores*/
  digitalWrite(pinMotor1, LOW);
  digitalWrite(pinMotor2, LOW);  /*Funcion para que el motor no gire 0 0 en los pinesMotores*/
  aux=0;
  lcd.clear();
}

