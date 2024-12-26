#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>

template <typename T>
class Heap
{
public:
	using Compare = std::function<int(const T&, const T&)>;

	// ������
	Heap(Compare comp) : comp(comp)
	{
	}

	// ���� ����ִ��� Ȯ��
	bool isEmpty() const
	{
		return heapArr.empty();
	}

	// ���� ������ ����
	void insert(const T& data)
	{
		heapArr.push_back(data);
		size_t idx = heapArr.size() - 1;

		while (idx > 0)
		{
			size_t parentIdx = getParentIdx(idx);

			// �������� �켱������ ���Ͽ� �ڸ� ����
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

	// ������ ������ ����
	T remove()
	{
		// 1. ���� ��� �ִ��� Ȯ��
		// ���� ��� ������ �����͸� ������ �� �����Ƿ� ���ܸ� �����ϴ�.
		if (isEmpty())
		{
			throw std::underflow_error("Heap is empty!"); // ��Ÿ�� ���� �߻�
		}

		// 2. ��ȯ�� ������ (��Ʈ ���) ����
		// ���� Ư���� ��Ʈ ���(ù ��° ���)�� �׻� �ְ� �켱���� �����͸� �����մϴ�.
		T retData = heapArr[0];

		// 3. ������ ��带 �����ɴϴ�.
		// ������ ���� ���� �� ���� �籸���� �� �� �ڸ��� ä��� �� ���˴ϴ�.
		T lastElem = heapArr.back();

		// 4. ������ ��带 �迭���� ����
		// `std::vector`�� `pop_back()` �޼��带 ����Ͽ� ������ ��Ҹ� �����մϴ�.
		heapArr.pop_back();

		// 5. �θ� ��� �ε����� �ʱ�ȭ
		// ���� �籸���� ���� ��Ʈ ���(�ε��� 0)���� �����մϴ�.
		size_t parentIdx = 0;

		// 6. �ڽ� ��� �ε����� ����� ���� ����
		// `getHigherPriorityChildIdx`�� ���� �켱������ �� ���� �ڽ� ��带 ����մϴ�.
		size_t childIdx;

		// 7. �� �籸�� (�ٿ��� ����)
		// �켱������ ���� �ڽ� ��带 ã�� �������鼭 �� Ư���� �����մϴ�.
		while ((childIdx = getHigherPriorityChildIdx(parentIdx)) != SIZE_MAX)
		{
			// 7.1. ������ ���� �ڽ� ��� ��
			// ���� ������ ��尡 ���� �ڽ� ��庸�� �켱������ ���ų� ���ٸ�
			// �� �̻� �ڸ��� ��ȯ�� �ʿ䰡 �����Ƿ� �ݺ����� �����մϴ�.
			if (comp(lastElem, heapArr[childIdx]) >= 0)
			{
				break;
			}

			// 7.2. �θ� ��忡 �ڽ� ��� ���� ����
			// ���� �θ� ��ġ�� �ڽ� ��� ������ ä��ϴ�.
			heapArr[parentIdx] = heapArr[childIdx];

			// 7.3. �θ� ��� �ε����� �ڽ� ���� ������Ʈ
			// ���� �ݺ����� ���� �ڽ� ��尡 ���ο� �θ� ��尡 �˴ϴ�.
			parentIdx = childIdx;
		}

		// 8. ������ ��带 ���� ��ġ�� ����
		// �ݺ����� ����Ǹ� ������ ��带 �ùٸ� ��ġ�� ��ġ�մϴ�.
		if (!heapArr.empty())
		{
			heapArr[parentIdx] = lastElem; // ������ ��Ҹ� �̵��� �θ� ��ġ�� ����
		}

		// 9. ��ȯ
		// ��Ʈ ��忡 �ִ� �����͸� ��ȯ�մϴ�.
		return retData;
	}

protected:
	// �θ� ��� �ε��� ���
	size_t getParentIdx(size_t idx) const {
		return (idx - 1) / 2;
	}

	// ���� �ڽ� ��� �ε��� ���
	size_t getLeftChildIdx(size_t idx) const {
		return idx * 2 + 1;
	}

	// ������ �ڽ� ��� �ε��� ���
	size_t getRightChildIdx(size_t idx) const {
		return idx * 2 + 2;
	}

	// �켱������ �� ���� �ڽ� ����� �ε��� ��ȯ
	size_t getHigherPriorityChildIdx(size_t idx) const
	{
		size_t left = getLeftChildIdx(idx);
		size_t right = getRightChildIdx(idx);

		if (left >= heapArr.size())
		{
			return SIZE_MAX; // �ڽ� ��� ����
		}
		else if (right >= heapArr.size())
		{
			return left; // ���� �ڽĸ� ����
		}
		else
		{
			// �� �ڽ��� ���Ͽ� �� ���� �켱������ ������ ��� ��ȯ
			return (comp(heapArr[left], heapArr[right]) > 0) ? left : right;
		}
	}

private:
	std::vector<T> heapArr; // ���� �迭�� �� ����
	Compare comp;           // �켱���� �� �Լ�	
};

int main() {
	// ����ڷκ��� �Է¹��� ������
	std::vector<int> inputData;
	int n;

	// ������ ������ ���� �Է�
	std::cout << "������ ������ ������ �Է��ϼ���: ";
	std::cin >> n;

	// ���� �Է�
	std::cout << "���ڵ��� �Է��ϼ���: ";
	for (int i = 0; i < n; ++i) {
		int value;
		std::cin >> value;
		inputData.push_back(value);
	}

	// ���� ��� ����
	int order;
	std::cout << "���� ����� �����ϼ��� (1: ��������, 2: ��������): ";
	std::cin >> order;

	// ���� ������ �����ϴ� �켱���� �� �Լ�
	Heap<int>::Compare comp = (order == 1)
		? [](int a, int b) -> int { return b - a; } : [](int a, int b) -> int { return a - b; };

	// �� ����
	Heap<int> heap(comp);

	// �����͸� ���� ����
	for (int value : inputData) {
		heap.insert(value);
	}

	// ���� ��� ����
	std::vector<int> sortedData;

	// ������ �����͸� ���� ����
	while (!heap.isEmpty()) {
		sortedData.push_back(heap.remove());
	}

	// ��� ���
	std::cout << (order == 1 ? "�������� ���� ���: " : "�������� ���� ���: ");
	for (int value : sortedData) {
		std::cout << value << " ";
	}
	std::cout << std::endl;

	return 0;
}
