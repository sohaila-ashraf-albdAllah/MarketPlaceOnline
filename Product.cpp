#include "Product.h"

int Product::getRate() const {
	return rate.getRate();
}

Product::Product(int Id, const std::string& name,
	const std::string categoryName,
	double price, int sellerId, int quantity)
	: id(Id), name(name), categoryName(categoryName),
	price(price), sellerID(sellerId), quantity(quantity) {}

