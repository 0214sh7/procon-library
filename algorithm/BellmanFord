class BellmanFord{
    private:
    typedef std::pair<std::pair<int,int>,long long> P;
    int V,E;
    long long INF = (1LL<<61);
    std::vector<std::pair<std::pair<int,int>,long long>> es;
    
    public:
    void init(std::vector<std::pair<std::pair<int,int>,long long>> edge){
        //辺数をもとめる　
        E=edge.size();
        //頂点数を決定する
        V=0;
        for(int i=0;i<edge.size();i++){
            V=std::max(V,edge[i].first.first+1);
            V=std::max(V,edge[i].first.second+1);
        }
        es=edge;
    }
    
    std::vector<std::pair<long long,bool>> solve(int s){
        std::vector<std::pair<long long,bool>> d;
        //INFで初期化する
        for(int i=0;i<V;i++){
            d.push_back({INF,false});
        }
        d[s].first=0;
        for(int j=0;j<2*V;j++){
             bool update=false;
            for(int i=0;i<E;i++){
                P k=es[i];
                if(d[k.first.first].first!=INF && d[k.first.second].first>d[k.first.first].first+k.second){
                    d[k.first.second].first=d[k.first.first].first+k.second;
                    if(j>=V){
                        d[k.first.second].second=true;
                    }
                    update=true;
                }
            }
            if(!update)break;
        }
        return d;
    }
    
    //init:{{int,int},longlong}のvectorを渡すことで有向グラフを構築する
    //solve:始点を渡すとinitで構築したグラフでベルマンフォードをし、コストのvectorを返す
};
