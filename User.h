#pragma once
#include <string>

class Stock;

class User {
private:
	int Id;
	std::string name, email, password;
public:
	bool checkPassword(const std::string& password) const;
	std::string getEmail() const;
	int getId() const;
	std::string getName() const;
	std::string getPassword() const;
	virtual ~User();
protected:
	Stock& stock;
	User(Stock& stock, int UserID, const std::string& name, const std::string& email, const std::string& password);
};