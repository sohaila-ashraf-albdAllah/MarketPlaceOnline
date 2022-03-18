#include "ListNode.h"

void ListNode::remove() {
	previous->next = next;
	next->previous = previous;
	delete this;
}
