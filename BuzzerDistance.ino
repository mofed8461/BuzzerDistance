int minDst = 20;
int triggerPin = 8;
int echoPin = 9;

long duration = 0;

int buzzerPin = 7;

long GetDistance()
{
  digitalWrite(triggerPin, 0);
  delayMicroseconds(2);
  digitalWrite(triggerPin, 1);
  delayMicroseconds(10);
  digitalWrite(triggerPin, 0);

  duration = pulseIn(echoPin, HIGH);
  return duration * 0.017;
}

void setup() {
  pinMode(triggerPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

long dstBuffer[100];
int counter = 0;
float avgDst = 0;
void loop() 
{
  {
    long newDst = GetDistance();
    dstBuffer[counter++ % 100] = newDst;
    if (avgDst < minDst)
    {
      for (int i = 0; i < 10; ++i)
      {
        dstBuffer[counter++ % 100] = newDst;
      }
    }
  }
  delay(20);

  
  for (int i = 0; i < 100; ++i)
  {
    avgDst += dstBuffer[i];
  }
  avgDst /= 100.0;

  if (avgDst < minDst)
  {
    for (int i = 0; i < 30; ++i)
    {
      digitalWrite(buzzerPin, 1);
      delay(i * 2);
      digitalWrite(buzzerPin, 0);
      delay(i * 2);
    }
  }

  Serial.println(avgDst);
}
