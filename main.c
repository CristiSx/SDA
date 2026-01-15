#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Nod{
    int secunde;
    struct Nod *next;
}Nod;

Nod *CreareNod(int sec){
    Nod *nou = malloc(sizeof(Nod));
    nou->secunde = sec;
    nou->next = NULL;
return nou;
};

Nod *Adugare(Nod *head, Nod *nou){
    if(head == NULL){
        return nou;
    }
    Nod *temp = head;
    while(temp->next != NULL){
        temp=temp->next;
    };
    temp->next = nou;
    return head;
}
Nod *AdugareSortata(Nod *head, Nod *nou){
    if(head == NULL){
        return nou;
    }
    if(head->secunde>=nou->secunde){
        nou->next = head;
        return nou;
    }
    Nod * temp = head;
    while(temp->next != NULL){
        if(temp->next->secunde>=nou->secunde){
            break;
        }
        temp = temp -> next;
    }
    nou->next = temp->next;
    temp->next = nou;
    
    return head;
}
Nod *AdugareSortatai(Nod *head, Nod *nou){
    if(head == NULL){
        return nou;
    }
    if(head->secunde<=nou->secunde){
        nou->next = head;
        return nou;
    }
    Nod * temp = head;
    while(temp->next != NULL){
        if(temp->next->secunde<=nou->secunde){
            break;
        }
        temp = temp -> next;
    }
    nou->next = temp->next;
    temp->next = nou;
    
    return head;
}

void Afisare(Nod *head){
     
    Nod *temp = head;
    while(temp != NULL){
        printf("%d\n", temp->secunde);
        temp=temp->next;
    }
}
void medie(Nod *head){
    Nod *temp = head;
    float sum = 0;
    int i = 0;
    while(temp!=NULL){
        sum += temp->secunde;
        i++;
        temp = temp -> next;
    }
    sum = sum/i;
    printf("%.2f", sum);
}
void Afisare4(Nod *head){
     
    Nod *temp = head;
    while(temp->next!= NULL){
        printf("%d\n", temp->secunde);
        temp=temp->next;
    }
}
int main(){
    int sec;
    int c;
    scanf("%d", &c);
    Nod *Lista = NULL;
    while(scanf("%d", &sec)!=EOF){
        
        Nod *nou = CreareNod(sec);
        Lista = Adugare(Lista, nou);
    }
    
    
    switch(c){
        case(1):{
         
            Afisare(Lista);
            
            break;
        };
        case(2):{
          medie(Lista);  
            break;
        };
        case(3):{
            Nod *ListaSortata = NULL;
            Nod *temp = Lista;
            while(temp!=NULL){
                Nod *nou = CreareNod(temp->secunde);
                ListaSortata = AdugareSortata(ListaSortata, nou);
                temp = temp->next;
            }
            temp = ListaSortata;
            int m[4];
            for(int i = 0;i<4;i++){
                m[i] = temp->secunde;
                temp = temp->next;
            }
            temp = Lista;
            while(temp!=NULL){
                for(int i = 0;i<4;i++){
                    if(temp->secunde == m[i]){
                        printf("%d\n",temp->secunde);
                    }
                }
                
                temp = temp->next;
            }
            break;
        };
        case(4):{
          Nod *ListaSortatai = NULL;
          Nod *temp = Lista;
            while(temp!=NULL){
                Nod *nou = CreareNod(temp->secunde);
                ListaSortatai = AdugareSortatai(ListaSortatai, nou);
                temp = temp->next;
            }  
            Afisare4(ListaSortatai);
            break;
        };
    }
    return 0;
}