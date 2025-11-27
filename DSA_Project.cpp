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
    
    bool search(const string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }
            current = current->children[ch];
        }
        return current->isEnd;
    }

    void remove(const string& word) {
        removeHelper(root, word, 0);
    }

    vector<string> getSuggestions(const string& word) {
        vector<string> suggestions;
        // Edit distance of 1 means one substitution, insertion, or deletion is allowed.
        const int MAX_DISTANCE = 1; 
        
        findSuggestionsHelper(root, word, "", suggestions, MAX_DISTANCE);
        return suggestions;
    }

};



int main() {



    
    return 0;
}

