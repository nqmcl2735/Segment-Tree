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
int n, t;
int ta, tb, tc, x;
int a[maxn];
int ST[maxn * 4];
int id[maxn];
void khoitao(int nut, int l, int r)
{
    if (l == r){
        ST[nut] = a[l];
        id[r] = nut;
        return;
    }
    int mid = (l + r)/2;
    khoitao(nut * 2, l, mid);
    khoitao(nut * 2 + 1, mid + 1, r);
    ST[nut] = min(ST[nut * 2], ST[nut * 2 + 1]);
}
void doi(int x, int y)
{
    int nut = id[x];
    a[x] = y;
    ST[nut] = y;
    while (nut > 1)
    {
        nut /= 2;
        ST[nut] = min(ST[nut * 2], ST[nut * 2 + 1]);
    }
}
int gtmin(int u, int v, int l, int r, int nut)
{
    // dacbiet1
    if (u > r || v < l) return oo;
    //dacbiet2
    if (l>=u && r <= v) return ST[nut];
    //binhthuong
    int mid = (l + r) / 2;
    int minL=gtmin(u, v, l, mid, nut * 2);
    int minR=gtmin(u, v, mid + 1, r, nut * 2 + 1);
    return min(minL, minR);

}
int main() {
    ios_base::sync_with_stdio(0); cin.tie(); cout.tie();
    cin >> n >> t;
    for (int i = 1; i <= n; i ++) {
        //fi >> x;
        //doi(i, x);
        cin >> a[i];
    }
    khoitao(1,1,n);
    while (t --)
    {
        cin >> ta >> tb >> tc;
        if (ta == 1) doi(tb, tc);
        else cout << gtmin(tb, tc, 1, n, 1) << "\n";
    }
}
