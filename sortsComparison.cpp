#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

// bubble sort, returns count of operations
int bubble_sort(int* array, const int length)
{
	int numOfOperations = 3; // i = 0; i < length - 1
	for (int i = 0; i < length - 1; i++)
	{
		numOfOperations += 4; // i < length - 1; i += 1
		numOfOperations += 4; // j = 0; j < length - i - 1
		for (int j = 0; j < length - i - 1; j++)
		{
			numOfOperations += 5; // j < length  - i - 1; j += 1
			numOfOperations += 4; // array[j + 1] < array[j]
			if(array[j + 1] < array[j])
			{
				numOfOperations += 9; // 4 array takes, 2 +, 3 assignments
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
	return numOfOperations;			
}

//bubble sort with Aiverson's condition 1
int bubble_sort_Aiverson1(int* array, const int length)
{
	int numOfOperations = 3; // i = 0; i < length - 1
	for (int i = 0; i < length - 1; i++)
	{
		numOfOperations += 4; // i < length - 1; i += 1
		numOfOperations += 1; // 1 assignment
		bool noChange = false;
		numOfOperations += 4; // j = 0; j < length - i - 1
		for (int j = 0; j < length - i - 1; j++)
		{
			numOfOperations += 5; // j < length  - i - 1; j += 1
			numOfOperations += 4; // array[j + 1] < array[j]
			if(array[j + 1] < array[j])
			{
				numOfOperations += 10; // 4 array takes, 2 +, 4 assignments
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
				noChange = true;
			}
		}
		numOfOperations += 1; // 1 comparison
		if(noChange == false)
			break;
	}
	return numOfOperations;	
}

//bubble sort with Aiverson's conditions 1 and 2
int bubble_sort_Aiverson12(int* array, const int length)
{
	int numOfOperations = 1; // 1 assignment
	int bound = length;
	int t;
	do
	{
		numOfOperations += 1; // 1 assignment
		t = 0;
		for (int i = 0; i < bound - 1; i++)
		{
			numOfOperations += 4; // i < length - 1; i += 1
			numOfOperations += 4; // 2 array takes, 1 +, 1 comparison
			if(array[i] < array[i + 1])
			{
				numOfOperations += 10; // 1 exchange, 1 assignment
				int temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
				t = i;
			}
		}
		bound = t + 1;
		numOfOperations += 3; // 1 comparison, 1 +, 1 assignment
	} while(t != 0);
	return numOfOperations;
}

// Sort with insertions
int insertion_sort(int* array, const int length)
{
	int numOfOperations = 2; // i = 1; i < length
	for (int i = 1; i < length; i++)
	{
		numOfOperations += 3; //i < length; i += 1 
		numOfOperations += 4; // 2 assignments, 1 -, 1 array take
		int current = array[i];
		int j = i - 1;
		numOfOperations += 3; // 2 comparisons , 1 array take
		while (j > 0 && array[j] > current)
		{
			numOfOperations += 3; // 2 comparison, 1 array take
			numOfOperations += 11; // 4 array takes, 2+, 4 assignments,1 -
			int temp = array[j + 1];
			array[j + 1] = array[j];
			array[j] = temp;
			j--;
		}
	}		
	return numOfOperations;
}

// sort with binary insertions
int bin_insertion_sort(int* array, const int length)
{ 
	int left, right, mid;
	int numOfOperations = 2; //i = 1; i < length
	for (int i = 1; i < length; i++)
	{
		numOfOperations += 3; // i < length; i++
		int current = array[i];
		left = 0;
		right = i - 1;
		numOfOperations += 5; // 3 assignments, 1 array take, 1 arithm
		while(left < right)
		{
			numOfOperations += 1; // 2 comparisons, 2 arithm, 1 array take
			mid = (left + right) / 2;
			if (current < array[mid])
			{
				numOfOperations += 1; // 1 assignment
				right = mid;
			}
			else
			{
				numOfOperations += 2; // 1 assignment, 1 arithm
				left = mid + 1;
			}
		}
		numOfOperations += 3; // j = i; j > left + 1
		for (int j = i; j > left + 1; j--)
		{
			numOfOperations += 7; // j > left + 1; j--, 1 assignment, 2 array takes, 1 arithm
			array[j] = array[j - 1];
		}
		numOfOperations += 2; // 1 assignment, 1 array take 
		array[left] = current;
	}
	return numOfOperations;
} 

//helping function for counting sort, finds max
int max_in_array(int* array, int length, int &numOfOperations)
{
	numOfOperations += 2; // 1 assignment, 1 array take
	int max = array[0];
	numOfOperations += 2; // i =1; i < length
	for (int i = 1; i < length; i++)
	{
		numOfOperations += 5; // i < length; i++, 1 comparison, 1 array take
		if (array[i] > max)
			{
				max = array[i];
				numOfOperations += 2; // 1 assignment, 1 array take
			}
	}
	return max;
}
//helping function for counting sort, finds min
int min_in_array(int* array, int length, int &numOfOperations)
{
	numOfOperations += 2; // 1 assignment, 1 array take
	int min = array[0];
	numOfOperations += 2; // i =1; i < length
	for (int i = 1; i < length; i++)
	{
		numOfOperations += 5; // i < length; i++, 1 comparison, 1 array take
		if (array[i] < min)
			{
				min = array[i];
				numOfOperations += 2; // 1 assignment, 1 array take
			}
	}
	return min;
}
// stable counting sort
int stable_counting_sort(int* array, const int length, const int max_num)
{
	int numOfOperations = 0;
	int current, index_of_previous;
	int max = max_in_array(array, length, numOfOperations);
	int min = min_in_array(array, length, numOfOperations);
	numOfOperations += 4; // i = 1; i < length
    int len = max - min + 1; 
	numOfOperations += 3; //  
	int *count = new int[len]; 
	numOfOperations += 3; // *c = new int[k]; i = 0; i < k 
	for (int i = 0; i < len; i++) 
	{ 
		count[i] = 0; 
		numOfOperations += 2; // c[i] = 0; 
	} 
	numOfOperations += 2; // i = 0; i < n 
	for (int i = 0; i < length; i++) 
	{ 
		count[array[i] - min]++; 
		numOfOperations += 5; // c[arr[i] - min]++; 
	} 
	int position = 0; 
	numOfOperations += 3; // pos = 0; j = 0; j < k 
	for (int j = 0; j < len; j++) 
	{ 
		numOfOperations += 3; // j < k; j++ 
		numOfOperations += 3; // i = 0; i < c[j] 
		for (int i = 0; i < count[j]; i++) 
		{ 
			numOfOperations += 4; // i < c[j]; i++ 
			array[position++] = j + min; 
			numOfOperations += 5; // arr[pos++] = j + min 
		} 
	} 
	delete[] count; 
	return numOfOperations;
}

union RadixUnion 
{
    unsigned int num;
    unsigned char set[5];
};
 
int radix_sort(int* array, int n)
{
	int numOfOperations = 1; // 1 assignments 
    int digit = 0, count;
    RadixUnion *temp = new RadixUnion[n];
    while (digit < 5) 
	{
		numOfOperations += 1; // 1 comparison
		numOfOperations += 2; // i = 0; i < n
        for (int i = 0; i < n; i++)
        {
        	numOfOperations += 3; // i < n; i++
            temp[i].num = (unsigned int)array[i];
            numOfOperations += 4; // type conversion doesn't count
        }
        int *ciphers = new int[256];
        numOfOperations += 2; // i = 0; i < 256
        for (int i = 0; i < 256; i++)
        {
        	numOfOperations += 5; // i < 256; i++, 1 assignment, 1 array take
            ciphers[i] = 0;
        }
        numOfOperations += 2; // i = 0; i < n
        for (int i = 0; i < n; i++)
        {
        	numOfOperations += 9; // i < n; i++, 3 array take, 1 union take, 1 ++
            ciphers[temp[i].set[digit]]++;
        }
        numOfOperations += 1; // 1 assignment
        int j;
		count = 0;
        numOfOperations += 2; // i = 0; i < 256
        for (int i = 0; i < 256; i++) 
		{
            numOfOperations += 9; // i < 256; i++; 3 assignments, 1 arithm, 2 array tajes
			j = ciphers[i];
            ciphers[i] = count;
            count += j;
        }
        numOfOperations += 2; // i = 0; i < n
        for (int i = 0; i < n; i++) 
		{
			numOfOperations += 15; // i < n; i++, 1++, 6 array takes, 2 unidon takes, 3 assignments,
            int tempIndex = temp[i].set[digit];
            array[ciphers[tempIndex]] = temp[i].num;
            ciphers[tempIndex]++;
        }
        numOfOperations += 2; // 1 ++
        digit++;
        delete[] ciphers;
    } 
    delete[] temp;
    return numOfOperations;
}

// generate array of random ints <= rightBorder, which length = length
int* generate_random_array(const int rightBorder, const int length)
{
	long ltime = time (NULL);
	int stime = (unsigned int) ltime/2;
	srand(stime);
	int r = rightBorder + 1;
	int *array = new int[length];
	for (int i = 0; i < length; i++)
		array[i] = rand() % r;
	return array;
}

// generates 1..length array
int* get_sorted_array(const int length)
{
	int *array = new int[length];
	for (int i = 1; i <= length; i++)
		array[i] = i;
	return array;
}

// mashes up 2 * numOfMashups elements in array 
int* mashup_array(int* array, int length, int numOfMashups)
{
	long ltime = time (NULL);
	int stime = (unsigned int) ltime/2;
	srand(stime);
	int *used_elems = new int[2 * numOfMashups];
	int j = 0;
	for (int i = 0; i < numOfMashups; i++)
	{
		int elem1 = 0, elem2 = 0;
		while(elem1 == elem2)
			elem1 = rand() % length;
			elem2 = rand() % length;
			for (int j = 0; j < 2 * numOfMashups; j++)
				if(elem1 == used_elems[j] || elem2 == used_elems[j])
					continue;
				else
					{
						used_elems[j++] = elem1;
						used_elems[j++] = elem2;
						std::swap(array[elem1], array[elem2]);
					}
	}
	return array;
}

// reverses array
int* reverse_array(int* array, int length)
{
	int *ans = new int[length];
	for (int i = 0; i < length; i++)
		ans[i] = array[length - i - 1];
	return ans;
}

//copies array by its copy, isn't safe
int* copy_array(int* array, int length_of_copy)
{
	int *ans = new int[length_of_copy];
	for(int i = 0; i < length_of_copy; i++)
		ans[i] = array[i];
	return ans;
}

int main()
{	
	std::ofstream fout("data_operations_of_sort.csv"); 
	if(!fout.is_open())
		std::cout << "OOOOOOOPS... Some problems with creating the data file";
	fout << "Размер массива" << ";" << "Пузырёк Случайные числа 0-9" << ";" << "Пузырёк случ макс" << ";" << "Пузырёк обратно сортир" << ";" << "Пузырёк почти сортир" << ";" 
	<< "Пузырёк Айверсона 1 Случайные числа 0-9" << ";" << "Пузырёк Айверсона 1 случ макс" << ";" << "Пузырёк Айверсона 1 обратно сортир" << ";" << "Пузырёк Айверсона 1 почти сортир" << ";" 
	<< "Пузырёк Айверсона 1 + 2 Случайные числа 0-9" << ";" << "Пузырёк Айверсона 1 + 2 случ макс" << ";" << "Пузырёк Айверсона 1 + 2 обратно сортир" << ";" << "Пузырёк Айверсона 1 + 2 почти сортир" << ";"
	<< "Простые вставки Случайные числа 0-9" << ";" << "Простые вставки случ макс" << ";" << "Простые вставки обратно сортир" << ";" << "Простые вставки почти сортир" << ";"
	<< "Бинарные вставки Случайные числа 0-9" << ";" << "Бинарные вставки случ макс" << ";" << "Бинарные вставки обратно сортир" << ";" << "Бинарные вставки почти сортир" << ";"
	<< "Подсчёт Случайные числа 0-9" << ";" << "Подсчёт случ макс" << ";" << "Подсчёт обратно сортир" << ";" << "Подсчёт почти сортир" << ";"
	<< "Цифровая Случайные числа 0-9" << ";" << "Цифровая случ макс" << ";" << "Цифровая обратно сортир" << ";" << "Цифровая почти сортир" << ";" << "\n";
	
	int step = 1000;
	int maxLength = 8000;
	int *base_array09 = generate_random_array(9, maxLength);
	int *base_array010000 = generate_random_array(10000, maxLength);
	int *base_array_almost_sorted = mashup_array(get_sorted_array(maxLength), maxLength, 9);
	int *base_array_reverse_sorted = reverse_array(get_sorted_array(maxLength), maxLength);
	for (int i = 1; i <= 8; i++)
	{
		fout << i * step << ";";
		//bubble sort
		int *arr09 = copy_array(base_array09, step * i);
		int *arr010000 = copy_array(base_array010000, step * i);
		int *arr_almost_sorted = copy_array(base_array_almost_sorted, step * i);
		int *arr_reverse_sorted = copy_array(base_array_reverse_sorted, step * i);
		fout << bubble_sort(arr09, i * step) << ";" << bubble_sort(arr010000, i * step) << ";" << bubble_sort(arr_almost_sorted, i * step) << ";" << bubble_sort(arr_reverse_sorted, i * step) << ";";
		//bubble sort with 1st Aiverson condition
		arr09 = copy_array(base_array09, step * i);
		arr010000 = copy_array(base_array010000, step * i);
		arr_almost_sorted = copy_array(base_array_almost_sorted, step * i);
		arr_reverse_sorted = copy_array(base_array_reverse_sorted, step * i);
		fout << bubble_sort_Aiverson1(arr09, i * step) << ";" << bubble_sort_Aiverson1(arr010000, i * step) << ";" << bubble_sort_Aiverson1(arr_almost_sorted, i * step) << ";" << bubble_sort_Aiverson1(arr_reverse_sorted, i * step) << ";";
		//bubble sort with 1st and 2nd Aiverson condition
		arr09 = copy_array(base_array09, step * i);
		arr010000 = copy_array(base_array010000, step * i);
		arr_almost_sorted = copy_array(base_array_almost_sorted, step * i);
		arr_reverse_sorted = copy_array(base_array_reverse_sorted, step * i);
		fout << bubble_sort_Aiverson12(arr09, i * step) << ";" << bubble_sort_Aiverson12(arr010000, i * step) << ";" << bubble_sort_Aiverson12(arr_almost_sorted, i * step) << ";" << bubble_sort_Aiverson12(arr_reverse_sorted, i * step) << ";";
		//Insertion sort
		arr09 = copy_array(base_array09, step * i);
		arr010000 = copy_array(base_array010000, step * i);
		arr_almost_sorted = copy_array(base_array_almost_sorted, step * i);
		arr_reverse_sorted = copy_array(base_array_reverse_sorted, step * i);
		fout << insertion_sort(arr09, i * step) << ";" << insertion_sort(arr010000, i * step) << ";" << insertion_sort(arr_almost_sorted, i * step) << ";" << insertion_sort(arr_reverse_sorted, i * step) << ";";
		//Binary insertion sort
		arr09 = copy_array(base_array09, step * i);
		arr010000 = copy_array(base_array010000, step * i);
		arr_almost_sorted = copy_array(base_array_almost_sorted, step * i);
		arr_reverse_sorted = copy_array(base_array_reverse_sorted, step * i);
		fout << bin_insertion_sort(arr09, i * step) << ";" << bin_insertion_sort(arr010000, i * step) << ";" << bin_insertion_sort(arr_almost_sorted, i * step) << ";" << bin_insertion_sort(arr_reverse_sorted, i * step) << ";";
		//Stable counting sort
		arr09 = copy_array(base_array09, step * i);
		arr010000 = copy_array(base_array010000, step * i);
		arr_almost_sorted = copy_array(base_array_almost_sorted, step * i);
		arr_reverse_sorted = copy_array(base_array_reverse_sorted, step * i);
		fout << stable_counting_sort(arr09, i * step, 9) << ";" << stable_counting_sort(arr010000, i * step, 10000) << ";" << stable_counting_sort(arr_almost_sorted, i * step, i * step) << ";" << stable_counting_sort(arr_reverse_sorted, i * step, i * step) << ";";
		//Radix sort
		arr09 = copy_array(base_array09, step * i);
		arr010000 = copy_array(base_array010000, step * i);
		arr_almost_sorted = copy_array(base_array_almost_sorted, step * i);
		arr_reverse_sorted = copy_array(base_array_reverse_sorted, step * i);
		fout << radix_sort(arr09, i * step) << ";" << radix_sort(arr010000, i * step) << ";" << radix_sort(arr_almost_sorted, i * step) << ";" << radix_sort(arr_reverse_sorted, i * step) << ";";
		fout << std::endl;
	}
	fout.close();
	std::cout << "Now my work is done, go check data_operations_of_sort.csv file";
	return 0;
}
