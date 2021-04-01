#include <bits/stdc++.h>

using namespace std;

// Complete the superReducedString function below.
string superReducedString(string s) 
{
    if(s == "")
        return "Empty String";
    
    string finalString;

    int i;
    for(i = 0; i < s.size()-1; i++)
        if(s[i] == s[i+1])
            i++;
        else
            finalString += s[i];

    if(i == s.size() - 1)
        finalString += s[s.size() - 1];

    if(s == finalString)
        return finalString;

    return superReducedString(finalString);    
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = superReducedString(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
