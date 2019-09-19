#include "main.h"
int mon_indice = 0;

//creation d'un maillon contenant le noeud en parametre
mmaillon creer_maillon (nnoeud n){
    mmaillon m = malloc(sizeof(struct maillon));
    m->n = n;
    m->suivant = NULL;
    return m;
}


//creation d'un noeud avec les valeurs des champs val, lettre et id en parametre
//code, fg et fd initialisés à NULL
nnoeud creer_noeud (int val, char lettre, int id){
    nnoeud n = malloc(sizeof(struct noeud));
    n->val = val;
    n->lettre = lettre;
    n->id = id;
    n->code = NULL;
    n->fd = NULL;
    n->fg = NULL;
    return n;
}


//creation d'un noeud comme creer_noeud, avec en plus les fils gauche et
//droit renseignés en parametres
nnoeud creer_noeud_complet (int val, char lettre, int id, nnoeud fg, nnoeud fd){
    nnoeud n = malloc(sizeof(struct noeud));
    n->val = val;
    n->lettre = lettre;
    n->id = id;
    n->code = NULL;
    n->fd = fd;
    n->fg = fg;
    return n;
}


//permet d'afficher la valeur, le caractere, l'id et le code du noeud en parametre
void aff_noeud (nnoeud n){
    printf("(%d|%c|%d|%s) ", n->val, n->lettre, n->id, n->code);
}


//affiche le noeud contenu dans le maillon en parametre
void aff_maillon (mmaillon m){
    if (m == NULL){
        puts("le maillon est vide");
    }else{
        aff_noeud(m->n);
    }
}


//affiche tout les noeuds contenu dans les maillons de la liste en parametre
void aff_liste (mmaillon m){
    if (m == NULL){
        aff_maillon(m);
    }
    while(m != NULL){
        aff_maillon (m);
        m = m->suivant;
    }
    puts("\n");
}


//affiche tout les noeuds d'un arbre
void aff_tree (nnoeud n){
    if (n != NULL){
        printf("(%d|%c|%d|%s) ", n->val, n->lettre, n->id, n->code);
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


//affiche le code de chacun des noeuds d'un arbre en parametre
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
}


//supprime le noeud en parametre
void del_noeud(nnoeud*  n){
    free((*n));
    (*n) = NULL;
}


//supprime tout les noeuds de l'arbre en parametre
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


//retourne 1 si la valeur en parametre existe dans l'arbre en parametre, sinon 0
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


//retourne le nombre de noeuds de l'arbre en parametre
int size_tree (nnoeud n){
    if(n != NULL){
        return 1 + size_tree(n->fg) + size_tree(n->fd);
    }
    else return 0;
}


//retourne la taille de la liste en parametre
int size_liste (mmaillon m){
    int taille = 0;
    while (m != NULL){
        taille++;
        m = m->suivant;
    }
    return taille;
}


//incremente la variable globale mon_indice et en retourne la valeur
int indice(){
    mon_indice ++;
    return mon_indice;
}


//fusionne deux noeud. Celui dont la valeur est la plus petite deviens fg, l'autre fd
//le noeud retourné a pour valeur la somme des valeurs des noeuds fusionnés
nnoeud fusion_par_2(nnoeud x, nnoeud y){ //x plus petit que y
    int valeur = x->val + y->val;
    nnoeud z = creer_noeud(valeur, 127, indice());
    z->fg = x;
    z->fd = y;
    return z;
}


//lis le fichier test.txt, retourne la liste des caracteres et de leur occurence
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
}


//utilise fusion_par_2 pour retorner un arbre, resultat de la fusion des noeuds de la liste en parametre
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
}

 
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
}


//retourne le nombre de caracteres dans un fichier
int nb_char_in_file(){
    FILE* fichier = NULL;
    int caractereActuel = 0;
    int nb = 0;
    fichier = fopen("compresse.txt", "r");
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


//ajoute le maillon ajout en tet de la liste liste
mmaillon ajouter_tete (mmaillon ajout, mmaillon liste){
    ajout->suivant = liste;
    return ajout;
}


//ajourte le maillon ajout en queue de la liste liste
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
}


//retourne la liste en parametre sans son maillon de tete
mmaillon sup_tete (mmaillon liste){
    return (liste->suivant);
}


//supprime le dernier maillon de la liste liste
mmaillon sup_queue (mmaillon liste){
    mmaillon tmp = liste;
    while(tmp -> suivant->suivant != NULL){
        tmp = tmp->suivant;
    }
    tmp->suivant = NULL;
    return liste;
}


//retourne le maillon dont l'id est indice dans la liste m
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
}


//supprime les doublons de la liste liste
mmaillon supp_1_occ(mmaillon liste){
    int val1 = 0;
    int val2 = 0;
    mmaillon tmp1 = liste;
    mmaillon tmp2 = liste->suivant;
    mmaillon tmp3 = NULL;

    while(tmp1->suivant != NULL){
        while(tmp2 != NULL){
            if(tmp1->n->lettre == tmp2->n->lettre){
                tmp3 = tmp1;
                val1 = tmp1->n->val;
                val2 = tmp2->n->val;
                supp_maillon(tmp3->n, liste);
                if(val1 > val2){
                    tmp2->n->val = val1;
                }
            }
            tmp2 = tmp2->suivant;
        }
        tmp1 = tmp1->suivant;
        tmp2 = tmp1->suivant;
    }
    return liste;
}

//supprime le maillon sup de la liste liste
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
}


//affecte a chaque noeud d'un arbre son code prefixe
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
}


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

//recupere le code associe au caractere x
void recup_code (nnoeud n, char x, FILE* fichier){
    if (n == NULL){
        puts("erreur1");
    }
    if (n->lettre == x){
        fprintf(fichier, "%s ", n->code);
    }
    if (n->fg != NULL){
        recup_code(n->fg, x, fichier);
    }
    if (n->fd != NULL){
        recup_code(n->fd, x, fichier);
    }
}

//ecrit l'index dans le fichier compresse.txt
void aff_table_in_compression (FILE* fichier, nnoeud n){
    if (n != NULL){
        if (n->lettre != 127){
            fprintf(fichier, "%d|%c ", n->val, n->lettre);
        }
    }else{
        puts("Arbre vide !!");
        return;
    } 
    if (n->fg != NULL){
        aff_table_in_compression(fichier, n->fg);
    }
    if (n->fd != NULL){
        aff_table_in_compression(fichier, n->fd);
    }
}

//compresse le fichier avec les données de l'arbre n
void compression (nnoeud n){
    FILE* fichier = NULL;
    FILE* fichier2 = NULL;
    FILE* fichier3 = NULL;
    fichier = fopen("compresse.txt", "w");
    fichier2 = fopen("test.txt", "r");
    fichier3 = fopen("compresse2.txt", "w");
    int caractereActuel = 0;
    fprintf(fichier, "#table\n");
    aff_table_in_compression(fichier, n);
    fprintf(fichier, "\n\n#code\n");
    if (fichier2 != NULL){
        while (caractereActuel != EOF){
            caractereActuel = fgetc(fichier2);
            recup_code(n, caractereActuel, fichier);
            recup_code(n, caractereActuel, fichier3);
        }
    }
    fclose(fichier);
    fclose(fichier2);
    fclose(fichier3);
}

//retourne le caractere c sous forme de chaine de caractere
char* char2string(char c){
   char *str=malloc(2*sizeof(char));
   if(str==NULL){
    return NULL;
   }
   str[0]=c;
   str[1]='\0';
   return str;
}


char* compressed_file_to_string (){
    FILE* fichier = NULL;
    char* contenu = malloc(sizeof(char)*nb_char_in_file());
    fichier = fopen("compresse.txt", "r");
    int b = 1;
    int ind = 0;
    int caractereActuel = 0;
    if (fichier != NULL){
        while(caractereActuel != EOF){
            caractereActuel = fgetc(fichier);
            strcat(contenu, char2string(caractereActuel));
        }
    }
    contenu = contenu + 7;
    for (int i = 0; i < strlen(contenu); i++){
        if (contenu[i] == '#'){
            ind = i;
            break;
        }
    }
    char* new_contenu = malloc(sizeof(char)*ind);
    for (int i = 0; i < ind; i++){
        new_contenu[i] = contenu[i];
    }
    return new_contenu;
}

//retourne l'arbre cree a partir de l'index
nnoeud create_arbre_from_compressed_file(char* string){
    int indisse = 0;
    mmaillon liste = creer_maillon(creer_noeud_complet(string[indisse]-48, string[indisse+2], indice(), NULL, NULL));
    while (indisse + 4 < strlen(string)){
        indisse = indisse + 4;
        ajouter_queue(creer_maillon(creer_noeud(string[indisse]-48, string[indisse+2], indice())), liste);
    }
    liste = sup_queue(liste);
    nnoeud neu = fusion(liste);
    affectation_code(neu, " ", "0");
    return(neu);
}

//compare a et b. Retourne 1 si elles sont identiques, 0 sinon
int compare_string (char* a, char* b){
    if (strlen (a) != strlen(b)){
        return 0;
    }else{
        for (int i = 0; i < strlen(a); i++){
            if (a[i] != b[i]){
                return 0;
            }
        }
        return 1;
    }
}

//recupere le caractere associe au code
void recup_lettre (nnoeud n, char* code, FILE* fichier){
    if (n == NULL){
        puts("erreur1");
    }
    if (compare_string(n->code+1,code) == 1){
        fprintf(fichier, "%c", n->lettre);
    }
    if (n->fg != NULL){
        recup_lettre(n->fg, code, fichier);
    }
    if (n->fd != NULL){
        recup_lettre(n->fd, code, fichier);
    }
}

//decompresse le fichier compresse.txt
void decompression (nnoeud n){
    FILE* fichier = NULL;
    FILE* fichier2 = NULL;
    fichier = fopen("decompresse.txt", "w");
    fichier2 = fopen("compresse2.txt", "r");
    char* chaine = malloc(sizeof(char)* size_tree(n));
    while (fscanf(fichier2, "%s", chaine) != EOF){
        recup_lettre(n, chaine, fichier);
    }
    fclose(fichier);
    fclose(fichier2);
}


int main(int argc, char *argv[]) {
    printf("voulez vous utiliser :\n1 : texte en argument\n2 : nom d'un fichier passé en argument\nautre : test.txt\n");
    int choix = 0;
    scanf("%d", &choix);
    if (choix == 1){
        mets_les_arguments_dans_fichier(argc, argv);
    }
    if (choix == 2){
        char* nom = argv[1];
        copie_fichier_en_argument_dans_testtxt (nom);
    }
    //partie qui permet de compresser à partir du texte choisi precedemment
    nnoeud n = fusion(lecture());
    affectation_code(n, " ", "0");
    aff_tree(n);

    compression(n);

    create_arbre_from_compressed_file(compressed_file_to_string());

    //décompression a partir du ficier compresse juste avant
    FILE* fichier = NULL;
    fichier = fopen("decompresse.txt", "w");

    decompression(create_arbre_from_compressed_file(compressed_file_to_string()));
    return 0;
}
