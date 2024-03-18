#include <bits/stdc++.h>
#include <fstream>
#include <time.h>

using namespace std;

struct Point {
    int x, y;
};

double dist(const Point &p1, const Point &p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

double trigCost(const Point &i, const Point &j, const Point &k) {
    return dist(i, j) + dist(j, k) + dist(k, i);
}

bool intersect(const Point &p1, const Point &p2, const Point &p3, const Point &p4) {
    // Compute the cross products of vectors (p1, p2) x (p1, p3) and (p1, p2) x (p1, p4)
    int cp1 = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    int cp2 = (p2.x - p1.x) * (p4.y - p1.y) - (p2.y - p1.y) * (p4.x - p1.x);

    // Compute the cross products of vectors (p3, p4) x (p3, p1) and (p3, p4) x (p3, p2)
    int cp3 = (p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x);
    int cp4 = (p4.x - p3.x) * (p2.y - p3.y) - (p4.y - p3.y) * (p2.x - p3.x);

    // If the cross products have opposite signs, the line segments intersect
    return (cp1 * cp2 < 0) && (cp3 * cp4 < 0);
}



// Ear Clipping Algorithm
double minTriangulationCostGreedy(Point *points, int *visited, int n) {
    if (n == 3) {
        return trigCost(points[visited[0]], points[visited[1]], points[visited[2]]);
    }
    int index;
    int newVisited[n - 1];
    double min = 1e7;
    double cost;

    for (int i = 1; i < n - 1; i++) {
        cost = trigCost(points[visited[i - 1]], points[visited[i]], points[visited[i + 1]]);
        if (cost < min) {
            min = cost;
            index = visited[i];
        }
    }
    cost = trigCost(points[visited[n - 1]], points[visited[n - 2]], points[visited[0]]);
    if (cost < min) {
        min = cost;
        index = visited[n - 1];
    }
    cost = trigCost(points[visited[0]], points[visited[1]], points[visited[n - 1]]);
    if (cost < min) {
        min = cost;
        index = visited[0];
    }
    int m = 0;
    for (int i = 0; i < n; i++) {
        if (visited[i] != index) {
            newVisited[m++] = visited[i];
        }
    }
    return cost + minTriangulationCostGreedy(points, newVisited, n - 1);
}

int main() {
    ifstream infile("output.txt");
    ofstream outfile("greedy.txt");
    ofstream outfile_time("greedy_time.txt");

    int N;
    while (infile >> N) {
        Point points[N];
        for (int i = 0; i < N; i++) {
            infile >> points[i].x >> points[i].y;
        }
        int visited[N];
        for (int k = 0; k < N; k++) {
            visited[k] = k;
        }
        clock_t start = clock();
        double result = minTriangulationCostGreedy(points, visited, N);
        clock_t end = clock();
        double elapsedTime = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
        cout << elapsedTime << endl;
        outfile << "Number of vertices: " << N << endl;
        outfile << result << endl;
        outfile_time << elapsedTime << endl;
    }
    infile.close();
    outfile.close();
    outfile_time.close();
    return 0;
}