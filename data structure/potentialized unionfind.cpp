class potentialized_unionfind{
    private:
    std::vector<int> UF,rank,pot;
    public:
    
    void init(int N){
        UF.clear();
        rank.clear();
        for(int i=0;i<N;i++){
            UF.push_back(i);
            rank.push_back(0);
            pot.push_back(0);
        }
    }
    
    int root(int k){
        if(UF[k]==k){
            return k;
        }else{
            int r = root(UF[k]);
            pot[k] += pot[UF[k]];
            UF[k] = r;
            return UF[k];
        }
    }
    
    int potential(int k){
        root(k);
        return pot[k];
    }
    
    bool same(int p,int q){
        return root(p)==root(q);
    }
    
    bool unite(int P,int Q,int d){
        //pot(Q)-pot(P)=dを満たす
        d+=potential(P);
        d-=potential(Q);
        int p=root(P), q=root(Q);
        if(p==q)return false;
        if(rank[p]<rank[q]){
            std::swap(p,q);
            d = -d;
        }
        UF[q]=p;
        if(rank[p]==rank[q])rank[p]++;
        pot[q]=d;
        
        return true;
    }
    
    int diff(int P,int Q){
        return potential(Q)-potential(P);
    }
    
};
