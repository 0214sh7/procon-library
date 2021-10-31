class Dinic{
    
    private:
    struct edge{
        int end;
        long long cap,rev;
        
    };
    
    const long long INF = (1LL<<61);
    int V;
    std::vector<std::vector<edge>> G;
    std::vector<long long> level;
    std::vector<int> iter;
    
    void Dinic_bfs(int s){
        for(int i=0;i<V;i++){
            level[i]=-1;
        }
        std::queue<int> que;
        level[s]=0;
        que.push(s);
        while(!que.empty()){
            int v=que.front();
            que.pop();
            for(unsigned int i=0;i<G[v].size();i++){
                edge &e = G[v][i];
                if(e.cap>0 && level[e.end]<0){
                    level[e.end]=level[v]+1;
                    que.push(e.end);
                }
            }
        }
    }
    
    long long Dinic_dfs(int v,int t,long long f){
        if(v==t)return f;
        for(int &i=iter[v];i<G[v].size();i++){
            edge &e = G[v][i];
            if(e.cap>0 && level[v]<level[e.end]){
                long long d = Dinic_dfs(e.end,t,std::min(f,e.cap));
                if(d>0){
                    e.cap -= d;
                    G[e.end][e.rev].cap+=d;
                    return d;
                }
            }
        }
        return 0;
    }
    
    public:
    
    void init(int N){
        V = N;
        G.clear();
        G.resize(V);
        level.resize(V);
        iter.resize(V);
    }
    
    Dinic(int N){
        init(N);
    }
    
    void add(int from,int end,long long cap){
        G[from].push_back((edge){end,cap,(long long)G[end].size()});
        G[end].push_back((edge){from,0,(long long)G[from].size()-1});
    }
    
    long long solve(int s,int t){
        long long flow=0;
        while(1){
            Dinic_bfs(s);
            if(level[t]<0){return flow;}
            for(int i=0;i<V;i++){
                iter[i]=0;
            }
            long long f;
            while((f=Dinic_dfs(s,t,INF))>0){
                flow+=f;
            }
        }
    }
    
};
