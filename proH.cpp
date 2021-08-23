//ngqminh.cl2735
#include <bits/stdc++.h>
#define PB push_back
#define pii pair <ll,ll>
#define vi vector <int>
#define vii vector <pii>
#define mpa make_pair
#define oo INT_MAX
#define F first
#define S second
#define reset(x, i) memset(x,i,sizeof(x))
#define sz(x) int(x.size())
#define mp make_pair
#define maxn 200005
#define coso 311
#define MOD 1000000007
#define Task "proH"
using namespace std;
ifstream fi(Task".inp");
ofstream fo(Task".out");
typedef long long ll;
typedef long double ld;
int n, m;
string s;
pii ST[maxn * 4];
int id[maxn];
ll mu[maxn];
int pos[maxn];
void Init(int nut, int l, int r)
{
    if (l == r)
    {
        ST[nut].F = s[l] - '0';
        id[l] = nut;
        ST[nut].S = 1;
        pos[nut] = l;
        return;
    }
    int mid = (l + r)/2;
    Init(nut * 2, l , mid);
    Init(nut * 2 + 1, mid + 1, r);
    ST[nut].S = ST[nut * 2].S + ST[nut * 2 + 1].S;
    ST[nut].F = (ST[nut * 2].F * mu[ST[nut * 2 + 1].S] % MOD + ST[nut * 2 + 1].F) % MOD;
}
pii get_hash(int nut, int l, int r, int u, int v)
{
    if (u > r || v < l) return {0, 0};
    if (l >= u && v >= r) return ST[nut];
    int mid = (l + r)/2;
    pii getL = get_hash(nut * 2, l, mid, u, v);
    pii getR = get_hash(nut * 2 + 1, mid + 1, r, u, v);
    return {(getL.F * mu[getR.S] % MOD + getR.F) % MOD, getL.S + getR.S};
}
void xoa (int x)
{
    int nut = id[x];
    ST[nut] = {0, 0};
    while (nut > 1)
    {
        nut /= 2;
        ST[nut].S = ST[nut * 2].S + ST[nut * 2 + 1].S;
        ST[nut].F = (ST[nut * 2].F * mu[ST[nut * 2 + 1].S] % MOD + ST[nut * 2 + 1].F) % MOD;
    }
}
int Get_pos(int nut, int l, int r, int u){
    if(l == r) return pos[nut];
    int x = ST[nut * 2].S;
    int y = ST[nut * 2 + 1].S;
    int mid = (l + r)/2;
    if(u <= x) return Get_pos(nut * 2, l, mid, u);
    else return Get_pos(nut * 2 + 1, mid + 1, r, u - x);
}
int main() {
    ios_base::sync_with_stdio(0); cin.tie(); cout.tie();
    cin >> s;
    n = sz(s);
    s = " " + s;
    mu[0] = 1;
    for (int i = 1; i <= n + 1; i ++)
        mu[i] = (mu[i - 1] * coso) % MOD;
    Init(1, 1, n);
    cin >> m;
    while (m --)
    {
        char type;
        int x, y, z;
        cin >> type;
        if (type == '?')
        {
            cin >> x >> y >> z;
            int xx = Get_pos(1, 1, n, x);
            int yy = Get_pos(1, 1, n, y);
            int pp = Get_pos(1, 1, n, x + z - 1);
            int qq = Get_pos(1, 1, n, y + z - 1);
            if (get_hash(1, 1, n, xx, pp) == get_hash(1, 1, n, yy, qq)) cout << "YES\n";
            else cout << "NO\n";
        }
        else
        {
            cin >> x;
            int p = Get_pos(1, 1, n, x);
            xoa(p);
        }
    }
}
