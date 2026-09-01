#include <bits/stdc++.h>

using namespace std;
using ll = long long;



int main() {

    ios::sync_with_stdio(false);

    cin.tie(nullptr);

    int m;

    cin >> m;

    vector<pair<ll,ll>> meetings(m);

    for (int i = 0; i < m; i++) {

        ll s, e;

        cin >> s >> e;

        meetings[i] = {s, e};

    }

    vector<ll> startTimes(m), endTimes(m);
    for (int i = 0; i < m; i++){
        startTimes[i] = meetings[i].first;
        endTimes[i] = meetings[i].second;
    }

    sort(startTimes.begin(), startTimes.end());
    sort(endTimes.begin(), endTimes.end());

    int i = 0, j = 0;
    int rooms = 0, maxRooms = 0;

    while (i < m && j < m) {
        if (startTimes[i] < endTimes[j]) {
            rooms++;
            maxRooms = max(maxRooms, rooms);
            i++;
        } else {
            rooms--;
            j++;
        }
    }

    cout << maxRooms << "\n";
    return 0;

}