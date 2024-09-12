#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int pinInicio = 7;
int pinFin = 8;
int pinSenal = A0;
int cont=0;
float *arreglo=new float[cont];
bool bandera=false;
bool recolectandoDatos = false;
bool ultimoEstadoInicio = HIGH;
bool ultimoEstadoFin = HIGH;
unsigned long tiempoInicio = 0;
unsigned long tiempoFin = 0;
int unsigned long debounceDelay = 50; 


float frecuencia(float arreglo[],int cont, float tiempo){
  float mayor1=arreglo[0];
  float mayor2=arreglo[0];
  float menor1=arreglo[0];
  float menor2=arreglo[0];
  if (arreglo[0]<arreglo[1]{
    
  for(int i=0;i<cont-1;i++){
    
      
      
    }
    else if{arreglo[i]>arreglo[i+1])
    }
    else{
    }
  
}

float amplitud(float arreglo[],int cont){
  float mayor=arreglo[0];
  float menor=arreglo[0];
  float amplitud;
  for(int i=0;i<cont-1;i++){
    if (menor>=arreglo[i+1]){
    	menor=arreglo[i+1];
    }
    if (mayor<=arreglo[i+1]){
     	mayor=arreglo[i+1];
    }
  }
  amplitud=(mayor-menor)/2;
  return amplitud;
}
  

void setup() {
  lcd.begin(16, 2);
  pinMode(pinInicio, INPUT);
  pinMode(pinFin, INPUT); 
  Serial.begin(9600);
}

void loop() {
  bool estadoInicio = digitalRead(pinInicio);
  bool estadoFin = digitalRead(pinFin);
  
  unsigned long tiempoActual = millis();
  
  if (ultimoEstadoInicio == HIGH && estadoInicio == LOW) {
    delay(debounceDelay);
    if (digitalRead(pinInicio) == LOW) {
      recolectandoDatos = true;
      tiempoInicio = tiempoActual;
      lcd.clear();
    }
  }

  if (ultimoEstadoFin == HIGH && estadoFin == LOW) {
    delay(debounceDelay);
    if (digitalRead(pinFin) == LOW) { 
      recolectandoDatos = false;
      tiempoFin = tiempoActual;
      lcd.clear();
      float tiempo=(tiempoFin - tiempoInicio) / 1000.0;
      Serial.print("Tiempo de recoleccion: ");
      Serial.print(tiempo);
      Serial.println(" segundos");
    }
  }
  if (recolectandoDatos) {
    float lecturaSenal = analogRead(pinSenal);
    lcd.setCursor(0, 1);
    lcd.print("Senal: ");
    lcd.print(lecturaSenal);
    arreglo[cont]=lecturaSenal/100;
    cont++;

    Serial.print("Lectura de senal: ");
    Serial.println(lecturaSenal);
    bandera=true;
  }
  else 
  {
    if (bandera){
      float *amplitudf= new float;
      *amplitudf=amplitud(arreglo,cont);
      lcd.print("A: ");
      lcd.print(*amplitudf);
      lcd.print(" V");
      delete amplitudf;
      }
    delete[]arreglo;
	cont=0;
    bandera=false;
    
  }
  ultimoEstadoInicio = estadoInicio;
  ultimoEstadoFin = estadoFin;
  
  delay(50);
}
//cambios
