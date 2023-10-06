#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define K 10
#define N pow(2,K)
#define O 2*M_PI/N
#define SWAP(a, b) do { \
    typeof(a) _temp = (a); \
    (a) = (b); \
    (b) = _temp; \
} while (0)

void four1(float data[], unsigned long nn, int isign){
    unsigned long n,mmax,m,j,istep,i;
    double wtemp,wr,wpr,wpi,wi,theta;
    float tempr,tempi;
    
    n=nn << 1;
    j=1;
    for (i=1;i<n;i+=2) {
        if (j > i) {
            SWAP(data[j],data[i]);
            SWAP(data[j+1],data[i+1]);
        }
        m=nn;
        while (m >= 2 && j > m) {
            j -= m;
            m >>= 1;
        }
        j += m;
    }
    mmax=2;
    while (n > mmax) {
        istep=mmax << 1;
        theta=isign*(6.28318530717959/mmax);
        wtemp=sin(0.5*theta);
        wpr = -2.0*wtemp*wtemp;
        wpi=sin(theta);
        wr=1.0;
        wi=0.0;
        for (m=1;m<mmax;m+=2) {
            for (i=m;i<=n;i+=istep) {
                j=i+mmax; 
                tempr=wr*data[j]-wi*data[j+1];
                tempi=wr*data[j+1]+wi*data[j];
                data[j]=data[i]-tempr;
                data[j+1]=data[i+1]-tempi;
                data[i] += tempr;
                data[i+1] += tempi;
            }
            wr=(wtemp=wr)*wpr-wi*wpi+wr;
            wi=wi*wpr+wtemp*wpi+wi;
        }
        mmax=istep;
    }
}


void realft(float data[], unsigned long n, int isign) {
    void four1(float data[], unsigned long nn, int isign);
    unsigned long i,i1,i2,i3,i4,np3;
    float c1=0.5,c2,h1r,h1i,h2r,h2i;
    double wr,wi,wpr,wpi,wtemp,theta;
    theta=3.141592653589793/(double) (n>>1);
    if (isign == 1) {
        c2 = -0.5;
        four1(data,n>>1,1);
    } else {
    c2=0.5; 
    }
    wtemp=sin(0.5*theta);
    wpr = -2.0*wtemp*wtemp;
    wpi=sin(theta);
    wr=1.0+wpr;
    wi=wpi;
    np3=n+3;
    for (i=2;i<=(n>>2);i++) {
        i4=1+(i3=np3-(i2=1+(i1=i+i-1)));
        h1r=c1*(data[i1]+data[i3]);
        h2r = -c2*(data[i2]+data[i4]);
        h2i=c2*(data[i1]-data[i3]);
        data[i1]=h1r+wr*h2r-wi*h2i;
        data[i2]=h1i+wr*h2i+wi*h2r;
        data[i3]=h1r-wr*h2r+wi*h2i;
        data[i4] = -h1i+wr*h2i+wi*h2r;
        wr=(wtemp=wr)*wpr-wi*wpi+wr;
        wi=wi*wpr+wtemp*wpi+wi;
    }
    if (isign == 1) {
        data[1] = (h1r=data[1])+data[2];
        data[2] = h1r-data[2];
    } else {
        data[1]=c1*((h1r=data[1])+data[2]);
        data[2]=c1*(h1r-data[2]);
        four1(data,n>>1,-1); 
    } 
}

void sinft(float y[], int n){
    void realft(float data[], unsigned long n, int isign);
    int j,n2=n+2;
    float sum,y1,y2;
    double theta,wi=0.0,wr=1.0,wpi,wpr,wtemp;
    theta=3.14159265358979/(double) n;
    wtemp=sin(0.5*theta);
    wpr = -2.0*wtemp*wtemp;
    wpi=sin(theta);
    y[1]=0.0;
    for (j=2;j<=(n>>1)+1;j++) {
        wr=(wtemp=wr)*wpr-wi*wpi+wr;
        wi=wi*wpr+wtemp*wpi+wi;
        y1=wi*(y[j]+y[n2-j]);
        y2=0.5*(y[j]-y[n2-j]);
        y[j]=y1+y2;
        y[n2-j]=y1-y2;
    }
    realft(y,n,1);
    y[1]*=0.5;
    sum=y[2]=0.0;
    for (j=1;j<=n-1;j+=2) {
        sum += y[j];
        y[j]=y[j+1];
        y[j+1]=sum;
    }
}

void dyskryminacja(float data[], int n, float threshold){
    for (int i = 0; i < n; i += 2) {
        if (fabs(data[i]) < threshold) {
            data[i] = 0.0;
            data[i + 1] = 0.0;
        }
    }
}

double y_0(double t){
    return sin(O*t)+sin(2*O*t)+sin(3*O*t);
}

double rand_alpha(){
    double Y = rand()/RAND_MAX;
    double X = rand()/(RAND_MAX+1.0);
    if(Y>0.5){
        return 2 * 1 * X;
    }else{
        return 2 * (-1) * X;
    }
}

int main(){
    srand(time(NULL));

    int n = N;
    float signal[n];
    float noisySignal[n];
    float y_max = 0;
    float threshold;

    for(int i=0; i<n; i++){
        noisySignal[i] = y_0(i) + rand_alpha();
        signal[i] = y_0(i);
        if(noisySignal[i] > y_max){
            y_max = noisySignal[i];
        }
    }

    //transformata
    sinft(noisySignal, n);

    //dyskryminacja
    threshold = 0.25 * fabs(y_max);
    dyskryminacja(noisySignal, n, threshold);

    //transformata odwrotna
    sinft(noisySignal, n);

    //przemnozenie przez 2/n
    for(int i=0; i<n; i++){
        noisySignal[i] = noisySignal[i] * (2.0 / n);
    }
}