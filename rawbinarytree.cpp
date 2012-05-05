
#include <stdio.h>

#include "rawbinarytree.h"
#include "voronoi.h"


template <>
void RawBinaryTree<Voronoi::SitePtr>::print() {

    RawBinaryTree<Voronoi::SitePtr>* node = minimum();

    while (node != nullptr) {
        printf("%d ", node->value->position.x);
        node = node->next();
    }
    printf("\n");
}











