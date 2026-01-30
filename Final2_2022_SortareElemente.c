#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NOD{
    char nume[16];
    int ident;
    struct NOD *next;
    struct NOD *prev;
}NOD;

NOD *CreareNod(char *nume, int ident){
    NOD *nou = malloc(sizeof(NOD));
    strcpy(nou->nume, nume);
    nou->ident = ident;
    nou->next = NULL;
    nou->prev = NULL;
    return nou;
}

NOD *AdugareNod(NOD *head, NOD *nou){
    if(head == NULL){
        return nou;
    }
    NOD *temp = head;
    while(temp->next!=NULL){
        temp = temp->next;
    }
    temp->next = nou;
    temp->next->prev = temp;
    return head;
}

void Afisare(NOD *head){
    NOD *temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
        
    while(temp!=NULL){
        printf("%s %d\n", temp->nume, temp->ident);
        temp = temp->prev;
    }
}

void identificatorm(NOD *head){
    NOD *temp = head;
    int identm = 0;
    char numem[16];
    while(temp!=NULL){
        if(temp->ident > identm){
            identm = temp->ident;
            strcpy(numem, temp->nume);
        }
        
        temp = temp -> next;
    }
    printf("%s\n", numem);
}

NOD *Stergere(NOD *head, int i){
    if(head == NULL){
        return NULL;
    }
    NOD *temp = head;
    while(temp!=NULL && temp->ident!=i){
        temp = temp->next;
    }
    
    if(temp == head){
        head = head->next;
        if(head!=NULL){

             head->prev = NULL;
        }
        free(temp);
        return head;
    }
    if(temp->next!=NULL){
        temp->next->prev = temp->prev; 
    }
    temp->prev->next=temp->next;
    free(temp);
    return head;
}

int identificator(NOD *head){
    NOD *temp = head;
    int identm = 0;
    while(temp!=NULL){
        if(temp->ident > identm){
            identm = temp->ident;
        }
        
        temp = temp -> next;
    }
    return identm;
}

NOD *AdugareNodS(NOD *head, NOD *nou){
    if(head == NULL){
        return nou;
    }
    nou->next = head;
    nou->prev = NULL;
    head->prev = nou;
    return nou;
}

NOD *Sortare(NOD *head, NOD *ListaS){
    while(head!=NULL){
        NOD *temp = head;
        int identm = identificator(head);
        while(temp->ident != identm){
            
              temp = temp->next;
        }
            NOD *nou = CreareNod(temp->nume, temp->ident);
            ListaS = AdugareNod(ListaS, nou);
            head = Stergere(head, identm);
    }
    return ListaS;
}

void AfisareP(NOD *head){
    NOD *temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
        
    while(temp!=NULL){
        if(temp->ident%2==0)
        printf("%s %d\n", temp->nume, temp->ident);
        temp = temp->prev;
    }
}

void AfisareI(NOD *head){
    NOD *temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    } 
    while(temp!=NULL){
        if(temp->ident%2!=0)
        printf("%s %d\n", temp->nume, temp->ident);
        temp = temp->prev;
    }
}

int main(){
    int c;
    scanf("%d", &c);
    int intreg;
    scanf("%d", &intreg);
    char nume[16];
    int ident;
    NOD *Lista = NULL;
    NOD *ListaS = NULL;
    while(scanf("%s", nume)!=EOF){
        scanf("%d", &ident);
        NOD *nou = CreareNod(nume, ident);
        Lista = AdugareNod(Lista, nou);
    }
    
    switch(c){
        case(1):{
            Afisare(Lista);
              
            break;
        };
        case(2):{
            identificatorm(Lista);
            break;
        };
        case(3):{
            Lista = Stergere(Lista, intreg);
            Afisare(Lista);
            break;
        };
        case(4):{
              ListaS = Sortare(Lista, ListaS);
              Afisare(ListaS);
            break;
        };
        case(5):{
            ListaS = Sortare(Lista, ListaS);
             AfisareI(ListaS);
             AfisareP(ListaS);
            break;
        };
    }
    return 0;
}
