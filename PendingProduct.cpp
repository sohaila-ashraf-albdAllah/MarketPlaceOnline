
#include <cassert>
#include "PendingProduct.h"
#include "Resources.h"
#include "Accounts.h"
#include "Seller.h"

void PendingProduct::loadPendingProducts(PendingProduct& pendingProducts, Accounts& accounts) {
    pendingProducts.accounts = &accounts;
    std::vector<Product> products = Resources::getPendingProducts();
    for (const auto& product : products) {
        pendingProducts.add(product);
    }
}

PendingProduct::PendingProduct(Stock& stock) : stock(stock) {}

bool PendingProduct::contains(int Id) const {
    return pendingProductsIds.count(Id);
}

void PendingProduct::add(const Product& product) {
    assert(!stock.contains(product.id));
    pendingProducts.pushBack(product);
    pendingProductsIds[product.id] = pendingProducts.backPosition();
    dynamic_cast<Seller*>(accounts->getUserById(product.sellerID))->pendingProducts[product.id]
        = pendingProducts.backPosition();
}

void PendingProduct::remove(int Id) {
    assert(contains(Id));
    auto iter = pendingProductsIds.find(Id);
    dynamic_cast<Seller*>(accounts->getUserById(iter->second->product.sellerID))->
        pendingProducts.erase(Id);
    pendingProductsIds[Id]->remove();
    pendingProductsIds.erase(iter);
}

Product PendingProduct::getProduct(int Id) {
    assert(contains(Id));
    return pendingProductsIds[Id]->product;
}

PendingProduct::~PendingProduct() {
    Resources::savePendingProducts(*this);
}

void PendingProduct::forEach(const std::function<void(const Product&)>& predicate) const {
    if (!predicate) { return; }
    for (const auto& p : pendingProductsIds) {
        predicate(p.second->product);
    }
}

