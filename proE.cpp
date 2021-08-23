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
#define Task ""
using namespace std;
ifstream fi(Task".inp");
ofstream fo(Task".out");
typedef long long ll;
typedef long double ld;
int n;
int a[maxn];
int STmin[4 * maxn];
int STmax[4 * maxn];
int pos[maxn];
int m, t, x, y;
void khoitao(int nut, int l, int r)
{
    if (l == r){
        STmin[nut] = pos[l];
        STmax[nut] = pos[l];
        return;
    }
    int mid = (l + r)/2;
    khoitao(nut * 2, l, mid);
    khoitao(nut * 2 + 1, mid + 1, r);
    STmin[nut] = min(STmin[nut * 2], STmin[nut * 2 + 1]);
    STmax[nut] = max(STmax[nut * 2], STmax[nut * 2 + 1]);
}
void Change(int nut, int l, int r, int val){
    if(l == r){
        STmin[nut] = STmax[nut] = pos[r];
        return;
    }
    int mid = (l + r)/2;
    if(val <= mid) Change(nut * 2, l, mid, val);
    else Change(nut * 2 +  1, mid + 1, r, val);
    STmin[nut] = min(STmin[nut * 2], STmin[nut * 2 + 1]);
    STmax[nut] = max(STmax[nut * 2], STmax[nut * 2 + 1]);
}
int gtmin(int u, int v, int l, int r, int nut)
{
    // dacbiet1
    if (u > r || v < l) return oo;
    //dacbiet2
    if (l>=u && r <= v) return STmin[nut];
    //binhthuong
    int mid = (l + r) / 2;
    int minL=gtmin(u, v, l, mid, nut * 2);
    int minR=gtmin(u, v, mid + 1, r, nut * 2 + 1);
    return min(minL, minR);

}
int gtmax(int u, int v, int l, int r, int nut)
{
    // dacbiet1
    if (u > r || v < l) return -oo;
    //dacbiet2
    if (l>=u && r <= v) return STmax[nut];
    //binhthuong
    int mid = (l + r) / 2;
    int maxL=gtmax(u, v, l, mid, nut * 2);
    int maxR=gtmax(u, v, mid + 1, r, nut * 2 + 1);
    return max(maxL, maxR);
}
bool check(int x, int y)
{
    return (y - x == gtmax(x, y, 1, n ,1) - gtmin(x, y, 1, n ,1));
}
int main() {
    ios_base::sync_with_stdio(0); cin.tie(); cout.tie();
        cin >> n >> m;
    for (int i = 1; i <= n; i ++)
    {
        cin >> a[i];
        pos[a[i]] = i;
    }
    khoitao(1, 1, n);
    while (m --)
    {
        cin >> t >> x >> y;
        if (t == 1)
        {
            swap(a[x], a[y]);
            pos[a[x]] = x;
            pos[a[y]] = y;
            Change(1, 1, n, a[x]);
            Change(1, 1, n, a[y]);
        }
        else if (check(x, y)) cout << "YES\n";
            else cout << "NO\n";
    }
}
