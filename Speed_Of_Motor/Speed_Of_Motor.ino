//Reading encoder count to find out the speed of a rotating shaft of a motor
//Motor driver used : Pimironi 2040
//Pins used : GPIO 0 ENCODER A_A, GPIO 1 ENCODER A_B
//The encoders produce 12 counts per revolution.
//There are 600 encoder counts per revoluiton at the shaft due to the gear used.
//The gear ratio of the motor is found to be 50:1

const int ENCA_A=0;
const int ENCA_B=1;
const int in_1=4;
const int in_2=5;
volatile long count = 0;
long previous_count = 0;
unsigned long timeBetweenCalculation= 1000;
unsigned long timeOfLastCalculation = 0;
float speed=0;
const int countsPerRevolution = 600; //number of encoder counts per revolution at the shaft


void setup()
{
  pinMode(ENCA_A, INPUT_PULLUP);
  pinMode(ENCA_B, INPUT_PULLUP);
  pinMode(in_1, OUTPUT);
  pinMode(in_2, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(ENCA_A),channelAEvent,CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCA_B),channelBEvent,CHANGE);
}

void loop()
{
  digitalWrite(in_1, HIGH);
  digitalWrite(in_2, LOW);
unsigned long current_time=millis();
//Serial.println(current_time);//for my reference
if((current_time - timeOfLastCalculation)>=timeBetweenCalculation)
{
  long change = count - previous_count; //The count used here is found from the count that is returned from interrupts. change: This is the change in encoder counts during the specified time interval. It tells you how many encoder counts have occurred during that time.
  float speed = (float)change / countsPerRevolution * 60 / (timeBetweenCalculation / 1000.0); //calculated speed in RPM
  Serial.print(count);
  Serial.print(" ");
  Serial.println(change);
  previous_count=count;
  timeOfLastCalculation=current_time;
  Serial.println(speed);
  Serial.print("rpm")
  
}
}

void channelAEvent()
{
  if(digitalRead (ENCA_A)!= digitalRead(ENCA_B))
  {
  count+=1;
}
  else
  {
  count-=1;
  }
}
void channelBEvent()
{
  if(digitalRead(ENCA_A)!=digitalRead(ENCA_B))
  {
    count-=1;
  }
  else
  {
    count+=1;
  }
}