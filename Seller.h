#pragma once

#include "User.h"
#include "ListNode.h"
#include <functional>
#include <map>

class Stock;
class PendingProduct;

class Seller : public User  {
private:
	friend Stock;
	friend PendingProduct;
	PendingProduct &pendingProduct;
	std::map<int, ListNode*> pendingProducts;
	std::map<int, ListNode*> products;

public:
	Seller(PendingProduct& PendingProduct,Stock& stock, int UserID, const std::string& name, const std::string& email, const std::string& password);
	void forEachProducts(const std::function<void(const Product&)>& predicate)const;
	void forEachPendingProducts(const std::function<void(const Product&)>& predicate)const;
	void addPendingProduct(const Product& product);
	void changeProductQuantity(int id,int newQuantity);
	void changePendingProductQuantity(int id, int newQuantity);
	/*void loadSellerProduct();
    void loadSellerPendingProduct();*/
};

