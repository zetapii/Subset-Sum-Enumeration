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

void bfsExpandCut(set<int> parLattice, set<int> childLattice, map< set<int> , int> & visited, int target) {
    queue<pair<set<int>, set<int>>> q;
    q.push({parLattice, childLattice});
    
    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        
        set<int> curParLattice = current.first;
        set<int> curChildLattice = current.second;
        
        if(visited[curChildLattice]==1) continue;

        visited[curChildLattice]=1;
        
        totcnt++;
        
        if (getsum(curParLattice) == target) finalSet.insert(curParLattice);
        
        if (getsum(curChildLattice) <= target) {
            cout<< "Error\n";
            exit(0);
        }
        
        for (auto itr : curChildLattice) {
            set<int> nextParLattice = curChildLattice;
            nextParLattice.erase(itr);
            
            if (getsum(nextParLattice) > target) {
                for (auto itrr : nextParLattice) {
                    set<int> temp = nextParLattice;
                    temp.erase(itrr);
                    if (getsum(temp) <= target) {
                        q.push({temp, nextParLattice});
                        break;
                    }
                }
            } else {
                if (getsum(nextParLattice) == target) finalSet.insert(nextParLattice);
                
                for (int itrr = 0; itrr < N; itrr++) {
                    if (nextParLattice.find(itrr) == nextParLattice.end()) {
                        set<int> temp = nextParLattice;
                        temp.insert(itrr);
                        if (getsum(temp) > target) {
                            q.push({nextParLattice, temp});
                        } else {
                            set<int> temp2 = curChildLattice;
                            temp2.insert(itr);
                            temp2.insert(itrr);
                            q.push({temp, temp2});
                        }
                    }
                }
            }
        }
    }
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

void solve(const char* filename = "tests/input.txt")
{
    totcnt=0;
    val.clear();
    map< set<int> , int > visited;
    
    //read from file tests/input.txt
    freopen(filename, "r", stdin);
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
            // expandCut(ret.first,ret.second,visited,target);
            bfsExpandCut(ret.first, ret.second, visited, target);
            cout<<finalSet.size()<<endl;
        }
    }
}

#define TEST

// #define BENCHMARK

int main()
{
    #ifdef TEST
        solve();
        exit(0);
    #endif

    #ifdef BENCHMARK
        //measure time
        clock_t start, end;
        start = clock();
        const char* filename = "test_case.txt";
        solve(filename);
        end = clock();
        double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        cout << "Time taken by program is : " << fixed << time_taken << setprecision(5);
    #endif

    N = 4;

    val = {1,3,4,6};

    map< set<int> , int > visited;
    // expandCut({0,1},{0,1,2},visited,7);
    bfsExpandCut({0,1},{0,1,2},visited,7);
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