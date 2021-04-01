#include <bits/stdc++.h>

using namespace std;

// Complete the caesarCipher function below.
string caesarCipher(string s, int k) 
{
    for(int i = 0; i < s.size(); i++)
        if(s[i] >= 'A' && s[i] <= 'Z')
            s[i] = (char)('A' + (s[i] - 'A' + k)%('Z' - 'A' + 1) );
        else if (s[i] >= 'a' && s[i] <= 'z')
            s[i] = (char)('a' + (s[i] - 'a' + k)%('z' - 'a' + 1) );

    return s;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string s;
    getline(cin, s);

    int k;
    cin >> k;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string result = caesarCipher(s, k);

    fout << result << "\n";

    fout.close();

    return 0;
}
