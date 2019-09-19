//
// Created by fabrice bazire on 18/09/2018.
//

#ifndef PROJET_MAIN_H
#define PROJET_MAIN_H

#include <stdio.h>
#include <stdlib.h>

struct noeud {
    int val;
    char lettre;
    struct noeud* fg;
    struct noeud* fd;
};

typedef struct noeud* nnoeud;

nnoeud creer_noeud (int val, char lettre);

void aff_noeud (nnoeud n);

void aff_tree (nnoeud n);

void aff_tab_node(nnoeud* tab, int taille);

void del_noeud (nnoeud* n);

void del_tree (nnoeud* n);

int search (nnoeud n, int val);

int taille(nnoeud n);

nnoeud* tab_node(int taille);

void lecture();

void fusion(nnoeud* tab, int taille);

void supprimer_struct_tab(nnoeud* tab, int i);

void ajouter_struct_tab(nnoeud* tab, nnoeud n);

int contains (char* chaine1, char* acomparer);

int nb_char_in_file();

int nb_char_diff(int taille);

#endif //PROJET_MAIN_H
