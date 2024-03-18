#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>


using namespace std;

bool compareVectors(const vector<int>& v1, const vector<int>& v2) {
    double angle1 = atan2(v1[1], v1[0]);
    double angle2 = atan2(v2[1], v2[0]);
    return angle1 < angle2;
}


int main() {
    // open vertices file
    ifstream infile("testcases.txt");
    ofstream outfile("output.txt");


    if (infile.is_open() && outfile.is_open()) {
        int N;

        // loop over all test cases
        while (infile >> N) {
            // initialize vectors to hold the coordinates
            vector<int> X(N);
            vector<int> Y(N);

            // read X and Y lists from file
            for (int i = 0; i < N; i++) {
                infile >> X[i] >> Y[i];
            }
            

            // sort X and Y lists and store their max and min elements
            sort(X.begin(), X.end());
            sort(Y.begin(), Y.end());
            int maxX = X[N-1];
            int maxY = Y[N-1];
            int minX = X[0];
            int minY = Y[0];

            // divide the other (not max or min) elements into two groups: X1 and X2, and Y1 and Y2
            vector<int> X1;
            vector<int> X2;
            vector<int> Y1;
            vector<int> Y2;
            vector<int> indices(N-2);
            for (int i = 1; i < N-1; i++) {
                indices[i-1] = i;
            }
            random_shuffle(indices.begin(), indices.end());
            for (int i = 0; i < indices.size(); i++) {
                if (i % 2 == 0) {
                    X1.push_back(X[indices[i]]);
                    Y1.push_back(Y[indices[i]]);
                } else {
                    X2.push_back(X[indices[i]]);
                    Y2.push_back(Y[indices[i]]);
                }
            }

            // re-insert the minimum and maximum elements at the start and end of the divided lists
            X1.insert(X1.begin(), minX);
            X1.push_back(maxX);
            X2.insert(X2.begin(), minX);
            X2.push_back(maxX);
            Y1.insert(Y1.begin(), minY);
            Y1.push_back(maxY);
            Y2.insert(Y2.begin(), minY);
            Y2.push_back(maxY);

            // calculate consecutive differences for X1 and X2 and store in XVec and YVec
            vector<int> XVec;
            for (int i = 0; i < X1.size()-1; i++) {
                XVec.push_back(X1[i+1] - X1[i]);
            }
            for (int i = X2.size()-1; i > 0; i--) {
                XVec.push_back(X2[i] - X2[i-1]);
            }
            vector<int> YVec;
            for (int i = 0; i < Y1.size()-1; i++) {
                YVec.push_back(Y1[i+1] - Y1[i]);
            }
            for (int i = Y2.size()-1; i > 0; i--) {
                YVec.push_back(Y2[i] - Y2[i-1]);
            }

            // print results
            // print max and min elements
            cout << "Max X: " << maxX << endl;
            cout << "Max Y: " << maxY << endl;
            cout << "Min X: " << minX << endl;
            cout << "Min Y: " << minY << endl;
            cout << "X1: ";
            for (int i = 0; i < X1.size(); i++) {
                cout << X1[i] << " ";
            }
            cout << endl;

            cout << "X2: ";
            for (int i = 0; i < X2.size(); i++) {
                cout << X2[i] << " ";
            }
            cout << endl;

            cout << "Y1: ";
            for (int i = 0; i < Y1.size(); i++) {
                cout << Y1[i] << " ";
            }
            cout << endl;

            cout << "Y2: ";
            for (int i = 0; i < Y2.size(); i++) {
                cout << Y2[i] << " ";
            }
            cout << endl;
            cout << "XVec: ";
            for (int i = 0; i < XVec.size(); i++) {
                cout << XVec[i] << " ";
            }
            cout << endl;

            cout << "YVec: ";
            for (int i = 0; i < YVec.size(); i++) {
                cout << YVec[i] << " ";
            }
            cout << endl;
            random_shuffle(YVec.begin(), YVec.end());

            // loop through XVec and YVec and treat each pair as a 2D vector
            for (int i = 0; i < XVec.size(); i++) {
                int x = XVec[i];
                int y = YVec[i];
                cout << "Vector " << i+1 << ": (" << x << ", " << y << ")" << endl;
            }

            vector<vector<int>> vectors;

            for (int i = 0; i < XVec.size(); i++) {
                int x = XVec[i];
                int y = YVec[i];
                vectors.push_back({x, y});
            }
            sort(vectors.begin(), vectors.end(), compareVectors);

            // Calculate the endpoints of the vectors
            vector<pair<int, int>> endpoints(vectors.size());
            int x = 0, y = 0;
            for (int i = 0; i < vectors.size(); i++) {
                x += vectors[i][0];
                y += vectors[i][1];
                endpoints[i] = {x, y};
            }

            // Find the min and max x and y coordinates of the endpoints
            int min_x = endpoints[0].first, max_x = endpoints[0].first;
            int min_y = endpoints[0].second, max_y = endpoints[0].second;
            for (int i = 1; i < endpoints.size(); i++) {
                if (endpoints[i].first < min_x) {
                    min_x = endpoints[i].first;
                }
                if (endpoints[i].first > max_x) {
                    max_x = endpoints[i].first;
                }
                if (endpoints[i].second < min_y) {
                    min_y = endpoints[i].second;
                }
                if (endpoints[i].second > max_y) {
                    max_y = endpoints[i].second;
                }
            }

            // Move the polygon to the original min and max coordinates
            int x_shift = -min_x, y_shift = -min_y;
            for (int i = 0; i < endpoints.size(); i++) {
                endpoints[i].first += x_shift;
                endpoints[i].second += y_shift;
            }

            // Print the sorted vectors and the endpoints
            for (int i = 0; i < vectors.size(); i++) {
                cout << "Vector " << i+1 << ": (" << vectors[i][0] << ", " << vectors[i][1] << ")" << endl;
            }
            for (int i = 0; i < endpoints.size(); i++) {
                cout << "Endpoint " << i+1 << ": (" << endpoints[i].first << ", " << endpoints[i].second << ")" << endl;
            }
            outfile << N << endl;
            for (int i = 0; i < endpoints.size(); i++) {
                outfile << endpoints[i].first << " " << endpoints[i].second << endl;
            }
        }

        infile.close();
        outfile.close();

    }
    else {
        cout << "Error opening file." << endl;
    }

    return 0;
}
