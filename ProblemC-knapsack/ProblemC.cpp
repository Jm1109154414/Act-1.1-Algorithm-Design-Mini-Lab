//You have n study modules. Each module i requires time[i] hours and yields value[i] points of learning benefit. You have a total available time budget T. Each module can be taken at most once.

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {

    ios::sync_with_stdio(false);

    cin.tie(nullptr);

    int n, T;

    cin >> n >> T;

    vector<int> t(n);

    vector<ll> v(n);

    for (int i = 0; i < n; i++) {

        cin >> t[i] >> v[i];

    }

    // TODO: compute maximum value achievable within time T
    vector<vector<ll>> dp(n + 1, vector<ll>(T + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int budget = 0; budget <= T; budget++) {
           ll noTomar = dp[i - 1][budget];
           
           ll siTomar= 0;
           if (t[i - 1] <= budget) {
               siTomar = v[i - 1] + dp[i - 1][budget - t[i - 1]];
           }

            dp[i][budget] = max(noTomar, siTomar);
        }
    }

    ll best = dp[n][T];

    cout << best << "\n";

    return 0;

}