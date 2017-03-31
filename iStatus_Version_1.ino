// include the library code:
#include <LiquidCrystal.h>

#include <IRLib.h>

//Create a receiver object to listen on pin 11
IRrecv My_Receiver(8);
//Create a decoder object
IRdecode My_Decoder;


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// initialize an array of integers with the remote’s values
long int remoteValues[11] = {16738455,
                             16724175,
                             16718055,
                             16743045,
                             16716015,
                             16726215,
                             16734885,
                             16728765,
                             16730805,
                             16732845,
                             16753245
                            };

String outputCommands[10][2] = {{"Come in!", "Green"},
                             {"Not Here", "Red"},
                             {"Sorry, I Am Busy", "Red"},
                             {"Sleeping", "Red"},
                             {"One Minute", "Yellow"},
                             {"Doing Homework", "Yellow"},
                             {"Come Back Later", "Red"},
                             {"Off Being Great!", "Red"},
                             {"GO AWAY!", "Red"}
};

int redPin = 13;
int greenPin = 7;
int bluePin = 6;

// initialize array containing commands for LCD display and RGB LED
String commands[2];

void setup() {
   // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

   // initialize the RGB led
   pinMode(redPin, OUTPUT);
   pinMode(greenPin, OUTPUT);
   pinMode(bluePin, OUTPUT);
  
   Serial.begin(9600);
   My_Receiver.enableIRIn(); // Start the receiver
}

void setColor(int red, int green, int blue)
{
   analogWrite(redPin, red);
   analogWrite(greenPin, green);
   analogWrite(bluePin, blue);
}


void findUserInput (long int val)
{
  String ans[2];
  for (int i = 0; i < sizeof(remoteValues); i++)
  {
    if (val == remoteValues[i])
    {
      ans[0] = outputCommands[i][0];
      ans[1] = outputCommands[i][1];
    }
  }
}

void loop() {
   // set the cursor to column 0, line 0
   // (note: line 1 is the second row, since counting begins with 0)
   lcd.setCursor(0, 0);
   if (My_Receiver.GetResults(&My_Decoder)) {
    lcd.clear();
    My_Decoder.decode(); //Decode the data
    long int remoteValue = My_Decoder.value;  //Store input from remote
    lcd.print(commands[0]);
    if (commands[1] == "Green")
    {
      setColor(0, 255, 0);
    }
    if (commands[1] == "Yellow")
    {
      setColor(255, 130, 0);
    }
    if (commands[1] == "Red")
    {
      setColor(255, 0, 0);
    }
    Serial.println(remoteValue); //Show the results on serial monitor
    delay(300); // delay for .3 seconds before next reading
    My_Receiver.resume();  //Restart the receiver
  }
}
