#include "main.h"

nnoeud creer_noeud (int val, char lettre){
    nnoeud n = malloc(sizeof(struct noeud));
    n->val = val;
    n->lettre = lettre;
    n->fd = NULL;
    n->fg = NULL;
    return n;
}


void aff_noeud (nnoeud n){
    printf("valeur du noeud : %d\n", n->val);
    if (n->fg != NULL){
        printf("as un fils gauche de valeur %d, ", n->fg->val);
    }else{
        printf("n'as pas de fils gauche, ");
    }
    if (n->fd != NULL){
        printf("as un fils droit de valeur %d\n", n->fd->val);
    }else{
        printf("n'as pas de fils droit\n");
    }
}


void aff_tree (nnoeud n){
    if (n != NULL){
        printf("%d%c ", n->val, n->lettre);
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


void aff_tab_node (nnoeud* tab, int taille){
    for(int i = 0; i<taille; i++){
        if(tab[i]->val == (-1)){
            printf(" (null)");
        }else{
            printf(" (%d|%c)", tab[i]->val, tab[i]->lettre);
        }
    }
    printf("\n");
}


void del_noeud(nnoeud*  n){
    free((*n));
    (*n) = NULL;
}


void del_tree (nnoeud* n){
    nnoeud tmpn = *n;
    if(!n) {
        return;
    }
    if(tmpn->fg){
        del_tree(&tmpn->fg); 
    }  
    if(tmpn->fd) {
        del_tree(&tmpn->fd);
    }
    free(tmpn);      
    *n = NULL;
}


int search(nnoeud n, int val){
    if(n->val == val){
        return 1;
    }
    if(n->val > val && n->fg != NULL){
        return (search(n->fg, val));
    }
    if(n->val < val && n->fd != NULL){
        return (search(n->fd, val));
    }
    return 0;
}


int taille(nnoeud n){
    if(n != NULL){
        return 1 + taille(n->fg) + taille(n->fd);
    }
    else return 0;
}


nnoeud* tab_node(int taille){
    nnoeud *tab = malloc(sizeof(struct noeud) * taille);
    for(int i = 0; i<taille; i++){
        tab[i] = creer_noeud(-1, ' ');
    }
    return tab;
}


void lecture(nnoeud* tab){
    FILE* fichier = NULL;
    fichier = fopen("test.txt", "r");

    int caractereActuel = 0;
    if (fichier != NULL){
        while(caractereActuel != EOF){
            caractereActuel = fgetc(fichier);

            int i = 0;
            int b = 1;

            while(tab[i]->val != (-1) && b == 1){
                if((tab[i]->lettre) == caractereActuel){
                    (tab[i]->val)++;
                    b = 0;
                }else{
                    i++;
                }
            }

            if(tab[i]->val == (-1)){
                tab[i]->val = 1;
                tab[i]->lettre = caractereActuel;
            }
        }
    //     puts("\n");
        fclose(fichier);
    }else{
        printf("Impossible d'ouvrir le fichier\n");
    }
}


void fusion(nnoeud* tab, int taille){

    int petit1 = tab[0]->val;
    int case_petit1 = 0;
    int petit2 = tab[1]->val;
    int case_petit2 = 1;

    if((petit1 > petit2) || (petit1 == petit2 && tab[case_petit1]->lettre > tab[case_petit2]->lettre)){
        petit1 = tab[1]->val;
        case_petit1 = 1;
        petit2 = tab[0]->val;
        case_petit2 = 0;
    }

    for(int i = 0; i<(taille - 1); i++){
        if((tab[i]->val < petit1) || (tab[i]->val == petit1 && tab[i]->lettre < tab[case_petit1]->lettre)){
            petit2 = petit1;
            case_petit2 = case_petit1;
            petit1 = tab[i]->val;
            case_petit1 = i;
        }else if((tab[i]->val < petit2) || (tab[i]->val == petit2 && tab[i]->lettre < tab[case_petit2]->lettre)){
            petit2 = tab[i]->val;
            case_petit2 = i;
        }
    }

    printf("petit 1 : %d\n", petit1);
    printf("petit 2 : %d\n", petit2);
    printf("case petit 1 : %d\n", case_petit1);
    printf("case petit 2 : %d\n", case_petit2);
}


void supprimer_struct_tab(nnoeud* tab, int i){
    //supprime tab[i] et redimentionne le tableau
}

void ajouter_struct_tab(nnoeud* tab, nnoeud n){
    //ajoute n dans tab sans soucis de placement
}


int contains (char* chaine1, char* acomparer){
    char* str1 = malloc(sizeof(char)*strlen(chaine1));
    strcpy(str1, chaine1);
    char* str2 = malloc(sizeof(char)*1);
    strncpy(str2, acomparer, 1);
    char ret = malloc(sizeof(char) 12);
    ret = strpbrk(str1, str2);
    if(ret) {
       return(1);
    } else {
       return(-1);
    }
}


int nb_char_in_file(){
    FILE* fichier = NULL;
    int caractereActuel = 0;
    int nb = 0;
    fichier = fopen("16chardiff.txt", "r");
    if (fichier != NULL){
        // Boucle de lecture des caractères un à un
        do{
            caractereActuel = fgetc(fichier); // On lit le caractère
            nb++; // On l'affiche
        } while (caractereActuel != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
        fclose(fichier);
    }
    return nb;
}


int nb_char_diff(int taille){
    FILE* fichier = NULL;
    char* presents = malloc(sizeof(char) * taille);
    int diff = 0;
    char caractereActuel = '0';
    fichier = fopen("16chardiff.txt", "r");
    if (fichier != NULL){
        // Boucle de lecture des caractères un à un
        do{
            caractereActuel = fgetc(fichier); // On lit le caractère
            char* c = malloc(sizeof(char));
            strncpy(c, &caractereActuel, 1);
            if(contains(presents, c) == -1){
                strncpy(&presents[diff], c, 1);
                diff++;
            }
        } while (caractereActuel != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
        fclose(fichier);
    }
    return (diff-1);
}


int main() {
    int taille = 12;
    nnoeud* tableau = tab_node(taille);   //pour une raison a determiner, prevoir une case de plus

    printf("\n");
    aff_tab_node (tableau, taille);

    lecture(tableau);

    printf("\n");
    aff_tab_node (tableau, taille);
    printf("\n");

    fusion(tableau, taille);

    return 0;
}
