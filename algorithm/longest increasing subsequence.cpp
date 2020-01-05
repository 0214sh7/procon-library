std::vector<long long> LIS(std::vector<long long> A){
    int N=A.size();
    std::vector<long long> D;
    for(int i=0;i<N;i++){
        int pos=distance(D.begin(),lower_bound(D.begin(), D.end(),A[i]));
        if(pos==D.size()){
            D.push_back(A[i]);
        }else{
            D[pos]=A[i];
        }
    }
    return D;
}
