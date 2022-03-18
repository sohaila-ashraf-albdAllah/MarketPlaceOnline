#include "Resources.h"
#include "Accounts.h"
#include "Admin.h"
#include "Seller.h"
#include "Customer.h"
#include "CsvFile.h"

static const char* const adminsFileName = "admins.csv";
static const char* const customersFileName = "customers.csv";
static const char* const sellersFileName = "sellers.csv";
static const char* const pendingFileName = "pending.csv";
static const char* const stockProductFileName = "stock.csv";

static int mxId;

int Resources::getUsers(Accounts& accounts, Stock& stock, PendingProduct& pendingProducts) {
	// UserId, Name, Email, Password
	int mx = 0;
	auto data = CsvFile::readData(adminsFileName);
	for (const auto& userData : data) {
		assert((int)userData.size() == 4);
		Admin *admin = new Admin(pendingProducts, stock,
			std::stoi(userData[0]), userData[1], userData[2], userData[3]);
		mx = std::max(mx, admin->getId());
		assert(accounts.signUp(admin));
	}
	data = CsvFile::readData(sellersFileName);
	for (const auto& userData : data) {
		Seller* seller = new Seller(pendingProducts, stock,
			std::stoi(userData[0]), userData[1], userData[2], userData[3]);
		mx = std::max(mx, seller->getId());
		assert(accounts.signUp(seller));
	}
	data = CsvFile::readData(customersFileName);
	for (const auto& userData : data) {
		Customer* customer = new Customer(stock,
			std::stoi(userData[0]), userData[1], userData[2], userData[3], userData[4], userData[5]);
		mx = std::max(mx, customer->getId());
		assert(accounts.signUp(customer));
	}
	return mx + 1;
}

void Resources::saveUsers(Accounts& accounts) {
	std::vector<std::vector<std::string>> admins;
	std::vector<std::vector<std::string>> customers;
	std::vector<std::vector<std::string>> sellers;
	accounts.forEach([&](User* user) -> void {
		if (dynamic_cast<Admin*>(user)) {
			Admin *admin = dynamic_cast<Admin*>(user);
			admins.emplace_back(
				std::vector<std::string>({
					std::to_string(admin->getId()),
					admin->getName(), admin->getEmail(),
					admin->getPassword()
					}));
			return;
		}
		if (dynamic_cast<Seller*>(user)) {
			Seller *seller = dynamic_cast<Seller*>(user);
			sellers.emplace_back(
				std::vector<std::string>({
					std::to_string(seller->getId()),
					seller->getName(),
					seller->getEmail(),
					seller->getPassword()
					})
			);
			return;
		}
		if (dynamic_cast<Customer*>(user)) {
			Customer* customer = dynamic_cast<Customer*>(user);
			customers.emplace_back(
				std::vector<std::string>({
					std::to_string(customer->getId()),
					customer->getName(),
					customer->getEmail(),
					customer->getPassword(),
					customer->getAddress(),
					customer->getPhoneNumber()
					})
			);
			return;
		}
		assert(false);
	});
	CsvFile::writeData(adminsFileName, admins);
	CsvFile::writeData(customersFileName, customers);
	CsvFile::writeData(sellersFileName, sellers);
}


std::vector<Product> Resources::getPendingProducts() {
	std::vector<Product> row;
	auto data = CsvFile::readData(pendingFileName);
	//id name categoryName price quantity sellerId ratingIniTotal ratingIntCount 
	for (const auto& pendingData : data) {
		assert((int)pendingData.size() == 6);
		Product p;
		p.id = std::stoi(pendingData[0]);
		mxId = std::max(mxId, p.id);
		p.name = pendingData[1];
		p.categoryName = pendingData[2];
		p.price = std::stod(pendingData[3]);
		p.quantity = std::stoi(pendingData[4]);
		p.sellerID = std::stoi(pendingData[5]);
		//p.rate = Rating(std::stoi(pendingData[6]), std::stoi(pendingData[7]));
		row.push_back(p);
	}
	return row;
}

void Resources::savePendingProducts(PendingProduct& pendingProducts) {
	std::vector<std::vector<std::string>> pp;
	pendingProducts.forEach([&](const Product& products)->void {
		pp.emplace_back(std::vector<std::string>(
			{ 
				std::to_string(products.id),
				products.name,
				products.categoryName,
				std::to_string(products.price),
				std::to_string(products.quantity),
				std::to_string(products.sellerID)
			}));
	});
	CsvFile::writeData(pendingFileName, pp);
}

std::vector<Product> Resources::getStockProducts() {
	std::vector<Product> row;
	auto data = CsvFile::readData(stockProductFileName);
	//id name categoryName price quantity sellerid 
	for (const auto& stockData : data) {
		assert((int)stockData.size() == 8);
		Product p;
		p.id = std::stoi(stockData[0]);
		mxId = std::max(mxId, p.id);
		p.name = stockData[1];
		p.categoryName = stockData[2];
		p.price = std::stod(stockData[3]);
		p.quantity = std::stoi(stockData[4]);
		p.sellerID = std::stoi(stockData[5]);
		p.rate = Rating(std::stoi(stockData[6]), std::stoi(stockData[7]));
		row.push_back(p);
	}
	return row;
}

void Resources::saveStockProducts(Stock& stock) {
	std::vector<std::vector<std::string>> sp;
	stock.forEach([&](const Product& products)->void {
		sp.emplace_back(
			std::vector<std::string>({
				std::to_string(products.id),
				products.name,
				products.categoryName,
				std::to_string(products.price),
				std::to_string(products.quantity),
				std::to_string(products.sellerID),
				std::to_string(products.rate.getTotal()),
				std::to_string(products.rate.getCount())
				}));
		}
	);
	CsvFile::writeData(stockProductFileName, sp);
}

int Resources::getProductNextId() {
	return ++mxId;
}
