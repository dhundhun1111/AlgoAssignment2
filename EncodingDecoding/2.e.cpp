#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <fstream>
using namespace std;
using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::vector;

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
        if(c!='\n')freq[c]++;
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
    string s="Aristotle considered human nature, habit and reason to be equally important forces to be cultivated in education, the ultimate aim of which should be to produce good and virtuous citizens. He proposed that teachers lead their students systematically, and that repetition be used as a key tool to develop good habits, unlike Socrates' emphasis on questioning his listeners to bring out their own ideas. He emphasized the balancing of the theoretical and practical aspects of subjects taught, among which he explicitly mentions reading, writing, mathematics, music, physical education, literature, history, and a wide range of sciences, as well as play, which he also considered important. During the Medieval period, the idea of Perennialism was first formulated by St. Thomas Aquinas in his work \"De Magistro\". Perennialism holds that one should teach those things deemed to be of everlasting importance to all people everywhere, namely principles and reasoning, not just facts (which are apt to change over time), and that one should teach first about people, not machines or techniques. It was originally religious in nature, and it was only much later that a theory of secular perennialism developed. During the Renaissance, the French skeptic Michel de Montaigne (1533 - 1592) was one of the first to critically look at education. Unusually for his time, Montaigne was willing to question the conventional wisdom of the period, calling into question the whole edifice of the educational system, and the implicit assumption that university-educated philosophers were necessarily wiser than uneducated farm workers, for example.";
    string encoded= encode(s);

    ofstream output2("Encoded2.txt");
    output2<<encoded<<endl;;
    for(const auto& x: codes){
        output2<< x.first<<" "<<freq[x.first]<<" "<<x.second<<endl;
    }
    output2<<compressionRatio()<<endl;
    output2.close();


    printHuffmanCodes(s);
    cout<<compressionRatio()<<endl;
}