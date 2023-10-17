#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define N 50

double f_1_rand(double x, double alpha){
    return 2*sin(x) + sin(2*x) + 2*sin(3*x) + alpha;
}

int main(){
    double x[2*N];
    double y[2*N];
    double W[2*N];
    int Ms, Mc;

    Ms = 30;
    Mc = 30;

    double a[Mc+1];
    double b[Ms+1];

    double alpha;
    srand(time(NULL));
    alpha = rand()/(RAND_MAX+1.0);
    alpha = alpha - 0.5;
    printf("\nalpha = %f \n\n", alpha);

    for(int i=0; i<2*N; i++){
        x[i] = 0 + i*2*M_PI/(2*N);
        y[i] = f_1_rand(x[i], alpha);

        printf("f(%f) = %f |", x[i], y[i]);
        if((i+1)%5 == 0) printf("\n");
    }

    for(int j=0; j<(2*N-1); j++){
        a[0] = a[0] + f_1_rand(x[j], alpha);
    }
    a[0] = a[0]/(2*N);

    for(int i=1; i<=Mc; i++){
        for(int j=0; j<=(2*N-1); j++){
            a[i] = a[i] + (f_1_rand(x[j], alpha) * cos(x[j] * i));
        }
        a[i] = a[i]/N;
    }

    printf("\nwspolczynniki a: \n");
    for(int i=0; i<=Mc; i++){
        printf("[%d] = %f ", i, a[i]);
        if((i+1)%5 == 0)printf("\n");
    }
    printf("\n");

    b[0] = 0.0;
    for(int i=1; i<=Ms; i++){
        for(int j=0; j<=(2*N-1); j++){
            b[i] = b[i] + (f_1_rand(x[j], alpha) * sin(x[j] * i));
        }
        b[i] = b[i]/N;
    }

    printf("wspolczynniki b: \n");
    for(int i=1; i<=Ms; i++){
        printf("[%d] = %f ", i, b[i]);
        if(i%5 == 0)printf("\n");
    }
    printf("\n");

    printf("\n-------------------\n\n");

    for(int i=0; i<(2*N); i++){
        W[i] = a[0]/2;
        for(int k=0; k<=Mc; k++){
            W[i] = W[i] + a[k]*cos(k*x[i]);
        }
        for(int j=0; j<=Ms; j++){
            W[i] = W[i] + b[j]*sin(j*x[i]);
        }
    }

    printf("otrzymane wartosci: \n");
    for(int i=0; i<2*N; i++){
        printf("f(%f) = %f |", x[i], W[i]);
        if((i+1)%5 == 0) printf("\n");
    }
}
