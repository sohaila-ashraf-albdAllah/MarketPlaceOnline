#pragma once

class Rating {
private:
	int total;
	int count;
public:
	Rating();
	Rating(int iniTotal, int iniCount);
	int getTotal() const;
	int getCount() const;
	void update(int starsCount);
	int getRate() const;
	bool operator<(const Rating& other) const;
};


