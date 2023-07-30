#include<bits/stdc++.h>
#define LL long long
#define fastIO ios_base::sync_with_stdio(false),cin.tie(NULL)

using namespace std;
namespace fs = std::filesystem;

/* constraints */
const int T_MAX = 100, T_MIN = 1; // test case
const int N_MAX = 1e6, N_MIN = 1; // N
const int D_MIN = 1, D_MAX = 1e7; // d[i]


/* handle files */
char* StringToPointer(string str) {
    // cout<<str<<" "<<str.size()<<endl;
    char* path = new char[str.size() + 1];
    for (int i = 0 ; i < str.size(); i++) {
        path[i] = str[i];
    }
    path[str.size()] = '\0';
    // printf(path);
    return path;
}


class Reader {
public:
    Reader(string fileName) {
        if (fileName == "") file = NULL;
        else file = fopen(StringToPointer(fileName), "r");
    }

    Reader() {
        file = NULL;
    }

    int ScanInt() {
        int a;
        if (file != NULL) assert(fscanf(file, "%d", &a) != EOF);
        else assert(scanf("%d", &a) != EOF);
        return a;
    }

private:
    FILE *file;
};

class Writer {
public:
    Writer(string fileName) {
        if (fileName == "") file = NULL;
        else file = fopen(StringToPointer(fileName), "w");
    }

    Writer() {
        file = NULL;
    }

    void PrintInt(int a) {
        if (file != NULL) fprintf(file, "%d   ", a);
        else printf("%d   ", a);
    }

    void PrintLL(LL a) {
        if (file != NULL) fprintf(file, "%lld ", a);
        else printf("%lld ", a);
    }

    void EndL() {
        if (file != NULL) fprintf(file, "\n");
        else printf("\n");
    }

private:
    FILE *file;
};


/* solution */
bool IsSame(int i, int j, vector < int > &nxt) {
    return 1LL*(nxt[i]-i)*(nxt[j]-j) >= 0;
}

bool IsCrossed(int i, int j, vector < int > &nxt) {
    return 1LL*(i-j)*(j-nxt[i]) >= 0 && 1LL*(j-i)*(i-nxt[j]) >= 0;
}

LL Move(
    int i,
    int j,
    vector < int > &dis,
    vector < int > &nxt,
    vector < int > &value,
    vector < pair < int,int > > &moves
) {
    swap(nxt[i], nxt[j]);
    swap(value[i], value[j]);
    moves.push_back({i,j});
    LL cost = 1LL*abs(dis[i] - dis[j])*(value[i] + value[j]);
    return cost;
}

// O(n) soln
LL SolveCycle(
    int n,
    vector < int > &dis,
    vector < int > &nxt,
    vector < int > &value,
    vector < pair < int,int > > &moves
) {
    if (nxt[n] == n) return 0;
    int cur = n;
    LL cost = 0;
    stack < int > nodes, lastNodes;

    while (nxt[cur] != cur) {
        int too = nxt[cur];
        if (!lastNodes.empty() && IsCrossed(cur, lastNodes.top(), nxt)) {
            int a = lastNodes.top();
            cost += Move(cur, a, dis, nxt, value, moves);

            // remove the cycle with cur in it
            while (!nodes.empty() && nodes.top() != a) {
                nodes.pop();
            }
            cost += SolveCycle(nxt[cur], dis, nxt, value, moves);
            // the following should solve but get a TLE verdict because of repeated push pop
            // cost += SolveCycle(cur, dis, nxt, value, moves);
            
            // remove the current node
            nodes.pop();
            lastNodes.pop();

            // keep the last node
            if (!nodes.empty()) {
                int b = nodes.top();
                if (IsSame(a, b, nxt)) {
                    if (!lastNodes.empty() && lastNodes.top() == b) {
                        lastNodes.pop();
                    }
                }
                else {
                    if (lastNodes.empty() || lastNodes.top() != b) {
                        lastNodes.push(b);
                    }
                }
            }
            cur = a;
        }
        else {
            nodes.push(cur);
            cur = nxt[cur];
        }

        if (!nodes.empty()) {
            int a = nodes.top();
            if (!IsSame(cur, a, nxt)) {
                if (lastNodes.empty() || lastNodes.top() != a) {
                    lastNodes.push(a);
                }
            }
        }
    }
    return cost;
}

void Solve(Reader* reader, Writer *writer) {
    int t = reader->ScanInt();

    while (t--) {
        int n = reader->ScanInt();
        vector < int > dis(n+1), perm(n+1), value(n+1);
        for (int i = 1; i <= n; i++) {
            value[i] = i;
            dis[i] = reader->ScanInt();
        }
        for (int i = 1; i <= n; i++) {
            perm[i] = reader->ScanInt();
        }

        LL cost = 0;

        vector < pair < int,int > > moves;
        for (int i = 1; i <= n; i++) {
            cost += SolveCycle(i, dis, perm, value, moves);
        }

        writer->PrintLL(cost);
        writer->PrintInt(moves.size());
        writer->EndL();
        
        for (auto move:moves) {
            writer->PrintInt(move.first);
            writer->PrintInt(move.second);
            writer->EndL();
        }
    }
}

void SolveFromConsole() {
    Reader* reader = new Reader();
    Writer* writer = new Writer();
    Solve(reader, writer);
}


int main() {
    SolveFromConsole();
    return 0;
}