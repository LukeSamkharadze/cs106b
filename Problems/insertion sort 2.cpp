#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the insertionSort2 function below.
void insertionSort2(int n, vector<int> arr) 
{
    vector<int> sortedArr;
    sortedArr.push_back(arr[0]);

    for(int i = 1; i < n; i++)
    {
        sortedArr.push_back(arr[i]);

        for(int j = i; j > 0; j--)
        {
            if(sortedArr[j] < sortedArr[j-1])
            {
                int tmp = sortedArr[j];
                sortedArr[j] = sortedArr[j-1];
                sortedArr[j-1] = tmp;
            }
        }

        for(int j = 0; j < sortedArr.size(); j++)
            cout << sortedArr[j] << " ";

        for(int j = sortedArr.size(); j < arr.size(); j++)
            cout << arr[j] << " ";
        
        cout << endl;
    }

}

int main()
{
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    insertionSort2(n, arr);

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}