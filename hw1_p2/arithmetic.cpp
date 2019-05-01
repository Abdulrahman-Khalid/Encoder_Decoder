// Your includes here
#include "arithmetic.h"
#include "bitset"
#include <math.h>
#include <unordered_map>
#include <iostream>
// Your implementations here

double Arithmetic::binary_to_decimal(const bitset<32> &fraction)
{
    double d = 0;
    string num = fraction.to_string();
    int bit;
    int power = -1;
    for (int i = 0; i < 32; i++, power--)
    {
        if (num[i] == '1')
            bit = 1;
        else
            bit = 0;
        d += (pow(2, power) * bit);
    }
    return d;
}

bitset<32> Arithmetic::decimal_to_binary(double fraction)
{
    bitset<32> b;
    int i = 32;
    b.reset();
    double r = fraction;
    while (i--)
    {
        r *= 2;
        if (r >= 1)
        {
            r -= 1;
            b.flip(i);
            if (!r)
                break;
        }
    }
    return b;
}

int Arithmetic::encode(const vector<unsigned char> &msg, int num_symbols_per_block, vector<bitset<32>> *encoded_msg)
{
    if (num_symbols_per_block <= 0 || msg.size() == 0) //check first
    {
        return 0;
    }

    unordered_map<unsigned char, unsigned long long> count;
    for (auto p : msg)
        count[p]++;
    long long totalPixelsNum = msg.size();
    tableSize = count.size();
    table = new row[tableSize];
    int tableIndex = 0;
    float l = 0;
    //make table
    for (pair<unsigned char, unsigned long long> distinctValue : count)
    {
        table[tableIndex].val = distinctValue.first;
        table[tableIndex].prob = distinctValue.second / (double)totalPixelsNum;
        table[tableIndex].range.l = l;
        table[tableIndex].range.u = table[tableIndex].range.l + table[tableIndex].prob;
        l = table[tableIndex].range.u;
        tableIndex++;
    }

    // encode
    int counter = 0;
    for (int i = 0; i < msg.size(); i++)
    {
        long double L = 0, U = 0;
        int j = num_symbols_per_block - 1;
        get_L_U(msg[i], L, U);
        long double tempL = L;
        long double tempU = U;
        while (j-- && i < msg.size())
        {
            i++;
            long double LL = 0, UU = 0;
            get_L_U(msg[i], LL, UU);
            L = tempL + (tempU - tempL) * LL;
            U = tempL + (tempU - tempL) * UU;
            tempL = L;
            tempU = U;
        }
        float tag = ((L + U) / 2.0);
        tags.push_back(tag);
        encoded_msg->push_back(decimal_to_binary(tag));
        if (U != L) // 1/0 runtime error
            counter += -ceil(log2((U - L))) + 1;
    }
    return counter;
}

void Arithmetic::get_L_U(unsigned char c, long double &L, long double &U)
{
    for (int i = 0; i < tableSize; i++)
    {
        if (table[i].val == c)
        {
            L = table[i].range.l;
            U = table[i].range.u;
            return;
        }
    }
}

void Arithmetic::decode(const vector<bitset<32>> &encoded_msg, int num_symbols_per_block, vector<unsigned char> *decoded_msg)
{
    // check
    if (encoded_msg.size() == 0 || num_symbols_per_block < 1)
    {
        return;
    }

    for (auto e : encoded_msg)
    {
        long double U = 1, L = 0;
        long double tempL = L, tempU = U;
        long double tag = binary_to_decimal(e);
        int j = num_symbols_per_block;
        while (j--)
        {
            row r = tStartToRow((tag - L) / (U - L));
            decoded_msg->push_back(r.val);
            L = tempL + (tempU - tempL) * r.range.l;
            U = tempL + (tempU - tempL) * r.range.u;
            tempL = L;
            tempU = U;
        }
    }
}

row Arithmetic::tStartToRow(double t)
{
    for (int i = 0; i < tableSize; i++)
        if (table[i].range.l <= t && table[i].range.u >= t)
            return table[i];
    return {};
}

void Arithmetic::printTable()
{
    cout << tableSize << " ";
    for (int i = 0; i < tableSize; i++)
    {
        cout << (int)table[i].val << " " << table[i].prob << " " << table[i].range.u << " " << table[i].range.l << endl;
    }
}

void Arithmetic::fillTable()
{
    cin >> tableSize;
    table = new row[tableSize];
    for (int i = 0; i < tableSize; i++)
    {
        int val;
        cin >> val;
        table[i].val = (unsigned char) val;
        cin >> table[i].prob >> table[i].range.u >> table[i].range.l;
        // cout << (int)table[i].val << " " << table[i].prob << " " << table[i].range.u << " " << table[i].range.l << endl;
    }
}