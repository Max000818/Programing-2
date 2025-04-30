#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <set>
using namespace std;

class ReadingManager {
public:
    void Read(int user_id, int page_count) {
        if (user_pages_.count(user_id)) {
            pages_.erase(pages_.find(user_pages_[user_id]));
        }
        user_pages_[user_id] = page_count;
        pages_.insert(page_count);
    }

    double Cheer(int user_id) const {
        if (!user_pages_.count(user_id)) {
            return 0;
        }
        if (user_pages_.size() == 1) {
            return 1;
        }
        int page_count = user_pages_.at(user_id);
        auto it = pages_.lower_bound(page_count);
        double less = distance(pages_.begin(), it);
        return less / (pages_.size() - 1);
    }

private:
    unordered_map<int, int> user_pages_;
    multiset<int> pages_;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}