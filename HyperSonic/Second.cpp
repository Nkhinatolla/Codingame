//By Nurbergen Hinatolla
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <cstring>
#include <cstdlib>  
#include <stdio.h>
#include <cstdio>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <cmath>
#include <math.h>
#include <map>
#include <set>
#include <time.h>
#include <bitset>
inline int Rand() { return (rand() << 16) | rand(); }
#define y1 google
#define INF 1000000000000000000LL
#define inf 2147483647
#define MOD 1000000007
#define pf push_front
#define pb push_back
#define mp make_pair
#define FI first
#define SI second
#define fname "" 
                                
using namespace std;

typedef long long ll;

const int N = 200005;
const double eps = 1e-9;

struct Pair {
    int x, y;     
    int p1, o, p2;
} A, E;
struct que {
    int x, y, u, m;    
} q[N], was[100][100], w[100][100], escape[10000];
 vector <Pair> B;
int r;
string row[20];
int width;
int height, ha = 0;
int watch[1000];
int myId, level = 0;
int s[20][20], ss[20][20];
void go(int v,  int u, int i, int j) {
    if (v < 0 || v > height || u < 0 || u > width || was[v][u].u || ((row[v][u] != '.') && s[v][u] >= was[i][j].m + 1) || (s[v][u] > 0 && row[v][u] == '.' && abs(s[v][u] - (was[i][j].m + 1)) <= 1))
        return;
    for (auto ii : B) {
        if (ii.x == v && ii.y == u)
            return;
    }
    was[v][u].u = true;
    q[++r].x = v;
    q[r].y = u;
    was[v][u].x = i;
    was[v][u].y = j;
    was[v][u].m = was[i][j].m + 1;
}
void go1(int v, int u, int i, int j) {
    if (v < 0 || v > height || u < 0 || u > width || w[v][u].u || ((row[v][u] != '.') && ss[v][u] >= w[i][j].m + 1) || (ss[v][u] > 0 && row[v][u] == '.' && abs(ss[v][u] - (w[i][j].m + 1) <= 1)))
        return;
    for (auto ii : B) {
        if (ii.x == v && ii.y == u)
            return;
    }
    w[v][u].u = true;
    q[++r].x = v;
    q[r].y = u;
    w[v][u].x = i;
    w[v][u].y = j;
    w[v][u].m = w[i][j].m + 1;
}
int calc(int x, int y) {
    int kol = 0;
    int k = A.p2 - 1;
    int x1 = x - 1, y1 = y;
    while (k > 0) {
        if (x1 < 0 || s[x1][y1] == 100)
            break;
        bool ok = false;
        for (auto ii : B) {
            if (ii.x == x1 && ii.y == y1) {
                ok = true;
                break;
            }
        }
        if (ok)
            break;
        if (s[x1][y1] == 50) {
            kol++;
            break;
        }
        x1--;    
        k--;
    }
    k = A.p2 - 1;
    x1 = x + 1, y1 = y;
    while (k > 0) {
        if (x1 >= height || s[x1][y1] == 100)
            break;
        bool ok = false;
        for (auto ii : B) {
            if (ii.x == x1 && ii.y == y1) {
                ok = true;
                break;
            }
        }
        if (ok)
            break;
        if (s[x1][y1] == 50) {
            kol++;
            break;
        }
        x1++;    
        k--;
    }
    k = A.p2 - 1;
    x1 = x, y1 = y - 1;
    while (k > 0) {
        if (y1 < 0 || s[x1][y1] == 100)
            break;
        bool ok = false;
        for (auto ii : B) {
            if (ii.x == x1 && ii.y == y1) {
                ok = true;
                break;
            }
        }
        if (ok)
            break;
        if (s[x1][y1] == 50) {
            kol++;
            break;
        }
        y1--;    
        k--;
    }
    k = A.p2 - 1;
    x1 = x, y1 = y + 1;
    while (k > 0) {
        if (y1 >= width || s[x1][y1] == 100)
            break;
        bool ok = false;
        for (auto ii : B) {
            if (ii.x == x1 && ii.y == y1) {
                ok = true;
                break;
            }
        }
        if (ok)
            break;
        if (s[x1][y1] == 50) {
            kol++;
            break;
        }
        y1++;    
        k--;
    }
    return kol;
}
bool Find() {
    int mn = 1000, mnn = 1, posx, posy;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j)
            if (was[i][j].u && (s[i][j] == 0 || (s[i][j] != 0 && s[i][j] - was[i][j].m > mn)))
                mnn = s[i][j], mn = was[i][j].m, posx = i, posy = j;
    }
    if (mn == 1000)
        return false;
    int x1 = posx, y1 = posy;
    int X;
    while (was[x1][y1].x != A.x || was[x1][y1].y != A.y) {
        X = x1;
        x1 = was[x1][y1].x, y1 = was[X][y1].y;
    }
    cout << "MOVE " << y1 << " " << x1 << endl;
    cerr << "OBXOD " << posx << " " << posy << "\n";          
    return true;
}
bool check(int x, int y, int timer) {
    if (s[x][y] > 0 && s[x][y] <= (8 - timer) + (was[x][y].m + 1))
        return false;
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j) {
            ss[i][j] = max(s[i][j] - (8 - timer) - (was[x][y].m + 1), 0);
            w[i][j].u = false, w[i][j].m = 1000;
        }
    Pair i;
    i.x = x;
    i.y = y;
    i.p1 = timer;
    i.p2 = A.p2;
    ss[i.x][i.y] = i.p1;
   // cerr << "Coor " << ss[i.x][i.y] << " " << i.x << " " << i.y << "\n";
    int k = i.p2 - 1;
    int x1 = i.x - 1, y1 = i.y;
    while (k > 0) {
        if (x1 < 0 || ss[x1][y1] == 100)
            break;
        if (ss[x1][y1] == 50) {
            ss[x1][y1] = i.p1;
            break;
        }
        if (ss[x1][y1] != 100 && ss[x1][y1] > 0)
            ss[x1][y1] = min(ss[x1][y1], i.p1);
        else
            ss[x1][y1] = i.p1;
            x1--;    
            k--;
    }
    x1 = i.x + 1, y1 = i.y;
    k = i.p2 - 1;
    while (k > 0) {
        if (x1 >= height || ss[x1][y1] == 100)
            break;
        if (ss[x1][y1] == 50) {
            ss[x1][y1] = i.p1;
            break;
        }
        if (ss[x1][y1] != 100 && ss[x1][y1] > 0)
            ss[x1][y1] = min(ss[x1][y1], i.p1);
        else
            ss[x1][y1] = i.p1;
        x1++;    
        k--;
    }
    x1 = i.x, y1 = i.y - 1;
    k = i.p2 - 1;
    while (k > 0) {
        if (y1 < 0 || ss[x1][y1] == 100)
            break;
        if (ss[x1][y1] == 50) {
            ss[x1][y1] = i.p1;
            break;
        }
        if (ss[x1][y1] != 100 && ss[x1][y1] > 0)
            ss[x1][y1] = min(ss[x1][y1], i.p1);
        else
            ss[x1][y1] = i.p1;
            y1--;    
            k--;
    }
    x1 = i.x, y1 = i.y + 1;
    k = i.p2 - 1;
    while (k > 0) {
        if (y1 >= width || ss[x1][y1] == 100)
            break;
        if (ss[x1][y1] == 50) {
            ss[x1][y1] = i.p1;
            break;
        }
        if (ss[x1][y1] != 100 && ss[x1][y1] > 0)
            ss[x1][y1] = min(ss[x1][y1], i.p1);
        else
            ss[x1][y1] = i.p1;
        y1++;    
        k--;
    }
    
    w[x][y].u = true;
    w[x][y].m = 0;
    int l = 1;
    r = 1;
    q[1].x = x;
    q[1].y = y;
    while (l <= r) {
        int i = q[l].x;
        int j = q[l].y;
        go1(i + 1, j, i, j);
        go1(i - 1, j, i, j);
        go1(i, j - 1, i, j);
        go1(i, j + 1, i, j);
        l++;
    }
    if (ss[x][y] != 0)
        w[x][y].u = false;
    int stats = 0;
    int M = 1000;
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j) {
            if (w[i][j].u && (ss[i][j] == 0 || ((ss[i][j] - w[i][j].m) < -1 && A.p1 - 1 > 0))) {
                return true;
          /*      if (M > w[i][j].m) {
                    M = w[i][j].m; 
                    escape[level].x = i;
                    escape[level].y = j; 
                   // cerr << "Safe Point " << escape[level].x << " " << escape[level].y << " " << ss[i][j] << "\n";
                }*/
            }         
        }
    return false;
}
void league1() {
    if (watch[ha - 1]) {
        cout << "MOVE " << A.y << " " << A.x << endl;
        cerr << "Wait " << watch[ha - 1] << endl;
        watch[ha - 1]--;
        return;
    }
    bool T = 0;
    if (T == 1) {
        be:
        return;
    }
    was[A.x][A.y].u = true;
    was[A.x][A.y].m = 0;
    int l = 1;
    r = 1;
    q[1].x = A.x;
    q[1].y = A.y;
    while (l <= r) {
        int i = q[l].x;
        int j = q[l].y;
        go(i + 1, j, i, j);
        go(i - 1, j, i, j);
        go(i, j - 1, i, j);
        go(i, j + 1, i, j);
        l++;
    }
    if (s[A.x][A.y] != 0)
        was[A.x][A.y].u = false;
    int col = 0, mn = 1000;
    que ans;
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j) {
            if (was[i][j].u == false)
                continue;
            int c = calc(i, j);
            if (s[i][j] > 0 && abs(s[i][j] - was[i][j].m) <= 1)
                continue;
            //cerr << i << " " << j << " " << s[i][j] << " " << c << endl;
            //cerr << c << " " << i << " " << j << endl;
            if ((c == col && was[i][j].m < mn) || c > col) {
                bool xorowo = false;
                for (int r = 8; r >= 2; --r) {
                    if (check(i, j, r)) {
                        xorowo = true;
                        watch[ha] = 8 - r;
                        break;
                    }
                }
                if (!xorowo)
                    continue;
                col = c, mn = was[i][j].m;
                ans.x = i;
                ans.y = j;
            }
        }
    cerr << col << " " << ans.y << " " << ans.x << " " << escape[level].x << " " << escape[level].y << endl;
    if (col == 0) {
        if (s[A.x][A.y] > 0) {
            if (!Find()) {
                cout << "MOVE " << A.y << " " << A.x << endl;
                cerr << "Stay " << A.y << " " << A.x << endl;    
            }
        }
        else {
            cout << "MOVE " << A.y << " " << A.x << endl;
            cerr << "Stay " << A.y << " " << A.x << endl;    
        }
            
        goto be;
    }
    if (ans.x == A.x && ans.y == A.y) {
        if (A.p1 == 0) {
            cout << "MOVE " << A.y << " " << A.x << endl;
            cerr << "No Bomb\n";
            goto be;
        }
        level++;
        ha++;
        cout << "BOMB " << A.y << " " << A.x << endl;
        cerr << "Plant on " << A.y << " " << A.x << endl;
        goto be;
    }
    int x1 = ans.x, y1 = ans.y;
    int X;
    while (was[x1][y1].x != A.x || was[x1][y1].y != A.y) {
        X = x1;
        x1 = was[x1][y1].x, y1 = was[X][y1].y;
    }
    cout << "MOVE " << y1 << " " << x1 << endl;
    cerr << "Go to " << y1 << " " << x1 << endl;
} 
int main()
{
    cin >> width >> height >> myId; cin.ignore();
    while (1) {
        for (int i = 0; i < height; ++i, cerr << "\n") {
            cin >> row[i]; cin.ignore();
            for (int j = 0; j < row[i].size(); ++j) {
                cerr << row[i][j];
                s[i][j] = 0;
                was[i][j].u = 0;
                was[i][j].m = 1000;
                if (row[i][j] != '.')
                    s[i][j] = 50;
                if (row[i][j] == 'X')
                    s[i][j] = 100;
            }
        }
        int entities;
        cin >> entities; cin.ignore();
        B.clear();
        for (int i = 0; i < entities; i++) {
            int entityType;
            int owner;
            int x;
            int y;
            int param1;
            int param2;
            cin >> entityType >> owner >> y >> x >> param1 >> param2; cin.ignore();
            if (entityType == 0) {
                if (owner == myId) {
                    A.x = x;
                    A.y = y;
                    A.p1 = param1;
                    A.p2 = param2;
                }
                else {
                    E.x = x;
                    E.y = y;
                    E.p1 = param1;
                    E.p2 = param2;
                }
            }
            else 
                if (entityType == 1) {
                Pair z; 
                z.o = owner;
                z.p1 = param1;
                z.p2 = param2;
                z.x = x;
                z.y = y;
                    B.pb(z);
                }
        }
        //cerr << B.size() << "\n";
        for (auto i : B) {
            if (i.p1 == 0)
                continue;
            //cerr << i.x << " " << i.y << " " << i.p1 << endl;
            s[i.x][i.y] = i.p1;
            int k = i.p2 - 1;
            int x1 = i.x - 1, y1 = i.y;
            while (k > 0) {
                if (x1 < 0 || s[x1][y1] == 100)
                    break;
                if (s[x1][y1] == 50) {
                    s[x1][y1] = i.p1;
                    break;
                }
                if (s[x1][y1] != 100 && s[x1][y1] > 0)
                    s[x1][y1] = min(s[x1][y1], i.p1);
                else
                    s[x1][y1] = i.p1;
                x1--;    
                k--;
            }
            x1 = i.x + 1, y1 = i.y;
            k = i.p2 - 1;
            while (k > 0) {
                if (x1 >= height || s[x1][y1] == 100)
                    break;
                if (s[x1][y1] == 50) {
                    s[x1][y1] = i.p1;
                    break;
                }
                if (s[x1][y1] != 100 && s[x1][y1] > 0)
                    s[x1][y1] = min(s[x1][y1], i.p1);
                else
                    s[x1][y1] = i.p1;
                x1++;    
                k--;
            }
            x1 = i.x, y1 = i.y - 1;
            k = i.p2 - 1;
            while (k > 0) {
                if (y1 < 0 || s[x1][y1] == 100)
                    break;
                if (s[x1][y1] == 50) {
                    s[x1][y1] = i.p1;
                    break;
                }
                if (s[x1][y1] != 100 && s[x1][y1] > 0)
                    s[x1][y1] = min(s[x1][y1], i.p1);
                else
                    s[x1][y1] = i.p1;
                y1--;    
                k--;
            }
            x1 = i.x, y1 = i.y + 1;
            k = i.p2 - 1;
            while (k > 0) {
                if (y1 >= width || s[x1][y1] == 100)
                    break;
                if (s[x1][y1] == 50) {
                    s[x1][y1] = i.p1;
                    break;
                }
                if (s[x1][y1] != 100 && s[x1][y1] > 0)
                    s[x1][y1] = min(s[x1][y1], i.p1);
                else
                    s[x1][y1] = i.p1;
                y1++;    
                k--;
            }
        }
        league1();
    }
}