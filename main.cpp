#include <iostream>
#include <vector>
#include <math.h>
#define ll long long
using namespace std;
const int lim = 1e6;
int lp[lim + 2],pr[lim],cnt = 0;
int prime[8] = {2,3,5,7,11,13,17,19};
ll _gcd(ll x,ll y){
    if (y == 0) return x;
    return _gcd(y , x % y);
}
pair <ll,ll> factor(ll x){
    ll s = 0;
    while (!(x & 1)){
        s++;
        x >>= 1;
    }
    return make_pair(s,x);
}
ll mul(ll x,ll y,ll mod){
    ll res = 0;
    x = x % mod;
    while (y > 0){
        if (y & 1) res = (res + x) % mod;
        y >>= 1;
        x = (x + x) % mod;
    }
    return res;
}
ll power(ll x,ll y,ll mod){
    ll res = 1;
    x = x % mod;
    while (y > 0){
        if (y & 1) res = mul(res,x,mod);
        y >>= 1;
        x = mul(x,x,mod);
    }
    return res;
}
bool Test(ll s,ll d,ll n,ll a){
    if (n == a) return true;
    ll p = power(a,d,n);
    if (p == 1) return true;
    for (; s > 0; s--){
        if (p == n - 1) return true;
        p = mul(p,p,n);
    }
    return false;
}
bool Miller(ll n){
    if (n < 2) return false;
    if (!(n & 1)) return n == 2;

    pair <ll,ll> tmp = factor(n - 1);
    bool check = true;
    for (int i = 0; i < 8; i++)
        check = check & Test(tmp.first,tmp.second,n,prime[i]);

    return check;
}
bool FakePrime(ll n){
    if (n < 2) return false;
    if (!(n & 1)) return n == 2;

    int Test_Prime = 50;

    while (Test_Prime--){
        ll a = rand() % (n - 1) + 1;
        if (_gcd(a,n) > 1) return false;
        if (power(a,n - 1,n) != 1) return false;
    }
    return true;
}
bool Square(ll x){
    ll p = sqrt(x);
    if (p * p == x) return true;
    return false;
}
bool Cube(ll x){
    ll p = round(pow(x,1.0/3));
    if (p * p * p == x) return true;
    return false;
}
void Sieve(){
    for (int i = 2; i <= lim; i++){
        if (lp[i] == 0) lp[i] = pr[++cnt] = i;
        int j = 1;
        while (j <= cnt && pr[j] <= lp[i] && i * pr[j] <= lim){
            lp[pr[j] * i] = pr[j];
            j++;
        }
    }
}
ll CubeRoot(ll x){
    Sieve();
    vector <pair<ll,int>> Titan;
    for (int i = 1; i <= cnt; i++){

        if (1LL * pr[i] * pr[i] * pr[i] > x) break;

        int d = 0;

        while (x % pr[i] == 0){
            d++;
            x /= pr[i];
        }

        if (d > 0) Titan.push_back(make_pair(pr[i],d));

    }

    ll sum = 1 , u = (int)Titan.size();

    for (auto p : Titan) sum = sum * (p.second + 1);

    if (Miller(x)) sum = sum * 2 , u++;
    else

    if (Square(x) && Miller((ll)sqrt(x))) sum = sum * 3 , u++;
    else

    if (x != 1){
        sum = sum * 4;
        u = u + (Cube(x) ? 1 : 2);
    }

    return sum - u;
}
ll SquareRoot(ll x){
    vector <pair<ll,int>> V;
    for (ll i = 2; i * i <= x; i++){
        int d = 0;
        while (x % i == 0){
            d++;
            x /= i;
        }
        if (d != 0) V.push_back(make_pair(i,d));
    }

    if (x > 1) V.push_back(make_pair(x,1));

    ll sum = 1;

    for (auto x : V) sum = sum * (x.second + 1);

    return sum - (int)V.size();
}
ll n;
int main()
{
    cin >> n;
    cout << SquareRoot(n) << " ? " << CubeRoot(n);
    return 0;
}
