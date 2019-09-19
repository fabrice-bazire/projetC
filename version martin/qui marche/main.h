//
// Created by fabrice bazire on 18/09/2018.
//

#ifndef PROJET_MAIN_H
#define PROJET_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct noeud {
    int val;
    char lettre;
    int id;
    char* code;
    struct noeud* fg;
    struct noeud* fd;
};

typedef struct noeud* nnoeud;

struct maillon {
	struct noeud* n;
	struct maillon* suivant; 
};

typedef struct maillon* mmaillon;

mmaillon creer_maillon (nnoeud n);

nnoeud creer_noeud (int val, char lettre, int id);

nnoeud creer_noeud_complet (int val, char lettre, int id, nnoeud fg, nnoeud fd);

void aff_noeud (nnoeud n);

void aff_maillon (mmaillon m);

void aff_liste (mmaillon m);

void aff_tree (nnoeud n);

void aff_code (nnoeud n);

void del_noeud (nnoeud* n);

void del_tree (nnoeud* n);

int search (nnoeud n, int val);

int size_tree(nnoeud n);

int size_liste (mmaillon m);

nnoeud fusion_par_2(nnoeud x, nnoeud y);

mmaillon lecture();

nnoeud fusion(mmaillon m);

int contains (char* chaine1, char* acomparer);

int nb_char_in_file();

int nb_char_diff(int taille);

mmaillon ajouter_tete (mmaillon ajout, mmaillon liste);

mmaillon ajouter_queue (mmaillon ajout, mmaillon liste);

mmaillon sup_tete (mmaillon liste);

mmaillon sup_queue (mmaillon liste);

mmaillon supp_maillon (nnoeud sup, mmaillon liste);

void affectation_code (nnoeud n, const char * prefix, char* car);

void mets_les_arguments_dans_fichier (int argc, char *argv[]);

#endif //PROJET_MAIN_H
