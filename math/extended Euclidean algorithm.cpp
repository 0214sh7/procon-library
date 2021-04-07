std::pair<long long,std::pair<long long,long long>> extgcd(long long a,long long b){
    /*
    Copyright (c) 2021 0214sh7
    https://github.com/0214sh7/library/
    */
    std::vector<long long> q;
    while(b!=0){
        long long r = a%b;
        r+=b;
        r%=b;
        long long q_ = (a-r)/b;
        q.push_back(q_);
        a = b;
        b = r;
    }
    
    long long g=a,x=1,y=0;
    if(g<0){
        g*=-1;
        x*=-1;
    }
    for(int i=-1+(int)q.size();i>=0;i--){
        long long tmp = y;
        y = x-q[i]*y;
        x = tmp;
    }
    
    return {g,{x,y}};
}
