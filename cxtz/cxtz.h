#pragma once

#include <iostream>

using namespace std;

#ifndef CXTZ
#define CXTZ
#endif

#ifdef SMALLOC
#define ALLOC SMALLOC
#define FREE SFREE
#else
#define ALLOC malloc
#define FREE free
#endif

template <class T>
class ChainSpot
{
	ChainSpot();
	~ChainSpot();
	void set(T value);
	T get();
	void setlast(ChainSpot* last);
	void setnext(ChainSpot* next);
private:
	T value;
	ChainSpot* lptr;
	ChainSpot* nptr;
};

template <class T>
class Chain
{
	friend class ChainSpot<T>;
public:
	Chain();
	~Chain();
	T get();
	void set(T v);
	unsigned long long int getsum();
	void setptr(unsigned long long int p);
	int getptr();
	void attend(T v);
	void sethead(ChainSpot<T> cs);
	void remove();
private:
	unsigned long long int ptr;
	unsigned long long int sum;
	ChainSpot<T> verychain;
	ChainSpot<T> headchain;
};

class Int
{
	//Little EndianµÄ´óÊý´æ´¢ÈÝÆ÷
public:
	Int();
	Int(Chain<int> *v);
	~Int();
	void set(Chain<int> *v);
	Chain<int>* get();
	Int* plus(Int* a);
	Int* minus(Int* a);
	Int* times(Int* a);
	Int* operator/(Int a);
	Int* operator++();
	Int* operator--();
	Int* operator%(Int a);
private:
	Chain<int> value;
};

class Cxtz
{
public:
	static void encrypt(Int ss, void* src, Int sd, void* det, Int key);
	static void decrypt(Int ss, void* src, Int sd, void* det, Int key);
	static Int random(Int rmax, Int seed);
};