#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <regex>
#include <unordered_map>
#include <unordered_set>
using namespace std;

//Read: Extract all the order rules into a map {before : vector(after)}
//      Extract all the pages into a 2d vector
void readFile(const string& filename, unordered_map<int, unordered_set<int>>& order, vector<vector<int>>& pages){
    fstream file(filename);

    if(!file.is_open()){
        cout << "Error!";
        return;
    }

    string line;

    //Extract all the numbers from the mul()
    regex numPattern(R"(\d+)");

    while(getline(file, line)){
        if(line.empty())
            break;

        sregex_iterator numBegin(line.begin(), line.end(), numPattern);
        sregex_iterator numEnd;

        order[stoi(numBegin->str())].insert(stoi((++numBegin)->str()));
    }

    vector<int> page;
    int tmp;
    
    while(getline(file, line)){
        std::replace(line.begin(), line.end(), ',', ' ');

        istringstream ss(line);

        while(ss >> tmp){
            page.push_back(tmp);
        }

        pages.push_back(page);
        page.clear();
    }
}

//Idea: Loop through each page
//          Loop O(n^2) -> i, j:
//              Check if the page[i], page[j] satisfy the order rules
//              
//          If the entire page satistifed the order list:
//              res += page[middle]
int countForMiddle(unordered_map<int, unordered_set<int>>& order, vector<vector<int>>& pages){
    int n = pages.size();

    int res = 0;

    for(vector<int>& page : pages){
        int m = page.size();
        bool flag = true;

        for(int i = 0; i < m - 1; i++){
            if(!flag) break;

            for(int j = i + 1; j < m; j++){
                if(order[page[j]].find(page[i]) != order[page[j]].end()){
                    flag = false; break;
                }
            }
        }

        if(flag) res += page[(m - 1) / 2];
    }

    return res;
}

//Idea: Loop through each page
//          Loop O(n^2) -> i, j:
//              Check if the page[i], page[j] satisfy the order rules
//              
//              If there is any pair that not satisfied:
//                  Swap them
//
//          If the page isn't satisfied the order rules
//              res += page[middle]
int countForMiddleIncorrect(unordered_map<int, unordered_set<int>>& order, vector<vector<int>>& pages){
    int n = pages.size();

    int res = 0;

    for(vector<int>& page : pages){
        int m = page.size();
        bool flag = true;

        for(int i = 0; i < m - 1; i++){
            for(int j = i + 1; j < m; j++){
                if(order[page[j]].find(page[i]) != order[page[j]].end()){
                    flag = false; 
                    swap(page[j], page[i]);
                }
            }
        }

        if(!flag) res += page[(m - 1) / 2];
    }

    return res;
}

int main(){
    unordered_map<int, unordered_set<int>> order;
    vector<vector<int>> pages;

    readFile("input.txt", order, pages);
    
    // cout << countForMiddle(order, pages);
    cout << countForMiddleIncorrect(order, pages);
}