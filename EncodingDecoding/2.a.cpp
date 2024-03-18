//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <unordered_map>
//
//using namespace std;
//
//// Structure to store symbol frequency and code
//struct ShannonFanoCode {
//    char symbol;
//    int frequency;
//    string code;
//};
//
//// Recursive function to compute Shannon-Fano codes
//void computeShannonFanoCode(vector<ShannonFanoCode>& codes, int start, int end, int totalFreq) {
//    if (start == end-1) {
//        return;
//    }
//
//    int mid = start;
//    int currentFreq = 0;
//
//    // Partition the range based on the frequency
//    while (abs(totalFreq-2*currentFreq)>abs(totalFreq-2*(currentFreq+codes[mid].frequency))) {
//        currentFreq += codes[mid].frequency;
//        ++mid;
//    }
//
//    // Assign 0 to the first half and 1 to the second half of the range
//    for (int i = start; i < mid; ++i) {
//        codes[i].code += "0";
//    }
//    for (int i = mid; i < end; ++i) {
//        codes[i].code += "1";
//    }
//
//    // Recursively compute Shannon-Fano codes for the two partitions
//    computeShannonFanoCode(codes, start, mid, currentFreq);
//    computeShannonFanoCode(codes, mid, end, totalFreq - currentFreq);
//}
//
//// Function to generate Shannon-Fano codes
//vector<ShannonFanoCode> generateShannonFanoCodes(const string& input) {
//    unordered_map<char, int> freqMap;
//
//    // Calculate symbol frequencies
//    for (char c : input) {
//        freqMap[c]++;
//    }
//
//    // Convert frequency map to vector of Shannon-Fano codes
//    vector<ShannonFanoCode> codes;
//    for (const auto& entry : freqMap) {
//        codes.push_back({entry.first, entry.second, ""});
//    }
//
//    // Sort the codes based on frequency in descending order
//    sort(codes.begin(), codes.end(), [](const ShannonFanoCode& a, const ShannonFanoCode& b) {
//        return a.frequency > b.frequency;
//    });
//
//    // Compute Shannon-Fano codes recursively
//    computeShannonFanoCode(codes, 0, codes.size(), input.size());
//
//    return codes;
//}
//
//void printShannonFanoCodes(string &s){
//
//    vector<ShannonFanoCode> ans=generateShannonFanoCodes(s);
//    for(const auto& x: ans){
//        cout<< x.symbol <<" "<<x.frequency<<" "<<x.code<<endl;
//    }
//}
//
//int main(){
//    string s="abcdabcdaaabcaadef";
//    printShannonFanoCodes(s);
//}
