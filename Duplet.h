// CS319 SCIENTIFIC COMPUTING PROJECT
// FILE:            Duplet.h
// NAME:			Amanda Forde
// STUDENT ID NO.:	16308191
// EMAIL:			a.forde21@nuigalway.ie
// DATE:            06/04/2019

// Header File for Duplet Class, defines Duplet class

#ifndef _DUPLET_H_INCLUDED
#define _DUPLET_H_INCLUDED

#include "Vector09.h"
#include "Matrix09.h"

class Duplet {

private:
  unsigned int *I, *J;
  unsigned int N;
  unsigned int NNZ;
  unsigned int NNZ_MAX;

public:
  Duplet (unsigned int N, unsigned int nnz_max); // Constructor
  Duplet (const Duplet &d); // Copy constructor
  ~Duplet(void);

  unsigned int size(void) {return (N);};
  unsigned int nnz(void) {return (NNZ);};
  unsigned int nnz_max(void) {return (NNZ_MAX);};

  int whereij (unsigned int i, unsigned int j);
  void setij (unsigned int i, unsigned int j);

  unsigned int getI (unsigned int k);
  unsigned int getJ (unsigned int k);

  void print(void);
};
#endif

