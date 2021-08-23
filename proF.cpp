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
#define maxn 100005
#define MOD
#define Task ""
using namespace std;
ifstream fi(Task".inp");
ofstream fo(Task".out");
typedef long long ll;
typedef long double ld;
int n, k;
int a[maxn];
int ST[4 * maxn];
int id[maxn];
void khoitao(int nut, int l, int r)
{
    if (l == r){
        id[r] = nut;
        return;
    }
    int mid = (l + r)/2;
    khoitao(nut * 2, l, mid);
    khoitao(nut * 2 + 1, mid + 1, r);
}
void doi(int x, int y)
{
    int nut = id[x];
    ST[nut] = y;
    while (nut > 1)
    {
        nut /= 2;
        ST[nut] = max(ST[nut * 2], ST[nut * 2 + 1]);
    }
}
int gtmax(int u, int v, int l, int r, int nut)
{
    // dacbiet1
    if (u > r || v < l) return -oo;
    //dacbiet2
    if (l >= u && r <= v) return ST[nut];
    //binhthuong
    int mid = (l + r) / 2;
    int maxL = gtmax(u, v, l, mid, nut * 2);
    int maxR = gtmax(u, v, mid + 1, r, nut * 2 + 1);
    return max(maxL, maxR);
}
int main() {
    ios_base::sync_with_stdio(0); cin.tie(); cout.tie();
    cin >> n >> k;
    vi v, x;
    for (int i = 1; i <= n; i ++)
        cin >> a[i];
    khoitao(1, 1, n);
    v.assign(a + 1, a + n + 1);
    x.assign(a + 1, a + n + 1);
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    int res = 0;
    for (int i : x)
    {
        int p = upper_bound(v.begin(), v.end(), i - k) - v.begin();
        int q = lower_bound(v.begin(), v.end(), i + k) - v.begin() + 1;
        int val = max(gtmax(1, p, 1, n, 1), gtmax(q, n, 1, n, 1)) + 1;
        res = max(res, val);
        int pos = lower_bound(v.begin(), v.end(), i) - v.begin() + 1;
        doi(pos, val);
    }
    cout << res;
}
