#include <stdio.h>
#include <math.h>

#define h 40 // hidden layer의 개수
#define e 2.7182818 // 자연대수 e의 정의
#define inbias 1 // bias element 정의
#define hibias 1 // bias element 정의

double sigmoid(double x){ // 시그모이드 함수
  return 1 / (1 + 1 / pow(e, x));
}

double sigmoid2(double x){ // 미분한 시그모이드 함수
  return (2e-1) / pow(pow(e, 2) - x + 1, 2);
}

int main(){
  int ip[10][10]; // input
  int ipip[100]; // input을 1차원으로 표현한 것.

  double op[10]; // output
  double op_ink[10];

  double hl[h]; // hidden layer
  double hl_inj[h];

  double v[100][h]; // 가중치 v
  double vCT[100][h]; // 가중치 v에 대한 보정항

  double w[h][10]; // 가중치 w
  double wCT[h][10]; // 가중치 w에 대한 보정항

  float a = 5; // 학습률

  double deltaK[10]; // 보정항을 구하기 위한 델타값
  double deltaJ[h]; // 보정항을 구하기 위한 델타값
  double delta_inj[h][10];
  double targetP = 5; // target value (이미 알고있는 값)

  int i, j, k; // 반복문

  k = 0;

  int count = 50; // step1 ~ step6을 도는 횟수
  double sum = 0;
  int result1, result2; // 최종결과물

  for (i = 0; i < 10; i++){ // 전부 0으로 초기화
    op[i] = 0;

    for (j = 0; j < 10; j++)
        ip[i][j] = 0;
  }

  for (i = 0; i < h; i++){
      hl[i] = 0;
  }



//############################ input 초기화 ###############################

ip[0][0] = 0; ip[0][1] = 0; ip[0][2] = 1; ip[0][3] = 1; ip[0][4] = 1; ip[0][5] = 1; ip[0][6] = 1; ip[0][7] = 1; ip[0][8] = 0; ip[0][9] = 0;

ip[1][0] = 0; ip[1][1] = 1; ip[1][2] = 1; ip[1][3] = 0; ip[1][4] = 0; ip[1][5] = 0; ip[1][6] = 0; ip[1][7] = 0; ip[1][8] = 0; ip[1][9] = 0;

ip[2][0] = 0; ip[2][1] = 0; ip[2][2] = 1; ip[2][3] = 1; ip[2][4] = 1; ip[2][5] = 1; ip[2][6] = 1; ip[2][7] = 1; ip[2][8] = 0; ip[2][9] = 0;

ip[3][0] = 0; ip[3][1] = 0; ip[3][2] = 1; ip[3][3] = 0; ip[3][4] = 0; ip[3][5] = 0; ip[3][6] = 0; ip[3][7] = 1; ip[3][8] = 0; ip[3][9] = 0;

ip[4][0] = 0; ip[4][1] = 0; ip[4][2] = 0; ip[4][3] = 0; ip[4][4] = 0; ip[4][5] = 0; ip[4][6] = 0; ip[4][7] = 1; ip[4][8] = 0; ip[4][9] = 0;

ip[5][0] = 0; ip[5][1] = 0; ip[5][2] = 0; ip[5][3] = 0; ip[5][4] = 0; ip[5][5] = 0; ip[5][6] = 0; ip[5][7] = 1; ip[5][8] = 0; ip[5][9] = 0;

ip[6][0] = 0; ip[6][1] = 0; ip[6][2] = 0; ip[6][3] = 0; ip[6][4] = 0; ip[6][5] = 0; ip[6][6] = 0; ip[6][7] = 1; ip[6][8] = 0; ip[6][9] = 0;

ip[7][0] = 0; ip[7][1] = 0; ip[7][2] = 1; ip[7][3] = 0; ip[7][4] = 0; ip[7][5] = 0; ip[7][6] = 0; ip[7][7] = 1; ip[7][8] = 0; ip[7][9] = 0;

ip[8][0] = 0; ip[8][1] = 0; ip[8][2] = 1; ip[8][3] = 1; ip[8][4] = 1; ip[8][5] = 1; ip[8][6] = 1; ip[8][7] = 1; ip[8][8] = 0; ip[8][9] = 0;

ip[9][0] = 0; ip[9][1] = 0; ip[9][2] = 0; ip[9][3] = 0; ip[9][4] = 0; ip[9][5] = 0; ip[9][6] = 0; ip[9][7] = 0; ip[9][8] = 0; ip[9][9] = 0;


  for (i = 0; i < 10; i++)
    ipip[i] = ip[0][i];

  for (i = 0; i < 10; i++)
    ipip[i + 10] = ip[1][i];

  for (i = 0; i < 10; i++)
    ipip[i + 20] = ip[2][i];

  for (i = 0; i < 10; i++)
    ipip[i + 30] = ip[3][i];

  for (i = 0; i < 10; i++)
    ipip[i + 40] = ip[4][i];

  for (i = 0; i < 10; i++)
    ipip[i + 50] = ip[5][i];

  for (i = 0; i < 10; i++)
    ipip[i + 60] = ip[6][i];

  for (i = 0; i < 10; i++)
    ipip[i + 70] = ip[7][i];

  for (i = 0; i < 10; i++)
    ipip[i + 80] = ip[8][i];

  for (i = 0; i < 10; i++)
    ipip[i + 90] = ip[9][i];

//#########################################################################

//########################### step 0~6 ####################################

while (count > 0){
//##################### step0 ####################

for (i = 0; i < 100; i++)

for (j = 0; j < h; j++)

v[i][j] = 3.3; // 가중치 v값 초기화@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

for (i = 0; i < h; i++)

for (j = 0; j < 10; j++)

w[i][j] = 4.1; // 가중치 w값 초기화@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//##################### step1~3 ####################

  while (k < h){
    for (i = 0; i < 100; i++){
      sum += ipip[i] * v[i][k];
    }
    
    hl_inj[k] = sigmoid(sum); // hidden unit computation
    hl[k] = hl_inj[k];

    sum = 0;
    k++;
  }

  k = 0;

  while (k < 10){
    for (i = 0; i < h; i++){
      sum += hl[i] * w[i][k];
    }

    op_ink[k] = sigmoid(sum); // output unit computation
    op[k] = op_ink[k];

    sum = 0;
    k++;
  }

//##################### step4 ####################

  for (i = 0; i < 10; i++){
    deltaK[i] = (targetP - op[i]) * sigmoid2(op_ink[i]);
  }

  for (i = 0; i < h; i++){
    for (j = 0; j < 10; j++){
      wCT[i][j] = a * deltaK[j] * hl[i]; // 은닉-출력층의 가중치에 대한 보정항을 구하는 계산
    }
  }

//##################### step5 ####################

  for (i = 0; i < h; i++){
    for (j = 0; j < 10; j++){
      delta_inj[i][j] = deltaK[j] * w[i][j];
    }
  }

  for (i = 0; i < h; i++){
    deltaJ[i] = delta_inj[i][0] * w[i][0] + delta_inj[i][1] * w[i][1] + delta_inj[i][2] * w[i][2] + delta_inj[i][3] * w[i][3]
    + delta_inj[i][4] * w[i][4] + delta_inj[i][5] * w[i][5] + delta_inj[i][6] * w[i][6] + delta_inj[i][7] * w[i][7]
    + delta_inj[i][8] * w[i][8] + delta_inj[i][9] * w[i][9];
  }

  for (i = 0; i < 100; i++){
    for (j = 0; j < h; j++){
      vCT[i][j] = a * deltaJ[j] * ipip[i]; // 입력-은닉층의 가중치에 대한 보정항을 구하는 계산
    }
  }

//##################### step6 ####################

  for (i = 0; i < h; i++){
    for (j = 0; j < 10; j++){
      w[i][j] = w[i][j] + wCT[i][j]; // 새로운 가중치는 지금까지 구한 가중치+보정항
    }
  }

  for (i = 0; i < 100; i++){
    for (j = 0; j < h; j++){
      v[i][j] = v[i][j] + vCT[i][j]; // 새로운 가중치는 지금까지 구한 가중치+보정항
    }
  }

  count--;

  }

  //#################### 최종 출력 ####################

  for (i = 0; i < 10; i++){
    for (j = 0; j < 10; j++){
      if (ip[i][j] == 0)
        printf("□");
      else
        printf("■");
    }
    printf("\n");
  }

  printf("\n");

  sum = 0;

  for (i = 0; i < h; i++){
    for (j = 0; j < 10; j++){
      sum += w[i][j];
    }
  }

  sum = sum / 400;

  result1 = sum;

  printf("가중치 w가 수렴하는 값 : %d\n", result1);

  sum = 0;

  for (i = 0; i < 100; i++){
    for (j = 0; j < h; j++){
      sum += v[i][j];
    }

  }

  sum = sum / 4000;

  result2 = sum;

  printf("가중치 v가 수렴하는 값 : %d\n", result2);

  printf("학습된 값 : %d\n", (result1 + result2) / 2);

  return 0;

}