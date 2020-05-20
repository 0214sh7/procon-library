class compress{
    private:
    std::vector<int> E;
    
    public:
    void init(std::vector<long long> A){
        E.clear();
        sort(A.begin(),A.end());
        for(int i=0;i<A.size();i++){
            if(i==0 || A[i]!=A[i-1]){
                E.push_back(A[i]);
            }
        }
    }
    
    int size(){
        return (int)E.size();
    }
    
    int value(int x){
        if(0<=x && x<(int)E.size()){
            return E[x];
        }else{
            return 0;
        }
    }
    
    int index(int X){
        return (upper_bound(E.begin(),E.end(),X))-E.begin()-1;
    }
    
};
