#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <unordered_map>
#include <set>
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

    //Needed to be stored in set
    bool operator<(const Point& other) const {
        return tie(x, y) < tie(other.x, other.y);
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// Custom hash function for Point
struct PointHash {
    std::size_t operator()(const Point& p) const {
        return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
    }
};

// Custom hash function for std::pair<Point, char>
struct PairHash {
    std::size_t operator()(const std::pair<Point, char>& p) const {
        return PointHash()(p.first) ^ (std::hash<char>()(p.second) << 1);
    }
};

class Guard {
public:
    Point coor;
    char direction;
    vector<Point> moves = { Point(-1, 0), Point(1, 0), Point(0, -1), Point(0, 1) };
    Guard(int x, int y, char d) : coor(x, y), direction(d) {}
    Guard(Point p, char d) : coor(p), direction(d) {}

    bool isInGrid(const vector<string>& words) {
        return (min(coor.x, coor.y) < 0 || coor.x > words.size() - 1 || coor.y > words[0].size() - 1) ? false : true;
    }

    bool collideObstacle(const vector<string>& words) {
        return (words[coor.x][coor.y] != '#') ? true : false;
    }

    void update() {
        if (direction == '^')
            coor = coor + moves[0];
        else if (direction == 'v')
            coor = coor + moves[1];
        else if (direction == '<')
            coor = coor + moves[2];
        else
            coor = coor + moves[3];
    }
};

class Control {
public:
    // Init Board
    vector<string> words;
    int m, n;
    Guard guard_origin;
    Guard guard;

    // Init Movement
    unordered_map<char, char> changeDirection = { {'<', '^'}, {'^', '>'}, {'>', 'v'}, {'v', '<'} };

    // Memorize the path in Part 01
    set<Point> visited;

    Control() : guard_origin(0, 0, '^'), guard(0, 0, '^') {
        readFile("input.txt", words);
        m = words.size(); n = words[0].size();

        guard = findGuard();
        guard_origin = guard;
    }

    //Part 1
    int countForUniquePos() {
        int res = 0;
        Point prev = guard.coor; // Store the previous move

        while (guard.isInGrid(words)) {
            if (!guard.collideObstacle(words)) {
                guard.direction = changeDirection[guard.direction];
                guard.coor = prev;
            }
            else {
                visited.insert(guard.coor);
                prev = guard.coor;
            }
            
            guard.update();
        }

        return visited.size();
    }
    
    bool createdLoop() {
        Point prev = guard.coor; // Store the previous move
        std::unordered_set<std::pair<Point, char>, PairHash> visited_obstacle;

        while (guard.isInGrid(words)) {
            if (!guard.collideObstacle(words)) {
                if(visited_obstacle.find({prev, guard.direction}) != visited_obstacle.end())
                    return true;
                else
                    visited_obstacle.insert({prev, guard.direction});

                guard.direction = changeDirection[guard.direction];
                guard.coor = prev;
            }
            else {
                visited.insert(guard.coor);
                prev = guard.coor;
            }
            
            guard.update();
        }
        
        return false;
    }

    //Part 2
    int countForObstacleThatCreateLoop(){
        int res = 0;

        for(const auto& point : visited){
            guard = guard_origin;
            words[point.x][point.y] = '#';

            //Check if the obstacle just have placed create a loop
            res += createdLoop();

            words[point.x][point.y] = '.';
        }

        return res;
    }
private:
    Guard findGuard() {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (words[i][j] == '^')
                    return Guard(i, j, '^');
                else if (words[i][j] == '>')
                    return Guard(i, j, '>');
                else if (words[i][j] == '<')
                    return Guard(i, j, '<');
                else if (words[i][j] == 'v')
                    return Guard(i, j, 'v');
            }
        }

        return Guard(0, 0, '^');
    }
};

int main() {
    Control ctrler;
    cout << ctrler.countForUniquePos() << endl;
    cout << ctrler.countForObstacleThatCreateLoop();

    return 0;
}