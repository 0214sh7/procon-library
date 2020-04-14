int totient(int N){
    if(N<0){
        return 0;
    }
    int R = N;
    for(int i=2;i*i<=N;i++){
        if(N%i==0){
            R -= R/i;
            while(N%i==0){
                N/=i;
            }
        }
    }
    if(N>1){
        R -= R/N;
    }
    return R;
}

std::vector<int> totient_array(int N){
    std::vector<int> R(N+1);
    for(int i=0;i<=N;i++){
        R[i]=i;
    }
    for(int i=2;i<=N;i++){
        if(R[i]!=i)continue;
        for(int j=i;j<=N;j+=i){
            R[j]-=(R[j]/i);
        }
    }
    return R;
}
