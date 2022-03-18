#include "List.h"

void List::pushFront(const Product& product) {
	ListNode* new_Node = new ListNode;
	new_Node->product = product;
	if (head) {
		new_Node->next = head;
		head->previous = new_Node;
	}
	head = new_Node;
	if (!tail) {
		tail = head;
	}
}

void List::pushBack(const Product& product) {
	ListNode* new_Node = new ListNode;
	new_Node->product = product;
	if (tail) {
		new_Node->previous = tail;
		tail->next = new_Node;
	}
	tail = new_Node;
	if (!head) {
		head = tail;
	}
}

ListNode* List::frontPosition() const {
	return head;
}

ListNode* List::backPosition() const {
	return tail;
}

void List::forwardForEachPosition(const std::function<void(ListNode*)>& predicate) const {
	if (!predicate) { return; }
	for (ListNode* start = head; start; start = start->next) {
		predicate(start);
	}
}
void List::backwardForEachPosition(const std::function<void(ListNode*)>& predicate) const {
	if (!predicate) { return; }
	for (ListNode* finish = tail; finish; finish = finish->previous) {
		predicate(finish);
	}
}

List::~List() {
	forwardForEachPosition([](ListNode* listNode) -> void {
		listNode->remove();
	});
}

