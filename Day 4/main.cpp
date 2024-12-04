#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

void readFile(const string& filename, vector<vector<char>>& words){
    fstream file(filename);

    if(!file.is_open()){
        cout << "Error!";
        return;
    }

    string line;
    
    while(getline(file, line)){
        vector<char> tmp(line.begin(), line.end());

        words.push_back(tmp);

        tmp.clear();
    }
}

bool isValid(pair<int, int> coor, const int m, const int n){
    if(coor.first < 0 || coor.first > m - 1)
        return false;
    if(coor.second < 0 || coor.second > n - 1)
        return false;
    return true;
}

int isXmas(vector<vector<char>>& words, vector<pair<int, int>>& coors){
    const int m = words.size(), n = words[0].size();

    for(int i = 0; i < 3; i++){
        if(!isValid(coors[i], m, n))
            return 0;
    }

    if(words[coors[0].first][coors[0].second] == 'M' 
    && words[coors[1].first][coors[1].second] == 'A'
    && words[coors[2].first][coors[2].second] == 'S'){
        return 1;
    }

    return 0;
}

int countForXmas(vector<vector<char>>& words){
    int res = 0, m = words.size(), n = words[0].size();

    vector<pair<int, int>> coors;

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(words[i][j] == 'X'){
                coors = {{i - 1, j - 1}, {i - 2, j - 2}, {i - 3, j - 3}};
                res += isXmas(words, coors);

                coors = {{i - 1, j}, {i - 2, j}, {i - 3, j}};
                res += isXmas(words, coors);

                coors = {{i - 1, j + 1}, {i - 2, j + 2}, {i - 3, j + 3}};
                res += isXmas(words, coors);

                coors = {{i, j + 1}, {i, j + 2}, {i, j + 3}};
                res += isXmas(words, coors);

                coors = {{i + 1, j + 1}, {i + 2, j + 2}, {i + 3, j + 3}};
                res += isXmas(words, coors);

                coors = {{i + 1, j}, {i + 2, j}, {i + 3, j}};
                res += isXmas(words, coors);

                coors = {{i + 1, j - 1}, {i + 2, j - 2}, {i + 3, j - 3}};
                res += isXmas(words, coors);

                coors = {{i, j - 1}, {i, j - 2}, {i, j - 3}};
                res += isXmas(words, coors);
            }
        }
    }

    return res;
}

bool isX_mas(vector<vector<char>>& words, vector<pair<int, int>>& coors){
    const int m = words.size(), n = words[0].size();

    for(int i = 0; i < 4; i++){
        if(!isValid(coors[i], m, n))
            return 0;
    }
    
    int x0 = coors[0].first, y0 = coors[0].second;
    int x1 = coors[1].first, y1 = coors[1].second;
    int x2 = coors[2].first, y2 = coors[2].second;
    int x3 = coors[3].first, y3 = coors[3].second;

    if((words[x0][y0] == 'M' && words[x2][y2] == 'S') || (words[x0][y0] == 'S' && words[x2][y2] == 'M'))
        if((words[x1][y1] == 'M' && words[x3][y3] == 'S') || (words[x1][y1] == 'S' && words[x3][y3] == 'M'))
            return 1;
    
    return 0;
}

int countForX_mas(vector<vector<char>>& words){
    int res = 0, m = words.size(), n = words[0].size();

    vector<pair<int, int>> coors;

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(words[i][j] == 'A'){
                coors = {{i - 1, j - 1}, {i - 1, j + 1}, {i + 1, j + 1}, {i + 1, j - 1}};
                res += isX_mas(words, coors);
            }
        }
    }

    return res;
}

int main(){
    vector<vector<char>> words;

    readFile("input.txt", words);

    cout << countForXmas(words) << endl;
    cout << countForX_mas(words);
    
    return 0;
}