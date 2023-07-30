#include<bits/stdc++.h>
using namespace std;
typedef long double Tf;
typedef long double Ti;

const Tf PI = acos(-1);
struct PT {
  Ti x, y;
  PT(Ti _x = 0, Ti _y = 0) : x(_x), y(_y) {}
  PT operator - (const PT& u)
            const { return PT(x - u.x, y - u.y); }
};
Tf angle(PT u) { return atan2(u.y, u.x); }
Tf angleBetween(PT a, PT b) { //in range [-PI, PI]
  Tf ans = angle(b) - angle(a);
  return ans <= -PI ? ans + 2*PI :
                    (ans > PI ? ans - 2*PI : ans);
}

void solve(int ces){
    Tf X, v;
    cin>>X>>v;
    Tf k = sqrtl(v*v-1);
    Tf a = 1-X;
    PT src = PT(1, 0);
    PT center = PT(0, 1/k);
    PT dest;
    dest.x = (a*v - sqrtl(a*a-1))*v/((v*v-1)*a*a+1);
    dest.y = k*(a*dest.x-1);

    Tf theta = angleBetween(src-center, dest-center);
    if(theta<0) theta += 2*PI;
    cout<< fixed << setprecision(12) << v*theta/k+sqrtl(a*a-1) << "\n";
}
/*
*/
int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int tc=1;
    cin>>tc;
    for(int ces=1; ces<=tc; ces++){
        solve(ces);
    }
}
