#define dviz 7
#define shim 6
#define temp 0
#define photo 1
#define potens 2
#define butt 8
bool led=true;
bool flag=true;
unsigned long butt_delay;
unsigned long off_delay;
int night=700;
void setup() {
  pinMode(dviz, INPUT);
  pinMode(shim, OUTPUT);
  pinMode(temp, INPUT);
  pinMode(photo, INPUT);
  pinMode(potens, INPUT);
  pinMode(butt, INPUT_PULLUP);
}

void butt_check();

void loop() {
  int val;
  if (led && (analogRead(photo)>night) && (digitalRead(dviz)==1)){
    val=analogRead(potens);
    val=map(val,0,1023,0,255);
    val=constrain(val,0, 255);
    analogWrite(shim, val);
    off_delay=millis();
    night=700;
  }
  else{
    if (millis()-off_delay>(10*1000)){
      off_delay=millis();
      analogWrite(shim, 0);
      night=800;
    }
  }
  butt_check();
}
void butt_check(){
  if (digitalRead(butt)==LOW && flag && (millis()-butt_delay>150)){
    butt_delay=millis();
    flag=!flag;
    led=!led;
    analogWrite(shim, 0);
  }
  if (digitalRead(butt)==HIGH && !flag && (millis()-butt_delay>150)){
    butt_delay=millis();
    flag=!flag;
  }
}
