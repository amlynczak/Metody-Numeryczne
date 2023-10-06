#include<stdio.h>
#include<math.h>
#include<stdlib.h>

double silnia(int x){
    double wynik = 1;
    for(int i=1; i<=x; i++){
        wynik = wynik*(double)i;
    }
    return wynik;
}

double f(double x, double k, double m){
    return pow(x, m)*sin(k*x);
}

int main(){
    double a = 0.0;
    double b = M_PI;
    double m, k;
    double I_a, I_b, I_c;

    double suma;

    ////
    //metoda rozwiecia
    ////
    printf("metoda rozwiniecia:\n");

    //pierwsza calka

    m = 0;
    k = 1;

    for(int i=0; i<30; i++){
        double tmp_a, tmp_b;
        tmp_b = pow(-1, i) * (pow(k*b, 2*i + m + 2)/(pow(k, m+1)*silnia(2*i + 1)*(2*i + m + 2)));
        tmp_a = pow(-1, i) * (pow(k*a, 2*i + m + 2)/(pow(k, m+1)*silnia(2*i + 1)*(2*i + m + 2)));
        suma = suma + (tmp_b - tmp_a);
    }

    I_a = suma;

    printf("pierwsza calka: %f \n", I_a);

    //druga calka
    suma = 0;

    m = 1;
    k = 1;

    for(int i=0; i<30; i++){
        double tmp_a, tmp_b;
        tmp_b = pow(-1, i) * (pow(k*b, 2*i + m + 2)/(pow(k, m+1)*silnia(2*i + 1)*(2*i + m + 2)));
        tmp_a = pow(-1, i) * (pow(k*a, 2*i + m + 2)/(pow(k, m+1)*silnia(2*i + 1)*(2*i + m + 2)));
        suma = suma + (tmp_b - tmp_a);
    }

    I_b = suma;

    printf("druga calka: %f \n", I_b);

    //trzecia calka

    suma = 0;

    m = 5;
    k = 5;

    for(int i=0; i<30; i++){
        double tmp_a, tmp_b;
        tmp_b = pow(-1, i) * (pow(k*b, 2*i + m + 2)/(pow(k, m+1)*silnia(2*i + 1)*(2*i + m + 2)));
        tmp_a = pow(-1, i) * (pow(k*a, 2*i + m + 2)/(pow(k, m+1)*silnia(2*i + 1)*(2*i + m + 2)));
        suma = suma + (tmp_b - tmp_a);
    }

    I_c = suma;

    printf("trzecia calka: %f \n", I_c);

    ////
    //metoda simpsona
    ////
    printf("\nmetoda simpsona");
    printf("\n---------------------------------\n\n");

    double p, n;
    double h, h_p;

    printf("11 wezlow\n");

    p = 5;
    n = 2 * p + 1;
    h = (b-a)/p;
    h_p = (b-a)/(2*p);

    m = 0;
    k = 1;
    suma = 0;

    for(int i=1; i<=p; i++){
        double xc, xs, xp;
        xc = a + (i-1)*h;
        xs = a + (i-1)*h + h_p;
        xp = a + (i-1)*h + 2 * h_p;
        suma = suma + ((h_p/3.0) * (f(xc, k, m) + 4 * f(xs, k, m) + f(xp, k, m)));
    }
    I_a = suma;

    printf("pierwsza calka: %f \n", I_a);

    m = 1;
    k = 1;
    suma = 0;

    for(int i=1; i<=p; i++){
        double xc, xs, xp;
        xc = a + (i-1)*h;
        xs = a + (i-1)*h + h_p;
        xp = a + (i-1)*h + 2 * h_p;
        suma +=(h_p/3.0) * (f(xc, k, m) + 4 * f(xs, k, m) + f(xp, k, m));
    }
    I_b = suma;

    printf("druga calka: %f \n", I_b);

    m = 5;
    k = 5;
    suma = 0;

    for(int i=1; i<=p; i++){
        double xc, xs, xp;
        xc = a + (i-1)*h;
        xs = a + (i-1)*h + h_p;
        xp = a + (i-1)*h + 2 * h_p;
        suma += (h_p/3.0) * (f(xc, k, m) + 4 * f(xs, k, m) + f(xp, k, m));
    }
    I_c = suma;

    printf("trzecia calka: %f \n", I_c);

    printf("\n----------\n");
    printf("21 wezlow \n");

    p = 10;
    n = 2 * p + 1;
    h = (b-a)/p;
    h_p = (b-a)/(2*p);

    m = 0;
    k = 1;
    suma = 0;

    for(int i=1; i<=p; i++){
        double xc, xs, xp;
        xc = a + (i-1)*h;
        xs = a + (i-1)*h + h_p;
        xp = a + (i-1)*h + 2 * h_p;
        suma = suma + (h_p/3.0) * (f(xc, k, m) + 4 * f(xs, k, m) + f(xp, k, m));
    }
    I_a = suma;

    printf("pierwsza calka: %f \n", I_a);

    m = 1;
    k = 1;
    suma = 0;

    for(int i=1; i<=p; i++){
        double xc, xs, xp;
        xc = a + (i-1)*h;
        xs = a + (i-1)*h + h_p;
        xp = a + (i-1)*h + 2 * h_p;
        suma = suma + (h_p/3.0) * (f(xc, k, m) + 4 * f(xs, k, m) + f(xp, k, m));
    }
    I_b = suma;

    printf("druga calka: %f \n", I_b);

    m = 5;
    k = 5;
    suma = 0;

    for(int i=1; i<=p; i++){
        double xc, xs, xp;
        xc = a + (i-1)*h;
        xs = a + (i-1)*h + h_p;
        xp = a + (i-1)*h + 2 * h_p;
        suma = suma + (h_p/3.0) * (f(xc, k, m) + 4 * f(xs, k, m) + f(xp, k, m));
    }
    I_c = suma;

    printf("trzecia calka: %f \n", I_c);

    printf("\n----------\n");
    printf("51 wezlow \n");

    p = 25;
    n = 2 * p + 1;
    h = (b-a)/p;
    h_p = (b-a)/(2*p);

    m = 0;
    k = 1;
    suma = 0;

    for(int i=1; i<=p; i++){
        double xc, xs, xp;
        xc = a + (i-1)*h;
        xs = a + (i-1)*h + h_p;
        xp = a + (i-1)*h + 2 * h_p;
        suma = suma + (h_p/3.0) * (f(xc, k, m) + 4 * f(xs, k, m) + f(xp, k, m));
    }
    I_a = suma;

    printf("pierwsza calka: %f \n", I_a);

    m = 1;
    k = 1;
    suma = 0;

    for(int i=1; i<=p; i++){
        double xc, xs, xp;
        xc = a + (i-1)*h;
        xs = a + (i-1)*h + h_p;
        xp = a + (i-1)*h + 2 * h_p;
        suma = suma + (h_p/3.0) * (f(xc, k, m) + 4 * f(xs, k, m) + f(xp, k, m));
    }
    I_b = suma;

    printf("druga calka: %f \n", I_b);

    m = 5;
    k = 5;
    suma = 0;

    for(int i=1; i<=p; i++){
        double xc, xs, xp;
        xc = a + (i-1)*h;
        xs = a + (i-1)*h + h_p;
        xp = a + (i-1)*h + 2 * h_p;
        suma = suma + (h_p/3.0) * (f(xc, k, m) + 4 * f(xs, k, m) + f(xp, k, m));
    }
    I_c = suma;

    printf("trzecia calka: %f \n", I_c);

    printf("\n----------\n");
    printf("101 wezlow \n");

    p = 50;
    n = 2 * p + 1;
    h = (b-a)/p;
    h_p = (b-a)/(2*p);

    m = 0;
    k = 1;
    suma = 0;

    for(int i=1; i<=p; i++){
        double xc, xs, xp;
        xc = a + (i-1)*h;
        xs = a + (i-1)*h + h_p;
        xp = a + (i-1)*h + 2 * h_p;
        suma = suma + (h_p/3.0) * (f(xc, k, m) + 4 * f(xs, k, m) + f(xp, k, m));
    }
    I_a = suma;

    printf("pierwsza calka: %f \n", I_a);

    m = 1;
    k = 1;
    suma = 0;

    for(int i=1; i<=p; i++){
        double xc, xs, xp;
        xc = a + (i-1)*h;
        xs = a + (i-1)*h + h_p;
        xp = a + (i-1)*h + 2 * h_p;
        suma = suma + (h_p/3.0) * (f(xc, k, m) + 4 * f(xs, k, m) + f(xp, k, m));
    }
    I_b = suma;

    printf("druga calka: %f \n", I_b);

    m = 5;
    k = 5;
    suma = 0;

    for(int i=1; i<=p; i++){
        double xc, xs, xp;
        xc = a + (i-1)*h;
        xs = a + (i-1)*h + h_p;
        xp = a + (i-1)*h + 2 * h_p;
        suma = suma + (h_p/3.0) * (f(xc, k, m) + 4 * f(xs, k, m) + f(xp, k, m));
    }
    I_c = suma;

    printf("trzecia calka: %f \n", I_c);

    printf("\n----------\n");
    printf("201 wezlow \n");

    p = 100;
    n = 2 * p + 1;
    h = (b-a)/p;
    h_p = (b-a)/(2*p);

    m = 0;
    k = 1;
    suma = 0;

    for(int i=1; i<=p; i++){
        double xc, xs, xp;
        xc = a + (i-1)*h;
        xs = a + (i-1)*h + h_p;
        xp = a + (i-1)*h + 2 * h_p;
        suma = suma + (h_p/3.0) * (f(xc, k, m) + 4 * f(xs, k, m) + f(xp, k, m));
    }
    I_a = suma;

    printf("pierwsza calka: %f \n", I_a);

    m = 1;
    k = 1;
    suma = 0;

    for(int i=1; i<=p; i++){
        double xc, xs, xp;
        xc = a + (i-1)*h;
        xs = a + (i-1)*h + h_p;
        xp = a + (i-1)*h + 2 * h_p;
        suma = suma + (h_p/3.0) * (f(xc, k, m) + 4 * f(xs, k, m) + f(xp, k, m));
    }
    I_b = suma;

    printf("druga calka: %f \n", I_b);

    m = 5;
    k = 5;
    suma = 0;

    for(int i=1; i<=p; i++){
        double xc, xs, xp;
        xc = a + (i-1)*h;
        xs = a + (i-1)*h + h_p;
        xp = a + (i-1)*h + 2 * h_p;
        suma = suma + (h_p/3.0) * (f(xc, k, m) + 4 * f(xs, k, m) + f(xp, k, m));
    }
    I_c = suma;

    printf("trzecia calka: %f \n", I_c);
}