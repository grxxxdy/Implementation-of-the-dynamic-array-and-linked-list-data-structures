#include <iostream>
#include <windows.h>
#include <ctime>

using namespace std;

struct cat								// кіт
{
	char name;
	float food;
	int fur;
};

struct DynamicArray						// Динамічний масив
{
	int maxAmount;
	cat* array;
	int amount;

	DynamicArray()
	{
		maxAmount = 1;
		array = new cat[maxAmount];
		amount = 0;
	}

	void reallocate(int size)
	{
		cat* temp = new cat[size];

		for (int i = 0; i < amount; i++)
		{
			temp[i] = array[i];
		}

		delete[] array;

		array = temp;
	}

	void push_back(cat* catt)
	{
		if (amount >= maxAmount)
		{
			maxAmount = (amount * 2);

			reallocate(maxAmount);
		}

		array[amount] = (*catt);

		amount++;
	}

	void pop_back()
	{
		if (amount <= 0)
		{
			cout << "The array is already empty" << endl;
		}
		else
		{
			amount--;
		}
	}

	cat get(int index)
	{
		if (index >= amount || index < 0)
		{
			cout << "Element with set index does not exist in the array" << endl;
		}
		else
		{
			return array[index];
		}
	}

	int size()
	{
		return amount;
	}

	void print()
	{
		if (amount == 0)
		{
			cout << "The array is empty" << endl;
			return;
		}

		for (int i = 0; i < amount; i++)
		{
			cout << "Cat " << (i + 1) << ":" << endl;
			cout << "Name: " << array[i].name << endl;
			cout << "Amount of food per day: " << array[i].food << " Kg" << endl;
			cout << "Fluffiness: " << array[i].fur << "%\n" << endl;
		}
	}

	void clear()
	{
		if (amount != 0)
		{
			amount = 0;
			maxAmount = 1;
		}
	}

	void push_front(cat* catt)
	{
		if (amount >= maxAmount)
		{
			maxAmount = (amount * 2);

			reallocate(maxAmount);
		}

		memmove(array + 1, array, sizeof(cat) * amount);

		array[0] = (*catt);

		amount++;
	}

	void pop_front()
	{
		if (amount <= 0)
		{
			cout << "The array is empty" << endl;
		}
		else
		{
			memmove(array, array + 1, sizeof(cat) * (amount - 1));

			amount--;
		}
	}

	void insert(cat* catt, int index)
	{
		if (index < 0 || index >= amount)
		{
			cout << "Error" << endl;
			return;
		}

		if (amount >= maxAmount)
		{
			maxAmount = (amount * 2);

			reallocate(maxAmount);
		}

		for (int i = amount; i > index; i--)
		{
			array[i] = array[i - 1];
		}

		array[index] = (*catt);

		amount++;
	}

	void remove(int index)
	{
		if (index < 0 || index >= amount)
		{
			cout << "Error" << endl;
			return;
		}
		else if (index == 0)
		{
			pop_front();
		}
		else if (index == (amount - 1))
		{
			pop_back();
		}

		amount--;

		for (int i = index; i < amount; i++)
		{
			array[i] = array[i + 1];
		}
	}

	~DynamicArray()
	{
		delete[] array;
	}
};

struct Node						// зв'язок
{
	cat data;
	Node* nextElement;
};

struct LinkedList				// зв'язний список
{
	Node* head;
	Node* tail;

	LinkedList()
	{
		head = nullptr;
		tail = nullptr;
	}

	void push_front(cat* catt)
	{
		Node* newNode = new Node();

		newNode->data = (*catt);

		if (!head)
		{
			tail = newNode;
		}
		else
		{
			newNode->nextElement = head;
		}

		head = newNode;
	}

	void push_back(cat* catt)
	{
		Node* newNode = new Node();

		newNode->data = (*catt);

		newNode->nextElement = nullptr;

		if (!head)
		{
			head = newNode;
		}
		else
		{
			tail->nextElement = newNode;
		}

		tail = newNode;

	}

	cat get(int element)
	{
		if (!head)
		{
			cout << "The linked list is empty" << endl;
		}

		bool error = false;

		if (element < 0)
		{
			cout << "Element with set index does not exist in the linked list" << endl;
			error = true;
		}
		Node* current = head;

		if (!error)
		{
			for (int i = 1; i < element; i++)
			{
				if (current->nextElement == nullptr)
				{
					cout << "Element with set index does not exist in the linked list" << endl;
					error = true;
					break;
				}
				current = current->nextElement;
			}

			if (!error)
			{
				return current->data;
			}
		}

	}

	void pop_front()
	{
		if (!head)
		{
			cout << "The linked list is already empty" << endl;
			return;
		}

		if (head == tail)
		{
			delete head;

			head = nullptr;
			tail = nullptr;

			return;
		}

		Node* temp = head->nextElement;

		delete head;

		head = temp;
	}

	void pop_back()
	{
		if (!head)
		{
			cout << "The linked list is already empty" << endl;
			return;
		}

		if (head == tail)
		{
			delete head;

			head = nullptr;
			tail = nullptr;

			return;
		}

		Node* current = head;

		while (current->nextElement && current->nextElement->nextElement && current->nextElement->nextElement->nextElement)
		{
			current = current->nextElement->nextElement;
		}

		if (current->nextElement->nextElement == tail)
		{
			current = current->nextElement;
		}

		delete tail;

		current->nextElement = nullptr;

		tail = current;
	}

	int size()
	{
		int amount = 0;

		Node* current = head;

		while (current != nullptr)
		{
			current = current->nextElement;
			amount++;
		}

		return amount;
	}

	void print()
	{
		if (!head)
		{
			cout << "The linked list is empty" << endl;
			return;
		}

		Node* current = head;
		int i = 1;

		while (current != nullptr)
		{
			cout << "Cat " << i << ":" << endl;
			cout << "Name: " << current->data.name << endl;
			cout << "Amount of food per day: " << current->data.food << " Kg" << endl;
			cout << "Fluffiness: " << current->data.fur << "%\n" << endl;

			current = current->nextElement;
			i++;
		}

	}

	void clear()
	{
		Node* current = head;

		while (head != nullptr)
		{
			current = head->nextElement;

			delete head;

			head = current;
		}

		head = nullptr;
		tail = nullptr;
	}

	void insert(cat* catt, int element)
	{
		if (element <= 0)
		{
			cout << "Error" << endl;
			return;
		}
		else if (element == 1)
		{
			push_front(&*catt);
			return;
		}

		Node* current = head;
		Node* previous = nullptr;

		for (int i = 1; i < element; i++)
		{
			if (current->nextElement == nullptr)
			{
				push_back(catt);
				return;
			}

			previous = current;

			current = current->nextElement;
		}

		Node* newNode = new Node();

		newNode->data = (*catt);

		previous->nextElement = newNode;
		newNode->nextElement = current;

	}

	void remove(int element)
	{
		if (element <= 0)
		{
			cout << "Element with set index does not exist in the linked list" << endl;
			return;
		}
		else if (element == 1)
		{
			pop_front();
			return;
		}

		Node* current = head;
		Node* previous = nullptr;

		for (int i = 1; i < element; i++)
		{
			if (current->nextElement == nullptr)
			{
				cout << "Element with set index does not exist in the linked list" << endl;
				return;
			}

			previous = current;

			current = current->nextElement;
		}

		previous->nextElement = current->nextElement;

		delete current;
	}

	~LinkedList()
	{
		clear();
	}
};

template<typename str>
void test()
{
	str cat1;

	cat catt;

	float food;

	int index;

	clock_t startTimeTotal1 = clock();

	clock_t startTime1 = clock();

	for (int i = 0; i < 50000; i++)				// 5.1
	{
		food = rand() % 10 * 0.85;
		catt = { 'a', food, rand() % 101 };
		cat1.push_back(&catt);
	}

	clock_t endTime1 = clock();

	double seconds1 = (double(endTime1 - startTime1)) / CLOCKS_PER_SEC;

	cout << "Runtime 1: " << seconds1 << " seconds" << endl;


	clock_t startTime2 = clock();

	for (int i = 0; i < 10000; i++)				// 5.2
	{
		food = rand() % 10 * 0.85;
		catt = { 'a', food, rand() % 101 };
		cat1.push_front(&catt);
	}

	clock_t endTime2 = clock();

	double seconds2 = (double(endTime2 - startTime2)) / CLOCKS_PER_SEC;

	cout << "Runtime 2: " << seconds2 << " seconds" << endl;



	clock_t startTime3 = clock();

	for (int i = 0; i < 20000; i++)				// 5.3
	{
		index = rand() % 10000;
		cat1.get(index);
	}

	clock_t endTime3 = clock();

	double seconds3 = (double(endTime3 - startTime3)) / CLOCKS_PER_SEC;

	cout << "Runtime 3: " << seconds3 << " seconds" << endl;



	clock_t startTime4 = clock();

	for (int i = 0; i < 5000; i++)				// 5.4
	{
		cat1.pop_front();
	}

	clock_t endTime4 = clock();

	double seconds4 = (double(endTime4 - startTime4)) / CLOCKS_PER_SEC;

	cout << "Runtime 4: " << seconds4 << " seconds" << endl;



	clock_t startTime5 = clock();

	for (int i = 0; i < 5000; i++)				// 5.5
	{
		cat1.pop_back();
	}

	clock_t endTime5 = clock();

	double seconds5 = (double(endTime5 - startTime5)) / CLOCKS_PER_SEC;

	cout << "Runtime 5: " << seconds5 << " seconds" << endl;

	clock_t endTimeTotal1 = clock();

	double secondsTotal1 = (double(endTimeTotal1 - startTimeTotal1)) / CLOCKS_PER_SEC;

	cout << "Total runtime: " << secondsTotal1 << " seconds" << endl;
}

int main()
{
	srand(time(NULL));

	int choise;
	
	while (true)
	{
		cout << "1 - test the dynamic array;\n2 - test the linked list;\n3 - exit the program" << endl;
		cin >> choise;
		
		switch (choise)
		{
		case 1:
			test<DynamicArray>();
			break;
		case 2: 
			test<LinkedList>();
			break;
		case 3:
			return 0;
		default:
			cout << "Enter the correct number" << endl;
			break;
		}
	}
}
