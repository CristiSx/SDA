#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NOD{
    char nume[16];
    int produse;
    struct NOD *next;
}NOD;

NOD *CreareNod(char *nume, int produse){
    NOD *nou = malloc(sizeof(NOD));
    strcpy(nou->nume, nume);
    nou->produse = produse;
    nou->next = NULL;
    
    return nou;
};

NOD *AdugareNod(NOD *head, NOD *nou){
  if(head == NULL){
      return nou;
  }
  NOD *temp = head;
  while(temp->next != NULL){
      temp = temp->next;
  }
  temp -> next = nou;
  return head;
};

void Afisare(NOD *head){
    NOD *temp = head;
    while(temp!=NULL){
        printf("%s %d\n", temp->nume, temp->produse);
        temp = temp->next;
    }}
void Afisare3(NOD *head){
    NOD *temp = head;
    while(temp!=NULL){
        printf("%s\n", temp->nume);
        temp = temp->next;
    }
     
}
int total(NOD *head){
    NOD *temp = head;
    int sum = 0;
    while(temp!=NULL){
        sum = sum + temp->produse;
        temp = temp->next;
    }
    
    return sum;
}
NOD *Sterge( NOD *head){
    if(head == NULL){
        return NULL;
    }
    NOD *nodSters = head;
    head = head->next;
    free(nodSters);
    return head;
    
}
void test4(NOD *head, int n){
    while(head!=NULL && n>head->produse){
  
        n = n - head->produse;
        head = Sterge(head);
    
        }
    Afisare3(head);
}

int main()
{
    
    int c;
    int n;
    char nume[16];
    NOD *Lista =NULL;
    NOD *coada1 = NULL;
    NOD *coada2 = NULL;
    int produse;
    scanf("%d", &c);
    scanf("%d", &n);
    while(scanf("%s", nume)!=EOF){
        scanf("%d", &produse);
        NOD *nou = CreareNod(nume, produse);
        Lista = AdugareNod(Lista, nou);
    }
    switch(c){
        case(1):{
            Afisare(Lista);
            break;
        };
        case(2):{
            int t = total(Lista);
            printf("%d", t);
            break;
        };
        case(3):{
        NOD *temp = Lista;
        int i = 1;
    
        while(temp!=NULL){
            NOD * nou = CreareNod(temp->nume, temp->produse);
            if(i%2==0){
                coada1 = AdugareNod(coada1,nou);
            }else{
                coada2 = AdugareNod(coada2,nou);
            }
        i++;
            temp = temp->next;
        }
        Afisare3(coada2);
        Afisare3(coada1);
          
        break;  
        };
        case(4):{
        NOD *temp = Lista;
        int i = 1;
    
        while(temp!=NULL){
            NOD * nou = CreareNod(temp->nume, temp->produse);
            if(total(coada2)>total(coada1)){
                coada1 = AdugareNod(coada1,nou);
            }else{
                coada2 = AdugareNod(coada2,nou);
            }
        i++;
            temp = temp->next;
        }
        Afisare3(coada2);
        Afisare3(coada1);
            
            break;
        };
        case(5):{
             NOD *temp = Lista;
        int i = 1;
    
        while(temp!=NULL){
            NOD * nou = CreareNod(temp->nume, temp->produse);
            if(total(coada2)>total(coada1)){
                coada1 = AdugareNod(coada1,nou);
            }else{
                coada2 = AdugareNod(coada2,nou);
            }
        i++;
            temp = temp->next;
        }
            test4(coada2,n);
            test4(coada1,n);
            
            break;
        };
    }
    
    return 0;
}
