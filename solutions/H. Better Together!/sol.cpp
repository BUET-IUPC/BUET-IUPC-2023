#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 998244353;
const ll inf = 1LL << 60;
 
int N, M;
pii P[100010];
ll gcd(ll a, ll b){
    if(b == 0)return a;
    return gcd(b, a % b);
}
int main(void){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> N >> M;
    for(int i = 0;i < M;i++)cin >> P[i].second >> P[i].first;
    sort(P, P + M);
    ll g = N, ans = 0;
    for(int i = 0;i < M;i++){
        ll ng = gcd(g, P[i].second);
        ans += P[i].first * (g - ng);
        g = ng;
    }
    cout << (g == 1 ? ans : -1) << endl;
    return 0;
}
