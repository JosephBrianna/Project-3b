#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <iomanip>
#include <utility>
#include <limits>

using namespace std;

struct Player {
    int id;
    string name;
    int score;
};

// Higher score ranks first. For ties, lower player ID ranks first.
bool ranksBefore(const Player& a, const Player& b) {
    if (a.score != b.score) return a.score > b.score;
    return a.id < b.id;
}

// TEAMMATE 1: Data generation and user interface.
vector<Player> generatePlayers(int count) {
    mt19937 generator(42); // Fixed seed: same demonstration data every run.
    uniform_int_distribution<int> scoreDistribution(0, 10000);
    vector<Player> players;
    players.reserve(count);

    for (int id = 1; id <= count; ++id) {
        players.push_back({id, "Player_" + to_string(id), scoreDistribution(generator)});
    }
    return players;
}

// TEAMMATE 2: Heap Sort 

// TEAMMATE 3: Merge Sort 

// Benchmark BOTH algorithms every time menu options 1, 2 or 3 are selected.
void runComparison(const vector<Player>& original, int choice) {
    vector<Player> heapPlayers = original;
    vector<Player> mergePlayers = original;
    using Clock = chrono::steady_clock;

    auto heapStart = Clock::now();
    heapSort(heapPlayers);
    auto heapEnd = Clock::now();

    auto mergeStart = Clock::now();
    mergeSort(mergePlayers);
    auto mergeEnd = Clock::now();

    double heapMs = chrono::duration<double, milli>(heapEnd - heapStart).count();
    double mergeMs = chrono::duration<double, milli>(mergeEnd - mergeStart).count();

    if (choice == 1) {
        cout << "\nTOP 10 PLAYERS (displayed from Heap Sort)\n";
        showPlayers(heapPlayers, true);
    } else if (choice == 2) {
        cout << "\nBOTTOM 10 PLAYERS (displayed from Heap Sort)\n";
        showPlayers(heapPlayers, false);
    }

    cout << "\n=== SORTING PERFORMANCE: " << original.size() << " PLAYERS ===\n";
    cout << fixed << setprecision(3);
    cout << "Heap Sort : " << heapMs << " ms\n";
    cout << "Merge Sort: " << mergeMs << " ms\n";
    cout << "Faster this run: "
         << (heapMs < mergeMs ? "Heap Sort" : mergeMs < heapMs ? "Merge Sort" : "Tie")
         << '\n';
    cout << "Correct order: "
         << (isRankedCorrectly(heapPlayers) && isRankedCorrectly(mergePlayers) ? "YES" : "NO")
         << '\n';
    cout << "Same results:  " << (sameLeaderboard(heapPlayers, mergePlayers) ? "YES" : "NO")
         << "\n";
    cout << "(Times measure sorting only, not menu display or data generation.)\n";
}

int main() {
    const int PLAYER_COUNT = 100000;
    const vector<Player> players = generatePlayers(PLAYER_COUNT);

    while (true) {
        cout << "\n========== VIDEO GAME LEADERBOARD ==========\n";
        cout << PLAYER_COUNT << " fictional players loaded\n";
        cout << "1. Display Top 10 Players + Compare Times\n";
        cout << "2. Display Bottom 10 Players + Compare Times\n";
        cout << "3. Compare Heap Sort vs. Merge Sort\n";
        cout << "4. Exit\n";
        cout << "Choose an option (1-4): ";

        int choice;
        if (!(cin >> choice)) {
            if (cin.eof()) break;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number from 1 to 4.\n";
            continue;
        }
        if (choice == 4) {
            cout << "Goodbye!\n";
            break;
        }
        if (choice >= 1 && choice <= 3)
            runComparison(players, choice);
        else
            cout << "Please choose 1, 2, 3, or 4.\n";
    }
    return 0;
}
