const float refcur = 2.5; //목표전압
const float Kp = 1; //비례게인
const float Ki = 0.1; //적분게인
const float Kd = 0.1; //미분게인

float x; //측정 결과


float dt; //미소시간
float pretime; //1개 전의 시간
float e,int_e,e_dot,pree; 
uint8_t duty = 0; //컨트롤치 0~255
int up = 10; //가로축 작성용
int down = 0; //가로축 작성용

void setup() {
  Serial.begin(9600);
  pinMode(10,OUTPUT);
}

void loop() {
  analogWrite(10,duty); //10번 핀에 pwm으로 duty값 제어

  //이렇게 duty값으로 출력한 전류 값을 다시 A0핀이 읽어들여 변수 x에 저장한다.
  
  for(int i=0;i<1000;i++){
    x+=analogRead(A0); //x의 평균값을 계산하기 위해서 더함.
  }
  x = 5*x/1000/1023; //  5/1023 으로 아날로그 입력(0~1023)을 5볼트로 환산
                     //  1000으로 나눈 이유는 1000번 더했으므로, 평균을 구하기 위함.



  //////////////// PID 제어기 //////////////////
  dt = (micros() - pretime)/1000000;
  pretime = micros();
  
  e = refcur - x;  //오차  
  int_e += e*dt;   //오차의 적분 
  e_dot = (e-pree)/dt; //오차의 미분 
  pree = e; //이전 오차값을 저장하여 다음 루프에서 사용. 

  

  duty += Kp*e+Kd*e_dot+Ki*int_e; //PID계산한 값
  
  Serial.print(x);
  Serial.print(",");
  Serial.print(up);
  Serial.print(",");
  Serial.println(down);

  
}
