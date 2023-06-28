/* 
GND               GND
5V                VCC
A2                SIG
*/
int r=11;
int g=9;
int b=10;           //r,g,b分别代表红色，绿色，蓝色，把相应的输出连接到PWM接口上
int j;
const int GSR=A2;
int threshold=0;
int sensorValue;

  void setup(){
 pinMode(r,OUTPUT);
 pinMode(g,OUTPUT);
 pinMode(b,OUTPUT);
 j=0;


  long sum=0;
  Serial.begin(9600);
  for(int i=0;i<500;i++)
  {
  sensorValue=analogRead(GSR);
  sum += sensorValue;
  delay(5);
  }                     //测量500次人体在某一时刻下的电阻值，并对其进行累加求和
  threshold = sum/500;   //用500次的电阻值的平均值作为该情绪的代表值
   Serial.print("threshold =");  
   Serial.println(threshold);   //输出某一情绪的代表电阻值
  }

  void color(int red,int green,int blue)  //各个参数范围为0~255，值不要超过255.
{
  analogWrite(r,red);
  analogWrite(g,green);
  analogWrite(b,blue);
  }

void loop(){
  long sum=0;
  sensorValue=analogRead(GSR);
  if(!sensorValue)                 //检测是否中途换人测量
  {
    for(int i=0;i<500;i++)
  {
  sensorValue=analogRead(GSR);
  sum += sensorValue;
  delay(5);
  }               
   threshold = sum/500;   
   Serial.println("The detected object is changed"); 
   Serial.print("threshold=");  
   Serial.println(threshold);   //输出新的受测对象的某一情绪的代表电阻值
    }
    
  int temp;                   //设置一个临时变量
  sensorValue=analogRead(GSR);
  Serial.print("sensorValue=");
  Serial.println(sensorValue);
  delay(300);
  temp = threshold - sensorValue;
  if((abs(temp)<50))
  {
    if (j==0){
    color(255,0,0);//红色
    delay(200);
    color(255,255,255);//白色
    delay(200);}                  //模式1
    
    else if (j==1){
    color(0,0,255);//蓝色
    delay(200);
    color(0,255,0);//绿色
    delay(200);}                 //模式2
    
     else if (j==2){
    color(255,128,0);//橙色
    delay(200);
    color(255,0,255);//紫色
    delay(200);}                //模式3
    
    else if (j==3){
    color(255,0,0);//红色
    delay(200);
    color(255,255,0);//黄色
    delay(200);}                 //模式4
    }                            
    else if(abs(temp)>=50){     //判断工作于哪种模式,情绪变化情况1
      if(j==3){
    Serial.print("sensorValue=");
    Serial.println(sensorValue);
    Serial.println("Emotion Changes Detected!"); 
      j=0;
     long add=0;
    for(int i=0;i<500;i++)
  {
  sensorValue=analogRead(GSR);
  add += sensorValue;
  delay(5);
  }               
   threshold = add/500;   
    Serial.print("threshold = ");  
   Serial.println(threshold);   //输出情绪变化后的新的阈值
    }else if(j<3){                    //判断工作于哪种模式,情绪变化情况2
      j=j+1;
    Serial.print("sensorValue=");
    Serial.println(sensorValue);
    Serial.println("Emotion Changes Detected!");
     long add=0;
    for(int i=0;i<500;i++)
  {
  sensorValue=analogRead(GSR);
  add += sensorValue;
  delay(5);
  }               
   threshold = add/500;   
    Serial.print("threshold = ");  
   Serial.println(threshold);   //输出情绪变化后的新的阈值
    }
  }
}
 
