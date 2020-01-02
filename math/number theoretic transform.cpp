class number_theoretic_transform{
    private:
    
    const long long MOD = 998244353;
    const long long k = 119;
    const long long n = 23;
    const long long pri_root = 3;
    //MOD=k*2^n+1
    
    long long BE(long long b,long long e){
        long long r=1;
        while(e){
            if(e&1){
                r=(r*b)%MOD;
            }
            b=(b*b)%MOD;
            e >>=1;
        }
        return r;
    }
    
    vector<long long> DFT(vector<long long> A){
        int N=A.size();
        if(N==1)return A;
        vector<long long> A0(N/2),A1(N/2),iA0,iA1,iA(N);
        for(int i=0;i<N;i++){
            if(i%2==0){
                A0[i/2]=A[i];
            }else{
                A1[i/2]=A[i];
            }
        }
        iA0=DFT(A0);
        iA1=DFT(A1);
        
        long long omega=BE(pri_root,k*(1<<n)/N);
        long long ith_zeta = 1;
        for(int i=0;i<N;i++){
            iA[i]=(iA0[i%(N/2)]+ ith_zeta*iA1[i%(N/2)])%MOD;
            ith_zeta = (ith_zeta*omega)%MOD;
        }
        return iA;
    }
     
    vector<long long> iDFT(vector<long long> iA){
        int N=iA.size();
        long long N_inverse = BE(N,MOD-2);
        vector<long long> A,dA,rA;
        dA=DFT(iA);
        for(int i=0;i<N;i++){
            rA.push_back(dA[(N-i)%N]);
            A.push_back((rA[i]*N_inverse)%MOD);
        }
        return A;
    }
    
    
    public:
    
    vector<long long> convolution(vector<long long> A,vector<long long> B){
        int deg = A.size() + B.size() -1;
        long long N=1;
        while(N<deg){N<<=1;}
        A.resize(N);B.resize(N);
        for(int i=0;i<A.size();i++){
            A[i]%=MOD;
        }
        for(int i=0;i<B.size();i++){
            B[i]%=MOD;
        }
        vector<long long> C(N),iC(N),iA,iB;
        iA=DFT(A);iB=DFT(B);
        for(int i=0;i<N;i++){
            iC[i]=(iA[i]*iB[i])%MOD;
        }
        C=iDFT(iC);
        C.resize(deg);
        return C;
    }
    
};
