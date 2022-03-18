#include "Cart.h"

Cart::Cart(Stock& stock, int customerId) : stock(stock), customerId(customerId) {}

void Cart::forEach(const std::function<void(const Product&)>& predicate) const {
    if (!predicate) { return; }
    for (const auto& p : products) {
        Product product = stock.getProduct(p.first);
        product.quantity = p.second;
        predicate(product);
    }
}

bool Cart::add(int id, int quantity) {
    Product p = stock.getProduct(id);
    if (quantity <= p.quantity) {
        products.insert(std::make_pair(id, quantity));
        return true;
    }
    return false;
}

void Cart::remove(int id) {
    products.erase(id);
}

bool Cart::changeProductQuantity(int id, int quantity) {
    if (products.count(id)) {
        Product p = stock.getProduct(id);
        if (quantity <= p.quantity) {
            products[id] = quantity;
            return true;
        }
    }
    return false;
}

std::optional<Receipt> Cart::buy() {
    if (products.empty()) { return {}; }

    for (const auto& it : products) {
        if (!stock.contains(it.first) || stock.getProduct(it.first).quantity < it.second) {
            return {};
        }
    }

    Receipt receipt;
    for (const auto& it : products) {
        stock.buy(it.first, it.second);
        Product product = stock.getProduct(it.first);
        product.quantity = it.second;
        receipt.recieptList.emplace_back(product);
        receipt.totalPrice = it.second * product.price;
        receipt.totalQuantitySold += it.second;
    }

    return receipt;
}

