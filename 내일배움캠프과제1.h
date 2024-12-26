#pragma once


#include <iostream>

using namespace std;

// 합계 계산 함수
int CalculateSum(const int arr[], int size) {
	int sum = 0;
	for (int i = 0; i < size; ++i) 
	{
		sum += arr[i];
	}
	return sum;
}

// 평균 계산 함수
double CalculateAverage(int sum, int size) {
	return static_cast<double>(sum) / size;
}
//
//int main() {
//	int n;
//	cout << "배열의 크기를 입력하세요: ";
//	cin >> n;
//
//	// 동적 메모리 할당으로 배열 생성
//	int* numbers = new int[n];
//
//	// 사용자로부터 숫자 입력
//	cout << n << "개의 숫자를 입력하세요:" << endl;
//	for (int i = 0; i < n; ++i) {
//		cout << i + 1 << "번째 숫자: ";
//		cin >> numbers[i];
//	}
//
//	// 합계와 평균 계산
//	int sum = CalculateSum(numbers, n);
//	double average = CalculateAverage(sum, n);
//
//	// 결과 출력
//	cout << "합계: " << sum << endl;
//	cout << "평균: " << average << endl;
//
//	// 동적 메모리 해제
//	delete[] numbers;
//
//	return 0;
//}
