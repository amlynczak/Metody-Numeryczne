#include<stdio.h>
#include<math.h>

#define N 11

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

double f_p_2(double x, double delta_x){
    double licznik, mianownik;

    licznik = f_1(x-delta_x);
    licznik = licznik - 2 * f_1(x);
    licznik = licznik + f_1(x+delta_x);
    mianownik = pow(delta_x, 2);

    return licznik/mianownik;
}

int main(){
    double x_min = -5, x_max = 5;
    double x[N], y[N];
    double A[N][N];
    double h, lambda, mi;
    double d[N], m[N];
    double alpha = 0, beta = 0;

    h = (x_max - x_min)/(N-1);
    lambda = h/(2*h);
    mi = 1 - lambda;

    for(int i=0; i<N; i++){
        x[i] = x_min + ((x_max - x_min)/(N-1)) * i;
    }

    for(int i=0; i<N; i++){
        y[i] = f_1(x[i]);
    }

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

    wyzWekD(N, h, alpha, beta, y, d);

    gauss_jordan(N, A, d, m);

    printf("wektor m:\n");
    for(int i=0; i<N; i++){
        printf("[%d] = %f |", i, m[i]);
    }
    printf("\n");

    double derivative[N];

    for(int i=0; i<N; i++){
        derivative[i] = f_p_2(x[i], 0.01);
    }

    printf("pochodne ze wzoru:\n");
    for(int i=0; i<N; i++){
        printf("[%d] = %f |", i, derivative[i]);
    }
    printf("\n");
}