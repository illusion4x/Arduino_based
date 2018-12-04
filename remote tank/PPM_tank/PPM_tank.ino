#define LMotor_PWM_ENA 3
#define LMotor_INT1 
#define Lmotor_INT2
#define LMorot_PWM_ENB 5
#define Rmotor_INT3
#define Rmotor_INT4

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
  
        Serial.begin(9600);  
    
        
        //PPM inputs from RC receiver
        pinMode(PPM, INPUT); 
      

        // 电平变化即触发中断
        attachInterrupt(0, rc1, CHANGE);    
           
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

void 

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
