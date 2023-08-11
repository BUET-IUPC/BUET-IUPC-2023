#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
const ll MOD = 998244353;

int *pfactor;
void build(int n){//prime factor of every number below n
    pfactor=new int[n+1];
    memset(pfactor,0,sizeof(int)*(n+1));
    int i,j;
    for(i=2;i<=n;i++){
        if(pfactor[i]==0){
            for(j=i;j<=n;j+=i){
                pfactor[j]=i;
            }
        }
    }
    return;
}
int get_p_factor(vector<int>& pf,vector<int>& pfp,int n){
    int i=0;
    int j,pw;
    while(n>1){
        j=pfactor[n];
        pw=0;
        while(!(n%j)){
            n/=j;
            pw++;
        }
        pf[i]=j;
        pfp[i]=pw;
        i++;
    }
    return i;
}

void solve(int cs)
{
    int k;
    cin >> k;

    vector<int> p(k);
    vector<int> f(k);

    for(auto & e : p)
        cin >> e;

    for(auto &e : f)
        cin >> e;

    vector<ll> pw(1000000,0);
    for(int i = 0; i < k; ++i)pw[p[i]] = f[i];

    vector<ll> res(1000000);
    res[2] = 1;
    vector<int> pf(40),pfp(40);
    for(int i = 3; i < 1000000; ++i)if(pfactor[i] == i){
        int j = get_p_factor(pf, pfp, i -1);
        ll tmp = 0;
        for(int k = 0; k < j; ++k){
            tmp += pfp[k] * res[pf[k]] % MOD;
        }
        res[i] = tmp % MOD;
    }
    ll ans = 0;
    for(int i = 2; i < 1000000; ++i)if(pfactor[i] == i ){
        ans += pw[i] * res[i] % MOD;
    }
    ans += (pw[2] == 0);
    cout << ans % MOD << '\n';
}
int main()
{
    build(1000000);
    fastio;
    int T=1;
    for(int t=0;t<T;t++)
    {
        solve(t+1);
    }
    return 0;
}

