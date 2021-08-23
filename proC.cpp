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
int n;
int m;
int z;
int u, v, w;
int add[4 * maxn];
int ST[4 * maxn];
int id[maxn];
void day(int nut)
{
    add[nut * 2] += add[nut];
    add[nut * 2 + 1] += add[nut];
    ST[nut * 2] += add[nut];
    ST[nut * 2 + 1] += add[nut];
    add[nut] = 0;
}
void doi(int nut, int l, int r, int u, int v, int w)
{
    //neu khong giao
    if (u > r || v < l) return ;
    //neu chua
    if (l>=u && r <= v)
    {
        add[nut] += w;
        ST[nut] += w;
        return;
    }
    //bthg
    int mid = (l + r) / 2;
    day(nut);
    doi(2 *nut, l, mid, u, v, w);
    doi(2 *nut + 1, mid + 1, r, u, v, w);
    ST[nut] = max(ST[nut * 2 + 1], ST[nut *2]) + add[nut];
}
ll gtmax(int u, int v, int l, int r, int nut)
{
    // dacbiet1
    if (u > r || v < l) return 0;
    //dacbiet2
    if (l>=u && r <= v) return ST[nut];
    //binhthuong
    int mid = (l + r) / 2;
    ll maxL=gtmax(u, v, l, mid, nut * 2);
    ll maxR=gtmax(u, v, mid + 1, r, nut * 2 + 1);
    return max(maxL, maxR) + add[nut];

}
int main() {
    ios_base::sync_with_stdio(0); cin.tie(); cout.tie();
    cin >> n >> m >> z;
    while (z --)
    {
        cin >> u >> v >> w;
        doi(1, 1, n, u, v - 1 , w);
        if (gtmax(u, v, 1, n, 1) > m) {
            cout << "N" << "\n";
            doi (1, 1, n, u, v -1, -1*w);
        }
        else
            cout <<"T" << "\n";
    }
}
