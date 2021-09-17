#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

struct Node
{
    char * word;
    int flag;
    int repetition;
    struct Node* next;

};
struct node  //yeni listemiz
{
    char * kelime;
    int adet;
    struct node* next;

};
struct  node *last,*prev,*lista = 0;
struct Word
{
    char chr;
    struct Word* next;
};
struct Node *head=0;
struct Node *iter,*temp,*list,*iter1;

void basa_ekle(struct node** head_ref, char *kelime,int new_data)
{

    struct node * new_node = (struct node*) malloc(sizeof(struct node));

    new_node->kelime  = kelime;
    new_node->adet  = new_data;

    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void araya_ekle(struct node** head_ref,char *kelime, int new_data)
{


    struct node * new_node =(struct node*) malloc(sizeof(struct node));
    struct node *prev = *head_ref;
    new_node->kelime  = kelime;
    new_node->adet  = new_data;

    while (prev->next->adet >= new_node->adet)

    {
        prev=prev->next;

    }
    new_node->next = prev->next;
    prev->next = new_node;

}


void sona_ekle(struct node** head_ref,char *kelime, int new_data)
{
    struct node * new_node = (struct node*) malloc(sizeof(struct node));

    struct node *last = *head_ref;


    new_node->kelime  = kelime;
    new_node->adet  = new_data;

    new_node->next = NULL;


    while (last->next != NULL)
    {
        last = last->next;
    }

    last->next = new_node;

}




void LinkedListOlustur ()

{

    //https://stackoverflow.com/questions/29355467/reading-words-from-file-into-dynamic-char-with-linked-lists
    FILE *file = fopen("file.txt", "r");
    struct  Node *list = 0;
    struct  Node **last = &list;
    struct Word *word = 0;
    int list_size = 0;
    int word_size = 0;
    if ( file != NULL )
    {
        int ch, inword = 0;
        while ( 1 )
        {
            ch = fgetc(file);
            if ( isspace(ch) || ch == EOF )
            {
                if ( inword )
                {
                    inword = 0;
                    char * string = (char *) malloc(word_size+1);
                    for(int i=word_size-1; i>=0; i--)
                    {
                        string[i]= word->chr;
                        struct   Word * temp = word;
                        word = word->next;
                        free(temp);
                    }
                    string[word_size] = '\0';
                    struct  Node * temp = ( struct Node *) malloc(sizeof( struct Node));
                    temp->word = string;
                    temp->next = 0;
                    *last = temp;
                    last = & temp->next;
                    word_size = 0;
                    list_size++;
                }
                if(ch == EOF)
                    break;
            }
            else
            {
                inword = 1;
                struct  Word * temp = word;
                word = (  struct Word *) malloc(sizeof( struct Word));
                word->chr = ch;
                word->next = temp;
                word_size++;
            }
        }
        fclose(file);

    }

    // tum kelimelerin flag ve repetition degerlerinin atanmasi
    for( struct Node * temp = list ; temp; temp=temp->next)
    {
        temp->flag=0;
        temp->repetition=1;
    }
    struct Node * iter = list ;//ust dongude donecek olan iteration
    struct Node * iter1 = list->next;
    struct Node * prev = list->next;
    //alt dongude donecek olan iteration
    int control=0;//for dongusune ilk girildiginde nextlerse 2. kelimeden kontrol etmeye baslayacagi icin bunu kullandim
    int max_rep = 0;
    int min_rep = 0;
    for(int i = 0; i < list_size; i++)
    {
        if(control != 0)
        {
            iter=iter->next;


        }
        control = 1;
        if(iter->flag==0)
        {
            iter1 = iter->next;
            for(int j=i+1; j<list_size; j++)
            {
                if(!strcasecmp(iter1->word,iter->word))
                {
                    iter->repetition++;
                    iter1->flag++;
                }
                iter1=iter1->next;

            }


            if(i==0)
            {
                max_rep = iter->repetition;
                min_rep = iter->repetition;

                basa_ekle(&lista,iter->word,iter->repetition);
            }

            else if(i==1)
            {
                if(iter->repetition>max_rep)
                {
                    max_rep = iter->repetition;
                    basa_ekle(&lista,iter->word,iter->repetition);
                }
                else if(iter->repetition<max_rep)
                {
                    min_rep = iter->repetition;
                    sona_ekle(&lista,iter->word,iter->repetition);
                }
            }
            else
            {
                if(iter->repetition>max_rep)
                {
                    max_rep = iter->repetition;
                    basa_ekle(&lista,iter->word,iter->repetition);
                }
                else if(iter->repetition==max_rep || (iter->repetition<max_rep && iter->repetition>min_rep))
                {
                    araya_ekle(&lista,iter->word,iter->repetition);
                }
                else if (iter->repetition==min_rep)
                {
                    sona_ekle(&lista,iter->word,iter->repetition);
                }
                else if (iter->repetition<min_rep)
                {
                    min_rep = iter->repetition;
                    sona_ekle(&lista,iter->word,iter->repetition);
                }
            }


        }
    }


    printf("\n");
    int i = 1;
    for( struct node * temp = lista ; temp; temp=temp->next)
    {

        printf("%d. ",i);
        i++;
        printf("%s:",temp->kelime);
        printf(" %d  ",temp->adet);
        printf("\n");



    }



    getchar();
}


int main()
{
    setlocale(LC_ALL,"turkish");
    LinkedListOlustur();

    return 0 ;
}
