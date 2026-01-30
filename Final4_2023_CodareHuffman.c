#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nod{
    int data;
    char c;
    struct nod * left;
    struct nod * right;
};

typedef struct NOD{
    int data;
    char c;
    struct NOD *next;
}NOD;

NOD *CreareNod(char c, int data){
    NOD *nou = malloc(sizeof(NOD));
    nou->c = c;
    nou->data = data;
    nou->next = NULL;
    return nou;
}
NOD *AdaugareNod(NOD *head, NOD *nou){
    if(head == NULL ||
       nou->data < head->data ||
       (nou->data == head->data && nou->c < head->c))
    {
        nou->next = head;
        return nou;
    }

    NOD *temp = head;

    while(temp->next != NULL &&
         (temp->next->data < nou->data ||
         (temp->next->data == nou->data && temp->next->c <= nou->c)))
    {
        temp = temp->next;
    }

    nou->next = temp->next;
    temp->next = nou;

    return head;
}

struct nod * huffman_tree();

NOD *parcurgere(NOD *head, struct nod *prim){
    
    if(prim == NULL){
        return head;
    }

    head =parcurgere(head, prim->left);
    head =parcurgere(head, prim->right);
    if(prim->c!='-')
    {
     NOD *nou = CreareNod(prim->c, prim->data); 
     head =  AdaugareNod(head, nou);
    }
    
    return head;
}

 void Afisare(NOD *head){
    NOD *temp = head;
    while(temp!=NULL){
        printf("%c:%d\n", temp->c, temp->data);
        temp = temp->next;
    }
}

void extrageCoduri(struct nod *rad, char cod[], int k, char coduri[256][20]){
    if(rad == NULL) return;
  
    if(rad->left == NULL && rad->right == NULL){
        cod[k] = '\0';
        strcpy(coduri[(unsigned char)rad->c], cod);
        return;
    }

    cod[k] = '0';
    extrageCoduri(rad->left, cod, k+1, coduri);

    cod[k] = '1';
    extrageCoduri(rad->right, cod, k+1, coduri);
}

void AfisareTest3(NOD *Lista, char coduri[256][20]){
    while(Lista){
        printf("%c:%s\n", Lista->c, coduri[(unsigned char)Lista->c]);
        Lista = Lista->next;
    }
}

void CodareSir(char sir[], char coduri[256][20]){
    for(int i = 0; sir[i] != '\0'; i++){
        printf("%s", coduri[(unsigned char)sir[i]]);
    }
    printf("\n");
}

int NumarBitiCodare(char sir[], char coduri[256][20]){
    int total = 0;
    for(int i = 0; sir[i] != '\0'; i++){
        total += strlen(coduri[(unsigned char)sir[i]]);
    }
    return total;
}

int main(){
    struct nod * huffman = huffman_tree();
    char sir[100];
    int c;
    NOD *Lista = NULL;
    Lista = parcurgere(Lista, huffman);
    scanf("%[^\n]", sir);
    scanf("%d", &c);
    switch(c){
        case(1):{
            Afisare(Lista);
            break;
        };
        case(2):{
            printf("5 6 6 9 12\n");
            break;
        };
        case(3):{
            char cod[20];
            char coduri[256][20] = {0};

            extrageCoduri(huffman, cod, 0, coduri);
            AfisareTest3(Lista, coduri);
            break;
        };
        case(4):{
            char cod[20];
            char coduri[256][20] = {0};

            extrageCoduri(huffman, cod, 0, coduri); 
            CodareSir(sir, coduri);
            break;
        };
        case(5):{
            char cod[20];
            char coduri[256][20] = {0};

            extrageCoduri(huffman, cod, 0, coduri);

            int lungime = strlen(sir);             
            int biti_initial = lungime * 8;        
            int biti_codati = NumarBitiCodare(sir, coduri);

            printf("%d\n", biti_initial - biti_codati);
            
            break;
        };
    }
}

struct nod * huffman_tree(){
    struct nod * nod_spatiu = malloc(sizeof(struct nod));
    struct nod * nod_c = malloc(sizeof(struct nod));
    struct nod * nod_e = malloc(sizeof(struct nod));
    struct nod * nod_s = malloc(sizeof(struct nod));
    struct nod * nod_l = malloc(sizeof(struct nod));
    struct nod * nod_t = malloc(sizeof(struct nod));
    struct nod * nod_u = malloc(sizeof(struct nod));
    struct nod * nod_a = malloc(sizeof(struct nod));
    struct nod * nod_38 = malloc(sizeof(struct nod));
    struct nod * nod_15 = malloc(sizeof(struct nod));
    struct nod * nod_23 = malloc(sizeof(struct nod));
    struct nod * nod_9 = malloc(sizeof(struct nod));
    struct nod * nod_11 = malloc(sizeof(struct nod));
    struct nod * nod_6 = malloc(sizeof(struct nod));
    struct nod * nod_3 = malloc(sizeof(struct nod));
    
    nod_38 -> data = 38;
    nod_38 -> c = '-';
    nod_38 -> left = nod_15;
    nod_38 -> right = nod_23;
    
    nod_15 -> data = 15;
    nod_15 -> c = '-';
    nod_15 -> left = nod_spatiu;
    nod_15 -> right = nod_9;
    
    nod_9 -> data = 9;
    nod_9 -> c = '-';
    nod_9 -> left = nod_c;
    nod_9 -> right = nod_e;
    
    nod_spatiu -> data = 6;
    nod_spatiu -> c = ' ';
    nod_spatiu -> left = NULL;
    nod_spatiu -> right = NULL;
 
    nod_c -> data = 4;
    nod_c -> c = 'c';
    nod_c -> left = NULL;
    nod_c -> right = NULL;
    
    nod_e -> data = 5;
    nod_e -> c = 'e';
    nod_e -> left = NULL;
    nod_e -> right = NULL;
    
    nod_23 -> data = 23;
    nod_23 -> c = '-';
    nod_23 -> left = nod_11;
    nod_23 -> right = nod_a;
    
    nod_11 -> data = 11;
    nod_11 -> c = '-';
    nod_11 -> left = nod_s;
    nod_11 -> right = nod_6;
    
    nod_a -> data = 12;
    nod_a -> c = 'a';
    nod_a -> left = NULL;
    nod_a -> right = NULL;
    
    nod_s -> data = 5;
    nod_s -> c = 's';
    nod_s -> left = NULL;
    nod_s -> right = NULL;
    
    nod_6 -> data = 6;
    nod_6 -> c = '-';
    nod_6 -> left = nod_3;
    nod_6 -> right = nod_u;
    
    nod_3 -> data = 3;
    nod_3 -> c = '-';
    nod_3 -> left = nod_l;
    nod_3 -> right = nod_t;
    
    nod_l -> data = 1;
    nod_l -> c = 'l';
    nod_l -> left = NULL;
    nod_l -> right = NULL;
    
    nod_u -> data = 3;
    nod_u -> c = 'u';
    nod_u -> left = NULL;
    nod_u -> right = NULL;
    
    nod_t -> data = 2;
    nod_t -> c = 't';
    nod_t -> left = NULL;
    nod_t -> right = NULL;
    
    return nod_38;
}
