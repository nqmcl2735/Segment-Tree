//ngqminh.cl2735
#include <bits/stdc++.h>
#define PB push_back
#define pii pair <int,int>
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
#define MOD
#define Task "proG"
using namespace std;
ifstream fi(Task".inp");
ofstream fo(Task".out");
typedef long long ll;
typedef long double ld;
int val[maxnd * 8];
int ST[maxn * 8];
vi v;
int n, m;
int a[maxn];
struct data{
    int y, l, r, t;
};
vector <data> doc;
bool cmp(data a, data b)
{
    return a.y < b.y;
}
void day(int nut, int l, int r)
{
    if (val[nut]) ST[nut] = a[r] - a[l] + 1;
    else if (l == r) ST[nut] = 0;
    else ST[nut] = ST[nut * 2] + ST[nut * 2 + 1];
}
void update(int nut, int l, int r, int u, int v, int w)
{
    if (u > r || v < l) return ;
    if (l >= u && v >= r)
    {
        val[nut] += w;
        day(nut, l, r);
        return;
    }
    int mid = (l + r)/2;
    update(nut * 2, l, mid, u, v, w);
    update(nut * 2 + 1, mid + 1, r, u, v, w);
    day(nut, l, r);
}
int main() {
    ios_base::sync_with_stdio(0); cin.tie(); cout.tie();
    fi >> n;
    for (int i = 1; i <= n; i ++)
    {
        int x1, x2, y1, y2;
        fi >> x1 >> x2 >> y1 >> y2;
        doc.PB({y1, x1, x2, 1});
        doc.PB({y2, x1, x2, -1});
        v.PB(x1);
        v.PB(x2);
    }
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    m = sz(v);
    for (int i = 1; i <= m; i ++) a[i] = v[i - 1];
    sort(doc.begin(), doc.end(), cmp);
    ll res = 0;
    for (int i = 0; i < sz(doc) - 1; i ++)
    {
        int l = lower_bound(a + 1, a + n + 1, doc[i].l) - a;
        int r = lower_bound(a + 1, a + n + 1, doc[i].r) - a;
        update(1, 1, m, l, r, doc[i].t);
        res += (1ll * ST[1] * (doc[i + 1].y - doc[i].y));
    }
    fo << res;
}
