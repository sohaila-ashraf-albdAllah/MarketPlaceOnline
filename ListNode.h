#pragma once
#include "Product.h"

class List;
class PendingProduct;

struct ListNode {
private:
	ListNode* previous = nullptr;
	ListNode* next = nullptr;
	friend List;
	friend PendingProduct;
public:
	Product product;

	void remove();
};