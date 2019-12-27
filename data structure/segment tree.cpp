class segmenttree{
    private:
    int n;
    long long identity = 0;//単位元
    std::vector<long long> dat;
    public:
    
    void init(int N){
        n=1;
        while(n<N)n*=2;
        dat.clear();
        for(int i=0;i<2*n-1;++i){
            dat.push_back(identity);
        }
    }
    
    long long calc();
    
    void update(int k,long long a){
        k+=n-1;
        dat[k]=a;
        while(k>0){
            k=(k-1)/2;
            dat[k]=calc(dat[2*k+1],dat[2*k+2]);
        }
    }
    
    long long query(long long a,long long b){
        a+=n;
        b+=n;
        long long R=0;
        while(a < b){
            if(a % 2 == 1){
                R = calc(R, dat[a - 1]);
                a += 1;
            }
            a /= 2;
            if(b % 2 == 1){
                b -= 1;
                R = calc(R, dat[b - 1]);
            }
            b /= 2;
        }
        return R;
    }
    
    long long calc(long long a,long long b){
        //your monoid here
        return a+b;
    }
    
};
