#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

#define ITMAX 100
#define EPS_gser 3.0e-7
#define EPS_gcf 3.0e-7
#define FPMIN 1.03-30

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

void gser(float *gamser, float a, float x, float *gln){
    int n;
    float sum,del,ap;
    *gln=gammln(a);
    if (x <= 0.0) {
        if (x < 0.0) nrerror("x less than 0 in routine gser");
        *gamser=0.0;
        return;
    } else {
        ap=a;
        del=sum=1.0/a;
        for (n=1;n<=ITMAX;n++) {
            ++ap;
            del *= x/ap;
            sum += del;
            if (fabs(del) < fabs(sum)*EPS_gser) {
                *gamser=sum*exp(-x+a*log(x)-(*gln));
                return;
            }
        }
        nrerror("a too large, ITMAX too small in routine gser");
        return;
    }
}

void gcf(float *gammcf, float a, float x, float *gln){
    int i;
    float an,b,c,d,del,h;
    *gln=gammln(a);
    b=x+1.0-a;
    c=1.0/FPMIN;
    d=1.0/b;
    h=d;
    for (i=1;i<=ITMAX;i++) {
        an = -i*(i-a);
        b += 2.0;
        d=an*d+b;
        if (fabs(d) < FPMIN) d=FPMIN;
        c=b+an/c;
        if (fabs(c) < FPMIN) c=FPMIN;
        d=1.0/d;
        del=d*c;
        h *= del;
        if (fabs(del-1.0) < EPS_gcf) break;
    }
    if (i > ITMAX) nrerror("a too large, ITMAX too small in gcf");
    *gammcf=exp(-x+a*log(x)-(*gln))*h;
}

float gammp(float a, float x){
    float gamser,gammcf,gln;
    if (x < 0.0 || a <= 0.0) nrerror("Invalid arguments in routine gammp");
    if (x < (a+1.0)) {
        gser(&gamser,a,x,&gln);
        return gamser;
    } else {
        gcf(&gammcf,a,x,&gln);
        return 1.0 - gammcf;
    }
}

float erff(float x){
    return x < 0.0 ? -gammp(0.5,x*x) : gammp(0.5,x*x);
}

void rozk_jednorodny(int a, int c, int m, int x0, int x[], double X[], int n){
    if(n!=0){
        x[0] = x0;
        for(int i=1; i<n; i++){
            x[i] = abs((a*x[i-1] + c)%m);
        }
        for(int i=0; i<n; i++){
            int m_tmp = m +1;
            X[i] = fabs((double)x[i]/((double)m_tmp));
        }
    }
}

void rozk_normalny(double mu, double sigma, double X[], double X_n[], int n){
    for(int i=0; i<n; i++){
        double x, y, z, res;
        do{
            int index1 = rand()%n;
            int index2 = rand()%n;
            x = X[index1];
            y = X[index2];
            z = pow(x, 2) + pow(y, 2);
            res = mu + sigma * x * sqrt(-2*log(z)/z);
        }while(res < mu - 3*sigma || res > mu + 3 * sigma || isnan(res));
        X_n[i] = res;
    }
}

double F(double x){
    return (1 + erf(x))/2
}

int main(){
    srand(time(NULL));

    int n = pow(10, 4);
    int x[n];
    double X[n];
    x[0] = 10;

    /// 2.1 podpunkt a
    int a = 123;
    int c = 1;
    int m = pow(2, 15);

    rozk_jednorodny(a, c, m, x[0], x, X, n);

    int ka[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    double przedzial = 1.0/12.0;
    for(int i=0; i<n; i++){
        int index = (int)(X[i]/przedzial);
        ka[index]++;
    }

    /// 2.1 podpunkt b
    a = 69069;
    c = 1;
    double m_b = pow(2, 32);

    rozk_jednorodny(a, c, (int)m_b, x[0], x, X, n);

    int kb[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for(int i=0; i<n; i++){
        int index = (int)(X[i]/przedzial);
        kb[index]++;
    }

    ///
    //rozklad normalny (2.2)
    ///

    double mu = 0.2;
    double sigma = 0.5;

    double X_n[n];

    rozk_normalny(mu, sigma, X, X_n, n);

    int k[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    double a1, a2;

    a1 = mu - 3 * sigma;
    a2 = mu + 3 * sigma;
    przedzial = (a2-a1)/12.0;

    for(int i=0; i<n; i++){
        if (X_n[i] >= a1 && X_n[i] < a2) {
            int index = (int)((X_n[i] - a1) / przedzial);
            k[index]++;
        }
    }

    double srednia = 0;
    for(int i=0; i<n; i++){
        srednia = srednia + X_n[i];
    }

    double wariancja = 0;
    for(int i=0; i<n; i++){
        wariancja = wariancja + pow((X_n[i]-srednia), 2);
    }
    wariancja = wariancja/n;
    double odchyl_standard;
    odchyl_standard = sqrt(wariancja);

    double statystyka_test;

    double p[12];
    for(int i=1; i<12; i++){
        
    }
}