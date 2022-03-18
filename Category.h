#pragma once
#include <string>
#include <map>
#include <functional>
#include "ListNode.h"

class Stock;

class Category {
private:
	std::string name;
	std::map<std::pair<int, int>, ListNode*> products;
	Category(const std::string& name);
public:
	bool empty();
	void remove(ListNode* position);
	void updateRating(ListNode* position, int rate);
	void add(ListNode* newProductPosition);
	void forEach(const std::function<void(const Product&)>& predicate) const;
	std::string getName() const;
	static void loadCategories(Stock& stock);
	static Category createNewCategory(const std::string& name);
};
