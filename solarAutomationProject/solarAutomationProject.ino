  
//This project is to use an Arduino to automatically control my Solar/Generator system. No warranties expressed or implied, use at your OWN RISK!
//This could use some monitoring and failsafes, for example, if the generator never starts due to any reason. May be easy to just monitor battery voltage and set a hard cutoff to catch many errors.
//Could do a ton of other fun stuff if I were to connect to the BMS via RS232. We'll see.

//inputs (buttons, switches)
int invSw;
int genSw;
int lowVoltage;
int genRunning;
int genManualOnSwitch;
int genManualOffSwitch;

//state tracking
int invState = 1; //normally closed relay/on
int genState = 0; //normally not running
int genFailure = 0;

int invStart(){
  invState = 1;
  //release relay (as connected as Normally Closed)
}

int invStop(){
  invState = 0;
  //connect relay (as connected as Normally Closed)
}
int genStart(){
  genState = 1;
  //Connect relay for 3 seconds (start button)
  //check genRunning to see if the generator is actually outputting power! If not, maybe retry, and if it fails, disconnect inverter and throw error on LCD (by setting genFailure = 1)
}

int genStop(){
  genState = 0;
  //connect relay for three seconds (stop button)
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

if (invSw || genSw) {
  if (!lowVoltage) {
    if (invState = 0) {
      invStart();
      if (genState = 1) {
        genStop();
      }
    }
    if (genState = 1) {
      genStop();
      if (invState = 0) {
        invStart();
      }
    }
  }
  if (lowVoltage) {
    if (invSw) {
      invStop();
    }
    if (genSw) {
      genStart();
    }
    if (genFailure = 1) {
      invStop();
    }
  }
}

if (genManualOnSwitch) {
  genStart();
  genState = 0; //just in case gen is unexpectedly stopped for some reason after
  }
if (genManualOffSwitch) {
  genStop();
  genFailure = 0; //switch to also clear genFailure state
  }
  
}
