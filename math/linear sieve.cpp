class linear_sieve{
    
    private:
    long long S=0;
    std::vector<long long> divisor_,prime;
    
    public:
    void init(long long N){
        S=N;
        prime.clear();
        divisor_.resize(N+1);
        for(long long i=0;i<N+1;i++){
            divisor_[i]=0;
        }
        
        if(N>=1){
            divisor_[1]=1;
        }
        
        
        for(long long i=2;i<=N;i++){
            if(divisor_[i]==0){
                divisor_[i]=i;
                prime.push_back(i);
            }
            for(long long j=0;j<=prime.size() && prime[j]<=divisor_[i] && i*prime[j]<=N ;j++){
                divisor_[prime[j]*i]=prime[j];
            }
        }
    }
    
    linear_sieve(long long N){
        init(N);
    }
    
    std::vector<long long> primearray(long long X){
        std::vector<long long> R;
        if(X<=1)return R;
        if(S<X)init(X);
        for(long long i=0;i<prime.size();i++){
            if(prime[i]<=X){
                R.push_back(prime[i]);
            }
        }
        return R;
    }
    
    long long divisor(long long X){
        if(X<=0)return -1;
        if(S<X)init(X);
        return divisor_[X];
    }
    
    std::vector<long long> factorization(long long X){
        std::vector<long long> R;
        if(X<=1)return R;
        if(S<X)init(X);
        R = factorization(X/divisor_[X]);
        R.push_back(divisor_[X]);
        return R;
    }
    
    std::vector<long long> exp_enum(long long N,long long M,long long mod=LLONG_MAX){
        std::vector<long long> R;
        if(N<0 || M<0)return R;
        if(S<N)init(N);
        
        for(long long i=0;i<=N;i++){
            R.push_back(-1);
        }
        R[0]=0;
        if(N>=1)R[1]=1;
        
        for(long long i=0;i<prime.size();i++){
            if(prime[i]>N)continue;
            long long r=1,b=prime[i],e=M;
            while(e){
                if(e&1){
                    r=(r*b)%mod;
                }
                b=(b*b)%mod;
                e >>=1;
            }
            R[prime[i]]=r;
        }
        
        for(long long i=0;i<=N;i++){
            if(R[i]!=-1)continue;
            R[i] = (R[i/divisor_[i]]*R[divisor_[i]])%mod;
        }
        return R;
    }
};
