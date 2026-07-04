#pragma once
#include<iostream>
#include<string>
using namespace std;
class clsPerson
{
private:
	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;
public:
	clsPerson(string FirsName, string LastName, string Email, string Phone) {

		_FirstName = FirsName;
		_LastName = LastName;
		_Email = Email;
		_Phone = Phone;
	}

	//property Set
	void SetFirstName(string FirstName){
		_FirstName = FirstName;
	}

	//property Get
	string GetFirstName() {
		return _FirstName;
	}

	_declspec(property(get = GetFirstName, put = SetFirstName))string FirstName;

	//property Set
	void SetLastName(string LastName) {
		_LastName = LastName;
	}

	//property Get
	string GetLastName() {
		return _LastName;
	}

	_declspec(property(get = GetLastName, put = SetLastName))string LastName;

	//property Set
	void SetEmail(string Email) {
		_Email = Email;
	}

	//property Get
	string GetEmail() {
		return _Email;
	}

	_declspec(property(get = GetEmail, put = SetEmail))string Email;

	//property Set
	void SetPhone(string Phone) {
		_Phone = Phone;
	}

	//property Get
	string GetEmail() {
		return _Phone;
	}

	_declspec(property(get = GetPhone, put = SetPhone))string Phone;

	string FullName() {
		return _FirstName + " " + _LastName;
	}
};

