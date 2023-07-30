#include <bits/stdc++.h>
using namespace std;

//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt")

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



const int N = 1e6+3, K = 26;
//====================================================================//
int d[N], p[N];
void testcase(){
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++)cin >> d[i];
	
	for(int i = 1; i <= n; i++)cin >> p[i];
	
	ll ans = 0;
	for(int i = 1; i <= n; i++){
		ans += 1LL * abs(d[i] - d[p[i]]) * i;
	}
	
	vector<vector<int>> cycles;
	vector<int> vis(n + 1);
	vis[0] = 1;
	for(int i = 1; i <= n; i++){
		if(vis[i])continue;
		int x = i;
		cycles.emplace_back();
		while(vis[x] == 0){
			vis[x] = 1;
			cycles.back().push_back(x);
			x = p[x];
		}
	}
	vector<ii> way;
	
	auto workCycle = [&](vector<int> &cyc){
		vector<int> bame;
		for(auto x : cyc){
			if(p[x] < x)bame.push_back(x);
		}
		sort(bame.begin(), bame.end());
		for(auto x : bame){
			vector<int> temp;
			int t = p[x];
			while(t < x){
				temp.push_back(t);
				t = p[t];
			}
			while(!temp.empty()){
				way.push_back({temp.back(), x});
				swap(p[temp.back()], p[x]);
				x = temp.back();
				temp.pop_back();
			}
		}
	};
	for(auto &x : cycles){
		workCycle(x);
	}	
	for(int i = 1; i <= n; i++)assert(p[i] == i);
	cout << ans << ' ' << way.size() << "\n";
	for(auto [x, y] : way)cout << x << ' ' << y << "\n";
	
	
	
	return;
}





int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T = 1;
	cin >> T;
	
	for(int qq = 1; qq <= T; ++qq){
		//cout << "Case #" << qq << ": ";
		testcase();
	}
	return 0;
}

