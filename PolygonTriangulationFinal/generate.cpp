#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

int main() {
    int maxN = 90;  // maximum number of vertices in the lists
    int C = 150; // range of the integers

    // initialize random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, C);

    ofstream outfile("testcases.txt");
    if (!outfile.is_open()) {
        cout << "Unable to open file." << endl;
        return 1;
    }

    for (int N = 3; N <= maxN; N++) {
        for (int i = 0; i < 30; i++) { // loop 30 times for each value of N
            // generate X and Y lists
            vector<int> X(N);
            vector<int> Y(N);
            for (int j = 0; j < N; j++) {
                int x = dist(gen);
                while (find(X.begin(), X.end(), x) != X.end()) {
                    x = dist(gen); // make sure there are no duplicates
                }
                X[j] = x;

                int y = dist(gen);
                while (find(Y.begin(), Y.end(), y) != Y.end()) {
                    y = dist(gen); // make sure there are no duplicates
                }
                Y[j] = y;
            }

            // output X and Y lists to file
            outfile << N << endl;
            for (int j = 0; j < N; j++) {
                outfile << X[j] << " " << Y[j] << endl;
            }
        }
    }

    outfile.close();
    cout << "Successfully wrote test cases to file." << endl;
    return 0;
}
