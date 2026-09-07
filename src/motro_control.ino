int m_pin = 5;
int valve = 7;
int e_btn = 2;
int current_speed= 0;
void setup() {
  pinMode(m_pin,OUTPUT);
  pinMode(valve,OUTPUT);
  pinMode(e_btn,INPUT_PULLUP);
  analogWrite(m_pin,0);
  digitalWrite(valve,HIGH); 
  
  Serial.begin(9600);
  Serial.println("serial monitor initialized");
  Serial.println("type in format speed pwm value");
}



void loop() {
  // put your main code here, to run repeatedly:
 if(Serial.available()>0){
  String cmd = Serial.readStringUntil('\n');
  cmd.trim();  
  processCmd(cmd);
  
 }
}

void processCmd(String command){
  command.toUpperCase();
  int index = command.indexOf(' ');
  if (index != -1){
  int value = command.substring( index+1).toInt();
  current_speed = constrain(value,0,255);
  analogWrite(m_pin,current_speed);
 

  }
  else if (command.equals("STOP")){
    analogWrite(m_pin,0);
    Serial.println("motor stopped");
  }
  else if (command.equals("E_STOP")){
    analogWrite(m_pin,0);
    Serial.println("motor stopped");
    digitalWrite(valve,LOW);
    Serial.println("interrupted the process");
  }
  else{
    Serial.println("error occured");
    Serial.println("try in correct format");
  }
}