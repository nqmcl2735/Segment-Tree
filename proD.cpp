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
#define maxn 100005
#define MOD 1000000007
#define Task ""
using namespace std;
ifstream fi(Task".inp");
ofstream fo(Task".out");
typedef long long ll;
typedef long double ld;
int n, m;
char ta;
int tb, tc, td;
ll a[maxn];
pii ST[maxn * 4];
ll id[maxn];
void khoitao(int nut, int l, int r)
{
    ST[nut] = {1, 0};
    if (l == r){
        id[r] = nut;
        return;
    }
    int mid = (l + r)/2;
    khoitao(nut * 2, l, mid);
    khoitao(nut * 2 + 1, mid + 1, r);
}
void day(int nut){
    ST[nut * 2].F = (ST[nut * 2].F * ST[nut].F) % MOD;
    ST[nut * 2].S = (ST[nut * 2].S * ST[nut].F + ST[nut].S) % MOD;
    ST[nut * 2 + 1].F = (ST[nut * 2 + 1].F * ST[nut].F) % MOD;
    ST[nut * 2 + 1].S = (ST[nut * 2 + 1].S * ST[nut].F + ST[nut].S) % MOD;
    ST[nut] = {1, 0};
}
void doi(int nut, int l, int r, int u, int v, int a, int b)
{
    //neu khong giao
    if (u > r || v < l) return ;
    //neu chua
    if (l >= u && r <= v)
    {
        if (a == 1) ST[nut].S = (ST[nut].S + b) % MOD;
        else
        {
                int x = (1ll * ST[nut].F * a) % MOD;
                int y = (1ll * ST[nut].S * a) % MOD;
                ST[nut] = {x, y};
        }
        return;
    }
    //bthg
    int mid = (l + r) / 2;
    day(nut);
    doi(2 *nut, l, mid, u, v, a, b);
    doi(2 *nut + 1, mid + 1, r, u, v, a, b);
}
ll fid(int pos)
{
    int nut = id[pos];
    ll res = a[pos];
    while (nut > 0)
    {
        res = (res * ST[nut].F + ST[nut].S) % MOD;
        nut /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(); cout.tie();
    cin >> n;
    for (int i = 1; i <= n; i ++)
        cin >> a[i];
    khoitao(1, 1, n);
    cin >> m;
    while (m --)
    {
        cin >> ta;
        if (ta == '?') {
            cin >> tb;
            cout << fid(tb) << "\n";
        }
        else {
            cin >> tb >> tc >> td;
            if(ta == '+') doi(1, 1, n, tb, tc, 1, td);
            else doi(1, 1, n, tb, tc, td, 0);
        }
    }
}
