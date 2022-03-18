#pragma once

#include <functional>

#include "ListNode.h"

class List {
private:
	ListNode* head = nullptr;
	ListNode* tail = nullptr;
public:
	void pushFront(const Product& product);
	void pushBack(const Product& product);
	ListNode* frontPosition() const;
	ListNode* backPosition() const;
	void forwardForEachPosition(const std::function<void(ListNode*)>& predicate) const;
	void backwardForEachPosition(const std::function<void(ListNode*)>& predicate) const;
	~List();
};