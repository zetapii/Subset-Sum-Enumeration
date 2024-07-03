#include <bits/stdc++.h>
using namespace std;

void solveTests()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int N,target;
    while(cin>>N)
    {
        cin>>target;
        vector<long long> val(N);
        for(int i = 0; i < N; i++) cin>>val[i];
        int ans = 0;
        for(int i = 0; i < (1<<N); i++)
        {
            long long sum = 0;
            for(int j = 0; j < N; j++)
            {
                if(i&(1<<j)) sum+=val[j];
            }
            ans += (sum==target);
        }
        cout<<ans<<endl;
    }
    return ;
}
int main()
{
    solveTests();
}