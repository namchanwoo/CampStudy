#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>

template <typename T>
class Heap
{
public:
	using Compare = std::function<int(const T&, const T&)>;

	// 생성자
	Heap(Compare comp) : comp(comp)
	{
	}

	// 힙이 비어있는지 확인
	bool isEmpty() const
	{
		return heapArr.empty();
	}

	// 힙에 데이터 삽입
	void insert(const T& data)
	{
		heapArr.push_back(data);
		size_t idx = heapArr.size() - 1;

		while (idx > 0)
		{
			size_t parentIdx = getParentIdx(idx);

			// 데이터의 우선순위를 비교하여 자리 변경
			if (comp(data, heapArr[parentIdx]) > 0)
			{
				heapArr[idx] = heapArr[parentIdx];
				idx = parentIdx;
			}
			else
			{
				break;
			}
		}

		heapArr[idx] = data;
	}

	// 힙에서 데이터 삭제
	T remove()
	{
		// 1. 힙이 비어 있는지 확인
		// 힙이 비어 있으면 데이터를 삭제할 수 없으므로 예외를 던집니다.
		if (isEmpty())
		{
			throw std::underflow_error("Heap is empty!"); // 런타임 예외 발생
		}

		// 2. 반환할 데이터 (루트 노드) 저장
		// 힙의 특성상 루트 노드(첫 번째 요소)가 항상 최고 우선순위 데이터를 저장합니다.
		T retData = heapArr[0];

		// 3. 마지막 노드를 가져옵니다.
		// 마지막 노드는 삭제 후 힙을 재구성할 때 빈 자리를 채우는 데 사용됩니다.
		T lastElem = heapArr.back();

		// 4. 마지막 노드를 배열에서 제거
		// `std::vector`의 `pop_back()` 메서드를 사용하여 마지막 요소를 삭제합니다.
		heapArr.pop_back();

		// 5. 부모 노드 인덱스를 초기화
		// 힙의 재구성을 위해 루트 노드(인덱스 0)부터 시작합니다.
		size_t parentIdx = 0;

		// 6. 자식 노드 인덱스를 계산할 변수 선언
		// `getHigherPriorityChildIdx`를 통해 우선순위가 더 높은 자식 노드를 계산합니다.
		size_t childIdx;

		// 7. 힙 재구성 (다운힙 연산)
		// 우선순위가 높은 자식 노드를 찾아 내려가면서 힙 특성을 복원합니다.
		while ((childIdx = getHigherPriorityChildIdx(parentIdx)) != SIZE_MAX)
		{
			// 7.1. 마지막 노드와 자식 노드 비교
			// 만약 마지막 노드가 현재 자식 노드보다 우선순위가 높거나 같다면
			// 더 이상 자리를 교환할 필요가 없으므로 반복문을 종료합니다.
			if (comp(lastElem, heapArr[childIdx]) >= 0)
			{
				break;
			}

			// 7.2. 부모 노드에 자식 노드 값을 복사
			// 현재 부모 위치를 자식 노드 값으로 채웁니다.
			heapArr[parentIdx] = heapArr[childIdx];

			// 7.3. 부모 노드 인덱스를 자식 노드로 업데이트
			// 다음 반복에서 현재 자식 노드가 새로운 부모 노드가 됩니다.
			parentIdx = childIdx;
		}

		// 8. 마지막 노드를 최종 위치에 저장
		// 반복문이 종료되면 마지막 노드를 올바른 위치에 배치합니다.
		if (!heapArr.empty())
		{
			heapArr[parentIdx] = lastElem; // 마지막 요소를 이동된 부모 위치에 설정
		}

		// 9. 반환
		// 루트 노드에 있던 데이터를 반환합니다.
		return retData;
	}

protected:
	// 부모 노드 인덱스 계산
	size_t getParentIdx(size_t idx) const {
		return (idx - 1) / 2;
	}

	// 왼쪽 자식 노드 인덱스 계산
	size_t getLeftChildIdx(size_t idx) const {
		return idx * 2 + 1;
	}

	// 오른쪽 자식 노드 인덱스 계산
	size_t getRightChildIdx(size_t idx) const {
		return idx * 2 + 2;
	}

	// 우선순위가 더 높은 자식 노드의 인덱스 반환
	size_t getHigherPriorityChildIdx(size_t idx) const
	{
		size_t left = getLeftChildIdx(idx);
		size_t right = getRightChildIdx(idx);

		if (left >= heapArr.size())
		{
			return SIZE_MAX; // 자식 노드 없음
		}
		else if (right >= heapArr.size())
		{
			return left; // 왼쪽 자식만 존재
		}
		else
		{
			// 두 자식을 비교하여 더 높은 우선순위를 가지는 노드 반환
			return (comp(heapArr[left], heapArr[right]) > 0) ? left : right;
		}
	}

private:
	std::vector<T> heapArr; // 내부 배열로 힙 관리
	Compare comp;           // 우선순위 비교 함수	
};

int main() {
	// 사용자로부터 입력받을 데이터
	std::vector<int> inputData;
	int n;

	// 정렬할 숫자의 개수 입력
	std::cout << "정렬할 숫자의 개수를 입력하세요: ";
	std::cin >> n;

	// 숫자 입력
	std::cout << "숫자들을 입력하세요: ";
	for (int i = 0; i < n; ++i) {
		int value;
		std::cin >> value;
		inputData.push_back(value);
	}

	// 정렬 방식 선택
	int order;
	std::cout << "정렬 방식을 선택하세요 (1: 오름차순, 2: 내림차순): ";
	std::cin >> order;

	// 정렬 순서를 결정하는 우선순위 비교 함수
	Heap<int>::Compare comp = (order == 1)
		? [](int a, int b) -> int { return b - a; } : [](int a, int b) -> int { return a - b; };

	// 힙 생성
	Heap<int> heap(comp);

	// 데이터를 힙에 삽입
	for (int value : inputData) {
		heap.insert(value);
	}

	// 정렬 결과 저장
	std::vector<int> sortedData;

	// 힙에서 데이터를 꺼내 정렬
	while (!heap.isEmpty()) {
		sortedData.push_back(heap.remove());
	}

	// 결과 출력
	std::cout << (order == 1 ? "오름차순 정렬 결과: " : "내림차순 정렬 결과: ");
	for (int value : sortedData) {
		std::cout << value << " ";
	}
	std::cout << std::endl;

	return 0;
}
