#include "Colisoes.h"

bool checkCollision(const BoundingBox& a, const BoundingBox& b) {
    return (a.x - a.width / 2 < b.x + b.width / 2 &&
            a.x + a.width / 2 > b.x - b.width / 2 &&
            a.y - a.height / 2 < b.y + b.height / 2 &&
            a.y + a.height / 2 > b.y - b.height / 2);
}
