#include "Seller.h"
#include "PendingProduct.h"

Seller::Seller(PendingProduct& pendingProduct, Stock& stock, int UserID, const std::string& name, const std::string& email, const std::string& password)
	: User(stock, UserID, name, email, password), pendingProduct(pendingProduct) {}

void Seller::forEachProducts(const std::function<void(const Product&)>& predicate) const {
	if (!predicate) { return; }
	for (const auto& p : products) {
		predicate(p.second->product);
	}
}

void Seller::forEachPendingProducts(const std::function<void(const Product&)>& predicate)const
{
	if (!predicate) { return; }
	for (const auto& p : pendingProducts) {
		predicate(p.second->product);
	}
}

void Seller::addPendingProduct(const Product& product)
{
	pendingProduct.add(product);
}

void Seller::changeProductQuantity(int id, int newQuantity)
{
	auto iter = products.find(id);
	assert(iter != products.end());
	iter->second->product.quantity = newQuantity;
}

void Seller::changePendingProductQuantity(int id, int newQuantity)
{
	auto iter = pendingProducts.find(id);
	assert(iter != pendingProducts.end());
	iter->second->product.quantity = newQuantity;
}

//void Seller::loadSellerProduct()
//{
//	pendingProduct.forEach([](const Product& product) -> void {////////////////////////
//		//std::cout << product.id << ' ' << product.name;
//		});
//}
//
//void Seller::loadSellerPendingProduct()
//{
//	pendingProduct.forEach([&](const Product& product) -> void {//////////////////////////
//		if (product.id == getId())
//		{
//			pendingProducts.emplace(product.id, &product);
//		}
//		});
//}
