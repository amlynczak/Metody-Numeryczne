#include<stdio.h>
#include<math.h>

int main(){
    double A[7][7];
    printf("macierz A: \n");
    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
            A[i][j] = sqrt(i+1+j+1);
            printf("[%d][%d] = %f ", i, j, A[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    double W[7][7];
    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
            W[i][j] = A[i][j];
        }
    }

    double x[7] = {1, 1, 1, 1, 1, 1, 1};
    double x_next[7] = {0, 0, 0, 0, 0, 0, 0};
    double lambda;
    double norma;
    
    for(int j=0; j<7; j++){
        for(int i=0; i<8; i++){
            lambda = 0;
            double licz = 0;
            double mian = 0;

            for(int k=0; k<7; k++){
                x_next[k] = 0;
            }

            //krok 1 x_k+1 = W_i * x_k

            for(int a=0; a<7; a++){
                for(int b=0; b<7; b++){
                    x_next[a] = x_next[a] + W[a][b] * x[b];
                }
            }

            //wyliczenie lambdy
            for(int k=0; k<7; k++){
                licz = licz + x_next[k] * x[k]; //x_next_T * x
                mian = mian + x[k] * x[k]; //x_T * x
            }
            lambda = licz/mian;

            //normalizowanie wektora
            double suma = 0;
            norma = 0;

            for(int k=0; k<7; k++){
                suma = suma + pow(x_next[k],2);
            }
            norma = sqrt(suma);

            for(int k=0; k<7; k++){
                x_next[k] = x_next[k]/norma;
            }

            //przypisanie wartosci x_next do x
            for(int k=0; k<7; k++){
                x[k] = x_next[k];
            }
        }

        printf("lambda = %.20lf \n", lambda);

        /*FILE *fl;
        fl = fopen("lambda.txt", "a");
        fprintf(fl, "lambda = %.20f dla j = %d \n", lambda, j);
        fclose(fl);*/

        //W_i+i = W_i - lambda * X_t * x

        for(int a=0; a<7; a++){
            for(int b=0; b<7; b++){
                W[a][b] = W[a][b] - lambda * x[a] * x[b];
            }
        }

        printf("wektor x: \n");
        for(int k=0; k<7; k++){
            printf("[%d] = %f ", k, x[k]);
        }
        printf("\n");

        /*FILE *fx;
        fx = fopen("x.txt", "a");
        fprintf(fx, "wektor x dla j = %d \n", j);
        for(int k=0; k<7; k++){
            fprintf(fx, "[%d] = %.10f ", k, x[k]);
        }
        fprintf(fx, "\n");
        fclose(fx);*/
    }
    printf("\n");
}