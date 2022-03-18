#pragma once

#include <map>
#include <functional>
#include "List.h"
#include "Category.h"
#include <cassert>

class Accounts;

class Stock {
private:
	friend void Category::loadCategories(Stock& stock);

	List products;
	std::map<int, ListNode*> productsIds;
	std::map<std::pair<int, int>, ListNode*> productsRating;
	std::map<std::string, ListNode*> productsName;
	std::map<std::string, Category> categories;
	Accounts* accounts = nullptr;
	void remove(int id);
public:
	static void loadStockProducts(Stock& stock, Accounts& accounts);
	void add(const Product& product);

	//void remove(const std::string& name);
	//Product* getProduct(int id) const;
	Product getProduct(const std::string& name);
	Product getProduct(int id) const;
	bool contains(int id) const;
	bool contains(const std::string& name) const;
	//function to get products by category 
	void forEach(const std::string& category, const std::function<void(const Product&)>& predicate);
	void forEach(const std::function<void(const Product&)>& predicate);
	void forEachCategory(const std::function<void(const std::string&)>& predicate);
	void buy(int Id, int quantity);
	void updateProductRating(int id, int rate);
	//void buy(const std::string& name, int quantity);
	~Stock();
};