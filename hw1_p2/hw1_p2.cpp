#include "arithmetic.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>

bitset<32> hex2Binary(const string &hexa);
string bin2Hex(const bitset<32> &binary);
void printEncoded(const vector<bitset<32>> &encoded, bool console, string directory);
void getEncoded(vector<bitset<32>> *encoded, int size);

int main(int argc, char *argv[])
{
  Arithmetic A;
  if (string(argv[1]) == "-bin_to_dec" && argc > 2)
  {
    string hexa = string(argv[2]);
    bitset<32> binary = hex2Binary(hexa);
    cout << "The decimal representation is: " << A.binary_to_decimal(binary);
    return 0;
  }
  else if (string(argv[1]) == "-dec_to_bin" && argc > 2)
  {
    double dec = stod(argv[2]);
    bitset<32> binary = A.decimal_to_binary(dec);
    cout << "The binary representation: " << bin2Hex(binary);
    return 0;
  }

  if (string(argv[1]) == "-encode" && argc > 2)
  {
    vector<unsigned char> msg;
    int width = 0, height = 0;
    string intensity;
    int maxIntensity;
    int c;
    cin >> intensity >> width >> height >> maxIntensity;
    unsigned int msgSize = width * height;
    unsigned int totalNumBitsMsg = msgSize * 8;
    for (int i = 0; i < msgSize; i++)
    {
      int temp;
      cin >> temp;
      msg.push_back(temp);
    }
    // calc totalNum of bits in msg to get compression ratio
    // for (auto m : msg)
    // {
    //   totalNumBitsMsg += (int)log2(m) + 1;
    // }

    vector<bitset<32>> encoded;
    int num_symbols_per_block = atoi(argv[2]);
    int bitsCount = A.encode(msg, num_symbols_per_block, &encoded);
    bool console = true;
    string directory = "";
    if (argc > 3 && string(argv[3]) == "-ratio")
    {
      cout << "Compression ratio: " << totalNumBitsMsg / (double)bitsCount << " ";
      return 0;
    }
    else if (argc > 3 && string(argv[3]) == "-ratioWencode")
    {
      cout << "Compression ratio: " << totalNumBitsMsg / (double)bitsCount << " ";
    }
    else if (argc > 3 && string(argv[3]) == "-file")
    {
      console = false;
      directory = "./output/Encode/";
      if (argc > 4)
        directory += string(argv[4]) + "_Encode.pgm";
      else
        directory += "output_encode.pgm";
    }
    printEncoded(encoded, console, directory);
    A.printTable();
  }
  else if (string(argv[1]) == "-decode" && argc > 5)
  {
    int num_symbols_per_block = atoi(argv[2]);
    int xres = atoi(argv[3]);
    int yres = atoi(argv[4]);
    int max = atoi(argv[5]);
    vector<bitset<32>> encoded;
    getEncoded(&encoded, ceil((xres * yres) / (double)num_symbols_per_block));
    A.fillTable();
    vector<unsigned char> decoded;
    A.decode(encoded, num_symbols_per_block, &decoded);

    ofstream myfile;
    string directory = "./output/";
    if (argc > 6)
      directory += string(argv[6]) + ".pgm";
    else
      directory += "output.pgm";
    myfile.open(directory);
    myfile << "P2\n"
           << xres << " " << yres << "\n"
           << max << "\n";
    cout << endl;
    int endLine = 0;
    for (auto d : decoded)
    {
      myfile << (int)d << " ";
      endLine++;
      if (endLine % xres == 0)
      {
        myfile << "\n";
      }
    }
    myfile << "\n";
    myfile.close();
  }

  //For testing and debuging
  // double d = 0.703125;
  // bitset<32> b = A->decimal_to_binary(d);
  // string s = A->decimal_to_binary(d).to_string();
  // cout << s;
  // cout << endl;
  // cout << A->binary_to_decimal(b);
  // vector<unsigned char> msg = {'2', '2', '3', '1'};
  // vector<bitset<32>> encoded;
  // A->encode(msg, 2, &encoded);
  // vector<unsigned char> decoded;
  // A->decode(encoded, 2, &decoded);

  // for (auto e : decoded)
  // {
  //   cout << e << " ";
  // }
  // cout<<endl<<decoded.size();
  return 0;
}

string bin2Hex(const bitset<32> &binary)
{
  stringstream res;
  res << hex << uppercase << binary.to_ulong();
  string resStr = "0x";
  resStr += res.str();
  return resStr;
}

bitset<32> hex2Binary(const string &hexa)
{
  stringstream ss;
  ss << hex << hexa;
  unsigned n;
  ss >> n;
  bitset<32> binary(n);
  return binary;
}

void printEncoded(const vector<bitset<32>> &encoded, bool console, string directory)
{
  if (console)
  {
    for (auto e : encoded)
    {
      cout << e.to_ulong() << " ";
    }
  }
  else
  {
    ofstream myfile;
    myfile.open(directory);
    for (auto e : encoded)
    {
      myfile << e.to_ulong() << " ";
    }
    myfile.close();
  }
}

void getEncoded(vector<bitset<32>> *encoded, int size)
{
  if (size > 0)
  {
    while (size--)
    {
      unsigned int tagBinary;
      cin >> tagBinary;
      bitset<32> b(tagBinary);
      encoded->push_back(b);
    }
  }
}