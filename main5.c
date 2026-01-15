#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Persoana{
    char nume[20];
    float inaltime;
    struct Persoana * next;
};

struct Hashmap{
    struct Persoana ** map;
    int capacitate;
    int nr_elemente;
};

struct Persoana * creare_nod(char nume[20], float inaltime){
    struct Persoana * nod_nou = malloc(sizeof(struct Persoana));
    strcpy(nod_nou->nume, nume);
    nod_nou->inaltime = inaltime;
    nod_nou->next = NULL;
    return nod_nou;
}

struct Persoana * adaugare_persoana_la_final(struct Persoana * head,
                                             char nume[20], 
                                             float inaltime){
// struct Persoana * adaugare_persoana_la_final(struct Persoana * head,
//                                              struct Persoana * nod_nou){
    if (head == NULL){
        return creare_nod(nume, inaltime);
        // return nod_nou;
    }
    
    struct Persoana * nod_curent = head;
    
    while(nod_curent->next != NULL){
        nod_curent = nod_curent->next;
    }
    
    nod_curent->next = creare_nod(nume, inaltime);
    // nod_curent->next = nod_nou;
    
    return head;
}

void afisare_lista(struct Persoana * head){
    while(head){
        printf("%s %.2f\n", head->nume, head->inaltime);
        head = head->next;
    }
}

int hash(char nume[20], float inaltime, int capacitate){
    int suma = 0;
    int i=0;
    int rezultat;
    
    while(nume[i]){ // cat timp caracterul curent este diferit de '\0'
        suma += nume[i++];
    }
    
    rezultat = suma * inaltime; // conversie implicita la nr intregi
    return rezultat % capacitate;
}

struct Hashmap * creare_hashmap(int capacitate){
    struct Hashmap * hashmap = malloc(sizeof(struct Hashmap));
    hashmap->map = calloc(capacitate, sizeof(struct Persoana *));
    hashmap->capacitate = capacitate;
    hashmap->nr_elemente = 0;
    return hashmap;
}

void inserare_element_hashmap(struct Hashmap * hashmap, 
                              struct Persoana * persoana){
    int index = hash(persoana->nume, 
                     persoana->inaltime, 
                     hashmap->capacitate);
    
    while(hashmap->map[index % hashmap->capacitate] != NULL){
        index++;
    }
    
    hashmap->map[index % hashmap->capacitate] = persoana;
    hashmap->nr_elemente = hashmap->nr_elemente + 1;
}

void afisare_elemente_hashmap(struct Hashmap * hashmap){
    for (int i=0; i<hashmap->capacitate; i++){
        if (hashmap->map[i] != NULL){
            printf("%d: %s\n", i, hashmap->map[i]->nume);
        }
        else{
            printf("%d: \n", i);
        }
    }
}

int nr_comparatii(struct Hashmap * hashmap, 
                  struct Persoana * persoana){
    int index_initial = hash(persoana->nume, 
                             persoana->inaltime, 
                             hashmap->capacitate);
    int nr_comparatii = 1;
    while (strcmp(persoana->nume, hashmap->map[index_initial % hashmap->capacitate]->nume) != 0){
        nr_comparatii++;
        index_initial++;
    }
    return nr_comparatii;
}

int main(){
    int capacity;
    int nr_persoane;
    char temp_nume[20];
    float temp_inaltime;
    int comanda;
    struct Persoana * lista = NULL;
    
    scanf("%d", &capacity);
    scanf("%d", &nr_persoane);
    
    for (int i=0; i<nr_persoane; i++){
        scanf("%s", temp_nume);
        scanf("%f", &temp_inaltime);
        lista = adaugare_persoana_la_final(lista, temp_nume, temp_inaltime);
        // struct Persoana * nod_nou = creare_nod(temp_nume, temp_inaltime);
        // lista = adaugare_persoana_la_final(lista, nod_nou);
    }
    
    scanf("%d", &comanda);
    
    switch(comanda){
        case 1:{
            afisare_lista(lista);
            break;
        }
        
        case 2:{
            struct Hashmap * map = creare_hashmap(capacity);
            while(lista){
                inserare_element_hashmap(map, lista);
                lista = lista->next;
            }
            
            afisare_elemente_hashmap(map);
            break;
        }
        
        case 3:{
            struct Hashmap * map = creare_hashmap(capacity);
            struct Persoana * head = lista;
            while(head){
                inserare_element_hashmap(map, head);
                head = head->next;
            }
            
            head = lista;
            while(head){
                printf("%s %d\n", head->nume, nr_comparatii(map, head));
                head = head->next;
            }
            break;
        }
        
        case 4:{
            int prag_comparatii;
            scanf("%d", &prag_comparatii);
            
            int nr_total_comparatii;
            capacity = nr_persoane;
            
            struct Hashmap * map = NULL;
            
            do {
                nr_total_comparatii = 0;
                map = creare_hashmap(capacity);
                struct Persoana * head = lista;
                while(head){
                    inserare_element_hashmap(map, head);
                    head = head->next;
                }
                
                head = lista;
                while(head){
                    nr_total_comparatii += nr_comparatii(map, head);
                    // printf("%s %d\n", head->nume, nr_comparatii(map, head));
                    head = head->next;
                }
                
                // printf("Capacitate:%d ---> comparatii:%d\n", capacity, nr_total_comparatii);
                capacity++;
            } while(nr_total_comparatii > prag_comparatii);
            
            printf("%d\n", capacity-1);
            afisare_elemente_hashmap(map);
            
            break;
        }
        
        default:{
            break;
        }
    }
    
    
    return 0;
}