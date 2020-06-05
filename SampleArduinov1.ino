#include <Adafruit_NeoPixel.h>
#define BUTTON_PIN1   2    // Digital IO pin connected to the button.  This will be
                          // driven with a pull-up resistor so the switch should
                          // pull the pin to ground momentarily.  On a high -> low
                          // transition the button press logic will execute.
 
#define PIXEL_PIN1    3    // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 60
#define BUTTON_PIN2   4
#define PIXEL_PIN2    5
#define BUTTON_PIN3   6
#define PIXEL_PIN3    7
#define BUTTON_PIN4   8
#define PIXEL_PIN4    9
#define BUTTON_PIN5   10
#define PIXEL_PIN5    11


int time = 10; //Define variable for timer and assign value which will be a time for a timer
const int buzzer = 13; //Define a constant for a buzzer pin and assign 13 to it
unsigned long prevMillis; //Storage for time value
int timer; //Timer for a game
short int i;
int score = 0; //Score holder
short int generateNextNum = 0; //Flag to generate next random number
volatile int stage = 1; //Stage of a game
short int randomNumber = 0; //Random number

//This is the function that runs once after Arduino is turned on.
void setup()
{
  Serial.begin(9600);

  pinMode(BUTTON_PIN1, INPUT_PULLUP);
  pinMode(BUTTON_PIN2, INPUT_PULLUP);
  pinMode(BUTTON_PIN3, INPUT_PULLUP);
  pinMode(BUTTON_PIN4, INPUT_PULLUP);
  pinMode(BUTTON_PIN5, INPUT_PULLUP);
  pinMode(PIXEL_PIN1, OUTPUT);
  pinMode(PIXEL_PIN2, OUTPUT);
  pinMode(PIXEL_PIN3, OUTPUT);
  pinMode(PIXEL_PIN4, OUTPUT);
  pinMode(PIXEL_PIN5, OUTPUT);
  
/*  pinMode(3, OUTPUT);  //Set pin 3 as an output to light a diode 1 up
  pinMode(4, OUTPUT);  //Set pin 4 as an output to light a diode 2 up
  pinMode(5, OUTPUT);  //Set pin 5 as an output to light a diode 3 up
  pinMode(6, OUTPUT);  //Set pin 6 as an output to light a diode 4 up
  pinMode(7, OUTPUT);  //Set pin 67 as an output to light a diode 5 up
  pinMode(buzzer, OUTPUT);  //Set buzzer pin 13 as an output
  pinMode(2, INPUT); //Set pin 2 as an input for signals from buttons
   pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(7, INPUT);*/

  //Set interruption to pin 2 on rising signal and trigger reset routine function
  attachInterrupt(digitalPinToInterrupt(2), reset_routine, RISING);
}

//This function is attached to interrupt and is triggered everytime any button is pressed.
void reset_routine()
{
  if (stage == 1)
  {
    //When button is pressed during welcome routine the value of status "stage" is changed from 1 to 2
    //and the program breaks a while loop in welcome_routine, then continues with start_routine function
    stage = 2;
  } else if (stage == 3)
  {
    generateNextNum = 1; //Set flag for program to generate random number
    digitalWrite(randomNumber, LOW); //Turn off the light with random number
  } else if (stage == 4)
  {
    stage = 1;
  }
}
//This is the first function running in the program.
void welcome_routine()
{
  digitalWrite(3, HIGH);     //First light is turned on.

  //sound to initiate sequence?


  while (stage == 1) {} //Loop to wait for button to be pressed. When button is pressed status "stage" is changed from 1 to 2.
}

void start_routine()
{

  // Change to speaker to start sequence


  for (i = 0; i <= 2; i++)  //Loop with 3 passes
  {
    for (int x = 3; x <= 7; x++) //Turned on all lights.
    {
      digitalWrite(x, HIGH);
    }
    if (i == 0)       //First pass of loop
    {

      //speaker to say Get Ready
    } else if (i == 1)
    { //Second pass of loop
      //      Speaker to say "Set"
    } else if (i == 2)      //Third pass of loop
    {
      //      Speaker to say GO
    }
    //    tone(buzzer, 500);      //Play sound on buzzer.
    //   delay(500);         //Hold sound on for 500msec.
    //    noTone(buzzer);       //Turn off sound.

    //      Speaker to play sound

    for (int x = 3; x <= 7; x++) //Turned off all lights.
    {
      digitalWrite(x, LOW);
    }
    delay(500);         //Wait 500msec.
  }
  stage = 3;              //Set status "stage" to 3.
  score = 0;              //Reset score to 0.
  timer = time;             //Assign game time to timer
  randomNumber = 0;           //Assign 0 to random number
}

//This function is the actual
void play_routine()
/*{
  prevMillis = millis();  //Capture current time
*/

{ while (timer > 0) //Repeat outer loop until timer value >0
  {
    //The outer loop pass occures only at the begining of the game
    //when randomNumber is 0 and when the button is pressed when randomNumber has some value.
    if (randomNumber != 0)
    {
      //That's why we need to check if it's 0 then skip adding a score
      //otherwise increase the score.
      score = score + 1;
    }
    //Assign random number to the storage so that
    //a new value can be generated and compared with the old one.
    int randomNumberOld = randomNumber;

    //WHILE is used instead of IF to avoid the same random number,
    //if new generated random number is the same then loop will continue
    while (randomNumberOld == randomNumber)
    {
      randomNumber = random(3, 8); //Generate random number between 3 and 7, assign it to variable
    }
    //Light up the button with a random number
    digitalWrite(randomNumber, HIGH);

    //Set the flag to generate random number to false, the flag is set to true
    //only when the correct button is pressed.
    generateNextNum = 0;

    //This inner loop updates the time and the score,
    //when the correct button is pressed then generateNextNum is set to true,
    //the loop breaks and the outer loop continues, if until the
    //button is pressed the inner loop continues so we need to check timer in it
    while (generateNextNum == 0 && timer > 0)
    {
      unsigned long curMillis = millis(); //Assignes current time to curMillis variable

      //Compares the time at the begging of the outer loop to the time in the inner loop
      //if 1 sec passed then it updates the timer
      if (curMillis - prevMillis >= 1000) //1000 = 1sec
      {
        timer -= 1;           //update the time by counting down


        prevMillis = prevMillis + 1000;
        //After 1 sec passes add 1 sec to the prevMillis
        //variable so that when we are subtracting the values above the max difference is 1 sec
      }
    }
  }
}

//This function is executed when the time is over and the program waits for the player to start over
void finish_routine()
{
  stage = 4;            //Set variable stage to 4
  digitalWrite(randomNumber, LOW); //Turn off the button which was last on
  tone(buzzer, 500);        //Send 1KHz sound signal.
  delay(100);           //Hold sound on for 100msec.
  noTone(buzzer);         //Turn off sound.


  delay(3000);          //Wait for 3sec
  digitalWrite(3, HIGH);      //Light up the first button
  while (stage == 4) {}     //Loop until the button is pressed to start over
}

//This is the main program which is always running and looping after setup fuction finishes.
void loop()
{
  welcome_routine();  //This is the first function triggered.
  start_routine();    //This function is triggered when button is pressed during welcome_routine.
  play_routine();   //This function is triggered automatically when start_routine finishes.
  finish_routine();   //This function is triggered automatically when the game time is over.
}
