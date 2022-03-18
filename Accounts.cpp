#include <cassert>
#include "Accounts.h"
#include "Resources.h"

int Accounts::nextId;

int Accounts::getNextId() {
	return nextId++;
}

void Accounts::loadAccounts(Stock& stock, PendingProduct& pendingProducts, Accounts& accounts) {
	nextId = Resources::getUsers(accounts, stock, pendingProducts);
}

bool Accounts::contains(const std::string& email) const {
	return usersAccount.count(email);
}

void Accounts::forEach(const std::function<void(User*)>& predicate) const {
	if (!predicate) { return; }
	for (const auto& p : usersAccount) {
		predicate(p.second);
	}
}

bool Accounts::logIn(const std::string& email, const std::string& password) {
	if (usersAccount.count(email) && usersAccount.at(email)->checkPassword(password)) {
		current = usersAccount.at(email);
		return true;
	}
	return false;
}

User* Accounts::getCurrentUser() const {
	assert(current);
	return current;
}

User* Accounts::getUserById(int Id) const {
	return usersIds.at(Id);
}

bool Accounts::signUp(User* newUser) {
	if (!usersAccount.count(newUser->getEmail())) {
		usersAccount.emplace(newUser->getEmail(), newUser);
		usersIds.emplace(newUser->getId(), newUser);
		current = usersAccount.at(newUser->getEmail());
		return true;
	}
	return false;
}

void Accounts::logOut() {
	current = nullptr;
}

Accounts::~Accounts() {
	Resources::saveUsers(*this);
	forEach([](User* user) -> void {
		delete user;
	});
}
