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

/**
 * Send your busters out into the fog to trap ghosts and bring them home!
 **/
struct Pair {
    int id, x, y, v, s, afk;    
} g[100], b[20], e[20], po[4], pp[4], A[20], BB[20], BBB[20], AA[20];
int sz (int x, int y, int x1, int y1) {
    return ((x - x1) * (x - x1)) + ((y - y1) * (y - y1));    
}
int st[20], pw[20];
bool was[20];
int main()
{
    srand(259);
    int bustersPerPlayer; // the amount of busters you control
    cin >> bustersPerPlayer; cin.ignore();
    int ghostCount; // the amount of ghosts on the map
    cin >> ghostCount; cin.ignore();
    int myTeamId; // if this is 0, your base is on the top left of the map, if it is one, on the bottom right
    cin >> myTeamId; cin.ignore();
    pp[0].x = 2573;
    pp[0].y = 1371;
    pp[1].x = 1457;
    pp[1].y = 2535;
    po[0].x = 13497;
    po[0].y = 7570;
    po[1].x = 14732;
    po[1].y = 6335;
    // game loop
    int ss, sss, G = 0, ans = 0;
    //bool rp = false;
    int z;
        if (myTeamId == 0)
            z = 0;
        else
            z = bustersPerPlayer;
    A[0].x = 1500;
    A[0].y = 7500;
    A[1].x = 11000;
    A[1].y = 7500;
    A[2].x = 4500;
    A[2].y = 4000;
    BB[0].x = 14500;
    BB[0].y = 1500;
    BB[1].x = 14500;
    BB[1].y = 4500;
    BB[2].x = 8000;
    BB[2].y = 4500;
    AA[0].x = 1500;
    AA[0].y = 7500;
    AA[1].x = 1500;
    AA[1].y = 4500;
    AA[2].x = 7500;
    AA[2].y = 4500;
    BBB[0].x = 14500;
    BBB[0].y = 1500;
    BBB[1].x = 5000;
    BBB[1].y = 1500;
    BBB[2].x = 11500;
    BBB[2].y = 5000;
    
    int t = z, xx = 0, yy = 0;
    for (int i = z; i < bustersPerPlayer + z; ++i) {
        pw[i] = 20;
    }
    int O = 0;
    while (1) {
        int entities; // the number of busters and ghosts visible to you
        cin >> entities; cin.ignore();
        //bustersPerPlayer = 0;
        G = 0;
        for (int i = 0; i < entities; ++i) {
            int entityId; // buster id or ghost id
            int x;
            int y; // position of this buster / ghost
            int entityType; // the team id if it is a buster, -1 if it is a ghost.
            int state; // For busters: 0=idle, 1=carrying a ghost.
            int value; // For busters: Ghost id being carried. For ghosts: number of busters attempting to trap this ghost.
            cin >> entityId >> x >> y >> entityType >> state >> value; cin.ignore();
            if (entityType != myTeamId && entityType != -1) {
                e[entityId].x = x;
                e[entityId].y = y;
                e[entityId].s = state;
                e[entityId].v = value;
                was[entityId] = true;
            }
            if (entityType == myTeamId) {
                b[entityId].x = x;
                b[entityId].y = y;
                
                b[entityId].s = state;
                b[entityId].v = value;
            }
            if (entityType == -1) {
                g[++G].x = x;
                g[G].id = entityId;
                g[G].y = y;
                g[G].s = state;
                g[G].v = value;
                
            }
        }
        O += 2;
        for (int i = z; i < bustersPerPlayer + z; ++i)
            pw[i]++, st[(bustersPerPlayer + i) % (bustersPerPlayer * 2)]--, cerr << (bustersPerPlayer + i) % (bustersPerPlayer * 2) << "\n";
            
        for (int i = z; i < bustersPerPlayer + z; ++i) {
            if (b[i].s == 1) {
                bool of = false;
                for (int j = bustersPerPlayer - z; j < bustersPerPlayer * 2 - z; ++j) {
                    if (!was[j])
                        continue;
                    ss = sz(e[j].x, e[j].y, b[i].x, b[i].y);
                    //cerr << j << " " << e[j].x << " " << e[j].y << " " << b[i].x << " " << b[i].y << " " << ss << "---\n";
                    if (st[j] <= 0 && ss <=  1760 * 1760 && pw[i] >= 20) {
                        cout << "STUN " << " " << j << "\n";
                        cerr << "Vrag na baze\n";
                        b[i].afk = 0;
                        pw[i] = 0;
                        st[j] = 10;
                        of = true;
                        break;
                    }    
                }
                if (of)
                    continue;
                if (myTeamId == 0) {
                    if (1120 >= b[i].x && 1120 >= b[i].y) {
                        cout << "RELEASE\n";
                        cerr << "Dostavleno\n";
                        ans++;
                        b[i].afk = 0;
                        continue;
                    }
                    if ((b[i].x > 3000 && b[i].y > 0) || (b[i].x > 0 && b[i].y > 3000)) {
                        ss = sz(3000, 0, b[i].x, b[i].y);
                        sss = sz(0, 3000, b[i].x, b[i].y);
                        if (ss > sss) {
                            cout << "MOVE 0 3000\n";
                            cerr << "Proxod po y\n";
                            b[i].afk = 0;
                        }
                        else {
                            cout << "MOVE 3000 0\n";
                            cerr << "Proxod po x\n";
                            b[i].afk = 0;
                        }
                        continue;
                    }
                    cout << "MOVE 0 0\n";
                    cerr << "Dostavliau\n";
                    b[i].afk = 0;
                    continue;
                }
                if (14880 <= b[i].x && 7880 <= b[i].y) {
                    cout << "RELEASE\n";
                    ans++;
                    cerr << "Dostavleno\n";
                    b[i].afk = 0;
                    continue;
                }
                if ((b[i].x < 13000 && b[i].y < 9000) || (b[i].x < 16000 && b[i].y < 6000)) {
                        ss = sz(13000, 9000, b[i].x, b[i].y);
                        sss = sz(16000, 6000, b[i].x, b[i].y);
                        if (ss > sss) {
                            cout << "MOVE 16000 3000\n";
                            cerr << "Proxod po y\n";
                            b[i].afk = 0;
                        }
                        else {
                            cout << "MOVE 13000 9000\n";
                            cerr << "Proxod po x\n";
                            b[i].afk = 0;
                        }
                        continue;
                }
                cout << "MOVE 16000 9000\n";
                cerr << "Dostavliau\n";
                b[i].afk = 0;
                continue;
            }
            bool ok = false, jdi = false, oxota = false;
            int xxx, yyy;
            bool of = false;
            for (int j = bustersPerPlayer - z; j < bustersPerPlayer * 2 - z; ++j) {
                if (!was[j])
                    continue;
                ss = sz(e[j].x, e[j].y, b[i].x, b[i].y);
                cerr << j << " " << ss << " " << st[j] << " " << e[j].v << " " << pw[i] << "----\n";
                if (st[j] <= 0 && ss <= 1760 * 1760 && pw[i] >= 20 && (e[j].s == 1 || e[j].s == 3)) {
                    cout << "STUN " << " " << j << "\n";
                    cerr << "Voruem\n";
                    pw[i] = 0;
                    st[j] = 10;
                    of = true;
                    b[i].afk = 0;
                    break;
                }    
            }
            if (of)
                continue;
            for (int j = 1; j <= G; ++j) {
                ss = sz(g[j].x, g[j].y, b[i].x, b[i].y);
                cerr << g[j].s << " " << O << " " << ss << " " << g[j].id << " <---Range\n";
                if (((O <= 50 && g[j].s <= 3) || (O > 50 && O <= 150 && g[j].s <= 15)  || (O > 150 && g[j].s <= 40)) && ss >= 900 * 900 && ss <= 1760 * 1760) {
                    cout << "BUST " << g[j].id << "\n";
                    cerr << "Beru 3aka3\n";
                    b[i].afk = 0;
                    ok = true;
                    break;
                }
                if (((O <= 50 && g[j].s <= 3) || (O > 50 && O <= 150 && g[j].s <= 15)  || (O > 150 && g[j].s <= 40)) && ss < 900 * 900)
                    jdi = true;
                if (((O <= 50 && g[j].s <= 3) || (O > 50 && O <= 150 && g[j].s <= 15)  || (O > 150 && g[j].s <= 40)) && ss > 1760 * 1760 && ss <= 2200 * 2200) {
                    xxx = g[j].x;
                    yyy = g[j].y;
                    oxota = true;
                }
            }
            if (ok)
                continue;
            if (jdi) {
                cout << "MOVE " << rand() % 16000 << " " << rand() % 9000 << "\n";
                cerr << "Riadom\n";
                b[i].afk = 0;
                continue;
            }
            if (oxota) {
                cout << "MOVE " << xxx << " " << yyy << "\n";
                cerr << "Na oxotu\n";
                b[i].afk = 0;
                continue;
            }
            if ((ans * 100) / ghostCount >= 30 && b[i].afk <= 70) {
                if (myTeamId == 0) {
                    int zz = rand() % 2;
                    cout << "MOVE " << po[zz].x << " " << po[zz].y << "\n";
                    cerr << "Idem vorovat\n";
                    b[i].afk++;
                } 
                else {
                    int zz = rand() % 2;
                    cout << "MOVE " << pp[zz].x << " " << pp[zz].y << "\n";
                    cerr << "Idem vorovat\n";
                    b[i].afk++;
                }
                continue;
            }
            if (myTeamId == 0) {
                if (i == 0) {
                    if (A[xx % 3].x == b[i].x && A[xx % 3].y == b[i].y)
                        xx = (xx + 1) % 3;
                    cout << "MOVE " << A[xx].x << " " << A[xx].y << "\n";
                    cerr << "Tochka\n";
                    continue;
                }
                if (i == 1) {
                    if (BB[yy % 3].x == b[i].x && BB[yy % 3].y == b[i].y)
                        yy = (yy + 1) % 3;
                    cout << "MOVE " << BB[yy].x << " " << BB[yy].y << "\n";
                    cerr << "Tochka\n";

                    continue;
                }
                int zz = rand() % 2;
                    cout << "MOVE " << po[zz].x << " " << po[zz].y << "\n";
                    cerr << "Ia  treti ili 4\n";
                continue;
            }
            if (myTeamId == 1) {
                cerr << i << " nomer\n";
                if (i == z) {
                    if (AA[xx % 3].x == b[i].x && AA[xx % 3].y == b[i].y)
                        xx = (xx + 1) % 3;
                    cout << "MOVE " << AA[xx].x << " " << AA[xx].y << "\n";
                    cerr << "Tochka\n";
                    continue;
                }
                if (i == z + 1) {
                    if (BBB[yy % 3].x == b[i].x && BBB[yy % 3].y == b[i].y)
                        yy = (yy + 1) % 3;
                    cout << "MOVE " << BBB[yy].x << " " << BBB[yy].y << "\n";
                    cerr << "Tochka\n";
                    continue;
                }
                int zz = rand() % 2;
                cout << "MOVE " << pp[zz].x << " " << pp[zz].y << "\n";
                cerr << "Ia  treti ili 4\n";
            }
            /*ss = sz(b[i].x, b[i].y, xx[i], yy[i]);
            while (ss < 800 * 800) {
                xx[i] = rand() % 16001;
                yy[i] = rand() & 9001;
                ss = sz(b[i].x, b[i].y, xx[i], yy[i]);
            }
            cout << "MOVE " << xx[i] << " " << yy[i] << "\n";
            cerr << "Randomnaia Tochka\n";*/
        }
        for (int i = 0; i <= 8; ++i)
            was[i] = false;
    }
}