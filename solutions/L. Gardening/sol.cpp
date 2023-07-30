#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt")

using ll = long long int;
using ull = unsigned long long int;
using vi = vector<ll>;
using ii = pair<ll,ll>;
using vii = vector<ii>;
using ld = long double;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T>
using ordered_set = tree < T, null_type, less<T>,
rb_tree_tag,
tree_order_statistics_node_update >;

#ifdef SA_DEBUG
template <class T>
void print(T a) {cerr << a << endl;}
template <class T, class... V> 
void print(T a, V... b) {cerr << a << ", "; print(b...);}
#define dbg(...) cerr << "[" << __LINE__ << "] " << #__VA_ARGS__ << " :: ", print(__VA_ARGS__)
#else
#define dbg(...) 7
#endif

#define eb emplace_back
#define fi first
#define se second

const ll INFL = 2e18;
const int INF = 1e9;
const double PI = acos(-1);
const ll mod = 1e9+7;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T, class V> 
ostream& operator << (ostream &s, pair<T, V> a){
	s << a.fi << ' ' << a.se; return s;
}

template<class T, class V> 
istream& operator >> (istream &s, pair<T, V> &a){
	s >> a.fi >> a.se; return s;
}

template<class T> 
ostream& operator << (ostream &s, vector<T> a){
	for(int i = 0; i < (int)a.size(); i++){
		if(i > 0)s << ' ' ; 
		s << a[i];
	} return s;
}

template<class T> 
istream& operator >> (istream &s, vector<T> &a){
	for(T &x : a)s >> x; 
	return s;
}

template<class T> 
void input(T a[], int l, int r, istream &s = cin){
	while(l <= r)s >> a[l++];
}

template<class T> 
void output(T a[], int l, int r, bool en = true, ostream &s = cout){
	while(l <= r){ s << a[l++];
		if(l <= r) s << ' ';
	} if(en)s << "\n";
}



const int N = 3e5+3, K = 19;
//====================================================================//

vector<int> adj[N];
int sub[N];
int dis[N];
int up[N][K];
ll subSum[N][K];
ll disSum[N];
int tin[N], tout[N], t;
int n;
ll dfs(int ind, int par){
	tin[ind] = t++;
	up[ind][0] = par;
	for(int i = 1; i < K; i++)up[ind][i] = up[up[ind][i - 1]][i - 1];
	ll ans = 0;
	sub[ind] = 1;
	for(auto x : adj[ind]){
		if(x == par)continue;
		dis[x] = dis[ind] + 1;
		ans += dfs(x, ind);
		ans += sub[x];
		sub[ind] += sub[x];
	}
	tout[ind] = t++;
	return ans;
}

bool isanc(int u, int v){
	return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int LCA(int u, int v){
	if(isanc(u, v))return u;
	for(int i = K - 1; i >= 0; i--){
		if(!isanc(up[u][i], v))u = up[u][i];
	}
	return up[u][0];
}

void dfs2(int ind, int par){
	subSum[ind][0] = sub[ind];
	for(int i = 1; i < K; i++)subSum[ind][i] = subSum[ind][i - 1] + subSum[up[ind][i - 1]][i - 1];
	
	for(auto x : adj[ind]){
		if(x == par)continue;
		disSum[x] = disSum[ind] + (n - 2 * sub[x]);
		dfs2(x, ind);
	}
}

int getDis(int u, int v, int lca){
	return dis[u] + dis[v] - 2 * dis[lca];
}

ll getSum(int u, int h){
	if(h < 0)return 0;
	ll ans = 0;
	for(int i = K - 1; i >= 0; i--){
		if((1 << i) <= h)ans += subSum[u][i], h -= (1 << i), u = up[u][i];
	}
	return ans + subSum[u][0];
}
void testcase(){
	cin >> n;
	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	disSum[1] = dfs(1, 1);
	dfs2(1, 1);
	
	int q;
	cin >> q;
	while(q--){
		int root, u, v;
		cin >> root >> u >> v;
		
		int lca = LCA(u, v);
		int ulca = LCA(root, u);
		int vlca = LCA(root, v);
		int nlca;
		if(isanc(ulca, lca) && isanc(vlca, lca)){
			//both lca are same
			nlca = lca;
		}else{
			if(lca == ulca){
				swap(u, v);
				swap(ulca, vlca);
			}
			nlca = ulca;
		}
		
		int uDis = getDis(u, nlca, nlca);
		int vDis = getDis(v, nlca, lca);
		if(nlca == lca){
			if(uDis < vDis){
				swap(u, v);
				swap(uDis, vDis);
				swap(ulca, vlca);
			}
		}
		//dbg(lca, nlca);
		ll ans = disSum[root];
		if(uDis >= vDis){
			int dif = uDis - vDis;
			if(dif > 1){
				int h = dif / 2 - 1;
				ans -= (dif % 2 + 1) * getSum(u, h);
				if(dif % 2 == 0)ans -= getSum(u, h - 1);
			}
		}else{
			int dv = getDis(v, lca, lca);
			int dif = vDis - uDis;
			if(dif > 1){
				int hv = dif / 2 - 1;
				if(dv > hv){
					ans -= (dif % 2 + 1) * getSum(v, hv);
					if(dif % 2 == 0)ans -= getSum(v, hv - 1);
				}else{
					int du = getDis(u, lca, lca);
					int hu = du + dv - hv;
					ll subU = getSum(u, du - 1) - getSum(u, du - 2);
					if(dv < hv){
						ans += (dif % 2 + 1) * getSum(u, du - 2);
						ans -= (dif % 2 + 1) * getSum(u, hu - 2);
						if(dif % 2 == 0){
							ans += getSum(u, du - 2);
							ans -= getSum(u, hu - 1);
						}
						ans -= (2 * du - 2 * hu - (dif % 2 == 0)) * subU;
					}
					ans -= (2 * du - 2 * hu - (dif % 2 == 0) + 2) * (n - subU);
					ans -= 2 * getSum(v, dv - 1);
				}
			}
			
		}
		cout << ans << "\n";
		
	}
	
	return;
}





int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T = 1;
	//cin >> T;
	
	for(int qq = 1; qq <= T; ++qq){
		//cout << "Case #" << qq << ": ";
		testcase();
	}
	return 0;
}
