#include <bits/stdc++.h>
using namespace std;

// map< pair<set<int>, set<int> > , int > visited;

set< set< int > > finalSet;

int N = 6 ;

long long ans;

vector<long long> val;

int getsum(set<int> s)
{
    int sum = 0;
    for(auto it : s) sum+=val[it];
    return sum;
}

int totcnt = 0;

void recurse(set<int> parLattice, set<int> childLattice ,  map< pair<set<int>, set<int> > , int >& visited  , int target)
{
    if(visited[{parLattice, childLattice}] == 1)
        return ;

    visited[{parLattice, childLattice}] = 1;

    totcnt++;
    //print the current set being visited
   /* cout<<"Printing parent lattice : ";
    for(auto it : parLattice)
    {
        cout<<val[it]<<" ";
    }
    cout<<"\n";
    
    cout<<"Printing child lattice : ";
    for(auto it : childLattice)
    {
        cout<<val[it]<<" ";
    }
    cout<<"\n";
    cout<<"-----\n";*/
    if(getsum(parLattice) == target) finalSet.insert(parLattice);
    if(getsum(childLattice) <= target) cout<<"Error\n";
    //Let Y1,Y2,Y3.......Y_C be the parents of C
    for(auto itr: childLattice)
    {
        set<int> curParLattice = childLattice;
        curParLattice.erase(itr);

        //now Y_i = curParLattice
        if(getsum(curParLattice) > target) //if Y_i is infrequent
        {
            //If one frequent parent PY_i of Y_i exists
            for(auto itrr: curParLattice)
            {
                set<int> temp = curParLattice;
                temp.erase(itrr);
                if(getsum(temp) <= target) 
                {
                    recurse(temp,curParLattice,visited,target);
                    break;
                }
            }
        }
        else  //If Y_i is frequent
        {
            if(getsum(curParLattice) == target) finalSet.insert(curParLattice);

            for(int itrr=0;itrr<N; itrr++)
            {
                // if(itrr == itr) continue;
                if(curParLattice.find(itrr) == curParLattice.end())
                {
                    set<int> temp = curParLattice;
                    temp.insert(itrr);
                    if(getsum(temp) > target) //if CYi is infrequent
                        recurse(curParLattice,temp,visited,target);
                    else 
                    {
                        //itrr  and itr , add both and we will get the common child
                        set<int> temp2 = childLattice;
                        temp2.insert(itr);
                        temp2.insert(itrr);
                        // cout<<"got here eee\n";
                        // for(auto i: temp2)
                        // {
                        //     cout<<val[i]<<" ";
                        // }
                        // cout<<endl;
                        // for(auto i: temp)
                        // {
                        //     cout<<val[i]<<" ";
                        // }
                        // cout<<endl<<"----\n";
                        recurse(temp, temp2 ,visited,target);        
                    }
                }
            }
        }
    }
}


void test()
{
    int iteration = 1;
    for(int i=0;i<iteration;i++)
    {
        //randomly initialise the array
        ans = 0;
        finalSet.clear();
        val.clear();
        N=5;
        srand(time(nullptr));
        for(int i=0;i<N;i++)
            val.push_back(rand()%10 + 1);
        int K=val[0]+val[1];
        map< pair<set<int>, set<int> > , int > visited;
        int idx=-1;
        for(int i=0;i<N;i++)
        {
            if(val[i]>K) idx = i;
        }
        if(idx == -1) continue;
        recurse({},{i},visited,K);
        int ans = 0;
        for(int i=0;i<(1<<N);i++)
        {
            int sum = 0;
            for(int j=0;j<N;j++)
            {
                if(i&(1<<j)) sum+=val[j];
            }
            if(sum == K) ans++;
        }
        assert(finalSet.size() == ans);
        cout<<"test passed";
    }
}
int main()
{
    // test();
    // return 0;
    val.push_back(1);
    val.push_back(1);
    val.push_back(1);
    val.push_back(1);
    val.push_back(1);
    val.push_back(1);

    map< pair<set<int>, set<int> > , int > visited;
    recurse({2,4},{2,4,5},visited,2);
    cout<<"printing size of finalSet : "<<finalSet.size()<<"\n";
    // for(auto it : finalSet)
    // {
    //     for(auto itr : it)
    //     {
    //         cout<<val[itr]<<" ";
    //     }
    //     cout<<"\n";
    // }
    // cout<<totcnt<<"\n";
    return 0;
}