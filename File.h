#pragma once
#include <string>
#include <iostream>
struct File {
	std::string Hash;
	std::string Path;
	File* next;
	File(std::string path, std::string hash) {
		Path = path;
		Hash = hash;
		next = nullptr;
	}

	bool operator>(File& file) {
		return Hash > file.Hash;
	}
	bool operator>(std::string hash) {
		return Hash > hash;
	}
	bool operator<(File& file) {
		return Hash < file.Hash;
	}bool operator<(std::string hash) {
		return Hash < hash;
	}
	bool operator == (File& file) {
		return Hash == file.Hash;
	}
	bool operator ==(std::string hash) {
		return Hash == hash;
	}
	bool operator <= (File& file) {
		return Hash <= file.Hash;
	}
	bool operator <= (std::string hash) {
		return Hash <= hash;
	}
	bool operator >= (File& file) {
		return Hash >= file.Hash;
	}
	bool operator >= (std::string hash) {
		return Hash >= hash;
	}
	friend std::ostream& operator<<(std::ostream& os, const File& obj) {
		os << obj.Hash << " " << obj.Path;
		return os;
	}

};



