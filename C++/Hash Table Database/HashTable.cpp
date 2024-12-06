// Michael Mowad
// Project 6
// HashTable.cpp
// HashTable class that handles the functioning of a 20 slot hash table


#include "HashTable.h"
#include "Record.h"
#include "Slot.h"
#include "hashfunction.h"
#include <algorithm>
#include <array>

using namespace std;


// Default Constructor
// Initializes Hash Table
HashTable::HashTable() {;
	// Iterates through to populate both the probeSequence with values and hash table with empty slots
	for (int i = 0; i < MAXHASH; i++) {
		probeSequence[i] = i;
		hash[i] = new Slot();
	}

	// Randomly shuffle probe sequence
	random_shuffle(probeSequence.begin(), probeSequence.end());
}

// Destructor
HashTable::~HashTable() {
	for (int i = 0; i < MAXHASH; i++) {
		delete hash[i];
	}
}

// Insert Function
// Params: key to insert, keys data index, collision reference
// Finds available slot to insert key and returns true, else returns false
bool HashTable::insert(int key, int index, int& collisions) {
	// Determine home index of key and set collisions to 0
	int home = jsHash(key) % MAXHASH;
	collisions = 0;

	// If home index available, load to that slot
	if (hash[home]->isEmpty()) {
		hash[home]->load(key, index);
		return true;
	}

	// Else collision happened must resolve with probing
	while (collisions < 20) {
		collisions += 1;
		int probeSlot = probe(key, collisions - 1);

		// If empty, insert
		if (hash[probeSlot]->isEmpty()) {
			hash[probeSlot]->load(key, index);
			return true;
		}
		// If deuplicate, return fasle
		else if (hash[probeSlot]->getKey() == key) {
			return false;
		}
	}

	// If thise point is reached, all slots have been probed without empty slot.
	// Return false
	return false;
	
}

// Probe Function
// Params: key to find, offset
// Determines probed index of hash table for given offset and key
int HashTable::probe(int key, int offset) {
	int slotIndex = ((jsHash(key) % MAXHASH) + probeSequence[offset]) % MAXHASH;
	return slotIndex;
}

// Remove Function
// Params: key to remove
// Searches hash table for key and deletes if found, else returns false
bool HashTable::remove(int key) {

	// Determine home index of key
	int home = jsHash(key) % MAXHASH;

	// If home is empty since start, return false
	if (hash[home]->isEmptySinceStart()) {
		return false;
	}

	// If home index matches, kill slot and return true
	if (hash[home]->getKey() == key) {
		hash[home]->kill();
		return true;
	}

	int offset = 0;
	// Else probe through list to find either entry or empty from start
	while (offset < 20) {
		int probeSlot = probe(key, offset);

		if (hash[probeSlot]->isEmptySinceStart()) {
			return false;
		}
		else if (hash[probeSlot]->getKey() == key) {
			hash[probeSlot]->kill();
			return true;
		}
		else {
			offset += 1;
		}
	}

	// If reaches here, list full but not containing key return false
	return false;
}

// Find Function
// Params: key to find, index reference, collisions counter
// Finds specified key in the table and sets index 
bool HashTable::find(int key, int& index, int& collisions) {
	index = -1;
	collisions = 0;

	// Determine home index of key
	int home = jsHash(key) % MAXHASH;

	// If home is empty since start, return false
	if (hash[home]->isEmptySinceStart()) {
		return false;
	}

	// If home index matches, return true
	if (hash[home]->getKey() == key) {
		index = hash[home]->getIndex();
		return true;
	}

	// Else probe through list to find either entry or empty from start
	while (collisions < 20) {
		collisions += 1;

		int probeSlot = probe(key, collisions - 1);

		if (hash[probeSlot]->isEmptySinceStart()) {
			return false;
		}
		else if (hash[probeSlot]->getKey() == key) {
			index = hash[probeSlot]->getIndex();
			return true;
		}
	}

	// If reaching here, list is full and not containing key return false
	return false;
}

// Alpha function
// Calculates and returns load factor of the table
float HashTable::alpha() {
	int notEmpty = 0;

	for (int i = 0; i < MAXHASH; i++) {
		if (hash[i]->isNormal()) {
			notEmpty += 1;
		}
	}

	float alpha = notEmpty / MAXHASH;

	return alpha;
}

// GetIndex Function
// Params: int slot number
// Given an input slot number, returns associated index if slot is not empty
int HashTable::getIndex(int slot) {
	if (hash[slot]->isNormal()) {
		return hash[slot]->getIndex();
	}
	else {
		return -1;
	}
}

// << operator
// prints contents of hash table
ostream& operator<<(ostream& os, const HashTable& hashtable) {
	for (int i = 0; i < hashtable.MAXHASH; i++) {
		if (hashtable.hash[i]->isNormal()) {
			Slot *slot = hashtable.hash[i];
			os << "HashTable Slot " << i << ": " << *slot << endl;
		}
	}
	return os;
}