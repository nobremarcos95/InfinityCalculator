#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//identifica se esta rodando em windows ou outro S.O.
#if defined(_WIN32) || defined(WIN32)
#define clearBuffer() fflush(stdin)
#define clearScreen() system("cls")
#else
#include <stdio_ext.h>
#define clearBuffer() __fpurge(stdin)
#define clearScreen() system("clear")
#endif

struct node
{
    char bin;
    struct node *next;
};

typedef struct node Node;
typedef struct node* List;

List* createList();
void insertNode(List* lista, char* bin, int pos);
int digitsNull(char* num, int size2);
void getBinary(char* bin, int size2);
void printList(List *lista);
void soma(List** arrLists, int arraySize, int pos1, int pos2);

int main()
{
    int quantity, size, newsize; //quantity == quantidades de numeros de entrada; size,newsize == tamanho dos numeros
    char *num;
    List **arrayLists, *list; //list eh um ponteiro para o primeiro numero na lista encadeada, arrayLists um array destes ponteiros

    clearBuffer();
    scanf("%d", &quantity);

    arrayLists = (List **) malloc(quantity*sizeof(List *));
    if (!arrayLists)
    {
        printf("Erro na alocacao da lista.\n");
        clearBuffer();
        getchar();
        return 0;
    }

    for (int i = 0; i < quantity; i++)
    {
        list = createList();
        if (!list)
        {
            printf("Erro na criacao da lista.\n");
            clearBuffer();
            getchar();
            return 0;
        }

        clearBuffer();
        scanf("%d", &size);

        num = (char *) malloc(size*sizeof(char));
        if (!num)
        {
            printf("Erro! Impossivel inserir numero binario.\n");
            clearBuffer();
            getchar();
        }
        else
        {
            getBinary(num, size);
            newsize = digitsNull(num, size);

            for (int j = 0; j <newsize; j++)
            {
                insertNode(list, num, j);
            }
            arrayLists[i] = list;
        }
    }

    if (quantity == 1)
    {
        printList(list);
    }
    else
    {
        for (int k = 1; k < quantity; k++)
        {
            soma(arrayLists, quantity, 0, k);
        }

    }

    return 0;
}

List* createList()
{
    List *lista = (List *) malloc(sizeof(List));
    if (lista != NULL)
    {
        (*lista) = NULL;
        return lista;
    }
    else
    {
        return NULL;
    }
}

void insertNode(List* lista, char* bin, int pos)
{
    Node *aux, *house;

    house = (Node *) malloc(sizeof(Node));
    if (!house)
    {
        return;
    }
    else
    {
        house->bin = bin[pos];
    }

    aux = *lista;

    if (!lista)
    {
        return;
    }

    if ((*lista) == NULL)
    {
        *lista = house;
        (*lista)->next = NULL;
    }
    else
    {
        while(aux->next != NULL)
        {
            aux = aux->next;
        }
        house->next = aux->next;
        aux->next = house;
    }
}

//Esta função "rejeita" os dígitos mais significativos que são nulos
int digitsNull(char* num, int size2)
{
    while (num[size2-1] == '0')
    {
        num[size2-1] = '\0';
        size2--;
    }
    return size2;
}

/*Esta função recebe um inteiro e pede ao usuário um número
com o tamanho predeterminado*/
void getBinary(char* bin, int size2)
{
    clearBuffer();
    scanf("%s", bin);
}

void printList(List *lista)
{
    Node *aux = (*lista);
     if(lista == NULL)
     {
         return;
     }

    while(aux != NULL)
    {
        printf("%c", aux->bin);
        aux = aux->next;
    }
}

void soma(List** arrLists, int arraySize, int pos1, int pos2)
{
    int num1, num2, intSum;
    char sumResult[1];
    int run, countSum = 0, count1, count2;
    int vaiUm = 0;
    List *sumList, *resultList;
    Node *arrCopy, *sumCopy, *auxCount;

    sumList = createList();
    if (!sumList)
    {
        return;
    }

    resultList = createList();
    if (!resultList)
    {
        return;
    }

    arrCopy = *arrLists[pos1];

    if ((*sumList) == NULL)
    {
        (*sumList) = arrCopy;
    }

    arrCopy = *arrLists[pos2];
    sumCopy = *sumList;

    count1 = 0;
    count2 = 0;

    auxCount = *arrLists[pos2];
    while (auxCount != NULL)
    {
        auxCount = auxCount->next;
        count1++;
    }

    auxCount = *sumList;
    while (auxCount != NULL)
    {
        auxCount = auxCount->next;
        count2++;
    }

    if (count1 > count2)
    {
        run = count1;
    }
    else
    {
        run = count2;
    }

    while (run > 0)
    {
        if (arrCopy == NULL)
        {
            num1 = 0;
        }
        else
        {
            num1 = (arrCopy->bin) - 'a' + '1'; //converte de char para int
        }

        if (sumCopy == NULL)
        {
            num2 = 0;
        }
        else
        {
            num2 = (sumCopy->bin) - 'a' + '1'; //converte de char para int
        }

        intSum = num1 + num2 + vaiUm;

        if (intSum == 2)
        {
            vaiUm = 1;
            sumResult[0] = '0';
            insertNode(resultList, sumResult, 0);
        }
        else if (intSum == 3)
        {
            vaiUm = 1;
            sumResult[0] = '1';
            insertNode(resultList, sumResult, 0);
        }
        else
        {
            sumResult[0] = intSum - '1' + 'a'; //converte de int para char
            insertNode(resultList, sumResult, 0);
            vaiUm = 0;
        }


        if (arrCopy != NULL)
        {
            arrCopy = arrCopy->next;
        }

        if (sumCopy != NULL)
        {
            sumCopy = sumCopy->next;
        }

        run--;
    }

    if (vaiUm == 1)
    {
        sumResult[0] = vaiUm - '1' + 'a'; //converte de int para char
        insertNode(resultList, sumResult, 0);
        vaiUm = 0;
    }

    //tamanho do numero resultante da soma
    sumCopy = (*resultList);

    *arrLists[pos1] = *resultList;
    while (sumCopy != NULL)
    {
        sumCopy = sumCopy->next;
        countSum++;
    }

    if (pos2 == (arraySize - 1))
    {
        printf("%d ", countSum);
        printList(resultList);
    }
    return;
}
