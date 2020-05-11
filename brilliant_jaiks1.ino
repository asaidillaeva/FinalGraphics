#include<LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// heart sign
byte newChar1[8] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};

// heart sign
byte newChar2[8] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};

// smile sign
byte newChar3[8] = {
  B00000,
  B00000,
  B01010,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};

// smile sign
byte newChar4[8] = {
  B00000,
  B00000,
  B01010,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};

// robot sign
byte newChar5[8] = {
  B11111,
  B10101,
  B11111,
  B11111,
  B01110,
  B01010,
  B11011,
  B00000
};

// robot sign
byte newChar6[8] = {
  B11111,
  B10101,
  B11111,
  B11111,
  B01110,
  B01010,
  B11011,
  B00000
};

// music sign
byte newChar7[8] = {
  B00001,
  B00011,
  B00101,
  B01001,
  B01001,
  B01011,
  B11011,
  B11000
};

// music sign
byte newChar8[8] = {
  B00001,
  B00011,
  B00101,
  B01001,
  B01001,
  B01011,
  B11011,
  B11000
};            //Total 8 Character is used for display

int prevR = 0, prevG = 0, prevB = 0; // all of the previous RGB values
int const Red = 16; //pin A2
int const Blue = 17; // pin A3
int const Green = 18; // pin A4

int i = 0;

int LED = 15;
int LDR = A0;
char var;
int sp = 13;
int speeden = 10;
int length = 26;
char notes[] = "eeeeeeegcdefffgfeeeeddedg";
int beats[] = { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2 };
int tempo = 250;


void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 's', 'g', 'a', 'v', 'b', 'C', 'D', 'E' };
  int tones[] = { 1915, 1700, 1519, 1432, 1352, 1275, 1136, 1073, 1014, 956, 852, 758 };

  // play the tone corresponding to the note name
  for (int j = 0; j < 8; j++) {
    if (names[j] == note) {
      playTone(tones[j], duration);              //calling the playTone Function
    }
  }
}
void playTone(int tone, int duration) {
  for (long j = 0; j < duration * 1000L; j += tone * 2) {
    digitalWrite(sp, HIGH);

    delayMicroseconds(tone);
    digitalWrite(sp, LOW);
    delayMicroseconds(tone);
  }
}

void setup() {
  Serial.begin(9600);
  lcd.createChar(0, newChar1);            //set the character starting with 0 to 8
  lcd.createChar(1, newChar2);
  lcd.createChar(2, newChar3);
  lcd.createChar(3, newChar4);
  lcd.createChar(4, newChar5);
  lcd.createChar(5, newChar6);
  lcd.createChar(6, newChar7);
  lcd.createChar(7, newChar8);            //set the character starting with 7 to 8
  lcd.begin(16, 2);
  for (int n = 0; n < 16; n++)           //starting a loop for character to print
  {
    lcd.setCursor(n * 2, 0);
    lcd.write(n);
  }
  lcd.setCursor(0, 1);
  lcd.print("Hello I am FAAAT");
  delay(4000);
  lcd.clear();
  for (int n = 0; n < 16; n++)
  {
    lcd.setCursor(n * 2, 0);
    lcd.write(n);
  }
  lcd.setCursor(0, 1);
  lcd.print("I am a ROBOT of FAAAT TEAM");
  delay(4000);                                   //print the messages for 4 second's
  lcd.clear();
  for (int n = 0; n < 16; n++)
  {
    lcd.setCursor(n * 2, 0);
    lcd.write(n);
  }
  lcd.setCursor(0, 1);
  lcd.print("Pls! Connect Me");
  tone(sp, 120.380, 500);             //some voice's for starting
  tone(sp, 124.240, 500);
  tone(sp, 200.410, 500);
  tone(sp, 222.400, 500);
  pinMode(sp, OUTPUT);               //sp declare for Speaker Output
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(Red, OUTPUT);
  pinMode(Blue, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(LDR, INPUT);
}
void loop()
{
  var = Serial.read();              //var directly read's serial data

  if (var == 'F')                     //if the value 'F' Means Forward Program Run
  {
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    tone(sp, 268, 500);
    tone(sp, 111, 500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Going to Forward");
    lcd.setCursor(0, 1);
    lcd.print("+++++Wohhooo+++++");
  }
  if (var == 'B')                    //if the value 'B' Means Backward Program Run
  {
    analogWrite(speeden, 150);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    tone(sp, 225, 500);
    tone(sp, 185, 500);
    tone(sp, 420, 500);
    tone(sp, 311, 500);

    lcd.clear();
    lcd.print(0, 0);
    lcd.print("Going to Back");
    lcd.setCursor(0, 1);
    lcd.print("-----BimBom-----");
  }
  if (var == 'X')                   //Robot Totally stop when you send 'X' value
  {
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
    tone(sp, 345, 500);
    tone(sp, 548, 500);

    lcd.clear();                             //Clear the display and print again
    lcd.setCursor(0, 0);
    lcd.print("Feeling Relax");
    lcd.setCursor(0, 1);
    lcd.print("Thank You");
  }
  if (var == 'L')                          //if the value 'L' Means Left Program Run
  {
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    tone(sp, 608, 500);
    tone(sp, 128, 500);

    lcd.clear();
    lcd.print(0, 0);
    lcd.print("Going to Left");
    lcd.setCursor(0, 1);
    lcd.print(">>>>>>Ribo>>>>>>");
  }
  if (var == 'R')                           //if the value 'R' Means Right Program Run
  {
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);;
    tone(sp, 708, 500);
    tone(sp, 111, 500);

    lcd.clear();
    lcd.print(0, 0);
    lcd.print("Going to Right");
    lcd.setCursor(0, 1);
    lcd.print("<<<<<<Momo<<<<<<");
  }
  if (var == 'V')
  {
    lcd.clear();
    for (int n = 0; n < 16; n++)           //starting a loop for character to print
    {
      lcd.setCursor(n * 1, 0);
      lcd.write(7);
    }
    lcd.setCursor(0, 1);
    lcd.print("Music Time");
    for (int j = 0; j < length; j++) {             //note running of tone directory
      if (notes[i] == ' ') {
        delay(beats[j] * tempo); // rest
      } else {
        playNote(notes[j], beats[j] * tempo);
      }

      // pause between notes
      delay(tempo / 2);
    }
  }
  if (var == ' ')
  {
    int R, G, B;                                //LED Cycle Control
    for (int i = 0; i <= 255; i++)
    {
      if (i >=  prevR - R && prevR < R) {

        analogWrite(Red, prevR + i);
      }
      if (i >= prevG - G && prevG < G) {

        analogWrite(Green, prevG + i);

      }
      if (i >= prevB - B && prevB < B) {

        analogWrite(Blue, prevB + i);

      }
      //delay(10);
      //}
      //for (int i = 0; i <= 255; i++)
      //{
      if (i >= R - prevR && prevR > R) {

        analogWrite(Red, prevR - i);
      }
      if (i >= G - prevG && prevG > G) {

        analogWrite(Green, prevG - i);

      }
      if (i >= B - prevB && prevB > B) {

        analogWrite(Blue, prevB - i);

      }
      delay(10);
    }
    delay(10);
    analogWrite(Red, R);
    analogWrite(Green, G);
    analogWrite(Blue, B);
    prevR = R;
    prevG = G;
    prevB = B;
  }

  int LDRValue = analogRead(LDR);
  if (LDRValue <= 700)
  {
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }

}