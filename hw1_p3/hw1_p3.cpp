// includes here
#include "lz77.h"
#include <iostream>
#include <fstream>

void printEncoded(const vector<Triplet> &encoded, bool console, string directory);
void printDecoded(vector<unsigned char> v);
void getEncoded(vector<Triplet> *encoded, int size);

int main(int argc, char *argv[])
{
  LZ77 L;
  if (string(argv[1]) == "-encode" && argc > 4)
  {
    int argvIndex = 2;
    vector<unsigned char> msg;
    int width = 0, height = 0;
    string intensity;
    int maxIntensity;
    int c;
    cin >> intensity >> width >> height >> maxIntensity;
    int msgSize = width * height;
    for (int i = 0; i < msgSize; i++)
    {
      int temp;
      cin >> temp;
      msg.push_back(temp);
    }
    bool callRegEncode = true;
    if (argc > argvIndex && string(argv[argvIndex]) == "-diff")
    {
      argvIndex++;
      callRegEncode = false;
    }
    vector<Triplet> encoded;
    int S = atoi(argv[argvIndex++]);
    int T = atoi(argv[argvIndex++]);
    int A = atoi(argv[argvIndex++]);
    int bitsCount;
    if (callRegEncode)
    {
      bitsCount = L.encode(msg, S, T, A, &encoded);
    }
    else
    {
      bitsCount = L.decorrelation(width, msg, S, T, A, &encoded);
    }

    string directory = "";
    bool console = true;
    if (argc > argvIndex && string(argv[argvIndex]) == "-ratio")
    {
      cout << "Compression ratio: " << (msgSize*8) / (double)bitsCount << " ";
      return 0;
    }
    else if (argc > argvIndex && string(argv[argvIndex]) == "-ratioWencode")
    {
      cout << "Compression ratio: " << (msgSize*8) / (double)bitsCount << " ";
    }
    else if (argc > argvIndex && string(argv[argvIndex]) == "-file")
    {
      argvIndex++;
      console = false;
      directory = "./output/Encode/";
      if (argc > argvIndex)
        directory += string(argv[argvIndex]) + "_Encode.pgm";
      else
        directory += "output_encode.pgm";
    }

    cout << encoded.size() << "\n";
    printEncoded(encoded, console, directory);
  }
  else if (string(argv[1]) == "-decode" && argc > 4)
  {
    int xres = atoi(argv[2]);
    int yres = atoi(argv[3]);
    int max = atoi(argv[4]);
    vector<Triplet> encoded;
    int size;
    cin >> size;
    unsigned pixelCount = xres * yres;
    L.setPixelCount(pixelCount);
    getEncoded(&encoded, size);
    vector<unsigned char> decoded;
    L.decode(encoded, &decoded);

    ofstream myfile;
    string directory = "./output/";
    if (argc > 5)
      directory += string(argv[5]) + ".pgm";
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

  // vector<unsigned char> msg = {'1', '1', '1', '1', '2', '1', '2', '1', '2', '1', '1', '1', '2'};
  // vector<Triplet> encoded;

  // LZ77 *cl = new LZ77;
  // int i = cl->encode(msg, 4, 4, 4, &encoded);

  // vector<unsigned char> decoded;
  // cl->decode(encoded, &decoded);
  // printDecoded(decoded);
  return 0;
}

/**
 * print encoded for both console and pipeline decoding (encode | decode)
 * No return
 * @param encoded vector which has encoded message 
*/
void printEncoded(const vector<Triplet> &encoded, bool console, string directory)
{
  if (console)
  {
    for (auto e : encoded)
      cout << e.j << " " << e.k << " " << (int)e.c << "\n";
  }
  else
  {
    ofstream myfile;
    myfile.open(directory);
    for (auto e : encoded)
      myfile << e.j << " " << e.k << " " << (int)e.c << "\n";
    myfile.close();
  }
}

/**
 * print decoded on console
 * No return
 * @param decoded vector which has decoded message 
*/
void printDecoded(vector<unsigned char> v)
{
  for (auto e : v)
    cout << e;
}

/**
 * get and fill encoded vector in pipeline decoding (encode | decode)
 * No return
 * @param encoded vector which has encoded message
 * @param size of encoded message 
*/
void getEncoded(vector<Triplet> *encoded, int size)
{
  if (size > 0)
  {
    while (size--)
    {
      Triplet t;
      int j, k, c;
      cin >> j >> k >> c;
      t.j = j;
      t.k = k;
      t.c = (unsigned char)c;
      encoded->push_back(t);
    }
  }
}