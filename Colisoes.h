#ifndef COLISOES_H
#define COLISOES_H

struct BoundingBox {
    float x, y;
    float width, height;
};

bool checkCollision(const BoundingBox& a, const BoundingBox& b);

#endif
