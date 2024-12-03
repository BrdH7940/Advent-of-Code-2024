#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

void readFile(const string& filename, vector<vector<int>>& nums){
    fstream file(filename);

    if(!file.is_open()){
        cout << "Error!";
        return;
    }

    string line;
    vector<int> num;
    int tmp;
    
    while(getline(file, line)){
        istringstream ss(line);

        while(ss >> tmp){
            num.push_back(tmp);
        }

        nums.push_back(num);

        num.clear();
    }
}

bool isSafe1(vector<int>& nums){
    int n = nums.size(), sign = nums[1] - nums[0];

    for(int i = 0; i < n - 1; i++){
        int d = nums[i + 1] - nums[i];

        if(abs(d) > 3 || abs(d) < 1 || sign * d <= 0)
            return false;
    }

    return true;
}

bool isSafe2(vector<int>& nums){
    int n = nums.size(), sign = nums[1] - nums[0];

    if(isSafe1(nums))
        return true;

    for(int i = 0; i < n; i++){
        vector<int> tmp = nums;

        tmp.erase(tmp.begin() + i);

        if(isSafe1(tmp))
            return true;
    }

    return false;
}

int main(){
    vector<vector<int>> nums;

    readFile("input.txt", nums);

    int n = nums.size(), count = 0;

    for(int i = 0; i < n; i++){
        if(isSafe2(nums[i]))
            ++count;
    }

    cout << count;

    return 0;
}