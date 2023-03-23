/*
   lzw.cpp

   driver for the lzw compression algorithm 
*/

#include "lzwAlgorithm.hpp"
#include <sstream> // std::stringstream

void compressionDriver(const std::string &filename);
// void decompressionDriver();
bool isValidFileExtension(const std::string &filename, const std::string &extension);
void LZW_writeResult(const std::string &filename, const std::vector<int> &compressed);

int main(int argc, char* argv[]) 
{
   std::cout << " _______________________________________________________ " << std::endl;
   std::cout << "|                                                       |" << std::endl;
   std::cout << "| 3460:435/535 Algorithms Project Two - LZW Compression |" << std::endl;
   std::cout << "|_______________________________________________________|" << std::endl << std::endl;

   // validate # of command-line args
   if (argc != 3)
   {
      std::cerr << "Error: invalid invocation" << std::endl;
      std::cerr << "Required Format: ./lzw435 <c/e> <filename>" << std::endl;
      
      return 1;
   }

   char option = *(argv[1]);
   std::string filename(argv[2]);
   switch (option)
   {
      case 'c':
      case 'C':
         std::cout << "Option Select: compress '" << filename << "'\n\n";
         compressionDriver(filename);
         break;
      case 'e':
      case 'E': 
         std::cout << "Option Select: expand '" << filename << "'\n\n";
         // decompressionDriver();
         break;
      default:
         std::cerr << "Error: unrecognized option '" << option
                   << "'. Valid options are 'c' for compress, and 'e' for expand (decompression)" << std::endl;
         return 1;
   }

   // std::vector<int> compressed;
   // std::string example = "AAAAAAABBBBBB"; //example
   
   // // pass string to compress and a back_insert_iterator that inserts elements at the end of container "compressed".
   // compress(example, std::back_inserter(compressed));
   // for(auto itr=compressed.begin(); itr !=compressed.end(); itr++)
   // {
   //    std::cout<<"\n"<<*itr;
   // }
            
   // std::string decompressed = decompress(compressed.begin(), compressed.end());
   // std::cout << "\nfinal decompressed:" << decompressed << std::endl;

   // // demo as the name suggests
   // std::cout << "\n ---------- binary IO demo ----------- \n";
   // binaryIODemo(compressed);
   
   return 0;
}

void compressionDriver(const std::string &filename)
{
   // validate file is a .txt
   if (!isValidFileExtension(filename, ".txt"))
   {
      std::cerr << "Error: unsupported file extension" << std::endl;
      std::cerr << "Compression can only be performed on a text file" << std::endl;

      return;
   }
 
   //open the input file
   std::ifstream inFile;
   inFile.open(filename); 

   if (!inFile)
   {
      std::cerr << "Error: unable to open file '" << filename << "'\n";
      std::cerr << "Please ensure it is located in the same directory as the executable" << std::endl;

      return;
   }

   // read the contents of the file and store in string
   std::stringstream sstream;
   sstream << inFile.rdbuf();
   std::string inputTxt = sstream.str(); 

   // pass string to compress and a back_insert_iterator that inserts elements at the end of container "compressed".
   // std::vector<int> compressed holds the sequence of codes produced by LZW compression 
   std::vector<int> compressed;
   compress(inputTxt, std::back_inserter(compressed));

   // Binary IO to write compression results
   LZW_writeResult(filename, compressed);

   return;
}

void LZW_writeResult(const std::string &filename, const std::vector<int> &compressed) 
{
   // assuming length of code word is 12 bits 
   int bits = 12;

   std::string bCode = "";
   std::string bCodeTemp = "";
   for (std::vector<int>::const_iterator itr = compressed.begin() ; itr != compressed.end(); ++itr) 
   {
      // convert current code to bits and append to running string of full byte code string
      bCodeTemp = int2BinaryString(*itr, bits);
      bCode += bCodeTemp;
   }

   std::string zeros = "00000000";
   // make sure the length of the binary string is a multiple of 8
   if (bCode.size() % 8 != 0) 
   {
      // if not, pad with 0s
      bCode += zeros.substr(0, 8 - bCode.size() % 8);
   }

   /* WRITING TO FILE */

   // produce substring of filename with extension removed
   // assuming the file extension is ".txt", we know we don't want the final 4 characters
   std::string extensionlessFileName = filename.substr(0, filename.length() - 4);
   
   // derive file name target
   std::string derivedFileToWrite = extensionlessFileName + ".lzw"; 

   std::ofstream outFile;
   outFile.open(derivedFileToWrite.c_str(),  std::ios::binary);
   
   int byteValue; 
   for (int i = 0; i < bCode.size(); i += 8)
   { 
      byteValue= 1;
      for (int j = 0; j < 8; j++) 
      {
         byteValue = byteValue << 1;
         if (bCode.at(i+j) == '1')
         {
            byteValue += 1;
         }
      }
      char outputByte = (char) (byteValue & 255); // save the string byte by byte
      outFile.write(&outputByte, 1);  
   }
  
   outFile.close();
}

bool isValidFileExtension(const std::string &filename, const std::string &extension)
{
   // filename is shorter than or of the same length as the extension
   if (filename.length() <= extension.length())
   {
      return false;
   }

   // search for extension, starting at position where the extension begins
   if (filename.find(extension, filename.length() - extension.length()) == std::string::npos)
   {
      // the expected extension did not match
      return false;
   }

   return true;
}
