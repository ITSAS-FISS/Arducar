/**
More info on what this code does and how to connect the cables on the Readme.md
file which should have been given along this file.

Created by the participants in an ITSAS workshop on 12/3/2014 (DD/MM/YYYY)
The workshop took place in the Facultad de Informatica de San Sebastian (FISS).

This code is in public domain.

Thanks to everyone who made this possible.

More info on ITSAS: http://ehu.es/itsas
More info on FISS: http://www.ehu.es/informatika-fakultatea
*/

#define MOTOR_DERECHO 160
#define MOTOR_IZQUIERDO 200
#define PLUS 50

#define ERR_ANG 3

#define OK 0
#define SALIDO_IZQ 1
#define SALIDO_DER 2

int anguloActual;
int anguloInicial;
int estado;

int E1 = 5;  
int M1 = 4; 
int E2 = 6;                      
int M2 = 7; 

int pinG = 10;
int pinR = 9;
int pinFotoR = A1;
int pinFotoG = A0;

#include <Wire.h>
#include <HMC5883L.h>

HMC5883L compass;

/**
  Inicializa lo necesario para acceder al magnetometro
*/
void initMagnetometer(){
 Wire.begin(); // Start the I2C interface.
  compass = HMC5883L();
  compass.SetScale(1.3); // Set the scale of the compass.
  
  compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous 
}

/**
  Devuelve los grados en los que difiere la posicion actual del magnetometro
  respecto al sur magnetico (de la tierra)
*/
float getHeadingDegrees(){
  MagnetometerRaw raw = compass.ReadRawAxis();
  MagnetometerScaled scaled = compass.ReadScaledAxis();  
  float heading = atan2(scaled.YAxis, scaled.XAxis);  
  float declinationAngle = -0.0193;
  heading += declinationAngle;  
  if(heading < 0)
    heading += 2*PI;    
  if(heading > 2*PI)
    heading -= 2*PI;   
  float headingDegrees = heading * 180/M_PI; 
  return headingDegrees;
}

// the setup routine runs once when you press reset:
void setup() {
  
  delay(1000);
  
  Serial.begin(9600);
  Serial.println("setup");
  
  pinMode( M1, OUTPUT );
  pinMode( M2, OUTPUT );
  pinMode( E2, OUTPUT );
  pinMode( E1, OUTPUT );
  
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  
  initMagnetometer();
  
  anguloInicial = getHeadingDegrees();
  Serial.print("And Inic: ");
  Serial.println(anguloInicial);
  
  analogWrite(E1, MOTOR_DERECHO);
  analogWrite(E2, MOTOR_IZQUIERDO);
}

void leerMagnetometro(){
  anguloActual = getHeadingDegrees();
}

void decidirEstado()
{
  if(anguloActual < (anguloInicial - ERR_ANG)){
    estado = SALIDO_IZQ;
  }
  else
  {
    if(anguloActual > (anguloInicial + ERR_ANG)){
      estado = SALIDO_DER;
    }
    else
    {
      estado = OK;
    }
  }
}

void actuarMotores()
{
  switch(estado){
    case OK:
      //Motores delante
      Serial.println("Motores OK");
      analogWrite(E1, MOTOR_DERECHO);
      analogWrite(E2, MOTOR_IZQUIERDO);
      break;
    
    case SALIDO_IZQ:
      //Motor IZQ plus
      Serial.println("Mas canya IZQ");
      analogWrite(E1, MOTOR_DERECHO*0);
      analogWrite(E2, MOTOR_IZQUIERDO + PLUS);
      break;
      
    case SALIDO_DER:
      //Motor DER plus
      Serial.println("Mas canya DER");
      analogWrite(E1, MOTOR_DERECHO + PLUS);
      analogWrite(E2, MOTOR_IZQUIERDO*0);
      break;
    
  }
}

// the loop routine runs over and over again forever:
void loop() {
  leerMagnetometro();  
  decidirEstado();
  actuarMotores(); 
  delay(100);
}
