//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:
    // 1. Create a MinHeap object.
    MinHeap CipherText;
    // 2. Push all leaf node indices into the heap.
    for (int i = 0; i < nextFree; ++i) {
        CipherText.push(i,weightArr);
    }
    // 3. While the heap size is greater than 1:
    //    - Pop two smallest nodes
    //    - Create a new parent node with combined weight
    //    - Set left/right pointers
    //    - Push new parent index back into the heap
    while (CipherText.size >= 2){
        int min1 = CipherText.pop(weightArr);
        int min2 = CipherText.pop(weightArr);
        int newParent = nextFree++;
        weightArr[newParent] = weightArr[min1] + weightArr[min2];
        leftArr[newParent] = min1;
        rightArr[newParent] = min2;
        CipherText.push(newParent, weightArr);
    }
    // 4. Return the index of the last remaining node (root)
    if (CipherText.size > 0) {
        return CipherText.data[0];
    } else {
        return -1; // placeholder
    }
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.

    for (int i = 0; i < 26; ++i) {
        codes[i].clear();
    }
    //single-char edge case
    if (root == -1) {
        return;
    }
    if (leftArr[root] == -1 && rightArr[root] == -1) {
        codes[charArr[root] - 'a'] = "0";
        return;
    }

    stack<pair<int,string>> S;
    S.push({root, ""});
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.
    while (!S.empty()) {
        pair<int,string> p = S.top();
        S.pop();
        int node = p.first;
        string code = p.second;

        bool isLeaf = (leftArr[node] == -1 && rightArr[node] == -1);
        if (isLeaf) {
            if (charArr[node] >= 'a' && charArr[node] <= 'z') {
                codes[charArr[node] - 'a'] = code.empty() ? "0" : code;
            }
            continue;
        }

        if (leftArr[node] != -1) {
            S.push({leftArr[node], code + "0"});
        }
        if (rightArr[node] != -1) {
            S.push({rightArr[node], code + "1"});
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}