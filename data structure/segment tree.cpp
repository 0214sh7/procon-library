template<typename T>
class segmenttree{
    /*
    Copyright (c) 2022 0214sh7
    https://github.com/0214sh7/library/
    */
    private:
    int n;
    
    std::vector<T> dat;
    std::function<T(T,T)> calc;
    T identity;
    public:
    
    void init(int N,std::function<T(T,T)> func,T Identity){
        n=1;
        while(n<N)n*=2;
        dat.resize(2*n-1);
        for(int i=0;i<2*n-1;++i){
            dat[i]=Identity;
        }
        calc = func;
        identity = Identity;
    }
    
    segmenttree(int N,std::function<T(T,T)> func,T Identity){
        init(N,func,Identity);
    }
    
    void update(int k,T a){
        k+=n-1;
        dat[k]=a;
        while(k>0){
            k=(k-1)/2;
            dat[k]=calc(dat[2*k+1],dat[2*k+2]);
        }
    }
    
    T query(int a,int b){
        a+=n-1;
        b+=n-1;
        T L= identity,R = identity;
        while(a < b){
            if(a % 2 == 0){
                L = calc(L,dat[a]);
                a++;
            }
            a = (a-1)/2;
            if(b % 2 == 0){
                R = calc(dat[b-1],R);
                b--;
            }
            b = (b-1)/2;
        }
        R = calc(L,R);
        return R;
    }
    
};
