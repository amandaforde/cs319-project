// CS319 SCIENTIFIC COMPUTING PROJECT
// FILE:            Cyclic_Friendship.cpp
// NAME:			Amanda Forde
// STUDENT ID NO.:	16308191
// EMAIL:			a.forde21@nuigalway.ie
// DATE:            06/04/2019

// To compile this programme, you will need Vector09.h, Vector09.cpp,
// Matrix09.h, Matrix09.cpp, Duplet.cpp and Duplet.h.
// This programme allows the user to create a cyclic network with shortcuts
// and to test the Friendship Paradox on this network.
// The user also has the option to a create a CSV file with the adjacency matrix
// of the cyclic network.


#include <iostream>
#include <iomanip>
#include <stdlib.h> // srand, rand
#include <fstream>  // For possible creation of CSV file with adjacency matrix
#include <string>
#include <time.h>   // time


#include "Vector09.h" // From 1819-CS319 Week 9
#include "Matrix09.h" // From 1819-CS319 Week 9
#include "Duplet.h"	  // Class for network storage, see Duplet.cpp for more details


unsigned int HowMany(Duplet D, unsigned int v);  // See below for definition of function


int main(void )
{

   std::cout << "CYCLIC NETWORK WITH SHORTCUTS AND THE FRIENDSHIP PARADOX\n" << std::endl;

   unsigned int N;
   unsigned int k;

   do {
   std::cout << "Enter the number of people, ie. vertices in cyclic network: ";
   std::cin >> N;}
   while (N < 3); // graph will not be cyclic if there are merely 1 or 2 points

   do {
   std::cout << "Enter the number of new 'friendships', ie. new edges in cyclic network: " ;
   std::cin >> k;
   }
   while (k > ((N*N) - 3*N)/2);
   // ensure value submitted by user is less than the maximum number of edges that can be added to a cyclic graph on N vertices


   srand(time(NULL));


   // Basic template for a cyclic network contained in a Duplet, ie. edges between each pair of adjacent vertices are recorded.
   // As graph is undirected, only required to contain each edge once, edge from [1] to [2] is equivalent to that from [2] to [1].
   Duplet D(N, N+k);

   D.setij(0,N-1);
   for (unsigned int i=1; i<N; i++)
     D.setij(i,i-1);   // see Duplet.cpp for definition of setij(i,j) function


   // New edges added randomly
    unsigned int edges = 0;
    while (edges < k)
    {
        unsigned int i = rand()%N;
        unsigned int j = rand()%N;
        // must ensure that edge doesn't already exist or an edge which loops a vertex to itself is not being created
        if ( i != j && D.whereij(i,j)== -1 )
        {
            D.setij(i,j);
            edges++;
        }
    }

    std::cout << "\nYour cyclic network of " << N << " vertices with " << k << " extra randomly added edges has been constructed!" << std::endl;


    // The following piece of code allows the user to decide if they want to create the adjacency matrix for the network. This
    // may be useful if the user wishes to view the network created online at website such as http://graphs.grevian.org/graph.
	// They must also use Adj2Dot.cpp to convert the CSV file to a dot file.
    char Adj;
    std::cout << "Do you wish to create the adjacency matrix for your cyclic network and store it in a CSV file? Y/N ";
    std::cin >> Adj;

    if (Adj == 'Y')
    {
        Matrix A(N);

        std::ofstream CSVFile;
        std::string FileName;

        A.zero(); // initialize it as a zero matrix, then we will add in our stored edges

		// if Duplet contains edge [1][2], this code inserts a '1' in A[1][2] and A[2][1], Duplet is iterated through
        for (unsigned int entry=0; entry<D.nnz_max(); entry++)
        {
            A.setij(D.getI(entry),D.getJ(entry), 1);
            A.setij(D.getJ(entry),D.getI(entry), 1);
        }

        std::cout << "What would you like to call the file? ";
        std::cin >> FileName;

        CSVFile.open(FileName.c_str()); // Open takes a "C string" argument
        for (unsigned int i=0; i<N; i++)
        {
            for (unsigned int j=0; j<N-1; j++)
            CSVFile <<  A.getij(i, j) << ",";
            CSVFile << A.getij(i,N-1) << std::endl;
        }

        CSVFile.close( ) ;
        std::cout << FileName << ".csv has been created. You can use this along with Adj2Dot.cpp and "
        << "http://graphs.grevian.org/graph to view your network." << std::endl;
    }



   // Find the total number of friends using HowMany(D,v) function for each vertex and adding up results
   unsigned int Friends=0;
   for(unsigned int v=0; v < N; v++)
    Friends += HowMany(D,v);

   double AveFriends = (double)Friends/(double)N; // divide total number of friends by total number of people

   std::cout << "\nThe average number of friends a person has in this network is: " << AveFriends << "." << std::endl;



	double totFofF=0;
	for (unsigned int v=0; v<N; v++)
	{
		Vector F(HowMany(D,v));  // Vector F created which will contain all of v's friends

		// loop for iterating through the Duplet to find where v exists
		// and then puts in its corresponding I/J entry, ie. its friend, into Vector F
		unsigned int f = 0;
		for (unsigned int iteration = 0; iteration < D.nnz_max(); iteration ++)
		{
			if (D.getI(iteration)==v)
				{(F.seti(f,D.getJ(iteration)));
				f++;}
			else if (D.getJ(iteration)==v) // Note: D.getI() will never be simultaneously equivalent to D.getJ()
				{(F.seti(f,D.getI(iteration)));
				f++;}
		}

		// Vector has been filled with all of v's friends, for each friend HowMany function implemented and results added up
		// to find how many friends of friends v has, then add this on to our running total of friends of friends
		int total=0;
		for (unsigned int j = 0; j < HowMany(D,v); j++)
		total+= HowMany(D,F.geti(j));

		totFofF += total;
	}

	double AveFofF = totFofF/(double)Friends; // divide total number of friends of friends by total number of friends

	std::cout << "The average number of friends of average friends a person has is: " << AveFofF << "." << std::endl;


	if (AveFofF > AveFriends)
    std::cout << "\nThis supports the idea of the Friendship Paradox as " << AveFofF << " is greater than " << AveFriends << "!"
      << std::endl;
	else if (AveFofF == AveFriends)
    std::cout << "\nThe two values are equivalent. All vertices must have the same number of friends!" << std::endl;
	else
    std::cout << "\nFriendship Paradox contradicted!" << std::endl; // Theoretically impossible, never happens no matter
    // how many different networks we try!


   return (0);
}



// Function: HowMany(D,v)
// Input: A Duplet and an individual vertex
// Output: The number of friends a vertex has, ie. the degree of the vertex
// This function counts the number of times the vertex appears in both the I and J vectors associated with Duplet.
// This is equivalent to the number of friends a vertex has. No vertex ever has an edge with itself so
// we never get D.getI(counter) == D.getJ(counter).
unsigned int HowMany(Duplet D, unsigned int v)
{
  unsigned int friends = 0;
   for (unsigned int counter = 0; counter < D.nnz_max(); counter++) // nnz_max is the 'size' of the Duplet
   {
       if (D.getI(counter) == v)
         {friends++;}
       else if (D.getJ(counter) == v)
         {friends++;}
   }

   return(friends);
}


