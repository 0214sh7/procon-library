#include <bits/stdc++.h>

//今回の最小単位は2
//long longだが、0か1(え？)
//TODO:これでは効率が悪いので一つのlong longが持つ値の範囲を広げる

// シフト演算を用いて2^n+1を法としてAのmodをとる
// TODO: 実装がきたねぇ！繰り上がりの末に先頭にきた数字から2^n+1がいくつ余計かがわかるかもしれない
// TODO: 0と2^nが区別つかない 暫定処理として2^nのときは最大の桁を2に
std::vector<long long> shiftmod(std::vector<long long> A,long long n){
    
    std::vector<long long> R(n,0),T(n+1,0);

    for(int i=0;i<A.size();i++){
        if((i/n)%2==0){
            R[i%n] += A[i];
        }else{
            R[i%n] -= A[i];
        }
    }

    while(1){
        
        //check
        bool zero = true;
        for(int i=1;i<n;i++){
            if(R[i]!=0)zero = false;
        }
        if(R[0]==-1 && zero){
            R[0] = 0;
            R[n-1] = 2;
            return R;
        }

        bool zeroone = true;
        for(int i=0;i<n;i++){
            if(R[i]!=0 && R[i]!=1)zeroone = false;
        }

        if(zeroone)return R;

        // mod
        T = R;
        T.resize(n+1);
        R = std::vector<long long>(n,0);

        for(int i=0;i<n;i++){
            long long c = T[i]%2;
            c+=2;c%=2;
            T[i+1]+=(T[i]-c)/2;
            T[i]=c;
        }
        while(T.back()!=0 && T.back()!=1 && T.back()!=-1){
            long long r = T.back();
            long long c = r%2;
            c+=2;c%=2;
            T[-1+T.size()]=c;
            T.push_back((r-c)/2);
        }

        for(int i=0;i<T.size();i++){
            if((i/n)%2==0){
                R[i%n] += T[i];
            }else{
                R[i%n] -= T[i];
            }
        }

    }

    return R;
}

// 2^n+1を法としてDFT(FFT)を行う
std::vector<std::vector<long long>> DFT(std::vector<std::vector<long long>> A,long long n){

    int N=A.size();
    if(N==1)return A;
    std::vector<std::vector<long long>> A0(N/2),A1(N/2),iA0,iA1,iA(N,std::vector<long long>(3*n,0)),R(N);
    for(int i=0;i<N;i++){
        if(i%2==0){
            A0[i/2]=A[i];
        }else{
            A1[i/2]=A[i];
        }
    }
    iA0=DFT(A0,n);
    iA1=DFT(A1,n);
    
    long long omega_point=2*n/N;
    long long ith_zeta_point = 0;
    for(int i=0;i<N;i++){
        for(int j=0;j<iA0[i%(N/2)].size();j++){
            iA[i][j]+=iA0[i%(N/2)][j];
        }
        for(int j=0;j<iA1[i%(N/2)].size();j++){
            iA[i][j+ith_zeta_point]+=iA1[i%(N/2)][j];
        }
        
        R[i] = shiftmod(iA[i],n);
        ith_zeta_point += omega_point;
    }
    
    return R;
}

// 2^n+1を法としてiDFTを行う
std::vector<std::vector<long long>> iDFT(std::vector<std::vector<long long>> A,long long n){
    
    long long N = A.size();
    for(int i=1;i<N-i;i++){
        std::swap(A[i],A[N-i]);
    }
    
    std::vector<std::vector<long long>> B = DFT(A,n);
    std::vector<std::vector<long long>> rB(N,std::vector<long long>(3*n,0)),R(N);
    
    long long lgN=0;
    while((1<<lgN)<N)lgN++;
    
    for(int i=0;i<N;i++){
        for(int j=0;j<B[i].size();j++){
            rB[i][j+2*n-lgN]+=B[i][j];
        }
        
        R[i] = shiftmod(rB[i],n);
        
    }

    return R;
}

//確認用の愚直解
std::vector<long long> product_tactless(std::vector<long long> A,std::vector<long long> B,long long N){
    
    long long deg = std::max((long long)(A.size()),(long long)(B.size()));
    std::vector<long long> R(2*deg,0);
    for(int i=0;i<A.size();i++){
        for(int j=0;j<B.size();j++){
            R[i+j]+=A[i]*B[j];
        }
    }
    for(int i=0;i<2*deg-1;i++){
        R[i+1]+=R[i]/2;
        R[i]%=2;
    }
    R = shiftmod(R,N);
    return R;
}

//AとBの積を2^N+1で割ったあまりを返す
std::vector<long long> Schonhage_Strassen(std::vector<long long> A,std::vector<long long> B,long long N){

    long long deg = std::max((long long)(A.size()),(long long)(B.size()));
    
    //再帰なので、小さい値が飛んできたときは愚直で返す
    if(A.size()==0 || B.size()==0){
        return {};
    }
    if(deg<=16){
        std::vector<long long> R(2*deg,0);
        for(int i=0;i<A.size();i++){
            for(int j=0;j<B.size();j++){
                R[i+j]+=A[i]*B[j];
            }
        }
        for(int i=0;i<2*deg-1;i++){
            R[i+1]+=R[i]/2;
            R[i]%=2;
        }
        R = shiftmod(R,N);
        return R;
    }

    //次数は2のべきがいい
    long long Deg = 1;
    while(Deg<deg)Deg*=2;
    deg = Deg;
    A.resize(deg);
    B.resize(deg);

    //YとXを定める　ここでY,Xはdeg桁をY桁の数X個に分割するというもの
    //だいたい√N
    //が、計算のために桁を拡張しまくるので最終的に4Y桁が2X個になるのでそれを前提に計算する
    long long Y = 1;
    while(2*Y*Y<deg)Y*=2;
    long long X = deg/Y;


    //再帰したときのNに相当するnを用意する
    //4Y以上でXの倍数であるものを採用　最初に捌けた小さい数の閾値が小さいと無限ループしそ～
    long long n = 4*Y;
    n = (n+X-1)/X;n*=X;

    //AとBを分割する
    //n桁の数が2X個になるようにする　上X個はDFTのため0
    X *= 2;
    std::vector<std::vector<long long>> As(2*X,std::vector<long long>(n,0)),Bs(2*X,std::vector<long long>(n,0));
    for(int i=0;i<deg;i++){
        As[i/Y][i%Y] = A[i];
        Bs[i/Y][i%Y] = B[i];
    }


    //分割したA,Bたちに重みベクトルWを乗する
    //今回w=2^(n/X)なので、i個目をi*(n/X)個シフトする
    for(int i=0;i<X;i++){
        std::vector<long long> S(Y+n,0);

        for(int j=0;j<Y;j++){
            S[i*(n/X)+j] = As[i][j];
        }
        As[i] = shiftmod(S,n);

    }
    for(int i=0;i<X;i++){
        std::vector<long long> S(Y+n,0);

        for(int j=0;j<Y;j++){
            S[i*(n/X)+j] = Bs[i][j];
        }
        Bs[i] = shiftmod(S,n);

    }
    

    //AsとBsをmod 2^n+1でDFTする　いまDFTはFFT
    std::vector<std::vector<long long>> dA = DFT(As,n),dB = DFT(Bs,n);


    //DFTした各桁の積をとる 積を計算するために再帰的にSSAを用いる
    std::vector<std::vector<long long>> dC = dA;
    for(int i=0;i<dC.size();i++){
        dC[i] = Schonhage_Strassen(dA[i],dB[i],n);
    }

    //dCをiDFTすればAsとBsの積ができる
    std::vector<std::vector<long long>> Cs = iDFT(dC,n);
    

    //Cに重みベクトルW^-1を乗する
    //A,Bにはi*(n/X)個のシフトをした
    //w=2^(n/X)で2^(2n)=1なのでi個目を(2n-i*(n/X))個シフトし、はみ出ていたらそのぶんマイナスし、桁を整える
    for(int i=0;i<X;i++){
        std::vector<long long> S(2*n+Cs[i].size(),0);

        for(int j=0;j<Cs[i].size();j++){
            S[2*n-i*(n/X)+j] = Cs[i][j];
        }
        Cs[i] = shiftmod(S,n);
    }


    //バラバラになったものを一つにまとめる
    std::vector<long long> C(X*Y+Y,0);
    for(int i=0;i<X;i++){
        for(int j=0;j<Cs[i].size();j++){
            C[i*Y+j]+=Cs[i][j];
        }
    }
    
    // 最後に繰り上がり処理をする
    C = shiftmod(C,N);

    return C;
}


int main(void){

    std::vector<long long> A = {0,1,0,1,0,0,0,1,0,0,1,1,1,1,0,0,0,0,0,0,0,1,0,1,1,1,0,1,1,1,0,1,0,0,1,1,0,1,1,0,0,0,0,0,1,1,1,0,1,1,0,0,1,1,0,0,0,1,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,1,0,1,1,0,1,1,1,0,1,1,0,1,0,0,1,0,1,1,1,1,1,0,1,1,1,1,1,0,0,0,1,0,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,0,1,0,0,0,0,0,1,1,0,1,0,1,0,0,1,1,0,0,1,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,1,0,0,0,0,1,1,0,1,0,1,1,1,0,0,1,0,0,0,0,1,1,1,1,1,1,1,0,0,1,0,1,1,0,0,1,0,0,0,0,0,1,1,0,1,0,1,1,1,0,1,1,0,1,0,1,1,1,1,1,0,0,1,1,1,1,0,1,0,1,1,1,1,0,0,1,0,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,1,1,0,0,1,0,0,1,1,1,0,1,0,0,1,0,1,1,1,1,1,0,1,0,0,0,1,1,0,0,0,1,0,0,0,0,1,0,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0,0,1,1,1,1,0,0,0,1,0,1,1,0,0,1,1,0,1,0,1,1,1,1,0,0,0,0,0,1,0,1,1,0,0,1,1,1,0,1,0,0,0,1,1,0,0,1,0,0,1,1,0,1,1,0,0,1,1,1,1,0,0,1,0,1,0,1,1,1,1,0,0,1,0,0,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,0,1,1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,0,0,1,0,1,0,1,0,1,1,0,1,0,0,1,1,1,1,0,0,1,0,0,1,1,1,1,1,1,1,0};
    std::vector<long long> B = {1,1,1,0,1,0,0,1,1,0,0,1,0,0,1,0,1,1,0,1,0,0,1,1,0,1,0,0,0,1,0,0,1,1,0,0,1,1,1,0,1,0,1,1,1,1,1,1,0,0,0,1,1,0,1,0,0,1,0,1,0,0,0,1,1,0,1,1,0,0,0,1,1,1,1,0,1,0,0,0,1,0,0,1,0,1,1,0,1,1,1,1,1,0,0,0,1,0,1,1,0,0,1,1,1,0,0,1,0,0,0,1,0,1,1,1,1,0,0,1,1,0,0,0,1,0,0,1,0,0,1,0,1,1,1,1,0,1,1,1,0,0,0,1,0,0,1,1,0,1,1,1,1,1,0,0,0,1,0,0,1,1,0,0,1,0,0,0,0,1,0,1,1,1,0,0,0,1,0,1,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,1,0,1,0,0,1,1,1,1,0,1,1,1,0,0,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,0,1,1,1,0,1,1,0,0,1,0,1,1,1,0,1,1,0,0,1,0,0,0,1,0,1,1,1,0,1,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,0,0,1,0,0,1,0,0,0,1,0,1,1,1,1,0,1,1,0,1,0,0,0,1,0,1,1,0,0,0,0,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,1,1,1,0,1,0,0,0,1,0,0,0,1,0,0,1,1,0,0,1,1,1,0,0,0,1,0,1,0,0,0,1,1,1,0,1,0,1,1,0,1,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,1,1,1,1,0,1,0,0,0,0,1,0,0,1,1,1,1,1,1,0,1,1,1,1,0,0,1,0,1,1,1,1,1,0,0,1,0,1,0,1,0,0,1,1,0,0,0,1,0,1,0,0,1,1,1,0,0,1,1,1,0,1,1,0,1,0,1,0,1,1,0,1,0,1,0,0,1,1,0,0,0,1,0,1,1,1,1,1,1,1,0,0,1,0,1,0,0,1,1,0,1,0,0,1,0,0,1,0,1,1,0,1,1,0,1,1,0};
    long long N = 1024;
    
    std::vector<long long> E = Schonhage_Strassen(A,B,N);

    std::cout << "result" << std::endl;
    for(int i=-1+E.size();i>=0;i--){
        std::cout << E[i];
        if(i%4==0 && i!=0)std::cout << "'";
    }
    std::cout << std::endl;
    std::cout << "   ";
    for(int i=-1+E.size();i>=0;i--){
        if(i%4==0){
            long long k = 0;
            for(int j=0;j<4 && i+j<E.size();j++){
                k += E[i+j]*(1LL<<j);
            }

            if(k<=9){
                std::cout << k;
            }else{
                std::cout << (char)('A'+k-10);
            }
            std::cout << "    ";
        }
    }
    std::cout << std::endl;
    
    std::vector<long long> F = product_tactless(A,B,N);
    std::cout << "   ";
    for(int i=-1+F.size();i>=0;i--){
        if(i%4==0){
            long long k = 0;
            for(int j=0;j<4 && i+j<F.size();j++){
                k += F[i+j]*(1LL<<j);
            }

            if(k<=9){
                std::cout << k;
            }else{
                std::cout << (char)('A'+k-10);
            }
            std::cout << "    ";
        }
    }
    std::cout << std::endl;
    
    return 0;
}

