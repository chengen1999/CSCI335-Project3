#ifndef DOUBLE_PROBING_H
#define DOUBLE_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>

namespace {

	// Internal method to test if a positive number is prime.
	bool IsPrimeDouble(size_t n) {
		if (n == 2 || n == 3)
			return true;

		if (n == 1 || n % 2 == 0)
			return false;

		for (unsigned int i = 3; i * i <= n; i += 2)
			if (n % i == 0)
				return false;

		return true;
	}


	// Internal method to return a prime number at least as large as n.
	int NextPrimeDouble(size_t n) {
		if (n % 2 == 0)
			++n;
		while (!IsPrimeDouble(n)) n += 2;
		return n;
	}

}  // namespace


// Linear probing implementation.
template <typename HashedObj>
class HashTableDouble {
public:
	enum EntryType { ACTIVE, EMPTY, DELETED };

	explicit HashTableDouble(size_t size = 101) : array_(NextPrimeDouble(size))
	{
		MakeEmpty();
	}

	bool Contains(const HashedObj& x) const {
		return IsActive(FindPos(x));
	}

	void MakeEmpty() {
		current_size_ = 0;
		for (auto& entry : array_)
			entry.info_ = EMPTY;
	}

	bool Insert(const HashedObj& x) {
		// Insert x as active
		size_t current_pos = FindPos(x);
		if (IsActive(current_pos))
			return false;

		array_[current_pos].element_ = x;
		array_[current_pos].info_ = ACTIVE;

		// Rehash; see Section 5.5
		if (++current_size_ > array_.size() / 2)
			Rehash();
		return true;
	}

	bool Insert(HashedObj&& x) {
		// Insert x as active
		size_t current_pos = FindPos(x);
		if (IsActive(current_pos))
			return false;

		array_[current_pos] = std::move(x);
		array_[current_pos].info_ = ACTIVE;

		// Rehash; see Section 5.5
		if (++current_size_ > array_.size() / 2)
			Rehash();

		return true;
	}

	bool Remove(const HashedObj& x) {
		size_t current_pos = FindPos(x);
		if (!IsActive(current_pos))
			return false;

		array_[current_pos].info_ = DELETED;
		return true;
	}



	//******************New Simple Functions******************
	//Number of Collisions 
	int NumOfCollisions() {
		return collision_amount;
	}

	// The size of table (T) 
	int getSize() {
		return array_.size();
	}

	// Total number of elements in the table(N)
	int NumOfElements() {
		return current_size_;
	}

	// The load factor (N/T)
	float LoadFactor() {
		return ((float)current_size_) / (array_.size());
	}

	//The average number of collisions(C / N).
	float AvgNumOfCollisions() {
		return ((float)collision_amount) / (current_size_);
	}

	void resetNumOfCollisions()
	{
		collision_amount = 0;
	}

private:
	struct HashEntry {
		HashedObj element_;
		EntryType info_;

		HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
			:element_{ e }, info_{ i } { }

		HashEntry(HashedObj&& e, EntryType i = EMPTY)
			:element_{ std::move(e) }, info_{ i } {}
	};

	// VARIABLES THAT WILL BE USED
	std::vector<HashEntry> array_;
	size_t current_size_;


	mutable size_t collision_amount;


	bool IsActive(size_t current_pos) const
	{
		return array_[current_pos].info_ == ACTIVE;
	}


	size_t FindPos(const HashedObj& x) const {
		size_t offset = InternalHashDouble(x);
		size_t current_pos = InternalHash(x);

		while (array_[current_pos].info_ != EMPTY &&
			array_[current_pos].element_ != x) {

			collision_amount++; // If that position of the hash table is not empty then their is a collision.

			current_pos += offset;  // Compute ith probe.			

			if (current_pos >= array_.size())
				current_pos -= array_.size();
		}

		return current_pos;
	}

	void Rehash() {
		std::vector<HashEntry> old_array = array_;

		// Create new double-sized, empty table.
		array_.resize(NextPrimeDouble(2 * old_array.size()));
		for (auto& entry : array_)
			entry.info_ = EMPTY;

		// Copy table over.
		current_size_ = 0;
		for (auto& entry : old_array)
			if (entry.info_ == ACTIVE)
				Insert(std::move(entry.element_));
	}

	size_t InternalHash(const HashedObj& x) const {
		static std::hash<HashedObj> hf;
		return hf(x) % array_.size();
	}

	//	New Internal Hash Function that applies R - (x mod R)
	//	Will be the offset
	size_t InternalHashDouble(const HashedObj& x) const{
		static std::hash<HashedObj> hf;
		return 101 - (hf(x) % 101);
		}
};

#endif  // LINEAR_PROBING_H
