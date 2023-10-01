#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <iterator>

using namespace std;

// Node class for Huffman tree
class Node {
public:
    char ch;
    int freq;
    Node *left, *right;
    Node(char ch, int freq, Node *left = NULL, Node *right = NULL) {
        this->ch = ch;
        this->freq = freq;
        this->left = left;
        this->right = right;
    }
};

// Compare two nodes
struct compare {
    bool operator()(Node *l, Node *r) {
        return (l->freq > r->freq);
    }
};


// Create Root Node
Node *createRoot(string text) {
    // Count the frequency of appearance of each character
    map<char, int> freq;
    for (char ch : text)
        freq[ch]++;

    // Create a priority queue to store live nodes of the Huffman tree
    priority_queue<Node *, vector<Node *>, compare> pq;

    // Create a leaf node for each character and add it
    // to the priority queue.
    for (auto pair : freq)
        pq.push(new Node(pair.first, pair.second));

    // do till there is more than one node in the queue
    while (pq.size() != 1) {
        // Remove the two nodes of the highest priority
        // (the lowest frequency) from the queue
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();

        // Create a new internal node with these two nodes as children and
        // with a frequency equal to the sum of the two nodes' frequencies.
        // Add the new node to the priority queue.
        int sum = left->freq + right->freq;
        pq.push(new Node('\0', sum, left, right));
    }

    // `root` stores pointer to the root of Huffman Tree
    return pq.top();
}

// Traverse the Huffman Tree and store Huffman Codes in a map.
void buildHuffmanCode(Node *root, string str, map<char, string> &huffmanCode) {
    if (root == NULL)
        return;

    // found a leaf node
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    buildHuffmanCode(root->left, str + "0", huffmanCode);
    buildHuffmanCode(root->right, str + "1", huffmanCode);
}

// Traverse the Huffman Tree and decode the encoded string
string decode(Node *root, string encodedString) {
    string decodedString = "";
    Node *curr = root;
    for (char ch : encodedString) {
        if (ch == '0')
            curr = curr->left;
        else
            curr = curr->right;

        // reached leaf node
        if (!curr->left && !curr->right) {
            decodedString += curr->ch;
            curr = root;
        }
    }
    return decodedString;
}

// accepts root and string
string encode(Node *root, string str) {
    // traverse the Huffman Tree and store Huffman Codes
    // in a map. Also, print them
    map<char, string> huffmanCode;
    buildHuffmanCode(root, "", huffmanCode);

    // print encoded string
    string encodedString = "";
    for (char ch : str) {
        encodedString += huffmanCode[ch];
    }
    return encodedString;
}

// compress the given text file
void compress(Node *root, string text, string file) {
    string encodedString = encode(root, text);
    ofstream out(file);
    out << encodedString;
    out.close();
}

// decompress the given text file
string decompress(Node *root, string file) {
    ifstream in(file);
    string encodedString;
    in >> encodedString;
    in.close();
    string decodedString = decode(root, encodedString);
    return decodedString;
}

int main(){
    string text;
    cout << "Enter text to be encoded: ";
    getline(cin, text);
    Node *root = createRoot(text);
    compress(root, text, "encoded.txt");
    string decoded = decompress(root, "encoded.txt");
    cout << "Decoded text from file: " << decoded;
}
