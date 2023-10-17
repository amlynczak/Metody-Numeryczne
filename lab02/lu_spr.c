#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define N 5

double d_rand(double min, double max){
	double r = (double) rand()/RAND_MAX;
	return r*(max-min) + min;
    }

void wypisz_wek(double *tab, int roz){
    for(int i=0; i<roz; i++){
        printf("[%d] = %f, ", i, tab[i]);
    }
    printf("\n");
}

void wypisz_mac(double tab[N][N]){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            printf("[%d][%d] = %f ", i, j, tab[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(){
    double q;
    srand(time(NULL));
    q = d_rand(0.2, 5); //wyznaczenie q z zakresu 0.2 do 5
    printf("q = %f \n", q);

    if(q==1){
        printf("dla q = 1 uklad nie posiada rozwiazan \n");
        abort();
    }

    double A[N][N] = {
        {q*0.0002, 1, 6, 9, 10}, 
        {0.0002, 1, 6, 9, 10},
        {1, 6, 6, 8, 6},
        {5, 9, 10, 7, 10},
        {3, 4, 9, 7, 9}
    };//dana na zajeciach macierz

    printf("macierz A: \n");
    wypisz_mac(A);

    double b[N] = {10, 2, 9, 9, 3};//wyrazy wolne

    //utworzenie macierzy L - z parametrami l - oraz macierzy - kopii macierzy A, ktora bedzie przeksztalcana
    double L[N][N] = {
        {1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1}
    };
    double U[N][N];
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            U[i][j] = A[i][j];
        }
    }

    //uzupelnianie macierzy L oraz przeksztalcanie macierzy A - tutaj U

    for(int i=0; i<N; i++){
        for(int j=i+1; j<N; j++){
            double l = U[j][i]/U[i][i];
            L[j][i] = l;
            for(int k=i; k<N; k++){
                U[j][k] = U[j][k] - U[i][k] * l;
            }
        }
    }

    printf("macierz U: \n");
    wypisz_mac(U);
    printf("macierz L: \n");
    wypisz_mac(L);

    //
    //krok 2 - Ly = b
    //
    printf("-------------------------------\n");

    double y[N] = {0.};
    
    double val = 0;
    for(int i=0; i<=N; i++){
        val = b[i];
        for(int j = 0; j<=i; j++){
            val = val - y[j] * L[i][j];
        }
        y[i] = val/L[i][i];
    }

    printf("wektor y: \n");
    wypisz_wek(y, 5);

    //
    //krok 3 - Ux = y
    //
    printf("-------------------------------\n");

    double x[N] = {0.};

    for(int i=N-1; i>=0; i--){
        val = y[i];
        for(int j=N-1; j>=i; j--){
            val = val - x[j] * U[i][j];
        }
        x[i] = val/U[i][i];
    }

    printf("wektor x: \n");
    wypisz_wek(x, 5);

    //
    //krok 4 - Ax = c
    //
    printf("-------------------------------\n");

    double c[5] = {0.};

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            c[i] = c[i] + A[i][j] * x[j];
        }
    }

    printf("wektor c: \n");
    wypisz_wek(c, 5);

    //
    //krok 5 - odchylenie
    //

    double odchyl = 0.;
    double suma = 0.;
    for(int i=0; i<N; i++){
        suma = suma + pow((c[i]-b[i]), 2);
    }
    odchyl = 0.2 * sqrt(suma);

    printf("odchylenie: %f \n", odchyl);
}
