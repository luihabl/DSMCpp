#pragma once 

#include <iostream>
#include <initializer_list>
#include <cmath>
#include <string>

using namespace std;

namespace DSMCpp{

// TMatrix stands for template matrix
template <class T>
struct TMatrix
{
	size_t n1, n2, n3;
	T * m;

	TMatrix(const size_t _n1, const size_t _n2, const size_t _n3);
	TMatrix(const size_t _n1, const size_t _n2);
	TMatrix(const size_t _n1);
	TMatrix(const TMatrix & other);
	TMatrix(initializer_list<T> list);
	TMatrix();
	~TMatrix();

	TMatrix<T> & operator = (const TMatrix<T>& other);
    TMatrix<T> & operator = (initializer_list<T> list);
	
	T first();
	T last();
	void set_zero();
	void set_all(const T a);
	void set_sequence(T offset = 0);
	void multipy_all(const T a);
	void getbox(TMatrix<T> & box, int ilower, int jlower, int iupper, int jupper);
	void setbox(TMatrix<T> & box, int ilower, int jlower, int iupper, int jupper);
	void setbox_value(T value, int ilower, int jlower, int iupper, int jupper);
	TMatrix<T> getnewbox(int ilower, int jlower, int iupper, int jupper);
    double max();
    double min();

    static TMatrix<T> zeros(int n1, int n2 = 1, int n3 = 1);
    static TMatrix<T> linspace(double x_0, double x_1, int size = 50);
    static TMatrix<T> logspace(double e_0, double e_1, int size = 50);
	
};


// Constructors, operator overloadings and destructors

template <class T>
TMatrix<T>::TMatrix(const size_t _n1, const size_t _n2, const size_t _n3)
{

	n1 = _n1;
	n2 = _n2;
	n3 = _n3;

	m = new T[n1 * n2 * n3];

	// remove the zero value initialization to increase code speed?
	//this->set_zero();
}

template <class T>
TMatrix<T>::TMatrix(const size_t _n1, const size_t _n2)
{

	n1 = _n1;
	n2 = _n2;
	n3 = 1;

	m = new T[n1 * n2 * n3];

	//this->set_zero();
}


template <class T>
TMatrix<T>::TMatrix(const size_t _n1)
{

	n1 = _n1;
	n2 = 1;
	n3 = 1;

	m = new T[n1 * n2 * n3];

}

template <class T>
TMatrix<T>::TMatrix(initializer_list<T> list)
{
	typename initializer_list<T>::iterator it = list.begin();

	n1 = list.size();
	n2 = 1;
	n3 = 1;

	m = new T[n1 * n2 * n3];

	for (size_t i = 0; i < n1; i++)
		m[i] = *it++;
}

template <class T>
TMatrix<T>::TMatrix() { m = new T[0]; }


template <class T>
TMatrix<T>::TMatrix(const TMatrix & other)
{

	n1 = other.n1;
	n2 = other.n2;
	n3 = other.n3;

	m = new T[n1 * n2 * n3];

	for (size_t i = 0; i < n1 * n2 * n3; i++) m[i] = other.m[i];
}

template <class T>
TMatrix<T> & TMatrix<T>::operator = (const TMatrix<T>& other)
{
	if (this != &other) { // protect against invalid self-assignment

		n1 = other.n1;
		n2 = other.n2;
		n3 = other.n3;

		delete[](m);
		m = new T[n1 * n2 * n3];

		//*val = *(other.val);
		for (size_t i = 0; i < n1 * n2 * n3; i++) m[i] = other.m[i];

	}
	// by convention, always return *this
	return *this;
}

template <class T>
TMatrix<T> & TMatrix<T>::operator = (initializer_list<T> list)
{
    typename initializer_list<T>::iterator it = list.begin();
    
    for (size_t i = 0; i < n1 * n2 * n3; i++)
        m[i] = *it++;
    
    return *this;
}


template <class T>
TMatrix<T>::~TMatrix()
{
	delete[] m;
}

// Methods

template <class T>
void TMatrix<T>::set_zero() {
	for (size_t i = 0; i < n1 * n2 * n3; i++) m[i] = 0;
}

template <class T>
void TMatrix<T>::set_all(const T a)
{
	for (size_t i = 0; i < n1 * n2 * n3; i++) m[i] = a;
}

template <class T>
void TMatrix<T>::set_sequence(T offset)
{
	for (size_t i = 0; i < n1 * n2 * n3; i++) m[i] = offset + (int) i;
}


template <class T>
T TMatrix<T>::first()
{
	return m[0];
}

template <class T>
T TMatrix<T>::last()
{
	return m[n1 * n2 * n3 - 1];
}


template <class T>
TMatrix<T> TMatrix<T>::zeros(int n1, int n2, int n3)
{
    TMatrix<T> n(n1, n2, n3);
    n.set_zero();
    return n;
}

template <class T>
TMatrix<T> TMatrix<T>::linspace(double x_0, double x_1, int size)
{
    TMatrix<T> n(size);
    for (size_t i = 0; i < size; i++) {
        n.m[i] = i * (x_1 - x_0) / (size - 1) + x_0;
    }
    return n;
}

template <class T>
TMatrix<T> TMatrix<T>::logspace(double e_0, double e_1, int size)
{
    TMatrix<T> m(size);
    for (size_t i = 0; i < size; i++) {
        m.m[i] = pow(10, i * (e_1 - e_0) / (size - 1) + e_0);
    }
    
    return m;
}

template <class T> 
void TMatrix<T>::getbox(TMatrix<T> & box, int ilower, int jlower, int iupper, int jupper){
	for (int i = 0; i < iupper - ilower + 1; i++)
	{
		for (int j = 0; j < jupper - jlower + 1; j++)
		{
			box.m[i * box.n2 + j] = m[(i + ilower) * n2 + (j + jlower)];
		}
	}
}

template <class T> 
void TMatrix<T>::setbox(TMatrix<T> & box, int ilower, int jlower, int iupper, int jupper){
	for (int i = 0; i < iupper - ilower + 1; i++)
	{
		for (int j = 0; j < jupper - jlower + 1; j++)
		{
			m[(i + ilower) * n2 + (j + jlower)] = box.m[i * box.n2 + j];
		}
	}
}

template <class T> 
void TMatrix<T>::setbox_value(T value, int ilower, int jlower, int iupper, int jupper){
	for (int i = 0; i < iupper - ilower + 1; i++)
	{
		for (int j = 0; j < jupper - jlower + 1; j++)
		{
			m[(i + ilower) * n2 + (j + jlower)] = value;
		}
	}
}

template <class T>
TMatrix<T> TMatrix<T>::getnewbox(int ilower, int jlower, int iupper, int jupper)
{
    TMatrix<T> n(iupper - ilower + 1, jupper - jlower + 1);

    for (int i = 0; i < iupper - ilower + 1; i++)
	{
		for (int j = 0; j < jupper - jlower + 1; j++)
		{
			n.m[i * n.n2 + j] = m[(i + ilower) * n2 + (j + jlower)];
		}
	}
	return m;
}

template <class T>
double TMatrix<T>::max(){
    double v = m[0];
    for (size_t i = 1; i < n1 * n2 * n3; i++) if(v < m[i]) v = m[i];
    return v;
}

template <class T>
double TMatrix<T>::min(){
    double v = m[0];
    for (size_t i = 1; i < n1 * n2 * n3; i++) if(v > m[i]) v = m[i];
    return v;
}

// Type definitions

typedef TMatrix<double> DoubleMat;  //fmatrix stants for floating-point matrix
typedef TMatrix<int> IntMat;        //imatrix stants for integer matrix
typedef TMatrix<string> StrMat;     //imatrix stants for integer matrix

};

