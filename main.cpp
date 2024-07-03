#include <bits/stdc++.h>
using namespace std;

// map< pair<set<int>, set<int> > , int > visited;

set< set< int > > finalSet;

int N = 4 ;

long long ans;

vector<long long> val;

int getsum(set<int> s)
{
    int sum = 0;
    for(auto it : s) sum+=val[it];
    return sum;
}

void recurse(set<int> parLattice, set<int> childLattice ,  map< pair<set<int>, set<int> > , int > visited  , int target)
{
    if(visited[{parLattice,childLattice}] == 1)
        return ;

    visited[{parLattice,childLattice}] = 1;

    if(getsum(parLattice) == target) finalSet.insert(parLattice);

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
                if(itrr == itr) continue;
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
                        recurse(temp, temp2 ,visited,target);        
                    }
                }
            }
        }
    }
}

int main()
{
    val.push_back(1);
    val.push_back(3);
    val.push_back(4);
    val.push_back(6);
    recurse({3},{2,3},{},7);
    cout<<"printing size of finalSet : "<<finalSet.size()<<"\n";
    for(auto it : finalSet)
    {
        for(auto itr : it)
        {
            cout<<val[itr]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}