#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define EPS1 3.0e-11 //do gauleg
#define EPS2 3.0e-14 //do gaulag
#define EPS3 3.0e-14 //do gauher
#define MAXIT 10 //do gaulag i gauher
#define PIM4 0.7511255444649425 //do gauher

void gauleg(float x1, float x2, float x[], float w[], int n){
    int m,j,i;
    double z1,z,xm,xl,pp,p3,p2,p1;
    m=(n+1)/2;
    xm=0.5*(x2+x1);
    xl=0.5*(x2-x1);
    for (i=1;i<=m;i++) {
        z=cos(3.141592654*(i-0.25)/(n+0.5));
        do {
            p1=1.0;
            p2=0.0;
            for (j=1;j<=n;j++) {
                p3=p2;
                p2=p1;
                p1=((2.0*j-1.0)*z*p2-(j-1.0)*p3)/j;
            }
            pp=n*(z*p1-p2)/(z*z-1.0);
            z1=z;
            z=z1-p1/pp;
        } while (fabs(z-z1) > EPS1);
        x[i]=xm-xl*z;
        x[n+1-i]=xm+xl*z;
        w[i]=2.0*xl/((1.0-z*z)*pp*pp);
        w[n+1-i]=w[i];
    }
}

float gammln(float xx){
    double x,y,tmp,ser;
    static double cof[6]={76.18009172947146,-86.50532032941677,24.01409824083091,-1.231739572450155,0.1208650973866179e-2,-0.5395239384953e-5};
    int j;
    y=x=xx;
    tmp=x+5.5;
    tmp -= (x+0.5)*log(tmp);
    ser=1.000000000190015;
    for (j=0;j<=5;j++) ser += cof[j]/++y;
    return -tmp+log(2.5066282746310005*ser/x);
}

void nrerror(char error_text[]){
    exit(1);
}

void gaulag(float x[], float w[], int n, float alf){
    int i,its,j;
    float ai;
    double p1,p2,p3,pp,z,z1;
    for (i=1;i<=n;i++) {
        if (i == 1) { 
            z=(1.0+alf)*(3.0+0.92*alf)/(1.0+2.4*n+1.8*alf);
        } else if (i == 2) {
            z += (15.0+6.25*alf)/(1.0+0.9*alf+2.5*n);
        } else { 
            ai=i-2;
            z += ((1.0+2.55*ai)/(1.9*ai)+1.26*ai*alf/(1.0+3.5*ai))*(z-x[i-2])/(1.0+0.3*alf);
        }
        for (its=1;its<=MAXIT;its++) {
            p1=1.0;
            p2=0.0;
            for (j=1;j<=n;j++) {
                p3=p2;
                p2=p1;
                p1=((2*j-1+alf-z)*p2-(j-1+alf)*p3)/j;
            }
            pp=(n*p1-(n+alf)*p2)/z;
            z1=z;
            z=z1-p1/pp;
            if (fabs(z-z1) <= EPS2) break;
        }
        if (its > MAXIT) nrerror("too many iterations in gaulag");
        x[i]=z;
        w[i] = -exp(gammln(alf+n)-gammln((float)n))/(pp*n*p2);
    }
}

void gauher(float x[], float w[], int n){
    int i,its,j,m;
    double p1,p2,p3,pp,z,z1;
    m=(n+1)/2;
    for (i=1;i<=m;i++) {
        if (i == 1) {
            z=sqrt((double)(2*n+1))-1.85575*pow((double)(2*n+1),-0.16667);
        } else if (i == 2) {
            z -= 1.14*pow((double)n,0.426)/z;
        } else if (i == 3) {
            z=1.86*z-0.86*x[1];
        } else if (i == 4) {
            z=1.91*z-0.91*x[2];
        } else {
            z=2.0*z-x[i-2];
        }
        for (its=1;its<=MAXIT;its++) {
            p1=PIM4;
            p2=0.0;
            for (j=1;j<=n;j++) {
                p3=p2;
                p2=p1;
                p1=z*sqrt(2.0/j)*p2-sqrt(((double)(j-1))/j)*p3;
            }
            pp=sqrt((double)2*n)*p2;
            z1=z;
            z=z1-p1/pp;
            if (fabs(z-z1) <= EPS3) break;
        }
        if (its > MAXIT) nrerror("too many iterations in gauher");
        x[i]=z;
        x[n+1-i] = -z;
        w[i]=2.0/(pp*pp);
        w[n+1-i]=w[i];
    }
}

double f_1(double x){
    return x/(4*pow(x,2) + 1);
}

double integral_analityc_1(double (*f)(double), double a, double c, double x1, double x2){
    double tmp1, tmp2;
    tmp1 = 1/(2*pow(a,2)) *log(fabs(pow(a, 2)*pow(x2, 2) + pow(c, 2)));
    tmp2 = 1/(2*pow(a,2)) *log(fabs(pow(a, 2)*pow(x1, 2) + pow(c, 2)));

    return tmp1 - tmp2;
}

double f_2(double x, double k){
    return pow(x, k);
}

double integral_analityc_2(double k){
    double result = 1;
    for(int i=1; i<=k; i++){
        result = result * (double)i;
    }
    return result;
}

double f_3_x(double x){
    return pow(sin(x), 2);
}

double f_3_y(double y){
    return pow(sin(y), 4);
}

int main(){
    int n;
    printf("\ncalka pierwsza: \n");
    printf("----rozwiazanie analityczne----\n");
    double x1 = 0;
    double x2 = 2;

    double c_1a;
    c_1a = integral_analityc_1(f_1, 2, 1, x1, x2);

    printf("wartosc calki: %.20f\n", c_1a);
    printf("----rozwiazanie gauleg----\n");

    for(int j=2; j<=20; j++){
        n = j;

        printf("n = %i\n", n);

        float w_1[n];
        float x_1[n];

        gauleg(x1, x2, x_1, w_1, n);

        float I_1 = 0;
        float suma = 0;
        for(int i=0; i<n; i++){
            I_1 = I_1 + w_1[i]*f_1(x_1[i]);
            suma = suma + w_1[i];
        }
        I_1 = ((x2-x1)/2) * I_1;

        printf("suma wspolczynnikow: %.20f\n", suma);
        printf("wartosc calki: %.20f\n", I_1);
        float roz;
        roz = fabs(I_1 - c_1a);
        printf("roznica: %.20f\n", roz);
    }

    //////////////////////////
    printf("\ncalka druga\n");

    for(int t = 1; t<=2; t++){
        double k = t*5;
        printf("\nk = %f\n\n", k);
        printf("----rozwiazanie analityczne----\n");

        float alfa = 0;
        double c2_a;
        c2_a = integral_analityc_2(k);

        printf("wartosc calki: %.20f\n", c2_a);

        printf("----rozwiazanie gaulag----\n");

        for(int j=2; j<=20; j++){
            n = j;
            printf("n = %i\n", n);
            float w_2[n];
            float x_2[n];
            gaulag(x_2, w_2, n, alfa);

            float I_2 = 0;
            float suma = 0;
            for(int i=0; i<n; i++){
                I_2 = I_2 + w_2[i]*f_2(x_2[i], k);
                suma = suma + w_2[i];
            }
            printf("suma wspolczynnikow: %.20f\n", suma);
            printf("wartosc calki: %.20f\n", I_2);
            float roz;
            roz = fabs(I_2 - c2_a);
            printf("roznica: %.20f\n\n", roz);
        }
    }

    //////////////////////////
    printf("\ncalka trzecia\n");
    printf("----wartosc dokladna----\n");
    
    double c_dok = 0.1919832644;
    printf("wartosc calki: %.10f\n", c_dok);

    printf("----rozwiazanie gauher----\n");
    for(int j=2; j<=15; j++){
        n = j;
        printf("n = %i\n", n);
        float w_3[n];
        float x_3[n];

        gauher(x_3, w_3, n);

        float I_3 = 0;
        float I_x = 0, I_y = 0;

        for(int i=0; i<n; i++){
            I_x = I_x + w_3[i] * f_3_x(x_3[i]);
            I_y = I_y + w_3[i] * f_3_y(x_3[i]);
        }

        I_3 = I_x * I_y;
        float roz;
        roz = fabs(I_3 - c_dok);

        printf("wartosc calki: %.20f\n", I_3);
        printf("roznica: %.20f\n\n", roz);
    }
}