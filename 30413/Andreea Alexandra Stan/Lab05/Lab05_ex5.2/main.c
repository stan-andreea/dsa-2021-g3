#include <stdio.h>
#include <stdlib.h>


//open the files/check if they can be opened
FILE *openAndCheck(char *filePath, char *mode)
{
    FILE *f = fopen(filePath, mode);
    if (NULL == f)
    {
        printf("Cannot open the file");
        exit(0);
    }
    return f;
}



typedef struct node_type
{
    char key;
    struct node_type *left, *right;

} BSTNodeT;

//function to create a node
BSTNodeT *createNode(char givenKey)
{
    /* build node */
    BSTNodeT *p = (BSTNodeT *) malloc (sizeof (BSTNodeT));
    if (p)
    {
        p->key = givenKey;
        p->left = p-> right = NULL; /* leaf node */
    }
    return p;
}

//function to insert a node:
BSTNodeT *insertNode(BSTNodeT *root, char key, FILE *f_out)
{
    /* If the tree is empty, then a single node tree is created */
    if (root == NULL)
        root = createNode(key);
    else
    {
        if (key < root->key)
            root->left = insertNode(root->left, key,f_out);

        else if (key > root->key)
            root->right = insertNode(root ->right, key,f_out);

        else
            fprintf(f_out,"\nNode with key = %c already exists\n", key);
    }
    return root;
}

//find a note with a given key:
BSTNodeT *find(BSTNodeT *root, char givenKey)
{
    if (root == NULL)
        return NULL; /* empty tree */

    for (BSTNodeT *p = root; p != NULL;)
    {
        if (givenKey == p->key) return p;
        else if (givenKey < p->key)
            p = p->left;
        else
            p = p->right;
    }

    return NULL; /* not found */
}

//find the minimum node of the tree:
BSTNodeT *findMin(BSTNodeT *node)
{
    if(node == NULL)
    {
        /* There is no element in the tree */
        return NULL;
    }

    if(node->left) /* Go to the left sub tree to find the min element */
        return findMin(node->left);
    else
        return node;
}


//find the maximum node of the tree:
BSTNodeT *findMax(BSTNodeT *node)
{
    if(node == NULL)
    {
        /* There is no element in the tree */
        return NULL;
    }

    if(node->right) /* Go to the left sub tree to find the min element */
        return findMax(node->right);

    else
        return node;
}


//delete a node with a given key:
BSTNodeT* delNode(BSTNodeT* node, char key, FILE *f_out)
{
    if(node == NULL)
    {
        fprintf(f_out,"Element %c Not Found to delete\n",key);
    }

    else if(key < node->key)
    {
        // must be in left subtree
        node->left = delNode(node->left, key,f_out);
    }

    else if(key > node->key)
    {
        // must be in right subtree
        node->right = delNode(node->right, key,f_out);
    }

    else
    {
        // found node

        if(node->right && node->left)
        {

            BSTNodeT *temp = findMin(node->right);
            node -> key = temp->key;
            node -> right = delNode(node->right, temp->key,f_out);

        }
        else
        {

            BSTNodeT *temp = node;
            if(node->left == NULL)
                node = node->right;

            else if(node->right == NULL)
                node = node->left;

            free(temp); /* temp is longer required */
        }
    }
    return node;
}

// Traversals of a BST

void preorder(BSTNodeT *p, FILE *f_out)
{
    if (p != NULL)
    {
        fprintf(f_out,"%c\n", p->key);
        preorder(p->left,f_out);
        preorder(p->right,f_out);
    }
}


void inorder(BSTNodeT *p,FILE *f_out)
{
    if (p != NULL)
    {
        inorder(p->left,f_out);
        fprintf(f_out,"%c\n", p->key);
        inorder(p->right,f_out);
    }
}


void postorder(BSTNodeT *p,FILE *f_out)
{
    if (p != NULL)
    {
        postorder(p->left,f_out);
        postorder(p->right,f_out);
        fprintf(f_out,"%c\n", p->key);
    }
}

//delete the BST:
void delTree(BSTNodeT *root)
{
    if (root != NULL)
    {
        delTree(root->left);
        delTree(root->right);
        free(root);
    }
}


int main(int argc, char* argv[])
{

    FILE *f_in, *f_out;
    f_in=openAndCheck(argv[1], "r");  //argv[1]="inputs.txt"
    f_out=openAndCheck(argv[2], "w"); //argv[2]="output,txt"

    //count the number of operations given in the file:
    int lines=1;
    char c;
    c=fgetc(f_in);
    while(c!=EOF)
    {
        if(c=='\n') lines++;
        c=fgetc(f_in);
    }

    rewind(f_in);


    BSTNodeT *root=NULL;

    //create a random tree:
    root=insertNode(root,'C',stdout);
    insertNode(root, 'A',stdout);
    insertNode(root, 'B',stdout);
    insertNode(root, 'G',stdout);
    insertNode(root, 'F',stdout);
    insertNode(root, 'M',stdout);
    insertNode(root, 'E',stdout);

    //postorder(root);




    char operation[3];
    for(int i = 0; i < lines; i++)

    {

        fscanf( f_in,"%s", operation );


        switch(operation[0])
        {
        case 'i':

            insertNode(root, operation[1],f_out);
            break;


        case 'd':

            delNode(root,operation[1],f_out);
            break;


        case 'f':

            if(find(root, operation[1]) != NULL)
                fprintf(f_out,"\nThe node %c was found\n" , operation[1]);

            else
                fprintf(f_out,"\nThe node %c was not found\n" , operation [1]);
             fprintf(f_out,"\n");


            break;


        case 't':

            if(operation[1] == 'p')
            {
                fprintf(f_out,"Preorder traversal is:\n");
                preorder(root,f_out);
                fprintf(f_out,"\n");
            }

            else if (operation[1] == 'P')
            {
                fprintf(f_out,"Postorder traversal is:\n");
                postorder(root,f_out);
                fprintf(f_out,"\n");
            }

            else if (operation[1] == 'i')
            {
                fprintf(f_out,"Inorder traversal is:\n");
                inorder(root,f_out);
                fprintf(f_out,"\n");
            }

            else
                fprintf(f_out,"\nThe operation is not valid\n");

            break;

        case 'g':

            if (operation[1] == 'm')
            {
                fprintf(f_out,"The minimum is: %c",findMin(root)->key);
                fprintf(f_out,"\n");
            }

            else if (operation[1] == 'M')
            {
                fprintf(f_out,"The maximum is: %c",findMax(root)->key);
                fprintf(f_out,"\n");
            }

            else
                fprintf(f_out,"\nThe operation is not valid\n");

            fprintf(f_out,"\n");

            break;


        default:
            fprintf(f_out,"\nThe operation %c is not valid\n",operation[0]);

        }

    }

    //close all the files
    fclose(f_out);
    fclose(f_in);

    //delete the tree:
    delTree(root);

    return 0;
}
