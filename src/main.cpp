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
#define pwmChannel 5  // 16 canales 0-15
#define freqPWM 5000  // Frecuencia en Hz
#define resolution 8  // 1-16 bits de resolución 

#define pinPWM 2      // GPIO 2 para tener la salida del PWM
//****************************************************************
// Prototipos de funciones
//****************************************************************
void configurarPWM(void);


//****************************************************************
// Variables Globales
//****************************************************************




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
}
//****************************************************************
// Loop Principal
//****************************************************************
void loop() {
  for(int dutycycle = 0; dutycycle < 256; dutycycle++ ){
    ledcWrite(pwmChannel, dutycycle);
    delay(10);
  }
  for(int dutycycle = 255; dutycycle > 0; dutycycle-- ){
    ledcWrite(pwmChannel, dutycycle);
    delay(10);
  }
}
//****************************************************************
// Función para configurar módulo PWM
//****************************************************************
void configurarPWM(void){

  // Paso 1: Configurar el módulo PWM
  ledcSetup(pwmChannel, freqPWM, resolution);

  // Paso 2: seleccionar en que GPIO tendremos nuestra señal PWM
  ledcAttachPin(pinPWM, pwmChannel);

}