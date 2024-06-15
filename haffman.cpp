#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Haffman{

    struct Node{
        char word;
        string code;
        Node* left {nullptr};
        Node* right {nullptr};
        Node(char word_, string code_)
        {
            word = word_;
            code = code_;
        }
    };
    
    Node* HaffmanTree = nullptr;
    unordered_map<char, string>code;

private:
    Node* make_tree(Node* root, string code, const vector<pair<int, char>>& word, int iter)
    {
        root = new Node('#', code);
        if(iter >= word.size()) return nullptr;
   
        root->left = new Node(word[iter].second, code + '0');
    
    
        root->right = make_tree(root->right, code + '1', word, iter+1);
    
        return root;
    }

    Node* build_HaffmanTree(const string& text)
    {
        unordered_map<char, int>count;
        for(char u: text)
            count[u]++;

        vector<pair<int, char>>word(count.size());
        int iter = 0;
        for(auto u: count)
        {
            word[iter] = {u.second, u.first};
            iter++;
        }
        sort(word.begin(), word.end(), [](pair<int, char> x, pair<int, char> y){
            return x.first > y.first;
        });
    
        Node* tree = new Node(' ', "");
    
        tree = make_tree(tree, "", word, 0);
    
        return tree;
    }

    void get_code(Node* tree, unordered_map<char, string>& code)
    {
        if(!tree) return;
        if(!tree->left && !tree->right) {
            code[tree->word] = tree->code;
            return;
        }
        get_code(tree->left, code);
        get_code(tree->right, code);
        }

    char decode_letter(Node* root, const string& code, int& iter)
    {
        if(!root->left && !root->right) return root->word;
        
        if(code[iter] == '0') return decode_letter(root->left, code, ++iter);
        return decode_letter(root->right, code, ++iter);
    }

public:
    string encode(const string& text)
    {
        HaffmanTree = build_HaffmanTree(text);
        
        get_code(HaffmanTree, code);
        
        string encode_text = "";
        for(char u: text)
            encode_text += code[u];
        
        return encode_text;
    }

    string decode(const string& encode_text)
    {
        string decode_text = "";
        int iter = 0;
        while(iter < encode_text.size())
            decode_text += decode_letter(HaffmanTree, encode_text, iter);

        return decode_text;
    }

};


int main()
{
    cout << "Input text:";
    string text; cin >> text;
    Haffman haffman;
    string encode = haffman.encode(text);

    cout << "Letter codes\n";
    for(auto u: haffman.code)
    {
        cout << u.first << ' ' << u.second << '\n';
    }

    cout << "Encoded text:";
    cout << encode << '\n';

    cout << "Decoded text:";
    cout << haffman.decode(encode);
    return 0;
}