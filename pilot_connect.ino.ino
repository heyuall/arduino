#include <SoftwareSerial.h>
#include <PS2X_lib.h>  //for v1.6
#include <Servo.h> //servomoteur

PS2X ps2x; // create PS2 Controller Class
// ps2_manette
int error = 0; 
byte type = 0;
byte vibrate = 0;
// capteur 
const int capteurGauche = 4;
const int capteurCentre = 3;
const int capteurDroit = 2;
// moteur_gauche
int en_g = 6;  //PWM
int in_1 = A0;
int in_2 = A1;
// moteur_Droite 
int en_d = 5; //PWM
int in_3 = A2;
int in_4 =A3;
// les led
int led_suiveur = A5 ;
int led_on = A4 ;
// test_capteur
bool etatCapteurGauche;
bool etatCapteurCentre;
bool etatCapteurDroit;

bool test_capteur = false;  // test pour activer les capteur 
bool stoppp = false; // marche_arret
// servomoteur
Servo myservo;
int servo =12 ; // degree de servo
bool etatservo =true ;// etat de servo
void setup(){
Serial.begin(9600);
// capteur 
 pinMode(capteurGauche, INPUT);
 pinMode(capteurCentre, INPUT);
 pinMode(capteurDroit, INPUT);
 // moteur
 pinMode(en_g,OUTPUT); //PWM 
 pinMode(en_d,OUTPUT); //PWM 
 pinMode(in_1,OUTPUT);
 pinMode(in_2,OUTPUT);
 pinMode(in_3,OUTPUT);
 pinMode(in_4,OUTPUT);
 // les led
 pinMode(led_suiveur,OUTPUT);
 pinMode(led_on,OUTPUT);
 //servomoteur
myservo.attach(9);


 //CHANGES for v1.6 HERE!!! *************PAY ATTENTION************
  
 error = ps2x.config_gamepad(13,11,10,12, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 
 if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
  Serial.println("holding L1 or R1 will print out the analog stick values.");
  Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   //Serial.print(ps2x.Analog(1), HEX);
   
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");
       break;
     }
  
}

void avance() {
  digitalWrite(in_1,HIGH);
  digitalWrite(in_2,LOW);
  analogWrite(en_g,130); 
  digitalWrite(in_3,HIGH);
  digitalWrite(in_4,LOW);
  analogWrite(en_d,130);  
  Serial.write("0");
}
void avance_high() {
  digitalWrite(in_1,HIGH);
  digitalWrite(in_2,LOW);
  analogWrite(en_g,255); 
  digitalWrite(in_3,HIGH);
  digitalWrite(in_4,LOW);
  analogWrite(en_d,255);
  Serial.write("1");   
}
void virageGauche() { 
  digitalWrite(in_1,HIGH);
  digitalWrite(in_2,LOW);
  analogWrite(en_g,0); 
  digitalWrite(in_3,HIGH);
  digitalWrite(in_4,LOW);
  analogWrite(en_d,200);  
Serial.write("2");
}

void virageDroite() { 
 digitalWrite(in_1,HIGH);
  digitalWrite(in_2,LOW);
  analogWrite(en_g,200); 
  digitalWrite(in_3,HIGH);
  digitalWrite(in_4,LOW);
  analogWrite(en_d,0); 
  Serial.write("3");  
}

void AngleGauche() { 
  digitalWrite(in_1,LOW);
  digitalWrite(in_2,HIGH);
  analogWrite(en_g,250); 
  digitalWrite(in_3,HIGH);
  digitalWrite(in_4,LOW);
  analogWrite(en_d,150); 
  Serial.write("4");    
}
void AngleDroite() { 
  digitalWrite(in_1,HIGH);
  digitalWrite(in_2,LOW);
  analogWrite(en_g,150); 
  digitalWrite(in_3,LOW);
  digitalWrite(in_4,HIGH);
  analogWrite(en_d,250);  
  Serial.write("5"); 
}
void Recule() {
  digitalWrite(in_1,LOW);
  digitalWrite(in_2,HIGH);
  analogWrite(en_g,100); 
  digitalWrite(in_3,LOW);
  digitalWrite(in_4,HIGH);
  analogWrite(en_d,100); 
  Serial.write("6");
  delay(100);  
}
void stopp() {
  digitalWrite(in_1,LOW);
  digitalWrite(in_2,HIGH);
  analogWrite(en_g,0); 
  digitalWrite(in_3,LOW);
  digitalWrite(in_4,HIGH);
  analogWrite(en_d,0); 
  Serial.write("7");  
}

void loop(){ 

   
 if(error == 1) //skip loop if no controller found
  return; 
  
 if(type == 2){ //Guitar Hero Controller
   
   ps2x.read_gamepad();          //read controller 
   
   if(ps2x.ButtonPressed(GREEN_FRET))
     Serial.println("Green Fret Pressed");
   if(ps2x.ButtonPressed(RED_FRET))
     Serial.println("Red Fret Pressed");
   if(ps2x.ButtonPressed(YELLOW_FRET))
     Serial.println("Yellow Fret Pressed");
   if(ps2x.ButtonPressed(BLUE_FRET))
     Serial.println("Blue Fret Pressed");
   if(ps2x.ButtonPressed(ORANGE_FRET))
     Serial.println("Orange Fret Pressed");
     

    if(ps2x.ButtonPressed(STAR_POWER))
     Serial.println("Star Power Command");
    
    if(ps2x.Button(UP_STRUM))          //will be TRUE as long as button is pressed
     Serial.println("Up Strum");
    if(ps2x.Button(DOWN_STRUM))
     Serial.println("DOWN Strum");
  
 
    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
         Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
         Serial.println("Select is being held");

    
    if(ps2x.Button(ORANGE_FRET)) // print stick value IF TRUE
    {
        Serial.print("Wammy Bar Position:");
        Serial.println(ps2x.Analog(WHAMMY_BAR), DEC); 
    } 
 }

 else { //DualShock Controller
  
    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
    
   /* if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
         Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
         Serial.println("Select is being held");
         
         
     if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
       Serial.print("Up held this hard: ");
       Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
      }
      if(ps2x.Button(PSB_PAD_RIGHT)){
       Serial.print("Right held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
      }
      if(ps2x.Button(PSB_PAD_LEFT)){
       Serial.print("LEFT held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
      }
      if(ps2x.Button(PSB_PAD_DOWN)){
       Serial.print("DOWN held this hard: ");
     Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
      }   */
  
    
      vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on 
                                              //how hard you press the blue (X) button    
    
    /*if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
    {
     
       
         
        if(ps2x.Button(PSB_L3))
         Serial.println("L3 pressed");
        if(ps2x.Button(PSB_R3))
         Serial.println("R3 pressed");
        if(ps2x.Button(PSB_L2))
         Serial.println("L2 pressed");
        if(ps2x.Button(PSB_R2))
         Serial.println("R2 pressed");
        if(ps2x.Button(PSB_GREEN))
         Serial.println("Triangle pressed");
         
    }   
         
    
    if(ps2x.ButtonPressed(PSB_RED))             //will be TRUE if button was JUST pressed
         Serial.println("Circle just pressed");
         
    if(ps2x.ButtonReleased(PSB_PINK))             //will be TRUE if button was JUST released
         Serial.println("Square just released");     
    
    if(ps2x.NewButtonState(PSB_BLUE))            //will be TRUE if button was JUST pressed OR released
         Serial.println("X just changed");    
    
    
    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
    {
        Serial.print("Stick Values:");
        Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_LX), DEC); 
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_RY), DEC); 
        Serial.print(",");
        Serial.println(ps2x.Analog(PSS_RX), DEC); 
    } */
    // etat de capteur 
 etatCapteurGauche = !digitalRead(capteurGauche);
 etatCapteurCentre = !digitalRead(capteurCentre);
 etatCapteurDroit = !digitalRead(capteurDroit);

// servo radar
if (servo==170){
  etatservo = false;
     }
else 
   if(servo==10){
    etatservo = true;  
   }
if (etatservo == true ){
  myservo.write(servo);
  servo +=1;
  }
else {
   myservo.write(servo);
  servo -=1;
}

if(ps2x.ButtonPressed(PSB_START)) { // marche_arret*****start******
  if (stoppp == false){
    stoppp = true;
    digitalWrite(led_on,HIGH);
  }
  else{
    stoppp = false;
      digitalWrite(led_on,LOW);
  }
}


if (stoppp==true){   // on_off
  stopp();
  }
  else {

  if(ps2x.ButtonPressed(PSB_SELECT)) { // select button changed
  if (test_capteur == false){
    test_capteur = true;
    digitalWrite(led_suiveur,HIGH);
  }
  else{
    test_capteur = false;
    digitalWrite(led_suiveur,LOW);
  }
}

if (test_capteur){ // test_capteur true -----> suiveur de ligne
  if(etatCapteurCentre) {
    if ((etatCapteurGauche) && (!etatCapteurDroit)) {
      virageGauche();
      }
    else if ((!etatCapteurGauche) && (etatCapteurDroit)) {
      virageDroite();
      }
    else {
      avance();
      }
    }
  else {
    if ((etatCapteurGauche) && (!etatCapteurDroit)) {
      AngleGauche();
      }
    else if ((!etatCapteurGauche) && (etatCapteurDroit)){
      AngleDroite();
      }
    else {
      Recule();
      }
  }  
}
// teleguidée up, down, right, left
else {
  if(ps2x.Button(PSB_PAD_UP)) { 
    if(ps2x.Button(PSB_L1)) {
      avance_high();
    }
    else { avance();}
  }
  else if (ps2x.Button(PSB_PAD_DOWN)){
    Recule(); 
  }
  else if (ps2x.Button(PSB_PAD_LEFT)){
    if(ps2x.Button(PSB_L1)) {
      AngleGauche();
    }
    else {virageGauche();}
  }
  else if (ps2x.Button(PSB_PAD_RIGHT)){
    if(ps2x.Button(PSB_L1)) {
      AngleDroite();
    }
    else {virageDroite();}
  }
} 
// fin


   }
 }

 }
