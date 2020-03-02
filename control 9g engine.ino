//UART send 1~9==>20~180 degree
#include <SoftwareSerial.h>
SoftwareSerial
softSerial(7, 8); //7为RX, 8为TX
int servopin=10;//设置舵机驱动脚到数字口9
int myangle;//定义角度变量
int pulsewidth;//定义脉宽变量
int k,val;
void servopulse(int servopin,int myangle)/*定义一个脉冲函数，用来模拟方式产生PWM值*/
{
  pulsewidth=(myangle*11)+500;//将角度转化为500-2480 的脉宽值
  digitalWrite(servopin,HIGH);//将舵机接口电平置高
  delayMicroseconds(pulsewidth);//延时脉宽值的微秒数
  digitalWrite(servopin,LOW);//将舵机接口电平置低
  delay(20-pulsewidth/1000);//延时周期内剩余时间
}
void setup()
{
  pinMode(servopin,OUTPUT);//设定舵机接口为输出接口
  Serial.begin(9600);//设置波特率为9600
  softSerial.begin(9600); //设定软串口波特率
  Serial.println("servo=o_seral_simple ready" ) ;
}
void loop()
{
	  //如果HC-06发来数据
      k = softSerial.read(); //读取1个字节的数据
	   if(k>0&&k<=9)
	   val = k;//读取串口收到的数据
	if(val>0&&val<=9)//判断收到数据值是否符合范围
	{
		val=val*(180/9);//将数字转化为角度，例9*（180/9）=180
		Serial.print("moving servo to ");
		Serial.print(val,DEC);
		Serial.println();
		for(int i=0;i<=50;i++) //产生PWM个数，等效延时以保证能转到响应角度
		{
			servopulse(servopin,val);//模拟产生PWM
		}
	}
}
