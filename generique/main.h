//
// Created by fabrice bazire on 18/09/2018.
//

#ifndef PROJET_MAIN_H
#define PROJET_MAIN_H

#include <stdio.h>
#include <stdlib.h>

struct noeud {
    void* val;
    struct noeud* fg;
    struct noeud* fd;
};

typedef struct noeud* nnoeud;

nnoeud creer_noeud (int val);

// void aff_noeud (nnoeud n);

void aff_tree (nnoeud n);

// void del_noeud (nnoeud* n);

// void del_tree (nnoeud* n);

// int search (nnoeud n, int val);

// int taille(nnoeud n);

#endif //PROJET_MAIN_H
