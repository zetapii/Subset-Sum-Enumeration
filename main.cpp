#include <bits/stdc++.h>
using namespace std;

set< set< int > > finalSet;

int N;

vector<long long> val;

int getsum(set<int> s)
{
    int sum = 0;
    for(auto it : s) sum+=val[it];
    return sum;
}

int totcnt = 0;

void recurse(set<int> parLattice, set<int> childLattice ,  map< pair<set<int>, set<int> > , int > & visited  , int target)
{
    if(visited[{parLattice, childLattice}] == 1)
        return ;

    visited[{parLattice, childLattice}] = 1;

    totcnt++;
    //uncomment to print the current cut being visited
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

    if(getsum(childLattice) <= target)
    {
        cout<<"Error\n";
        exit(0);
    }

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
    return ;
}

//Assuming the cut exits, the function finds out one of the cuts randomly
pair< set<int> , set<int> > getCut(vector<long long> arr, int K)
{
    int N=arr.size();
    set<int> parentCut,childCut;
    int sum = 0;
    vector<int> indices(N);
    for(int i = 0; i < N; i++) indices[i] = i;
    std::random_device rd;
    std::mt19937 g(rd());

    shuffle(indices.begin(),indices.end(),g);
    for(int i = 0; i < N; i++)
    {
        sum+=arr[indices[i]];
        if(sum > K)
        {
            for(int j=0;j<i;j++) parentCut.insert(indices[j]),childCut.insert(indices[j]);
            childCut.insert(indices[i]);
            break;
        }
    }
    return {parentCut,childCut};
}

void solve()
{
    totcnt=0;
    val.clear();
    map< pair<set<int>, set<int> > , int > visited;
    //read from file tests/input.txt
    freopen("tests/input.txt", "r", stdin);
    freopen("program_output.txt", "w", stdout);
    int target;
    while(cin>>N)
    {
        finalSet.clear();
        cin>>target;
        val.resize(N);
        visited.clear();
        set<int> childCut,parentCut;
        int sum = 0;
        for(int i = 0; i < N; i++) 
        {   
            cin>>val[i];
            sum += val[i];
        }
        if(sum <= target)
        {
            cout<<(sum == target)<<endl;
        }
        else 
        {
            pair<set<int>,set<int> > ret = getCut(val,target);
            recurse(ret.first,ret.second,visited,target);
            cout<<finalSet.size()<<endl;
        }
    }
}

// #define TEST

int main()
{
    #ifdef TEST
        solve();
        exit(0);
    #endif

    N = 4;

    val = {1,3,4,6};

    map< pair<set<int>, set<int> > , int > visited;
    recurse({0,1},{0,1,2},visited,7);
    cout<<"printing size of finalSet : "<<finalSet.size()<<"\n";
    for(auto it : finalSet)
    {
        for(auto itr : it)
        {
            cout<<val[itr]<<" ";
        }
        cout<<"\n";
    }
    cout<<"total number of cuts : " <<totcnt<<"\n";
    return 0;
}