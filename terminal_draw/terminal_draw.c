#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#define HEIGHT 30
#define WIDTH 50
int height=HEIGHT,width=WIDTH,cX=2,cY=HEIGHT-2,stop=0;
int frame[WIDTH][HEIGHT]={0};
int kbhit(void);
char getch(void);
void render(void);
void checkCursorChange(void);
void toggleBit(void);
void generateCode(void);
main()
{
 while(!stop)
 {
  render();
  checkCursorChange();
 }
 generateCode();
 printf("\n\t\tOuput code generated : terminal_draw_output.c\n\n\n");
}

void render(void)
{
 int i,j;
 system("clear");
 for(i=0;i<=height;i++)
 {
  for(j=0;j<=width;j++)
  {
    if(i==0||i==height)
     printf("-");
    else if(j==0||j==width)
     printf("|");
    else if(i==cY&&j==cX)
      printf("+");
    else if(frame[j][i])
      printf("*");
    else
     printf(" ");
  }
  printf("\n");
 }
}

void toggleBit(void)
{
  frame[cX][cY]=!(frame[cX][cY]); 
 //frame[cX][cY]=1; 
}

void checkCursorChange(void)
{
 if(kbhit())
 {
  char ch=getch();
  switch (ch)
  {
   case 'w':
    if(cY!=1)
    cY--;
    break;
   case 'd':
    if(cX!=width-1)
    cX++;
    break;
   case 's':
    if(cY!=height-1)
    cY++;
    break;
   case 'a':
    if(cX!=1)
    cX--;
    break;
   case 'q':
    stop=1;
    break;
    case ' ':
    toggleBit();
  }

 }
}

void generateCode(void)
{
 int i,j;
 FILE *copf;
 copf=fopen("terminal_draw_output.c","w");

 fprintf(copf,
 "#include<stdio.h>\n"
 "main()\n"
 "{\n");
 fprintf(copf,"int frame[%d][%d] = \n {\n",height,width);
 for(i=0;i<height;i++)
 {
  fprintf(copf,"  {");
  for(j=0;j<width;j++)
  {
   j==width-1? fprintf(copf,"%d",frame[j][i]):fprintf(copf,"%d,",frame[j][i]);
  }
  i==height-1?fprintf(copf,"}"):fprintf(copf,"},\n");
 }
 fprintf(copf,"\n };\n");
 fprintf(copf,
 " int i,j,height=%d,width=%d;\n"
 " for(i=0;i<height;i++)\n"
 " {\n"
 "  for(j=0;j<width;j++)\n"
 "  {\n"
 "   (frame[i][j])?printf(\"*\"):printf(\" \");\n"
 "  }\n"
 "  printf(\"\\n\");\n"
 " }\n"
 "}",
 height,
 width
 );
}

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

char getch()
{
    char c;
    system("stty raw");
    c= getchar();
    system("stty sane");
    return(c);
}
