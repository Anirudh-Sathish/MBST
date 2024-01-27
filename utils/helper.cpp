#pragma once
#include <iostream>
#include <string>
#include<vector>
using namespace std;

void generatePermutations(vector<int>& current, int length, vector<string>& result) {
    if (current.size() == length) {
        string permutation;
        for (int digit : current) {
            permutation += to_string(digit);
        }
        result.push_back(permutation);
        return;
    }
    current.push_back(0);
    generatePermutations(current, length, result);
    current.pop_back();  

    current.push_back(1);
    generatePermutations(current, length, result);
    current.pop_back();  
}

vector<string> generateStrings(int n) {
    string currentString(n, '0');
    vector<string> stringList;
    vector<int> current;

    generatePermutations(current, n, stringList);
    return stringList;
}
