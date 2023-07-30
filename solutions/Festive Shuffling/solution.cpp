#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
using namespace std;
#define getbit(n, i) (((n) & (1LL << (i))) != 0) 
#define setbit0(n, i) ((n) & (~(1LL << (i)))) 
#define setbit1(n, i) ((n) | (1LL << (i))) 
#define togglebit(n, i) ((n) ^ (1LL << (i))) 
#define lastone(n) ((n) & (-(n))) 
char gap = 32;

#define ll long long 
#define lll __int128_t
#define pb push_back
typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll hashPrime = 1610612741;
string s; 
int k; 
int dp[501][501][501];
int is_special_position[501];

int in_between[501][501];


int recurse(int l, int r, int one_count) {
    if(l > r) return 0;
    if(dp[l][r][one_count] != -1) return dp[l][r][one_count];
    int ans = 0;
    if(l == r) return 1;
    else {
        if(is_special_position[l] and is_special_position[r]) {
            if(one_count >= 2) {
                ans = max(ans, 2 + recurse(l + 1, r - 1, one_count - 2));
            }
            if(in_between[l][r] - one_count >= 2) {
                ans = max(ans, 2 + recurse(l + 1, r - 1, one_count));
            }
            if(one_count >= 1) {
                ans = max({ans, recurse(l + 1, r, one_count - 1), recurse(l, r - 1, one_count - 1)});
            }
            if(in_between[l][r] - one_count >= 1) {
                ans = max({ans, recurse(l + 1, r, one_count), recurse(l, r - 1, one_count)});
            }
        }
        else if(is_special_position[l]) {
            if(one_count >= 1) {
                ans = recurse(l + 1, r, one_count - 1);
                ans = max(ans, recurse(l, r - 1, one_count));
                if(s[r - 1] == '1') ans = max(ans, 2 + recurse(l + 1, r - 1, one_count - 1));
            }
            if(in_between[l][r] - one_count >= 1) {
                ans = max(ans, recurse(l + 1, r, one_count));
                ans = max(ans, recurse(l, r - 1, one_count));
                if(s[r - 1] == '0') ans = max(ans, 2 + recurse(l + 1, r - 1, one_count));
            }
        }
        else if(is_special_position[r]) {
            if(one_count >= 1) {
                ans = recurse(l + 1, r, one_count);
                ans = max(ans, recurse(l, r - 1, one_count - 1));
                if(s[l - 1] == '1') ans = max(ans, 2 + recurse(l + 1, r - 1, one_count - 1));
            }
            if(in_between[l][r] - one_count >= 1) {
                ans = max(ans, recurse(l + 1, r, one_count));
                ans = max(ans, recurse(l, r - 1, one_count));
                if(s[l - 1] == '0') ans = max(ans, 2 + recurse(l + 1, r - 1, one_count));
            }
        }
        else {
            ans = max(recurse(l + 1, r, one_count), recurse(l, r - 1, one_count));
            if(s[l - 1] == s[r - 1]) ans = max(ans, recurse(l + 1, r - 1, one_count) + 2);
        }
    }
    return dp[l][r][one_count] = ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> s;

    cin >> k;
    for(int i = 1; i <= k; i++) {
        int idx; cin >> idx;
        is_special_position[idx] = 1;
    }
    int n = s.size();
    for(int i = 1; i <= n; i++) {
        int cnt = 0;
        for(int j = i; j <= n; j++) {
            cnt += is_special_position[j];
            in_between[i][j] = cnt;
        }
    } 

    memset(dp, -1, sizeof(dp));

    int total_ones = 0;
    for(int i = 1; i <= n; i++) {
        if(s[i - 1] == '1' and is_special_position[i]) total_ones++;
    }

    cout << recurse(1, n, total_ones) << "\n";

    return 0;
}
