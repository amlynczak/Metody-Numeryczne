#include<stdio.h>
#include<math.h>

#define IT 200

int main(){
    double kch = 5.92 * pow(10, 2);
    double kcc = 15.8 * pow(10, 2);
    double mh = 1;
    double mc = 12;

    double D[4][4] = {
        {kch/mh, -kch/mh, 0, 0},
        {-kch/mh, (kch+kcc)/mc, -kcc/mc, 0},
        {0, -kcc/mc, (kch+kcc)/mc, -kch/mc},
        {0, 0, -kch/mh, kch/mh}
    };

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

    double H[4][4];
    double P[4][4];

    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            H[i][j] = D[i][j];
            P[i][j] = I[i][j];
        }
    }

    for(int z=0; z<IT; z++){
        double R[4][4];
        double Q[4][4];

        //poczatkowe macierze R i Q
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                R[i][j] = H[i][j];
                Q[i][j] = I[i][j];
            }
        }


        //rozklad QR
        for(int n=0; n<3; n++){

            //wektor x 
            double x[4];
            for(int i=0; i<4; i++){
                x[i] = R[n][i];
                if(i<n){
                    x[i] = 0;
                }
            }

            double suma = 0;
            double norma_x;
            for(int i=0; i<4; i++){
                suma = suma + x[i]*x[i];
            }
            norma_x = sqrt(suma);

            //wektor e
            double e[4];
            for(int i=0; i<4; i++){
                e[i] = 0;
                if(i==n){
                    e[i] = 1;
                }
            }

            //znalezienie wekotra u
            double u[4];
            for(int i=0; i<4; i++){
                u[i] = x[i] - norma_x * e[i];
            }

            suma = 0;
            double norma_u;
            for(int i=0; i<4; i++){
                suma = suma + u[i]*u[i];
            }
            norma_u = sqrt(suma);

            //znalezienie wektora v
            double v[4];
            for(int i=0; i<4; i++){
                v[i] = u[i]/norma_u;
            }

            //znalezienie macierzy Q_t
            double Q_t[4][4];
            for(int i=0; i<4; i++){
                for(int j=0; j<4; j++){
                    Q_t[i][j] = I[i][j] - 2 * v[i] * v[j];
                }
            }

            //przypisanie Q = Q_t * Q i R = Q_t * R
            double Q_temp[4][4];
            double R_temp[4][4];

            for(int i=0; i<4; i++){
                for(int j=0; j<4; j++){
                    Q_temp[i][j] = 0;
                    R_temp[i][j] = 0;
                    for(int k=0; k<4; k++){
                        Q_temp[i][j] += Q_t[i][k] * Q[k][j];
                        R_temp[i][j] += Q_t[i][k] * R[k][j]; 
                    }
                }
            }

            for(int i=0; i<4; i++){
                for(int j=0; j<4; j++){
                    Q[i][j] = Q_temp[i][j];
                    R[i][j] = R_temp[i][j];
                }
            }

            //przypisanie Q = Q_transponowane
            double Q_tr[4][4];
            for(int i=0; i<4; i++){
                for(int j=0; j<4; j++){
                    Q_tr[i][j] = Q[j][i];
                }
            }
            for(int i=0; i<4; i++){
                for(int j=0; j<4; j++){
                    Q[i][j] = Q_tr[i][j];
                }
            }
        }

        

        //przypisanie H = RQ i P =PQ
        double H_temp[4][4];
        double P_temp[4][4];
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                H_temp[i][j] = 0;
                P_temp[i][j] = 0;
                for(int k=0; k<4; k++){
                    H_temp[i][j] += R[i][k] * Q[k][j];
                    P_temp[i][j] += P[i][k] * Q[k][j];
                }
            }
        }

        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                H[i][j] = H_temp[i][j];
                P[i][j] = P_temp[i][j];
            }
        }

    }

    printf("macierz H: \n");
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            printf("[%d][%d] = %lf |", i, j, H[i][j]);
        }
        printf("\n");
    }
    printf("\n");


    //wyznaczenie wektorow wlasnych
    double wek_x[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

    for(int i = 0; i<4; i++){
        for(int j=0; j<4; j++){
            if(j>i){
                wek_x[i][j] = 0;
            }
            if(j==1){
                wek_x[i][j] = 1;
            }
            if(j<i){
                double licznik = 0;
                double mianownik = 0;

                for(int k=j+1; k<=i; k++){
                    licznik = licznik + H[j][k] * wek_x[i][k];
                }

                if(H[j][j] != H[i][i]){
                    mianownik = H[j][j] - H[i][i];
                }

                wek_x[i][j] = -licznik/mianownik;

            }
        }
    }

    //normalizacja tych wektorow
    double suma;
    double norma;

    for(int i=0; i<4; i++){
        suma = 0;
        for(int j=0; j<4; j++){
            suma = suma + wek_x[i][j] * wek_x[i][j];
        }
        norma = sqrt(suma);
        for(int j=0; j<4; j++){
            wek_x[i][j] = wek_x[i][j]/norma;
        }
    }

    //wypisanie otrzymanych wynikow
    printf("wartosci wlasne macierzy D: \n");
    for(int i=0; i<4; i++){
        printf("[%d] = %lf |", i, H[i][i]);
    }
    printf("\n");

    printf("wekotry wlasne macierzy D: \n\n");
    for(int i=0; i<4; i++){
        printf("wektor A[%d]: \n", i);
        for(int j=0; j<4; j++){
            printf("[%d] = %lf | ", j, wek_x[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}