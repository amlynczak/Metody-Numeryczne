#include<stdio.h>
#include<math.h>

int main(){
    float x[5] = {-2., -1., 0., 1., 2.};
    float a[5] = {1, -2, 3, -1, 4};
    float A[5][5];
    float y[5];
    float x_roz[5];
    
    for(int i=0; i<5; i++){
        y[i] = a[4]*pow(x[i], 4) + a[3]*pow(x[i], 3) + a[2]*pow(x[i], 2) + a[1]*pow(x[i], 1) + a[0];
        printf("y[%d] = %.2f ", i, y[i]);
    }
    
    printf("\n \n");
    
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            A[i][j] = pow(x[i], j);
            printf("A[%d][%d] = %.2f  ", i, j, A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    float G[5][5]; //kopia A
    float b[5]; //kopia y

    for(int i=0; i<5; i++){
        b[i]=y[i];
    }
    
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            G[i][j] = A[i][j];
            //printf("G[%d][%d] = %.2f  ", i, j, G[i][j]);
        }
        //printf("\n");
    }

    //przeksztalcanie macierzy A (tutaj jako G-skopiowane A)    
    for(int i=0; i<5; i++){
        for(int j=i+1; j<=5; j++){
            float l = G[j][i]/G[i][i];
            //printf("l = %.2f", l);
            b[j] = b[j] - l * b[i];
            for(int k=0; k<5; k++){
                G[j][k] = G[j][k] - l*G[i][k];
            }
        }
    }
        
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            printf("G[%d][%d] = %.2f  ", i, j, G[i][j]);
        }
        printf("     b[%d] = %.2f", i, b[i]);
        printf("\n");
    }

    //rozwiazywanie dla x - tablica x_roz
    for(int i=4; i>=0; i--){
        float n = G[i][i];
        for(int j=4; j>i; j--){
            n = n - G[i][j]*x_roz[j];
        }
        n = n/G[i][i];
        x_roz[i] = n;
    }

    for(int i=0; i<5; i++){
        printf("x_roz[%d] = %.2f \n", i, x_roz[i]);
    }
    printf("\n");

}