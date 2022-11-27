#include "car.h"
#include "data.h"

struct masina
{
    int id;
    char *nume;
    char *carburant;
    char *culoare;
    int locuri;
    int km;
    int pret;
    struct masina *urm;
};
typedef struct masina Masina;

struct lista
{
    int nr;
    MASINA primul;
    MASINA ultimul;
};
typedef struct lista Lista;


LISTA newl()
{
    LISTA header = (LISTA) malloc( sizeof(Lista) );
    if(header != NULL)
    {
        header->nr = 0;
        header->primul = NULL;
        header->ultimul = NULL;
    }
    return header;
}

static MASINA creareMasina(int idu, char *numec, char *combustibil, char *culoarem, int nr_locuri, int kmp, int pretm, MASINA urmator)
{
    MASINA w= (MASINA) malloc( sizeof(Masina) );
    if(w!=NULL)
    {

        w->id = idu;
        w->nume = numec;
        w->carburant = combustibil;
        w->culoare = culoarem;
        w->locuri = nr_locuri;
        w->km = kmp;
        w->pret= pretm;
        w->urm  = urmator;
    }
    return w;
}

LISTA ins_la_urma(LISTA l, int idu, char *numec, char *combustibil, char *culoarem, int nr_locuri,int km, int pretm)
{
    assert(l!=NULL);

    if(isFull(l))
        return l;
    MASINA w = creareMasina(idu, numec, combustibil, culoarem, nr_locuri,km, pretm, NULL);
    if(w!=NULL)
    {
        if(isEmptyl(l))
        {
            l->primul = l->ultimul = w;
        }
        else
        {
            l->ultimul->urm = w;
            l->ultimul = w;
        }
        l->nr++;
    }
    return l;
}


int nrMasini(LISTA l)
{
    assert(l!=NULL);
    return l->nr;
}
bool isEmptyl(LISTA l)
{
    return nrMasini(l)==0;
}
bool isFull(LISTA l)
{
    return FALS;
}

char *toStringl(LISTA l,char *s)
{
    char buf[5000];
    sprintf(s, "\t\t\t\t\t\t--Lista Masini-- \n ");

    assert(l!=NULL);

    if(isEmptyl(l))
    {
        strcat(s, "vida ");
    }
    else
    {
        MASINA p;
        for(p=l->primul; p!=NULL; p = p->urm)
        {
            sprintf(buf,  "\nID: %-4d \tNume: %-20s \tCarburant: %-15s \tCuloare: %-15s  \tNumar locuri: %-4d \tKm/h: %-4d \tPret(RON)/zi: %-4d", p->id, p->nume, p->carburant, p->culoare,p->locuri, p->km, p->pret );
            strcat(s, buf);
        }
    }
    return s;
}


void destroyl(LISTA l)
{
    MASINA e, p;
    if(l==NULL || l->primul==NULL)
        return;

    e= l->primul;
    while(e!=NULL)
    {
        p=e;
        e = e->urm;
        free(p);
    }
}


LISTA adauga_masina ( LISTA l)
{
    assert(l!=NULL);
    char zona[1000], *nume, *culoare, *carburant;
    int id, nrlocuri, km, pret;

    fflush(stdin);
    printf("Numele masinii este: ");
    gets(zona);

    nume = calloc(strlen(zona)+1, sizeof(char));
    strcpy(nume, zona);

    fflush(stdin);
    printf("Carburantul este: ");
    gets(zona);
    carburant = calloc(strlen(zona)+1, sizeof(char));
    strcpy(carburant, zona);

    fflush(stdin);
    printf("Culoarea este: ");
    gets(zona);
    culoare = calloc(strlen(zona)+1, sizeof(char));
    strcpy(culoare, zona);

    printf("Numarul de locuri: ");
    scanf("%d", &nrlocuri);

    printf("Maxim km/h: ");
    scanf("%d", &km);

    printf("Pret autovechicul/zi: ");
    scanf("%d", &pret);

    id=l->nr+1;

    ins_la_urma(l,id,nume, carburant, culoare, nrlocuri,km, pret);
    adaugafisier(l);
    printf("\nMasina a fost inregistrata!\n");

    return l;
}

void adaugafisier(LISTA l)
{
    FILE *fp=fopen("masini.txt","wt");
    assert(fp!=NULL);
    fprintf(fp,"%d\n",l->nr);
    MASINA p;
    for(p=l->primul; p!=NULL; p=p->urm)
    {
        fprintf(fp, "%d,", p->id);
        fprintf(fp, "%s,", p->nume);
        fprintf(fp, "%s,", p->carburant);
        fprintf(fp, "%s,", p->culoare);
        fprintf(fp, "%d,", p->locuri);
        fprintf(fp, "%d,", p->km);
        fprintf(fp, "%d\n",p->pret);

    }
    fclose(fp);
}

LISTA citirefisier()
{
    LISTA l=newl();
    assert(l!=NULL);

    FILE *f = fopen("masini.txt", "r");
    if(f==NULL)
        printf("Eroare la deschiderea fisierului");
    else
    {
        char zona[100], *buff, *nume, *culoare, *carburant;
        int id, nrlocuri, km, pret,nr;

        fscanf(f, "%d", &nr);
        char c[5];
        fgets(c,5,f);//Trece pe urmatorul rand
        for(int i=0; i<nr; i++)
        {
            fflush(stdin);
            fgets(zona,100,f);

            buff=strtok(zona, ",");
            id=atoi(buff);

            buff=strtok(NULL, ",");
            nume=calloc(strlen(buff)+1, sizeof(char));
            assert(nume!=NULL);
            strcpy(nume, buff);

            buff=strtok(NULL, ",");
            carburant=calloc(strlen(buff)+1, sizeof(char));
            assert(carburant!=NULL);
            strcpy(carburant, buff);

            buff=strtok(NULL, ",");
            culoare=calloc(strlen(buff)+1, sizeof(char));
            assert(culoare!=NULL);
            strcpy(culoare, buff);

            buff=strtok(NULL, ",");
            nrlocuri=atoi(buff);

            buff=strtok(NULL, ",");
            km=atoi(buff);

            buff=strtok(NULL, ",");
            pret=atoi(buff);

            ins_la_urma(l,id,nume,carburant,culoare,nrlocuri,km,pret);

        }
    }
    return l;
}

LISTA sterge_masina(LISTA l)
{
    printf("\nDati ID-ul masinii pe care doriti sa o stergeti:");
    int ID;
    do{scanf("%d",&ID);
    }while(ID<1 || ID>l->nr);
    MASINA p;
    MASINA j;
    int ok=0;
    for(p=l->primul;p!=NULL;p=p->urm)
    {
        if(ok==1)
        {
            p->id=p->id -1;
        }
        else
        {
            if(p->id==ID)
            {
                ok=1;
                if(p==l->primul)
                {
                    remove_primul(l);
                }
                else
                {
                    if(p==l->ultimul)
                    {
                        remove_ultimul(l);
                    }
                    else
                    {
                        for(j=l->primul;j->urm!=p;j=j->urm);
                        j->urm=p->urm;
                        free(p);
                         l->nr--;
                    }
                }
            }
        }
    }
    adaugafisier(l);
    destroyl(l);
    return l;
}

LISTA remove_primul(LISTA l)
{
    assert(l!=NULL);

    if(l->primul!=NULL)
    {
        l->nr--;
        MASINA p = l->primul->urm;
        free(l->primul);
        l->primul = p;
        if(l->primul == NULL )
            l->primul=NULL;
    }
    return l;
}

LISTA remove_ultimul(LISTA l)
{
    assert(l!=NULL);
    if(isEmptyl(l))
        return l;
    l->nr--;
    if(l->primul == l->ultimul)
    {
        free(l->primul);
        l->primul = l->ultimul = NULL;
    }
    else
    {
        MASINA p;
        for(p=l->primul; p->urm!=l->ultimul; p = p->urm) ;
        free(l->ultimul );
        p->urm = NULL;
        l->ultimul = p;
    }
    return l;
}

void administrator()
{
    LISTA l = newl();
    char zona[5000];
    int c;
    do
    {
        system("cls");
        printf("1.Vizualizeaza lista de masini\n");
        printf("2.Adauga masina\n");
        printf("3.Sterge masina\n");
        printf("4.Revina la meniul anterior");

        printf("\n\nCe optiune doriti sa selectati?\n");

        scanf("%d", &c);
        switch(c)
        {
        case 1:
            l=citirefisier();
            printf("%s", toStringl(l, zona));
            getch();
            break;

        case 2:
            l=adauga_masina(l);
            getch();
            break;

        case 3:
            printf("%s", toStringl(l, zona));
            printf("\n");
            l=sterge_masina(l);
            getch();
            break;

        case 4:
            destroyl(l);
            return;
        default:
            printf("\nOptiune invalida");
            getch();
            break;
        }
    }
    while(1);
}

void client()
{
    LISTA l=newl();
    MASINA m;
    char zona[5000],raspuns,x[200];

    printf("************************************** BINE ATI VENIT PE SITE-UL NOSTRU ***********************************************\n\n");
    printf("Mai jos este afisata o lista cu masinile disponibile pentru inchiriere:\n\n");
    l=citirefisier();
    printf("%s", toStringl(l, zona));
    do{printf("\n\n\n\nDoriti sa inchiriati o masina din lista de mai sus?[D-DA // N-NU]\n");
    scanf("%s",&raspuns);
    if(raspuns=='D' || raspuns=='d')
    {
        printf("Va rugam tastati numele masinii pe care doriti sa o inchiriati:");
            fflush(stdin);
            gets(x);
        for(m=l->primul ; m!=NULL ; m=m->urm)
        {

            if(strcmp(x,m->nume) == 0)
            {
                printf("Masina se afla in lista");
                printf("\n\nVa rugam introduceti datele dumeavoastra:");
                preluare_date_client();
                printf("\n\nAti ales:\n%s\nCarburant: %s\nCuloare: %s\nNumar locuri: %d\nMaxim km/h: %d\nPret(RON)/zi: %d",x,m->carburant,m->culoare,m->locuri,m->km,m->pret);
                confirmare();
            }
        }
    }
    else if(raspuns=='N' || raspuns=='n')
    {
        printf("\nVA MULTUMIM CA ATI VIZITAT SITE-UL NOSTRU!!!\n");
        exit(0);
    }
    else
        printf("Va rugam alegeti una din cele doua optiuni!!!");
    }while(1);
}

void preluare_date_client()
{
    char nume[30],prenume[40],adresa[100];

    fflush(stdin);
    printf("\nIntroduceti numele: ");
    gets(nume);

    fflush(stdin);
    printf("Introduceti prenumele: ");
    gets(prenume);


    fflush(stdin);
    printf("Introduceti adresa de unde doriti sa preluati autoturismul: ");
    gets(adresa);

    numar_tel();
    printf("\nDatele dumneavoastra au fost inregistrate cu succes.");

}

void numar_tel()
{
    char tel[15];

    while(strlen(tel) != 10)
    {
        printf("Introduceti numarul de telefon: ");
        scanf("%s",&tel);
        if(strlen(tel) != 10)
        {
            printf("Numar de telefon invalid!\n");
        }
        else
            break;
    }

}

void confirmare()
{
    char alegere;
    printf("\n\nConfirmati alegerea?(D-DA//N-NU)");
    scanf("%s",&alegere);
    if(alegere=='d' || alegere=='D')
        {printf("\nCEREREA DUMNEAVOASTRA A FOST INREGISTRATA!!!\nVA MULTUMIM!\n");
        exit(0);
        }
    if(alegere=='n' || alegere=='N')
        {printf("\nCEREREA DUMNEAVOASTRA VA FI ANULATA!!!\nVA MULTUMIM PENTRU CA ATI VIZITAT SITE-UL NOSTRU\n");
        exit(0);
        }
}

void parola()
{
    int pass, x=10;

	while (x!=0)
	{
	printf("\nIntroduceti parola: ");
	scanf("%d",&pass);

	if (pass==1234)
	{
		printf("Parola corecta.  ACCES PERMIS ");
		getch();
		x=0;
    }
    else
    {
       printf("Parola gresita, reincercati");
	}
	printf("\n");
   }

}
