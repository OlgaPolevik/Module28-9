//
//  main.cpp
//  Module28-9
//
//  Created by Ольга Полевик on 30.12.2021.
//

#include <iostream>
#include <vector>
#include <future>
#include <cassert>

void merge(int* arr, int l, int m, int r)
{
   int nl = m - l + 1;
   int nr = r - m;

   // создаем временные массивы
   int left[nl], right[nr];

   // копируем данные во временные массивы
   for (int i = 0; i < nl; i++)
       left[i] = arr[l + i];
   for (int j = 0; j < nr; j++)
       right[j] = arr[m + 1 + j];

   int i = 0, j = 0;
   int k = l;  // начало левой части

   while (i < nl && j < nr) {
       // записываем минимальные элементы обратно во входной массив
       if (left[i] <= right[j]) {
           arr[k] = left[i];
           i++;
       }
       else {
           arr[k] = right[j];
           j++;
       }
       k++;
   }
   // записываем оставшиеся элементы левой части
   while (i < nl) {
       arr[k] = left[i];
       i++;
       k++;
   }
   // записываем оставшиеся элементы правой части
   while (j < nr) {
       arr[k] = right[j];
       j++;
       k++;
   }
}

void mergeSort( int array[], int l, int r )
{
    if ( l >= r )
        return;
    
    int m = l + ( r - l ) / 2;
    
    if ( r - l > 100 )
    {
        auto futureLeft = std::async( std::launch::async, [&]()
        {
            mergeSort( array, l, m );
        });
        
        auto futureRight = std::async( std::launch::async, [&]()
        {
            mergeSort( array, m + 1, r );
        });
    }
    else
    {
        mergeSort( array, l, m );
        mergeSort( array, m + 1, r );
    }
        
    merge( array, l, m, r );
}

int main(int argc, const char * argv[]) {
    std::vector<int> v( 10000 );
    std::generate( v.begin(), v.end(), std::rand );

    std::vector<int> copy = v;
    std::sort( copy.begin(), copy.end() );
    
    mergeSort( v.data(), 0, (int)v.size() - 1 );
    
    assert( copy == v );
    
    std::cout << "Done" << std::endl;
    
    return 0;
}
