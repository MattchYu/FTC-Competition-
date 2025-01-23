#include <PRIZM.h>
#include <TELEOP.h>

PRIZM prizm;
EXPANSION exc1;
PS4 ps4;

double mPowers[] = {0,0,0,0};
float powerMultiplier = 0.5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  prizm.PrizmBegin();
  ps4.setDeadZone(LEFT, 10);   // set the left joystick dead zone range to +/- 10
  ps4.setDeadZone(RIGHT, 10);  // set the right joystick dead zone range to +/- 10
  prizm.setServoSpeed(1,100); // Set Servo Speed for Claw
  prizm.setMotorInvert(1, 1);
  exc1.setMotorInvert(1,1,1);
  prizm.setServoSpeed(6,100); //Set Servo Speed for Ice Pile Stick
  prizm.setServoPosition(6,63); //Set Servo for Ice Pile Stick to Closed
}

void loop() {
  ps4.getPS4();

  if(ps4.Connected){        

    /**
    if(ps4.Button(L1) == 1){
      powerMultiplier = 1;
    }
    else{
      powerMultiplier = 0.5;
    }
    **/
    //int mPowers[] = {-constrain((ps4.Motor(LY)*0.75+ps4.Motor(LX)+ps4.Motor(RX)*powerMultiplier),-100,100), -constrain((ps4.Motor(LY)*0.75-ps4.Motor(LX)-ps4.Motor(RX)*powerMultiplier),-100,100),
    //               -constrain((ps4.Motor(LY)*0.75-ps4.Motor(LX)+ps4.Motor(RX)*powerMultiplier),-100,100), -constrain((ps4.Motor(LY)*0.75+ps4.Motor(LX)-ps4.Motor(RX)*powerMultiplier),-100,100)};                
    int mPowers[] = {-constrain((ps4.Motor(LY)+ps4.Motor(LX)+ps4.Motor(RX)*powerMultiplier),-100,100), -constrain((ps4.Motor(LY)-ps4.Motor(LX)-ps4.Motor(RX)*powerMultiplier),-100,100),
                   -constrain((ps4.Motor(LY)-ps4.Motor(LX)+ps4.Motor(RX)*powerMultiplier),-100,100), -constrain((ps4.Motor(LY)+ps4.Motor(LX)-ps4.Motor(RX)*powerMultiplier),-100,100)};                
             
    prizm.setMotorPowers(mPowers[0], mPowers[1]);                     // set PRIZM motor powers based on the values from the mPowers array
    exc1.setMotorPowers(1,mPowers[2], mPowers[3]);

    //Claw Commands on a Servo
    if(ps4.Button(L2)){
      prizm.setServoPosition(1, 0); //0 closes claw
    }
    else if(ps4.Button(L1)){
      prizm.setServoPosition(1, 180); //180 opens claw
    }
 
    //Arm Extension Commands on a Continuous Rotation Servo
    if(ps4.Button(R1)){
      prizm.setCRServoState(2, 100);
      }
    else if(ps4.Button(R2)){
      prizm.setServoPosition(1,180);
      prizm.setCRServoState(2, -100);
      }
     else{
      prizm.setCRServoState(2, 0);
    }

    //Ice Pile Stick Position Commands
    if(ps4.Button(SQUARE)){
      prizm.setServoPosition(6, 63); //Angle 63 = closed
    }
    else if(ps4.Button(TRIANGLE)){
      prizm.setServoPosition(6, 160); //Angle 160 = open or sticking out
    }
 
    //Diagnostic commands for Ice Pile Servo Position
    /**
    degree = prizm.readEncoderDegrees(1);
    Serial.print("Variable_1:");
    Serial.println(degree);
    **/
    //Door Open and Close Commands Set Positions
    if(ps4.Button(CIRCLE)){
      exc1.setMotorDegree(2,2,400,95); //Expansion #2, Motor #2, Speed 0-720, degrees 95 = open
    }
 
     if(ps4.Button(CROSS)){
      exc1.setMotorDegree(2,2,350,0); //Expansion #2, Motor #2, Speed 0-720, degrees 0 = closed
    }
  }

  else{  
    //Standard setup if PS4 Controller not connected                                      
    prizm.setMotorPowers(0,0);
    prizm.setServoPosition(1,180);
    prizm.setServoPosition(6,63);
  }

   
}



