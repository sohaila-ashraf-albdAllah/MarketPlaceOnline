#include "Admin.h"
#include <cassert>
#include "Accounts.h"

Admin::Admin(PendingProduct& pendingProducts, Stock& stock,
	int Id, const std::string& name, const std::string& email,
	const std::string& password)
	: User(stock, Id, name, email, password), pendingProducts(pendingProducts) {}

void Admin::approve(int Id) {
	assert(pendingProducts.contains(Id));
	Product temProduct = pendingProducts.getProduct(Id);
	stock.add(temProduct);
	pendingProducts.remove(Id);
}

void Admin::reject(int Id) {
	assert(pendingProducts.contains(Id));
	pendingProducts.remove(Id);
}