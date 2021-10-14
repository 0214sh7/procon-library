class double_sweep{
    
    private:
    const long long INF = (1LL<<61);
    int V,V1,V2;
    std::vector<std::vector<std::pair<int,long long>>> G;
    std::vector<int> parent;
    std::vector<long long> parent_cost;
    long long diam;
    long long temp;
    
    void dfs(int phase,int v,int p,long long d){
        if(phase==1){
            if(d>temp){
                V1 = v;
                temp = d;
            }
        }
        if(phase==2){
            parent[v] = p;
            if(d>temp){
                V2 = v;
                temp = d;
            }
        }
        for(std::pair<int,long long> E:G[v]){
            int e = E.first;
            long long f = E.second;
            if(e!=p){
                dfs(phase,e,v,d+f);
                if(phase==2){
                    parent_cost[e] = f;
                }
            }
        }
    }
    
    public:
    
    void init(int N,std::vector<std::pair<std::pair<int,int>,long long>> edge){
        V = N;
        V1 = 0,V2 = 0;
        
        G.clear();
        G.resize(V);
        for(int i=0;i<edge.size();i++){
            int from=edge[i].first.first,to=edge[i].first.second;
            long long cost=edge[i].second;
            G[from].push_back({to,cost});
            G[to].push_back({from,cost});
        }
        
        parent.resize(V);
        for(int i=0;i<V;i++){
            parent[i] = -1;
        }
        parent_cost.resize(V);
        for(int i=0;i<V;i++){
            parent_cost[i] = -1;
        }
        
        temp = -INF;
        dfs(1,0,-1,0);
        temp = -INF;
        dfs(2,V1,-1,0);
        diam = -1;
    }
    
    double_sweep(int N,std::vector<std::pair<std::pair<int,int>,long long>> edge){
        init(N,edge);
    }
    
    std::pair<int,int> vertex(void){
        return std::make_pair(V2,V1);
    }
    
    std::vector<int> pass(void){
        std::vector<int> R;
        diam = 0;
        int r = V2;
        while(r!=V1){
            R.push_back(r);
            diam += parent_cost[r];
            r = parent[r];
        }
        R.push_back(r);
        return R;
    }
    
    long long diameter(void){
        if(diam==-1){
            pass();
        }
        return diam;
    }
};
