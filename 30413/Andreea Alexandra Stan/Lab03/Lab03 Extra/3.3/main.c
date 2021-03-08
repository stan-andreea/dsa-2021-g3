#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int key;
    struct node *next_prev;//can point to either the next or the previous node
} NodeT;


typedef struct
{
    int count;
    NodeT *first; /* link to the first node in the list */
    NodeT *last; /* link to the last node in the list */
} ListT;


//function to create an initial empty list:
ListT *createEmptyList()
{
    ListT *listPtr = (ListT*)malloc(sizeof(ListT));
    if (listPtr)
    {
        listPtr->count = 0;
        listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}


NodeT *createNode(int key)
{
    NodeT *p = (NodeT *)malloc(sizeof(NodeT));
    if (p)
    {
        p->key = key;
        p->next_prev = NULL;
    }
    return p;
}


NodeT *createNodeXOR(NodeT *a,NodeT *b)
{

    return (int) a ^ (int )b;
}


int isEmpty( ListT *listPtr )
{
    return listPtr->first == NULL;
}




//insert every new node at the front of the list
int insertAtFront(ListT *listPtr, NodeT *p)
{
    NodeT *q;

    if (listPtr)
    {

        p->next_prev= createNodeXOR(listPtr->first,NULL);
        if (isEmpty(listPtr))
        {
            listPtr->last = p;
        }
        else
        {
            q=createNodeXOR(listPtr->first->next_prev, NULL);
            listPtr->first->next_prev = createNodeXOR(p,q );
        }
        listPtr->first = p;
        listPtr->count++;
        return 1;
    }
    return 0;
}



//traverse from left to right and print

void print_left_to_right(ListT *listPtr, FILE *pf)
{
    NodeT *p, *pnext,*pprev;
    //p is the current node,pnext the next node,and pprev the previous one

    p = listPtr->first;
    if(p == NULL)
        fprintf(pf,"none");//the list is empty
    else
    {
        pprev=NULL;//no node before the first one
        while (p!= NULL)
        {
            fprintf(pf,"%d ",p->key);

            pnext=createNodeXOR(pprev,p->next_prev);
            pprev=p;
            p=pnext;
        }
    fprintf(pf,"\n");
    }

}


//traverse from right to left and print
void print_right_to_left(ListT *listPtr,FILE *pf)
{
    NodeT *p, *pnext,*pprev;
    //p is the current node,pnext the next node,and pprev the previous one
    p = listPtr->last;
    if(p == NULL)
        fprintf(pf,"none");//the list is empty
    else
    {
        pnext=NULL;//because there is no node after the last one

        while (p!= NULL)
        {
            fprintf(pf,"%d ",p->key);

            pprev=createNodeXOR(pnext,p->next_prev);
            pnext=p;
            p=pprev;
        }
        fprintf(pf,"\n");
    }
}

//function to open and check a file:
FILE *openAndCheck(char *filePath, char *mode)
{
    FILE *f = fopen(filePath, mode);
    if (f==NULL)
    {
        printf("Cannot open the file");
        exit(0);
    }
    return f;
}


int main(int argc, char* argv[])
{
    ListT *list=createEmptyList();
    FILE *f, *pf;

     if (argc < 2)
         {
             printf("No file name given\n");
             exit(1);
         }

    f=openAndCheck(argv[1], "r"); //input files contains nodes of the list
    pf=openAndCheck(argv[2], "w");


    int x;

    while(!feof(f))
    {
        fscanf(f,"%d",&x);
        insertAtFront(list,createNode(x));
    }

    print_left_to_right(list,pf);
    print_right_to_left(list,pf);









    /*insertAtFront(list,createNode(10));
    insertAtFront(list,createNode(20));
    insertAtFront(list,createNode(25));
    print(list);
    print_reverse(list);*/

    return 0;
}
