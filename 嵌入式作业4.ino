#define NOT_AN_INTERRUPT -1
/*以按键单击（表示为0），长击（表示为1）为输入，统计连续1出现的状态总共的次数。*/
static int count=0;//count用来保存连续的1
static int num=0;//保存连续1出现的次数
unsigned int t1 = 10;//去抖动时间
unsigned int t2 = 700;//长按时间的阈值
int currentt1=0,currentt2=0;
int key_state=HIGH;//HIGH（1）表示未按下状态，LOW（0）表示按下状态
int button_state = 0;//0未按下，1短按，2长按
int state = 0;//0free，1wait，2count
const int Buttonpin = 2;//设置按钮为2号口

//中断处理程序，处理连续的1


void CountContinutionOne(){
  
  if(key_state==HIGH){
    currentt1=millis();
  }else{
    currentt2=millis()-currentt1;
  }
  key_state=digitalRead(Buttonpin);
  if(HIGH==key_state){
    if(currentt2>t2){
      //长击  
		  Serial.print("LONG\n");
		  button_state = 2;
      
    }else if(currentt2<t1){
      //抖动，忽略
    }else{
      //短击
	  Serial.print("SHORT\n");
	  button_state = 1;
      
    }
	
  }
  
  switch(state){
	  case 0: //状态空闲时
		if(button_state == 2){ //遇到第一个长击
			num++;
			Serial.println(num);
			state = 2; //进入计数状态
		}
		break;
	  case 1://等待下一个按击结果
		if(button_state == 1){//遇到短击，等待状态结束，进入空闲状态
			state = 0;
		}
		break;
	  case 2://计数状态时
		if(button_state == 1){//遇到短击就进入空闲状态
			state = 0;
		}
		else //遇到长击进入等待状态，等待连续长击结束
			state = 1;
		break;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Buttonpin,INPUT);
  //Enable中断管脚, 中断服务程序为CountContinutionOne(), 监视引脚变化,当引脚为LOW即按下按钮时，调用中断程序
  attachInterrupt( digitalPinToInterrupt(Buttonpin), CountContinutionOne, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
}

