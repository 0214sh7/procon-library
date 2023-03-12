std::vector<long long> Mo(int N,int Q,std::vector<std::pair<int,int>> X, std::function<void(int,long long&)> lm, std::function<void(int,long long&)> lp, std::function<void(int,long long&)> rm, std::function<void(int,long long&)> rp){
    
    int rQ;
    std::map<std::pair<int,int>,std::vector<int>> index;
    std::vector<int> block(N,0);
    std::vector<long long> Ans(Q);

    std::function<bool(std::pair<int,int>, std::pair<int,int>)> comp = [&](std::pair<int,int> A,std::pair<int,int> B){
        if(block[A.first]!=block[B.first]){
            return (block[A.first]<block[B.first]);
        }
        if(A.second != B.second){
            return (A.second < B.second);
        }
        return (A.first < B.first);
    };

    for(int i=0;i<Q;i++){
        index[X[i]].push_back(i+1);
    }
    int q = index.size();

    rQ = 1;
    while((rQ+1)*(rQ+1)<=q)rQ++;

    int now = 0;
    for(int i=0;i<rQ-1;i++){
        now += ((N+rQ-1-i)/rQ);
        block[now]++;
    }
    for(int i=0;i<N-1;i++){
        block[i+1] += block[i];
    }

    std::vector<std::pair<int,int>> Y(q);
    now = 0;
    for(auto e:index){
        Y[now] = e.first;
        now++;
    }

    std::sort(Y.begin(),Y.end(),[&](auto a, auto b){return comp(a, b);});

    int L = 0,R = 0;
    long long Result = 0;

    for(int i=0;i<q;i++){
        
        while(Y[i].first < L){
            lm(L,Result);
            L--;
        }
        while(R < Y[i].second){
            rp(R,Result);
            R++;
        }
        while(L < Y[i].first){
            lp(L,Result);
            L++;
        }
        while(Y[i].second < R){
            rm(R,Result);
            R--;
        }

        for(int k:index[Y[i]]){
            Ans[k-1] = Result;
        }

    }

    return Ans;

    //lm(i): [i,r)を[i-1,r)にする
    //lp(i): [i,r)を[i+1,r)にする
    //rm(i): [i,r)を[i,r-1)にする
    //rp(i): [i,r)を[i,r+1)にする

}
