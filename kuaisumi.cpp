#include <iostream>
using namespace std;
typedef long long ll;
ll binpow(ll a, ll b){  //a是底数，b是指数
    ll res = 1;
    while(b > 0){
        if(b & 1) res *= a;
        a *= a;
        b >>= 1;    //相当于b除以2
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    ll a, b;
    cin >> a >> b;
    cout << binpow(a, b) << endl;
    return 0;
}
