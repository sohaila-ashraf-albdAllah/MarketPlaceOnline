#include "Rating.h"

#include <cassert>

Rating::Rating() : total(1), count(1) {}

Rating::Rating(int iniTotal, int iniCount) : total(iniTotal), count(iniCount) {}

void Rating::update(int starsCount) {
	//assert(1 <= starsCount && starsCount <= 5);
	total += starsCount;
	++count;
}

int Rating::getTotal() const {
	return total;
}

int Rating::getRate() const {
	return total / count;
}

int Rating::getCount() const {
	return count;
}

bool Rating::operator<(const Rating& other) const {
	return getRate() < other.getRate();
}

