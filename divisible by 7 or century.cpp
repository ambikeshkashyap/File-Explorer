#include <iostream>
using namespace std;

#include<vector>

void processArray(vector<int> &arr);

int main()
{
    vector<int> arr;
    int temp;

    while(1)
    {
        cin >> temp;
        if(0 > temp)
            break;
        arr.push_back(temp);
    }

    processArray(arr);

    return 0;
}

void processArray(vector<int> &arr)
{
    int size = arr.size();
    bool is7Divisible = false,is100Greater = false;

    for(int i = 0;i < size;i++)
    {
        if(0 == arr[i] % 7)
            is7Divisible = true;
        if(arr[i] > 100)
            is100Greater = true;

        if(is100Greater && is7Divisible)
            arr[i] = -3;
        else if(is7Divisible)
            arr[i] = -1;
        else if(is100Greater)
            arr[i] = -2;

        is7Divisible = is100Greater = false;
    }
}
