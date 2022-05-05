// File:     Matrix09.cpp (version: Week09)
// Author:   Niall Madden (NUI Galway) Niall.Madden@NUIGalway.ie
// Date:     Week 9 of 1819-CS319
// What:     Header file for Matrix class
// See also: Matrix09.h

#include <iostream>
#include "Vector09.h"
#include "Matrix09.h"

// Basic constructor. See below for copy constructor.
Matrix::Matrix (unsigned int Size)
{
  N = Size;
  entries = new double [N*N];
}

Matrix::~Matrix(void)
{
  delete [] entries;
}

void Matrix::setij (unsigned int i, unsigned int j, double x)
{
  if (i<N && j<N)
    entries[i*N+j]=x;
  else
    std::cerr << "Matrix::setij(): Index out of bounds." << std::endl;
}

double Matrix::getij (unsigned int i, unsigned int j)
{
  if (i<N && j<N)
    return(entries[i*N+j]);
  else
  {
    std::cerr << "Matrix::getij(): Index out of bounds." << std::endl;
    return(0);
  }
}

void Matrix::print (void)
{
//   std::cout << "Matrix is of size " << M << "-by-" << N << std::endl;
  for (unsigned int i=0; i<N; i++)
  {
    for (unsigned int j=0; j<N; j++)
      std::cout << "[" << entries[i*N+j] << "]";
    std::cout << std::endl;
  }
}


// Matrix copy constructor
Matrix::Matrix (const Matrix &m)
{
  N = m.N;
  entries = new double[N*N];
  for (unsigned int i=0; i<N*N; i++)
    entries[i] = m.entries[i];
}


// Overload the assignment = operator.
Matrix &Matrix::operator=(const Matrix &B)
{
  if (this == &B)
    return(*this); // Taking care for self-assignment

  delete [] entries; // Just in case there was any memory
  // already allocated to this

  entries = new double[(B.N)*(B.N)];
  for (unsigned int i=0; i<N*N; i++)
    entries[i] = B.entries[i];

  return(*this);
}

// Overload the operator multiplication (*) for a Matrix-Vector
// product. Matrix is passed implicitly as "this", the Vector is
// passed explicitly. Will return v=(this)*u
Vector Matrix::operator*(Vector u)
{
  Vector v(N); // v = A*w, where A is the implicitly passed Matrix
  if (N != u.size())
    std::cerr << "Error: Matrix::operator* - dimension mismatch"
	      << std::endl;
  else
    for (unsigned int i=0; i<N; i++)
    {
      double x=0;
      for (unsigned int j=0; j<N; j++)
	x += entries[i*N+j]*u.geti(j);
      v.seti(i,x);
    }
  return(v);
}


void Matrix::zero (void)
{
  for (unsigned int i=0; i<N; i++)
    for (unsigned int j=0; j<N; j++)
      entries[i*N+j] = 0.0;
}
