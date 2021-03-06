#include "pch.h"
#include <iostream>
#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template<typename T>
class Array
{
public:
	// (default) constructor
	Array(const size_t size = 0)
		: m_size(size)
		, m_array(m_size ? new T[m_size]() : nullptr)
	{
		std::cout << "default" << std::endl;
	}

	const size_t size() const
	{
		return m_size;
	}

	T& operator [](const size_t index)
	{
		assert(index < m_size);

		return m_array[index];
	}
	//конструктор копирования
	Array(const Array& copy) : m_size( copy.m_size ), m_array(m_size ? new T[m_size]() : nullptr)
	{	
		std::cout << "copy" << std::endl;
			std::copy(copy.m_array, copy.m_array + m_size, m_array);
	}
	//конструктор перемещения
	Array(Array&& move):m_array(std::move(move.m_array)), m_size(std::move(move.m_size))
	{
		std::cout << "move" << std::endl;
		move.m_array = nullptr;
		move.m_size = 0;
	}
	//оператор присваивания
	Array& operator=(Array& assignment)
	{
		std::cout << "assignment" << std::endl;
		if (&assignment == this) return *this;
		Array temp(assignment.m_size);
		try {
			std::copy(assignment.m_array, assignment.m_array + assignment.m_size, temp.m_array);
			delete[] m_array;
			m_size = assignment.m_size;
			m_array = temp.m_array;
			temp.m_array = nullptr;

		}
		catch (...) {
			delete[] temp.m_array;
			temp.m_array = nullptr;
			throw;
		}
		return *this;
	}
	~Array()
	{
		delete[] m_array;
		m_size = 0;
	}
private:
	size_t m_size;
	T* m_array;
};

int main()
{
	/*Array <int> a = Array <int>(4);
	std::cout << "________" << std::endl;
	Array <int> b(6);
	std::cout << "________" << std::endl;
	a = b;
	std::cout << "________" << std::endl;
	//a = Array <int>(8);
	//std::cout << "________" << std::endl;
	Array <int> c = a;
	std::cout << "________" << std::endl;
	Array <int> d = std::move(a);
	std::cout << "________" << std::endl;*/
	Array <int> a = Array <int>(4);
	for (int i = 0; i < 4; i++)
		a[i] = i;
	Array <int> d = std::move(a);
	std::cout <<"size d:"<< d.size() << std::endl;
	std::cout << "arr d:" << std::endl;
	for (int i = 0; i < d.size(); i++)
		std::cout << d[i] << " ";
	return 0;
}

