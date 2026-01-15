#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//----------------------Prima parte, am facut o lista simplu inlantuita--------------------
    typedef struct Nod{
        char nume[21];
        char CNP[14];
        struct Nod *next;
    }Nod;
    Nod *CreareNod(char *nume, char *CNP){
        Nod *nou = malloc(sizeof(Nod));
        strcpy(nou->nume,nume);
        strcpy(nou->CNP, CNP);
        nou->next=NULL;
        return nou;
    };
     Nod *AdugareNod(Nod *head, Nod *nou){
         nou->next = head;
         return nou;
     }
        Nod *AdugareNodFinal(Nod *head, Nod *nou){
        Nod *temp = head;
        if(head == NULL){
            return nou;
        }
        while(temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=nou;
        return head;
        }
    void Afisare(Nod *head){
        Nod *temp = head;
        while(temp!=NULL){
            printf("%s %s\n", temp->nume, temp->CNP);
            temp = temp->next;
        }
    }
 
// //---------------Acum o sa creez hashtable-ul-----------------------------------------
    
    typedef struct Hashtable{
        Nod **buckets;
        int size;
    } Hashtable;
    
    int hash(char *CNP, int key, int size){
        int h=0;
        int cod = 0;
        for(int i = 7; i < 13; i++){
            cod = cod * 10 + (CNP[i]-'0');
        }
        h = cod * key;
        return h % size;
    }
    void insert(Hashtable *ht, Nod *nou, int key){
        int index = hash(nou->CNP, key, ht->size);
        
        Nod *copie = CreareNod(nou->nume, nou->CNP);
        
        ht->buckets[index] = AdugareNod(ht->buckets[index], copie);
    }
    void insertTest3(Hashtable *ht, char *CNP, char *nume, int size, int key){
        int index = hash(CNP, key, size);
        
        Nod *copie = CreareNod(nume, CNP);
        
        ht->buckets[index] = AdugareNod(ht->buckets[index], copie);
    }
      char* getNume(Hashtable *ht, int poz){
          Nod *temp = ht->buckets[poz];
          return temp->nume;
      }
      char* getCNP(Hashtable *ht, int poz){
          Nod *temp = ht->buckets[poz];
          return temp->CNP;
      }
      Nod *stergeNod(Nod *head){
          Nod *nodSters;
          if(head==NULL)
              return NULL;
          
              nodSters=head;
              head=head->next;
              free(nodSters);
              return head;
          
      }
       void AfisareHashTable(Hashtable *ht){
        for(int i = 0; i < ht->size; i++){
            Nod *temp =ht->buckets[i];
            printf("%d: ", i);
            while(temp!=NULL){
                printf("%s ",temp->nume);
                temp = temp->next;
            }
            printf("\n");
            
        }
    }

  
        
        
        
    
    int main(){
        int cap;
        int nr_persoane;
        char nume[21];
        char CNP[14];
        int key;
        int c;
        
//-----facem lista simplu inlantuita si adaugam informatia-----------------
        Nod *lista = NULL;
        
        scanf("%d %d", &cap, &nr_persoane);
        
        for(int i = 0; i < nr_persoane; i++){
            scanf("%s %s", nume, CNP);
            Nod *nou=CreareNod(nume, CNP);
            lista = AdugareNodFinal(lista, nou);
            
        }
        scanf("%d %d", &key, &c);
       
//-------hashtable intializare -------------------
        Hashtable ht;
        ht.size = cap;
        ht.buckets = calloc(ht.size, sizeof(Nod*));
        
        switch(c){
            case 1:{
                Afisare(lista);
                break;
            };
            case 2:{
                Nod *temp = lista;
                while(temp!=NULL){
                    insert(&ht, temp, key);
                    temp=temp->next;
                }
                AfisareHashTable(&ht);
                break;
            };
            case 3:{
                Hashtable ht2;
                ht2.size= cap;
                ht2.buckets = calloc(ht2.size, sizeof(Nod*));
                 Nod *temp = lista;
                while(temp!=NULL){
                    insert(&ht, temp, key);
                    temp=temp->next;
                }
                int numere;
                char nume[21] ;
                char CNP[14];
                while(scanf("%d", &numere)!=EOF){
                    strcpy(nume,getNume(&ht, numere));
                    strcpy(CNP,getCNP(&ht, numere));
                    insertTest3(&ht2, CNP, nume, cap, key);
                    ht.buckets[numere] = stergeNod(ht.buckets[numere]);
                }
                AfisareHashTable(&ht);
                AfisareHashTable(&ht2);
                break;
            }
        }
        
        
        return 0;
    }