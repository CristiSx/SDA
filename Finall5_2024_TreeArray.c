#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NOD{
    char cuv[21];
    int frecv;
    struct NOD *next;
    
}NOD;

typedef struct NODA{
    char cuv[21];
    int frecv;
    struct NODA *NODs;
    struct NODA *NODd;    
}NODA;

NODA *creare(char *cuv){
    NODA *nod = malloc(sizeof(NODA));
    strcpy(nod->cuv, cuv);
    nod->frecv = 1;
    nod->NODs = NULL;
    nod->NODd = NULL;
    return nod;
}

NODA *adugare(NODA *head, char *cuv){
    if(head == NULL){
        return creare(cuv);
    }
    if(strcmp(head->cuv, cuv)==0){
        head->frecv++;
        return head;
    }
    if(strcmp(head->cuv, cuv)>0){
        head->NODs=adugare(head->NODs, cuv);
    }else{
        head->NODd=adugare(head->NODd, cuv);
    }
    return head;
}

void afisare(struct NODA *prim){
    if(prim == NULL){
        return;
    }
    afisare(prim->NODs);
    printf("%s\n", prim->cuv); 
    afisare(prim->NODd);
}

void afisarepost(struct NODA *prim){
    if(prim == NULL){
        return;
    }
    afisarepost(prim->NODs);
    
    afisarepost(prim->NODd);
    printf("%s\n", prim->cuv);
}

void parcurgere(struct NODA *prim, char *var){
    if(prim == NULL){
        return;
    }
    if(strcmp(prim->cuv, var)!=0){
        parcurgere(prim->NODs,var);
        parcurgere(prim->NODd,var);
    }else{
        afisarepost(prim);
    }
}

void CeiMaiMari(struct NODA *prim,char *cuvmm, char *cuvm, int mai_mare, int mare){
     if(prim == NULL){
        return;
    }
    if(prim->frecv>mai_mare){
        mare = mai_mare;
        strcpy(cuvm, cuvmm);
        mai_mare = prim->frecv;
         strcpy(cuvmm, prim->cuv);
    }else if(prim->frecv>mare){
        mare = prim->frecv;
        strcpy(cuvm, prim->cuv);
    }
    
    CeiMaiMari(prim->NODs, cuvmm, cuvm, mai_mare,mare);
    CeiMaiMari(prim->NODd, cuvmm, cuvm, mai_mare,mare);
}

void parcurgere2(struct NODA *prim, char *var){
    if(prim == NULL){
        return;
    }
    if(strcmp(prim->cuv, var)!=0){
        parcurgere2(prim->NODs,var);
        parcurgere2(prim->NODd,var);
    }else{
            int mai_mare = 0;
            int mare = 0;
            char cuvmm[21];
            char cuvm[21];
        CeiMaiMari(prim, cuvmm, cuvm, mai_mare, mare);
        printf("%s\n%s\n",cuvmm,cuvm);
    }
    
}

NOD *CreareNod(char *cuv){
    NOD *nou = malloc(sizeof(NOD));
    strcpy(nou->cuv, cuv);
    nou->frecv = 1;
    nou->next = NULL;
    
    return nou;
}

NOD *AdugareNod(NOD *head, NOD *nou){
    if(head == NULL){
        return nou;
    }
    NOD *temp = head;
    while(temp->next != NULL){
        
        temp =temp->next;
    }
    temp->next = nou;
    
    return head;
    
}

void Afisare(NOD *head){
    NOD *temp = head;
    while(temp!=NULL){
        printf("%s\n", temp->cuv);
        temp = temp->next;
    }
    
}

void Afisare2(NOD *head){
    NOD *temp = head;
    while(temp!=NULL){
        printf("%s %d\n", temp->cuv, temp->frecv);
        temp = temp->next;
    }
}

NOD *AdugareNod2(NOD *head, NOD *nou){
    if(head == NULL){
        return nou;
    }
    if(strcmp(head->cuv, nou->cuv)==0){
        head->frecv++;
        return head;
    }
    NOD *temp = head;
    while(temp->next != NULL){
        
        if(strcmp(temp->next->cuv, nou->cuv)==0){
                temp->next->frecv++;
            
            return head;
        }
        temp = temp->next;
    }
    temp->next = nou;
    
    return head;
}

NOD *Frecventa(NOD *Lista, NOD *Frecv){
    NOD *temp = Lista;
    while(temp!=NULL){
        NOD *nou = CreareNod(temp->cuv);
        Frecv = AdugareNod2(Frecv, nou);
        temp = temp->next;
        
    }
    return Frecv;
}

NOD *AdugareNod3(NOD *head, NOD *nou){
    if(head == NULL){
        return nou;
    }
    if(strcmp(head->cuv, nou->cuv)>0){
        nou->next = head;
        return nou;
    }
    NOD *temp = head;
    while(temp->next != NULL){
        
        if(strcmp(temp->next->cuv, nou->cuv)>0){
            nou -> next = temp ->next;
            temp->next  = nou;
            return head;
        }
        temp = temp->next;
    }
    
    temp->next = nou;
    return head;
    
}

int main(){
    int c;
    NOD *Lista = NULL;
    NOD *ListaF = NULL;
    NODA *prim = NULL;
    int i;
    char var[21];
    char cuv[21];
    scanf("%d %d", &c, &i);
    while(scanf("%s", cuv)!=EOF){
        
        if(i!=0){
            i--;
        }else{
            strcpy(var, cuv);
            i--;
        }
        
        NOD *nou = CreareNod(cuv);
        Lista = AdugareNod(Lista, nou);
    }
     NOD *temp = Lista;
          while(temp!=NULL){
              prim = adugare(prim, temp->cuv);
              temp = temp->next;
          }
    switch(c){
        case(1):{
            Afisare(Lista);  
            break;
        };
        case(2):{
           ListaF = Frecventa(Lista, ListaF);
           Afisare2(ListaF);
           break;
        };
        case(3):{
          afisare(prim);
          
          break;     
        };
        case(4):{
          parcurgere(prim, var);
          break;
        };
        case(5):{
          parcurgere2(prim, var);
          break;  
        };
    }
    
    return 0;
}
