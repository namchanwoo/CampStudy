#include <iostream>
#include <vector>
using namespace std;

// Animal �⺻ Ŭ����
class Animal {
public:
	// ���� ���� �Լ�: �� ������ �Ҹ��� ����
	virtual void makeSound() const = 0;

	// �Ҹ��� ���� (�������� ���� ���� �Ҹ��ڷ� ����)
	virtual ~Animal() {}
};

// Dog Ŭ����
class Dog : public Animal {
public:
	void makeSound() const override {
		cout << "�۸� ũ������ ����������!" << endl;
	}
};

// Cat Ŭ����
class Cat : public Animal {
public:
	void makeSound() const override {
		cout << "�ϸϸϸϸϸϸϸϸϸϿ�������������!" << endl;
	}
};

// Cow Ŭ����
class Cow : public Animal {
public:
	void makeSound() const override {
		cout << "���ӸӾ�����" << endl;
	}
};

int main() {
	// Animal Ÿ���� ������ �迭 ����
	vector<Animal*> animals;

	// �� ���� ��ü�� �����ϰ� �迭�� �߰�
	animals.push_back(new Dog());
	animals.push_back(new Cat());
	animals.push_back(new Cow());

	// �迭�� ��ȸ�ϸ� �� ������ �Ҹ��� ���
	for (const Animal* animal : animals) {
		animal->makeSound();
	}

	// ���� �޸� ����
	for (Animal* animal : animals) {
		delete animal;
	}

	return 0;
}
