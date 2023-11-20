bool Flag;
int Error;

void setup() {
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
Serial.begin(9600);
}

void loop() {
   while (Serial.available() > 0) {             
   Error = (byte)Serial.read();        
   Flag = true;                  
   delay(10);
  }
   if (Flag) {        
   int power = computePID(Error, 0, 0.29, 0.08, 0.11, 0.01, -128, 128);  
   Flag = false; 
   analogWrite(3,128 + power);
   analogWrite(5,128 - power);    
  }
}

int computePID(float input, float setpoint, float kp, float ki, float kd, float dt, int minOut, int maxOut) {
  float err = setpoint - input;
  static float integral = 0, prevErr = 0;
  integral = constrain(integral + (float)err * dt * ki, minOut, maxOut);
  float D = (err - prevErr) / dt;
  prevErr = err;
  return constrain(err * kp + integral + D * kd, minOut, maxOut);
}
