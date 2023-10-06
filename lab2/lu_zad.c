#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define N 5

double d_rand(double min, double max){
	double r = (double) rand()/RAND_MAX;
	return r*(max-min) + min;
    }

void wypisz_wek(float *tab, int roz){
    for(int i=0; i<roz; i++){
        printf("[%d] = %f, ", i, tab[i]);
    }
    printf("\n");
}

void wypisz_mac(float tab[N][N]){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            printf("[%d][%d] = %f ", i, j, tab[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(){
    float q;
    srand(time(NULL));
    q = d_rand(0.2 , 5); //wyznaczenie losowego q
    //q=0.2;
    printf("q = %f  \n", q);

    if(q==1){
        printf("uklad nie posiada rozwiazan dla q =1\n");
        abort();
    }
/*for(; q<5; q = q + 0.001){
    if(q != 1){*/
    //wyrazy wolne
    float b[N] = {10, 2, 9, 9, 3};

    //macierz A z zadania
    float A[N][N] = {
        {q*0.0002, 1, 6, 9, 10}, 
        {0.0002, 1, 6, 9, 10},
        {1, 6, 6, 8, 6},
        {5, 9, 10, 7, 10},
        {3, 4, 9, 7, 9}
    };
    
    //wypisanie macierzy A z juz ustalonym q
    printf("macierz A: \n");
    wypisz_mac(A);

    //tworze macierze u oraz L, przypisujac na przekatnej L jedynki
    float U[N][N];
    float L[N][N];

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            L[i][j] = 0;
            if(i==j){
                L[i][j] = 1;
            }
        }
    }
    
    //macierz U staje sie poczatkowo kopia macierzy A
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            U[i][j] = A[i][j];
        }
    }

    //metoda eliminacji Gaussa z jednoczyesnym uzupelnianiem macierzy L
    for(int i=0; i<N-1; i++){
        for(int j=i+1; j<N; j++){
            float l = U[j][i]/U[i][i];
            L[j][i] = l;
            for(int k=0; k<N; k++){
                U[j][k] = U[j][k] - l*U[i][k];
            }
        }
    }
    
    //wypisanie koncowej macierzy U oraz L
    printf("macierz L: \n");
    wypisz_mac(L);

    printf("macierz U: \n");
    wypisz_mac(U);
    
    float LxU[N][N]; //macierz do sprawdzenia czy macierze L i U sa poprawne

    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            LxU[i][j] = 0;
            for(int k = 0; k<N; k++){
                LxU[i][j] += L[i][k] * U[k][j];
            }
        }
    }

    //wypisanie macierzy LxU do sprawdzenia poprawnosci wczesniejszych wyliczen
    printf("macierz LxU: \n");
    wypisz_mac(LxU);

    //
    //krok 2 Ly = b
    //
    printf("-------------------------------------\n");

    float y[N]; //tworze wektor y
    
    for(int i=0; i<N; i++){
        y[i] = b[i];
        for(int j=0; j<i; j++){
            y[i] = y[i] - L[i][j] * y[j];
        }
        y[i] = y[i]/L[i][i];
    }

    printf("wektor y: \n");
    wypisz_wek(y, 5);

    //
    //krok 3 Ux = y
    //
    printf("-------------------------------------\n");

    float x[N]; //tworze wektor x

    for(int i=N-1; i>=0; i--){
        x[i] = y[i];
        for(int j=i+1; j<N; j++){
            x[i] = x[i] - U[i][j] * x[j];
        }
        x[i] = x[i]/U[i][i];
    }

    printf("wektor x: \n");
    wypisz_wek(x, 5);

    //
    //krok 4 Ax = c;
    //
    printf("-------------------------------------\n");

    float c[N];

    for(int i = 0; i<N; i++){
        c[i] = 0;
        for(int j = 0; j<N; j++){
            printf("%f, %f, %f \n", A[i][j], c[i], x[j]);
            c[i] = c[i] + (A[i][j] * x[j]);
        }
    }

    printf("wektor c: \n");
    wypisz_wek(c, 5);

    float odchyl = 0;
    float suma = 0;

    for(int i=0; i<N; i++){
        suma = suma + pow((c[i]-b[i]), 2);
    }
    printf("\n");

    odchyl = 0.2 * sqrt(suma);
    printf("odchylenie: %f \n", odchyl);
    /*
    FILE *fq;
    FILE *fodchyl;
    fq = fopen("q.txt", "a");
    fodchyl = fopen("odchyl.txt", "a");
    fprintf(fq, "%f \n", q);
    fprintf(fodchyl, "%f \n", odchyl);
    fclose(fq);
    fclose(fodchyl);
    }
}*/
}