#include<stdio.h>
#include<math.h>

double f(double x){
    return exp(-pow(x,2));
}

int main(){
    double skok;
    double omega_x;
    double omega_xj;
    double y_uzup[100];
    double x_uzup[100];
    double skok_uzup = (5 - (-5));
    skok_uzup = skok_uzup / 99;
    double suma;

    for(int i=0; i<100; i++){
        x_uzup[i] = -5 + i * skok_uzup;
        printf("[%d] = %f, ", i, x_uzup[i]);
        if((i+1)%10 == 0){
            printf("\n");
        }
    }//ustalanie x do uzupelnienia - rozklad ich na osi

    ////
    //// 6 wezlow 
    ////
    printf("\n-------------------------------------\n");

    double y_1[6];
    double x_1[6];
    skok = (5 - (-5))/4;

    for(int i=0; i<6; i++){
        x_1[i] = -5 + i*skok;
    }

    printf("otrzymane wartosci funkcji dla 6 wezlow: \n");
    for(int i=0; i<6; i++){
        y_1[i] = f(x_1[i]);
        printf("%f | ", y_1[i]);
    }
    printf("\n");

    for(int i=0; i<100; i++){
        suma = 0;
        for(int j=0; j<6; j++){
            omega_x = 1;
            omega_xj = 1;
            for(int k=0; k<6; k++){
                if(k!=j){
                    omega_x = omega_x * (x_uzup[i] - x_1[k]);
                    omega_xj = omega_xj * (x_1[j] - x_1[k]);
                }
            }
            suma = suma + y_1[j] * omega_x / omega_xj;
        }
        y_uzup[i] = suma;
    }
    
    
    printf("otrzymane wartosci z uzupelnieniem: \n");
    for(int i=0; i<100; i++){
        printf("f(%f) = %f, ", x_uzup[i], y_uzup[i]);
        if((i+1)%5 == 0){
            printf("\n");
        }
    }

    ////
    //// 11 wezlow 
    ////
    printf("\n-------------------------------------\n");

    double y_2[11];
    double x_2[11];
    skok = (5 - (-5))/9;

    for(int i=0; i<11; i++){
        x_2[i] = -5 + i*skok;
    }
    
    printf("otrzymane wartosci funkcji dla  11 wezlow: \n");
    for(int i=0; i<11; i++){
        y_2[i] = f(x_2[i]);
        printf("%f | ", y_2[i]);
    }
    printf("\n");

    for(int i=0; i<100; i++){
        suma = 0;
        for(int j=0; j<11; j++){
            omega_x = 1;
            omega_xj = 1;
            for(int k=0; k<11; k++){
                if(k!=j){
                    omega_x = omega_x * (x_uzup[i] - x_2[k]);
                    omega_xj = omega_xj * (x_2[j] - x_2[k]);
                }
            }
            suma = suma + y_2[j] * omega_x / omega_xj;
        }
        y_uzup[i] = suma;
    }

    printf("otrzymane wartosci z uzupelnieniem: \n");
    for(int i=0; i<100; i++){
        printf("f(%f) = %f, ", x_uzup[i], y_uzup[i]);
        if((i+1)%5 == 0){
            printf("\n");
        }
    }

    ////
    //// 16 wezlow 
    ////
    printf("\n-------------------------------------\n");

    double y_3[16];
    double x_3[16];
    skok = (5 - (-5));
    skok = skok / 14;

    for(int i=0; i<16; i++){
        x_3[i] = -5 + i*skok;
    }
    
    printf("otrzymane wartosci funkcji dla  16 wezlow: \n");
    for(int i=0; i<16; i++){
        y_3[i] = f(x_3[i]);
        printf("%f | ", y_3[i]);
    }
    printf("\n");

    for(int i=0; i<100; i++){
        suma = 0;
        for(int j=0; j<16; j++){
            omega_x = 1;
            omega_xj = 1;
            for(int k=0; k<16; k++){
                if(k!=j){
                    omega_x = omega_x * (x_uzup[i] - x_3[k]);
                    omega_xj = omega_xj * (x_3[j] - x_3[k]);
                }
            }
            suma = suma + y_3[j] * omega_x / omega_xj;
        }
        y_uzup[i] = suma;
    }

    printf("otrzymane wartosci z uzupelnieniem: \n");
    for(int i=0; i<100; i++){
        printf("f(%f) = %f, ", x_uzup[i], y_uzup[i]);
        if((i+1)%5 == 0){
            printf("\n");
        }
    }

    ////
    //// 21 wezlow 
    ////
    printf("\n-------------------------------------\n");

    double y_4[21];
    double x_4[21];
    skok = (5 - (-5));
    skok = skok / 19;

    for(int i=0; i<21; i++){
        x_4[i] = -5 + i*skok;
    }
    
    printf("otrzymane wartosci funkcji dla  21 wezlow: \n");
    for(int i=0; i<21; i++){
        y_4[i] = f(x_4[i]);
        printf("%f | ", y_4[i]);
    }
    printf("\n");

    for(int i=0; i<100; i++){
        suma = 0;
        for(int j=0; j<21; j++){
            omega_x = 1;
            omega_xj = 1;
            for(int k=0; k<21; k++){
                if(k!=j){
                    omega_x = omega_x * (x_uzup[i] - x_4[k]);
                    omega_xj = omega_xj * (x_4[j] - x_4[k]);
                }
            }
            suma = suma + y_4[j] * omega_x / omega_xj;
        }
        y_uzup[i] = suma;
    }

    printf("otrzymane wartosci z uzupelnieniem: \n");
    for(int i=0; i<100; i++){
        printf("f(%f) = %f, ", x_uzup[i], y_uzup[i]);
        if((i+1)%5 == 0){
            printf("\n");
        }
    }

    ////
    //// 21 wezlow - chebyszew
    ////
    printf("\n-------------------------------------\n");

    double y_c[21];
    double x_c[21];
    double xmin = -5;
    double xmax = 5;

    for (int m = 0; m < 21; m++) {
        double x_m = (xmax - xmin) * cos((M_PI * (2 * m + 1)) / 42);
        x_m = (x_m + xmin + xmax);
        x_m = x_m / 2.0;
        x_c[m] = x_m;
    }

    printf("otrzymane wartosci funkcji dla  21 wezlow: \n");
    for(int i=0; i<21; i++){
        y_c[i] = f(x_c[i]);
        printf("%f | ", y_c[i]);
    }
    printf("\n");

    for(int i=0; i<100; i++){
        suma = 0;
        for(int j=0; j<21; j++){
            omega_x = 1;
            omega_xj = 1;
            for(int k=0; k<21; k++){
                if(k!=j){
                    omega_x = omega_x * (x_uzup[i] - x_c[k]);
                    omega_xj = omega_xj * (x_c[j] - x_c[k]);
                }
            }
            suma = suma + y_c[j] * omega_x / omega_xj;
        }
        y_uzup[i] = suma;
    }

    printf("otrzymane wartosci z uzupelnieniem: \n");
    for(int i=0; i<100; i++){
        printf("f(%f) = %f, ", x_uzup[i], y_uzup[i]);
        if((i+1)%5 == 0){
            printf("\n");
        }
    }
}