#include <bits/stdc++.h>

using namespace std;

// Complete the pangrams function below.
string pangrams(string s) 
{
    int arr['z' - 'a' + 1];

    for(int i = 0; i< s.size(); i++)
        if(s[i] != ' ')
            arr[tolower(s[i])-'a']++;

    for(int i = 0; i < 'z' - 'a' + 1; i++)
       if(arr[i] == 0)
            return "not pangram";

    return "pangram";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = pangrams(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
