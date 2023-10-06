#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define E 5
#define N 400
#define IT 1000

double d_rand(double min, double max){
	double r = (double) rand()/RAND_MAX;
	return r*(max-min) + min;
    }

int main(){
    srand(time(NULL));

    const int n = 2*N +1;

    double y[n];
    double A[n][n];
    double x[n];
    double b[2*N +1] = {0.};
    double h = 6./N;

    //wypelnienie wektora x
    for(int i=0; i<n; i++){
        x[i] =i * h - 6;
    }

    //wypelnienie wektora y losowymi wartosciami z przedzialu [0, 1]
    for(int i=0; i<n; i++){
        y[i] = d_rand(0. , 1.);
    }
    y[0] = 0;
    y[2*N] = 0;

    //wypelnienie macierzy A, aby powstala macierz wstegowa
    for(int i=0; i<n; i++){
        A[i][i] = 2*E*pow(h, 2) - pow(x[i], 2) * pow(h, 2) - 2;
    }
    A[0][0] = 1;
    A[2*N][2*N] = 1;
    for(int i=0; i<2*N; i++){
        A[i][i+1] = 1;
        A[i+1][i] = 1;
    }
    A[0][1] = 0;
    A[2*N][2*N-1] = 0;

    
    /*for(int i=0; i<2*N +1; i++){
        for(int j=0; j<2*N+1; j++){
            printf("A[%d][%d] = %f ", i, j, A[i][j]);
        }
        printf("\n");
    }
    printf("\n");*/

    //
    //
    //
    printf("---------------------------\n");
    double r[n];
    double alpha;
    double Ay[2*N+1];


for(int z=0; z<IT; z++){
    for(int i=0; i<n; i++){
        Ay[i] = 0;
        for(int j=0; j<n; j++){
            Ay[i] = Ay[i] + A[i][j]*y[j];
        }
    }

    for(int i=0; i<2*N+1; i++){
        r[i] = b[i] - Ay[i];
    }

    double Ar[n];

    for(int i=0; i<2*N+1; i++){
        Ar[i] = 0;
        for(int j=0; j<2*N+1; j++){
            Ar[i] = Ar[i] + A[i][j] * r[j];
        }
    }

    double rt_r;
    for(int i=0; i<2*N+1; i++){
        rt_r = rt_r + r[i]*r[i];
    }

    double rt_Ar;
    for(int i=0; i<2*N+1; i++){
        rt_Ar = rt_Ar + r[i]*Ar[i];
    }

    alpha = rt_r/rt_Ar;
    double norma;
    for(int k =0; k<n; k++){
        y[k] = y[k] + alpha * r[k];
        y[0] = 0;
        y[2*N] = 0;
        norma = 0;
        double suma =0;
        for(int i=0; i<2*N+1; i++){
            suma = suma + pow(y[i], 2);
        }
        norma = sqrt(suma);

        y[k] = y[k]/norma/h;

        
        
    }
    FILE *fr;
    fr = fopen("norma.txt", "a");
    fprintf(fr, "%f \n", norma);
    fclose(fr);
}


    /*for(int i=0; i<2*N+1; i++){
        printf("y[%d] = %f ", i, y[i]);
    }
    printf("\n");*/

    for(int i=0; i<n; i++){
        FILE *fx;
        FILE *fy;
        fx = fopen("x.txt", "a");
        fy = fopen("y.txt", "a");
        fprintf(fx, "%f \n", x[i]);
        fprintf(fy, "%f \n", y[i]);
        fclose(fx);
        fclose(fy);
    }
    
}