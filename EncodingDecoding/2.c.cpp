//#include <iostream>
//#include <vector>
//#include <unordered_map>
//
//using namespace std;
//
//// Function to decode the input using the provided code dictionary
//string decodeInstantaneous(const string& input, const unordered_map<string, char>& codeDict) {
//    string output;
//    string currentCode;
//    for (char c : input) {
//        currentCode += c;
//        if (codeDict.count(currentCode)) {
//            output += codeDict.at(currentCode);
//            currentCode = "";
//        }
//    }
//    return output;
//}
