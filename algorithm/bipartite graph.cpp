std::vector<int> bipartite(std::vector<std::pair<int,int>> edge){
    int E = edge.size();
    if(E==0)return {};
    int V = 0;
    for(int i=0;i<E;i++){
        V=std::max(V,edge[i].first+1);
        V=std::max(V,edge[i].second+1);
    }
    std::vector<int> R(V,-1);
    std::vector<int> S(0);
    std::vector<std::vector<int>> es(V,std::vector<int>(0));
    for(int i=0;i<E;i++){
        es[edge[i].first].push_back(edge[i].second);
        es[edge[i].second].push_back(edge[i].first);
    }
    std::queue<int> Q;
    std::vector<bool> visited(V,false);
    for(int j=0;j<V;j++){
        if(visited[j])continue;
        Q.push(j);
        R[j]=0;
        visited[j]=true;
        while(!Q.empty()){
            int q=Q.front();
            Q.pop();
            visited[q]=true;
            for(int i=0;i<es[q].size();i++){
                if(R[es[q][i]]==R[q]){
                    return S;
                }
                if(visited[es[q][i]])continue;
                Q.push(es[q][i]);
                R[es[q][i]]=1-R[q];
            }
        }
    }
    return R;
}
