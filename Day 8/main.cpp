#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <unordered_map>
#include <set>
#include <map>
#include <unordered_set>
using namespace std;

void readFile(const string& filename, vector<string>& words) {
    fstream file(filename);
    if (!file.is_open()) {
        cout << "Error!"; return;
    }

    string line;
    while (getline(file, line)) words.push_back(line);
}

class Point {
public:
    int x, y;
    Point(int x, int y) : x(x), y(y) {}

    Point operator + (const Point& r) const {
        return Point(x + r.x, y + r.y);
    }

    Point operator - (const Point& r) const {
        return Point(x - r.x, y - r.y);
    }

    friend Point operator*(int scalar, const Point& p) {
        return Point(scalar * p.x, scalar * p.y);
    }

    bool operator < (const Point& other) const {
        return tie(x, y) < tie(other.x, other.y);
    }

    bool operator == (const Point& other) const {
        return x == other.x && y == other.y;
    }
};

struct PointHash {
    std::size_t operator()(const Point& p) const {
        return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
    }
};

bool isInMap(const int& m, const int& n, Point cur){
    return (min(cur.x, cur.y) >= 0 && cur.x < m && cur.y < n);
}

int countUniqueAntinodes1(vector<string>& words){
    int m = words.size(), n = words[0].size();

    map<char, vector<Point>> locations;
    unordered_set<Point, PointHash> visited;

    //Extract all the antenna from the map
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(words[i][j] != '.')
                locations[words[i][j]].push_back(Point(i,j));
        }
    }

    //Find all the antinode locations
    for(const auto& it : locations){
        auto location = it.second;
        int k = location.size();

        for(int i = 0; i < k - 1; i++){
            for(int j = i + 1; j < k; j++){
                Point antinode1 = 2 * location[i] - location[j];
                Point antinode2 = 2 * location[j] - location[i];

                if(isInMap(m, n, Point(antinode1)))
                    visited.insert(antinode1);
                if(isInMap(m, n, Point(antinode2)))
                    visited.insert(antinode2);
            }
        }
    }

    return visited.size();
}

int countUniqueAntinodes2(vector<string>& words){
    int m = words.size(), n = words[0].size();

    map<char, vector<Point>> locations;
    unordered_set<Point, PointHash> visited;

    //Extract all the antenna from the map
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(words[i][j] != '.')
                locations[words[i][j]].push_back(Point(i,j));
        }
    }

    //Find all the antinode locations
    for(const auto& it : locations){
        auto location = it.second;
        int k = location.size();

        for(int i = 0; i < k - 1; i++){
            visited.insert(location[i]);

            for(int j = i + 1; j < k; j++){
                Point direction = location[j] - location[i];
                Point antinode1 = location[j] + direction;
                Point antinode2 = location[i] - direction;

                while(isInMap(m, n, antinode1)){
                    visited.insert(antinode1);
                    antinode1 = antinode1 + direction;
                }
                while(isInMap(m, n, antinode2)){
                    visited.insert(antinode2);
                    antinode2 = antinode2 - direction;
                }
            }
        }

        visited.insert(location[k - 1]);
    }

    return visited.size();
}

int main(){
    vector<string> words;
    readFile("input.txt", words);

    cout << countUniqueAntinodes1(words) << endl;
    cout << countUniqueAntinodes2(words);

    return 0;
}