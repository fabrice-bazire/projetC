#include "main.h"
int mon_indice = 0;

mmaillon creer_maillon (nnoeud n){
    mmaillon m = malloc(sizeof(struct maillon));
    m->n = n;
    m->suivant = NULL;
    return m;
}//ok ok


nnoeud creer_noeud (int val, char lettre, int id){
    nnoeud n = malloc(sizeof(struct noeud));
    n->val = val;
    n->lettre = lettre;
    n->id = id;
    n->code = NULL;
    n->fd = NULL;
    n->fg = NULL;
    return n;
}//ok ok


nnoeud creer_noeud_complet (int val, char lettre, int id, nnoeud fg, nnoeud fd){
    nnoeud n = malloc(sizeof(struct noeud));
    n->val = val;
    n->lettre = lettre;
    n->id = id;
    n->code = NULL;
    n->fd = fd;
    n->fg = fg;
    return n;
}//ok ok


void aff_noeud (nnoeud n){
    printf("(%d|%c|%d|%s) ", n->val, n->lettre, n->id, n->code);
}//ok ok


void aff_maillon (mmaillon m){
    if (m == NULL){
        puts("le maillon est vide");
    }else{
        aff_noeud(m->n);
    }
}//ok ok


void aff_liste (mmaillon m){
    if (m == NULL){
        aff_maillon(m);
    }
    while(m != NULL){
        aff_maillon (m);
        m = m->suivant;
    }
    puts("\n");
}//ok ok


void aff_tree (nnoeud n){
    if (n != NULL){
        printf("(%d|%c|%d) ", n->val, n->lettre, n->id);
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
}//ok ok


void aff_code (nnoeud n){
    if (n != NULL){
        printf("(%s), ", n->code);
    }else{
        puts("Arbre vide !!");
        return;
    } 
    if (n->fg != NULL){
        aff_code(n->fg);
    }
    if (n->fd != NULL){
        aff_code(n->fd);
    }
}//ok ok


void del_noeud(nnoeud*  n){
    free((*n));
    (*n) = NULL;
}//ok ok


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
}//ok ok


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
}//ok ok


int size_tree (nnoeud n){
    if(n != NULL){
        return 1 + size_tree(n->fg) + size_tree(n->fd);
    }
    else return 0;
}//ok ok


int size_liste (mmaillon m){
    int taille = 0;
    while (m != NULL){
        taille++;
        m = m->suivant;
    }
    return taille;
}//ok ok


int indice(){
    mon_indice ++;
    return mon_indice;
}//ok ok


nnoeud fusion_par_2(nnoeud x, nnoeud y){ //x plus petit que y
    int valeur = x->val + y->val;
    nnoeud z = creer_noeud(valeur, 127, indice());
    z->fg = x;
    z->fd = y;
    return z;
}//ok ok


mmaillon lecture(){
    FILE* fichier = NULL;
    mmaillon m = NULL;
    fichier = fopen("test.txt", "r");
    int b = 1;
    int caractereActuel = 0;
    if (fichier != NULL){
        while(caractereActuel != EOF){
            caractereActuel = fgetc(fichier);

            b = 1;
            mmaillon x = m;
            while(x != NULL  && b == 1){
                if(x->n->lettre == caractereActuel){
                    x->n->val ++;
                    b = 0;
                }
                x = x->suivant;
            }

            if(x == NULL){
                m = ajouter_queue(creer_maillon(creer_noeud(1, caractereActuel, indice())), m);
            }
        }
    //     puts("\n");
        fclose(fichier);
    }else{
        printf("Impossible d'ouvrir le fichier\n");
    }
    m = sup_queue(m);
    return m;
}//ok ok


nnoeud fusion(mmaillon m){

    if(m->suivant != NULL){
        nnoeud x = creer_noeud_complet(m->n->val, m->n->lettre, m->n->id, m->n->fg, m->n->fd);
        nnoeud y = creer_noeud_complet(m->suivant->n->val, m->suivant->n->lettre, m->suivant->n->id, m->suivant->n->fg, m->suivant->n->fd);
        mmaillon tmp = m;
        tmp = tmp->suivant->suivant;
        if(x->val > y->val || (x->val == y->val && x->lettre > y->lettre)){
            free(x);
            x = NULL;
            x = creer_noeud_complet(m->suivant->n->val, m->suivant->n->lettre, m->suivant->n->id, m->suivant->n->fg, m->suivant->n->fd);
            free(y);
            y = NULL;
            y = creer_noeud_complet(m->n->val, m->n->lettre, m->n->id, m->n->fg, m->n->fd);
        }
        while(tmp != NULL){
            if(tmp->n->val < x->val || (tmp->n->val == x->val && tmp->n->lettre < x->lettre)){
                free(y);
                y = NULL;
                y = creer_noeud_complet(x->val, x->lettre, x->id, x->fg, x->fd);
                free(x);
                x = NULL;
                x = creer_noeud_complet(tmp->n->val, tmp->n->lettre, tmp->n->id, tmp->n->fg, tmp->n->fd);
            }else if(tmp->n->val < y->val || (tmp->n->val == y->val && tmp->n->lettre < y->lettre)){
                free(y);
                y = NULL;
                y = creer_noeud_complet(tmp->n->val, tmp->n->lettre, tmp->n->id, tmp->n->fg, tmp->n-> fd);
            }
            tmp = tmp->suivant;
        }
        nnoeud z = fusion_par_2(x, y);
        mmaillon mz = creer_maillon(z);
        m = ajouter_tete(mz, m);
        tmp = m;
        m = supp_maillon(x, m);
        m = supp_maillon(y, m);

        return fusion(m);
    }
    return m->n;
}//ok ok


int contains (char* chaine1, char* acomparer){
    char* str1 = malloc(sizeof(char)*strlen(chaine1));
    strcpy(str1, chaine1);
    char* str2 = malloc(sizeof(char)*1);
    strncpy(str2, acomparer, 1);
    char* ret = malloc(sizeof(char) * 12);
    ret = strpbrk(str1, str2);
    if(ret) {
       return(1);
    } else {
       return(-1);
    }
}//ok ok


int nb_char_in_file(){
    FILE* fichier = NULL;
    int caractereActuel = 0;
    int nb = 0;
    fichier = fopen("test.txt", "r");
    if (fichier != NULL){
        // Boucle de lecture des caractères un à un
        do{
            caractereActuel = fgetc(fichier); // On lit le caractère
            nb++; // On l'affiche
        } while (caractereActuel != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
        fclose(fichier);
    }
    return nb;
}//ok ok


int nb_char_diff(int taille){
    FILE* fichier = NULL;
    char* presents = malloc(sizeof(char) * taille);
    int diff = 0;
    char caractereActuel = '0';
    fichier = fopen("test.txt", "r");
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
}//ok ok


mmaillon ajouter_tete (mmaillon ajout, mmaillon liste){
    ajout->suivant = liste;
    return ajout;
}//ok ok


mmaillon ajouter_queue (mmaillon ajout, mmaillon liste){
    if (liste == NULL){
        return ajout;
    }else{
        mmaillon tmp = liste;
        while(tmp -> suivant != NULL){
            tmp = tmp->suivant;
        }
        tmp->suivant = ajout;
        return liste;
    }
}//ok ok


mmaillon sup_tete (mmaillon liste){
    return (liste->suivant);
}//ok ok


mmaillon sup_queue (mmaillon liste){
    mmaillon tmp = liste;
    while(tmp -> suivant->suivant != NULL){
        tmp = tmp->suivant;
    }
    tmp->suivant = NULL;
    return liste;
}//ok ok


// //ne fonctionne pas encore
// // mmaillon supp_1_occ (mmaillon liste){
// //     mmaillon tmp = liste;
// //     while (tmp -> suivant -> suivant != NULL){
// //         if (tmp->n->lettre == tmp->suivant->n->lettre){
// //             tmp->suivant = tmp->suivant->suivant;
// //         }
// //         tmp = tmp->suivant;
// //     }
// //     return liste;
// // }


mmaillon recherche_maillon (int indice, mmaillon m){
    if (indice == 0){
        return m;
    }else{
        mmaillon tmp = m;
        int i = 0;
        while(tmp -> suivant != NULL && i < indice){
            tmp = tmp->suivant;
            i++;
        }
        return tmp;
    }
}//ok ok


mmaillon supp_maillon (nnoeud sup, mmaillon liste){
    mmaillon tmp = liste;
    
    if(tmp->n->id == sup->id){
        tmp = tmp->suivant;
        free(liste);
        liste = NULL;
     }else{

        while(tmp->suivant->suivant != NULL){
            if(tmp->suivant->n->id == sup->id){
                mmaillon tmp2 = tmp->suivant;
                tmp->suivant = tmp->suivant->suivant;
            
              free(tmp2);
              tmp2 = NULL;
              return liste;
            }
            tmp = tmp->suivant;
        }
        if(tmp->suivant->n->id == sup->id){
            free(tmp->suivant);
            tmp->suivant = NULL;
        }
    }
    return liste;
}//ok ok



void affectation_code (nnoeud n, const char * prefix, char* car){
    if (n == NULL){
        puts("arbre vide");
        return;
    }else{
        n->code=malloc(strlen(prefix)+2);
        strcpy(n->code,prefix);
        strcat(n->code,car);
    }
    if (n->fg != NULL){
        affectation_code(n->fg, n->code, "0");
    }
    if (n->fd != NULL){
        affectation_code(n->fd, n->code, "1");
    }
}//ok ok, je dirais meme merci tete carré, t'es le plus beau 


void mets_les_arguments_dans_fichier (int argc, char *argv[]){
    FILE* fichier = NULL;

    fichier = fopen("test.txt", "w");

    int taille = 0;
    for (int i = 0; i < argc; i++){
        taille += strlen(argv[i]);
    } 
    char* arguments = malloc(sizeof(char)*taille);
    for (int i = 1; i < argc; i++){
        strcat(arguments, argv[i]);
        strcat(arguments, " ");
    }
    fprintf(fichier, "%s\n", arguments);
    fclose(fichier);
}


void copie_fichier_en_argument_dans_testtxt (char* nom_fichier){
    FILE *fc;
    fc=fopen("test.txt","w");;    
    fclose(fc);


    FILE* fSrc;    
    FILE* fDest;
    char* line = malloc(sizeof(char)*90);
 
    if ((fSrc = fopen(nom_fichier, "r+")) == NULL)
    {
        printf("erreur avec le fichier : %s\n", nom_fichier);
    }
 
    if ((fDest = fopen("test.txt", "r+")) == NULL)
    {
        fclose(fSrc);
        puts("erreur avec le fichier : test.txt");
    }
 
      while(fgets(line, 90, fSrc) != NULL)
        fprintf(fDest, "%s", line);
 
    fclose(fDest);
    fclose(fSrc);
}



int main(int argc, char *argv[]) {
    // printf("voulez vous utiliser :\n1 : texte en argument\n2 : nom d'un fichier passé en argument\nautre : test.txt\n");
    // int choix = 0;
    // scanf("%d", &choix);
    // if (choix == 1){
    //     mets_les_arguments_dans_fichier(argc, argv);
    // }
    // if (choix == 2){
    //     char* nom = argv[1];
    //     copie_fichier_en_argument_dans_testtxt (nom);
    // }

    nnoeud n = creer_noeud(3, 'e', 0);
    n->fd = creer_noeud(2, 'a', 1);
    n->fg = creer_noeud(4, 'z', 2);
    n->fg->fd = creer_noeud(7, 'y', 3);
    n->fg->fg = creer_noeud(5, 'n', 4);

    aff_tree(n);

    affectation_code(n, " ", "0");

    puts("\n");
    aff_code(n);
    puts("\n");
    return 0;
}
//pour distinguer l'espace du del, ascii respectifs en decimal 027 et 127
