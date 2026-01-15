#include <stdio.h>
#include <stdlib.h>
#include <string.h>
    typedef struct Nod{
        char nume[31];
        char parola[31];
        int comp;
        struct Nod *next;
    }Nod;
    struct hashmap{
        Nod **buckets;  
    };
    int hash(char *parola){
        int a = 0;
        for(int i = 0;i<strlen(parola);i++){
            a += parola[i];
        }
        return a%7;
    }
    Nod *CreareNod(char *nume, char *parola){
        Nod *nodnou = malloc(sizeof(Nod));
        strcpy(nodnou->nume, nume);
        strcpy(nodnou->parola, parola);
        nodnou->next = NULL;
        return nodnou;
    };
     Nod *CreareNod2(char *nume, char *parola, int comp){
        Nod *nodnou = malloc(sizeof(Nod));
        strcpy(nodnou->nume, nume);
        strcpy(nodnou->parola, parola);
        nodnou->comp = comp;
        nodnou->next = NULL;
        return nodnou;
    };
    Nod *Adugare(Nod *head, Nod *nou){
        if(head == NULL){
            return nou;
        }
        if(nou->comp < head->comp){
            nou->next = head;
            return nou;
            
        }
        
        Nod *temp = head;
        while(temp->next!=NULL){
            if(nou->comp<temp->next->comp){
                
                break;
            }
            temp = temp->next;
        }
        
        nou->next = temp->next;
        temp->next = nou;
        
        return head;
    };
       Nod *AdugareFinal(Nod *head, Nod *nou){
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
            printf("%s %s\n", temp->nume, temp->parola);
            temp=temp->next;
        }
    }
    
    void afisaretest2(Nod *head){
        Nod *temp = head;
        while(temp!=NULL){
            printf("%s %s %d\n", temp->nume, temp->parola, temp->comp);
            temp=temp->next;
        }
    }
    Nod *complexitate(Nod *head){
        Nod *temp = head;
        while(temp!=NULL){
            int complex = 0;
            char par[31];
            strcpy(par, temp->parola);
            complex += strlen(par);
            for(int i = 0;i<strlen(par);i++){
                if(par[i]>='A'&&par[i]<='Z'){
                    complex += 1;
                }
                else if(!(par[i]>='a'&&par[i]<='z')){
                    complex += 2;
                }
                
            }
            temp->comp = complex;
            temp = temp->next;
        }
        return head;
    };
    void CreareMap(struct hashmap *ht, Nod *head){
        Nod *temp = head;
        while(temp!=NULL){
            int index = hash(temp->parola);
            Nod *nou = CreareNod2(temp->nume, temp->parola, temp->comp);
            
            ht->buckets[index] = Adugare(ht->buckets[index], nou);
            
            temp = temp->next;
        }
    }
    void AfisareMap(struct hashmap *ht){
        for(int i = 0;i<7;i++){
            Nod *temp = ht->buckets[i];
            while(temp!=NULL){
                printf("%s\n", temp->nume);
                temp = temp->next;
            }
        }
    }

    
    
    
int main(){
    char nume_main[31];
    char parola_main[31];
    int comanda;
    Nod *Lista = NULL;
    while(1){
        scanf("%s", nume_main);
        if(strcmp(nume_main,"STOP")==0)
        break;
        
        scanf("%s", parola_main);
     
        Nod *nou = CreareNod(nume_main, parola_main);
        Lista = AdugareFinal(Lista, nou);
    }
    scanf("%d", &comanda);
    switch(comanda){
        case(1):{
            afisare(Lista);
            break;
        };
        case(2):{
         Lista = complexitate(Lista);
         afisaretest2(Lista);
          break;  
        };
        case(3):{
            Nod *ListaAranjata = NULL;
            Lista = complexitate(Lista);
            Nod *temp = Lista;
            while(temp!=NULL){
            Nod *nou = CreareNod2(temp->nume, temp->parola, temp->comp); 
            ListaAranjata = Adugare(ListaAranjata, nou);
            temp = temp->next;
            }
            afisaretest2(ListaAranjata);
          break;  
          
        };
        case(4):{
            struct hashmap ht;
            ht.buckets = calloc(7, sizeof(Nod*));
            Lista = complexitate(Lista);
            CreareMap(&ht, Lista);
            AfisareMap(&ht);
            break;
        };
    }
    
    return 0;
}