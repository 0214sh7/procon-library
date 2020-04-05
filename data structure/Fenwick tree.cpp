class Fenwick_tree{
    private:
    std::vector<long long> BIT;
    
    public:
    
    void add(int a,long long w){
        for(int x=a;x<BIT.size();x|=(x+1)){
            BIT[x]+=w;
        }
    }
    
    void init(int n){
        BIT.clear();
        for(int i=0;i<n;i++){
            BIT.push_back(0);
        }
    }
    
    long long sum(int a){
        long long r=0;
        for(int x=a-1;x>=0;x=(x&(x+1))-1){
            r+=BIT[x];
        }
        return r;
    }
    
    long long inversion(std::vector<long long> V){
        long long r=0;
        init(V.size());
        for(int i=0;i<V.size();i++){
            add(V[i],1);
            r+=i-sum(V[i]);
        }
        return r;
    }
};
