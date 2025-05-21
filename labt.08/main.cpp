#include <iostream>
#include <list>
#include <map>
#include <string>
#include <iterator>

#include "profile.h"

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    LOG_DURATION("Total execution time");

    std::list<int> lineup;
    std::map<int, std::list<int>::iterator> athlete_iterators;

    int num_operations;
    std::cin >> num_operations;

    for (int i = 0; i < num_operations; ++i) {
        int new_athlete_id;
        int target_athlete_id;
        
        std::cin >> new_athlete_id >> target_athlete_id;

        auto map_entry_it = athlete_iterators.find(target_athlete_id);

        if (map_entry_it != athlete_iterators.end()) {
            std::list<int>::iterator insert_before_iter = map_entry_it->second;
            std::list<int>::iterator new_athlete_list_iter = lineup.insert(insert_before_iter, new_athlete_id);
            athlete_iterators[new_athlete_id] = new_athlete_list_iter;
        } else {
            lineup.push_back(new_athlete_id);
            std::list<int>::iterator new_athlete_list_iter = std::prev(lineup.end());
            athlete_iterators[new_athlete_id] = new_athlete_list_iter;
        }
    }

    for (int athlete_id : lineup) {
        std::cout << athlete_id << "\n";
    }

    return 0;
}