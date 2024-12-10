#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
#include <unordered_set>
using namespace std;

class Point {
public:
    int x, y;
    Point(int x, int y) : x(x), y(y) {}

    Point operator + (const Point& r) const {
        return Point(x + r.x, y + r.y);
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

struct PointHash {
    std::size_t operator()(const Point& p) const {
        return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
    }
};

void readFile(const string& filename, vector<vector<int>>& nums){
    fstream file(filename);

    if(!file.is_open()){
        cout << "Error!"; return;
    }

    string line;
    vector<int> num;
    
    while(getline(file, line)){
        for(int i = 0; i < line.length(); i++){
            num.push_back(line[i] - '0');
        }

        nums.push_back(num);
        num.clear();
    }
}

int bfs(vector<vector<int>>& nums, Point cur){
    const int m = nums.size(), n = nums[0].size();
    vector<Point> moves = {Point(-1, 0), Point(1, 0), Point(0, -1), Point(0, 1)};
                        //Up, Down, Left, Right
    int res = 0;

    unordered_set<Point, PointHash> visited;
    queue<pair<Point, int>> frontier;
    frontier.push({cur, 0});

    while(!frontier.empty()){
        int sz = frontier.size();

        while(sz--){
            auto [cur, score] = frontier.front(); frontier.pop();

            if(score == 9){
                ++res; continue;
            }

            for(Point& move : moves){
                Point tmp = cur + move;

                if(min(tmp.x, tmp.y) < 0 || tmp.x >= m || tmp.y >= n)
                    continue;

                if(visited.find(tmp) == visited.end() && (nums[tmp.x][tmp.y] - score == 1)){
                    frontier.push({tmp, score + 1});
                    visited.insert(tmp);
                }
            }
        }
    }

    return res;
}

int scoreTrailheads(vector<vector<int>>& nums){
    const int m = nums.size(), n = nums[0].size();

    int res = 0;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(nums[i][j] == 0)
                res += bfs(nums, Point(i,j));
        }
    }

    return res;
}

int main(){
    vector<vector<int>> nums; readFile("input.txt", nums);

    cout << scoreTrailheads(nums);

    return 0;
}