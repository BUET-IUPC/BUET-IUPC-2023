#include<bits/stdc++.h>
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt")
using namespace std;
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count())
#define endl '\n'
#ifdef LOCAL
#include "debug.h"
#else
#define dbg1(args...) 
#define dbg2(x) 
#define stop 
#endif
typedef long long LL;
typedef unsigned long long uLL;
//typedef __int128_t LLL;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int,int> pii;
typedef pair<LL, int> pli;
typedef pair<LL, LL> pll;
const int INF=1e9;
const LL MOD=998244353;
void solve(int csno)
{
    int n;
    cin >> n;
    string pc;
    cin >> pc;

    int val[n];
    for(int i = 0; i < n; i++)
        cin >> val[i];
    
    int cc = 0;
    for(char &c: pc)
        cc += c == 'C';
    dbg1(cc);
    int ri = -1;
    for(int i = 0; i < n and cc; i++)
    {
        cc -= pc[i] == 'P';
        ri = i;
        if(cc == 0)
            break;
    }
    dbg1(ri);
    multiset<int> rem;
    for(int j = n - 1; j > ri; j--)
    {
        if(pc[j] == 'C')
            rem.insert(val[j]);
    }

    LL res = 0;
    while(ri >= 0)
    {
        if(pc[ri] == 'P')
        {
            int cval = *rem.begin();
            rem.erase(rem.begin());
            res += 1LL * cval * val[ri];
        }
        else
            rem.insert(val[ri]);
        ri--;
    }

    cout << res << endl;
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T = 1;
    cin>>T;
    for(int csno = 1; csno <= T; csno++)
        solve(csno);
}
