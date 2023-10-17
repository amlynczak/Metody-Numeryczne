#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define N 50

double f_1(double x){
    return 2*sin(x) + sin(2*x) + 2*sin(3*x);
}

double f_2(double x){
    return 2*sin(x) + sin(2*x) + 2*cos(x) + cos(2*x);
}

double f_3(double x){
    return 2*sin(1.1 * x) + sin(2.1 * x) + 2*sin(3.1 * x);
}

void aprox(int n, int Ms, int Mc, double x[2*n], double y[2*n], double a[Mc+1], double b[Ms+1], double W[2*n], double (*fun)(double)){

    for(int i=0; i<2*n; i++){
        x[i] = 0 + i*2*M_PI/(2*n);
        y[i] = fun(x[i]);

        /*printf("f(%f) = %f ", x[i], y[i]);
        if((i+1)%5 == 0) printf("\n");*/
    }

    for(int j=0; j<(2*n-1); j++){
        a[0] = a[0] + fun(x[j]);
    }
    a[0] = a[0]/(2*n);

    for(int i=1; i<=Mc; i++){
        for(int j=0; j<=(2*n-1); j++){
            a[i] = a[i] + (f_1(x[j]) * cos(x[j] * i));
        }
        a[i] = a[i]/n;
    }

    printf("wspolczynniki a: \n");
    for(int i=0; i<=Mc; i++){
        printf("[%d] = %f ", i, a[i]);
    }
    printf("\n");

    b[0] = 0.0;
    for(int i=1; i<=Ms; i++){
        for(int j=0; j<=(2*n-1); j++){
            b[i] = b[i] + (fun(x[j]) * sin(x[j] * i));
        }
        b[i] = b[i]/n;
    }

    printf("wspolczynniki b: \n");
    for(int i=1; i<=Ms; i++){
        printf("[%d] = %f ", i, b[i]);
    }
    printf("\n");

    printf("\n-------------------\n\n");

    for(int i=0; i<(2*n); i++){
        W[i] = a[0]/2;
        for(int k=0; k<=Mc; k++){
            W[i] = W[i] + a[k]*cos(k*x[i]);
        }
        for(int j=0; j<=Ms; j++){
            W[i] = W[i] + b[j]*sin(j*x[i]);
        }
    }

    /*printf("otrzymane wartosci: \n");
    for(int i=0; i<2*n; i++){
        printf("f(%f) = %f ", x[i], W[i]);
        if((i+1)%5 == 0) printf("\n");
    }*/
}

int main(){
    double x[2*N];
    double y[2*N];
    double W[2*N];

    ////
    //aproksymacja f1
    ////
    printf("aproksymacja funkcji f1, Ms = Mc = 5 \n");
    printf("\n----------------------------------\n\n");

    int Ms = 5, Mc = 5;

    double *a = malloc(sizeof(double) * (Mc+1));
    double *b = malloc(sizeof(double) * (Ms+1));


    aprox(N, Ms, Mc, x, y, a, b, W, f_1);

    ////
    //aproksymacja f2
    ////
    printf("aproksymacja funkcji f2, Ms = Mc = 5 \n");
    printf("\n----------------------------------\n\n");

    Ms = 5;
    Mc = 5;

    a = malloc(sizeof(double) * (Mc+1));
    b = malloc(sizeof(double) * (Ms+1));


    aprox(N, Ms, Mc, x, y, a, b, W, f_2);

    free(a);
    free(b);

    ////
    //aproksymacja f3 - pierwsza para dla M
    ////
    printf("aproksymacja funkcji f3, Ms =  5, Mc = 0 \n");
    printf("\n----------------------------------\n\n");

    Ms = 5;
    Mc = 0;

    a = malloc(sizeof(double) * (Mc+1));
    b = malloc(sizeof(double) * (Ms+1));


    aprox(N, Ms, Mc, x, y, a, b, W, f_3);

    free(a);
    free(b);

    ////
    //aproksymacja f3 - druga para dla M
    ////
    printf("aproksymacja funkcji f3, Ms =  5, Mc = 5 \n");
    printf("\n----------------------------------\n\n");

    Ms = 5;
    Mc = 5;

    a = malloc(sizeof(double) * (Mc+1));
    b = malloc(sizeof(double) * (Ms+1));


    aprox(N, Ms, Mc, x, y, a, b, W, f_3);

    free(a);
    free(b);

    ////
    //aproksymacja f3 - trzecia para dla M
    ////
    printf("aproksymacja funkcji f3, Ms =  10, Mc = 10 \n");
    printf("\n----------------------------------\n\n");

    Ms = 10;
    Mc = 10;

    a = malloc(sizeof(double) * (Mc+1));
    b = malloc(sizeof(double) * (Ms+1));


    aprox(N, Ms, Mc, x, y, a, b, W, f_3);

    free(a);
    free(b);
}