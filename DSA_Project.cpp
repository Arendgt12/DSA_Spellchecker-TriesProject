#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream> 

using namespace std;

struct TrieNode {
    bool isEnd;
    unordered_map<char, TrieNode*> children;

    TrieNode() : isEnd(false) {}
    
    ~TrieNode() {
        for (auto const& pair : children) {
            delete pair.second;
        }
    }
};

struct Trie {
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }
    
    ~Trie() {
        delete root;
    }

    // --- Core Trie Operations ---
    
    void insert(const string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->isEnd = true;
    }

};



int main() {



    
    return 0;
}

