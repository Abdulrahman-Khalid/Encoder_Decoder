#include "huffman.h"
#include <fstream>
#include <iostream>
#include <math.h>
//test huffman
void printEncoded(vector<unsigned int> encoded, bool console, string directory);

int main(int argc, char *argv[])
{
  // read parameters here ...

  // perform the required operation ...

  Huffman H;
  vector<unsigned char> msg;
  int width = 0, height = 0;
  string intensity;
  int maxIntensity;
  int c;
  cin >> intensity >> width >> height >> maxIntensity;
  for (int i = 0; i < width * height; i++)
  {
    int temp;
    cin >> temp;
    msg.push_back(temp);
  }
  vector<unsigned int> encoded;
  int argvIndex = 1;
  bool console = true; //print in console if true in file if false;
  string directory = "";
  if (string(argv[argvIndex]) == "-encode")
  {
    argvIndex++;
    if (argc > argvIndex && string(argv[argvIndex]) == "-diff")
    {
      argvIndex++;
      cout << "number of bytes: " << ceil(H.decorrelation(width, msg, &encoded) / 8.0) << endl; // /8 to get number of bytes
    }
    else
    {
      cout << "number of bytes: " << ceil(H.encode(msg, &encoded) / 8.0) << endl; // /8 to get number of bytes
    }
    if (argc > argvIndex && string(argv[argvIndex]) == "-file")
    {
      console = false;
      argvIndex++;
      directory = "./output/";
      if (argc > argvIndex)
        directory += string(argv[argvIndex]) + "_Encode.pgm";
      else
        directory += "output_encode.pgm";
    }

    H.print_code_table();
    printEncoded(encoded, console, directory);
  }
  else if (string(argv[1]) == "-entropy")
  {
    vector<Symbol> prob;
    cout << "Entropy = " << H.compute_entropy(msg, &prob);
  }
  else if (string(argv[1]) == "-tree")
  {
    vector<Symbol> prob;
    H.compute_entropy(msg, &prob);
    H.build_tree(prob);
    H.print_code_table();
  }
  // write output ...

  //huffman coding test
  // Huffman H2;
  // vector<unsigned char> msg = {'1', '2', '1', '1', '2', '1', '3', '3', '1', '2', '1', '2', '1', '2', '1', '3', '4', '1', '4', '1'};
  // vector<unsigned int> encoded;
  // H2.encode(msg, &encoded);
  // printEncoded(encoded);
  // cout << endl;
  return 0;
}

//test huffman
void printEncoded(vector<unsigned int> encoded, bool console, string directory)
{
  if (console)
  {
    for (auto e : encoded)
    {
      cout << e << " ";
    }
  }
  else
  {
    ofstream myfile;
    myfile.open(directory);
    int i = 0;
    for (auto e : encoded)
    {
      if (i % 256 == 0) // line has 256 unsigned char
        myfile << "\n";
      myfile << e << " ";
      i++;
    }
    myfile.close();
  }
}