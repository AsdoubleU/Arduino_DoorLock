#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

#define ROWS 4
#define COLS 4
#define DOOR 7
#define BUZZER 10

int melody[] = {659,622,659,622,659,494,587,523,440}; //실행 시 엘리제를 위하여 멜로디 
int op[] = {659,698,784}; // 올바른 비밀전호를 입력했을 떄의 음.

char number[4] = {'0','0','0','0'}; //초기 비밀번호를 전역변수로 설정.
char keys[ROWS][COLS] = {
  {'1','2','3','R'},
  {'4','5','6','C'},
  {'7','8','9','N'},
  {'*','0','#','N'}
}; //키패드 배치 설정 

byte rowPins[ROWS] = {24,25,26,27};
byte colPins[COLS] = {23,22,29,28};

Keypad kdp = Keypad( makeKeymap(keys),rowPins,colPins,ROWS,COLS); //키패드 초기설정 
LiquidCrystal lcd(12,11,2,3,4,5); // LCD 초기설정 

int type_number(char ans[]); //비밀번호 입력 함수 
int det_nums(char ans[],char nums[],int count); // 비밀번호 판단 함수 
int setting(char nums[]); // 비밀번호 변경 함수 

void setup() {
  int i;
  lcd.begin(16,2);
  lcd.clear();
  pinMode(DOOR,OUTPUT);
  for(i=0;i<9;i++){
    tone(BUZZER,melody[i],500); //실행 시 멜로디 연주 한 번 해줌 
    delay(300);
    noTone(BUZZER);
  }
}

void loop() {
  int i;
  char answer[5]; //내가 입력한 비밀번호 
  int define,count;
  
  define = type_number(answer); //비밀번호 입력 시 리셋 버튼을 눌렀는지 안 눌렀는지 판단. 

  if(define == 1){//리셋 버튼 눌렀다면, 비밀번호 설정 모드로 돌입.
    count = setting(number);
  }
  
  else{ //리셋 버튼이 아니라, 비밀번호를 입력했다면 이를 비교 후 문을 열거나 닫음.
  if(det_nums(answer,number,count) == 1){
    lcd.clear();
    lcd.print("Succeed!");
    digitalWrite(DOOR,HIGH);
    delay(200);
    for(i=0;i<3;i++){
      tone(BUZZER,op[i],100);
      delay(100);
      noTone(BUZZER);
    }
    delay(3000);
    digitalWrite(DOOR,LOW); // 성공시 문을 열고 succeed! 출력 
  }

  else{ // 실패시 틀렸다는 문구와 함께 틀렸다는 음 출력 
    lcd.clear();
    lcd.print("Wrong Number!");
    delay(200);
    tone(BUZZER,1047,200);
    delay(1000);
    noTone(BUZZER);
    delay(500);
  }
  }
  
}

//입력 함수. 리셋 키를 누르면 1을 출력 , 그 외에 버튼을 누르고 *키를 누르면 비밀번호를 바꾸며 0을 출
int type_number(char answer[]){ 
  int count = 0;
  lcd.clear();

  lcd.print("Type the number!");
  lcd.setCursor(0,1);
  
  while(count != 100){
    char key = kdp.getKey();
    if(key){
      if(key == 'R'){
        tone(BUZZER,831,100);
        delay(100);
        noTone(BUZZER);
        return 1;
        }
        else{
          lcd.print(key);
          tone(BUZZER,831,100);
          delay(100);
          noTone(BUZZER);
          answer[count] = key;
          count++;
          if(key == '*'){
            
            return 0;
          }
          }
    }
  }
  
  return 0;
}

//입력 함수. 리셋 키를 누르면 1을 출력 , 그 외에 버튼을 누르고 *키를 누르면 비밀번호를 바꾸며 0을 출력
int det_nums(char ans[],char nums[],int count){
  int i;
  for(i=0;i<4;i++){
    if(ans[i] != nums[i]){
      return 0;
    }
  }
  return 1;
}

//비밀번호 재설정 함수. *을 누를 때까지 숫자를 계속 입력할 수 있다. 
int setting(char nums[]){
  int count = 0;
  lcd.clear();
  lcd.print("Changing numbers");
  lcd.setCursor(0,1);
  for(;;){
    char key = kdp.getKey();
    if(key){
      if(key == '*'){
        tone(BUZZER,831,100);
        delay(100);
        noTone(BUZZER);
        return count;
      }
      else{
        lcd.print(key);
        tone(BUZZER,831,100);
        delay(100);
        noTone(BUZZER);
        nums[count] = key;
        count++;
      }
    }
  }
}
