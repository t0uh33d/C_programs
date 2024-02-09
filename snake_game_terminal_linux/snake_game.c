#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<termios.h>
 //cobra
 int cabecax, cabecay;
 int corpox[324], corpoy[324];
 char cabeca = 'O', corpo = 'o';

 //fruta
 int frutax, frutay;
 char fruta = '@';

//paramentros
int altura = 20, largura = 20,tamanho = 0, score = 0, speed = 100000, direcao = 2;

//fim de jogo
int fimdejogo = 0;

 int lerinteiro() {
    int numero;
    char buffer[100];
    while (1) {
        fgets(buffer, sizeof(buffer), stdin); // Lê uma linha de entrada
        if (sscanf(buffer, "%d", &numero) == 1) { // Verifica se foi lido um número inteiro
            return numero;
        } else {
            return 10;
        }
    }
}

char getch(void)
{
    char c;
    system("stty raw");
    c= getchar();
    system("stty sane");
    return(c);
}

int menu(exit)
 {
    int option = 5;
    while (option > 3)
    {
    system("clear");
    printf("BEM VINDO AO JOGO DA COBRINHA DO LINUX\n\n");
    printf("ESCOLHA SUA OPÇÃO: \n\n");
    //opções
    printf("1 - COMEÇAR A JOGAR\n");
    printf("2 - CONTROLES\n");
    printf("0 - SAIR\n");
    
        option = lerinteiro();
    
    switch (option)
    {
    case 1:
       
        break;
    case 2:
        system("clear");
        printf("\n\n\n CONTROLES: \n W: CIMA. \n A: ESQUERDA. \n S: BAIXO. \n D: DIREITA. \n\n\n ");
        system("read -p \"PRESSIONE ENTER PARA VOLTAR AO MENU INICIAL\" continue ");

        option = 5;
        break;
    case 0:
        exit = 1;
        return exit;

        break;
    default:
        option = 5;
        break;
    }

    }
    return 0;
 }

void colocafruta(void)
{ 
    resetfruitX:
    frutax = rand() % (largura - 2) + 2; // Posição aleatória dentro da área de jogo, excluindo as bordas
    resetfruitY:
    frutay = rand() % (altura - 2) + 2; // Posição aleatória dentro da área de jogo, excluindo as bordas

    // Verificar se a fruta está sobreposta ao corpo da cobra
    for (int i = 0; i < tamanho; i++) {
        if (frutax == corpox[i] && frutay == corpoy[i]) {
            goto resetfruitX; // Se estiver sobreposta, reposicione a fruta e verifique novamente
        }
    }
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

void render(void)
{
 system("clear");
 int i,j,k,p;
 for(j=0;j<=altura;j++)
 {
  for(i=0;i<=largura;i++)
  {
    p=1;
    if(i==0||j==0||j==altura||i==largura)
      printf("X");
    else if(i==frutax&&j==frutay)
      printf("%c", fruta);
    else if(i==cabecax&&j==cabecay)
      printf("%c", cabeca);
    else
    {
     for(k=0;k<tamanho;k++)
     {
      if(i==corpox[k] && j==corpoy[k])
      {
       printf("%c", corpo);
       p=0;
      }
     }
      if(p)
      printf(" ");
    }
  }
  printf("\n");
 }
 printf("Score : %5d",score);
}

void temfruta(void)
{
 if(cabecax==frutax && cabecay==frutay)
 {
  score+=10;
  tamanho++;
  if(speed>50000)
  speed-=500;
  colocafruta();
 }
}

void inputCheck(void)
{
 if(kbhit())
 {
  char key=getch();
  switch (key)
  {
   case 'w':
    if(direcao!=3)
    direcao=1;
    break;
   case 'd':
    if(direcao!=4)
    direcao=2;
    break;
   case 's':
    if(direcao!=1)
    direcao=3;
    break;
   case 'a':
    if(direcao!=2)
    direcao=4;
  }
 }
}

void moveSnake(void)
{
 int x1,x2,y1,y2,i;
 if(tamanho==1)
 {
  corpox[0]=cabecax;
  corpoy[0]=cabecay;
 }
 else
 {
  x1=cabecax;
  y1=cabecay;
  for(i=0;i<tamanho;i++)
  {
   x2=corpox[i];
   y2=corpoy[i];
   corpox[i]=x1;
   corpoy[i]=y1;
   x1=x2;
   y1=y2;
  }
 }
 switch (direcao)
 {
   case 1:
    cabecay--;
    break;
   case 2:
    cabecax++;
    break;
   case 3:
    cabecay++;
    break;
   case 4:
    cabecax--;
 }
}

void gameOverCheck(void)
{
 int i;
 for(i=1;i<tamanho;i++)
 {
  if(cabecax==corpox[i] && cabecay==corpoy[i])
    fimdejogo=1;
 }
 if(cabecax==largura||cabecax==0||cabecay==altura||cabecay==0)
   fimdejogo=1;
  if(tamanho == 324)
    fimdejogo=1;
}




//-------------------------------------------------------------------------------------------------------------------------------------------------------------
 int main()
 {
    int exit = 0;
    if(menu(exit) == 1)
    {
        return 0;
    }
    //condições iniciais.
    cabecax = 1;
    cabecay = 1;

  colocafruta();
  while(!fimdejogo)
  {
   render();
   inputCheck();
   moveSnake();
   temfruta();
   gameOverCheck();
   usleep(speed);
  }
  usleep(speed);
  system("clear");
  printf("\n\n\n\n\t\t\tScore : %5d\n\n\t\t\tOBRIGADO POR JOGAR!!\n\n\n\n",score);
  while(!kbhit());
    return 0;
 }


