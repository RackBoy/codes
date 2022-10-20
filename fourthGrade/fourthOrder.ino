#define ADC0pin 39          // Pin ADC0
#define DAC1pin 26          // Pin DAC1
#define Tm 100              // ms

volatile int interruptCounter;

void IRAM_ATTR onTimer() {
  interruptCounter++;
}

hw_timer_t * timer = NULL;

void setup() {
  
  Serial.begin(115200);
  timer = timerBegin(0, 8000, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 10*Tm, true);
  timerAlarmEnable(timer);
}

const float b0A = 0.0003402;  // transfer function values in order
const float a1A = -0.9753;

const float b0B = 0.09827;  // transfer function values 
const float a1B = -0.9656; 

const float b0C = 1;        // transfer function values 
const float b1C = -0.804;
const float a1C = -0.9608;

const float b0D = 1;        // transfer function values 
const float b1D = -0.7652;
const float a1D = -0.956;

float U = 0, U_1 = 0;          // INPUTS AND OUTPUTS
float YA = 0, YA_1 = 0;          

 
float YB = 0, YB_1 = 0;          // delays and outputs
float YC = 0, YC_1 = 0;          
float YD = 0, YD_1 = 0;          

void loop() {
  
  if (interruptCounter > 0) { 
    interruptCounter--;
    U = analogRead(ADC0pin)*3.2/4095.0;           
    YA = b0A*U_1-a1A*YA_1;  
    YB = b0B*YA_1-a1B*YB_1; 
    YC = b1C*YB_1+b0C*YB-a1C*YC_1;
    YD = b1D*YC_1+b0D*YC-a1D*YD_1;
 
    U_1 = U;                                      // saves U(k-1) for the next loop
    YA_1 = YA;                                      // saves Y(k-1) for the next loop
                                         
    YB_1 = YB;
    YC_1 = YC;
    YD_1 = YD;
    
    if (YD<0) YD=0;                                 
    else if (YD>3.2) YD=3.2;                        
    dacWrite(DAC1pin,YD*255/3.2);                  
    Serial.print(interruptCounter);
    Serial.print(",");
    Serial.print(U);
    Serial.print(",");
    Serial.println(YD);
  }
}
