class lowest_common_ancestor{
    private:
    int V,LOG;
    std::vector<std::vector<long long>> G,table;
    std::vector<long long> depth;
    
    void dfs(long long v,long long p,long long d){
        depth[v] = d;
        table[v][0] = p;
        for(long long e:G[v]){
            if(e!=p){
                dfs(e,v,d+1);
            }
        }
    }
    
    public:
    void init(long long root,std::vector<std::pair<long long,long long>> edge){
        V = 1+edge.size();
        LOG = 1;
        while((1<<LOG)<V)LOG++;

        G.clear();
        G.resize(V);
        for(int i=0;i<edge.size();i++){
            G[edge[i].first].push_back(edge[i].second);
            G[edge[i].second].push_back(edge[i].first);
        }
        
        table.resize(V);
        for(int i=0;i<V;i++){
            table[i].resize(LOG);
        }
        depth.resize(V);
        dfs(root,-1,0);
        
        for(int j=0;j<LOG-1;j++){
            for(int i=0;i<V;i++){
                if(table[i][j]==-1){
                    table[i][j+1] = -1;
                }else{
                    table[i][j+1] = table[table[i][j]][j];
                }
                
            }
        }
        
    }
    
    lowest_common_ancestor(long long root,std::vector<std::pair<long long,long long>> edge){
        init(root,edge);
    }
    
    
    long long climb(long long u,long long k = 1){
        for(int i=0;k>0;k>>=1,i++){
            if(u==-1)return -1;
            if(k&1)u = table[u][i];
        }
        return u;
    }
    
    long long lca(long long u,long long v){
        if(depth[u]>depth[v])std::swap(u,v);
        v = climb(v,depth[v]-depth[u]);
        if(u==v)return u;
        
        for(int i=LOG-1;i>=0;i--){
            if(table[u][i]!=table[v][i]){
                u = table[u][i];
                v = table[v][i];
            }
        }
        return table[u][0];
    }
    
};
