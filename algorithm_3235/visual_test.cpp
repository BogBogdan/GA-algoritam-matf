#include "raylib.h"
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <algorithm>

// Struktura za koordinate na ekranu
struct Point2D {
    int x, y;
    bool operator<(const Point2D& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    bool operator==(const Point2D& other) const {
        return x == other.x && y == other.y;
    }
};

void draw(int w, int h, std::vector<std::vector<int>> circles, bool ok)
{
    const float skala = 50.0f;
    const int offset = 50;

    int screenW = (int)(w * skala) + 2 * offset;
    int screenH = (int)(h * skala) + 2 * offset;

    if (!IsWindowReady()) {
        InitWindow(screenW, screenH, "MATF - Vizuelizacija");
        SetTargetFPS(60);
    }

    // --- GRAFIČKI PRONAĐI PUTANJU (samo ako je ok == true) ---
    std::vector<Vector2> pathPoints;
    if (ok) {
        // Početak i kraj u koordinatama ekrana
        Point2D start = { offset, offset + (int)(h * skala) };
        Point2D end = { offset + (int)(w * skala), offset };

        // Definišemo korak za mrežni BFS
        int step = 5;

        std::queue<Point2D> q;
        std::map<Point2D, Point2D> parent; // Za rekonstrukciju puta

        q.push(start);
        parent[start] = start; // Početak je sam sebi roditelj

        bool foundPath = false;

        while (!q.empty()) {
            Point2D current = q.front();
            q.pop();

            if (current == end) {
                foundPath = true;
                break;
            }

            // Mogući pravci kretanja na grafičkoj mreži
            int dx[] = {-step, step, 0, 0, -step, -step, step, step};
            int dy[] = {0, 0, -step, step, -step, step, -step, step};

            for (int i = 0; i < 8; ++i) {
                Point2D next = {current.x + dx[i], current.y + dy[i]};

                // Provera granica unutar pravougaonika
                if (next.x < offset || next.x > offset + (int)(w * skala) ||
                    next.y < offset || next.y > offset + (int)(h * skala)) {
                    continue;
                }

                // Provera da li je tačka unutar bilo kog kruga
               bool inCircle = false;
                float probX = (next.x - offset) / skala;
                float probY = (offset + (int)(h * skala) - next.y) / skala;

                float margina = 0.1f;

                for (const auto& c : circles) {
                    float dx = probX - c[0];
                    float dy = probY - c[1];
                    float dist2 = dx * dx + dy * dy;

                    // Proveravamo protiv (r + margina)^2 umesto samo r^2
                    float proveraR = (float)c[2] + margina;
                    if (dist2 <= proveraR * proveraR) {
                        inCircle = true;
                        break;
                    }
                }

                if (!inCircle && parent.find(next) == parent.end()) {
                    parent[next] = current;
                    q.push(next);
                }
            }
        }

        // Rekonstrukcija putanje
        if (foundPath) {
            Point2D curr = end;
            while (!(curr == start)) {
                pathPoints.push_back({(float)curr.x, (float)curr.y});
                curr = parent[curr];
            }
            pathPoints.push_back({(float)start.x, (float)start.y});
            // Obrćemo putanju da ide od starta do kraja
            std::reverse(pathPoints.begin(), pathPoints.end());
        }
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // --- OKVIR ---
        DrawRectangleLines(offset, offset, (int)(w * skala), (int)(h * skala), BLACK);

        // --- GRAFIČKI PRONAĐEN PUT (IZLOMLJENA LINIJA) ---
        if (ok && !pathPoints.empty()) {
            // Crtamo seriju spojenih linija
            for (size_t i = 0; i < pathPoints.size() - 1; ++i) {
                // Koristimo deblju i uočljiviju boju
                DrawLineEx(pathPoints[i], pathPoints[i+1], 4.0f, GREEN);
            }
            // Markeri za početak i kraj
            DrawCircleV(pathPoints[0], 6, BLUE);
            DrawCircleV(pathPoints.back(), 6, GOLD);
            DrawText("PUTANJA SLOBODNA (ZELENO)", offset + 10, offset / 2, 20, DARKGREEN);
        } else {
            DrawText("PUTANJA JE BLOKIRANA", offset + 10, offset / 2, 20, MAROON);
        }

        // --- KRUGOVI ---
        for (const auto& c : circles)
        {
            float scaledCX = offset + (c[0] * skala);
            float scaledCY = (offset + (h * skala)) - (c[1] * skala);
            float scaledR = c[2] * skala;
            DrawCircleV({scaledCX, scaledCY}, scaledR, Fade(MAROON, 0.3f));
            DrawCircleLines((int)scaledCX, (int)scaledCY, scaledR, BLACK);
        }

        DrawText("Pritisni ESC", 10, 10, 15, GRAY);
        EndDrawing();
        if (IsKeyPressed(KEY_ESCAPE)) break;
    }
}
