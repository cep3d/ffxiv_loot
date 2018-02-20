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
#include <stdlib.h>
#include <chrono>   // std::chrono
#include "color.h"

#define MIN_LOOT    (1)
#define MAX_LOOT    (99)

enum State {PASS = 0, NEED, GREED};
const char *StateStr[] = {"Pass", "Neeed", "Greed"};

typedef struct Party {
    int pos;
    int lot;
    int state;
}party_t;

void drawing_lot(int mode, const char *item, int max_party = 4) {
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
        //free(p);
    }
    
    std::uniform_int_distribution<> lots(MIN_LOOT, MAX_LOOT);

    for (auto &pt: party_list) {
        int lot = lots(generator);
        pt.lot = lot;
        if (pt.state == 0) { pt.lot = 0; }
        if (pt.pos == 0) {
            std::cout << BOLDCYAN << "[*]";
        } else {
            std::cout << RESET << "   ";
        }
        
        std::cout << "P" << (pt.pos + 1) << "は" << item << "に" << StateStr[pt.state] << "のダイスで" << lot << "を出した。" << '\n';
        //std::cout << "P" << (pt.pos + 1) << ": " << lot << " [" << (pt.state) << "]" << '\n';
    }
    
    /**
     * Get max element in a vector of structures in c++
     * @see - https://stackoverflow.com/questions/16772477/how-to-get-min-or-max-element-in-a-vector-of-structures-in-c-based-on-some-fi
     */
    std::vector<party_t>::iterator itr;
    itr = std::max_element(party_list.begin(), party_list.end(), [](party_t &p1, party_t &p2) { return p1.lot < p2.lot; });
    std::cout << "P" << (itr->pos + 1) << "は" << item << "を手に入れた。" << '\n';
}

int main(int argc, const char * argv[]) {
    char mode;
    std::cout << "ロットしてください。[(N)eed/(G)reed/(P)ass]";
    std::cin >> mode;
    if (mode == 'N') {
        std::cout << "Needしました。" << '\n';
    } else if(mode == 'G') {
        std::cout << "Greedしました。" << '\n';
    } else {
        std::cout << "Passしました。" << '\n';
    }
    /**
     * 処理計測
     * @see - http://en.cppreference.com/w/cpp/chrono
     */
    std::chrono::system_clock::time_point start, end;
    start = std::chrono::system_clock::now(); // 計測開始
    
    std::cout << StateStr[0] << '\n';
    std::map<char, int> choose;
    choose['N'] = NEED;
    choose['G'] = GREED;
    choose['P'] = PASS;
    drawing_lot(choose[mode], "アイテム", 8);
    
    end = std::chrono::system_clock::now();
    double elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "処理計測: " << elapsed << " ms" << '\n';
    return 0;
}
