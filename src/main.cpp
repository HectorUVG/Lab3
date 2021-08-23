//Universidad del Valle de Guatemala
//Hector Manuel de León Salguero
//Digital 2
//Clase
//Laboratorio 3 PWM
//

//****************************************************************
// Librerías
//****************************************************************
#include <Arduino.h>
//****************************************************************
// Definición de etiquetas
//****************************************************************
// Paso 1: selección de parámetros de la señal PWM
#define pwmChannel 0 // 16 canales 0-15
#define pwmChannel2 2
#define pwmChannel3 1
#define freqPWM 5000  // Frecuencia en Hz
#define resolution 8  // 1-16 bits de resolución 
#define LedR 23        // GPIOs para tener la salida del PWM
#define LedG 22
#define LedB 21    

#define B1  12
#define B2  14
#define B3  27
#define B4  26
//****************************************************************
// Prototipos de funciones
//****************************************************************
void configurarPWM(void);
void boton3(void);
void escogerLed(void);
//void ejemplo(void);


//****************************************************************
// Variables Globales
//****************************************************************
int contadorLeds = 0;
int intensidad = 0;
int presionado = 0;//antirrebote1, tengo que ver la clase donde Pablo lo hace de otra forma jeje
int presionado2 = 0;//antirrebote 2
int contB4 = 0;


//****************************************************************
// ISR: Interrupciones
//****************************************************************
//void IRAM_ATTR ISR(){
//
//}


//****************************************************************
// Configuración
//****************************************************************
void setup() {
  configurarPWM();

  //pinMode(LedR, OUTPUT);//esto no es necesario al parecer
  //pinMode(LedG, OUTPUT);
  //pinMode(LedB, OUTPUT);

  //digitalWrite(LedR, 0);
  //digitalWrite(LedG, 0);
  //digitalWrite(LedB, 0);

  //Boton 1
  pinMode(B1, INPUT_PULLUP);
  //Boton 2
  pinMode(B2, INPUT_PULLUP);
  //Boton 3
  pinMode(B3, INPUT_PULLUP);
  //Boton 4
  pinMode(B4, INPUT_PULLUP);
}
//****************************************************************
// Loop Principal
//****************************************************************
void loop() {
  configurarPWM();
  boton3();
  escogerLed();
 // ejemplo();
}
//****************************************************************
// Función para configurar módulo PWM
//****************************************************************
void configurarPWM(void){

  // Paso 1: Configurar el módulo PWM
  ledcSetup(pwmChannel, freqPWM, resolution);
  ledcSetup(pwmChannel2, freqPWM, resolution);
  ledcSetup(pwmChannel3, freqPWM, resolution);

  // Paso 2: seleccionar en que GPIO tendremos nuestra señal PWM
  ledcAttachPin(LedB, pwmChannel3);//le asigne un canal diferente a cada led para poder variar la intensidad
  ledcAttachPin(LedG, pwmChannel2);
  ledcAttachPin(LedR, pwmChannel);

}

//****************************************************************
// Función para escoger led
//****************************************************************

/*El primer if suma 1 al contador cada vez que se presiona el 
boton 3. El segundo if evita que el contador escoja una 
opcion mayor a las unicas que existen */
void boton3(){

  if (digitalRead(B3)==0){
    presionado = 1;
  }
  if (digitalRead(B3) == 1 && presionado == 1){
    contadorLeds = contadorLeds + 1;
    presionado = 0;
    delay(150);
  }

  if (contadorLeds == 3 ){
    contadorLeds = 0 ;
  }
  
}

//****************************************************************
// Función para cambiar brillo
//****************************************************************


/**
 * aqui imprlemento al boton 4, que deberia cambiar la intensidad del led dependiendo 
 * de que led este activo. segun yo, el contador deberia escoger un led diferente cada vez que 
 * presiono el boton 3, pero eso no me funciona por alguna razon. 
 * 
 * 
 */
void escogerLed(){
  if (contadorLeds == 0){
    //varia la intensidad del led rojo cuando el contador lo selecciona
    int a = 0;
    if (digitalRead(B4)==0){
      presionado2 = 1;
    }
    if (digitalRead(B4) == 1 && presionado2 == 1){
      a = a + 51;
      presionado = 0;
      delay(150);
    }

    if (a > 255){
      a = 0;
    }

    ledcWrite(pwmChannel, a);


  }
  if(contadorLeds == 1){
    //varia la intensidad del led verde cuando el contador lo selecciona
    int a = 0;
    if (digitalRead(B4)==0){
      presionado2 = 1;
    }
    if (digitalRead(B4) == 1 && presionado2 == 1){
      a = a + 51;
      presionado = 0;
      delay(150);
    }

    if (a > 255){
      a = 0;
    }

    ledcWrite(pwmChannel2, a);

  }

  if(contadorLeds == 2){
    //varia la intensidad del led azul cuando el contador lo selecciona
    int a = 0;
    if (digitalRead(B4)==0){
      presionado2 = 1;
    }
    if (digitalRead(B4) == 1 && presionado2 == 1){
      a = a + 51;
      presionado = 0;
      delay(150);
    }

    if (a > 255){
      a = 0;
    }

    ledcWrite(pwmChannel3, a);



  }
}

//****************************************************************
// prueba ejemplo de clase
//****************************************************************
/*
void ejemplo(){
  for(int dutycycle = 0; dutycycle < 256; dutycycle++ ){
    ledcWrite(pwmChannel, dutycycle);
    delay(10);
  }
  for(int dutycycle = 255; dutycycle > 0; dutycycle-- ){
    ledcWrite(pwmChannel, dutycycle);
    delay(10);
  }
}*/
