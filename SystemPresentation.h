#pragma once

#include "Stock.h"
#include "PendingProduct.h"
#include "Accounts.h"
#include "Seller.h"
#include "Admin.h"
#include "Customer.h"

#include <iostream>

class SystemPresentation {
private:
	Stock stock;
	PendingProduct pendingProducts;
	Accounts accounts;
	int getNumber(const char* const message);
	int getNumberInRange(int end, const char* const message);
	bool isYes(const char* const message);
	void showLogin();
	void showSellerOptions();
	void showAdminOptions();
	std::optional<int> showProductsAndChosenId(const std::vector<Product>& products);
	void showCustomerOptions();
	void showCurrentUserOptions();
	void showProduct(const Product& product);
	void showCartOptions(Customer* customer);
	void showReceipt(const Receipt& receipt);
	void stockProducts(Seller* seller);
	void showPendingProductsOptions(Seller* seller);
	void addProduct(Seller* seller);
	double getDecimal(const char* const message);
	void signUp();
public:
	SystemPresentation();
	void start();
};
