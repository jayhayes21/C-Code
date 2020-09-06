//Data Structures and Algorithms HW#2
//Comparing Mergesort versus Quicksort with Insertionsort as our threshold
#include <iostream>
#include <algorithm>
#include <time.h>
#include <bits/stdc++.h>

int comparisons;
template<class T>
void printArray(T items[], int size);
template<class T>
void reset(T items[], T fixedarray[], int size);
template<class T>
void insertionSort(T items[], int size);
template<class T>
void mergeSort(T items[], int size, int threshold);
template<class T>
void quickSort(T items[], int min, int max, int threshold);

//int n;

int main()
{
    int n;
    int choice;
    int manual; // 0_auto 1_manual
    int displayed; //0_not 1_displayed
    int threshold;
    srand(time(NULL));
    while(1)
    {
        comparisons = 0;
        std::cout << "How many items are to be sorted? ";
        std::cin >> n;
        if(n <= 15)
        {
            std::cout << "List entered manually? [Yes_1,No_0] ";
            std::cin >> manual;
            std::cout << "Sorted list to be displayed? [Yes_1,No_0] ";
            std::cin >> displayed;
        }
        else
        {
            manual = 0;
            displayed = 0;
        }
        std::cout << "What do you want the threshold to be? ";
        std::cin >> threshold;
        int items[n];

        if(manual == 0)
        {
            for (int i = 0; i < n; i++)
            {
                items[i] = rand() % (10);
            }
        }
        else if(manual == 1)
        {
            for (int i = 0; i < n; i++)
            {
                std::cout << "Enter array element " << i << ": ";
                std::cin >> items[i];
            }
        }
        int fixedarray[n]; //dummy array
        for (int i = 0; i < n; i++)
        {
            fixedarray[i] = items[i];
        }
        if((displayed == 1) && (n <= 15))
        {
            //Merge Test
            std::cout << "Mergesort Test: " << std::endl;
            printArray(items, n); //Initial Array
            mergeSort(items, n, threshold);
            printArray(items, n); //Sorted Array
            std::cout<<"Number of comparisons for Merge Sort: "<<comparisons<<std::endl;

            comparisons = 0;
            reset(items, fixedarray, n);
            std::cout<<std::endl;
            std::cout << "Quicksort Test: " << std::endl;
            printArray(items, n);
            quickSort(items, 0, n - 1, threshold);
            printArray(items, n); //Sorted Array
            std::cout<<"Number of comparisons for Quick Sort: "<<comparisons<<std::endl;
            std::cout<<std::endl;
        }
        else
        {
            //Merge Test
            std::cout << "Mergesort Test: " << std::endl;
            mergeSort(items, n, threshold);
            std::cout<<"Number of comparisons for Merge Sort: "<<comparisons<<std::endl;

            comparisons = 0;
            reset(items, fixedarray, n);
            std::cout<<std::endl;
            std::cout << "Quicksort Test: " << std::endl;
            quickSort(items, 0, n - 1, threshold);
            std::cout<<"Number of comparisons for Quick Sort: "<<comparisons<<std::endl;
            std::cout<<std::endl;
        }
        std::cout<<"Do you want to run the program again?"<<std::endl;
        std::cout<<"Press 0 to exit the program"<<std::endl;
        std::cout<<"Press 1 to run the program again"<<std::endl;
        std::cin>>choice;
        std::cout<<std::endl;
        if (choice == 0)
        {
            break;
        }


    }
    return 0;
}

template<class T>
void printArray(T items[], int size)
{
    for (int d = 0; d < size; d++)
    {
        std::cout << items[d] << " ";
    }
    std::cout << std::endl;
}

template<class T>
void reset(T items[], T fixedarray[], int size)
{
    for (int i = 0; i < size; i++)
    {
        items[i] = fixedarray[i];
    }
}

template <class T>
void insertionSort(T items[], int size)
{
    for (int i = 1; i < size; i++)
    {
        T temp = items[i];
        int prev = i - 1;
        while (prev >= 0 && items[prev] > temp)
        {
            items[prev + 1] = items[prev];
            prev--;
        }
        items[prev + 1] = temp;
    }
}

template <class T>
void merge(T A[], T B[], T C[], int alen, int blen)
{
    int aloc = 0, bloc = 0;
    while (aloc < alen && bloc < blen)
    {
        if (A[aloc] < B[bloc])
        {
            C[aloc + bloc] = A[aloc];
            aloc++;
            comparisons++;
        }
        else
        {
            C[aloc + bloc] = B[bloc];
            bloc++;
            comparisons++;
        }
    }
    while (aloc < alen)
    {
        C[aloc + bloc] = A[aloc];
        aloc++;
    }
    while (bloc < blen)
    {
        C[aloc + bloc] = B[bloc];
        bloc++;
    }
}

template <class T>
void mergeSort(T items[], int size, int threshold)
{
    if (size <= threshold)
    {
        return insertionSort(items, size);
    }

    int half = size / 2;
    int otherhalf = half + (size % 2);
    T A[half], B[otherhalf];
    for (int i = 0; i < half; i++)
    {
        A[i] = items[i];
    }
    for (int i = 0; i < otherhalf; i++)
    {
        B[i] = items[half + i];
    }

    mergeSort(A, half, threshold);
    mergeSort(B, otherhalf, threshold);
    merge(A, B, items, half, otherhalf);
}

template <class T>
int split(T items[], int min, int max)
{
    T temp = 0, pivot = items[max];
    int i = min - 1, j = min;
    for (; j < max; j++)
    {
        if (items[j] <= pivot)
        {
            i++;
            comparisons++;
            temp = items[j];
            items[j] = items[i];
            items[i] = temp;
        }
    }
    temp = items[i + 1];
    items[i + 1] = items[max];
    items[max] = temp;
    return i + 1;
}

template <class T>
void quickSort(T items[], int min, int max, int threshold)
{
    int size;
    size = (max - min) + 1;
    if (size <= threshold)
    {
        return insertionSort(items, size);
    }
    if (min < max)
    {
        int mid = split(items, min, max);
        quickSort(items, min, mid - 1, threshold);
        quickSort(items, mid + 1, max, threshold);

        for(int i = 0; i < size; i++){
            if(items[i] > items[i+1]){
                std::swap(items[i], items[i+1]);
            }
        }
    }
}


