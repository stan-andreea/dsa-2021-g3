#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define B 2879

//2879 is the sum of the ascii codes of all the letters +space
//so entries would collide only if they have the exact same letters

//calculate the hash value
int f(char key[])
{
    int sum;
    sum = 0;
    int c;
    for (int i = 0; i < strlen(key); i++)
    {
        c=key[i];
        sum += c;
    }

    return(sum % B);
}



typedef struct cell
{
    char key[60];
    /* other useful info */
    struct cell *next;
} NodeT;

NodeT *BucketTable[B];

//create an emtpy table:
NodeT *create_empty()
{
    if(BucketTable)
    {
        for (int i = 0; i < B; i++)
            BucketTable[i] = NULL;
    }

    return BucketTable[B];
}


//function to check if a name is in the table:
int *find(NodeT *BucketTable[B],char key[])
{
    NodeT *p;
    int h;
    h=f(key);
    p = BucketTable[h];
    while (p != NULL)
    {
        if (strcmp(key, p->key) == 0)
            return h;//found, return the index
        p = p->next;
    }
    return -1;//not found
}


//function to insert in the hash table
void insert(NodeT *BucketTable[B],char key[], FILE *fo)
{
    NodeT *p;
    int h;
    p = (NodeT *) malloc(sizeof(NodeT));
    if (p)
    {
        strcpy(p->key,key);
        p->next = NULL;//intialize the node

        h = f(p->key);

        if (BucketTable[ h ] == NULL)
        {

            BucketTable[ h ] = p;
            p->next = NULL;
        }

        else
        {

            int q;

            q = find(BucketTable,p->key);
            if (q == -1)
            {
                /* not found. Insert it */
                p -> next = BucketTable[ h ];
                BucketTable[ h ] = p;
                //p->next->next=NULL;

            }

        }


    }
    else
    {
        fprintf(fo,"error allocating memory for the node");
        exit(1);
    }

}

//function to delete a given key from a linked list



void deleteByKey(NodeT *p, char givenKey[])//function to delete a given key from a linked list
{
    NodeT *q, *q1;
    q1 = NULL;
    q =p;

    while ( q!= NULL )
    {
        if(strcmp(q->key,givenKey)==0)
            break;
        q1 =q;
        q= q->next;
    }
    if ( q != NULL )
    {
        if ( q == p )
        {

            q1=p;
            p=p->next;
            free( q1 );
            // if (  == NULL ) listPtr->last = NULL;
        }
        else
        {
            q1->next=q->next;
            if ( q ->next==NULL)  q= q1;
            free( q );
        }



    }

}



//delete an element from the table:

void delete_el(NodeT *BucketTable[B],char key[])
{
    NodeT *p;

    if(find(BucketTable,key)==-1)
        return;
    else
    {
        int h;
        h = f(key);
        if(BucketTable[h]->next==NULL)
            BucketTable[h]=NULL;
        else
        {
            p=BucketTable[h];
            NodeT *q, *q1;
            q1 = NULL;
            q =p;

            while ( q!= NULL )
            {
                if(strcmp(q->key,key)==0)
                    break;
                q1 =q;
                q= q->next;
            }

            if(q==p)
            {
                q->next=p;
                free(q);
            }
            else if(q->next==NULL)
            {
                q1->next=NULL;
                free(q);
            }
            else
            {
                q1->next = q1->next->next;
                free(q);
            }




        }
    }


}

void print(NodeT *BucketTable[B], FILE *fo)
{
    NodeT *p;
    p = (NodeT *) malloc(sizeof(NodeT));


    for (int i = 0; i < B; i++)
        if (BucketTable[ i ] != NULL)
        {
            fprintf(fo,"\nBucket for hash value %d\n", i);
            NodeT *p;
            p = (NodeT *) malloc(sizeof(NodeT));

            p =BucketTable[ i ];
            while (p != NULL)
            {
                fprintf(fo,"%s\n",p->key);
                p = p->next;
            }
        }

}

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


    if (argc < 2)
    {
        printf("No file name given\n");
        exit(1);
    }

    BucketTable[B]=create_empty();


    FILE *fi, *fo;
    fi=openAndCheck(argv[1], "r");//argv[1]="input.txt"
    fo=openAndCheck(argv[2], "w");//argv[2]="output.txt"

    //count the number of commands given in the file by counting the lines:

    int lines=1;
    char c;

    c=fgetc(fi);
    while(c!=EOF)
    {
        if(c=='\n') lines++;
        c=fgetc(fi);
    }

    rewind(fi);


    char name[50];
    for(int i = 0; i < lines; i++)

    {

        fgets(name,50,fi);

        if(i!=lines-1)
            name[strlen(name)-1]='\0';//delete the newline characther,which would appear in all lines except the last one



        switch(name[0])
        {
        case 'i':

            insert(BucketTable,name+1,fo);
            break;



        case 'f':

            if(find(BucketTable,name+1)!=-1)

            {
                //int c=f(name+1);

                fprintf(fo,"\nYes, %s found at table index %d\n",name+1, find(BucketTable,name+1));
            }

            else fprintf(fo,"\nNo, %s not found \n",name+1);

            break;


        case 'd':

            delete_el(BucketTable,name+1);
            break;

        case 'l':
            print(BucketTable,fo);

            break;


        default:
            fprintf(fo,"\nThe operation %c is not valid\n",name[0]);

        }


    }


    fclose(fi);
    fclose(fo);

    return 0;
}

