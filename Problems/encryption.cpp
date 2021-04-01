#include <bits/stdc++.h>

using namespace std;

// Complete the encryption function below.
string encryption(string s) 
{
    string newString = "";

    for(int i =0; i < s.size(); i++)
        if(s[i] != ' ')
            newString += s[i];

    int rows = floor(sqrt(newString.size()));
    int collumns = ceil(sqrt(newString.size()));

    string finalString = "";

    for(int i = 0; i < collumns; i++)
    {
        for(int j = 0; i+j*collumns < newString.size(); j++)
            finalString += newString[i + j*collumns];
        finalString+= " ";
    }

    return finalString;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = encryption(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
