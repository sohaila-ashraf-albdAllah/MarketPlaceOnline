#pragma once
#include<iostream>
#include "Stock.h"
#include "product.h"
#include "User.h"
#include"Customer.h"
#include"PendingProduct.h"
#include<vector>
#include"Accounts.h"
#include"Seller.h"
#include"Admin.h"
#include"User.h"
class Presentation
{
private:
	Stock& stock;
	PendingProduct& pendingProduct;
	Accounts& accounts;
	Admin& admin;
public:
	Presentation(Stock& stock, PendingProduct& pendingProduct, Accounts& accounts, Admin& admin);
	void begin();
	void login();
	void signup();
	void sellerMenu(Seller* seller);
	void buyerMenu(Customer* customer);
	void adminMenu();
	void addProduct(Seller* seller);
	void searchByName();
	void searchByCategory();
	void showProduct(const Product& product);
	//void addproduct();
	//std::vector<Product>sellerPendingProducts(const Product & product)const;
};

