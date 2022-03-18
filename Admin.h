#pragma once

#include "PendingProduct.h"
#include "Stock.h"
#include "User.h"

class Admin : public User {
private:
	PendingProduct &pendingProducts;
public:
	Admin(PendingProduct& pendingProducts,
		Stock& stock, int Id, const std::string& name,
		const std::string& email, const std::string& password);
	void approve(int Id);
	void reject(int Id);
};
