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

bool verificarcuadrada(float arreglo[],int cont){
    if (cont < 2) {
        return false;
    }

    int primerValor = arreglo[0];
    int segundoValor;
    bool encontradoSegundoValor = false;

    for (int i = 1; i < cont-1; i++) {
        if (arreglo[i] != primerValor) {
            if (!encontradoSegundoValor) {
                segundoValor = arreglo[i];
                encontradoSegundoValor = true;
            } else if (arreglo[i] != segundoValor) {
                return false;
            }
        }
    }
    return true;
}
bool verificartriangular(float arreglo[], int cont){
    float tiempoentredatos=0.1;
    float pendiente1=(arreglo[1]-arreglo[0])/tiempoentredatos;
    float pendiente2;
    bool encontradoSegundoValor = false;
    bool bandera;
    bool bandera2=true;
    for (int i = 1; i < cont-1; i++) {
      	if (arreglo[i]==arreglo[i+1]){
          return false;
        }
        if(pendiente1>0){
            if (((arreglo[i+1]-arreglo[i])/ tiempoentredatos)>0){
                if(((arreglo[i+1]-arreglo[i])/ tiempoentredatos)<=(pendiente1*1.5) && ((arreglo[i+1]-arreglo[i])/ tiempoentredatos)-pendiente1>=(-1*(pendiente1*1.5))){
                    bandera=true;
                }
                else{
                    return false;
                }
            }
            else{
                bandera=false;
            }
        }
        else{
            if (((arreglo[i+1]-arreglo[i])/ tiempoentredatos)<0){
                if(((arreglo[i+1]-arreglo[i])/ tiempoentredatos)>=(pendiente1*1.5) && ((arreglo[i+1]-arreglo[i])/ tiempoentredatos)<=(-1*(pendiente1*1.5))){
                    bandera=true;
                }
                else{
                    return false;
                }
            }
            else{
                bandera=false;
            }
        }      
        if (!bandera){
            if (!encontradoSegundoValor) {
                pendiente2 = (arreglo[i+1]-arreglo[i])/tiempoentredatos;
                encontradoSegundoValor = true;
            } 
            else{
                if(pendiente2>0){
                    if ((arreglo[i+1]-arreglo[i])/ tiempoentredatos>0){
                        if(((arreglo[i+1]-arreglo[i])/ tiempoentredatos)<=(pendiente2*1.5) && ((arreglo[i+1]-arreglo[i])/ tiempoentredatos)>=(-1*(pendiente2*1.5))){
                            bandera2=true;
                        }
                        else{
                            return false;
                        }
                    }
                    else{
                        bandera2=false;
                    }
                }
                else{
                    if (((arreglo[i+2]-arreglo[i+1])/ tiempoentredatos)<0){
                        if(((arreglo[i+2]-arreglo[i+1])/ tiempoentredatos)>=(pendiente2*1.5) && ((arreglo[i+2]-arreglo[i+1])/ tiempoentredatos)<=(-1*(pendiente2*1.5))){
                            bandera2=true;
                        }
                        else{
                            return false;
                        }
                    }
                    else{
                        bandera2=false;
                    }
                }
            }
            if (!bandera2) {
                return false;
            }
        }  
    }
    return true;
}
  
bool verificarsenoidal(float arreglo[], int cont){
	float suavidad;
  	bool bandera=true;
  	for (int i = 1; i < cont-1; i++){
  		if (arreglo[i]==arreglo[i+1] || arreglo[i]==arreglo[i-1]){
    		return false;
    	}
    	if ((arreglo[i]>arreglo[i-1])&& bandera){
    		suavidad=arreglo[i]-arreglo[i-1];
          	bandera=false;
   		}
        if((arreglo[i]<arreglo[i-1])&& bandera){
          	suavidad=arreglo[i-1]-arreglo[i];
          	bandera=false;
       	}
        if(!((arreglo[i+1]-arreglo[i])<=(suavidad*1.5) && ((arreglo[i+1]-arreglo[i])>=(-1*(suavidad*1.5))))){
          return false;
       	}     
    }
    return true;
}

int tiposenal(float arreglo[], int cont){
  bool cuadrada=false;
  bool triangular=false;
  bool senoidal=false;
  bool desconocida=true;
  if (cont>6);
  	cuadrada=verificarcuadrada(arreglo,cont);
    triangular=verificartriangular(arreglo,cont);
    senoidal=verificarsenoidal(arreglo,cont);
  if (cuadrada){
    return 1;
  }
  else if(triangular){
    return 2;
  }   
  else if(senoidal){
    return 3;
  }
  else if(desconocida){
    return 4;
  }
}
 
      
        

/*
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
*/
  
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
  return amplitud/100;
}
  

void setup(){
  lcd.begin(16, 2);
  pinMode(pinInicio, INPUT);
  pinMode(pinFin, INPUT); 
  Serial.begin(9600);
}

void loop(){
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
    arreglo[cont]=lecturaSenal;
    cont++;

    Serial.print("Lectura de senal: ");
    Serial.println(lecturaSenal);
    bandera=true;
  }
  else{
    if (bandera){
      float amplitudf;
      int *tiposenalvar=new int;
      amplitudf=amplitud(arreglo,cont);
      lcd.print("A: ");
      lcd.print(amplitudf);
      lcd.print(" V");
      lcd.setCursor(0, 1);
      lcd.print("T.S: ");
      *tiposenalvar=tiposenal(arreglo,cont);    
      if (*tiposenalvar==1){
        lcd.print("C");
      }
      if (*tiposenalvar==2){
        lcd.print("T");
      }
      if (*tiposenalvar==3){
        lcd.print("S");
      }
      if (*tiposenalvar==4){
        lcd.print("DES");
      }
    }
    delete[]arreglo;
	cont=0;
    bandera=false;
    
  }
  ultimoEstadoInicio = estadoInicio;
  ultimoEstadoFin = estadoFin;
  
  delay(100);
}
