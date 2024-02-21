#define enA 5  // speed of M1
#define enB 6  // speed of M2
#define in1 11 // 1 -> fwd M1
#define in2 10 // 1 -> bwd M1
#define in3 13 // 1 -> fwd M2
#define in4 12 // 1 -> bwd M2
/***********************/
#define s_r 8 // ir-sensor right
#define s_l 9 // ir-sensor left
/***********************/
char mode; // mode = V -> Remote Controlled Car, v -> Line Follower
bool r_sen; // right sensor value
bool l_sen; // left  sensor value
void setup() {
  Serial.begin(9600);
  pinMode(s_r,INPUT);
  pinMode(s_l,INPUT);
  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
}
void loop() {
  Stop();
  while(Serial.available()>0){
    mode = Serial.read();
    if (mode == 'V'){
      //Serial.println("RC Car");
      while (true){
        mode = Serial.read();
        if( RC_Car(mode) ) break;
      }
    }
    else if (mode == 'v' ){
      //Serial.println("Line Follower");
      while(true){
        mode = Serial.read();
        if( Line_Follower(mode) ) break;
      }
    }
  }
}

bool Line_Follower(char command){
  if (tolower(command) == 'w' ){
    /*Serial.println("-----------------------");
    Serial.println("Switch Please choose V");
    Serial.println("for RC Car or v ");
    Serial.println("for Line follower");
    Serial.println("-----------------------");*/
    return 1;
  }
  r_sen = digitalRead(s_r);
  l_sen = digitalRead(s_l);
  if(r_sen && !l_sen){
    right();
  }
  else if(!r_sen && l_sen){
    left();
  }
  else if(!r_sen && !l_sen){
    forward();
  }
  else if(r_sen && l_sen){
    Stop();
  }
  return 0;
}

bool RC_Car(char command){
  switch (tolower(command))
      {
        case 'f':
          //Serial.println("Forward");
          forward();
          delay(5);
          break;
        case 'l':
          //Serial.println("Right");
          right();
          delay(5);
          break;
        case 'r':
          //Serial.println("Left");
          left();
          delay(5);
          break;
        case 'b':
          //Serial.println("Back");
          reverse();
          delay(5);
          break;
        case 'i':
          //Serial.println("Forward Left");
          f_left();
          delay(5);
          break;
        case 'g':
          //Serial.println("Forward Right");
          f_right();
          delay(5);
          break;
        case 'h':
          //Serial.println("Back Left");
          b_left();
          delay(5);
          break;
        case 'j':
          //Serial.println("Back Right");
          b_right();
          delay(5);
          break;
        case 's':
          //Serial.println("Stop");
          Stop();
          delay(5);
          break;
        case 'w':
          /*Serial.println("-----------------------");
          Serial.println("Switch Please choose V");
          Serial.println("for RC Car or v ");
          Serial.println("for Line follower");
          Serial.println("-----------------------");*/
          return 1;
          break;
      }
      return 0;
}

void forward(){
  analogWrite(enA,150);
  analogWrite(enB,150);
  digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,1);
  digitalWrite(in4,0);
}
void right(){
  analogWrite(enA,150);
  analogWrite(enB,150);
  digitalWrite(in1,0);
  digitalWrite(in2,0);
  digitalWrite(in3,1);
  digitalWrite(in4,0);
}
void left(){
  analogWrite(enA,150);
  analogWrite(enB,150);
  digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,0);
  digitalWrite(in4,0);
}
void reverse()
{
  analogWrite(enA,100);
  analogWrite(enB,100);
  digitalWrite(in1,0);
  digitalWrite(in2,1);
  digitalWrite(in3,0);
  digitalWrite(in4,1);
}
void Stop()
{
  analogWrite(enA,0);
  analogWrite(enB,0);
  digitalWrite(in1,0);
  digitalWrite(in2,0);
  digitalWrite(in3,0);
  digitalWrite(in4,0);
}
void b_left(){
  analogWrite(enA,150);
  digitalWrite(in1,0);
  digitalWrite(in2,1);
  digitalWrite(in3,0);
  digitalWrite(in4,1);
}
void b_right(){
  analogWrite(enB,150);
  digitalWrite(in1,0);
  digitalWrite(in2,1);
  digitalWrite(in3,0);
  digitalWrite(in4,1);
}
void f_right(){
  analogWrite(enB,150);
  digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,1);
  digitalWrite(in4,0);
}
void f_left(){
  analogWrite(enA,150);
  digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,1);
  digitalWrite(in4,0);
}