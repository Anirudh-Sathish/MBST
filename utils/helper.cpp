#pragma once
#include <iostream>
#include <string>
#include<vector>
using namespace std;
void generateStringsUtil(int m, int n, int index, int count, string &currentString , vector<string> &stringList) {
    if (count == m) {
        // cout << currentString << endl;
        stringList.push_back(currentString);
        return;
    }
    if (index < n) {
        currentString[index] = '0';
        generateStringsUtil(m, n, index + 1, count, currentString, stringList);

        currentString[index] = '1';
        generateStringsUtil(m, n, index + 1, count + 1, currentString, stringList);
    }
}

vector<string> generateStrings(int m, int n) {
    string currentString(n, '0');
    vector<string> stringList;
    generateStringsUtil(m, n, 0, 0, currentString, stringList);
    return stringList;
}
