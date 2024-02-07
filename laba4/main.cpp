#include<iostream>
#include <vector>
using namespace std;

vector<int> findLCS(const vector<int>& sequence1, const vector<int>& sequence2) {
    int m = sequence1.size();
    int n = sequence2.size();

    // Create a 2D vector to store the lengths of LCS for subproblems
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (sequence1[i - 1] == sequence2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    int i = m;
    int j = n;
    vector<int> lcs;

    while (i > 0 && j > 0) {
        if (sequence1[i - 1] == sequence2[j - 1]) {
            lcs.insert(lcs.begin(), sequence1[i - 1]);
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    return lcs;
}

int main() {
    vector<int> sequence1 = {1, 2, 3, 4};
    vector<int> sequence2 = {6, 4, 1, 2, 1, 3};

    vector<int> lcs = findLCS(sequence1, sequence2);

    // Output the result
    cout << "Longest Common Subsequence: ";
    for (int num : lcs) {
        cout << num << " ";
    }

    return 0;
}

