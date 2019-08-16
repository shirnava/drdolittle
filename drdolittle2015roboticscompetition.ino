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
  pinMode(26,INPUT);//left white sensor
  pinMode(24,INPUT);//middle white sensor
  pinMode(22,INPUT);//right white sensor

//white line sensor set as INPUT

  pinMode(6,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(9,OUTPUT);
//4,9left motors
  pinMode(5,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
//7,8=right motors 
//wheel motors set as OUTPUT
  pinMode(34,INPUT);
  pinMode(36,INPUT);
  pinMode(38,INPUT); 
//limit switches set as INPUT
  pinMode(3,OUTPUT);
  pinMode(12,OUTPUT); 
//ardumoto
//gate motor set as OUTPUT
}
void loop()
{

    if(digitalRead(digpin2)==LOW) //if the middle sensor senses the black line
    {
      driveForward(); //function that makes the robot drive forward
    }
    if(digitalRead(digpin1)==LOW) //if the left sensor senses the black line
    {
      deviateLeft(); //function that makes robot move slightly left
    }
    if(digitalRead(digpin3)==LOW) //if the right sensor senses the black line
    {
      deviateRight(); //function that makes the robot move slightly right
    }

  if(digitalRead(digpin1)==HIGH&&digitalRead(digpin2)==HIGH&&digitalRead(digpin3==HIGH)) // if all sensors sense white (no black line detected)
    road++; //count additional bowl, every station has a long white line to be detected by the robot as a bowl

if(digitalRead(slswi)==LOW)//bowl detected-limit switch was pressed
  {
    stopDriving(); //function that makes robot stop
    delay (100); //wait 100 mili seconds

    TimerA=millis(); //Timer equals millis: function that calculates the 
                     // time that elapsed since the start of the program
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

    stopDriving();
    delay (100) ; //stop driving, wait 100 mili-seconds
      while(digitalRead(rglswi)== HIGH) // as long as the limit switch to the right
                                        // of the container is not pushed
                                        // (the gate still hasn't upened all the way)
      {
        digitalWrite(12,LOW); //Counterclockwise
        analogWrite(3,60); // SPEED OF LIFTING 45 
       }
       
     //activate the gate motor until the gate is fully open(food is coming out through gate)
 
    digitalWrite( 12,HIGH); //Counterclockwise
    analogWrite(3,0); 
    //
    delay(2000);   
//wait 2 seconds

      if(road==2) //if it's the first bowl
      {
        delay(bowl1); 
// wait the amount of time we previously noted
// in respect to the amount of food we aim to release to the first bowl
      }
      if(road==3) //if it's the second bowl
      {
        delay(bowl2);  
// wait the amount of time we previously noted
// in respect to the amount of food we aim to release to the second bowl
      }

    digitalWrite(12,HIGH); //Counterclockwise
    analogWrite(3,55);
// activate the gate motor in the opposite direction
// until the gate is closed(if the left limit is activated
// and the gate returned to its original state-closed
      if(digitalRead(lglswi)==LOW)//check if the gate is closed 
      {
        digitalWrite(12,LOW);
        analogWrite(3,0);
//stop the gate motor if closed
      } 
  }//motor-stop

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
