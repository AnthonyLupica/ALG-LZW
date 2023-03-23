/*
   lzw.cpp

   driver for the lzw compression algorithm 
*/

#include "lzwAlgorithm.hpp"
#include <sstream> // std::stringstream

void compressionDriver(const std::string &filename);
void decompressionDriver();
bool isValidFileExtension(const std::string &filename, const std::string &extension);

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
         decompressionDriver();
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

   std::stringstream strStream;
   strStream << inFile.rdbuf(); //read the file
   std::string str = strStream.str(); //str holds the content of the file

   std::cout << str << "\n"; //you can do anything with the string!!!






   return;
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

void decompressionDriver()
{
   std::cout << "sup again";
}
 
