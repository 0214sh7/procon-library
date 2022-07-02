class iterated_function{
    private:
    std::vector<int> T[64];
    int N;
    
    public:
    void init(std::vector<int> F){
        N = F.size();
        T[0] = F;
        for(int j=1;j<64;j++){
            T[j].resize(N);
            for(int i=0;i<N;i++){
                T[j][i] = T[j-1][T[j-1][i]];
            }
        }
        
    }

    iterated_function(std::vector<int> F){
        init(F);
    }

    int solve(int x,long long k){
        if(!(0<=x && x<N) || k<0){
            return -1;
        }

        int y = x;
        for(int i=0;(k>>i)>0;i++){
            if((k>>i)%2==1){
                y = T[i][y];
            }
        }

        return y;
    }
    
};
