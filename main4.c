#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nod{
    char numari[8];
    char CNP[14];
    float suma;
    float rating;
    struct Nod* next;
}Nod;
struct hashtable{
    Nod **buckets;
    int size;
};

Nod *CreareNod(char *numari, char *CNP, float suma, float rating){
    Nod *nou = malloc(sizeof(Nod));
    strcpy(nou->numari, numari);
    strcpy(nou->CNP, CNP);
    nou->suma = suma;
    nou->rating = rating;
    nou->next = NULL;
    return nou;
};

Nod *AdugareNod(Nod *head, Nod *nou){
    if(head == NULL ){
        return nou;
    }
    Nod * temp = head;
    char aux[3];
    strncpy(aux, nou->CNP+1, 2);
    aux[2]='\0';
    int an = atoi(aux);
    if(an >= 50){
        an += 1900;
    }else{
        an += 2000;
    }
    
    strncpy(aux, temp->CNP+1, 2);
    aux[2]='\0';
    int an2 = atoi(aux);
     if(an2 >= 50){
        an2 += 1900;
    }else{
        an2 += 2000;
    }
    
    
    if(an<an2){
        nou->next = head;
        return nou;
    }
    
    while(temp->next!=NULL){
        
        strncpy(aux, temp->next->CNP+1, 2);
        aux[2]='\0';
        int an2 = atoi(aux);
         if(an2 >= 50){
        an2 += 1900;
    }else{
        an2 += 2000;
    }
    
        if(an<an2){
            break;
        }
        
        
        temp = temp->next;
    }
    nou->next = temp->next;
    temp->next = nou;
    return head;
};

Nod *AdugareNodtest4(Nod *head, Nod* nou){
    if(head == NULL ){
        return nou;
    }
    Nod * temp = head;
    if(nou->rating<=head->rating){
        nou->next = head;
        return nou;
    }
    while(temp->next != NULL){
        if(nou->rating<=temp->next->rating){
            break;
        }
        
        temp = temp->next;
    }
    nou->next = temp->next;
    temp->next = nou;
    return head;
}

int hash(char *numar, int size){
    int h = 0;
    if(numar[1]<'A'){
        h += numar[0];
        return h % size;
    }
    h = numar[0] + numar [1];
    return h % size;
}
void inserare(struct hashtable *ht, Nod* nou){
    int h = hash(nou->numari, ht->size);
    ht->buckets[h] = AdugareNod(ht->buckets[h], nou);
}
void afisare(struct hashtable *ht, int size){
    for(int i = 0;i<size;i++){
        Nod *temp = ht->buckets[i];
        while(temp!=NULL){
            printf("%s",temp->numari);
            printf("\n");
            temp = temp->next;
            
        }
        
    }
}
void afisaretest2(struct hashtable *ht, int size, char *cod){
        int i = hash(cod, size);
        Nod *temp = ht->buckets[i];
        int k = 1;
        while(temp!=NULL){
            char aux[3];
            strncpy(aux,temp->numari, 2);
            k++;
            if(strcmp(aux,cod)==0){
            k--;
            printf("%s %s %.2f %.2f\n",temp->numari, temp->CNP, temp->suma, temp->rating);}
            temp = temp->next;
        }
        printf("%d\n", k);
}
void afisaretest3(struct hashtable *ht, int size, char *cod1, char *cod2){
        int i1 = hash(cod1, size);
        int i2 = hash(cod2, size);
        Nod *temp = ht->buckets[i1];
        int k = 0;
        float sumat = 0;
        float ratingt = 0;
        while(temp!=NULL){
            char aux[3];
            if(temp->numari[1]<'A'){
            strncpy(aux,temp->numari, 1);
            aux[1]='\0';
            }else{
            strncpy(aux,temp->numari, 2);   
            aux[2]='\0';}
            if(strcmp(aux,cod1)==0){
            sumat += temp->suma;
            ratingt += temp->rating;
            k++;
            }
            temp = temp->next;
        }
        printf("%s %d %.2f %.2f %.2f\n",cod1, k, sumat, sumat/k, ratingt/k);
        temp = ht->buckets[i2];
         k = 0;
         sumat = 0;
         ratingt = 0;
        while(temp!=NULL){
            char aux[3];
             if(temp->numari[1]<'A'){
            strncpy(aux,temp->numari, 1);
            aux[1]='\0';
            }else{
            strncpy(aux,temp->numari, 2);   
            aux[2]='\0';}
            if(strcmp(aux,cod2)==0){
            sumat += temp->suma;
            ratingt += temp->rating;
            k++;
            }
            temp = temp->next;
        }
        printf("%s %d %.2f %.2f %.2f\n",cod2, k, sumat, sumat/k, ratingt/k);
}
    
    void afisaretest4(struct hashtable *ht, float rating){
        Nod *ListaSortata = NULL;
        for(int i = 0 ;i<ht->size;i++){
            Nod *temp = ht->buckets[i];
                while(temp!=NULL){
                    if(temp->rating<rating){
                        Nod *nou = CreareNod(temp->numari, temp->CNP, temp->suma, temp->rating);
                        ListaSortata = AdugareNodtest4(ListaSortata, nou);
                    }
                    temp = temp->next;
                }
            
        }
        Nod *temp = ListaSortata;
        while(temp!=NULL){
            printf("%s %.2f\n", temp->numari, temp->rating);
            temp = temp->next;
        }
    }





int main(){
    char numari[8];
    char CNP[14];
    float suma;
    float rating;
    int nr;
    int cap;
    scanf("%d", &nr);
    scanf("%d", &cap);
    struct hashtable ht;
    ht.size = cap;
    ht.buckets = calloc(ht.size, sizeof(Nod*));
    for(int i = 0;i< nr;i++){
        scanf("%s", numari);
        scanf("%s", CNP);
        scanf("%f", &suma);
        scanf("%f", &rating);
        Nod *nou = CreareNod(numari, CNP, suma, rating);
        inserare(&ht, nou);
    }
    int c;
    scanf("%d", &c);
    switch(c){
        case(1):{
            afisare(&ht, ht.size);
            break;
        };
        case(2):{
            char cod[3];
            scanf("%s", cod);
            afisaretest2(&ht, ht.size, cod);
              
            break;
        };
        case(3):{
            char cod1[3];
            char cod2[3];
            scanf("%s %s", cod1, cod2);
            afisaretest3(&ht, ht.size, cod1, cod2);
            break;
        };
        case(4):{
          float ratingmin;
          scanf("%f", &ratingmin);
          afisaretest4(&ht, ratingmin);
          
          break;  
        };
    };
    
    
    
}