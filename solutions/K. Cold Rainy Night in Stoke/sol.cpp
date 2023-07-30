#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fast ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;

#define Point pair<int,int>
#define Vector Point
#define x first
#define y second
#define Segment pair<int,int> //indices

const int N=500;

int n;
vector<Point> v;
Point C(0,0);
int R;
vector<Segment>all; // first=from, second=to
ll dist[N][N];

bool up (Vector p) {
  return p.y > 0 or (p.y == 0 and p.x >= 0);
}

Vector getVector(Point from, Point to)
{
    return Vector(to.x-from.x,to.y-from.y);
}
ll getCross(Vector A, Vector B)
{
    return (1LL*A.x*B.y-1LL*A.y*B.x);
}
ll triangleDoubleArea(Point a, Point b)
{
    ll ans=1LL*a.x*b.y+1LL*b.x*(-a.y);

    return ans;
}

void solve()
{
    cin>>n;
    v.resize(n);
    all.clear();
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            dist[i][j]=1e18;
        }

    }
    for(auto &u:v)
        cin>>u.x>>u.y;
    cin>>R;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(v[i]==v[j]) continue;

            Vector i_to_j=getVector(v[i],v[j]);
            Vector i_to_center=getVector(v[i],C);

            ll area_2=triangleDoubleArea(v[i],v[j]);

            if(area_2<0) continue;

            ll area_area_4=area_2*area_2;

            ll base_squared=1LL*(v[i].x-v[j].x)*(v[i].x-v[j].x)+
                            1LL*(v[i].y-v[j].y)*(v[i].y-v[j].y);

            ll left=area_area_4/(1LL*R*R);

            if(left>=base_squared)
            {
                all.push_back(Segment(i,j));
            }
        }
    }
    sort(all.begin(),all.end(),[&](Segment s1, Segment s2)
     {
         Vector v1=getVector(v[s1.first],v[s1.second]);
         Vector v2=getVector(v[s2.first],v[s2.second]);
         return up(v1) == up(v2) ? getCross(v1,v2) > 0 : up(v1) < up(v2);
     });
    for(Segment s:all)
    {
        ll area=triangleDoubleArea(v[s.first],v[s.second]);
        dist[s.first][s.second]=min(dist[s.first][s.second], area);
        for(int i=0;i<n;i++)
        {
            dist[i][s.second]=min(dist[i][s.second], dist[i][s.first]+area);
        }
    }
    ll ans=1e18;
    for(int i=0;i<n;i++)
    {
        ans=min(ans,dist[i][i]);
    }
    if(ans==1e18) cout<<"-1\n";
    else cout<<ans<<"\n";
}

main()
{
    fast;
    int t;
    cin>>t;
    while(t--)
    {
        solve();
    }
}

