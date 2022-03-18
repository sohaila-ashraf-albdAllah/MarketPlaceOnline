#pragma once
#include <iostream>
#include <functional>
#include <optional>
#include <string>
#include "User.h"
#include "Cart.h"

class Stock;

class Customer : public User {
private:
	std::string address, phoneNumber;
	Cart cart;
public:
	Customer(Stock& stock, int Id, const std::string& name,
		const std::string& email, const std::string& password,
		const std::string& address, const std::string& phoneNumber);
	void forEach(const std::function<void(const Product&)>& predicate) const;
	void addProduct(int Id, int quantity);
	bool changeProductQuantity(int Id, int quantity);
	void removeProduct(int Id);
	std::optional<Receipt> buy();
	std::string getAddress() const;
	std::string getPhoneNumber() const;
};

