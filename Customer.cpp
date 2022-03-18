#include "Customer.h"
#include "Stock.h"

Customer::Customer(Stock& stock, int Id, const std::string& name,
	const std::string& email, const std::string& password,
	const std::string& address, const std::string& phoneNumber)
	: User(stock, Id, name, email, password), cart(stock, Id), address(address), phoneNumber(phoneNumber) {}

void Customer::forEach(const std::function<void(const Product&)>& predicate) const {
	cart.forEach(predicate);
}

void Customer::addProduct(int Id, int quantity) {
	cart.add(Id, quantity);
}

bool Customer::changeProductQuantity(int Id, int quantity) {
	return cart.changeProductQuantity(Id, quantity);
}

void Customer::removeProduct(int Id) {
	cart.remove(Id);
}

std::optional<Receipt> Customer::buy() {
	return cart.buy();
}

std::string Customer::getAddress() const {
	return address;
}

std::string Customer::getPhoneNumber() const {
	return phoneNumber;
}
