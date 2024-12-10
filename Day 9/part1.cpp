#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

void readFile(const string& filename, string& disk) {
    fstream file(filename);
    if (!file.is_open()) {
        cout << "Error!"; return;
    }

    getline(file, disk);
}

vector<int> convertToID(string& disk){
    vector<int> res;
    int idx = -1;

    for(int i = 0; i < disk.length(); i++){
        int cur = stoi(string(1, disk[i]));

        if(cur == 0) continue;

        if(i % 2 == 1)
            while(cur--) res.push_back(-1); // '.'
        else{
            ++idx;
            while(cur--) res.push_back(idx);
        }
    }

    return res;
}

void moveVector(vector<int>& diskMap){
    int i = 0, j = diskMap.size() - 1;

    while(true){
        while(diskMap[i] != -1) ++i;
        while(diskMap[j] == -1) --j;

        if(i >= j) break;

        swap(diskMap[i], diskMap[j]);
    }
}

unsigned long long checkSum(vector<int>& diskMap) {
    unsigned long long res = 0;

    for (int i = 0; i < diskMap.size(); i++) {
        if (diskMap[i] == -1) break;

        res += i * (unsigned long long)diskMap[i]; // Use stoull for consistency
    }

    return res;
}

void cookPart1(string& disk){
    vector<int> diskMap = convertToID(disk);
    moveVector(diskMap);
    cout << endl << checkSum(diskMap) << endl;
}

int main() {
    string disk; readFile("input.txt", disk);
    
    vector<int> diskMap = convertToID(disk);
    moveVector(diskMap);

    cout << checkSum(diskMap);

    return 0;
}