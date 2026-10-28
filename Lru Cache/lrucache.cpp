#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

class LRUCache {
private:
    int capacity;
    list<pair<int, int>> cache;
    unordered_map<int, list<pair<int, int>>::iterator> mp;

public:
    LRUCache(int cap) {
        capacity = cap;
    }

    void put(int key, int value) {
        if (capacity <= 0) {
            cout << "Cache capacity must be positive.\n";
            return;
        }

        if (mp.find(key) != mp.end()) {
            mp[key]->second = value;
            cache.splice(cache.begin(), cache, mp[key]);
            cout << "Key updated successfully.\n";
            return;
        }

        if ((int)cache.size() == capacity) {
            int lruKey = cache.back().first;
            cache.pop_back();
            mp.erase(lruKey);
            cout << "Evicted key: " << lruKey << '\n';
        }

        cache.push_front({key, value});
        mp[key] = cache.begin();

        cout << "Entry inserted successfully.\n";
    }

    int get(int key) {
        auto it = mp.find(key);

        if (it == mp.end()) {
            cout << "Key not found in cache.\n";
            return -1;
        }

        cache.splice(cache.begin(), cache, it->second);

        cout << "Value: " << it->second->second << '\n';
        return it->second->second;
    }

    void remove(int key) {
        auto it = mp.find(key);

        if (it == mp.end()) {
            cout << "Key not found.\n";
            return;
        }

        cache.erase(it->second);
        mp.erase(it);

        cout << "Entry deleted successfully.\n";
    }

    void display() {
        if (cache.empty()) {
            cout << "Cache is empty.\n";
            return;
        }

        cout << "\nCache (MRU -> LRU):\n";

        for (const auto &entry : cache) {
            cout << "[Key: " << entry.first
                 << ", Value: " << entry.second << "]\n";
        }
    }

    void showStats() {
        cout << "Capacity: " << capacity << '\n';
        cout << "Current entries: " << cache.size() << '\n';
        cout << "Available slots: "
             << capacity - (int)cache.size() << '\n';
    }
};

int main() {
    int capacity;

    cout << "=================================\n";
    cout << "       LRU CACHE SYSTEM\n";
    cout << "=================================\n";

    cout << "Enter cache capacity: ";
    cin >> capacity;

    if (!cin || capacity <= 0) {
        cout << "Invalid capacity. Enter a positive integer.\n";
        return 1;
    }

    LRUCache lru(capacity);

    int choice, key, value;

    do {
        cout << "\n========== MENU ==========\n";
        cout << "1. Insert / Update\n";
        cout << "2. Get Value\n";
        cout << "3. Delete Entry\n";
        cout << "4. Display Cache\n";
        cout << "5. Show Statistics\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input.\n";
            return 1;
        }

        switch (choice) {
            case 1:
                cout << "Enter key and value: ";
                if (!(cin >> key >> value)) {
                    cout << "Invalid input.\n";
                    return 1;
                }
                lru.put(key, value);
                break;

            case 2:
                cout << "Enter key to search: ";
                if (!(cin >> key)) {
                    cout << "Invalid input.\n";
                    return 1;
                }
                lru.get(key);
                break;

            case 3:
                cout << "Enter key to delete: ";
                if (!(cin >> key)) {
                    cout << "Invalid input.\n";
                    return 1;
                }
                lru.remove(key);
                break;

            case 4:
                lru.display();
                break;

            case 5:
                lru.showStats();
                break;

            case 6:
                cout << "Exiting LRU Cache System.\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 6);

    return 0;
}