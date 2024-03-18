#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <fstream>
using namespace std;

struct Node {
    char data;
    int frequency;
    Node* left;
    Node* right;

    Node(char data, int frequency) {
        this->data = data;
        this->frequency = frequency;
        left = right = nullptr;
    }

    Node(int frequency, Node* left, Node* right) {
        data = '\0';
        this->frequency = frequency;
        this->left = left;
        this->right = right;
    }
};

struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;
    }
};

//void preorderHuffmanTree(Node *root);

unordered_map<char, string> codes;
unordered_map<char, int> freq;

void generateCodes(Node* root, string code) {
    if (root == nullptr) {
        return;
    }
    if (root->data != '\0') {
        codes[root->data] = code;
    }
    generateCodes(root->left, code + "0");
    generateCodes(root->right, code + "1");
}

string encode(string text) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    /*unordered_map<char, int> is a C++ Standard Library container that represents an associative array, which allows you to store and access data based on a unique key. In this case, the keys are characters (char) and the values are integers (int).
The name of the map is freq, which suggests that it is being used to store frequency counts. For example, you might use this map to count the number of occurrences of each character in a string.*/
    for (char c : text) {
        freq[c]++;
    }

    for(const auto& z: freq){
        cout<< z.first<<" "<<z.second<<endl;
    }

    for (auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }
    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        int sum = left->frequency + right->frequency;
        pq.push(new Node(sum, left, right));
    }
    Node* root = pq.top();
//    preorderHuffmanTree(root);
    cout<<endl;
    pq.pop();
    generateCodes(root, "");
    string encoded = "";
    for (char c : text) {
        encoded += codes[c];
    }
    return encoded;
}

//void preorderHuffmanTree(Node *root) {
//    cout<<root->data<<" ";
//    if(root->left) preorderHuffmanTree(root->left);
//    if(root->right) preorderHuffmanTree(root->right);
//}


void printHuffmanCodes(string &s){

//    encode(s);
    for(const auto& x: codes){
        cout<< x.first<<" "<<freq[x.first]<<" "<<x.second<<endl;
    }
}

string decode(string &input){
    string output;
    string currentCode;
    unordered_map<string, char> codeDict;
    for(const auto& x: codes){
        codeDict[x.second]=x.first;
    }

    for (char c : input) {
        currentCode += c;
        if (codeDict[currentCode]) {
            output += codeDict[currentCode];
            currentCode = "";
        }
    }
    return output;
}

double compressionRatio(){
    unsigned long long originalBits=0;
    for(const auto& z: freq){
        originalBits+=8*z.second;
    }

    unsigned long long compressedBits=0;
    unsigned int sumLens=0;
    for(const auto& x: codes){
        compressedBits+=(x.second).length()*freq[x.first];
        sumLens+=x.second.length();
    }
    unsigned long long totalCompressedBits=compressedBits+sumLens+8*codes.size()+4;

    return ((double)originalBits/(double)totalCompressedBits);
}

int main(){
    string s="abcdabcdaaabcaadef";
    string encoded= encode(s);
    printHuffmanCodes(s);
    cout<<endl;
    string decoded=decode(encoded);
    cout<<"Decoded string is: "<<endl;
    cout<<decoded<<endl;
}