// white line sensors initialization
const int digpin1 =26;//left  white sensor
const int digpin2 =24;//middle white sensor
const int digpin3 =22; //right white sensor

// time in miliseconds that we want the gate to be open according to bowl number
const int bowl1=3000;
const int bowl2=2000; 

// 4,9 left motors 
const int pwm2=6;
const int ina2=4;
const int inb2=9;

// 7,8=right motors 
const int pwm1=5;
const int ina1=7;
const int inb1=8;

// wheel motors setup done
const int lglswi =34;//left gate limit switch
const int rglswi =36;//right gate limit switch
const int slswi =38; //slide limit switch 
// all limit switches normally high(N.O., normally open)

const int pwm_b=3;//255=max speed
const int dirB=12; 

// food gate motor init
int road=1;//counts number of T's
int TimerA; 

// counter created to know which number bowl the robot has reached
// timer created to allow the robot to continue
// a little after the "flag"(where the bowl is situated)
void setup()
{
Serial.begin(9600); // communication between the computer and the controller 

// white line sensor set as INPUT
  pinMode(26,INPUT);//left white sensor
  pinMode(24,INPUT);//middle white sensor
  pinMode(22,INPUT);//right white sensor

// 4,9left motors
  pinMode(6,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(9,OUTPUT);

// 7,8=right motors 
// wheel motors set as OUTPUT
  pinMode(5,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);

// limit switches set as INPUT
  pinMode(34,INPUT);
  pinMode(36,INPUT);
  pinMode(38,INPUT); 

// ardumoto
// gate motor set as OUTPUT
  pinMode(3,OUTPUT);
  pinMode(12,OUTPUT); 
}
void loop()
{
    // if the middle sensor senses the black line
    if(digitalRead(digpin2)==LOW) 
    {
     // function that makes the robot drive forward
      driveForward(); 
    }
    // if the left sensor senses the black line
    if(digitalRead(digpin1)==LOW) 
    {
      // function that makes robot move slightly left
      deviateLeft(); 
    }
    // if the right sensor senses the black line
    if(digitalRead(digpin3)==LOW) 
    {
      // function that makes the robot move slightly right
      deviateRight(); 
    }

  // if all sensors sense white (no black line detected)
  if(digitalRead(digpin1)==HIGH&&digitalRead(digpin2)==HIGH&&digitalRead(digpin3==HIGH)) 
      // count additional bowl, every station has a long white line to be detected by the robot as a bowl
      road++; 

// bowl detected-limit switch was pressed
if(digitalRead(slswi)==LOW)
  {
    // function that makes robot stop
    stopDriving(); 

    // wait 100 mili seconds
    delay (100); 

    // Timer equals millis: function that calculates the time that elapsed since the start of the program
    TimerA=millis(); 
      while(millis()-TimerA<700) 
      // as long as this condition: the current time that has passed since the start
      // of the program minus the time we found earlier(TimerA) is smaller than 700 miliseconds
      // the while goes on- so until 700 miliseconds pass the robot continues to follow the black line
      // and doesn't move from the path
      {
        if(digitalRead(digpin2)==LOW)
        {
          driveForward ();
        }
        if(digitalRead(digpin1)==LOW)
        {
          deviateLeft();
        }
        if(digitalRead(digpin3)==LOW)
        {
          deviateRight();
        }
      }

    // stop driving, wait 100 mili-seconds
    stopDriving();
    delay (100); 

    // as long as the limit switch to the right of the container 
    // is not pushed (the gate still hasn't upened all the way)
      while(digitalRead(rglswi)== HIGH) 
      {
        digitalWrite(12,LOW); // Counterclockwise
        analogWrite(3,60); // SPEED OF LIFTING 45 
       }
       
    // activate the gate motor until the gate is fully open(food is 
    // coming out through gate)
    digitalWrite( 12,HIGH); // Counterclockwise
    analogWrite(3,0); 
    
    // wait 2 seconds
    delay(2000);   

      // if it's the first bowl
      if(road==2) 
      {
        // wait the amount of time we previously noted
        // in respect to the amount of food we aim to release to the first bowl
        delay(bowl1); 
      }
       // if it's the second bowl
      if(road==3)
      {
        // wait the amount of time we previously noted
        // in respect to the amount of food we aim to release to the second bowl
        delay(bowl2);  
      }

    // activate the gate motor in the opposite direction
    // until the gate is closed(if the left limit is activated
    // and the gate returned to its original state-closed
    digitalWrite(12,HIGH); //Counterclockwise
    analogWrite(3,55);

    // check if the gate is closed 
      if(digitalRead(lglswi)==LOW)
      {
        // stop the gate motor if closed
        digitalWrite(12,LOW);
        analogWrite(3,0);
      } 
  }// motor-stop

}
void driveForward () 
// function that makes the robot drive forward
// (because one side of the motors is stronger than the other,
// we equalized it by checking which PWM values allow the robot to
// drive straight. We decided on one-then changed the other value 
// accordingly.
{
    digitalWrite(4,LOW);//CLOCKWISE
    digitalWrite(9,HIGH);
    analogWrite(6,35);
    //
    digitalWrite(7,LOW);
    digitalWrite(8,HIGH);
    analogWrite(5,26);
}
void deviateLeft () 
// function that makes the robot deviate slightly to the left.
// in order to make the robot go slightly to the left we left the right motor
// PWM values from the driveForward function, and changed the left motor PWM to 0.
{
    digitalWrite(4,LOW);
    digitalWrite(9,HIGH);
    analogWrite(6,40);
    //
    digitalWrite(7,LOW);
    digitalWrite(8,HIGH);
    analogWrite(5,0);
}
void deviateRight () 
// function that makes the robot deviate slightly to the right.
// in order to make the robot go slightly to the right we left the left motor
// PWM values from the driveForward function, and changed the right motor PWM to 0.
{
    digitalWrite(4,LOW);
    digitalWrite(9,HIGH);
    analogWrite(6,0);
    //
    digitalWrite(7,LOW);
    digitalWrite(8,HIGH);
    analogWrite(5,40);
}
void stopDriving() 
// function that enables the robot to stop driving
// by setting both motors PWM to 0
{
    digitalWrite(4,HIGH);
    digitalWrite(9,HIGH);
    analogWrite(6,0);
    //
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    analogWrite(5,0);
}
