#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define TOL 0.000001

double f(double x){
    return log(x) * pow(x-2, 2);
}

double f_p(double x){
    double val;
    val = (1/x) * pow(x-2,2) + log(x) * 2 * (x-2);
    return val;
}

double u(double x){
    return f(x)/f_p(x);
}

double u_p(double x){
    double val;
    val = 2 * pow(x,2) * pow(log(x), 2) + pow(x-2, 2) + pow(x-2, 2)*log(x);
    double mian;
    mian = pow(x+2*x*log(x)-2, 2);
    val = val/mian;
    return val;
}

int main(){
    double x0 = 0.5, x1=0.5;
    double f0;
    double f_p0;
    double e;

    int n = 0;

    //
    //pierwsze szukanie - metoda niemodyfikowana, pierwiastek 1
    //
    printf("\nmetoda pierwsza (x_i+1 = x_i - f(x)/f'(x)) - szukanie x = 1: \n\n");
     
    do{
        n++;
        x0 = x1;
        f_p0 = f_p(x0);
        f0 = f(x0);
        printf("pochodna: %.15f, funkcja: %.15f \n", f_p0, f0);
        if(f_p0 == 0) exit(0);


        x1 = x0 - (f0/f_p0);
        printf("x0 = %.15f, x1 = %.15f \n", x0, x1);

        if(f(x1) == 0){
            printf("dla x = %.2f wartosc funkcji to %.2f \n", x1, f(x1));
        }

        e = fabs(x1-x0);
        printf("aktualna wartosc epsilon: %.10f \n", e);
    }while(e > TOL);

    printf("\npierwiastek: %.2f \n", x1);
    printf("liczba iteracji: %d\n\n", n);

    //
    //drugie szukanie - metoda niemodyfikowana, szukanie x = 2
    //
    printf("\nmetoda pierwsza (x_i+1 = x_i - f(x)/f'(x)) - szukanie x = 2: \n\n");

    x0 = 3;
    x1 = 3;
    n = 0;
    do{
        n++;
        x0 = x1;
        f_p0 = f_p(x0);
        f0 = f(x0);
        printf("pochodna: %.15f, funkcja: %.15f \n", f_p0, f0);
        if(f_p0 == 0) exit(0);


        x1 = x0 - (f0/f_p0);
        printf("x0 = %.15f, x1 = %.15f \n", x0, x1);

        if(f(x1) == 0){
            printf("dla x = %.2f wartosc funkcji to %.2f \n", x1, f(x1));
        }

        e = fabs(x1-x0);
        printf("aktualna wartosc epsilon: %.10f \n", e);
    }while(e >= TOL);

    printf("\npierwiastek: %.2f \n", x1);
    printf("liczba iteracji: %d\n\n", n);

    //trzecie szukanie
    printf("metoda druga (to samo co pierwsza, ale znamy krotnosc pierwiastka [=2]): \n\n");
    x0 = 3;
    x1 = 3;
    n=0;

    do{
        n++;
        x0 = x1;
        f_p0 = f_p(x0);
        f0 = f(x0);
        printf("pochodna: %.15f, funkcja: %.15f \n", f_p0, f0);
        if(f_p0 == 0) exit(0);


        x1 = x0 - 2*(f0/f_p0);
        printf("x0 = %.15f, x1 = %.15f \n", x0, x1);

        if(f(x1) == 0){
            printf("dla x = %.2f wartosc funkcji to %.2f \n", x1, f(x1));
        }

        e = fabs(x1-x0);
        printf("aktualna wartosc epsilon: %.10f \n", e);
    }while(e > TOL);

    printf("\npierwiastek: %.2f \n", x1);
    printf("liczba iteracji: %d\n\n", n);

    //
    //czwarte szukanie
    //

    printf("metoda trzecia (x_i+1 = x_i - u(x)/u'(x)): \n\n");
    x0 = 3;
    x1 = 3;
    n=0;

    do{
        n++;
        x0 = x1;
        f_p0 = f_p(x0);
        f0 = f(x0);
        printf("pochodna: %.15f, funkcja: %.15f \n", f_p0, f0);
        if(f_p0 == 0) exit(0);

        x1 = x0 - (u(x0)/u_p(x0));
        printf("x0 = %.15f, x1 = %.15f \n", x0, x1);

        if(f(x1) == 0){
            printf("dla x = %.2f wartosc funkcji to %.2f \n", x1, f(x1));
        }

        e = fabs(x1-x0);
        printf("aktualna wartosc epsilon: %.10f \n", e);
    }while(e>=TOL);

    printf("\npierwiastek: %.2f \n", x1);
    printf("liczba iteracji: %d\n\n", n);

}