#include<stdio.h>
#include<math.h>

#define N 21

void gauss_jordan(int n, double A[n][n], double y[n], double x[n]){
    double U[n][n+1];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            U[i][j] = A[i][j];
        }
    }
    for(int i=0; i<n; i++){
        U[i][n] = y[i];
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i != j){
                double l = U[j][i]/U[i][i];
                for(int k=0; k<=n; k++){
                    U[j][k] -= l*U[i][k];
                }
            }
        }
    }
    for(int i=0; i<n; i++){
        double om = U[i][i];
        for(int j=0; j<n+1; j++){
            U[i][j] = U[i][j]/om;
        }
    }
    for(int i=0; i<n; i++){
        x[i] = U[i][n];
    }
}

double f_1(double x){
    return 1/(1 + x * x);
}

double f_2(double x){
    return cos(2*x);
}

void wyzWekD(int n, double h, double alpha, double beta, double y[n], double d[n]){
    for(int i=0; i<n; i++){
        if(i==0){
            d[i] = alpha;
        }else if(i==n-1){
            d[i] = beta;
        }else{
            double tmp1, tmp2, tmp3;
            tmp1 = 6/(h + h);
            tmp2 = (y[i+1] - y[i])/h;
            tmp3 = (y[i] - y[i-1])/h;

            d[i] = tmp1 * (tmp2 - tmp3);
        }
    }
}

int main(){
    double x_min = -5, x_max = 5;
    double x[N], y[N];
    double A[N][N];
    double h, lambda, mi;
    double d[N], m[N];
    double alpha = 0, beta = 0;
    double x_gest[100], s[100];

    //wyznaczenie wartosci pomocniczych parametrow
    h = (x_max - x_min)/(N-1);
    lambda = h/(2*h);
    mi = 1 - lambda;

    //uzupelnienie x-ow, rownoodlegle
    for(int i=0; i<N; i++){
        x[i] = x_min + ((x_max - x_min)/(N-1)) * i;
    }

    //wyznaczenie wartosci punktow w danych punktach
    for(int i=0; i<N; i++){
        y[i] = f_1(x[i]);
    }

    printf("\n");
    for(int i=0; i<N; i++){
        printf("f(%f) = %f \n", x[i], y[i]);
    }
    printf("\n");

    //uzupelnienie macierzy A
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            A[i][j] = 0;
            if(j==i){
                A[i][j] = 2;
            }
            if(j==i+1){
                A[i][j] = mi;
            }
            if(j==i-1){
                A[i][j] = lambda;
            }
        }
    }
    A[0][0] = 1;
    A[N-1][N-1] = 1;
    A[0][1] = 0;
    A[N-1][N-2] = 0;

    printf("macierz A:\n");
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            printf("[%d][%d] = %f |", i, j, A[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    //inicjalizacja wartosic dla wektora d

    wyzWekD(N, h, alpha, beta, y, d);

    printf("wektor d:\n");
    for(int i=0; i<N; i++){
        printf("[%d] = %f |", i, d[i]);
    }
    printf("\n");

    ////
    ////szuaknie rozwiazan ukladu Am = d
    ////
    printf("\n----------------------------------\n");

    gauss_jordan(N, A, d, m);
    
    printf("wektor m:\n");
    for(int i=0; i<N; i++){
        printf("[%d] = %f |", i, m[i]);
    }
    printf("\n");

    ////
    //// wyznaczanie wartosci zageszczen
    ////
    printf("\n----------------------------------\n");

    for(int i=0; i<100; i++){
        x_gest[i] = x_min + ((x_max-x_min)/99.0) * i;
    }

    for(int z=0; z<(N-1); z++){
        double A = (y[z+1] - y[z])/h - (h/6)*(m[z+1] - m[z]);
        double B = y[z] - m[z] * (h*h)/6;
        for(double i=z*(100/(N-1)); i<(z+1)*(100/(N-1)); i++){
            double i_cpy = round(i);
            int i_int = (int)i_cpy;
            double tmp1, tmp2, tmp3;
            tmp1 = m[z] * pow((x[z+1] - x_gest[i_int]), 3)/(6*h);
            tmp2 = m[z+1] * pow((x_gest[i_int] - x[z]), 3)/(6*h);
            tmp3 = A * (x_gest[i_int] - x[z]) + B;

            s[i_int] = tmp1 + tmp2 + tmp3;
        }
    }

    for(int i=0; i<100; i++){
        printf(" f(%f) = %f ", x_gest[i], s[i]);
        if((i+1)%5 == 0){ 
            printf("\n");
        }else{
            printf("|");
        }
    }
    printf("\n");


    ////
    //FUNKCJA 2 - COS(2X)
    ////
    //wartosci x zostaja takie same, watosci h, lambda i mi tez
    ////
    printf("\n----------------------------------\n");
    printf("FUNKCJA 2 - COS(2x)");
    printf("\n----------------------------------\n");

    //wyznaczenie wartosci punktow w danych punktach
    for(int i=0; i<N; i++){
        y[i] = f_2(x[i]);
    }

    printf("\n");
    for(int i=0; i<N; i++){
        printf("f(%f) = %f \n", x[i], y[i]);
    }
    printf("\n");

    printf("macierz A:\n");
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            printf("[%d][%d] = %f |", i, j, A[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    //inicjalizacja wartosic dla wektora d

    wyzWekD(N, h, alpha, beta, y, d);

    printf("wektor d:\n");
    for(int i=0; i<N; i++){
        printf("[%d] = %f |", i, d[i]);
    }
    printf("\n");

    ////
    ////szuaknie rozwiazan ukladu Am = d
    ////
    printf("\n----------------------------------\n");

    gauss_jordan(N, A, d, m);
    
    printf("wektor m:\n");
    for(int i=0; i<N; i++){
        printf("[%d] = %f |", i, m[i]);
    }
    printf("\n");

    ////
    //// wyznaczanie wartosci zageszczen
    ////
    printf("\n----------------------------------\n");

    for(int z=0; z<(N-1); z++){
        double A = (y[z+1] - y[z])/h - (h/6)*(m[z+1] - m[z]);
        double B = y[z] - m[z] * (h*h)/6;
        for(double i=z*(100/(N-1)); i<(z+1)*(100/(N-1)); i++){
            double i_cpy = round(i);
            int i_int = (int)i_cpy;
            double tmp1, tmp2, tmp3;
            tmp1 = m[z] * pow((x[z+1] - x_gest[i_int]), 3)/(6*h);
            tmp2 = m[z+1] * pow((x_gest[i_int] - x[z]), 3)/(6*h);
            tmp3 = A * (x_gest[i_int] - x[z]) + B;

            s[i_int] = tmp1 + tmp2 + tmp3;
        }
    }

    for(int i=0; i<100; i++){
        printf(" f(%f) = %f ", x_gest[i], s[i]);
        if((i+1)%5 == 0){ 
            printf("\n");
        }else{
            printf("|");
        }
    }
    printf("\n");
}