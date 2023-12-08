#pragma once
#include <string>
#include <iostream>
struct File {
	int Hash;
	std::string Name;
	File* next;
	File(std::string name, int hash ) {
		Name = name;
		Hash = hash;
		next = nullptr;
	}

	bool operator>( File& file) {
		std::cout << ">";
		return Hash > file.Hash;
	}
	bool operator<( File& file) {
		std::cout << "<";
		return Hash < file.Hash;
	}
	bool operator == ( File& file) {
		std::cout << "==";
		return Hash == file.Hash;
	}

	bool operator <= ( File& file) {
		std::cout << "<=";
		return Hash <= file.Hash;
	}
	bool operator >= ( File& file) {
		std::cout << ">=";
		return Hash >= file.Hash;
	}
	friend std::ostream& operator<<(std::ostream& os,const File& obj) {
		os << obj.Hash;
		//os << "Name :" << obj.Name << "\nHash :" << obj.Hash;
		return os;
	}

};



