#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){
    float A[3][3] = {
        {3., 1., 1.},
        {2., -1., 3.},
        {1., 3., -1.}
    };
    float y[3] = {6., 0., 6.};
    float x_roz[3];

    float U[3][4]; //tworze macierz uzupelniona

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            U[i][j] = A[i][j];
        }
    }
    for(int i=0; i<3; i++){
        U[i][3] = y[i];
    }

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("U[%d][%d] = %.2f ", i, j, U[i][j]);
        }
        printf(" | U[%d][3] = %.2f ", i, U[i][3]);
        printf("\n");
    }
    printf("\n");

    //implementuje metode gaussa-jordana

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(i != j){
                float l = U[j][i]/U[i][i];
                for(int k=0; k<=3; k++){
                    U[j][k] -= l*U[i][k];
                }
            }
        }
    }
    for(int i=0; i<3; i++){
        float om = U[i][i];
        for(int j=0; j<4; j++){
            U[i][j] = U[i][j]/om;
        }
    }

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("U[%d][%d] = %.2f ", i, j, U[i][j]);
        }
        printf(" | U[%d][3] = %.2f ", i, U[i][3]);
        printf("\n");
    }
    printf("\n");
    
    //wpisuje rozwiazania do tablicy x_roz

    for(int i=0; i<3; i++){
        x_roz[i] = U[i][3];
        printf("x_roz[%d] = %.2f ", i, x_roz[i]);
    }
    printf("\n");


}