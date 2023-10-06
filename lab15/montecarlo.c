#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define frand() ((double)rand())/(RAND_MAX) * 4.0 - 2.0

double norma(double R[3]){
    double tmp;
    for(int i=0; i<3; i++){
        tmp += R[i]*R[i];
    }
    tmp = sqrt(tmp);
    return tmp;
}

int main(){
    int n = 10; //wartosc n zmienna w zaleznosci od podpunktu
    double R1[3] = {-1.0, -1.0, -1.0};
    double R2[3] = {1.0, 1.0, 1.0};

    FILE *fp;
    fp = fopen("wartosci.txt", "a");
    fprintf(fp, "n = %d\n", n);

    
    double r_i[3][n];
    for(int i=0; i<n; i++){
        for(int j=0; j<3; j++){
            r_i[j][i] = frand();
        }
    }//przypisanie wartosci do wektora

    
    for(int i=0; i<n; i++){
        printf("wektor %d: ", i);
        for(int j=0; j<3; j++){
            printf("%f, ", r_i[j][i]);
        }
        printf("\n");
    }//wyswietlenie wektora

    

    //metoda Monte Carlo
    double rho = 1.0;
    double V = 4.0 * 4.0 * 4.0;
    double theta;
    double dist = 0;
    double I_1 = 0;
    double warian;
    double war1 = 0, war2;
    double odchyl;

    for(int i=0; i<n; i++){
        if(r_i[0][i]<=1 && r_i[0][i]>=-1 && r_i[1][i]<=1 && r_i[1][i]>=-1 && r_i[2][i]<=1 && r_i[2][i]>=-1){
            theta = 1;
            double R2_R1[3];//R2-R1
            for(int k=0; k<3; k++){
                R2_R1[k] = R2[k] - R1[k];
            }
            double norm = norma(R2_R1);//norma(R2-R1)
            double tmp1[3], tmp2[3]; 
            //(R*(R2-R1))/norma(R2-R1)
            for(int k=0; k<3; k++){
                tmp1[k] = r_i[k][i] * R2_R1[k];
                tmp1[k] = tmp1[k]/norm;
                //(R2-R1)/norma(R2-R1)
                tmp2[k] = R2_R1[k]/norm;
            }
            //wymnozenie tych dwoch tmp wektorow
            double tmp[3];
            for(int k=0; k<3; k++){
                tmp[k] = tmp1[k] * tmp2[k];
            }
            double tmp_last[3];
            for(int k=0; k<3; k++){
                tmp_last[k] = r_i[k][i] - tmp[k];
            }
            dist = norma(tmp_last);//obliczona odleglosc

        }else{
            theta = 0;//w tym przypadku dist ma wartosc ostatniej wyliczonej wartosci, ale nie ma znaczenia przez theta = 0
        }
        
        //liczenie calki
        I_1 = I_1 + (V * rho * dist * dist * theta);
        war1 = war1 + pow((V * rho * dist * dist * theta), 2); //do obliczenia wariancji
    }
    I_1 = I_1/n;
    printf("wartosc calki: %f\n", I_1);
    fprintf(fp, "wartosc calki: %f\n", I_1);

    //liczenie wariancji
    war2 = I_1 * n;
    war2 = pow(war2, 2);
    war2 = war2/n;

    warian = war1 - war2;
    warian = warian/n;
    printf("wariancja = %f\n", warian);

    //odchylenie standardowe

    odchyl = sqrt(warian/n);
    printf("odchylenie = %f\n", odchyl);
    fprintf(fp, "odchylenie standardowe: %f\n\n", odchyl);

    fclose(fp);
}