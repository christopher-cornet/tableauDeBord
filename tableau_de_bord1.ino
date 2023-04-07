int temp;
float grad;
int LED_rouge = 8;
int LED_bleue = 9;
int LED_verte = 10;
int LED_jaune = 11;
int Venti = 12;
int moisture = 1;
unsigned int light;

int button = 13;

int lastButtonState = 0;
int buttonState = 0;
int start_state = 0;

#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {
  lcd.begin(16, 2);
  pinMode(button, INPUT);
  pinMode(LED_rouge, OUTPUT); // met la broche numérique en sortie
  pinMode(LED_bleue, OUTPUT); // met la broche numérique en sortie
  pinMode(LED_verte, OUTPUT); // met la broche numérique en sortie
  pinMode(LED_jaune, OUTPUT); // met la broche numérique en sortie
  pinMode(Venti, OUTPUT); // met la broche numérique en sortie
  pinMode(A1, INPUT);
  pinMode(A0, OUTPUT);
  pinMode(A2, INPUT);
  pinMode(A5, INPUT);
  Serial.begin(9600);  // ouvre le port série
  
}

void loop() {
  
  // read the pushbutton input pin
  buttonState = digitalRead(button);
  if (buttonState != lastButtonState) {
    // if the state has changed
    if (buttonState == HIGH && start_state == 0) {
      
      start_state = 1;
      Serial.println("button clicked");
      Serial.println(start_state);
    } else if (buttonState == HIGH && start_state == 1) {
      
      start_state = 0;
      Serial.println("button clicked");
      Serial.println(start_state);
    }
    // delay a little bit to avoid debouncing
    delay(1); // Wait for 5 millisecond(s)
  }
  
  light = analogRead(A5);
  Serial.println("Luminosite: ");
  Serial.println(light);
  
  temp = analogRead(A1); // récupération de la température
  float voltage= (temp* 5.0)/1024;
 
  float tempC = (voltage-0.5)* 100;
  // Apply power to the soil moisture sensor
  digitalWrite(A0, HIGH);
  delay(10); // Wait for 10 millisecond(s)
  moisture = analogRead(A2); // récupération de l'humidité
  // Turn off the sensor to reduce metal corrosion
  // over time
  digitalWrite(A0, LOW);
  //grad = (temp/1023.0)*5.0*1000/10;
  //Serial.println(grad);
  //Serial.println(temp);
  //Serial.println(moisture);
  
  if (start_state == 1) {
  	if (temp < 149) { digitalWrite(Venti, LOW);}
  	if (temp > 123 && temp < 139) { digitalWrite(LED_bleue, HIGH); digitalWrite(LED_rouge, LOW); digitalWrite(Venti, LOW);}
  	else if (temp > 139 && temp < 149) { digitalWrite(LED_rouge, HIGH); digitalWrite(LED_bleue, LOW); digitalWrite(Venti, LOW); }
  	else if (temp > 149) { digitalWrite(LED_rouge, HIGH); digitalWrite(Venti, HIGH); }
  	else { digitalWrite(LED_rouge, LOW); digitalWrite(LED_bleue, LOW); }
  	if (moisture < 610) { digitalWrite(LED_verte, HIGH); digitalWrite(LED_jaune, LOW); }
  	else if (moisture > 610) { digitalWrite(LED_jaune, HIGH); digitalWrite(LED_verte, LOW);}
  }
  else if (start_state == 0) { digitalWrite(LED_bleue, LOW); digitalWrite(LED_rouge, LOW); digitalWrite(LED_verte, LOW); digitalWrite(LED_jaune, LOW);digitalWrite(Venti, LOW);}
  
  
  lcd.setCursor(0,0);
  lcd.print("Temperature :");
  lcd.setCursor(0,1);
  lcd.print(tempC);
  lcd.setCursor(7,1);
  lcd.print("C");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Luminosite: ");
  lcd.setCursor(0,1);
  lcd.print(light);
  delay(3000);
  lcd.clear();
  //lcd.setCursor(7,1);
  //lcd.print("C");

  //lcd.setCursor(0,0);
  delay(1000); // attend une seconde
}