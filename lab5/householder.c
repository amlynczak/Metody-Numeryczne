#include<stdio.h>
#include<math.h>

#define IT 200

int main(){
    double kch = 5.92 * pow(10, 2);
    double kcc = 15.8 * pow(10, 2);
    double mh = 1;
    double mc = 12;

    double D[4][4];

    D[0][0] = kch / mh;
    D[0][1] = -kch / mc;
    D[0][2] = 0; D[0][3] = 0;
    D[1][0] = -kch/ mh;
    D[1][1] = (kch+kcc)/mc;
    D[1][2] = -kcc/mc;
    D[1][3] = 0; D[2][0] = 0;
    D[2][1] = -kcc/mc;
    D[2][2] = (kch+kcc)/mc;
    D[2][3] = -kch/mh;
    D[3][0] = 0; D[3][1] = 0;
    D[3][2] = -kch/mc;
    D[3][3] = kch/mh;

    printf("macierz D: \n");
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            printf("[%d][%d] = %f ", i, j, D[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    double I[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    ///////// krok 1 ///////
    printf("-------------------------------------\n");
    double R[4][4];

    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            R[i][j] = D[i][j];
        }
    }

    double Q[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };


    ///////// krok 2 ///////
    printf("-------------------------------------\n");

    for(int k=0; k<3; k++){
        double u[4];
        double v[4];
        double x[4];
        double e[4];
        double norma_x = 0;
        double norma_u = 0;
        double suma = 0;

        //przypisanie wartosci do e
        for(int i=0; i<4; i++){
            if(i==k){
                e[i] = 1;
            }else{
                e[i] = 0;
            }
        }

        //przypisanie wartosci do wektora x
        for(int i=0; i<4; i++){
            if(i<k) x[i] = 0;
            x[i] = R[i][k];
        }

        printf("wektor x, k = %d :", k);
        for(int i=0; i<4; i++){
            printf("[%d] = %lf ", i, x[i]);
        }
        printf("\n");

        for(int i=0; i<4; i++){
            suma += x[i]*x[i];
        }
        norma_x = sqrt(suma);

        //znalezienie wektora u
        for(int i=0; i<4; i++){
            u[i] = x[i] - norma_x * e[i];
        }

        printf("wektor u, k = %d :", k);
        for(int i=0; i<4; i++){
            printf("[%d] = %lf ", i, u[i]);
        }
        printf("\n");

        suma = 0;
        for(int i=0; i<4; i++){
            suma += u[i]*u[i];
        }
        norma_u = sqrt(suma);

        //znaleznienie wektora v
        for(int i=0; i<4; i++){
            v[i] = u[i] / norma_u;
        }
        printf("wektor v, k = %d :", k);
        for(int i=0; i<4; i++){
            printf("[%d] = %lf ", i, v[i]);
        }
        printf("\n");

        //znalezienie macierzy Q_t
        double Q_t[4][4];
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                Q_t[i][j] = I[i][j] - 2 * v[i] * v[j];
            }
        }

        //Q = Q_t * Q

        double Q_temp[4][4];

        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                Q_temp[i][j] = 0;
                for(int a=0; a<4; a++){
                    Q_temp[i][j] += Q_t[i][a] * Q[a][j]; 
                }
            }
        }

        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                Q[i][j] = Q_temp[i][j];
            }
        }

        //R = Q_t * R
        double R_temp[4][4];

        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                R_temp[i][j] = 0;
                for(int a=0; a<4; a++){
                    R_temp[i][j] += Q_t[i][a] * R[a][j];
                }
            }
        }

        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                R[i][j] = R_temp[i][j];
            }
        }

        printf("macierz R na koniec iter. k= %d: \n", k);
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                printf("[%d][%d] = %lf |", i, j, R[i][j]);
            }
            printf("\n");
        }
        printf("\n");        

    }

    /// Q = Q_transfotmacja

    double Q_T[4][4];

    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            Q_T[i][j] = Q[j][i];
        }
    }
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            Q[i][j] = Q_T[i][j];
        }
    }

    printf("macierz Q na koniec: \n");
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            printf("[%d][%d] = %lf |", i, j, Q[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("macierz R na koniec: \n");
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            printf("[%d][%d] = %lf |", i, j, R[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    /// Q * R
    double D_2[4][4];

    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            D_2[i][j] = 0;
            for(int k=0; k<4; k++){
                D_2[i][j] += Q[i][k] * R[k][j];
            }
        }
    }

    printf("macierz QxR na koniec: \n");
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            printf("[%d][%d] = %lf |", i, j, D_2[i][j]);
        }
        printf("\n");
    }
    printf("\n");

/*    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            H[i][j] = 0;
            for(int k=0; k<4; k++){
                H[i][j] += R[i][k] * Q[k][j];
            }
        }
    }

    double P_temp[4][4];
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            P_temp[i][j] = 0;
            for(int k=0; k<4; k++){
                P_temp[i][j] += P[i][k] * Q[k][j];
            }
        }
    }
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            P[i][j] = P_temp[i][j];
        }
    }

    

}

printf("Macierz H: \n");
for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
        printf("[%d][%d] = %lf |", i, j, H[i][j]);
    }
    printf("\n");
}
printf("\n");*/
}