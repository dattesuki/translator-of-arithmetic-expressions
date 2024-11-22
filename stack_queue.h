//реализация ветктора
//выбрана реализация на динамическом массиве
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
template <typename T>
class Vector {
protected:
	T* pMem; //указатель на начало массива
	size_t sz; //количество элементов в векторе
	size_t capacity; //размер выделенной в данный момент памяти(максимальное кол-во элементов до перевыделения памяти)
public:
	Vector(size_t _capacity = 0) :sz(0), capacity(_capacity) {
		if (_capacity < 0) throw std::bad_alloc();
		if (capacity == 0) capacity = 10;
		pMem = new T[capacity];
		if (pMem == nullptr) throw std::bad_alloc();
	}

    Vector(Vector const &v) :sz(v.sz), capacity(v.capacity) {
		pMem = new T[capacity];
		if (pMem == nullptr) throw std::bad_alloc();
		std::copy(v.pMem, v.pMem+sz, pMem);
	}

	Vector(T* arr, size_t size_array):sz(size_array), capacity(size_array) {
		if (capacity <= 0) throw std::bad_alloc();
		pMem = new T[capacity];
		if (pMem == nullptr) throw std::bad_alloc();
		std::copy(arr, arr + (sz * sizeof(T)), pMem);
	}

    ~Vector(){
        delete[] pMem;
        pMem=nullptr;
    }
    
	size_t size() { return sz; }

	//перевыделение памяти
	void Overexpression() {
		T* temp_pMem = new T[(capacity*=2)];
		memcpy(temp_pMem, pMem, (capacity/2) * sizeof(T));
		delete[] pMem;
		pMem = temp_pMem;
	}

	bool IsFull() {
		return (sz == capacity);
	}

	bool IsEmpty() {
		return (sz == 0);
	}

	T& operator[](size_t n) {
		if (n < 0 || n >= capacity) throw std::logic_error("error");
		return pMem[n]; 
	}

	virtual void push_back(T el) {
		if (IsFull()) Overexpression();
		pMem[sz++] = el;
	}

    virtual void push_front(T el) {
		if (IsFull()) Overexpression();
		for (size_t i = 0; i < sz; ++i) pMem[i + 1] = pMem[i];
		pMem[0] = el;
		++sz;
	}

    virtual T back() {
		if (IsEmpty()) throw std::logic_error("error");
		return pMem[sz - 1];
	}

    virtual T front() {
		if (IsEmpty()) throw std::logic_error("error");
		return pMem[0];
	}

    virtual void pop_back() {
		if (IsEmpty()) throw std::logic_error("error");
		--sz;
	}

    virtual void pop_front() {
		if (IsEmpty()) throw std::logic_error("error");
		sz--;
		for (size_t i = 0; i < (sz); ++i) pMem[i] = pMem[i + 1];
	}
	
	void insert(T el, size_t ind) {
		if (ind < 0 || ind > sz) throw std::logic_error("error");
		if (IsFull()) Overexpression();
		for (size_t i = ind; i < sz; ++i) pMem[i + 1] = pMem[i];
		pMem[ind] = el;
		sz++;
	}

	std::vector<T> GetVector() {
		std::vector<T> temp;
		for (size_t i = 0; i < sz; ++i) {
			temp.push_back(pMem[i]);
		}
		return temp;
	}
};



template <typename T>
class Stack: public Vector<T> {
private:
	//переопределение незадействованных методов
	void push_front(T el) override{};
	void pop_front() override {};
	//T front() override { return T(); }
	void insert(T el, size_t ind) {};
	using Vector<T>::operator[];
public:
	Stack(size_t n=10) : Vector<T>(n) {};
	void push(T el) { this->push_back(el); }
	void pop() { this->pop_back(); }
	T get() { return this->back(); }
};


template <typename T>
class Queue : public Vector<T> {
private:
	size_t start = 0;
	size_t end = 0;
	//переопределение незадействованных методов
	using Vector<T>::operator[];
	void push_front(T el) override {};
	void pop_back() override {};
    void insert(T el, size_t ind) {};
	using Vector<T>::Overexpression;
public:
    Queue(int n = 10):Vector<T>(n) {};
	void push_back(T el) override {
		if (Vector<T>::IsFull()) throw std::logic_error("error");
		if (end < (Vector<T>::capacity - 1)) Vector<T>::pMem[end++] = el;
		else Vector<T>::pMem[end = 0] = el;
		++Vector<T>::sz;
	}
	
	void pop_front() override {
		if (Vector<T>::IsEmpty()) throw std::logic_error("error");
		if (start == (Vector<T>::capacity - 1)) start = 0;
		else ++start;
		--Vector<T>::sz;
	}
	
	T front() override{
		if (Vector<T>::IsEmpty()) throw std::logic_error("error");
		return Vector<T>::pMem[start];
	}
	T back() override { 
		if (Vector<T>::IsEmpty()) throw std::logic_error("error");
		return Vector<T>::pMem[end];
	}
	T get() { return this->front(); }
};


template <typename T>
class Queue2{
	Stack<T> stack1;
	Stack<T> stack2;
	size_t sz;
	size_t copacity;
public:
	Queue2(int n = 10) :stack1(n), stack2(n), sz(0), copacity(n) {}
	bool IsEmpty() {
		if (!(stack2.IsEmpty())) {
			return stack2.IsEmpty();
		}
		return stack1.IsEmpty();
	}
	void push_back(T el) { ++sz; stack1.push(el); }
	
	void pop_front() {
		T temp;
		if (IsEmpty()) throw std::logic_error("error");
		--sz;
		if (!stack2.IsEmpty()){
			stack2.pop();
		}
		else {
			while (!stack1.IsEmpty()) {
				temp = stack1.get();
				stack2.push(temp);
				stack1.pop();
			}
			stack2.pop();
		}
	}
	
    T back(){
        if (!stack1.IsEmpty()) return stack1.back();
        else if (!stack2.IsEmpty()) return stack2.front();
        throw std::logic_error("empty");
    }
    
	T front() {
		T temp;
		if (IsEmpty()) throw std::logic_error("error");
		if (!(stack2.IsEmpty())) {
			return stack2.get();
		}
		while (!(stack1.IsEmpty())) {
			temp = stack1.get();
			stack2.push(temp);
			stack1.pop();
		}
		return stack2.get();
	}
	size_t size() { return sz; }
	T get() { return front(); }
};

