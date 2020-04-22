std::vector<long long> slide_minimum(std::vector<long long> A,int K){
    std::vector<long long> R;
    int N = A.size();
    std::deque<int> D;
    for(int i=0;i<N;i++){
        while(!D.empty() && A[D.back()]>=A[i]){D.pop_back();}
        D.push_back(i);
        if(i-K+1>=0){
            R.push_back(A[D.front()]);
            if(D.front()==i-K+1){
                D.pop_front();
            }
        }
    }
    return R;
}
