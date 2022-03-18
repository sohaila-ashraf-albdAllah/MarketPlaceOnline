#pragma once

#include <vector>
#include "User.h"

class Accounts;
class PendingProduct;
struct Product;

namespace Resources {
	int getUsers(Accounts& accounts, Stock& stock, PendingProduct& pendingProducts);
	void saveUsers(Accounts& accounts);
	std::vector<Product> getPendingProducts();
	void savePendingProducts(PendingProduct& pendingProducts);
	std::vector<Product> getStockProducts();
	void saveStockProducts(Stock& stock);
	int getProductNextId();
}
