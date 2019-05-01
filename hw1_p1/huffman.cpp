#include "huffman.h"
#include "unordered_map"
#include "math.h"
#include <algorithm>
#include <iostream>
// Your implementations here
float Huffman::compute_entropy(const vector<unsigned char> &msg, vector<Symbol> *prob)
{
    unordered_map<unsigned char, unsigned long long> count;
    for (auto p : msg)
        count[p]++;
    long long totalPixelsNum = msg.size();
    float entropy = 0;
    for (pair<unsigned char, unsigned long long> distinctValue : count)
    {
        float probabilty = distinctValue.second / (float)totalPixelsNum;
        prob->push_back({distinctValue.first, probabilty});
        entropy += probabilty * log2(probabilty);
    }
    entropy *= -1;
    return entropy;
}

void Huffman::build_tree(const vector<Symbol> &prob)
{
    vector<Node> probCpy;
    for (auto e : prob)
        probCpy.push_back({e});
    auto sortByProb = [](const Node &a, const Node &b) { return a.s.p > b.s.p; }; // from bigger to smaller
    Node *n;
    while (probCpy.size() > 1)
    {
        sort(probCpy.begin(), probCpy.end(), sortByProb);
        Node *min1 = new Node;
        *min1 = probCpy.back();
        probCpy.pop_back();
        Node *min2 = new Node;
        *min2 = probCpy.back();
        probCpy.pop_back();

        n = new Node;

        n->s.p = min1->s.p + min2->s.p;
        n->right = min1;
        n->left = min2;

        probCpy.push_back(*n);
    }
    tree = n;

    const int MAX_TREE_HEIGHT = 256;
    unsigned char arr[MAX_TREE_HEIGHT];
    getCodeWord(tree, arr, 0);
}

void Huffman::getCodeWord(Node *n, unsigned char *arr, int index)
{
    if (n->left)
    {
        arr[index] = '1';
        getCodeWord(n->left, arr, index + 1);
    };

    if (n->right)
    {
        arr[index] = '0';
        getCodeWord(n->right, arr, index + 1);
    }

    if (!(n->left || n->right))
    {
        pair<unsigned char, vector<unsigned char>> pr;
        pr.first = n->s.val;
        vector<unsigned char> v(arr, arr + index);
        pr.second = v;
        codeWords.push_back(pr);
        return;
    }
}

int Huffman::encode(const vector<unsigned char> &msg, vector<unsigned int> *encoded_msg)
{
    compute_entropy(msg, &prob);
    build_tree(prob);
    int counter = 0;
    for (auto e : msg)
    {
        vector<unsigned char> v = getMsgCodeFromCodeWord(e);
        counter += v.size();
        encoded_msg->push_back(bitVectorToDecimal(v));
    }
    this->encoded_msg = encoded_msg;
    return counter;
}

int Huffman::bitVectorToDecimal(vector<unsigned char> v)
{
    int p = 0;
    int num = 0;
    for (int i = v.size() - 1; i >= 0; i--)
    {
        int b = (v[i] == '1') ? 1 : 0;
        num += pow(2, p) * b;
        p++;
    }
    return num;
}

vector<unsigned char> Huffman::getMsgCodeFromCodeWord(unsigned char m)
{
    for (auto c : codeWords)
        if (c.first == m)
            return c.second;
}

void Huffman::print_code_table()
{
    for (auto e : codeWords)
    {
        cout << (int)e.first << ' ';
        for (auto code : e.second)
        {
            if (code == '1')
                cout << 1;
            else
                cout << 0;
        }
        cout << endl;
    }
}

int Huffman::decorrelation(const int &width, const vector<unsigned char> &msg, vector<unsigned int> *encoded_msg)
{
    vector<unsigned char> msgCpy(msg);
    int i = 0;
    int j = 0;
    while (j < msg.size())
    {
        i++;
        j++;
        while (j < width * i)
        {
            msgCpy[j] = msg[j] - msg[j - 1];
            j++;
        }
    }
    int numBits =  encode(msgCpy, encoded_msg);
    return numBits;
}