#include <LiquidCrystal.h> //申明1602液晶的函数库
#include <dht11.h>
#define DHT11PIN 13
dht11 DHT11;
//申明1602液晶的引脚所连接的Arduino数字端口，8线或4线数据模式，任选其一
LiquidCrystal lcd(12,11,10,9,8,7,6,5,4,3,2);   //8数据口模式连线声明
//LiquidCrystal lcd(12,11,10,5,4,3,2); //4数据口模式连线声明
int i;
int Echo = A5;  
int Trig =A4; 
int Out =10; 
int MQ2=A1;//指定模拟端口A1
int val=0;//声明临时变量
int body_sensor = A0; //指定模拟端口A3

int Distance = 0;

void setup()
{
  Serial.begin(9600);     // 初始化串口
  //初始化超声波引脚
  pinMode(Echo, INPUT);    // 定义超声波输入脚
  pinMode(Trig, OUTPUT);   // 定义超声波输出脚
  pinMode(Out, OUTPUT);   
  lcd.begin(16,2);      //初始化1602液晶工作                       模式
  pinMode(DHT11PIN,OUTPUT);
}


void Distance_test()   // 量出前方距离 
{
  digitalWrite(Trig, LOW);   // 给触发脚低电平2μs
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  // 给触发脚高电平10μs，这里至少是10μs
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);    // 持续给触发脚低电
  float Fdistance = pulseIn(Echo, HIGH);  // 读取高电平时间(单位：微秒)
  Fdistance= Fdistance/58;       //为什么除以58等于厘米，  Y米=（X秒*344）/2
  // X秒=（ 2*Y米）/344 ==》X秒=0.0058*Y米 ==》厘米=微秒/58
  Distance = Fdistance;
}  

void loop()
{
  Distance_test();
  if((2<Distance)&(Distance<400))//超声波测距范围2cm到400cm
  {
    Serial.print("Distance:");      //输出距离（单位：厘米）
    Serial.print(Distance);         //显示距离
    Serial.println("cm");        //显示
    if(Distance>100){
      Serial.println("high");  
      digitalWrite(Out, HIGH);
    }else{
      Serial.println("low"); 
      digitalWrite(Out, LOW);
    }
  }
  else
  {
    Serial.println("!!! Out of range");       //显示超出距离
  }
  val=analogRead(MQ2);//读取A0口的电压值并赋值到val
  Serial.print("MQ2:"); 
  Serial.println(val);//串口发送val值
    lcd.clear();
    lcd.home();        //把光标移回左上角，即从头开始输出   
    lcd.print("Distance:"); //显示
    lcd.print(Distance); //显示
    lcd.setCursor(0,1);   //把光标定位在第1行，第0列
    lcd.print("MQ2:");       //显示
    lcd.print(val);       //显示
  delay(2000);
    
      int chk = DHT11.read(DHT11PIN);
  Serial.print("Tep: ");
  Serial.print((float)DHT11.temperature, 2);
  Serial.println("C");
  Serial.print("Hum: ");
  Serial.print((float)DHT11.humidity, 2);
  Serial.println("%");
  Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);        //把光标移回左上角，即从头开始输出   
    lcd.print("Tep: "); //显示
    lcd.print((float)DHT11.temperature); //显示
    lcd.setCursor(0,1);   //把光标定位在第1行，第0列
    lcd.print("Hum:");       //显示
    lcd.print((float)DHT11.humidity);       //显示
 
  delay(2000);
}


