// Michael Mowad
// Project 6
// Database.h
// Header file for Database.cpp

#pragma once

#include <vector>

#include "HashTable.h"
#include "Record.h"
#include "Slot.h"

using namespace std;

class Database
{
private:

	HashTable* indexTable;
	vector<Record> recordStore;

public:

	Database();

	~Database();

	bool insert(const Record& newRecord, int& collisions);

	bool remove(int key);

	bool find(int uid, Record& foundRecord, int& collisions);

	float alpha();

	friend ostream& operator<<(ostream& os, const Database& database);
};