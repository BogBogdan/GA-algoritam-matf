#include <cmath>
#include <map>
#include <cmath>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_set>
#include <vector>

void draw(int w, int h, std::vector<std::vector<int>> circles, bool ok);

using namespace std;

class Solution {
public:

    bool intersectCircles(const vector<int>& c1, const vector<int>& c2) {
        long long dx = (long long)c1[0] - c2[0];
        long long dy = (long long)c1[1] - c2[1];
        long long rSum = (long long)c1[2] + c2[2];
        return (dx * dx + dy * dy) <= (rSum * rSum);
    }

    bool intersectInside(const vector<int>& c1, const vector<int>& c2, int xCorner, int yCorner) {
        double dx = (double)c2[0] - c1[0];
        double dy = (double)c2[1] - c1[1];
        double d2 = dx * dx + dy * dy;
        double d = sqrt(d2);

        if (d < 1e-9) return true;

        double r1 = c1[2];
        double r2 = c2[2];

        double a = (r1 * r1 - r2 * r2 + d2) / (2 * d);
        double h2 = r1 * r1 - a * a;
        double h = sqrt(max(0.0, h2));

        double x0 = c1[0] + (a / d) * dx;
        double y0 = c1[1] + (a / d) * dy;

        double rx = -(dy * (h / d));
        double ry = dx * (h / d);

        double x1 = x0 + rx, y1 = y0 + ry;
        double x2 = x0 - rx, y2 = y0 - ry;

        return ((x1 >= 0 && x1 <= xCorner && y1 >= 0 && y1 <= yCorner) ||
                (x2 >= 0 && x2 <= xCorner && y2 >= 0 && y2 <= yCorner));
    }

    bool canReachCorner(int xCorner, int yCorner, vector<vector<int>>& circles) {
        int n = circles.size();
        vector<vector<int>> circle_graph(n);
        queue<int> q;
        unordered_set<int> target_nodes;
        vector<bool> visited(n, false);

        for (int i = 0; i < n; i++) {

            if (intersectCircles(circles[i], {0, 0, 0}) ||
                intersectCircles(circles[i], {xCorner, yCorner, 0})) return false;


            if (intersectAboveD(circles[i], xCorner, yCorner)) {
                q.push(i);
                visited[i] = true;
            }


            if (intersectBelowD(circles[i], xCorner, yCorner)) {
                target_nodes.insert(i);
            }

            for (int j = i + 1; j < n; j++) {
                if (intersectCircles(circles[i], circles[j])) {

                    if (intersectInside(circles[i], circles[j], xCorner, yCorner)) {
                        circle_graph[i].push_back(j);
                        circle_graph[j].push_back(i);
                    }
                }
            }
        }

        while (!q.empty()) {
            int i = q.front();
            q.pop();

            if (target_nodes.count(i)) return false;

            for (int neighbor : circle_graph[i]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        return true;
    }

    bool intersectAboveD(const vector<int>& c, int xCorner, int yCorner) {
        if (c[1] >= 0 && c[1] <= yCorner && (abs(c[0]) <= c[2])) return true; // Leva ivica
        if (c[0] >= 0 && c[0] <= xCorner && (abs(c[1] - yCorner) <= c[2])) return true; // Gornja ivica
        return false;
    }

    bool intersectBelowD(const vector<int>& c, int xCorner, int yCorner) {
        if (c[0] >= 0 && c[0] <= xCorner && (abs(c[1]) <= c[2])) return true; // Donja ivica
        if (c[1] >= 0 && c[1] <= yCorner && (abs(c[0] - xCorner) <= c[2])) return true; // Desna ivica
        return false;
    }
};
int main() {
    Solution sol;

    //Primer 1
    vector<vector<int>> circles = {{1,4,1},{3,4,1},{5,4,1},{7,4,1}};
    int xCorner = 8;
    int yCorner = 8;

    //Primer 2
    //vector<vector<int>> circles = {{2,20,13},{20,2,13}};
    //int xCorner = 15;
    //int yCorner = 15;

    //Primer 3
    //vector<vector<int>> circles = {{2,1,1},{1,2,1}};
    //int xCorner = 3;
    //int yCorner = 3;

    //Primer 4
    //vector<vector<int>> circles = {{1,2,1},{3,2,1},{5,2,1},{7,2,1}, {3,5,1},{5,5,1},{7,5,1},{9,5,1}};
    //int xCorner = 10;
    //int yCorner = 10;

    bool ok = sol.canReachCorner(xCorner, yCorner, circles);
    if (ok) {
        std::cout << "Putanja postoji!" << std::endl;
    } else {
        std::cout << "Putanja je blokirana!" << std::endl;
    }

    draw(xCorner,yCorner,circles,ok);

    return 0;
}
