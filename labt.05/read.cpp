#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

class FenwickTree {
private:
    vector<int> tree;

public:
    FenwickTree(int size) : tree(size + 2, 0) {}

    void Update(int index, int delta) {
        index++;
        while (index < tree.size()) {
            tree[index] += delta;
            index += index & -index;
        }
    }

    int Query(int index) const {
        index++;
        int sum = 0;
        while (index > 0) {
            sum += tree[index];
            index -= index & -index;
        }
        return sum;
    }
};

class ReadingManager {
public:
    ReadingManager() : user_pages_(MAX_USER_ID_ + 1, 0), total_users_(0), fenwick_(MAX_PAGE_ + 1) {}

    void Read(int user_id, int page_count) {
        int old_page = user_pages_[user_id];
        if (old_page != 0) {
            fenwick_.Update(old_page, -1);
        } else {
            total_users_++;
        }
        user_pages_[user_id] = page_count;
        fenwick_.Update(page_count, 1);
    }

    double Cheer(int user_id) const {
        int page = user_pages_[user_id];
        if (page == 0) return 0.0;
        if (total_users_ == 1) return 1.0;

        int count_less = fenwick_.Query(page - 1);
        return static_cast<double>(count_less) / (total_users_ - 1);
    }

private:
    static const int MAX_USER_ID_ = 100'000;
    static const int MAX_PAGE_ = 1000;

    vector<int> user_pages_;
    int total_users_;
    FenwickTree fenwick_;
};

int main() {
    freopen("input.txt", "r", stdin);
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