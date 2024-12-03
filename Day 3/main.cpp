#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <regex>
using namespace std;

void readFile(const string& filename, string& s){
    fstream file(filename);

    if(!file.is_open()){
        cout << "Error!";
        return;
    }

    string line;
    vector<int> num;
    int tmp;
    
    while(getline(file, line)){
        s += line;
    }
}

void mul1(const string& s){
    //Find all the mul()

    regex pattern(R"(mul\(\d+,\d+\))");

    sregex_iterator begin(s.begin(), s.end(), pattern);
    sregex_iterator end;

    string a;
    for (auto it = begin; it != end; ++it) {
        a += it->str(); // Store the matched string
    }

    //Extract all the numbers from the mul()

    regex numPattern(R"(\d+)");

    sregex_iterator numBegin(a.begin(), a.end(), numPattern);
    sregex_iterator numEnd;

    vector<int> nums;
    for(auto it = numBegin; it != numEnd; ++it){
        nums.push_back(stoi(it->str()));
    }
    
    int res = 0;
    for(int i = 0; i < nums.size() - 1; i += 2){
        res += nums[i] * nums[i + 1];
    }

    cout << res;
}

void mul2(const string& s){
    //Find all the mul() if do()

    regex pattern(R"(mul\(\d+,\d+\)|do\(\)|don't\(\))");

    sregex_iterator begin(s.begin(), s.end(), pattern);
    sregex_iterator end;

    string a;
    bool flag = true;

    for (auto it = begin; it != end; ++it) {
        string tmp = it->str();

        if(tmp == "do()")
            flag = true;
        else if(tmp == "don't()")
            flag = false;
        
        if(flag && tmp[0] == 'm')
            a += it->str(); // Store the matched string
    }

    //Extract all the numbers from the mul()

    regex numPattern(R"(\d+)");

    sregex_iterator numBegin(a.begin(), a.end(), numPattern);
    sregex_iterator numEnd;

    vector<int> nums;
    for(auto it = numBegin; it != numEnd; ++it){
        nums.push_back(stoi(it->str()));
    }
    
    int res = 0;
    for(int i = 0; i < nums.size() - 1; i += 2){
        res += nums[i] * nums[i + 1];
    }

    cout << res;
}

int main(){
    string s;
    readFile("input.txt", s);

    mul2(s);
    
    return 0;
}