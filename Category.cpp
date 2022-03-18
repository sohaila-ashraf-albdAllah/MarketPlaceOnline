#include "Category.h"
#include "Stock.h"

Category::Category(const std::string& name) : name(name) {}

bool Category::empty() {
	return products.empty();
}

void Category::remove(ListNode* position) {
	products.erase(std::make_pair(position->product.getRate(), position->product.id));
	position->remove();
}

void Category::updateRating(ListNode* position, int rate) {
	products.erase(std::make_pair(position->product.getRate(), position->product.id));
	position->product.rate.update(rate);
	products[std::make_pair(position->product.getRate(), position->product.id)] = position;
}

void Category::add(ListNode* newProductPosition) {
	products[std::make_pair(newProductPosition->product.getRate(),
		newProductPosition->product.id)] = newProductPosition;
}

void Category::forEach(const std::function<void(const Product&)>& predicate) const {
	if (!predicate) { return; }
	for (const auto& p : products) {
		predicate(p.second->product);
	}
}

std::string Category::getName() const {
	return name;
}

void Category::loadCategories(Stock& stock) {
	auto& categories = stock.categories;
	for (const auto& p : stock.productsRating) {
		ListNode* position = p.second;
		auto iter = categories.find(position->product.categoryName);
		if (iter == categories.end()) {
			Category category(position->product.name);
			categories.emplace(category.getName(), category);
		}
		iter->second.add(position);
	}
}

Category Category::createNewCategory(const std::string& name) {
	return Category(name);
}
