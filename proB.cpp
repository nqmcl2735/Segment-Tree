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
#define maxn 100005
#define MOD
#define Task ""
using namespace std;
ifstream fi(Task".inp");
ofstream fo(Task".out");
typedef long long ll;
typedef long double ld;
ll n, m, a[maxn];
ll ST[4 * maxn], val[maxn * 4];
ll ta, tb, tc, td;
void khoitao(ll nut, ll l, ll r)
{
    if (l == r){
        ST[nut] = a[l];
        return;
    }
    ll mid = (l + r)/2;
    khoitao(nut * 2, l, mid);
    khoitao(nut * 2 + 1, mid + 1, r);
    ST[nut] = min(ST[nut * 2], ST[nut * 2 + 1]);
}
void day(ll nut)
{
    val[nut * 2] = val[nut];
    val[nut * 2 + 1] = val[nut];
    ST[nut * 2] = val[nut];
    ST[nut * 2 + 1] = val[nut];
    val[nut] = 0;
}
void doi(ll nut, ll l, ll r, ll u, ll v, ll w)
{
    //neu khong giao
    if (u > r || v < l) return ;
    //neu chua
    if (l>=u && r <= v)
    {
        val[nut] = w;
        ST[nut] = w;
        return;
    }
    //bthg
    ll mid = (l + r) / 2;
    if (val[nut]) day(nut);
    doi(2 *nut, l, mid, u, v, w);
    doi(2 *nut + 1, mid + 1, r, u, v, w);
    ST[nut] = min(ST[nut * 2 + 1], ST[nut *2]);
}
ll gtmin(ll u, ll v, ll l, ll r, ll nut)
{
    // dacbiet1
    if (u > r || v < l) return oo;
    //dacbiet2
    if (l>=u && r <= v) return ST[nut];
    //binhthuong
    ll mid = (l + r) / 2;
    if (val[nut]) day(nut);
    ll minL = gtmin(u, v, l, mid, nut * 2);
    ll minR = gtmin(u, v, mid + 1, r, nut * 2 + 1);
    return min(minL, minR);

}
int main() {
    ios_base::sync_with_stdio(0); cin.tie(); cout.tie();
    cin >> n >> m;
    for (int i = 1; i <= n; i ++)
        cin >> a[i];
    khoitao(1, 1, n);
    while (m --)
    {
        cin >> ta ;
        if (ta == 1)
        {
            cin >> tb >> tc >> td;
            doi(1, 1, n, tb, tc, td);
        }
        else
        {
            cin >> tb >> tc;
            cout << gtmin(tb, tc, 1, n, 1) << "\n";
        }
    }
    return 0;
}
