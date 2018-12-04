#define LMotor_PWM_ENA 3
#define LMotor_INT1 
#define LMotor_INT2
#define LMorot_PWM_ENB 5
#define RMotor_INT3
#define RMotor_INT4
//asume
#define LMotor_dir 1
#define RMotor_dir 1

#define RMotor

#define PPM 2




unsigned long PPM_last_time;     
volatile int PPM_high_pulse,PPM_channel_cnt,PPM_is_ok;
int PPM_buf[6];
void setup() {
  pinMode(LMotor_PWM_ENA,OUTPUT);
  pinMode(LMotor_INT1,OUTPUT);
  pinMode(LMotor_INT2,OUTPUT);
  
  pinMode(RMotor_PWM_ENB,OUTPUT);
  pinMode(RMotor_INT3,OUTPUT);
  pinMode(Rmotor_INT4,OUTPUT);
  
  pinMode(PPM, INPUT);
  
  Serial.begin(9600);  
  
  attachInterrupt(0, rc1, CHANGE);    
           
}

void stright_move(bool dir,int sped){
  
  if(dir){ 
    digitalWrite(RMotor_INT3,RMotor_dir);//!1 is 0 and !0 is 1 so good may be it is boolen
    digitalWrite(RMotor_INT4,!Rmotor_dir);
    analogWrite(RMotr_PWM_ENB,sped);
    
    digitalWrite(LMotor_INT3,LMotor_dir);
    digitalWrite(LMotor_INT4,!LMotor_dir);
    analogWrite(LMotr_PWM_ENB,sped);
  }
  else{
    digitalWrite(RMotor_INT3,!LMotor_dir);
    digitalWrite(RMotor_INT4,LMotor_dir);
    analogWrite(RMotr_PWM_ENB,sped);
    
    digitalWrite(LMotor_INT3,!LMotor_dir);
    digitalWrite(LMotor_INT4,LMotor_dir);
    analogWrite(LMotr_PWM_ENB,sped);
    }
}

void turn_dir(int mode, bool dir, int sped){
  switch(mode){
    case 0://turn dir situ
       if(dir){
          digitalWrite(RMotor_INT3,!LMotor_dir);
          digitalWrite(RMotor_INT4,LMotor_dir);
          analogWrite(RMotr_PWM_ENB,sped);
          
          digitalWrite(LMotor_INT3,LMotor_dir);
          digitalWrite(LMotor_INT4,!LMotor_dir);
          analogWrite(LMotr_PWM_ENB,sped);
        }
        else{
          digitalWrite(RMotor_INT3,LMotor_dir);
          digitalWrite(RMotor_INT4,!LMotor_dir);
          analogWrite(RMotr_PWM_ENB,sped);
          
          digitalWrite(LMotor_INT3,LMotor_dir);
          digitalWrite(LMotor_INT4,!LMotor_dir);
          analogWrite(LMotr_PWM_ENB,sped);
          }
    case 1:// turn dir like a car
        
    }
  }


void rc1()
{
       if(digitalRead(PPM) == 1){
          PPM_last_time = micros();
        } 
        else{
          PPM_high_pulse = micros()-PPM_last_time;
          
          if(PPM_is_ok == 1){
             PPM_channel_cnt++;
             PPM_buf[PPM_channel_cnt-1] = PPM_high_pulse+300;  
              if(PPM_channel_cnt >6){
               PPM_is_ok = 0;
               }
       }
       if(PPM_high_pulse>=2050){
          PPM_is_ok = 1;
          PPM_channel_cnt = 0;
        }
        }
                
}

void loop() {
    
    if(PPM_is_ok == 0){
    for(int i = 0;i<6;i++){
      Serial.print("channel ");
      Serial.print(i+1);
      Serial.print("  :");
      
      Serial.println(PPM_buf[i]);
      }
    }
    
    
}
