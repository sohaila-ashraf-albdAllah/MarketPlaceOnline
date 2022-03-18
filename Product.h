#pragma once

#include <string>
#include "Rating.h"
#include "Resources.h"

class Category;
class Stock;

struct Product {
	friend std::vector<Product> Resources::getStockProducts();
	friend void Resources::saveStockProducts(Stock& stock);
	int id;
	std::string name;
	std::string categoryName;
	double price;
	int sellerID;
	int quantity;
	int getRate() const;
	Product() = default;
	Product(int Id, const std::string& name,
		const std::string categoryName, 
		double price, int sellerId, int quantity);
private:
	Rating rate;
	friend Category;
};
