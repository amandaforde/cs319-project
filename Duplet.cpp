// CS319 SCIENTIFIC COMPUTING PROJECT
// FILE:            Duplet.cpp
// NAME:			Amanda Forde
// STUDENT ID NO.:	16308191
// EMAIL:			a.forde21@nuigalway.ie
// DATE:            06/04/2019

// Another version of a sparse matrix class, similar to Triplet.cpp.
// Used for storing the edges of undirected networks.
// Consists of two arrays, I[k] and J[k], in which for a given k, I[k]
// and J[k] represents an edge between I[k] and J[k]. It can be thought of
// storing all the non-zero values, which are assumed to be 1, of the
// adjacency matrix of the network. Class member functions are detailed below.


#include <iostream>
#include <iomanip>
#include "Vector09.h"
#include "Matrix09.h"
#include "Duplet.h"

// Standard  constructor.
Duplet::Duplet (unsigned int N, unsigned int nnz_max) {
  this->N = N;
  this->NNZ_MAX = nnz_max;
  this->NNZ = 0;

  I = new unsigned int [nnz_max];
  J = new unsigned int [nnz_max];
  for (unsigned int k=0; k<nnz_max; k++)  {
    I[k]=-1;
    J[k]=-1;
  }
}

// Duplet copy constructor
Duplet::Duplet (const Duplet &d)
{
  N = d.N;
  NNZ = d.NNZ;
  NNZ_MAX = d.NNZ_MAX;


  I = new unsigned int [NNZ_MAX];
  J = new unsigned int [NNZ_MAX];
  for (unsigned int k=0; k<NNZ; k++)
    I[k] = d.I[k];
  for (unsigned int k=0; k<NNZ; k++)
    J[k] = d.J[k];
}

// Duplet destructor
Duplet::~Duplet(void)
{
  delete [] I;
  delete [] J;
}

// Duplet implemented on undirected graph, each edge only stored once.
// Irrelevant if vertex1 is stored in I[k] and vertex2 is stored in J[k] or viceversa.
int Duplet::whereij(unsigned int i, unsigned int j)
{
  unsigned int k=0;
  do {
    if ( ((I[k]==i) && (J[k]==j)) || ((I[k]==j) && (J[k]==i)) ) // eg. want whereij(1,2) to return same value as whereij(2,1)
      return(k);
    k++;
  } while (k<NNZ);
  return(-1); // -1 is returned if edge is not stored
}

void Duplet::setij (unsigned int i, unsigned int j)
{
  if (i>N-1)
    std::cerr << "Duplet::setij(): i Index out of bounds." << std::endl;
  else if (j>N-1)
    std::cerr << "Duplet::setij(): j Index out of bounds." << std::endl;
  else if (NNZ > NNZ_MAX-1)
    std::cerr << "Duplet::setij(): Matrix full." << std::endl;
  else
  {
    int k=whereij(i,j); // must check edge is not already stored
    if (k == -1)
    {
      if (i<j)   // I[k],J[k] will be directly associated with the upper half of the adjacency matrix
        {I[NNZ]=i;
        J[NNZ]=j;}
      else
        {I[NNZ]=j;
        J[NNZ]=i;}
    NNZ++;
    }

    else
      I[k]=i;
      J[k]=j;
  }
}

void Duplet::print (void)   // used to display Duplet entries, returns pairs of vertices, corresponding to edges
{
  for (unsigned int k=0; k<NNZ; k++)
  {
    std::cout << "[" << std::setw(2) << I[k] << "]";
    std::cout << "[" << std::setw(2) << J[k] << "]" << std::endl;
  }
}


unsigned int Duplet::getI (unsigned int k)  // returns entry k in I array
{
    if (k < NNZ_MAX)
        return (I[k]);
    else {
        std::cerr << "Duplet::getI(): Index out of bounds." << std::endl;
        return(0);
    }
}

unsigned int Duplet::getJ (unsigned int k)  // returns entry k in J array
{
    if (k < NNZ_MAX)
        return (J[k]);
    else {
        std::cerr << "Duplet::getJ(): Index out of bounds." << std::endl;
        return(0);
    }
}
