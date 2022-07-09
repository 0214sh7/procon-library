std::vector<std::pair<char,int>> runlength_encode(std::string S){
    std::vector<std::pair<char,int>> R;
    for(int i=0;i<(int)S.size();i++){
        if(i==0 || S[i]!=S[i-1]){
            R.push_back({S[i],1});
        }else{
            R.back().second++;
        }
    }
    return R;
}
