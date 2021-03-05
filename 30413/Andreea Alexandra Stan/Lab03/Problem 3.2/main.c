#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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


//Doubly linked list node structure:
typedef struct node_type
{
    char key[20];
    int repetitions;
    struct node_type *next;
    struct node_type *prev;
} NodeT;


//doubly linked list header
typedef struct
{
    int count;
    NodeT *first;
    NodeT *last;

} ListT;



//create an initial empty list:
ListT *createEmptyList()
{
    ListT *listPtr=(ListT*)malloc(sizeof(ListT));
    if (listPtr)
    {
        listPtr->count = 0;
        listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}

//function to check if the list is empty or not
int isEmpty( ListT *listPtr )
{
    return listPtr->first == NULL;
}



//function to create a node:
NodeT *createNode(char s[],int re)
{
    NodeT *p= (NodeT *)malloc(sizeof(NodeT));
    if(p)
    {
        strcpy(p->key,s);
        p->repetitions=re;
        p->next=p->prev=NULL;
    }
    return p;

}


//function to delete a node from a doubly linked list
void delete_node(NodeT *p)
{
    if (p)
    {
        p->next->prev = p->prev;
        p->prev->next = p->next;
    }

}



//function to insert a node at the end of the list
void insertAtRear(ListT *listPtr, NodeT *p)
{
    if (listPtr)
    {
        if(isEmpty(listPtr))
        {
            listPtr->first=listPtr->last=p;
            p->prev=p->next=NULL;
        }
        else
        {
            listPtr->last->next=p;
            p->prev=listPtr->last;
            p->next=NULL;

        }
        listPtr->last = p;
        listPtr->count++;

    }

}


//make all the uppercase letters of a word into lowercase
void lowercase(char s[])
{
    for(int i=0; i<strlen(s); i++)
        if(s[i]>='A' && s[i]<='Z')
            s[i]+=32;
}


//function to compare 2 character string
int compare(char s[],char t[])
{
    char aux1[20],aux2[20];
    strcpy(aux1,s);
    strcpy(aux2,t);
    //made auxiliary copies of the strings in the arguments so they won't be modified

    lowercase(aux1);
    lowercase(aux2);
    //comparing is most of the time not case sensitive in this problem
    //so i compared the strings with all letters lowercase



    if(strcmp(aux1,aux2)>0)
        return 1; //1 means that they are in descending alphabetical order

    if(strcmp(aux1,aux2)==0)

        if(strcmp(s,t)<0) // if the words are identical we check if the first letter is upper or lower case
            return 1;//in this case,when sorting in ascending aphabetical order, the lowercase letter comes first


    return 0; //=they are in descending alphabetical order

}


//sort the nodes of the doubly linked list in ascending alphabetical order according to the key
void sort(ListT *listPtr)
{
    NodeT *p;

    int ok;
    char aux[20];
    p=listPtr->first;

    //bubble sort:

    do
    {
        ok=0;
        p=listPtr->first;
        while(p->next!=NULL)
        {

            if(compare(p->key,p->next->key)==1)//if they are in descending order we swap the information of the two neighour nodes
            {
                strcpy(aux,p->key);
                strcpy(p->key,p->next->key);
                strcpy(p->next->key,aux);

                ok=1; //we swapped something
            }

            p=p->next;
        }


    }
    while(ok);


}




//we modify the list according to the assignment: we delete the nodes that appear multiple times, keeping on of them
//also count the number of repetitions of each word and add it to the node of the list
void modify_repetitions(ListT *listPtr)
{
    NodeT *p,*q;
    int count;

    char aux[20];

    p=listPtr->first;
    q=listPtr->first;

    if(p==NULL)
        return;

    while(p!=NULL)
    {
        strcpy(aux,p->key);

        //count=number of occurences of the current word in the list
        count=1;

        if(p->next!=NULL)
        {
            q=p->next;

            while(q->next!=NULL && strcmp(q->key,p->key)==0)
            {
                delete_node(p->next);
                q=q->next;
                count++;
                listPtr->count--;//decrease the number of nodes everytime we delete a new one

            }
            //keep deleting the nodes till we find a different one
        }
        p->repetitions=count;


        p=p->next;
    }
    free(p);
    free(q);


}



//print the list in ascending order
void print_ascending(ListT *listPtr, FILE* pf)
{
    NodeT *p;
    for(p=listPtr->first; p!=NULL; p=p->next)
        fprintf(pf,"%s:%d\n",p->key,p->repetitions);

}

//print the list in descending order
void print_descending(ListT *listPtr,FILE *pf)
{
    NodeT *p;
    for(p=listPtr->last; p!=NULL; p=p->prev)
        fprintf(pf,"%s:%d\n",p->key,p->repetitions);

}


//purge the list:
void purge(ListT *listPtr)
{
	NodeT *p;
	while ( listPtr->first != NULL )
	{
	  p = listPtr->first;
	  listPtr->first = listPtr->first->next;
	  free( p );
	}
	listPtr->last = NULL;
	listPtr->count = 0;
}



int main(int argc, char* argv[])
{

    FILE *f, *pf;

     if (argc < 2)
         {
             printf("No file name given\n");
             exit(1);
         }


    f=openAndCheck(argv[1], "r");//argv[1]="input.txt"
    pf=openAndCheck(argv[2], "w");//argv[2]="output.txt"


    ListT *list= createEmptyList(); //create an empty list

    char *s=(char*)malloc(20*sizeof(char));

    //read all the words from the file. they should be the key of every node of the doubly linked list
    //create a note with the word read from the file, then add it at the end of the list
    //number of repetitions of each word is initially 0
    while(fscanf(f,"%s",s)!=EOF)

        insertAtRear(list,createNode(s,0));

    free(s);


    sort(list);
    modify_repetitions(list);
    print_ascending(list,pf);
    //fprintf(pf,"\n\n");
    print_descending(list,pf);

    //close the files
    fclose(f);
    fclose(pf);

    purge(list);



    return 0;
}
