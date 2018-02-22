//
//  main.cpp
//  loot-luck
//
//  Created by cep3d on 2018/02/20.
//  Copyright © 2018 cep3d. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <random>
#include <iomanip>  // std::setprecision
#include <iterator> // std::distance
#include <chrono>   // std::chrono
#include "color.h"

#define MIN_LOOT    (1)
#define MAX_LOOT    (99)

enum State {PASS = 0, GREED, NEED};
const char *StateStr[] = {"Pass", "Greed", "Need"};

typedef struct Party {
    int pos;
    int lot;
    int state;
}party_t;

/**
 * ロット
 * @param mode - ロットタイプ
 * @param item - アイテム名
 * @param max_party - パーティ人数
 */
void drawing_loot(int mode, const char *item, int max_party = 4);


int main(int argc, const char * argv[]) {
    char mode;
    std::cout << "Loot Phase [(N)eed/(G)reed/(P)ass]: ";
    std::cin >> mode;
    /**
     * 処理計測
     * @see - http://en.cppreference.com/w/cpp/chrono
     */
    std::chrono::system_clock::time_point start, end;
    start = std::chrono::system_clock::now(); // 計測開始
    
    std::map<char, int> choose;
    choose['N'] = NEED;
    choose['G'] = GREED;
    choose['P'] = PASS;
    drawing_loot(choose[mode], "Halonic friar's ring", 8);
    
    end = std::chrono::system_clock::now();
    double elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Elapsed Time: " << elapsed << " μs" << '\n';
    std::cout << '\t' << std::fixed << std::setprecision(6) << (elapsed/1000000) << " sec" << '\n';
    return 0;
}

void drawing_loot(int mode, const char *item, int max_party) {
    std::random_device dev;
    std::mt19937 generator(dev());
    
    std::uniform_int_distribution<> st(0,2);
    std::vector<party_t> party_list;
    for (int a = 0; a < max_party; ++a) {
        int state = st(generator);
        party_t p = {0, 0};
        p.pos = a;
        p.lot = 0;
        p.state = (a == 0) ? mode : state;
        party_list.push_back(p);
    }
    
    std::uniform_int_distribution<> lots(MIN_LOOT, MAX_LOOT);
    
    for (auto &pt: party_list) {
        int lot = lots(generator);
        pt.lot = lot;
        if (pt.state == PASS) { pt.lot = 0; }
        if (pt.pos == 0) {
            std::cout << BOLDCYAN;
            if (pt.state == PASS) {
                std::cout << "You casts rot for the " << item << ".";
            } else {
                std::cout << "You roll " << StateStr[pt.state] << " on the " << item << "." << pt.lot << "!";
            }
            std::cout << '\n';
        } else {
            std::cout << RESET << "   ";
            if (pt.state == PASS) {
                std::cout << "P" << (pt.pos + 1) << " casts rot for the " << item << ".";
            } else {
                std::cout << "P" << (pt.pos + 1) << " rolls " << StateStr[pt.state] << " on the " << item << "." << pt.lot << "!";
            }
            std::cout << '\n';
        }
    }

    // Needのみ
    std::vector<party_t> group;
    for (auto &a : party_list) {
        if (a.state == NEED) {
            group.push_back(a);
        }
    }
    // Needがない場合大元のコンテナを格納
    if (group.empty()) {
        group.swap(party_list);
    }
    
    /**
     * Get max element in a vector of structures in c++
     * @see - https://stackoverflow.com/questions/16772477/how-to-get-min-or-max-element-in-a-vector-of-structures-in-c-based-on-some-fi
     */
    std::vector<party_t>::iterator itr;
    itr = std::max_element(group.begin(), group.end(), [](party_t &p1, party_t &p2) {
        return p1.lot < p2.lot;
    });
    if (itr->pos == 0) {
        std::cout << "You obtain a " << item << "." << '\n';
        std::cout << "The " << item << " is added to your inventory.";
    } else {
        std::cout << "P" << (itr->pos + 1) << " obtain a " << item << ".";
    }
    std::cout << '\n';
}

