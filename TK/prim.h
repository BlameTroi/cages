#include <stdio.h>

char *G[30][25];

void
load()
{
  int a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y;
/*   char *calloc(); */

  a=0; b=1; c=2; d=3; e=4; f=5; g=6; h=7; i=8; j=9;
  k=10; l=11; m=12; n=13; o=14; p=15; q=16; r=17;
  s=18; t=19; u=20; v=21; w=22; x=23; y=24;

/*   G[5]=calloc(2,sizeof(char *)); */
G[5][a]="(0,1,2,3,4)";
G[5][b]="(0)(1,2,4,3)";

/*   G[6]=calloc(1,sizeof(char *)); */
G[6][a]="(0,5)(1)(2,3)(4)";

/*   G[7]=calloc(3,sizeof(char *)); */
G[7][a]="(0,1,2,3,4,5,6)";
G[7][b]="(0)(1,3,2,6,4,5)";
G[7][c]="(0)(1,2)(3,6)(4)(5)";

/*   G[8]=calloc(4,sizeof(char *)); */
G[8][a]="(0,7)(1,3)(2,6)(4,5)";
G[8][b]="(0,3)(1,7)(2,4)(5,6)";
G[8][c]="(0,6)(1,4)(2,7)(3,5)";
G[8][d]="(0,7)(1,6)(2,3)(4,5)";

/*   G[9]=calloc(6,sizeof(char *)); */
G[9][a]="(0,1,2)(3,4,5)(6,7,8)";
G[9][b]="(0,3,6)(1,4,7)(2,5,8)";
G[9][c]="(0)(1,5,3,8,2,7,6,4)";
G[9][d]="(0)(1)(2)(3,6)(4,7)(5,8)";
G[9][e]="(0)(1,3,8)(2,6,4)(5)(7)";
G[9][f]="(0)(1,6)(2,5)(3,4)(7,8)";

/*   G[10]=calloc(3,sizeof(char *)); */
G[10][a]="(0,7)(1,4,5,2)(3,8,6,9)";
G[10][b]="(0,4,6)(1,8,3)(2,7,9)(5)";
G[10][c]="(0,9)(1)(2)(3,6)(4,5)(7,8)";

/*   G[11]=calloc(4,sizeof(char *)); */
G[11][a]="(0,1,2,3,4,5,6,7,8,9,10)";
G[11][b]="(0)(1,2,4,8,5,10,9,7,3,6)";
G[11][c]="(0,10)(1,6)(2,4)(3,5)(7)(8)(9)";
G[11][d]="(0)(1)(2)(3,7)(4,8)(5,6)(9,10)";

/*   G[12]=calloc(3,sizeof(char *)); */
G[12][a]="(0,11)(1,10)(2,5)(3,7)(4,8)(6,9)";
G[12][b]="(0)(1,4)(2,5)(3,6)(7)(8)(9)(10,11)";
G[12][c]="(0)(1)(2)(3,6)(4,7)(5,8)(9)(10,11)";

/*   G[13]=calloc(3,sizeof(char *)); */
G[13][a]="(0,1,2,3,4,5,6,7,8,9,10,11,12)";
G[13][b]="(0)(1,2,4,8,3,6,12,11,9,5,10,7)";
G[13][c]="(0)(1,2)(3)(4,9)(5)(6,10)(7)(8,11)(12)";

/*   G[14]=calloc(1,sizeof(char *)); */
G[14][a]="(0,13)(1,12)(2,6)(3,4)(5)(7,11)(8)(9,10)";

/*   G[15]=calloc(5,sizeof(char *)); */
G[15][a]="(0,14,6,4,11)(1,8,12,13,7)(2,5,9,10,3)";
G[15][b]="(0,3,4)(1,7,9)(2,11,14)(5,12,10)(6,8,13)";
G[15][c]="(0,6)(1,10)(2,11)(3,12)(4,9)(5)(7,13)(8)(14)";
G[15][d]="(0,8,4,13,12,1,5)(2,14,3,6,7,11,10)(9)";
G[15][e]="(0,2,1)(3,7,11)(4,10,13)(5,8,14)(6,9,12)";

/*   G[16]=calloc(11,sizeof(char *)); */
G[16][a]="(0,15)(1,2)(3,4)(5,6)(7,8)(9,10)(11,12)(13,14)";
G[16][b]="(0,2)(1,15)(3,5)(4,6)(7,9)(8,10)(11,13)(12,14)";
G[16][c]="(0,4)(1,5)(2,6)(3,15)(7,11)(8,12)(9,13)(10,14)";
G[16][d]="(0,8)(1,9)(2,10)(3,11)(4,12)(5,13)(6,14)(7,15)";
G[16][e]="(0,11,6,4)(1,3,12,10)(2,7,9,13)(5,8)(14)(15)";
G[16][f]="(0,2,1)(3,11,7)(4,14,9)(5,12,10)(6,13,8)(15)";
G[16][g]="(0)(1,2)(3)(4)(5,6)(7,11)(8,12)(9,14)(10,13)(15)";
G[16][h]="(0,14)(1,11)(2)(3,9)(4)(5)(6,8)(7)(10)(12)(13)(15)";
G[16][i]="(0,6)(1,11)(2,10)(3,9)(4,12)(5)(7)(8,14)(13)(15)";
G[16][j]="(0,13)(1,12)(2)(3,10)(4)(5)(6,7)(8)(9)(11)(14)(15)";
G[16][k]="(0,2)(1)(3,7)(4,10)(5,9)(6,8)(11)(12,14)(13)(15)";

/*   G[17]=calloc(3,sizeof(char *)); */
G[17][a]="(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16)";
G[17][b]="(0)(1,3,9,10,13,5,15,11,16,14,8,7,4,12,2,6)";
G[17][c]="(0)(1,2)(3,8)(4,6)(5,7)(9,13)(10,12)(11,14)(15,16)";

/*   G[18]=calloc(1,sizeof(char *)); */
G[18][a]="(0,17)(1)(2,9)(3,6)(4,13)(5,7)(8,15)(10,12)(11,14)(16)";

/*   G[19]=calloc(2,sizeof(char *)); */
G[19][a]="(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18)";
G[19][b]="(0)(1,2,4,8,16,13,7,14,9,18,17,15,11,3,6,12,5,10)";

/*   G[20]=calloc(1,sizeof(char *)); */
G[20][a]="(0,19)(1,18)(2,9)(3,6)(4,14)(5,15)(7,8)(10,17)(11,12)(13,16)";

/*   G[21]=calloc(9,sizeof(char *)); */
G[21][a]="(0,1,2,3,4,5,6)(7,8,9,10,11,12,13)(14,15,16,17,18,19,20)";
G[21][b]="(0)(1)(2)(3,7,14)(4,8,15)(5,17,10)(6,20,13)(9,11,19)(12,18,16)";
G[21][c]="(0,1,2)(3,4,6)(5)(7,8,20)(9,11,19)(10)(12,16,18)(13,14,15)(17)";
G[21][d]="(0)(1)(2)(3)(4)(5)(6)(7,14)(8,15)(9,16)(10,17)(11,18)(12,19)(13,20)";
G[21][e]="(0)(1)(2)(3,14,7)(4)(5,18,11)(6,20,13)(8)(9,10,12)(15)(16,19,17)";
G[21][f]="(0)(1,7)(2)(3)(4)(5)(6,13)(8,14)(9)(10)(11)(12,19)(15,18)(16)(17)(20)";
G[21][g]="(0,1,7)(2,14,8)(3)(4)(5)(6,13,20)(9,18,15)(10)(11)(12,19,16)(17)";
G[21][h]="(0)(1,2,4,3,6,10,15,17)(5,8,14,16,20,18,13,19)(7,12,9,11)";
G[21][i]="(0,1,6)(2,3,7,17,10,11)(4,5,20,15,16,19)(8,9,18,14,12,13)";

/*   G[22]=calloc(1,sizeof(char *)); */
G[22][a]="(0,21)(1)(2)(3)(4,5)(6)(7,14)(8,10)(9,19)(11)(12,16)(13,20)(15,17)(18)";

/*   G[23]=calloc(3,sizeof(char *)); */
G[23][a]="(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22)";
G[23][b]="(0,4,1,9,3,19,7,16,15,10,8,21,17,20,12,18,2,14,5,6,11,13)(22)";
G[23][c]="(0)(1)(2,16,9,6,8)(3,12,13,18,4)(5)(7,17,10,11,22)(14,19,21,20,15)";

/*   G[24]=calloc(1,sizeof(char *)); */
G[24][a]="(0,23)(1,22)(2,11)(3,15)(4,17)(5,9)(6,19)(7,13)(8,20)(10,16)(12,21)(14,18)";

/*   G[25]=calloc(9,sizeof(char *)); */
G[25][a]="(0,1,2,3,4)(5,6,7,8,9)(10,11,12,13,14)(15,16,17,18,19)(20,21,22,23,24)";
G[25][b]="(0,5,10,15,20)(1,6,11,16,21)(2,7,12,17,22)(3,8,13,18,23)(4,9,14,19,24)";
G[25][c]="(0,1)(2)(3)(4)(5,6)(7)(8)(9)(10,11)(12)(13)(14)(15,16)(17)(18)(19)(20,21)(22)(23)(24)";
G[25][d]="(0,5)(1,6)(2,7)(3,8)(4,9)(10)(11)(12)(13)(14)(15)(16)(17)(18)(19)(20)(21)(22)(23)(24)";
G[25][e]="(9,21)(1,5)(2,10)(3,15)(4,20)(6)(7,11)(8,16)(13,17)(14,22)(19,23)";
G[25][f]="(0)(1,8,6,20,13,23,2,11,12,15,21,16,4,22,24,5,17,7,3,19,18,10,9,14)";
G[25][g]="(0)(1,13,16)(2,21,7)(3,9,23)(4,17,14)(5,6,19)(8,10,12)(11,20,24)(15,18,22)";
G[25][h]="(0)(1)(2)(3)(4)(5,10,20,15)(6,11,21,16)(7,12,22,17)(8,13,23,18)(9,14,24,19)";
G[25][i]="(0)(1)(2)(3)(4)(5,6,7,8,9)(10,12,14,11,13)(15,18,16,19,17)(20,24,23,22,21)";

/*   G[26]=calloc(1,sizeof(char *)); */
G[26][a]="(0,25)(1)(2,3)(4)(5,15)(6,9)(7,11)(8,14)(10,20)(12,17)(13,18)(16,22)(19,23)(21,24)";

/*   G[27]=calloc(15,sizeof(char *)); */
G[27][a]="(0,1,2)(3,4,5)(6,7,8)(9,10,11)(12,13,14)(15,16,17)(18,19,20)(21,22,23)(24,25,26)";
G[27][b]="(0,3,6)(1,4,7)(2,5,8)(9,12,15)(10,13,16)(11,14,17)(18,21,24)(19,22,25)(20,23,26)";
G[27][c]="(0,9,18)(1,10,19)(2,11,20)(3,12,21)(4,13,22)(5,14,23)(6,15,24)(7,16,25)(8,17,26)";
G[27][d]="(0)(1,3,9,4,12,13,16,25,20,5,15,22,11)(2,6,18,8,24,26,23,14,10,7,21,17,19)";
G[27][e]="(0)(1,2)(3)(4,5)(6)(7,8)(9)(10,11)(12)(13,14)(15)(16,17)(18)(19,20)(21)(22,23)(24)(25,26)";
G[27][f]="(0)(1)(2)(3,6)(4,7)(5,8)(9)(10)(11)(12,15)(13,16)(14,17)(18)(19)(20)(21,24)(22,25)(23,26)";
G[27][g]="(0)(1)(2)(3)(4)(5)(6)(7)(8)(9,18)(10,19)(11,20)(12,21)(13,22)(14,23)(15,24)(16,25)(17,26)";
G[27][h]="(0)(1,3)(2,6)(4)(5,7)(8)(9)(10,12)(11,15)(13)(14,16)(17)(18)(19,21)(20,24)(22)(23,25)(26)";
G[27][i]="(0)(1,9)(2,18)(3)(4,12)(5,21)(6)(7,15)(8,24)(10)(11,19)(13)(14,22)(16)(17,25)(20)(23)(26)";
G[27][j]="(0)(1)(2)(3,4,5)(6,7,8)(9,16,13)(10,17,14)(11,15,12)(18,23,26)(19,21,24)(20,22,25)";
G[27][k]="(0,26)(1)(2,3)(4,5)(6,9)(7,10)(8,11)(12,16)(13,17)(14)(15)(18,21)(19)(20)(22)(23,25)(24)";
G[27][l]="(0)(1)(2,4)(3,5)(6,10)(7,9)(8,12)(11,16)(13,18)(14)(15)(17,21)(19,20)(22,24)(23)(25)(26)";
G[27][m]="(0,25,24)(1)(2)(3,6,9)(4,7,10)(5)(8,13,17)(11)(12)(14)(15)(16,21,18)(19)(20)(22,26,23)";
G[27][n]="(0)(1,2)(3)(4)(5,14)(6)(7)(8)(9)(10)(11,19)(12)(13)(15)(16,22)(17)(18,23)(20)(21,26)(24)(25)";
G[27][o]="(0)(1)(2)(3)(4,8)(5,11)(6)(7,13)(9)(10,17)(12)(14,19)(15,20)(16)(18)(21)(22)(23)(24)(25)(26)";

/*   G[28]=calloc(18,sizeof(char *)); */
G[28][a]="(0,1,2,5,7,9,4)(3,6,12,17,11,15,19)(8,13,16,20,22,26,24)(10,14,18,21,23,25,27)";
G[28][b]="(0)(1,2,7)(3,8,10)(4,9,5)(6,16,23)(11,13,18)(12,22,14)(15,20,27)(17,24,25)(19,26,21)";
G[28][c]="(0)(1,3)(2,10)(4,11)(5,13)(6,17)(7,8)(9,18)(12)(14,22)(15,20)(16,25)(19,26)(21)(23,24)(27)";
G[28][d]="(0)(1,4)(2,9)(3,11)(5,7)(6,17)(8,13)(10,18)(12)(14)(15,19)(16,24)(20,26)(21,27)(22)(23,25)";
G[28][e]="(0,1,2,6,5,8,4)(3,7,12,16,18,23,27)(9,13,22,25,20,24,26)(10,14,21,17,19,11,15)";
G[28][f]="(0)(1,3)(2,9)(4,10)(5,11)(6,13)(7,17)(8,18)(12,19)(14)(15,25)(16,22)(20,23)(21,26)(24)(27)";
G[28][g]="(0)(1,4)(2,8)(3,12)(5,6)(7)(9,20)(10,19)(11,15)(13,25)(14,17)(16,27)(18,23)(21)(22)(24,26)";
G[28][h]="(0)(1,5,2)(3,11,9)(4,6,8)(7,21,22)(10,13,18)(12,15,20)(14,24,27)(16,17,26)(19,25,23)";
G[28][i]="(0)(1)(2,3)(4,25,19,16,7,13,10,22)(5,27,20,18,8,15,11,24)(6,26,21,17,9,14,12,23)";
G[28][j]="(0)(1,4,7)(2,5,8)(3,6,9)(10,15,17)(11,13,18)(12,14,16)(19,23,27)(20,24,25)(21,22,26)";
G[28][k]="(0,1)(2,3)(4,7)(5,23)(6,15)(8,17)(9,27)(10,19)(11,14)(12,18)(13)(16)(20,26)(21,24)(22)(25)";
G[28][l]="(0)(1)(2,3)(4)(5,6)(7)(8,9)(10,19)(11,21)(12,20)(13,22)(14,24)(15,23)(16,25)(17,27)(18,26)";
G[28][m]="(0,27)(1,2)(3,19)(4,21)(5,24)(6,11)(7,12)(8,15)(9,17)(10,13)(14,16)(18,22)(20,26)(23,25)";
G[28][n]="(0,8,16,24,21,14,7)(1,2,3,4,5,6,15)(9,10,11,12,13,22,23)(17,18,19,20,25,26,27)";
G[28][o]="(0,1,8)(2,16,9)(3)(4)(5)(6)(7,15,23)(10,24,17)(11)(12)(13)(14,22,26)(18,21,25)(19)(20)(27)";
G[28][p]="(0,1,2,3,4,5,6,7)(8,9,10,11,12,13,14,15)(16,17,18,19,20,21,22,23)(24,25,26,27)";
G[28][q]="(0)(1,8)(2)(3)(4)(5)(6)(7,15)(9,16)(10)(11)(12)(13)(14,22)(17,24)(18)(19)(20)(21,25)(23)(26)(27)";
G[28][r]="(0,26)(1,27)(2)(3)(4)(5)(6)(7)(8)(9)(10)(11)(12)(13)(14,15)(16)(17)(18)(19,20)(21)(22,24)(23,25)";

/*   G[29]=calloc(2,sizeof(char *)); */
G[29][a]="(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28)";
G[29][b]="(0)(1,2,4,8,16,3,6,12,24,19,9,18,7,14,28,27,25,21,13,26,23,17,5,10,20,11,22,15)";

/*   G[30]=calloc(1,sizeof(char *)); */
G[30][a]="(0,29)(1,28)(2,14)(3,19)(4,7)(5,23)(6,24)(8,18)(9,16)(10,26)(11,21)(12)(13,20)(15,27)(17)(22,25)";
}
