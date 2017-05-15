#define Moisture A0 //定义AO 引脚 为 IO-A0  
#define DO 7        //定义DO 引脚 为 IO-7  
  
void setup() {  
  pinMode(Moisture, INPUT);//定义A0为输入模式  
  pinMode(DO, INPUT);  
  Serial.begin(9600);  
}  
  
void loop() {  
  //串口返回测量数据  
  Serial.write(analogRead(Moisture)/4);//读取AO的数值  
  delay(100);  
}  
