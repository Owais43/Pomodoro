// a simple pomodoro timer

int message = 0;
// the following variables are longs because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long TASK_TIME = 10000; // for testing: 10 seconds
unsigned long BREAK_TIME = 5000; // for testing: 5 seconds
//unsigned long TASK_TIME = 2400000; // 40 mins
//unsigned long BREAK_TIME = 600000; // 10 mins
unsigned long taskDelayStart = 0; // the time the delay started
unsigned long breakDelayStart = 0; // the time the delay started
bool taskDelayRunning = false; // true if still waiting for delay to finish
bool breakDelayRunning = false; // true if still waiting for delay to finish
bool taskLightOn = false; // keep track of the lamp state

#define taskLampPin 13
#define breakLampPin 12
#define triggerPin 4

void setup() {
  pinMode(triggerPin, INPUT_PULLUP); //set up switch pin with internal pullup resistor
  pinMode(taskLampPin, OUTPUT);        
  digitalWrite(taskLampPin, LOW);
  pinMode(breakLampPin, OUTPUT);        
  digitalWrite(breakLampPin, LOW);

  // start the serial connection
  Serial.begin(9600);
}

void loop() {
  message = digitalRead(triggerPin);
  if (message == 0){ //if a task is in progress
    if (!taskLightOn && !taskDelayRunning & !breakDelayRunning){ // if the lamp is off and neither timer has started yet
      taskDelayStart = millis(); //start delay
      taskDelayRunning = true;   //start the task timer

      digitalWrite(taskLampPin, HIGH);         //turns on the light
      taskLightOn = true;
      Serial.println("New task: begin work, and continue...");
    }
      
    if (taskLightOn && taskDelayRunning && ((millis() - taskDelayStart) >= TASK_TIME)) { // this code executes when task time is up
      taskDelayStart += TASK_TIME; // this prevents drift in the delays
      taskDelayRunning = false;
      Serial.println("time has elapsed, you've been working hard, take a break");
      digitalWrite(breakLampPin, HIGH);         //turns on the light
      digitalWrite(taskLampPin, LOW);          //turns off the light
      taskLightOn = false;

       breakDelayStart = millis(); //start delay
       breakDelayRunning = true;
     }
    
    if (!taskLightOn && breakDelayRunning && ((millis() - breakDelayStart) >= BREAK_TIME)) { // this code executes when break time is up
      breakDelayStart += BREAK_TIME; // this prevents drift in the delays
      breakDelayRunning = false;
      Serial.println("break time is over, back to work");
      taskDelayRunning = true;
      taskDelayStart = millis(); //start delay
    digitalWrite(breakLampPin, LOW);         //turns on the light
      digitalWrite(taskLampPin, HIGH);         //turns on the light
      taskLightOn = true;
    }
  }
      
    if (message == 1){ //if task is completed, turn it off
      breakDelayRunning = false;
      taskDelayRunning = false;
      if (taskLightOn){
      Serial.println("task complete");
      digitalWrite(taskLampPin, LOW);          //turns off the light
      digitalWrite(breakLampPin, LOW);  
      taskLightOn = false;
          
      }
     Serial.println(" waiting for task"); 
     }
}