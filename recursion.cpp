#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int cnt = 0;

void generateSubsetsUp(vector<int>& nums, int target, vector<vector<int>>& result, vector<int>& current, int index, int currentSum) {
    if (currentSum == target) {
        result.push_back(current);
        return;
    }

    if (index >= nums.size() || currentSum > target) {
        return;
    }

    cnt++;

    // Include the current number
    current.push_back(index);

    generateSubsetsUp(nums, target, result, current, index + 1, currentSum + nums[index]);

    current.pop_back();
    
    // Ignore the current number
    generateSubsetsUp(nums, target, result, current, index + 1, currentSum);

    return ;
}

vector<vector<int>> subsetSum(vector<int>& nums, int target) {
    vector<vector<int>> result;
    vector<int> current;
    sort(nums.begin(), nums.end());
    generateSubsetsUp(nums, target, result, current, 0, 0);
    return result;
}


void test(const char* filename = "tests/input.txt")
{
    freopen(filename, "r", stdin);
    freopen("program_output.txt", "w", stdout);

    int N,target;
    while(cin>>N)
    {
        vector<int> nums;   
        cin>>target;
        for(int i=0;i<N;i++)
        {
            int x;
            cin>>x;
            nums.push_back(x);
        }
        vector<vector<int>> subsets = subsetSum(nums, target);
        cout<<subsets.size()<<endl;
    }
    return ;
}

// #define BENCHMARK
#define TEST

int main() {


    #ifdef TEST
        test();
        exit(0);
    #endif


    #ifdef BENCHMARK

        freopen("test_case.txt", "r", stdin);
        freopen("program_output.txt", "w", stdout);

        int N,target;
        while(cin>>N)
        {
            vector<int> nums;   
            cin>>target;
            for(int i=0;i<N;i++)
            {
                int x;
                cin>>x;
                nums.push_back(x);
            }
            auto start = chrono::high_resolution_clock::now();

            vector<vector<int>> subsets = subsetSum(nums, target);

            auto end = chrono::high_resolution_clock::now();

            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

            cout << "Number of subsets with sum " << target << ": " << subsets.size() << endl;
            cout << "Time taken: " << duration.count() << " microseconds" << endl;
            cout << "Number of recursion "<<cnt<<endl;
            cout << "--------------------------------------------------------------------------" << endl;
        }
    #endif 

    return 0;
}
