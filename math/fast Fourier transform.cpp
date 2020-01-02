class fast_Fourier_transform{
    private:
    const double PI=3.14159265358979; 
    
    vector<complex<double>> DFT(vector<complex<double>> A){
        int N=A.size();
        if(N==1)return A;
        vector<complex<double>> A0(N/2),A1(N/2),iA0,iA1,iA(N);
        for(int i=0;i<N;i++){
            if(i%2==0){
                A0[i/2]=A[i];
            }else{
                A1[i/2]=A[i];
            }
        }
        iA0=DFT(A0);
        iA1=DFT(A1);
        
        for(int i=0;i<N;i++){
            complex<double> ith_zeta = complex<double>(cos(2*PI*i/N),sin(2*PI*i/N));
            iA[i]=(iA0[i%(N/2)]+ ith_zeta*iA1[i%(N/2)]);
        }
        return iA;
    }
    
    vector<complex<double>> iDFT(vector<complex<double>> iA){
        int N=iA.size();
        vector<complex<double>> A,dA,rA;
        dA=DFT(iA);
        for(int i=0;i<N;i++){
            rA.push_back(dA[(N-i)%N]);
            A.push_back(rA[i]/complex<double>(N,0));
        }
        return A;
    }
    
    public:
    vector<int> convolution(vector<int> A,vector<int> B){
        int deg = A.size() + B.size() -1;
        int N=1;
        while(N<deg){N<<=1;}
        A.resize(N);B.resize(N);
        vector<complex<double>> dC(N),iC(N),dA,iA,dB,iB;
        vector<int> C(N);
        for(int i=0;i<A.size();i++){
            dA.push_back(A[i]);
        }
        for(int i=0;i<B.size();i++){
            dB.push_back(B[i]);
        }
        iA=DFT(dA);iB=DFT(dB);
        for(int i=0;i<N;i++){
            iC[i]=iA[i]*iB[i];
        }
        dC=iDFT(iC);
        for(int i=0;i<dC.size();i++){
            C[i]=(int)(0.1+dC[i].real());
        }
        return C;
    }
    
};
