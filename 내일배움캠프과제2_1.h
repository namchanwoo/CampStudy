#include <iostream>
#include <vector>
using namespace std;

// Animal 기본 클래스
class Animal {
public:
	// 순수 가상 함수: 각 동물의 소리를 정의
	virtual void makeSound() const = 0;

	// 소멸자 선언 (다형성을 위해 가상 소멸자로 설정)
	virtual ~Animal() {}
};

// Dog 클래스
class Dog : public Animal {
public:
	void makeSound() const override {
		cout << "멍멍 크르르를 으르르르릉!" << endl;
	}
};

// Cat 클래스
class Cat : public Animal {
public:
	void makeSound() const override {
		cout << "먀먀먀먀먀먀먀먀먀먀오오오오오오옹!" << endl;
	}
};

// Cow 클래스
class Cow : public Animal {
public:
	void makeSound() const override {
		cout << "음머머어어어어어" << endl;
	}
};

int main() {
	// Animal 타입의 포인터 배열 생성
	vector<Animal*> animals;

	// 각 동물 객체를 생성하고 배열에 추가
	animals.push_back(new Dog());
	animals.push_back(new Cat());
	animals.push_back(new Cow());

	// 배열을 순회하며 각 동물의 소리를 출력
	for (const Animal* animal : animals) {
		animal->makeSound();
	}

	// 동적 메모리 해제
	for (Animal* animal : animals) {
		delete animal;
	}

	return 0;
}
