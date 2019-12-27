class Dijkstra{
    private:
    typedef std::pair<long long,int> P;
    std::vector<std::vector<P>> G;
    int V;
    long long INF = (1LL<<61);
    std::priority_queue<P,std::vector<P>,std::greater<P>> que;
    
    public:
    void init(std::vector<std::pair<std::pair<int,int>,long long>> edge){
        //頂点数を決定する
        V=0;
        for(int i=0;i<edge.size();i++){
            V=std::max(V,edge[i].first.first+1);
            V=std::max(V,edge[i].first.second+1);
        }
        
        //辺集合を扱いやすい形式に変換する
        G.resize(V);
        for(int i=0;i<edge.size();i++){
            int from=edge[i].first.first,to=edge[i].first.second;
            long long cost=edge[i].second;
            G[from].push_back({cost,to});
        }
    }
    
    std::vector<long long> solve(int s){
        std::vector<long long> d;
        //INFで初期化する
        for(int i=0;i<V;i++){
            d.push_back(INF);
        }
        d[s]=0;
        que.push({0,s});
        //queは{cost,to}をコストが小さい順に出す
        while(!que.empty()){
            P p = que.top();
            que.pop();
            int v=p.second;
            if(d[v]<p.first)continue;
            for(int i=0;i<G[v].size();i++){
                P e = G[v][i];
                if(d[e.second]>d[v]+e.first){
                    d[e.second] = d[v]+e.first;
                    que.push({d[e.second],e.second});
                }
            }
        }
        return d;
    }
    
    //init:{{int,int},longlong}のvectorを渡すことで有向グラフを構築する
    //solve:始点を渡すとinitで構築したグラフでダイクストラをし、コストのvectorを返す
};
