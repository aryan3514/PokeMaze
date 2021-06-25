#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define  in(ar,n) for(int i=0;i<(int)n;i++)cin>>ar[i];
#define out(ar,n)     for(int i=0;i<(int)n;i++)     cout<<ar[i]<<" ";     cout<<endl;
#define for2d(n,m) for(int i=0;i<(int)n;i++)for(int j=0;j<(int)m;j++)
#define fori(i,a,b) for(ll i=a;i<(int)b;++i)
#define all(ar) ar.begin(),ar.end()
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define disp(x) cout << #x << " = " << x << endl;
#define um unordered_map
#define INF 1000000000
using namespace std;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
using namespace std;
// const ll mod = 1e9 + 7;

bool sortbysec(const pair<int,int> &a,
              const pair<int,int> &b)
{   
    if (a.second == b.second){
        return a.first < b.first;
    }
    return (a.second > b.second);
}

 
int main(){
 
    ll t;
    cin>>t;

    while(t--){
        ll n;
        cin>>n;

        ll ar[n];

        in(ar,n);

        vector<pll> vec;

        fori(i,0,n){
            vec.push_back(pll (ar[i],i+1));
        }

        sort(all(vec));
        ll ans = 0;
        fori(i,0,n){
            fori(j,i+1,n){

                //cout<<(vec[i].first)*(vec[j].first)<<" ";
                //cout<<vec[i].second + vec[j].second<<endl;

                if (vec[i].first*vec[j].first>=2*n){
                    break;
                }else if ((vec[i].first)*(vec[j].first) == vec[i].second + vec[j].second){
                    ans++;
                }
            }

        }
        
        cout<<ans<<endl;
    }

    
    



    
}