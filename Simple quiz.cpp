#include <LiquidCrystal.h>
int Contrast = 150; //depends on your screen
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

boolean buttonLeft;
boolean buttonRight;

//Verb forms: PS Past Simple - PP Part Participle - T Translation
String topQuestions[] = {"PS of to give:", "PS of to swim:", "PP of to choose:", "PP of to be:", "T of to cast:"};
String bottomQuestions[] = {"gave", "swum", "chose", "been", "werpen"};
int maxNumQuestions = 5;
int NumQuestions = 0;
int answers[] = {1, 0, 0, 1, 1};    //1 is correct - 0 is wrong
int score = 0;

void setup()
{
    pinMode(13, INPUT);  //Rechter knop
    pinMode(1, INPUT);   //Linker knop
    pinMode(10, OUTPUT); //LED groen
    pinMode(9, OUTPUT);  //LED geel
    pinMode(8, OUTPUT);  //LED rood

    analogWrite(6, Contrast);
    lcd.begin(16, 2);

    lcd.setCursor(0, 0);             //Introduction welcome
    lcd.print("Welcome");
    lcd.setCursor(0, 1);
    lcd.print("Dear Youtuber");
    delay(3000);
    lcd.clear();
    lcd.print("Quiz game!");
    delay(3000);
    lcd.clear();
    lcd.print("Starting...");
    marioIntro();
    lcd.clear();
}

void correctAnswer()
{                                   //Function for correct answers
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CORRECT!");
    digitalWrite(10, HIGH);
    tone(7, 2500, 100);
    delay(100);
    tone(7, 3500, 100);
    delay(250);
    digitalWrite(10, LOW);
    noTone(7);
    delay(2000);
    lcd.clear();
}

void wrongAnswer()
{                                      //Function for Wrong answers
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WRONG!");
    digitalWrite(8, HIGH);
    tone(7, 1350, 100);
    delay(100);
    tone(7, 1000, 100);
    delay(250);
    digitalWrite(8, LOW);
    noTone(7);
    delay(2000);
    lcd.clear();
}

void marioIntro()
{                                      //Mario theme song (short version)
    tone(7, 660, 100);
    delay(150);
    tone(7, 660, 100);
    delay(300);
    tone(7, 660, 100);
    delay(300);
    tone(7, 510, 100);
    delay(100);
    tone(7, 660, 100);
    delay(300);
    tone(7, 770, 100);
    delay(550);
    tone(7, 380, 100);
    delay(575);
}

void showScore()                        //Score on screen
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Thanks 4 playing");
    lcd.setCursor(0, 1);
    lcd.print("Your score:");
    lcd.setCursor(13, 1);
    lcd.print(score);
    if (score > 3)                      //LED according to score
    { 
        digitalWrite(10, HIGH);
    }
    else if (score = 3)
    {
        digitalWrite(9, HIGH);
    }
    else if (score < 3)
    {
        digitalWrite(8, HIGH);
    }
    delay(30000);                       //end of game
}

void loop()
{
    buttonLeft = digitalRead(1);         //False button
    buttonRight = digitalRead(13);       //True button

    if (NumQuestions != maxNumQuestions)
    {
        lcd.setCursor(0, 0);                        //display question
        lcd.print(topQuestions[NumQuestions]);
        lcd.setCursor(0, 1);                        //display possible answer
        lcd.print(bottomQuestions[NumQuestions]);

        if (buttonRight == HIGH)                     //if True button is clicked
        {
            if ((answers[NumQuestions]) == 1)       
            {
                correctAnswer();
                NumQuestions++;
                score++;
            }
            else if ((answers[NumQuestions]) == 0)
            {
                wrongAnswer();
                NumQuestions++;
            }
        }
        if (buttonLeft == HIGH)                     //if False button is clicked
        {
            if ((answers[NumQuestions]) == 0)
            {
                correctAnswer();
                NumQuestions++;
                score++;
            }
            else if ((answers[NumQuestions]) == 1)
            {
                wrongAnswer();
                NumQuestions++;
            }
        }
    }
    if (NumQuestions == maxNumQuestions)            //5 questions solved? --> score
    {
        showScore();
    }
}
