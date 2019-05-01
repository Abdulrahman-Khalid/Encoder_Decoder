// Your includes here
#include "lz77.h"
#include <math.h>
#include <iostream>
// Your implementations here

int LZ77::encode(const vector<unsigned char> &msg, int S, int T, int A, vector<Triplet> *encoded_msg)
{

    int separator = 0;
    while (separator < msg.size())
    {
        Triplet newTag = findLongestMatch(msg, separator, S, T);
        encoded_msg->push_back(newTag);
        separator += newTag.k + 1;
    }
    int bitsCount = encoded_msg->size() * (ceil(log2(S)) + ceil(log2(S + T)) + ceil(log2(A)));
    return bitsCount;
}

Triplet LZ77::findLongestMatch(const vector<unsigned char> &msg, int separator, int S, int T)
{
    // Max max = {separator + 1, 0};
    int startSearchBuffer = separator - S;
    int endLookAheadBuffer = separator + T - 1;
    startSearchBuffer = startSearchBuffer >= 0 ? startSearchBuffer : 0;
    endLookAheadBuffer = endLookAheadBuffer < msg.size() ? endLookAheadBuffer : msg.size() - 1;

    // unsigned int j = 0;
    // unsigned int len = 0;
    Triplet max = {0, 0, msg[separator]};
    for (int i = 1; i <= separator - startSearchBuffer; i++)
    {
        Triplet temp = {0, 0};
        int searchIndex = separator - i;
        int matchIndex = separator;
        while (startSearchBuffer <= searchIndex && endLookAheadBuffer >= searchIndex && matchIndex < msg.size())
        {
            if (msg[searchIndex] == msg[matchIndex])
            {
                temp.j = separator - searchIndex;
                searchIndex++;
                matchIndex++;
                temp.k++;
                break;
            }
            else
            {
                searchIndex--;
            }
        }
        while (startSearchBuffer <= searchIndex && endLookAheadBuffer >= searchIndex && matchIndex < msg.size())
        {
            if (msg[searchIndex] == msg[matchIndex])
            {
                searchIndex++;
                matchIndex++;
                temp.k++;
            }
            else
            {
                break;
            }
        }

        if (temp.k > max.k)
        {
            if (matchIndex < msg.size())
            {
                temp.c = msg[matchIndex];
            }
            max = temp;
        }
    }
    return {max.j, max.k, max.c};
}

void LZ77::decode(const vector<Triplet> &encoded_msg, vector<unsigned char> *decoded_msg)
{
    const int size = encoded_msg.size() - 1;

    //first tag
    decoded_msg->push_back(encoded_msg[0].c);
    //tags except last one <num,num, NULL>
    unsigned int i = 1;
    unsigned int decodedIndex = 1;
    while (i < size)
    {
        unsigned int startIndex = decodedIndex - encoded_msg[i].j;
        unsigned int endIndex = startIndex + encoded_msg[i].k;
        while (startIndex < endIndex)
        {
            decoded_msg->push_back(decoded_msg->at(startIndex));
            startIndex++;
        }
        decoded_msg->push_back(encoded_msg[i].c);
        decodedIndex = decoded_msg->size();
        i++;
    }

    //last tag
    unsigned int startIndex = decodedIndex - encoded_msg[i].j;
    unsigned int endIndex = startIndex + encoded_msg[i].k;
    while (startIndex < endIndex)
    {
        decoded_msg->push_back(decoded_msg->at(startIndex));
        startIndex++;
    }
    if (decoded_msg->size() < pixelCount)
    {
        decoded_msg->push_back(encoded_msg[i].c);
    }
}

void LZ77::setPixelCount(unsigned int size)
{
    pixelCount = size;
}

int LZ77::decorrelation(const int &width, const vector<unsigned char> &msg, int S, int T, int A, vector<Triplet> *encoded_msg)
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
    int numBits = encode(msgCpy, S, T, A, encoded_msg);

    return numBits;
}