#include "User.h"

bool User::checkPassword(const std::string& password) const
{
	return this->password == password;
}

std::string User::getEmail() const
{
	return email;
}

int User::getId() const
{
	return Id;
}

std::string User::getName() const
{
	return name;
}

std::string User::getPassword() const
{
	return password;
}

User::~User() {}

User::User(Stock& stock, int Id, const std::string& name, const std::string& email, const std::string& password) : stock (stock)
{
	this->Id = Id;
	this->name = name;
	this->email = email;
	this->password = password;
}
