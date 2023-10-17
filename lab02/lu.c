#include<stdio.h>
#include<math.h>


int main(){
    float A[3][3] = {{1, 2, 3}, {2, 8, 11}, {3, 14, 25}};
    
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("A[%d][%d] = %.2f ", i, j, A[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    
    float U[3][3];
    float L[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            U[i][j] = A[i][j];
            //printf("U[%d][%d] = %.2f  ", i, j, U[i][j]);
        }
        //printf("\n");
    }
    //printf("\n");

    for(int i=0; i<3; i++){
        for(int j=i+1; j<=3; j++){
            float l = U[j][i]/U[i][i];
            //printf("l = %.2f", l);
            L[j][i] = l;
            for(int k=0; k<3; k++){
                U[j][k] = U[j][k] - l*U[i][k];
            }
        }
    }
    


    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("U[%d][%d] = %.2f ", i, j, U[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("L[%d][%d] = %.2f ", i, j, L[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    float check[3][3]; //macierz do sprawdzenia czy macierze L i U sa poprawne

    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            for(int k = 0; k < 3; ++k){
                check[i][j] += L[i][k] * U[k][j];
            }
        }
    }

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("[%d][%d] = %.2f ", i, j, check[i][j]);
        }
        printf("\n");
    }
}
