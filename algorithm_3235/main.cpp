#include <vector>
#include <cmath>
#include <queue>

using namespace std;

class Solution {
public:
    bool canReachCorner(int xCorner, int yCorner, vector<vector<int>>& circles) {
        int n = circles.size();
        vector<vector<int>> adj(n);
        vector<bool> visited(n, false);
        queue<int> q;

        for (int i = 0; i < n; i++) {
            long long x = circles[i][0], y = circles[i][1], r = circles[i][2];

            // Da li krug direktno pokriva start ili cilj
            if (x*x + y*y <= r*r || (x-xCorner)*(x-xCorner) + (y-yCorner)*(y-yCorner) <= r*r)
                return false;


            if ((x + r > 0 && x - r <= 0 && y >= 0 && y <= yCorner) ||
            (y - r < yCorner && y + r >= yCorner && x >= 0 && x <= xCorner) ||
            (x*x + (y-yCorner)*(y-yCorner) <= r*r)) {
                    q.push(i);
                    visited[i] = true;
                }

            // Pravljenje grafa
            for (int j = i + 1; j < n; j++) {
                long long dx = x - circles[j][0];
                long long dy = y - circles[j][1];
                long long r_sum = r + circles[j][2];
                if (dx*dx + dy*dy <= r_sum*r_sum) {
                    long long x1 = circles[i][0], y1 = circles[i][1], r1 = circles[i][2];
                    long long x2 = circles[j][0], y2 = circles[j][1], r2 = circles[j][2];

                    if (x1 * r2 + x2 * r1 < (r1 + r2) * xCorner &&
                        y1 * r2 + y2 * r1 < (r1 + r2) * yCorner) {
                        adj[i].push_back(j);
                        adj[j].push_back(i);
                    }
                }
            }
        }

        // BFS
        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            long long x = circles[curr][0], y = circles[curr][1], r = circles[curr][2];

            if ((x - r < xCorner && x + r >= xCorner && y >= 0 && y <= yCorner)
            || (y + r > 0 && y - r <= 0 && x >= 0 && x <= xCorner)
            || (x-xCorner)*(x-xCorner)+y*y <= r*r) {
                    return false;
                }

            for (int sused : adj[curr]) {
                if (!visited[sused]) {
                    visited[sused] = true;
                    q.push(sused);
                }
            }
        }

        return true;
    }
};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
