/*Ivanov
 Traffic_Light 
 */
//light for car
int redCar = 5;
int yellowCar = 4;
int greenCar = 0;
//light for pedestrian
int greenPed =12;
int redPed=14;
//pedestrian control
int button =13;
//
int crossTime=5000;
unsigned long changeTime;
int incByte = 0;
const int zero = 48;
const int one = 49;

void setup() {
  // here we are initializing our pins as outputs
  pinMode(redCar, OUTPUT);
  pinMode(yellowCar, OUTPUT);
  pinMode(greenCar, OUTPUT);
  pinMode(redPed, OUTPUT);
  pinMode(greenPed, OUTPUT);
  pinMode(button, INPUT);
  //turn on the green light
  digitalWrite(greenCar, HIGH);
 // digitalWrite(redPed, HIGH);
  digitalWrite(redCar, LOW);
  digitalWrite(yellowCar, LOW);
  digitalWrite(greenPed, LOW);
  changeTime=millis();
  Serial.begin(115200);
}

void loop() {
//this variable will tell us if the button is pressed 
  int state= digitalRead(button);  
/*if the button is pressed and if it has passed 5 seconds since last
   button press, call the function to change the lights*/
   if (Serial.available()>0){
    incByte = Serial.read();
    Serial.print("recived: ");
    Serial.println(incByte,DEC);
    if (incByte == one){
      changeLights();}
     else if (incByte == zero){
      off();}
   }
  
 if (state == HIGH || (millis() - changeTime) > crossTime){ 
  
     }
}

void changeLights() {
  Serial.println("Regulated mode");
  digitalWrite(greenCar, LOW);    // the green LED will turn off
  digitalWrite(yellowCar, HIGH); // the yellow LED will turn on for 2 second
  digitalWrite(redCar, LOW);
  digitalWrite(redPed, HIGH);
  digitalWrite(greenPed, LOW);
  delay(2000); 
  
  digitalWrite(yellowCar, LOW); // the yellow LED will turn off
  digitalWrite(redCar, HIGH); // the red LED will turn on for 5 seconds
  delay(crossTime);
  digitalWrite(redPed, LOW);
  digitalWrite(greenPed, HIGH);
  delay(crossTime);
  
  // flash the ped green
  for (int x=0; x<10; x++) {
    digitalWrite(greenPed, LOW);
    delay(100);
    digitalWrite(greenPed, HIGH);
    delay(100);
  }
  digitalWrite(greenPed, LOW);
  digitalWrite(redCar, LOW);
  digitalWrite(redPed, HIGH);
  digitalWrite(greenCar, HIGH);
  delay(crossTime);
  
  changeTime = millis();
 }
void off(){
  Serial.println("Unregulated mode");
  digitalWrite(greenCar, LOW);
  digitalWrite(redCar, LOW);
  digitalWrite(greenPed, LOW);
  digitalWrite(redPed, LOW);
  digitalWrite(yellowCar, LOW);
  for (int x=0; x<10; x++) {
    digitalWrite(yellowCar, LOW);
    delay(1000);
    digitalWrite(yellowCar, HIGH);
    delay(1000);
  };
}
