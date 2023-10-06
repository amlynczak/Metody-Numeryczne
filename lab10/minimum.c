#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define delta 0.0001

double f(double x, double y){
    return (5.0/2.0)*pow(pow(x,2)-y, 2) + pow(1-x,2);
}

double dfdx(double x, double y){
    double val;
    val = f(x + delta, y) - f(x - delta, y);
    val = val/(2*delta);
    return val;
}

double dfdy(double x, double y){
    double val;
    val = f(x, y + delta) - f(x, y - delta);
    val = val/(2*delta);
    return val;
}

double norma(double wektor[2]){
    return sqrt(pow(wektor[0],2)+pow(wektor[1],2));
}

int main(){
    double h = 0.1;
    double eps = pow(10, -3);
    double r0[2] = {-0.75, 1.75};
    double r_i[2];
    double r[2];
    FILE *fr/*, *fxy, *fm*/;

    /*fm = fopen("minimum.dat", "a");
    fprintf(fm, "%f  %f \n", 1.0, 1.0);
    fclose(fm);*/
    
    //double x[201], y[201], z[201][201];

    /*fxy = fopen("fxy.dat", "a");

    for(int i=0; i<201; i++){
        x[i] = -2.0 + i * 0.02;
        y[i] = -2.0 + i * 0.02;
    }

    for(int i=0; i<201; i++){
        for(int j=0; j<201; j++){
            z[i][j] = f(x[i], y[j]);
            fprintf(fxy, "%f %f %f \n", x[i], y[j], z[i][j]);
        }
    }
    fclose(fxy);*/

    r[0] = r_i[0] = r0[0];
    r[1] = r_i[1] = r0[1];

    double norm;
    double r_war[2];
    int i = 1;

    fr = fopen("eps2.dat", "a");
    fprintf(fr, "%f %f \n", r0[0], r0[1]);

    do{
        r_i[0] = r[0];
        r_i[1] = r[1];

        double grad_r[2];
        grad_r[0] = dfdx(r_i[0], r_i[1]);
        grad_r[1] = dfdy(r_i[0], r_i[1]);
        r[0] = r_i[0] - h * grad_r[0];
        r[1] = r_i[1] - h * grad_r[1];

        r_war[0] = r[0] - r_i[0];
        r_war[1] = r[1] - r_i[1];

        fprintf(fr, "%f %f \n", r[0], r[1]);
        
        norm = norma(r_war);
        i++;
    }while(norm>eps && i <1000);

    fclose(fr);

    printf("wartosc epsilon: %f \n", eps);
    printf("liczba iteracji: %d \n", i);
    printf("wektor r na koniec: \n");
    printf("[%d] = %f, [%d] = %f \n", 0, r[0], 1, r[1]);
}