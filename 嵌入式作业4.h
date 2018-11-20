/*以按键单击（表示为0），长击（表示为1）为输入，统计连续1出现的状态总共的次数。*/
static int count=0;//count用来保存连续的1
static int num=0;//保存连续1出现的次数
unsigned int t1 = 10;//去抖动时间
unsigned int t2 = 700;//长按时间的阈值
int currentt1=0,currentt2=0;
int key_state=HIGH;

const int Buttonpin = 2;//设置按钮为2号口
unsigned int stateFlag = 0;
//中断处理程序，处理连续的1
void carryOut()
{
	if(key_state==HIGH){
		currentt1=millis();
    }else{
		currentt2=millis()-currentt1;
    }
    key_state=digitalRead(Buttonpin);
	//按钮不按状态
	if(key_state){
		//之前按钮按下过
		if(stateFlag == 1){
			if(currentt2>t2){
				//长击
				if(count==0){
				num++;
				Serial.println(num);
				}
				count++;
			}else if(currentt2<t1){
			//抖动，忽略
			}else{
			//短击
				count=0;
			}
		}
		stateFlag == 0;
	}
	else{
		stateFlag  == 1;
	}
}

void CountContinutionOne(){
  //利用fsm
  if(key_state==HIGH){
    currentt1=millis();
  }else{
    currentt2=millis()-currentt1;
  }
  key_state=digitalRead(Buttonpin);
  if(HIGH==key_state){
    if(currentt2>t2){
      //长击
	  if(count==0){
		num++;
		Serial.println(num);
	  }
      count++;
    }else if(currentt2<t1){
      //抖动，忽略
    }else{
      //短击
      count=0;
    }
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
