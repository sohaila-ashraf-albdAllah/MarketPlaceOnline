#include "Presentation.h"
Presentation::Presentation(Stock& stock, PendingProduct& pendingProduct, Accounts& accounts, Admin& admin)
	:stock(stock), pendingProduct(pendingProduct), accounts(accounts), admin(admin) {}
void Presentation:: begin()
{
	std::string check;
	std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
	std::cout << "\t\t\t\t\t\t\t\t\t Welcome to Our Online Marketing\t\t\t\t\t\t\t\t\t\n";
	std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
	do
	{
		std::cout << "Please Enter 1 To Signup Or 2 To Login Or 3 To exit : ";
		std::cin >> check;
		std::cout << "\n";
		if (check == "1")
		{
			signup();
		}
		else if (check == "2")
		{
			login();
		}
		else if (check == "3")
		{
			exit(0);
		}
	} while (true);
}
void Presentation:: login()
{
	std::string email, password;
		std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
		std::cout << "Please Enter E_mail : ";
		std::cin >> email;
		std::cout << "\n";
		std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
		std::cout << "Please Enter Password : ";
		std::cin >> password;
		std::cout << "\n";
		std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
		if (accounts.logIn(email,password))
		{
			//////////get account and dynmic;
		}
		else
		{
			std::cout << "Login Failed";
		}
}
void Presentation::signup()
{
	std::string name, email, password, check,address,phoneNumber;
	//int id = getNextId();
	do {
		std::cout << "Please Enter 1 To Be Seller Or 2 To Be Buyer : ";
		std::cin >> check;
		if (check == "1")
		{
			break;
		}
		else if (check == "2")
		{
			break;
		}
	} while(true);
	std::cout << "\n";
	std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
	std::cout << "Please Enter E_mail : ";
	std::cin >> email;
	std::cout << "\n";
	std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
	std::cout << "Please Enter Username : ";
	std::cin >> name;
	std::cout << "\n";
	std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
	std::cout << "Please Enter Password : ";
	std::cin >> password;
	std::cout << "\n";
	std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
	
	//if (!accounts.signUp())///////////////new user
	/*{
		std::cout << "Signup Failed ";
		return;
	}*/
	if (check == "1")
	{
		Seller seller(pendingProduct, stock, Accounts::getNextId(), name, email, password);
		if (!accounts.signUp(&seller)) {
			std::cout << "Signup Failed ";
			return;
		}
		sellerMenu(dynamic_cast<Seller*>(accounts.getUserById(seller.getId())));
	}
	else if (check == "2")
	{
		std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
		std::cout << "Please Enter Address : ";
		std::cin >> address;
		std::cout << "\n";
		std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
		std::cout << "Please Enter PhoneNumber : ";
		std::cin >> phoneNumber;
		std::cout << "\n";
		std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
		Customer customer(stock, Accounts::getNextId(), name, email, password, address, phoneNumber);
		if (!accounts.signUp(&customer)) {
			std::cout << "Signup Failed ";
			return;
		}
		buyerMenu(dynamic_cast<Customer*>(accounts.getUserById(customer.getId())));
	}
}
void Presentation:: sellerMenu(Seller* seller)
{
	std::string check;
	std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
	do
	{
		std::cout << "Please Enter 1 To Add New Product Or 2 To See Your Pending List Or 3 See Your Product List Or 4 To Logout : ";
		std::cin >> check;
		std::cout << "\n";
		std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
		if (check == "1")
		{
			addProduct(seller);
		}
		else if (check == "2")
		{
			seller->forEachPendingProducts([](const Product& product) -> void {
				std::cout << "id : " << product.id << "\n" << "Name : " << product.name << "\n" << "CategoryName : "
					<< product.categoryName << "\n" << "Price : " << product.price << "\n" << "Quantity : " << product.quantity << "\n";
				});
		}
		else if (check== "3")
		{
			seller->forEachProducts([](const Product& product) -> void {
				std::cout << "id : " << product.id << "\n" << "Name : " << product.name << "\n" << "CategoryName : "
					<< product.categoryName << "\n" << "Price : " << product.price << "\n" << "Quantity : " << product.quantity << "\n";
				});
		}
		else if (check == "4")
		{
			accounts.logOut();
			break;
		}
	} while (true);
}
void Presentation:: buyerMenu(Customer* customer)
{
	std::string check;
	std::cout << "Please Enter 1 To Browse The Market Or Enter 2 To Search By Name Or 3 To Search By Category Or 4 to add to cart Or 5 to buy the products in cart Or 6 To Logout : ";
	std::cin >> check;
	do {
		if (check == "1")
		{
			stock.forEach([&](const Product& product) -> void { showProduct(product); });
		}
		else if (check == "2")
		{
			searchByName();
		}
		else if (check == "3")
		{
			searchByCategory();
		}
		else if (check == "4")
		{
			accounts.logOut();
			break;
		}
	}while (true);

}
void Presentation::adminMenu()
{
	std::string check;
	int id;
	do
	{
		std::cout << "Please Enter 1 To See Pending Product List Or 2 To Logout : ";
		std::cin >> check;
		if (check == "1")
		{
			pendingProduct.forEach([](const Product& product) -> void {
				std::cout << "id : " << product.id << "\n" << "Name : " << product.name << "\n" << "CategoryName : "
					<< product.categoryName << "\n" << "Price : " << product.price << "\n" << "Quantity : " << product.quantity << "\n";
			});
			std::cout << "Please Enter 1 To Approve Or 2 To Reject : ";
			std::cin >> check;
			std::cout << "Please Enter Product Id : ";
			std::cin >> id;
			if (check == "1")
			{
				admin.approve(id);
			}
			else if (check == "2")
			{
				admin.reject(id);
			}
		}
		else if (check == "2")
		{
			accounts.logOut();
			break;
		}
	} while (true);
}
void Presentation::addProduct(Seller* seller)
{
	int Quantity;
	std::string name, categoryName;
	double price;
	std::cout << "Please Enter Product Name : ";
	std::cin >> name;
	if (!stock.contains(name))
	{
		std::cout << "This Prodoct Is Already Exist";
	    return;
    }
	std::cout << "\n";
	std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
	std::cout << "Please Enter Category Name : ";
	std::cin >> categoryName;
	std::cout << "\n";
	std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
	std::cout << "Please Enter Price : ";
	std::cin >> price;
	std::cout << "\n";
	std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
	std::cout << "Please Enter Quantity : ";
	std::cin >> Quantity;
	std::cout << "\n";
	std::cout << "The Product Is Successfully Added \n";
	seller->addPendingProduct(Product(Resources::getProductNextId(), name, categoryName, price, seller->getId(), Quantity));
}

void Presentation::searchByName()
{
	std::string name;
	std::cout << "Enter Product Name: ";
	std::cin >> name;
	if (stock.contains(name))
	{
		showProduct(stock.getProduct(name));
		//buy()
	}
	else
	{
		std::cout << "This Product Doesnot Exist! \n";
	}
}

void Presentation::searchByCategory()
{
	int categoryChoicesCount = 1;
	std::vector<std::string> categoriesNames;
	stock.forEachCategory([&](const std::string& categoryName) -> void {
		std::cout << categoryChoicesCount++ << "- " << categoryName << '\n';
		categoriesNames.emplace_back(categoryName);
	});
	int choice;
	while (true) {
		std::string stringChoice;
		std::cin >> stringChoice;
		char* end;
		choice = strtol(stringChoice.c_str(), &end, 10);
		if (choice == stringChoice.size() && 1 <= choice && choice <= (int)categoriesNames.size()) { break; }
	}
	stock.forEach(categoriesNames[choice - 1], [&](const Product& product) -> void {
		showProduct(product);
	});
}

void Presentation::showProduct(const Product& product)
{
	std::cout << "id : " << product.id << "\n" << "Name : " << product.name << "\n" << "CategoryName : "
		<< product.categoryName << "\n" << "Price : " << product.price << "\n" << "Quantity : " << product.quantity << "\n";
}

/*std::vector<Product> Presentation::sellerPendingProducts(const Product& product) const
{
	std::vector<Product>pendingProducts;
	if (product.sellerID == accounts.getCurrentUser()->getId())
	{
		pendingProducts.push_back(product);
	}
	return pendingProducts;
}*/
