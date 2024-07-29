#include <bits/stdc++.h>
#include <stdexcept>
using namespace std;

class ImplementationError: public exception 
{ 
  virtual const char* what() const throw() 
  { 
    return "Identified cut not satisfying definition"; 
  } 
}; 


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
int mxQueueSize = 1;
int alreadyVisited = 0;

void bfsExpandCut(set<int> parLattice, set<int> childLattice, map< set<int> , int> & visited, int target) {
    map< set<int> , int > explored_1;
    map< set<int> , int > explored_2;

    queue<pair<set<int>, set<int>> > q;
    q.push({parLattice, childLattice});
    visited[childLattice] = 1;
    totcnt=1;
    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        
        set<int> curParLattice = current.first;
        set<int> curChildLattice = current.second;
        
        
        if (getsum(curParLattice) == target) finalSet.insert(curParLattice);
        
        if (getsum(curChildLattice) <= target) {
            throw ImplementationError();
            exit(0);
        }
        
        for (auto itr : curChildLattice) {
            set<int> nextParLattice = curChildLattice;
            nextParLattice.erase(itr);
            
            //Let Y_1 , Y_2 , ..... Y_C be the parents of C
            if (getsum(nextParLattice) > target) {  //if Y_i is infrequent
                if(explored_2[nextParLattice] == 1) continue;
                explored_2[nextParLattice] = 1;
                for (auto itrr : nextParLattice) {   
                    set<int> temp = nextParLattice;
                    temp.erase(itrr);
                    if (getsum(temp) <= target ) {
                       if(visited[nextParLattice]==0) //if one frequent parent exists
                       {
                            visited[nextParLattice]=1;
                            q.push({temp, nextParLattice});
                            totcnt++;
                            break; 
                       }
                       else 
                       {
                            alreadyVisited++;
                       }
                    }
                }
            } else {    //If Y_i is frequent
                if (getsum(nextParLattice) == target) finalSet.insert(nextParLattice);
                if (explored_1[nextParLattice] == 1) continue; //condition to avoid visiting duplicate cuts
                explored_1[nextParLattice] = 1;
                for (int itrr = 0; itrr < N; itrr++) {
                    if (nextParLattice.find(itrr) == nextParLattice.end()) {
                        set<int> temp = nextParLattice;
                        temp.insert(itrr);      //for each child C_Y_i of Y_i
                        if (getsum(temp) > target ) { //if C_Y_i is infrequent
                            if(visited[temp]==0)
                            {
                                q.push({nextParLattice, temp});
                                visited[temp]=1;
                                totcnt++;
                            }
                            else 
                            {
                                alreadyVisited++;
                            }
                        } else {   //if C_Y_is is frequent
                            set<int> temp2 = curChildLattice;
                            temp2.insert(itr);
                            temp2.insert(itrr);
                            if(visited[temp2]==0)
                            {
                                q.push({temp, temp2});
                                visited[temp2]=1;
                                totcnt++;
                            }
                            else 
                            {
                                alreadyVisited++;
                            }
                        }
                    }
                }
            }
        }
        mxQueueSize = max(mxQueueSize , (int)q.size());
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
        clock_t start, end;
        start = clock();
        const char* filename = "test_case.txt";
        solve(filename);
        end = clock();
        double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        cout << "Time taken by program is : " << fixed << time_taken << setprecision(5);
        cout << "Total Number of cuts : " << totcnt << endl;
        cout << "Maximum Size of Queue at any instant " << mxQueueSize << endl;
        cout << "Number of Cuts Visited which were already explored  " << alreadyVisited << endl;
        cout<<endl;
        exit(0);
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