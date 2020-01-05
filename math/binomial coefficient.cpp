std::vector<long long> binomial_coefficient(long long N){
    const long long MOD = 998244353;
    std::vector<long long> fac;
    std::vector<long long> facIE;
    std::vector<long long> comb;
    for(int i=0;i<=N;i++){
        if(i==0){
            fac.push_back(1);
        }else{
            fac.push_back(i*fac[i-1]%MOD);
        }
    }
    for(int i=0;i<=N;i++){
        long long r=1,b=fac[i],e=MOD-2;
        while(e){
            if(e&1){
                r=(r*b)%MOD;
            }
            b=(b*b)%MOD;
            e >>=1;
        }
        facIE.push_back(r);
    }
    for(int i=0;i<=N;i++){
        long long r=fac[N];
        r = (r*facIE[i])%MOD;
        r = (r*facIE[N-i])%MOD;
        comb.push_back(r);
    }
    return comb;
}
