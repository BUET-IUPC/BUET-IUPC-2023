#include<bits/stdc++.h>
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt")
using namespace std;
#define rng_23 mt19937 rng(chrono::steady_clock::now().time_since_epoch().count())
#ifdef LOCAL
#include "debug.h"
#else
#define dbg1(args...) 
#define dbg2(x) 
#define stop 
#endif
#define endl '\n'
typedef long long LL;
typedef unsigned long long uLL;
//typedef __int128_t LLL;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int,int> pii;
typedef pair<LL, int> pli;
typedef pair<LL, LL> pll;
typedef tuple<int, int, int> tiii;
const int INF=1e9;
const LL MOD=998244353;

LL ara[1 << 20], cnt[1 << 20], sos[1 << 20], ans[1 << 20];
bool  adj[20][20], ase[20];
void zeta(LL d[],int m, bool complement = 0)
{
    for(int i=0;i<m;++i)
    {
        for(int j=(1 << m) - 1;j>=0;--j)
        {
            if(((j >> i) & 1) ^ complement)
            {
                d[j]+=d[j^(1<<i)];
                d[j] %= MOD;

            }
        }
    }
}

void zinv(LL d[],int m)
{
    for(int i=0;i<(1<<m);++i)
    {
        d[i]=(((__builtin_popcount(i)%2?-1:1)*d[i]) + MOD) % MOD;
    }
    zeta(d,m, true);
    for(int i=0;i<(1<<m);++i)
    {
        d[i]=(((__builtin_popcount(i)%2?-1:1)*d[i]) + MOD) % MOD;
    }
}

bool blocked[20], vis[20];
bool dfs(int u, int k)
{
    dbg1(u);
    vis[u] = true;
    bool _ase = ase[u];
    for(int i = 0; i < k; i++)
    {
        if(!blocked[i] and adj[u][i] and !vis[i])
        {
            _ase |= dfs(i, k);
        }
    }
    dbg1(u, _ase);
    return _ase;
}
LL bigmod(LL a,LL b){//mod should be <32 bit
    LL ans=1;
    while(b>0){
        if(b&1)ans=(ans*a)%MOD;
        b=b>>1;
        a=(a*a)%MOD;
    }
    return ans;
}
void solve(int csno)
{
    int n, k;
    cin >> n >> k;
    int orsum = 0;
    for(int i = 0; i < n; i++)
    {
        cin >> ara[i];
        orsum |= ara[i];
        vector<int> off;
        for(int j = 0; j < k; j++)
        {
            if(!((ara[i] >> j) & 1))
            {
                off.push_back(j);
                ase[j] = true;
            }

        }
        
        for(int j = 0; j < off.size(); j++)
            for(int k = j + 1; k < off.size(); k++)
            {
                dbg1(off[j], off[k]);
                adj[off[j]][off[k]] = true;
                adj[off[k]][off[j]] = true;
            }

        cnt[ara[i]]++;
    }

    zeta(cnt, k, true);

    // for(int i = 0; i < (1 << 3); i++)
        // cout << i << " " << cnt[i] << endl;
    
    for(int i = 0; i < (1 << k); i++)
    {
        memset(blocked, 0, sizeof blocked);
        for(int j = 0; j < k; j++)
        {
            if(!((i >> j) & 1))
            {
                blocked[j] = true;
            }
        }

        LL cc = cnt[i];
        dbg1(cc);
        memset(vis, 0, sizeof vis);
        for(int j = 0; j < k; j++)
        {
            if(((i >> j) & 1) and !vis[j])
            {
                dbg1(j);
                cc += dfs(j, k);
                cc %= MOD;
            }
        }
        dbg1(cc);
        ans[i] = bigmod(2, cc);
        dbg1(i, ans[i]);
    }

    for(int i = 0; i < (1 << k); i++)
    {
        ans[i] -= 2;
        ans[i] += MOD;
        ans[i] %= MOD;
        ans[i] *= bigmod(2, MOD - 2);
        ans[i] %= MOD;
        dbg1(ans[i]);
    }

    zinv(ans, k);

    for(int i = 0; i < (1 << k); i++)
        cout << ans[i] << "\n";
    


}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T = 1;
    //cin>>T;
    for(int csno = 1; csno <= T; csno++)
        solve(csno);
}
