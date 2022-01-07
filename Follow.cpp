#include "Follow.h"
const map<char, set<char>> &Follow::getFollow1() const {
    return FOLLOW;
}

void Follow::setFollow(const map<char, set<char>> &follow) {
    FOLLOW = follow;
}