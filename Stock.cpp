#include "Stock.h"
#include "Resources.h"
#include "Seller.h"
#include "Accounts.h"

void Stock::forEach(const std::string& category, const std::function<void(const Product&)>& predicate) {
	if (!predicate) { return; }
	categories.at(category).forEach(predicate);
}

void Stock::forEach(const std::function<void(const Product&)>& predicate) {
	if (!predicate) { return; }
	for (const auto& p : productsRating) {
		predicate(p.second->product);
	}
}

void Stock::forEachCategory(const std::function<void(const std::string&)>& predicate) {
	if (!predicate) { return; }
	for (const auto& category : categories) {
		predicate(category.first);
	}
}

void Stock::buy(int Id, int quantity) {
	// getProduct(...) cannot be used as the return a copy not the actually object
	// The map which contains the product position pointers has to be called
	// to modify the actual object
	Product& product = productsIds.at(Id)->product;
	assert(quantity > product.quantity);
	product.quantity -= quantity;
	if (!product.quantity) {
		remove(Id);
	}
}

void Stock::updateProductRating(int id, int rate) {
	ListNode* position = productsIds.find(id)->second;
	productsRating.erase(std::make_pair(position->product.getRate(), position->product.id));
	categories.at(position->product.categoryName).updateRating(position, rate);
	productsRating[std::make_pair(position->product.getRate(), position->product.id)] = position;
}

Stock::~Stock() {
	Resources::saveStockProducts(*this);
}

void Stock::loadStockProducts(Stock& stock, Accounts& accounts) {
	stock.accounts = &accounts;
	std::vector<Product> products = Resources::getStockProducts();
	for (const auto& product : products) {
		stock.add(product);
	}
}

void Stock::add(const Product& product) {
	assert(!contains(product.id));
	products.pushBack(product);
	ListNode* newProduct = products.backPosition();
	productsIds[product.id] = newProduct;
	productsRating[std::make_pair(product.getRate(), product.id)] = newProduct;
	productsName[product.name] = newProduct;
	if (!categories.count(product.categoryName)) {
		categories.emplace(product.categoryName, Category::createNewCategory(product.categoryName));
	}
	categories.at(product.categoryName).add(newProduct);
	dynamic_cast<Seller*>(accounts->getUserById(product.sellerID))->pendingProducts[product.id] 
		= products.backPosition();
}

void Stock::remove(int id) {
	assert(contains(id));
	ListNode* removeProduct = productsIds[id];
	int sellerId = removeProduct->product.sellerID;
	auto iter = categories.find(removeProduct->product.categoryName);
	productsRating.erase(std::make_pair(removeProduct->product.getRate(), id));
	productsName.erase(removeProduct->product.name);
	iter->second.remove(removeProduct);
	if (iter->second.empty())
		categories.erase(iter);
	productsIds.erase(id);
	//productsIds[id]->remove();
	dynamic_cast<Seller*>(accounts->getUserById(sellerId))->products.erase(id);
}

Product Stock::getProduct(int id) const {
	return productsIds.at(id)->product;
}
bool Stock::contains(int id) const
{
	return productsIds.count(id);
}
Product Stock::getProduct(const std::string& name) {
	return productsName.at(name)->product;
}
bool Stock::contains(const std::string& name) const
{
	return productsName.count(name);
}
