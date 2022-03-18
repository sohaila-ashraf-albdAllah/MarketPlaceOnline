#pragma once

#include <iostream>
#include <vector>
#include "Product.h"

struct Receipt {
	std::vector<Product> recieptList;
	int customerId;
	int totalQuantitySold;
	double totalPrice;
};