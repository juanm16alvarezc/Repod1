#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int pinInicio = 7;
int pinFin = 8;
int pinSenal = A0;

bool recolectandoDatos = false;
bool ultimoEstadoInicio = HIGH;
bool ultimoEstadoFin = HIGH;
unsigned long tiempoInicio = 0;
unsigned long tiempoFin = 0;
int unsigned long debounceDelay = 50; 

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
      Serial.print("Tiempo de recoleccion: ");
      Serial.print((tiempoFin - tiempoInicio) / 1000.0);
      Serial.println(" segundos");
    }
  }

 
  if (recolectandoDatos) {
    int lecturaSenal = analogRead(pinSenal);
    lcd.setCursor(0, 1);
    lcd.print("Senal: ");
    lcd.print(lecturaSenal);


    Serial.print("Lectura de senal: ");
    Serial.println(lecturaSenal);
  }
  ultimoEstadoInicio = estadoInicio;
  ultimoEstadoFin = estadoFin;

  delay(50);
}
