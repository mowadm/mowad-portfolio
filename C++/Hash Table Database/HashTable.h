// Michael Mowad
// Project 6
// HashTable.h
// Header file for HashTable.cpp


#pragma once
#include "Slot.h"
#include <array>

using namespace std;

class HashTable 
{
private:
	const int MAXHASH = 20;
	array<int, 20> probeSequence;
	array<Slot*, 20> hash;
public:

	HashTable();

	~HashTable();

	bool insert(int key, int index, int& collisions);

	int probe(int key, int offset);

	bool remove(int key);

	bool find(int key, int& index, int& collisions);

	float alpha();

	int getIndex(int slot);

	friend ostream& operator<<(ostream& os, const HashTable& hashtable);
};