class rollinghash{
    private:
    const long long mod = (1LL << 61)-1;
    std::vector<long long> Base = {12345,10000000};
    std::vector<long long> BaseInv;
    std::vector<std::vector<long long>> BaseInvExp;
    const long long h = 100;
    
    long long product(long long a,long long b){
        const long long m = 1LL << 31;
        long long a1 = a/m,a2 = a%m;
        long long b1 = b/m,b2 = b%m;
        
        long long r = 0 , s;
        r = (r + 2*a1*b1) % mod;
        s = (a1*b2 + b1*a2) % mod;
        long long s1 = s/m,s2 = s%m;
        s = (2*s1+m*s2) % mod;
        r = (r + s) % mod;
        r = (r + a2*b2) % mod;
        
        return r;
    }
    
    long long power(long long b,long long e){
        long long r=1;
        while(e){
            if(e&1){
                r=product(r,b)%mod;
            }
                b=product(b,b)%mod;
                e >>=1;
        }
        return r;
    }
    
    public:
    std::string S;
    std::vector<std::vector<long long>> H,Hsum;
    
    void init(std::string cs){
        S=cs;
        int n=S.size();
        
        BaseInv.resize(Base.size());
        BaseInvExp.resize(Base.size());
        H.resize(Base.size());
        Hsum.resize(Base.size());
        for(int i=0;i<Base.size();i++){
            BaseInvExp[i].assign(n+1,1);
            H[i].assign(n+1,0);
            Hsum[i].assign(n+1,0);
        }
        
        //逆元
        for(int i=0;i<Base.size();i++){
            BaseInv[i]=power(Base[i],mod-2);
        }
        for(int i=0;i<Base.size();i++){
            for(int j=0;j<n;j++){
                BaseInvExp[i][j+1] = product(BaseInvExp[i][j],BaseInv[i]);
            }
        }
        
        //本体
        for(int i=0;i<Base.size();i++){
            long long b=1;
            for(int j=0;j<n;j++){
                H[i][j]=product(b,S[j]+h);
                b=product(b,Base[i]);
            }
        }
        
        //累積和
        for(int i=0;i<Base.size();i++){
            for(int j=0;j<n;j++){
                Hsum[i][j+1]=(Hsum[i][j]+H[i][j])%mod;
            }
        }
    }
    
    rollinghash(std::string S){
        init(S);
    }
    
    std::vector<long long> get(int l,int r){
        std::vector<long long> R;
        for(int i=0;i<Base.size();i++){
            long long g = (Hsum[i][r]-Hsum[i][l]+mod)%mod;
            g=product(g,BaseInvExp[i][l]);
            R.push_back(g);
        }
        return R;
    }
    
};
