#include<bits/stdc++.h>
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt")
using namespace std;
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count())
#define endl '\n'
#ifdef LOCAL
#include "../cp-template/Basic/debug.h"
#else
#define dbg1(args...) 
#define dbg2(x) 
#define stop 
#endif
typedef long long LL;
#define int LL
typedef unsigned long long uLL;
//typedef __int128_t LLL;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int,int> pii;
typedef pair<LL, int> pli;
typedef pair<LL, LL> pll;
const int INF=1e9;
const LL MOD=998244353;

vector<int> g[500001];
namespace LCA
{
    const int MAXN = 500001, LOG = 20;
    
    int n;
    int bparent[MAXN][LOG], sub[MAXN], depth[MAXN];
    LL delta[MAXN][LOG], distsum[MAXN];
    // build depth[] and immediate ancestor
    void dfs(int node, int _par)
    {
        sub[node] = 1;
        for (auto v : g[node]){
            if (v == _par) continue;

            bparent[v][0] = node;
            depth[v] = 1 + depth[node];
            dfs(v, node);
            sub[node] += sub[v];
            distsum[node] += sub[v] + distsum[v];
        }
    }
    void buildDistsum(int u, int _par)
    {
        for(int v: g[u])
        {
            if(v == _par) continue;
            distsum[v] += distsum[u] - distsum[v] - sub[v];
            distsum[v] += n - sub[v];
            buildDistsum(v, u);
        }
    }
    // build bparent[]
    void build_ancestor()
    {
        for (int i = 1; (1 << i) < n; i++)
            for (int j = 1; j <= n; j++)
                bparent[j][i] = bparent[bparent[j][i - 1]][i - 1];
    }
    void buildDelta()
    {
        for(int j = 1; j <= n; j++)
        {
            delta[j][0] = sub[bparent[j][0]] - sub[j];
        }
        for (int i = 1; (1 << i) < n; i++)
            for (int j = 1; j <= n; j++)
            {
                int upper_sub = 1LL * sub[bparent[j][i]] - sub[bparent[j][i - 1]];
                delta[j][i] = delta[j][i - 1] + delta[bparent[j][i - 1]][i - 1] 
                            + (upper_sub << (i - 1));
            }
    }
    LL getDelta(int u, int h)
    {
        //int cursub = 0;
        LL _delta = 0, curh = 0;
        for(int i = LOG - 1; i >= 0; i--)
        {
            if(h >= (1 << i))
            {
                _delta += delta[u][i];
                _delta += (sub[bparent[u][i]] - sub[u]) * curh;
                curh += (1 << i);
                u = bparent[u][i];
                h -= (1 << i);
            }
        }
        return _delta;
    }
    int pth_ancestor(int a, int p)
    {
        for (int i = 0; (1 << i) <= p; i++)
            if ((1 << i) & p)
                a = bparent[a][i];
        return a;
    }

    void init(int _n)
    {
        n = _n;
        depth[1] = 0;
        dfs(1, 0);
        build_ancestor();
        buildDelta();
        buildDistsum(1, 0);
    }

    int lca(int u, int v)
    {
        if (depth[v] > depth[u])
            v = pth_ancestor(v, depth[v] - depth[u]);
        if (depth[u] > depth[v])
            u = pth_ancestor(u, depth[u] - depth[v]);
        if (u == v)
            return u;
        for (int i = log2(n - 1); i >= 0; i--)
        {
            if (bparent[u][i] != bparent[v][i])
            {
                u = bparent[u][i];
                v = bparent[v][i];
            }
        }
        return bparent[u][0];
    }
    int dist(int u, int v)
    {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }
}

void solve(int csno)
{
    int n;
    cin >> n;
    for(int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    LCA::init(n);

    // for(int u = 1; u <= n; u++)
    // {
    //     cout << LCA::getDelta(u, 2) << " ";
    // }
    // cout << endl;

    // for(int u = 1; u <= n; u++)
    //     cout << LCA::distsum[u] << " ";
    // cout << endl;


    int q;
    cin >> q;
    while(q--)
    {
        int u, v, r;
        cin >> r >> u >> v;

        int luv = LCA::lca(u, v);
        //if(LCA::lca(r, luv) != luv)
        //{
        int du = LCA::dist(r, u);
        int dv = LCA::dist(r, v);

        if(du > dv)
        {
            swap(u, v);
            swap(du, dv);
        }
        if(du == dv)
        {
            cout << LCA::distsum[r] << endl;
            continue;
        }
        LL delta = 0;
        int lift = (dv - du - 1) / 2;
        LL res = LCA::distsum[r];
        dbg1(res);
        if(LCA::dist(v, luv) > lift)
        {
            dbg1(du, dv);
            delta = LCA::getDelta(v, lift);
            dbg1(delta);
            res += 2 * delta + LCA::sub[LCA::pth_ancestor(v, lift)] 
                * (du - dv + 1);
            cout << res << endl;
            continue;
        }
        int dlv = LCA::dist(luv, v);
        dbg1(du, dv);

        if(dlv)
            res += 2 * LCA::getDelta(v, dlv - 1) 
                + LCA::sub[LCA::pth_ancestor(v, dlv - 1)] * (du - dv + 1);
        
        int duv = LCA::dist(u, v);
        int uu = LCA::pth_ancestor(u, duv - dlv - 1);
        int vv = dlv == 0 ? 0 : LCA::pth_ancestor(v, dlv - 1);
        res += (n - LCA::sub[uu] - LCA::sub[vv]) * (du - dv + 1 + 2 * dlv);
        dbg1(n-LCA::sub[uu]-LCA::sub[vv]);

        
        if(dlv < lift)
        {
             
            int uu = LCA::pth_ancestor(u, duv - lift - 1);
            u = LCA::pth_ancestor(uu, 1);  
            dbg1(u, uu);
            lift -= dlv + 1;
            dbg1(lift);
            int usub = LCA::sub[LCA::pth_ancestor(u, lift)] - LCA::sub[uu];
            dbg1(usub);
            res += -2 * LCA::getDelta(u, lift) 
                + usub * (du - dv + 1 + 2 * dlv + 2)
                + usub * 2 * lift;
        }
        cout << res << endl;
    }
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T = 1;
    //cin>>T;
    for(int csno = 1; csno <= T; csno++)
        solve(csno);
}
