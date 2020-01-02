std::vector<int> compress(std::vector<int> D){
    std::map<int,int> G;
    std::vector<int> E,r;
    int s=D.size();
    for(int i=0;i<s;i++){
        E.push_back(D[i]);
    }
    sort(E.begin(),E.end());
    int t=0;
    for(int i=0;i<s;i++){
        if(i!=0 && E[i]!=E[i-1]){
            t++;
        }
        G[E[i]]=t;
    }
    for(int i=0;i<s;i++){
        r.push_back(G[D[i]]);
    }
    return r;
}
