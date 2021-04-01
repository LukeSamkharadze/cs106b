#include <bits/stdc++.h>

using namespace std;

int findMaximum(vector<vector<int>>& matrix, int i, int j, vector<vector<int>>& usedPoints)
{
    int sum = 0;
    for(int dy = -1; dy <= 1; dy++)
    {
        for(int dx = -1; dx <= 1; dx++)
        {
            if(i+dy < 0 || j+dx < 0 || i+dy >= matrix.size() || j+dx >= matrix[0].size())
               continue;

            bool flag = true;
            for(int k = 0; k < usedPoints.size(); k++)
                if(i+dy == usedPoints[k][0] && j+dx == usedPoints[k][1])
                    flag = false;
            if(flag == false)
                continue;

            if(matrix[i+dy][j+dx] == 1)
            {
                vector<int> cordinate;
                cordinate.push_back(i+dy);
                cordinate.push_back(j+dx);
                usedPoints.push_back(cordinate);
                sum += 1 + findMaximum(matrix, i + dy, j+dx, usedPoints);
            }
        }
    }

    return sum;
}

int connectedCell(vector<vector<int>> matrix) 
{
    vector<vector<int>> usedPoints;
    int maximum = 0;

    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix[0].size(); j++)
        {
            if(matrix[i][j] == 1)
            {
                vector<vector<int>> usedPoints;

                vector<int> cordinate;
                cordinate.push_back(i);
                cordinate.push_back(j);
                usedPoints.push_back(cordinate);

                int currentValue = findMaximum(matrix, i, j, usedPoints) + 1;
                if(maximum < currentValue)
                    maximum = currentValue;
            }
        }
    }
    cout << maximum << endl;
    return maximum;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int m;
    cin >> m;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> matrix(n);
    for (int i = 0; i < n; i++) {
        matrix[i].resize(m);

        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = connectedCell(matrix);

    fout << result << "\n";

    fout.close();

    return 0;
}
