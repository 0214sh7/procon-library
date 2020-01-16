//小数点以下切り上げ
long long roundup(long long a,long long b){
    return (a+b-1)/b;
}

//階乗
long long fact(long long x,long long MOD=INT_MAX){
    long long k=1;
    for(int i=1;i<=x;i++){
        k=(k*i)%MOD;
    }
    return k;
}

//最大公約数
long long gcd(long long a,long long b){
    a=std::abs(a);
    b=std::abs(b);
    if(a>b)std::swap(a,b);
    if(a==0){
        return b;
    }
    
    long long r=a%b;
    while(r){
        a=b;
        b=r;
        r=a%b;
    }
    return b;
}

//最小公倍数
long long lcm(long long a,long long b){
    if(std::abs(a)>std::abs(b))std::swap(a,b);
    if(a==0){
        return b;
    }
    
    long long s=a,t=b;
    a=std::abs(a);
    b=std::abs(b);
    if(a>b)std::swap(a,b);
    
    long long r=a%b;
    while(r){
        a=b;
        b=r;
        r=a%b;
    }
    
    return s / b * t;
}

//素数判定
bool prime(long long X){
    if(X<2)return false;
    for(long long i=2;i*i<=X;i++){
        if(X%i==0){
            return false;
        }
    }
    return true;
}

//素数列挙
std::vector<long long> primearray(long long N){
    std::vector<long long> R;
    std::vector<bool> prime;
    for(int i=0;i<=N;i++){
        prime.push_back(true);
    }
    if(N<2){
        return R;
    }
    prime[0]=false;
    prime[1]=false;
    for(long long i=2;i*i<=N;i++){
        if(!prime[i])continue;
        for(int j=2*i;j<=N;j+=i){
            prime[j]=false;
        }
    }
    for(long long i=0;i<prime.size();i++){
        if(prime[i]){
            R.push_back(i);
        }
    }
    return R;
}

//累乗(繰り返し二乗法)
long long power(long long b,long long e,long long MOD=INT_MAX){
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

//逆元(素数MOD)
long long inverse(long long b,long long MOD){
    long long r=1,e=MOD-2;
    while(e){
        if(e&1){
            r=(r*b)%MOD;
        }
        b=(b*b)%MOD;
        e >>=1;
    }
    return r;
}
