#pragma once

#include <functional>
#include <map>
#include "Stock.h"
#include <map>
#include "Reciept.h"
#include <optional>

class Cart {
private:
	int customerId;
	std::map<int, int> products;
	Stock& stock;
	
public:
	Cart(Stock& stock, int customerId);
	void forEach(const std::function<void(const Product&)>& predicate) const;
	bool add(int id, int quantity);
	void remove(int id);
	bool changeProductQuantity(int id, int quantity);
	std::optional<Receipt> buy();
};