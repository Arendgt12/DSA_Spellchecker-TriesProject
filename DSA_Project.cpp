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

    //calls the removehelper function
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

    // --- Helper Functions ---

    bool removeHelper(TrieNode* node, const string& word, int depth) {
        if (!node) return false;

        if (depth == word.size()) {
            if (!node->isEnd) return false;
            node->isEnd = false;
            return node->children.empty();
        }

        char ch = word[depth];
        auto it = node->children.find(ch);
        if (it == node->children.end())
            return false;

        bool shouldDeleteChild = removeHelper(it->second, word, depth + 1);

        if (shouldDeleteChild) {
            delete it->second;
            node->children.erase(it);

            return (!node->isEnd && node->children.empty());
        }

        return false;
    }

    void findSuggestionsHelper(TrieNode* node, const string& targetWord, 
                               const string& currentPrefix, 
                               vector<string>& suggestions, 
                               int maxDistance) {
        
        if (!node) return;
          //calls the distance function                     
        int dist = Distance(currentPrefix, targetWord);

        if (dist > maxDistance && currentPrefix.size() > targetWord.size() + maxDistance) {
            return;
        }

        if (node->isEnd && dist <= maxDistance && currentPrefix != targetWord) {
             suggestions.push_back(currentPrefix);
        }

        for (auto const& pair : node->children) {
            findSuggestionsHelper(pair.second, targetWord, currentPrefix + pair.first, suggestions, maxDistance);
        }
    }

    // Calculates the minimum edit distance between two strings
    int Distance(const string& s1, const string& s2) {
        int m = s1.length();
        int n = s2.length();
        
        vector<int> dp(n + 1);
        vector<int> prev_dp(n + 1);

        for (int j = 0; j <= n; j++) {
            prev_dp[j] = j;
        }

        for (int i = 1; i <= m; i++) {
            dp[0] = i; 
            for (int j = 1; j <= n; j++) {
                int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;

                dp[j] = min({
                    dp[j - 1] + 1,          
                    prev_dp[j] + 1,         
                    prev_dp[j - 1] + cost   
                });
            }
            prev_dp = dp;
        }
        return prev_dp[n];
    }
};




int main() {



    
    return 0;
}

