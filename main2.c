#include <stdio.h>
#include <stdlib.h>
#include <string.h>
    typedef struct Nod{
        char cuvant[21];
        struct Nod *next;
    }Nod;
    
    Nod *CreareNod(char *cuvant){
        Nod *nou = malloc(sizeof(struct Nod));
        strcpy(nou->cuvant, cuvant);
        nou->next = NULL;
        return nou;
    };
    
    Nod *Adugare(Nod *head, Nod *nou){
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
    
    struct hashmap{
        Nod **buckets;
        int size;
    };
    int hash(char *cuvant, int size){
        int a = 0;
        for(int i = 0; i<strlen(cuvant);i++){
            a += cuvant[i];
        }
        return a % size;
    }
    void afisare(struct hashmap *ht){
        for(int i = 0;i<ht->size;i++){
            Nod *temp = ht->buckets[i];
            while(temp!=NULL){
                int h = hash(temp->cuvant, ht->size);
                printf("%s %d\n", temp->cuvant, h);
                temp = temp->next;
            }
        }
        
    }
    int anag(char *s1, char *s2){
        int c1[256] = {0};
        int c2[256] = {0};
        int i = 0;
        while(s1[i]){
            c1[s1[i++]]++;
        }
        i = 0;
        while(s2[i]){
            c2[s2[i++]]++;
        }
        for(i = 0;i<256;i++){
            if(c1[i]!=c2[i]){
                return 0;
            }
        }
        return 1;
        
        
    }
    void test2(struct hashmap *ht, char *cuv){
        for(int i = 0;i<ht->size;i++){
            Nod *temp = ht->buckets[i];
            while(temp!=NULL){
                int h = hash(temp->cuvant, ht->size);
                if(anag(temp->cuvant, cuv)){
                    printf("%s\n", temp->cuvant);
                }
                temp = temp->next;
            }
        }
        
    }
    void test3(struct hashmap *ht){
        
        for(int i = 0;i<ht->size;i++){
            Nod *temp1 = ht->buckets[i];
            while(temp1!=NULL){
                int a = -1;
                for(int i = 0;i<ht->size;i++){
                    Nod *temp2 = ht->buckets[i];
                    while(temp2!=NULL){
                        if( anag(temp1->cuvant, temp2->cuvant)){
                            a++;
                        }
                        temp2=temp2->next;
                    }
                }
                if(a==0){
                    printf("%s\n", temp1->cuvant);
                }
                temp1 = temp1->next;
            }
        }
    
        
    }
    
    

int main(){
    int sizeh;
    int numarc;
    char cuvant[21];
    int c;
    struct hashmap ht;
    
    scanf("%d", &sizeh);
    scanf("%d", &numarc);
    
    ht.size = sizeh;
    ht.buckets = calloc(ht.size, sizeof(Nod*));
    
    for(int i = 0;i<numarc;i++){
        scanf("%s", cuvant);
        int index = hash(cuvant, ht.size);
        Nod *nou = CreareNod(cuvant);
        ht.buckets[index] = Adugare(ht.buckets[index], nou);
    };
    scanf ("%d", &c);
    switch(c){
        case(1):{
            afisare(&ht);
            break;            
        };
        case(2):{
            scanf("%s", cuvant);
            test2(&ht, cuvant);
            break;
        };
        case(3):{
            test3(&ht);
            break;
        }
    }
    
    
    
    
    return 0;
}