#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct NOD{
    char nume[31];
    
    struct NOD *next;
}NOD;

NOD *CreareNod(char *nume){
    NOD *nou = malloc(sizeof(NOD));
    strcpy(nou->nume, nume);
    nou->next =NULL;
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
    return head;
}

void Afisare(NOD *head){
    NOD *temp = head;
    int k = 0;
    while(temp!=NULL){
        printf("%s\n", temp->nume);
        temp = temp->next;
        k++;
        if(k%2==0){
            printf("\n");
        }
        
    }
}

void Intalnire(NOD *head, char *nume1, char *nume2){
    int i1 = 0;
    int i2 = 0;
    int i = 0 ;
    
    NOD *temp = head;
    while(temp!=0){
        i++;
        if(strcmp(temp->nume, nume1)==0){
            i1 = i;
        }else if(strcmp(temp->nume, nume2)==0){
            i2 = i;
        }
        temp = temp->next;
    }
    int sum = 0;
    sum = i2 - i1;
    sum = sum/2;
    printf("%d", sum+1);
    
}

NOD *Stergere(NOD *head, char *nume){
    NOD *temp = head;
    NOD *ant = NULL;
    while(temp != NULL && strcmp(temp->nume, nume) != 0){
        ant = temp;
        temp = temp->next;
    }
    if(temp == NULL){
        return head;
    }
    if(ant == NULL){
        head = temp->next;
    }else{
        ant->next = temp->next;
    }
    free(temp);
    return head;
}


NOD *test3(NOD *head){
    NOD *temp = head;
    int p;
    int i;
    while(temp!=NULL){
        int k = 0;
        int m;
        
        scanf("%d", &p);
        for(i=0;i<p;i++){
            scanf("%d", &m);
            if(m==6){
                k++;
            }
        }
        
        NOD *urm1 = temp->next;
        if(k!=3){
            head = Stergere(head, temp->nume);
        }
        
        temp=urm1;
        if(temp == NULL){
            break;
        }
        
        k = 0;
        for(i=0;i<p;i++){
            scanf("%d", &m);
            if(m==6){
                k++;
            }
        }
        NOD *urm2 = temp->next;
        if(k!=3){
            head = Stergere(head, temp->nume);
        }
        temp = urm2;
        
    }
    return head;
}

void test4(NOD *head){
    NOD *temp = head;
    int p, m, i;
    char nume1[31];
    char nume2[31];
    int sumamax = 0;
    while(temp!=NULL){
        int suma = 0;
        scanf("%d", &p);
        for (i=0;i<p;i++){
            scanf("%d", &m);
            suma += m;
        }
        for (i=0;i<p;i++){
            scanf("%d", &m);
            suma += m;
        }
        if(suma>sumamax){
            sumamax = suma;
            strcpy(nume1, temp->nume);
            temp = temp->next;
            strcpy(nume2, temp->nume);
            temp = temp->next;
        }else{
             temp = temp->next->next;
        }
    }
    printf("%s\n%s\n", nume1, nume2);
}

int main(){
    int n;
    NOD *Lista = NULL;
    char nume[31];
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        scanf("%s", nume);
        NOD *nou=CreareNod(nume);
        Lista = AdugareNod(Lista,nou);
    }
    int c;
    scanf("%d", &c);
    switch(c){
        case(1):{
            Afisare(Lista);  
            break;
        };
        case(2):{
            char nume1[31];
            char nume2[32];
            scanf("%s", nume1);
            scanf("%s", nume2);
            Intalnire(Lista,nume1,nume2);
            break;
        };
        case(3):{
            Lista = test3(Lista);
            Afisare(Lista);
            break;
        };
        case(4):{
            test4(Lista);  
            break;
        };
        case(5):{
            while(Lista->next != NULL){
                Lista = test3(Lista);
            }
            Afisare(Lista);
            break;
        };
    }
    
    return 0;
}
