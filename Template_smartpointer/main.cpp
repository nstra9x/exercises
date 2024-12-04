#include <iostream>
#include <string>

template <class T>
class smart_ptr {
private:
	T* p = nullptr;
	int *ref_count = nullptr;
public:
	~smart_ptr() {
		if (ref_count && --(*ref_count) == 0) {  
			delete p;  
			delete ref_count; 
		}
	}

	explicit smart_ptr(T *ptr) {
		p = ptr;
		if (p) {
			ref_count = new int(1);
		}
	}

	smart_ptr& operator=(const smart_ptr& ptr) {
		if (this == &ptr)
			return *this;

		if (ref_count && --(*ref_count) == 0) {
			delete p;
			delete ref_count;
		}

		p = ptr.p;
		ref_count = ptr.ref_count;

		if (ref_count) {
			++(*ref_count);
		}

		return *this;
	}

	smart_ptr(const smart_ptr &ptr) {
		p = ptr.p;
		ref_count = ptr.ref_count;
		if (ref_count) {
			++(*ref_count);
		}
	}

	T* operator->() const {
		return p;
	}

	T& operator*() const {
		return *p;
	}

	void reset(T* newPtr = nullptr) {
		if (ref_count && --(*ref_count) == 0) {
			delete p;
			delete ref_count;
		}

		p = newPtr;
		if (p) {
			ref_count = new int(1);
		}
		else {
			ref_count = nullptr;
		}
	}

};

class People {
public:
	std::string name;
	int age;
	People(std::string name, int age) {
		this->name = name;
		this->age = age;
	}

	void showPeople() {
		std::cout << name << " is " << age << " years old.\n";
	}
};

int main() {
	smart_ptr<People> p1(new People("son", 30));
	p1->showPeople();

	smart_ptr<People> p2(p1);
	p2->showPeople();

	{
		smart_ptr<People> p3 = p2;
		p3->showPeople();
	}

	p2.reset();

	return 0;
}