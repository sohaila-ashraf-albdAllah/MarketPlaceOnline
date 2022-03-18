#include "SystemPresentation.h"

SystemPresentation::SystemPresentation() : pendingProducts(stock) {
	Accounts::loadAccounts(stock, pendingProducts, accounts);
	Stock::loadStockProducts(stock, accounts);
	PendingProduct::loadPendingProducts(pendingProducts, accounts);
}

int SystemPresentation::getNumber(const char* const message) {
	while (true) {
		std::cout << message;
		std::string stringChoice;
		std::cin >> stringChoice;
		char* end;
		int choice = strtol(stringChoice.c_str(), &end, 10);
		int total = end - stringChoice.c_str();
		if (total != stringChoice.size()) {
			std::cout << "Input has to be a number.\n";
			continue;
		}
		return choice;
	}
}
int SystemPresentation::getNumberInRange(int end, const char* const message) {
	while (true) {
		int n = getNumber(message);
		if (1 <= n && n <= end) { return n; }
		std::cout << "Number has to be between 1 to " << std::to_string(end) << '\n';
	}
}
bool SystemPresentation::isYes(const char* const message) {
	std::cout << message << '\n';
	int choice = getNumberInRange(2, "1: Yes\n2: No\n");
	if (choice == 2) { return true; }
	return false;
}
void SystemPresentation::showLogin() {
	std::cout << "Log-in window\n";
	while (true) {
		std::string email, password;
		std::cout << "Email: ";
		std::cin >> email;
		std::cout << "Password: ";
		std::cin >> password;
		if (accounts.logIn(email, password)) {
			break;
		}
		std::cout << "Invalid credentials.\n";
		if (!isYes("Do you to try again ?")) {
			break;
		}
	}
}
void SystemPresentation::showSellerOptions() {
	Seller* seller = dynamic_cast<Seller*>(accounts.getCurrentUser());
	if (!seller) { return; }
	while (true) {
		std::cout << "1: Show Your Pending Products.\n";
		std::cout << "2: Show Your Stock Products.\n";
		std::cout << "3: Log-out\n";
		switch (getNumberInRange(3, "Choice: ")) {
		case 1:
			showPendingProductsOptions(seller);
			break;
		case 2:
			stockProducts(seller);
			break;
		case 3:
			accounts.logOut();
			return;
		}
	}
}

void SystemPresentation::showPendingProductsOptions(Seller* seller) {
	std::vector<Product> products;
	int order = 1;
	seller->forEachPendingProducts([&](const Product& product) -> void {
		std::cout << "Order: " << order++ << '\n';
		showProduct(product);
	});
	while (true) {
		std::cout << "1: Change quantity.\n";
		std::cout << "2: Add Product.\n";
		std::cout << "3: Return.\n";
		int nQuantity;
		int choice = getNumberInRange(3, "Choice: ");
		switch (choice) {
		case 1:
			order = getNumberInRange((int)products.size(), "Product Order: ");
			nQuantity = getNumber("New Quantity: ");
			seller->changePendingProductQuantity(products[order - 1].id, nQuantity);
			break;
		case 2:
			addProduct(seller);
			break;
		case 3:
			return;
		}
	}
}

void SystemPresentation::addProduct(Seller* seller) {
	std::string name, categoryName;
	int quantity; double price;
	std::cout << "Name: "; std::cin.ignore(); std::getline(std::cin, name);
	if (stock.contains(name)) {
		std::cout << "Product already exists.\n";
		return;
	}
	std::cout << "Category Name: "; std::cin.ignore(); std::getline(std::cin, categoryName);
	quantity = getNumberInRange(1000000, "Quantity: ");
	price = getDecimal("Price: ");
	pendingProducts.add(
		Product(Resources::getProductNextId(), name, categoryName, price, seller->getId(), quantity));
	std::cout << "Product added successfully.\n";
}

double SystemPresentation::getDecimal(const char* const message) {
	while (true) {
		std::cout << message << ": ";
		std::string stringChoice;
		std::cin >> stringChoice;
		char* end;
		double choice = strtod(stringChoice.c_str(), &end);
		int total = end - stringChoice.c_str();
		if (total != stringChoice.size()) {
			std::cout << "Input has to be a number.\n";
			continue;
		}
		return choice;
	}
}

void SystemPresentation::stockProducts(Seller* seller) {
	std::vector<Product> products;
	int order = 1;
	seller->forEachProducts([&](const Product& product) -> void {
		std::cout << "Order: " << order++ << '\n';
		showProduct(product);
	});
	while (true) {
		std::cout << "1: Change quantity.\n";
		std::cout << "2: Return.\n";
		int choice = getNumberInRange(2, "Choice: ");
		if (choice == 2) { return; }
		order = getNumberInRange((int)products.size(), "Product Order: ");
		int nQuantity = getNumber("New Quantity: ");
		seller->changeProductQuantity(products[order - 1].id, nQuantity);
	}
}

void SystemPresentation::showAdminOptions() {
	Admin* admin = dynamic_cast<Admin*>(accounts.getCurrentUser());
	if (!admin) { return; }
	std::vector<Product> products;
	int order = 1;
	pendingProducts.forEach([&](const Product& product) -> void {
		std::cout << "Order: " << order++ << '\n';
		showProduct(product);
	});
	while (true) {
		std::cout << "1: Approve.\n";
		std::cout << "2: Reject.\n";
		std::cout << "3: Log-out\n";
		int choice = getNumberInRange(3, "Choice: ");
		switch (choice) {
		case 1:
			order = getNumber("Product Order: ");
			admin->approve(products[order - 1].id);
			break;
		case 2:
			order = getNumber("Product Order: ");
			admin->reject(products[order - 1].id);
			break;
		case 3:
			accounts.logOut();
			return;
		}
	}
}
std::optional<int> SystemPresentation::showProductsAndChosenId(const std::vector<Product>& products) {
	int order = 1;
	for (const auto& product : products) {
		std::cout << "Order:\t" << order++ << '\n';
		showProduct(product);
		std::cout << '\n';
	}
	std::cout << "1: Choose Product.\n";
	std::cout << "2: Return.\n";
	if (getNumberInRange(2, "Choice: ") == 2) {
		return {};
	}
	return products[getNumberInRange((int)products.size(), "Product order number") - 1].id;
}
void SystemPresentation::showCustomerOptions() {
	Customer* customer = dynamic_cast<Customer*>(accounts.getCurrentUser());
	if (!customer) { return; }
	std::cout << "1: Search by name.";
	std::cout << "2: Show products by category.";
	std::cout << "3: Show all products.";
	std::cout << "4: Cart.";
	std::cout << "5: Log-out.";
	std::string name;
	std::vector<Product> products;
	std::optional<int> option;
	switch (getNumberInRange(5, "Choice: ")) {
	case 1:
		std::cout << "Name: ";
		std::cin.ignore();
		std::getline(std::cin, name);
		std::cout << "Choose product to add to cart\n";
		option = showProductsAndChosenId({ stock.getProduct(name) });
		if (option.has_value()) {
			int quantity = getNumber("Enter quantity: ");
			customer->addProduct(option.value(), quantity);
		}
		break;
	case 2:
		std::cout << "Name: ";
		std::cin.ignore();
		std::getline(std::cin, name);
		stock.forEach(name, [&](const Product& product) -> void { products.emplace_back(product); });
		std::cout << "Choose product to add to cart\n";
		option = showProductsAndChosenId(products);
		if (option.has_value()) {
			int quantity = getNumber("Enter quantity: ");
			customer->addProduct(option.value(), quantity);
		}
		break;
	case 3:
		stock.forEach([&](const Product& product) -> void { products.emplace_back(product); });
		std::cout << "Choose product to add to cart\n";
		option = showProductsAndChosenId(products);
		if (option.has_value()) {
			int quantity = getNumber("Enter quantity: ");
			customer->addProduct(option.value(), quantity);
		}
		break;
	case 4:
		showCartOptions(customer);
		break;
	case 5:
		accounts.logOut();
		break;
	default:
		assert(false);
	}
}
void SystemPresentation::showCurrentUserOptions() {
	showAdminOptions();
	showCustomerOptions();
	showSellerOptions();
}
void SystemPresentation::showProduct(const Product& product) {
	std::cout << "Name:\t" << product.name << '\n';
	std::cout << "Category Name:\t" << product.categoryName << '\n';
	std::cout << "Price:\t" << product.price << '\n';
	std::cout << "Quantity:\t" << product.quantity << '\n';
	std::cout << "Rating:\t" << product.getRate() << '\n';
}
void SystemPresentation::showCartOptions(Customer* customer) {
	std::vector<Product> products;
	int order = 1, nQuantity;
	customer->forEach([&](const Product& product) -> void {
		products.emplace_back(product);
		std::cout << "Order: " << order++ << '\n';
		showProduct(product);
	});
	std::cout << "1: Remove.\n";
	std::cout << "2: Change product quantity.\n";
	std::cout << "3: Buy.\n";
	std::cout << "4: Return.\n";
	switch (getNumberInRange(4, "Choice: ")) {
	case 1:
		order = getNumberInRange((int)products.size(), "Product Order: ");
		customer->removeProduct(products[order - 1].id);
		break;
	case 2:
		order = getNumberInRange((int)products.size(), "Product Order: ");
		nQuantity = getNumber("New quantity: ");
		customer->changeProductQuantity(products[order - 1].id, nQuantity);
		break;
	case 3:
		if (isYes("Are you sure?")) {
			auto result = customer->buy();
			if (!result.has_value()) {
				std::cout << "Purchasement cannot be completed.\n";
				break;
			}
			showReceipt(result.value());
		}
		break;
	}
}
void SystemPresentation::showReceipt(const Receipt& receipt) {
	std::cout << "Customer Id: " << receipt.customerId << '\n';
	std::cout << "Total quantity: " << receipt.totalQuantitySold << '\n';
	std::cout << "Total price" << receipt.totalPrice << '\n';
	for (const auto& product : receipt.recieptList) {
		showProduct(product);
	}
}

void SystemPresentation::signUp() {
	std::cout << "Choose your account type\n";
	std::cout << "1: Seller.\n";
	std::cout << "2: Customer.\n";
	int choice = getNumberInRange(2, "Choice: ");
	std::string name, email, password, phoneNumber, address;
	User* user;
	std::cout << "Name: "; std::cin >> name;
	std::cout << "Email: "; std::cin >> email;
	if (accounts.contains(email)) {
		std::cout << "Email already used.\n";
		return;
	}
	std::cout << "password: "; std::cin >> password;
	if (choice == 1) {
		user = new Seller(pendingProducts, stock, Accounts::getNextId(), name, email, password);
	} else {
		std::cout << "Phone number: "; std::cin >> phoneNumber;
		std::cout << "Address: "; std::cin >> address;
		user = new Customer(stock, Accounts::getNextId(), name, email, password, address, phoneNumber);
	}
	assert(accounts.signUp(user));
}

void SystemPresentation::start() {
	while (true) {
		std::cout << "Online Market System\n";
		std::cout << "1: Log-in\n";
		std::cout << "2: Sign-up\n";
		std::cout << "3: Exit\n";
		switch (getNumberInRange(3, "Choice: ")) {
		case 1:
			showLogin();
			showCurrentUserOptions();
			break;
		case 2:
			signUp();
			break;
		case 3:
			return;
		}
	}
}