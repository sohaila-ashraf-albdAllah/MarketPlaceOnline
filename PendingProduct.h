#pragma once
#include "List.h"
#include "Stock.h"
#include "Product.h"
#include "ListNode.h"
#include <map>
#include <vector>

class PendingProduct {
private:
    Stock& stock;
    List pendingProducts;
    std::map<int, ListNode*> pendingProductsIds;
    Accounts* accounts = nullptr;
public:
    static void loadPendingProducts(PendingProduct& pendingProducts, Accounts& accounts);
    PendingProduct(Stock& stock);
    bool contains(int id) const;
    void add(const Product& product);
    void remove(int id);
    void forEach(const std::function<void(const Product&)>& predicate) const;
    Product getProduct(int id);
    ~PendingProduct();
};