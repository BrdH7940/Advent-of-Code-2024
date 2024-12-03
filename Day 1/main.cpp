#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>
using namespace std;

void readFile(const string& filename, vector<int>& v1, vector<int>& v2){
    fstream file(filename);

    if(!file.is_open()){
        cout << "Error!";
        return;
    }

    string line;
    int first, second;

    while(getline(file, line)){
        istringstream ss(line);

        ss >> first >> second;

        v1.push_back(first);
        v2.push_back(second);
    }
}

int main(){
    ///First part
    vector<int> v1, v2;

    readFile("input.txt", v1, v2);
    
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    int sum = 0, n = v1.size();

    for(int i = 0; i < n; i++){
        sum += abs(v1[i] - v2[i]);
    }

    cout << "First part: " << sum;


    ///Second part
    int similarity = 0;

    unordered_map<int, int> freq;

    for(int i = 0; i < n; i++){
        freq[v2[i]]++;
    }

    for(int i = 0; i < n; i++){
        similarity += v1[i] * freq[v1[i]];
    }

    cout << "\nSecond part: " << similarity;

    return 0;
}