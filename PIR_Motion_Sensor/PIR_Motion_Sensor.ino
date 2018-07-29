//PIR Motion Sensor
const int PIRSensor=2;
const int ledPin=13;
int sensorValue=0;
void setup()
{
    pinMode(PIRSensor,INPUT);    
    pinMode(ledPin,OUTPUT);       
}
void loop()
{
    sensorValue=digitalRead(PIRSensor);
    if (sensorValue==HIGH)
    {    
        digitalWrite(ledPin,HIGH);
        delay(50);
        digitalWrite(ledPin,LOW);
        delay(50);
    }
    else 
    {
        digitalWrite(ledPin, LOW);
    }
}

