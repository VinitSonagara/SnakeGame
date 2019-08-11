#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<ctype.h>

#define Rows 20
#define Columns 40

int i,j,Field[Rows][Columns];
int x,y,Head,Tail;
int Gy;// To store the parts of the snake body and get to the approx middle of the matrix. 
int Game;// To exit the game or restart the game.
int Frogs,a,b; // a,b to store the position of Frog in the matrix. 
int var;// To store the character which user enters. 
int dir;// Stores var by which we will change the direction.
int score,HighScore;
int Speed;

FILE *f; // To handle file.

void print(); // To print the field.
void snakeInitialization();
void ResetScreenPosition();
void Random();
int getPressedKey();
void movement();
void TailRemove();
void GameOver();


//Main Function
int main(){
  system("cls");
  snakeInitialization();
  while(Game==0){
     print();
     ResetScreenPosition();
     Random();
     movement();
     TailRemove();
     Sleep(Speed);
  }
  return 0;
}


// Snake Initialization
void snakeInitialization(){
  f = fopen("highScore.txt","r");
  fscanf(f,"%d",&HighScore);
  fclose(f);



  for(i=0;i<Rows;i++){
    for(j=0;j<Columns;j++){
      Field[i][j]=0;
    }
  }

  x=Rows/2;
  y=Columns/2;
  Gy=y;
  Head=5;
  Tail=1;
  Game=0;
  Frogs=0;
  dir='d';
  score=0;
  Speed=99;

  for(i=0;i<Head;i++){
    Gy++;
    Field[x][Gy-Head] = i+1;
  }
}

// To print the field where the snake will be roaming.
void print(){
      // To print 1st row of the field
  for(i=0;i<=Columns+1;i++){
    if(i==0){
      printf("%c",201);
    }
    else if(i==Columns+1){
      printf("%c",187);
    }
    else{
      printf("%c",205);
    }
  }
  printf("Current Score: %d  HighScore: %d",score,HighScore);
   // To go to next line to print the remaining field.
  printf("\n");

   // To print the middle rows of the field.
  for(i=0;i<Rows;i++){
    printf("%c",186);
    for(j=0;j<Columns;j++){
      if(Field[i][j]==0){
        printf(" ");
      }
      if(Field[i][j]>0 && Field[i][j]!=Head){
        printf("%c",176);
      }
      if(Field[i][j]==Head){
        printf("%c",178);
      }
      if(Field[i][j]==-1){
        printf("%c",15);
      }
      if(j==Columns-1){
        printf("%c\n",186);
      }
    }
      // printf("\n");
  }

  // To print last row of the field.
  for(i=0;i<=Columns+1;i++){
    if(i==0){
      printf("%c",200);
    }
    else if(i==Columns+1){
      printf("%c",188);
    }
    else{
      printf("%c",205);
    }
  }
}

// To reset screen position.
void ResetScreenPosition(){
  HANDLE hOut;
  COORD Position;
  hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  Position.X=0;
  Position.Y=0;
  SetConsoleCursorPosition(hOut,Position);

}


// To create random position for Frog.
void Random(){
  srand(time(0));

  a=1+rand()%18;
  b=1+rand()%38;

  if(Frogs==0 && Field[a][b]==0){
    Field[a][b]=-1;
    Frogs=1;
  }
}

// This function return the ascii value of character which is hit otherwise returns -1.
int getPressedKey(){
  if(_kbhit()){  // To set if the key has been pressed or not. Returns non-zero value if key is pressed otherwise returns 0.
    return _getch(); // Returns the pressed character.
  }
  else{
    return -1;
  }
}


// To control the movement of the snake.
void movement(){
  var = getPressedKey(); // var stores the user pressed key.
  var = tolower(var); // To convert to lowercase so not to be worried about whether CapsLock is on or not.

  if( ((var=='d' || var=='a') || (var=='s' || var=='w')) && (abs(dir-var)>5) ){
    dir = var;
  }
   
  // For continuous movement of snake from right side to left side. 
  if(dir == 'd'){
    y++;
    // For GameOver
    if(Field[x][y]!=0 && Field[x][y]!=-1){
      GameOver();
    }
    if(y==Columns-1){
      y=0;
    }
    if(Field[x][y] == -1){
      Frogs=0;
      score = score+5;
      Tail = Tail-2;// For increase in size when snake eats frog.
    }
    Head++;
    Field[x][y] = Head;
  }

  // For continuous movement of snake from left side to right side.
  if(dir == 'a'){
    y--;
    // For GameOver
    if(Field[x][y]!=0 && Field[x][y]!=-1){
      GameOver();
    }
    if(y==0){
      y=Columns-1;
    }
    if(Field[x][y] == -1){
      Frogs=0;
      score = score+5;
      Tail = Tail-2;// For increase in size when snake eats frog. 
    }
    Head++;
    Field[x][y] = Head;
  }

  // For continuous movement of snake from up to down.
  if(dir == 'w'){
    x--;
    // For GameOver
    if(Field[x][y]!=0 && Field[x][y]!=-1){
      GameOver();
    }
    if(x==-1){
      x=Rows-1;
    }
    if(Field[x][y] == -1){
      Frogs=0;
      score = score+5;
      Tail = Tail-2;// For increase in size when snake eats frog.
    }
    Head++;
    Field[x][y] = Head;
  }

  // For continuous movement of snake from down to up.
  if(dir == 's'){
    x++;
    // For GameOver
    if(Field[x][y]!=0 && Field[x][y]!=-1){
      GameOver();
    }
    if(x==Rows){
      x=0;
    }
    if(Field[x][y] == -1){
      Frogs=0;
      score = score+5;
      Tail = Tail-2;// For increase in size when snake eats frog.
    }
    Head++;
    Field[x][y] = Head;
  }
}




// To restart the game or exit the game.
void GameOver(){
  printf("\a");
  Sleep(1500);
  system("cls");// To clear the screen

   
  if(score>HighScore){
    printf("New HighScore %d!!!!!\n\n",score);
    system("pause");
    f = fopen("highScore.txt","w"); // Opens the highScore.txt file.
    fprintf(f,"%d",score); // Copies the score in file and removes the text in the file.
    fclose(f);
  }

  system("cls");
  printf("\n\n\n     Game Over     \n");
  printf("     Score: %d\n\n",score);
  printf("     Press ENTER to play again or ESC to exit.... ");
  
  while(1){
    var = getPressedKey();
    if(var == 13){  // 13 is the ascii character for ENTER. 
      Game = 0;
      snakeInitialization();
      break;
    }
    else if(var == 27){ // 27 is the ascii character for ESC.
      Game = 1;
      break; // To exit the game.
    }
  }   
  system("cls");
}



// To change the tail from fixed size to variable.
void TailRemove(){
  for(i=0;i<Rows;i++){
    for(j=0;j<Columns;j++){
      if(Field[i][j]==Tail){
        Field[i][j]=0;
      }
    }
  }
  Tail++;
}










