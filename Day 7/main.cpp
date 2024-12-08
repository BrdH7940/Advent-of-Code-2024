#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

void readFile(const string& filename, vector<unsigned long long>& targets, vector<vector<unsigned long long>>& nums){
    fstream file(filename);
    if(!file.is_open()){
        cout << "Error!"; return;
    }

    string line;
    string target, tmp; vector<unsigned long long> num;
    while(getline(file, line)){
        istringstream ss(line);

        getline(ss, target, ':');
        targets.push_back(stoull(target));

        while(ss >> tmp){
            num.push_back(stoi(tmp));
        }

        nums.push_back(num);
        num.clear();
    }
}

unsigned long long concat(unsigned long long n1, unsigned long long n2){
    return stoull(to_string(n1) + to_string(n2));
}

bool backtrack1(unsigned long long target, vector<unsigned long long> nums){
    if(nums.size() == 1)
        return target == nums[0];

    vector<unsigned long long> vec1 = {nums[0] + nums[1]};
    vector<unsigned long long> vec2 = {nums[0] * nums[1]};
    vec1.insert(vec1.end(), nums.begin() + 2, nums.end());
    vec2.insert(vec2.end(), nums.begin() + 2, nums.end());

    return backtrack1(target, vec1) || backtrack1(target, vec2);
}

bool backtrack2(unsigned long long target, vector<unsigned long long> nums){
    if(nums.size() == 1)
        return target == nums[0];

    vector<unsigned long long> vec1 = {nums[0] + nums[1]};
    vector<unsigned long long> vec2 = {nums[0] * nums[1]};
    vector<unsigned long long> vec3 = {concat(nums[0], nums[1])};
    vec1.insert(vec1.end(), nums.begin() + 2, nums.end());
    vec2.insert(vec2.end(), nums.begin() + 2, nums.end());
    vec3.insert(vec3.end(), nums.begin() + 2, nums.end());

    return backtrack2(target, vec1) || backtrack2(target, vec2) || backtrack2(target, vec3);
}

unsigned long long totalCalibration1(vector<unsigned long long>& targets, vector<vector<unsigned long long>>& nums){
    unsigned long long res = 0;

    for(unsigned long long i = 0; i < targets.size(); i++){
        if(backtrack1(targets[i], nums[i]))
            res += targets[i];
    }

    return res;
}

unsigned long long totalCalibration2(vector<unsigned long long>& targets, vector<vector<unsigned long long>>& nums){
    unsigned long long res = 0;

    for(unsigned long long i = 0; i < targets.size(); i++){
        if(backtrack2(targets[i], nums[i]))
            res += targets[i];
    }

    return res;
}

int main(){
    vector<unsigned long long> targets;
    vector<vector<unsigned long long>> nums;

    readFile("input.txt", targets, nums);

    cout << totalCalibration1(targets, nums) << endl;
    cout << totalCalibration2(targets, nums) << endl;
    
    return 0;
}