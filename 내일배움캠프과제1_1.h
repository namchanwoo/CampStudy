#pragma once


#include <iostream>

using namespace std;

// �հ� ��� �Լ�
int CalculateSum(const int arr[], int size) {
	int sum = 0;
	for (int i = 0; i < size; ++i) 
	{
		sum += arr[i];
	}
	return sum;
}

// ��� ��� �Լ�
double CalculateAverage(int sum, int size) {
	return static_cast<double>(sum) / size;
}
//
//int main() {
//	int n;
//	cout << "�迭�� ũ�⸦ �Է��ϼ���: ";
//	cin >> n;
//
//	// ���� �޸� �Ҵ����� �迭 ����
//	int* numbers = new int[n];
//
//	// ����ڷκ��� ���� �Է�
//	cout << n << "���� ���ڸ� �Է��ϼ���:" << endl;
//	for (int i = 0; i < n; ++i) {
//		cout << i + 1 << "��° ����: ";
//		cin >> numbers[i];
//	}
//
//	// �հ�� ��� ���
//	int sum = CalculateSum(numbers, n);
//	double average = CalculateAverage(sum, n);
//
//	// ��� ���
//	cout << "�հ�: " << sum << endl;
//	cout << "���: " << average << endl;
//
//	// ���� �޸� ����
//	delete[] numbers;
//
//	return 0;
//}
