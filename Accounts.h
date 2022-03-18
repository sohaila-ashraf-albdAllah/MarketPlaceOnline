#pragma once

#include <functional>
#include <string>
#include <map>
#include "User.h"

class Stock;
class PendingProduct;

class Accounts {
private:
	std::map<int, User*> usersIds;
	std::map<std::string, User*> usersAccount;
	User* current = nullptr;
	static int nextId;
public:
	static int getNextId();
	static void loadAccounts(Stock& stock, PendingProduct& pendingProducts, Accounts& accounts);
	bool contains(const std::string& email) const;
	void forEach(const std::function<void(User*)>& predicate) const;
	bool logIn(const std::string& email, const std::string& password);
	User* getCurrentUser() const;
	User* getUserById(int Id) const;
	bool signUp(User* newUser);
	void logOut();
	~Accounts();
};
