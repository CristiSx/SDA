#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct Nod{
    char nume[21];
    char CNP[14];
    struct Nod *next;
}Nod;
typedef struct Hashmap{
    Nod **buckets;
    int cap;
}Hashmap;


Nod *CreareNod(char *nume, char *CNP){
    Nod *nou = malloc(sizeof(Nod));
    strcpy(nou->nume,nume);
    strcpy(nou->CNP,CNP);
    nou->next = NULL;
    return nou;
};


Nod *AdugareNod(Nod *head, Nod *nou){
    if(head == NULL){
        return nou;
    }  
    Nod *temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = nou;
    
return head;
 
    
};

void afisare(Nod *head){
    Nod *temp = head;
    while(temp!=NULL){
        printf("%s %s\n",temp->nume, temp->CNP);
        temp = temp->next;
    }
};




int hash(char *CNP, int size){
    char six[7];
    char two[3];
    strncpy(six, CNP+7, 6);
    six[6] = '\0';
    strncpy(two, CNP+1, 2);
    two[2] = '\0';
    int a, b;
    a = atoi(six);
    b = atoi(two);
    int h;
    
    h = (a*b)%size;
    return h; 
};


Nod *AdugareSortata(Nod *head, Nod *nou){
    Nod *temp = head;
    if(head == NULL){
        return nou;
    }
    char two1[3];
    strncpy(two1, nou->CNP+1, 2);
    two1[2] = '\0';
    int b = atoi(two1);
    char two2[3];
    strncpy(two2, temp->CNP+1, 2);
    two2[2] = '\0';
    int a;
    a = atoi(two2);
    if(b<a){
        nou->next = head;
        return nou;
    }
    while(temp->next!=NULL){
        strncpy(two2, temp->next->CNP+1, 2);
        two2[2] = '\0';
        int a;
        a = atoi(two2);
        if(b<a){
            break;
        }
        temp = temp->next;
    }
    nou->next = temp->next;
    temp->next = nou;
return head;
};


void inserare(Hashmap *ht, Nod *head){
    Nod *temp = head;
    while(temp!=NULL){
        int h = hash(temp->CNP, ht->cap);
        Nod *Nou = CreareNod(temp->nume,temp->CNP);
        ht->buckets[h] = AdugareSortata(ht->buckets[h], Nou);
        temp = temp->next;
    }
};


void afisareh(Hashmap *ht){
    for(int i = 0;i<ht->cap;i++){
        Nod *temp = ht->buckets[i];
        printf("%d: ", i);
        while(temp!=NULL){
            printf("%s ", temp->nume);
            temp = temp->next;
        }
        printf("\n");
    }
    
}

void test4(Nod *head, float load){
    Hashmap ht2;
    int cap = 1;
    while(1){
        int ocupat = 0;
        ht2.cap = cap;
        ht2.buckets = calloc(ht2.cap, sizeof(Nod*));
        Nod *temp = head;
        while(temp!=NULL){
            int h = hash(temp->CNP, ht2.cap);
            Nod *Nou = CreareNod(temp->nume,temp->CNP);
            ht2.buckets[h] = AdugareSortata(ht2.buckets[h], Nou);
            temp = temp->next;
        }
        for(int i = 0;i<cap;i++){
            Nod *temp2 = ht2.buckets[i];
            if(temp2 != NULL){
                ocupat++;
            }
        }
        float ver;
        ver = (float)ocupat/cap;
        if(ver<load){
            printf("%d", cap);
            break;
        }
        cap++;
    }
};

int main(){
    int cap;
    int numar;
    char nume[21];
    char CNP[14];
    int c;
    Nod *Lista = NULL;
    Hashmap ht;
    
    scanf("%d %d", &cap, &numar);
    
    ht.cap = cap;
    ht.buckets = calloc(ht.cap, sizeof(Nod*));
    for (int i = 0;i<numar;i++){
        scanf("%s %s", nume, CNP);
        Nod *nou = CreareNod(nume, CNP);
        Lista = AdugareNod(Lista, nou);
    }
    scanf("%d", &c);
    switch(c){
        case(1):{
            afisare(Lista);
        break;  
        };
        case(2):{
            Nod *temp = Lista;
            int h;
             
            while(temp!=NULL){
                h = hash(temp->CNP, ht.cap);
                printf("%d\n", h);
                temp = temp->next;
            }
        break;
        };
        case(3):{
            inserare(&ht, Lista);
            afisareh(&ht);
            break;
        };
        case(4):{
        float load;
        scanf("%f", &load);
        test4(Lista, load);
        break;  
        };
        
        
    }
    return 0;
}