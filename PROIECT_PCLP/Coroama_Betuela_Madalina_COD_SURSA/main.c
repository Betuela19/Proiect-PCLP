#include "car.h"
#include "data.h"

int main()
{
    int op;
    do
    {
        system("cls");
        printf("\n\n\t\t\tAutentificare:\n\n");
        printf("\t1.Administrator\n");
        printf("\t2.Client\n");

        scanf("%d",&op);

        switch(op)
        {
        case 1:
            parola();
            administrator();
            getch();
            break;

        case 2:
            client();
            getch();
            break;
        default:
            printf("Optiunea aleasa nu exista!!!");
            getch();
            break;

        }
    }
    while(1);
}

