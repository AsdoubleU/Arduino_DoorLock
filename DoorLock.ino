#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

#define ROWS 4
#define COLS 4
#define DOOR 7
#define BUZZER 10

int melody[] = {659,622,659,622,659,494,587,523,440};
int op[] = {659,698,784};

char number[4] = {'0','0','0','0'};
char keys[ROWS][COLS] = {
  {'1','2','3','R'},
  {'4','5','6','C'},
  {'7','8','9','N'},
  {'*','0','#','N'}
};

byte rowPins[ROWS] = {24,25,26,27};
byte colPins[COLS] = {23,22,29,28};

Keypad kdp = Keypad( makeKeymap(keys),rowPins,colPins,ROWS,COLS);
LiquidCrystal lcd(12,11,2,3,4,5);

int type_number(char ans[]);
int det_nums(char ans[],char nums[],int count);
int setting(char nums[]);

void setup() {
  int i;
  lcd.begin(16,2);
  lcd.clear();
  pinMode(DOOR,OUTPUT);
  for(i=0;i<9;i++){
    //tone(BUZZER,melody[i],500);
    delay(300);
    noTone(BUZZER);
  }
}

void loop() {
  int i;
  char answer[5];
  int define,count;
  
  define = type_number(answer);

  if(define == 1){
    count = setting(number);
  }
  
  else{
  if(det_nums(answer,number,count) == 1){
    lcd.clear();
    lcd.print("Succed!");
    digitalWrite(DOOR,HIGH);
    delay(200);
    for(i=0;i<3;i++){
      tone(BUZZER,op[i],100);
      delay(100);
      noTone(BUZZER);
    }
    delay(3000);
    digitalWrite(DOOR,LOW);
  }

  else{
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

int det_nums(char ans[],char nums[],int count){
  int i;
  for(i=0;i<4;i++){
    if(ans[i] != nums[i]){
      return 0;
    }
  }
  return 1;
}

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
