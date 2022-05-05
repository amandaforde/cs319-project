// Adj2Dot.cpp 1819-CS319 Lab 7
//   What: Convert a graph, stored as an adjacency matrix in a csv file,
//         into a dot (GraphViz) file. You can then upload that to one of 
// http://graphs.grevian.org/graph
// http://www.webgraphviz.com or
// http://sandbox.kidstrythisathome.com/erdos/
// Author: Niall Madden

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream> // For files
#include <string> 
#include <sstream> // For manipulating string streams

int main(void)
{
  std::string AdjFileName;
  std::ifstream AdjFile;
  
  // Prompt the user  for the name of the file
  std::cout << "Enter the name of a \"csv\" file: " << std::endl;
  std::cin >> AdjFileName;
  
  AdjFile.open(AdjFileName.c_str());
  while (AdjFile.fail())
  {
    std::cerr << "Error - can't open file " << AdjFileName 
	      << ". Try again. " << std::endl;
    std::cout << "Enter the name of a \"csv\" file: " << std::endl;
    std::cin >> AdjFileName;
    AdjFile.open(AdjFileName.c_str());
  }
  
  // Check the number of rows in the file
  int N=0;
  char c;
  AdjFile.get(c);
  while(!AdjFile.eof())
  {
    if (c == '\n')
      N++;
    AdjFile.get(c);
  }
  
  std::cout << AdjFileName << " has " << N << " rows." << std::endl;
  
  // Should really check that there are the same number of rows
  //   but we are going to be a little lazy
  
  // Rewind...
  AdjFile.clear();
  AdjFile.seekg(std::ios::beg);
  
  // Now make the output file:
  std::string DotFileName  = AdjFileName;
  // Change ".csv" to ".gv"
  DotFileName[DotFileName.length()-3]='g';
  DotFileName[DotFileName.length()-2]='v';
  DotFileName[DotFileName.length()-1]='\0';
  
  std::cout << "Writing to " << DotFileName << std::endl;
  std::ofstream DotFile(DotFileName.c_str());
  if (DotFile.fail())
  {
    std::cout << "Error opening " << DotFileName << std::endl; 
    exit(EXIT_FAILURE);
  }
  
  DotFile << "digraph G {" << std::endl;
  for (int row=1; row<=N; row++)
  {
    DotFile << row << " -> {";
    for (int col=1; col<=N; col++)
    {	 
      AdjFile.get(c); // this should be a 0 or 1
      if (c == '1')
	DotFile << col << " ";
      AdjFile.get(c); // this should be a comma or '\n'
    }
    DotFile << "}" << std::endl;
  }
  DotFile << "}" << std::endl;

  AdjFile.close() ;
  DotFile.close();

  return (0);
}

