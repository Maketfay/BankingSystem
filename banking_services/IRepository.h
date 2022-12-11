#pragma once
template <class T>
class IRepository {
protected:

	std::vector<T*> repository;

	std::string filename;

	void virtual Build() = 0;

	void virtual UpdateDate() = 0;

};