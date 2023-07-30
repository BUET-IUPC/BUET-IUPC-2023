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



const int N = 41, K = 7e6 + 5;
//====================================================================//

vector<ll> v[N];
ll ans = 0, p, q;
ll A[K], B[K];
ii temp[K];
int M, cur;
void gen(int ind, ll sum){
	if(ind < 0){
		A[cur++] = sum;
		return;
	}
	gen(ind - 1, sum);
	for(auto x : v[ind]){
		gen(ind - 1, sum + x);
	}
}
void testcase(){
	int n;
	cin >> n;
	M = cur = ans = 0;
	ll tot = 1;
	for(int i = 0; i < n; i++){
		int k;
		cin >> k;
		tot = tot * (k + 1);
		v[i].resize(k);
		for(auto &x : v[i])cin >> x;
	}
	cin >> p >> q;
	ll g = __gcd(p, q);
	p /= g;
	q /= g;
	if(q > n || p > (ll)n * INF){
		cout << "0\n";
		return;
	}
	sort(v, v + n, [&](vector<ll> &a, vector<ll> &b){
		return a.size() < b.size();
	});
	for(int i = 0; i < n; i++){
		for(auto &x : v[i])x = x * q - p;
	}
	ll mx = sqrtl(tot);
	ll part1 = 1;
	while(M < n){
		if(v[M].size() < mx){
			part1 *= (v[M].size() + 1);
			mx /= (v[M].size() + 1);
			M++;
		}else{
			break;
		}
	}
	assert(M < n);
	ll part2 = tot / part1 / (v[M].size() + 1);
	if(part1 < part2)M++;
	gen(M - 1, 0);
	int p1Cur = cur;
	for(int i = 0; i < cur; i++)B[i] = A[i];
	cur = 0;
	int t = 0;
	while(M < n){
		v[t++] = v[M++];
	}
	gen(t - 1, 0);
	int p2Cur = cur;
	
	int u = 0;
	if(p1Cur > p2Cur){
		sort(A, A + p2Cur);
		temp[u] = {A[0], 0};
		for(int i = 0; i < p2Cur; i++){
			if(temp[u].fi != A[i])u++;
			temp[u].fi = A[i];
			temp[u].se++;
		}
		u++;
		for(int i = 0; i < p1Cur; i++){
			int x = lower_bound(temp, temp + u, ii(-B[i], -1)) - temp;
			if(x < u && temp[x].fi == -B[i])
				ans += temp[x].se;
		}
	}else{
		sort(B, B + p1Cur);
		temp[u] = {B[0], 0};
		for(int i = 0; i < p1Cur; i++){
			if(temp[u].fi != B[i])u++;
			temp[u].fi = B[i];
			temp[u].se++;
		}
		u++;
		for(int i = 0; i < p2Cur; i++){
			int x = lower_bound(temp, temp + u, ii(-A[i], -1)) - temp;
			if(x < u && temp[x].fi == -A[i])
				ans += temp[x].se;
		}
	}
	
	for(int i = 0; i < u; i++)temp[i].se = 0;
	
	cout << ans - 1 << "\n";
	
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
