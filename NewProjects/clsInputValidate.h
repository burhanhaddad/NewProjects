#pragma once

#include<iostream>
#include<string>
#include"clsString.h"
#include"clsDate.h"

class clsInputValidate
{
public:
	static bool IsNumberBetween(short Number, short From, short To) {

		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}
	static bool IsNumberBetween(int Number, int From, int To) {

		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}
	static bool IsNumberBetween(float Number, float From, float To) {

		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}
	static bool IsNumberBetween(double Number, double From, double To) {

		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}



};

