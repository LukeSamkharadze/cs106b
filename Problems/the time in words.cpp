#include <bits/stdc++.h>

using namespace std;

string GetMultiplesOf10(int n)
{
    switch(n) 
    {
        case 2: return "twenty";
        case 3: return "thirty";
        case 4: return "fourty";
        case 5: return "fifty";
    }

    return "ERROR";
}

string GetNumberUnder20(int n)
{
    switch(n) 
    {
        case 1: return "one";
        case 2: return "two";
        case 3: return "three";
        case 4: return "four";
        case 5: return "five";
        case 6: return "six";
        case 7: return "seven";
        case 8: return "eight";
        case 9: return "nine";
        case 10: return "ten";
        case 11: return "eleven";
        case 12: return "twelve";
        case 13: return "thirteen";
        case 14: return "fourteen";
        case 15: return "fifteen";
        case 16: return "sixteen";
        case 17: return "seventeen";
        case 18: return "eighteen";
        case 19: return "nineteen";
    }

    return "ERROR";
}

string GetNumber(int n)
{
    if(n < 20)
        return GetNumberUnder20(n);
    else
        return GetMultiplesOf10(n/10) + " " + GetNumberUnder20(n%10);
}

// Complete the timeInWords function below.
string timeInWords(int h, int m) 
{
    if(m == 0)
        return GetNumberUnder20(h) + " o' clock";
    else if(m == 15)
        return "quarter past " + GetNumberUnder20(h);
    else if(m == 30)
        return "half past " + GetNumberUnder20(h);
    else if(m == 45)
        return "quarter to " + GetNumberUnder20(h+1);
    else if(m < 30)
        return GetNumber(m) + " minute" + (m == 1 ? "" : "s") + " past " + GetNumberUnder20(h);
    else
        return GetNumber(60 - m) + " minutes to " + GetNumberUnder20(h+1);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int h;
    cin >> h;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int m;
    cin >> m;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string result = timeInWords(h, m);

    fout << result << "\n";

    fout.close();

    return 0;
}
