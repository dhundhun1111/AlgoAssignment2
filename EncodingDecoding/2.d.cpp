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
    string s="Today I Rabindranath Tagore complete eighty years of my life .As I look back on the vast stretch of years that lie behind me and see in clear perspective the history of my early development, I am struck by the change that has taken place both in my own attitude and in the psychology of my countrymen -- a change that carries within it a cause of profound tragedy. Our direct contact with the larger world of men was linked up with the contemporary history of the English people whom we came to know in those earlier days. It was mainly through their mighty literature that we formed our ideas with regard to these newcomers to our Indian shores. In those days the type of learning that was served out to us was neither plentiful nor diverse, nor was the spirit of scientific enquiry very much in evidence. Thus their scope being strictly limited, the educated of those days had recourse to English language and literature. Their days and nights were eloquent with the stately declamations of Burke, with Macaulay’s long-rolling sentences; discussions centered upon Shakespeare's drama and Byron's poetry and above all upon the large-hearted liberalism of the nineteenth-century English politics. At the time though tentative attempts were being made to gain our national independence, at heart we had not lost faith in the generosity of the English race. This belief was so firmly rooted in the sentiments of our leaders as to lead them to hope that the victor would of his own grace pave the path of freedom for the vanquished. This belief was based upon the fact that England at the time provided a shelter to all those who had to flee from persecution in their own country. Political martyrs who had suffered for the honour of their people were accorded unreserved welcome at the hands of the English. I was impressed by this evidence of liberal humanity in the character of the English and thus I was led to set them on the pedestal of my highest respect. This generosity in their national character had not yet been vitiated by imperialist pride. About this time, as a boy in England, I had the opportunity of listening to the speeches of John Bright, both in and outside Parliament. The large-hearted, radical liberalism of those speeches, overflowing all narrow national bounds, had made so deep an impression on my mind that something of it lingers even today, even in these days of graceless disillusionment.";
    string encoded= encode(s);

    ofstream output2("Encoded1.txt");
    output2<<encoded<<endl;;
    for(const auto& x: codes){
        output2<< x.first<<" "<<freq[x.first]<<" "<<x.second<<endl;
    }
    output2<<compressionRatio()<<endl;
    output2.close();


    printHuffmanCodes(s);
    cout<<compressionRatio()<<endl;
}