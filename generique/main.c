#include "main.h"

nnoeud creer_noeud (void* val){
    nnoeud n = malloc(sizeof(struct noeud));
    n->val = val;
    n->fd = NULL;
    n->fg = NULL;
    return n;
}

// void aff_noeud (nnoeud n){
//     printf("valeur du noeud : %d\n", n->val);
//     if (n->fg != NULL){
//         printf("as un fils gauche de valeur %d, ", n->fg->val);
//     }else{
//         printf("n'as pas de fils gauche, ");
//     }
//     if (n->fd != NULL){
//         printf("as un fils droit de valeur %d\n", n->fd->val);
//     }else{
//         printf("n'as pas de fils droit\n");
//     }
// }



void aff_tree (nnoeud n){
    if (n != NULL){
        printf("%d ", *((int*)n->val));
    }else{
        puts("Arbre vide !!");
        return;
    } 
    if (n->fg != NULL){
        aff_tree(n->fg);
    }
    if (n->fd != NULL){
        aff_tree(n->fd);
    }
}

// void del_noeud(nnoeud*  n){
//     free((*n));
//     (*n) = NULL;
// }

// void del_tree (nnoeud* n){
//     nnoeud tmpn = *n;
//     if(!n) {
//         return;
//     }
//     if(tmpn->fg){
//         del_tree(&tmpn->fg); 
//     }  
//     if(tmpn->fd) {
//         del_tree(&tmpn->fd);
//     }
//     free(tmpn);      
//     *n = NULL;
// }


// int search(nnoeud n, int val){
//     if(n->val == val){
//         return 1;
//     }
//     if(n->val > val && n->fg != NULL){
//         return (search(n->fg, val));
//     }
//     if(n->val < val && n->fd != NULL){
//         return (search(n->fd, val));
//     }
//     return 0;
// }



// int taille(nnoeud n){
//     if(n != NULL){
//         return 1 + taille(n->fg) + taille(n->fd);
//     }
//     else return 0;
// }


int main() {
    int a = 8;
    void* ptr = &a;
    nnoeud n = creer_noeud(ptr);
    aff_tree(n);
    puts("\n");
    // n->fd = creer_noeud(10);
    // n->fg->fg = creer_noeud(1);
    // n->fg->fd = creer_noeud(6);
    // n->fg->fd->fg = creer_noeud(4);
    // n->fg->fd->fd = creer_noeud(7);
    // n->fd->fd = creer_noeud(14);
    // n->fd->fd->fg = creer_noeud(13);

    // aff_tree(n);
    // puts("\n");
    // //printf("La taille de l'arbre est de : %d\n", taille(n));

    // printf("resultat de la recherche de 8 : %d\n", search(n, 8));
    // printf("resultat de la recherche de 3 : %d\n", search(n, 3));
    // printf("resultat de la recherche de 10 : %d\n", search(n, 10));
    // printf("resultat de la recherche de 1 : %d\n", search(n, 1));
    // printf("resultat de la recherche de 6 : %d\n", search(n, 6));
    // printf("resultat de la recherche de 14 : %d\n", search(n, 14));
    // printf("resultat de la recherche de 4 : %d\n", search(n, 4));
    // printf("resultat de la recherche de 7 : %d\n", search(n, 7));
    // printf("resultat de la recherche de 13 : %d\n", search(n, 13));
    // printf("resultat de la recherche de 9 (n'existe pas) : %d\n", search(n, 9));

    // del_tree(&n);

    // aff_tree(n);
    return 0;
}
