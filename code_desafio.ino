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
int unsigned long debounceDelay = 50; 

bool verificarcuadrada(float arreglo[],int cont){
  //recibe como argumentos un arreglo de cont posiciones, retorna true si el arreglo solo contiene dos valores diferentes, de lo contrario retorna false
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
bool verificartriangular(float arreglo[], int cont,float tiempoentredato){
  //recibe como argumentos un arreglo de cont posiciones,y un float, retorna true si el arreglo tiene comportamiento similar al de una funcion triangular, de lo contrario retorna false
    float tiempoentredatos=tiempoentredato;
  	float pendiente1;
  	bool bandera;
 	for (int i = 0; i < cont-1; i++) {
      if (arreglo[i+1]>0){
        if (arreglo[i]>0){
          if (arreglo[i+1]>arreglo[i]){          
          	pendiente1=(arreglo[i+1]-arreglo[i])/tiempoentredato;
         	 break;
          }
        }
      }
    }
    for (int i = 1; i < cont-1; i++) {
      	if (arreglo[i]==arreglo[i+1]){
          return false;
        }
     	if(pendiente1<0){
          pendiente1=pendiente1*(-1);
        }
      	if (arreglo[i+1]>0){
              if(arreglo[i]>0){
                bandera=true;   
              }
              else{
                bandera=false;
              }
        }
        else{
          	if(arreglo[i]<0){
                bandera=true;
            }
            else{
                bandera=false;
            } 
       	}
        if(pendiente1>0){
          	if (bandera){
              if(arreglo[i+1]>arreglo[i]){
                if(!(((arreglo[i+1]-arreglo[i])/ tiempoentredatos)<=(pendiente1*1.2) && ((arreglo[i+1]-arreglo[i])/ tiempoentredatos)>=-1*(pendiente1*1.2))){
                    return false;
                }
              }
            }
        }
    }
    return true;
}
  
bool verificarsenoidal(float arreglo[], int cont,float tiempoentredato){
  //recibe como argumentos un arreglo de cont posiciones, y un float, retorna true si el arreglo tiene comportamiento similar al de una funcion senoidal, de lo contrario retorna false
	float suavidad;
  	int conttrue=0;
  	int contfalse=0;
  	float pendiente,pendientet;
  	float contptrue=0;
  	float contpfalse=0;
  	bool bandera=true;
  	for (int i = 1; i < cont-1; i++){
      	pendiente=(arreglo[i]-arreglo[i-1])/0.1;
        pendientet=(arreglo[i+1]-arreglo[i])/0.1;
      	if (pendiente<0){
          pendiente=pendiente*(-1);
        }
      	if (pendiente>0){
          if(pendientet>0){
            if (pendientet>=pendiente*0.9 && pendientet<=pendiente*1.1){
              contpfalse++;
            }
            else{
              contptrue++;
            }
          }
          else{
            pendientet=pendientet*(-1);
            if (pendientet>=pendiente*0.9 && pendientet<=pendiente*1.1){
              contpfalse++;
            }
            else{
              contptrue++;
            }
          }  
        }     	
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
      	if (suavidad<0){
          suavidad=suavidad*(-1);
        }
     	if (!bandera){
      		if ((arreglo[i]>arreglo[i-1])&& (arreglo[i+1]>arreglo[i])){
        		if(((arreglo[i+1]-arreglo[i])<=(suavidad*1.3) && ((arreglo[i+1]-arreglo[i])>=(-1*(suavidad*1.3))))){
          			conttrue++;
                }
              	else{
                  contfalse++;
                }
                
            }
       	}     
    }
  	if (conttrue>contfalse){
      if (contptrue>contpfalse){
      	return true;
      }
    }
  	else{
      return false;
    }
    
}

int tiposenal(float arreglo[], int cont,float tiempoentredato){
  //recibe como argumentos un arreglo de cont unidades, y tiempo entre dato es un float, retorna un valor entre 1 y 5
  bool cuadrada=false;
  bool triangular=false;
  bool senoidal=false;
  bool desconocida=true;
  if (cont>6);
  	cuadrada=verificarcuadrada(arreglo,cont);
    triangular=verificartriangular(arreglo,cont,tiempoentredato);
    senoidal=verificarsenoidal(arreglo,cont,tiempoentredato);
  if (cuadrada){
    return 1;
  }
  else if(triangular){
    if(senoidal){
      return 5;
    }
    return 2;
  }   
  else if(senoidal){
    return 3;
  }
  else if(desconocida){
    return 4;
  }
}
 
float frecuencia_c(float arreglo[],int cont,float tiempoentredato){
  //recibe como argumento un arreglo de cont unidades, retorna un float cercano a la frecuencia de una funcion cuadrada
  float frecuencia;
  bool cambio=false;
  int p=0;
  int primervalor=arreglo[0];
  int valor;
  int valorcambio;
  for (int i = 1; i < cont; i++){
    valor=arreglo[i];
    valorcambio=arreglo[i+1];
    if((valor!=primervalor)&& cambio==false){
      p++;
      if(valorcambio==primervalor){
       	cambio=true;
        p--;
      }
    }
    if (cambio){
      p++;
      if (valorcambio!=primervalor){
        frecuencia=1/(tiempoentredato*p);
        return frecuencia;
      }
    }
  }
}

float frecuencia_st(float arreglo[],int cont,float tiempoentredato){
  //recibe como argumento un arreglo de cont unidades, retorna un float cercano a la frecuencia si se tienen los suficientes datos
  float frecuencia;
  int c=1;
  int pos;
  int max=arreglo[0];
  int min=arreglo[0];
  for (int i = 1; i < cont-1; i++){
    if (arreglo[i]>=max){
      max=arreglo[i];
    }
    if (arreglo[i]<=min){
      min=arreglo[i];
    }
  }
  for (int i = 0; i < cont-1; i++){
    if (arreglo[i]>=max){
      pos=i;
      break;
    }
  }
  for (int j = pos+1; j < cont-1-pos; j++){
    c++;
    if (min>=0){   
        if (arreglo[j]<=min*1.1){
          frecuencia=1/((c*tiempoentredato)*2);
          return frecuencia;
        }
    }
    if (min<0){
      if (arreglo[j]<=min*0.9){
        frecuencia=1/((c*tiempoentredato)*2);
      	return frecuencia;
      }
    }
  }
}

float amplitud(float arreglo[],int cont){
  //recibe como argumento un arreglo de cont unidades, retorna un float cercano a la amplitud en voltaje
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
  float tiempoentredato;
  bool estadoInicio = digitalRead(pinInicio);
  bool estadoFin = digitalRead(pinFin);
  int *tiposenalvar=new int;
  float tiempoinicial;
  float tiempofinal;
  float tiempo;
  
  if (ultimoEstadoInicio == HIGH && estadoInicio == LOW) {
    delay(debounceDelay);
    if (digitalRead(pinInicio) == LOW) {
      recolectandoDatos = true;
      tiempoinicial=millis();
      lcd.clear();
    }
  }

  if (ultimoEstadoFin == HIGH && estadoFin == LOW) {
    delay(debounceDelay);
    if (digitalRead(pinFin) == LOW) { 
      recolectandoDatos = false;
      tiempofinal=millis();
      tiempo=(tiempofinal-tiempoinicial)/1000;
      lcd.clear();
    }
  }
  if (recolectandoDatos) {
    float lecturaSenal = analogRead(pinSenal);
    //lcd.setCursor(0, 1);
    //lcd.print("Senal: ");
    //lcd.print(lecturaSenal);
    arreglo[cont]=lecturaSenal;
    cont++;

    //Serial.print("Lectura de senal: ");
    bandera=true;
  }
  else{
    if (bandera){
      Serial.println(tiempo);
      tiempoentredato=tiempo/cont;
      float amplitudf;
      amplitudf=amplitud(arreglo,cont);
      lcd.print("A:");
      lcd.print(amplitudf);
      lcd.print("V");
      lcd.setCursor(9, 0);
      lcd.print("T.S:");
      *tiposenalvar=tiposenal(arreglo,cont,tiempoentredato);    
      if (*tiposenalvar==1){
        lcd.print("C");
        lcd.setCursor(5, 1);
        lcd.print("F:");
        lcd.print(frecuencia_c(arreglo,cont,tiempoentredato));
        lcd.print("H");
      }
      if (*tiposenalvar==2){
        lcd.print("T");
        lcd.setCursor(5, 1);
        lcd.print("F:");
       	lcd.print(frecuencia_st(arreglo,cont,tiempoentredato));
        lcd.print("H");
      }
      if (*tiposenalvar==3){
        lcd.print("S");
        lcd.setCursor(5, 1);
        lcd.print("F:");
       lcd.print(frecuencia_st(arreglo,cont,tiempoentredato));
        lcd.print("H");
      }
      if (*tiposenalvar==4){
        lcd.print("DES");
        lcd.setCursor(5, 1);
        lcd.print("F:DES");
      }
      if (*tiposenalvar==5){
        lcd.print("T_S");
        lcd.setCursor(5, 1);
        lcd.print("F:");
        lcd.print(frecuencia_st(arreglo,cont,tiempoentredato));
        lcd.print("H");
      }
    }
    delete[]arreglo;
    delete tiposenalvar;
	cont=0;
    bandera=false;
    
  }
  ultimoEstadoInicio = estadoInicio;
  ultimoEstadoFin = estadoFin;
  
  delay(30);
}
