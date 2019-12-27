class unionfind{
    private:
    std::vector<int> UF,rank;
    public:
    
    void init(int N){
        UF.clear();
        rank.clear();
        for(int i=0;i<N;i++){
            UF.push_back(i);
            rank.push_back(0);
        }
    }
    
    int root(int k){
        if(UF[k]==k){
            return k;
        }else{
            UF[k]=root(UF[k]);
            return UF[k];
        }
    }
    
    bool same(int p,int q){
        return root(p)==root(q);
    }
    
    void unite(int P,int Q){
        int p=root(P);
        int q=root(Q);
        if(p==q)return;
        if(rank[p]<rank[q])std::swap(p,q);
        UF[q]=p;
        if(rank[p]==rank[q])rank[p]++;
    }
    
};
