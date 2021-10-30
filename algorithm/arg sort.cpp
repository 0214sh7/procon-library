std::vector<std::pair<long long,long long>> arg_sort(std::vector<std::pair<long long,long long>> A,std::pair<long long,long long> d = {1,0}){
    
    long long N = A.size();
    A.push_back(d);
    std::sort(A.begin(),A.end(),[&](std::pair<long long,long long> x, std::pair<long long,long long> y){
        assert(x.first != 0 || x.second != 0);
        assert(y.first != 0 || y.second != 0);
        
        long long a,b;
        if(x.first>0 && x.second==0){
            a=0;
        }else if(x.first>0 && x.second>0){
            a=1;
        }else if(x.first==0 && x.second>0){
            a=2;
        }else if(x.first<0 && x.second>0){
            a=3;
        }else if(x.first<0 && x.second==0){
            a=4;
        }else if(x.first<0 && x.second<0){
            a=5;
        }else if(x.first==0 && x.second<0){
            a=6;
        }else{
            a=7;
        }
        
        if(y.first>0 && y.second==0){
            b=0;
        }else if(y.first>0 && y.second>0){
            b=1;
        }else if(y.first==0 && y.second>0){
            b=2;
        }else if(y.first<0 && y.second>0){
            b=3;
        }else if(y.first<0 && y.second==0){
            b=4;
        }else if(y.first<0 && y.second<0){
            b=5;
        }else if(y.first==0 && y.second<0){
            b=6;
        }else{
            b=7;
        }
        
        if(a!=b){
            return (a<b);
        }
        
        if(a%2==0){
            return (std::abs(x.first+x.second) < std::abs(y.first+y.second));
        }
        
        if(y.first*x.second != x.first*y.second){
           return (y.first*x.second < x.first*y.second);
        }
        
        return x.first < y.first;
    });
    
    std::vector<std::pair<long long,long long>> B(N);
    for(int i=0;i<N+1;i++){
        if(A[i]==d){
            for(int j=i+1;j<N+1;j++){
                B[j-i-1]=A[j];
            }
            for(int j=0;j<i;j++){
                B[N-i+j]=A[j];
            }
            break;
        }
    }
    
    return B;
}
