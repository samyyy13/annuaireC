#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>

#ifdef DEBUG
#define MAX 20
#else
#define MAX 100
#endif

typedef struct
{
    char nom[40];
    char telephone[20];
    char email[100];
} contact;

contact annuaire[MAX];

void saisieContact(contact *c)
{
    printf("\n NOM : ");
    scanf("%s",c->nom);
    printf("\n TELEPHONE :");
    scanf("%s",c->telephone);
    printf("\n E-MAIL :");
    scanf("%s",c->email);
}

contact* rechercherContact(char* nom)
{
    for(int i=0; i<MAX; i++)
    {
        if (strcmp(annuaire[i].nom, nom)==0)
        {
            return &annuaire[i];
        }
    }
    return NULL;
}

void afficheContact(contact* c)
{
            printf("\n%s\t\t\t%s\t\t\t%s",c->nom,c->telephone,c->email);
}

void ajouter()
{
    bool saisieOK = false;
    // rechercher une page vide (le nom doit être vide)
    for(int i=0; i<MAX; i++)
    {
        if (strcmp(annuaire[i].nom,"")==0)
        {
            // à la 1ere  page vide on saisit le contact
            saisieContact(&annuaire[i]);
            saisieOK = true;
            break;
        }
    }

    // si pas de page vide on le signale
    if (!saisieOK)
    {
        printf("Pas de place dans l'annuaire !");
    }
}

void modifier()
{
    char nom[40];
    printf("Nom du contact à modifier : ");
    scanf("%s", nom);
    contact* c = rechercherContact(nom);
    if (c==NULL)
    {
        printf("Contact non trouvé\n");
    }
    else
    {
        saisieContact(c);
    }
}

void supprimer()
{
    char nom[40];
    printf("Nom du contact à supprimer : ");
    scanf("%s", nom);
    contact* c = rechercherContact(nom);
    if (c==NULL)
    {
        printf("Contact non trouvé\n");
    }
    else
    {
        c->nom[0]='\0'; // Marque la fin de chaine dès le début de la chaine => chaine vide
    }
}

void menuRechercher()
{
    char nom[40];
    printf("Nom du contact à afficher : ");
    scanf("%s", nom);
    contact* c = rechercherContact(nom);
    if (c==NULL)
    {
        printf("Contact non trouvé\n");
    }
    else
    {
        afficheContact(c);
    }
}

void sauverAnnuaireBloc()
{
    FILE *f;
    f=fopen("annuaire.txt","wb");
    if (f==NULL)
    {
        printf("Erreur d'ouverture fichier ! \n");
    }
    else
    {
        fwrite(annuaire,sizeof(annuaire),1,f);
    }
}


void sauverAnnuaireContacts()
{
    FILE *f;
    f=fopen("annuaire.txt","wb");
    if (f==NULL)
    {
        printf("Erreur d'ouverture fichier ! \n");
    }
    else
    {
        contact c;
        for(int i=0; i<MAX; i++)
        {
            c = annuaire[i];
            if (strcmp(annuaire[i].nom,"")!=0)
            {
                fwrite(&c,sizeof(c),1,f);
            }
        }
        printf("Données enregistrées ! \n");
    }
    fclose(f);
}

void sauverAnnuaire()
{
    FILE *f;
    f=fopen("annuaire.txt","w");
    if (f==NULL)
    {
        printf("Erreur d'ouverture fichier ! \n");
    }
    else
    {
        contact c;
        for(int i=0; i<MAX; i++)
        {
            c = annuaire[i];
            if (strcmp(annuaire[i].nom,"")!=0)
            {
                fprintf(f, "%s;%s;%s\n", c.nom, c.telephone, c.email);
            }
        }
        printf("Données enregistrées ! \n");
    }
    fclose(f);
}

void chargerAnnuaire()
{
    FILE *f;
    f=fopen("annuaire.txt","rb");
    if (f==NULL)
    {
        printf("Erreur d'ouverture fichier ! \n");
    }
    else
    {
        contact c;
        char s[sizeof(contact)];
        for(int i=0; (i<MAX) && (fscanf(f,"%s",s)>0); i++)
        {
#ifdef DEBUG
            printf("%s\n",s);
#endif // DEBUG
           // annuaire[i] = c;
        }

        printf("Données chargées ! \n");
    }
    fclose(f);
}

void chargerAnnuaireContacts()
{
    FILE *f;
    f=fopen("annuaire.txt","rb");
    if (f==NULL)
    {
        printf("Erreur d'ouverture fichier ! \n");
    }
    else
    {
        contact c;
    /*
        int i=0;

        while ((i<MAX) && (fread(&c,sizeof(c),1,f)==1))
        {
            annuaire[i] = c;
            i++;
        }
    */
        for(int i=0; (i<MAX) && (fread(&c,sizeof(c),1,f)==1); i++)
        {
            annuaire[i] = c;
        }

        printf("Données chargées ! \n");
    }
    fclose(f);
}


void afficheListe()
{
    system("cls");
    printf("\n****************** LISTE DES CONTACTS *******************\n\n ");
    printf("\nID\tNOM\t\t\tTELEPHONE\t\tE-MAIL\n");
    contact c;
    for(int i=0; i<MAX; i++)
    {
        c = annuaire[i];
        if (strcmp(annuaire[i].nom,"")!=0)
        {
            printf("\n%d\t%s\t\t\t%s\t\t\t%s",i,c.nom,c.telephone,c.email);
        }
    }
}

void afficheMenu()
{
    int choix;
    do
    {
       // system("cls"); // Effacer la console
        printf("MENU\n");
        printf("1. AJOUTER\n");
        printf("2. MODIFIER\n");
        printf("3. SUPPRIMER\n");
        printf("4. RECHERCHER\n");
        printf("5. AFFICHER LA LISTE\n");
        printf("6. QUITTER\n");
        printf("Votre choix :");
        scanf("%u",&choix);

        switch (choix)
        {
            case 1 :
                ajouter();
                break;
            case 2:
                modifier();
                break;
            case 3:
                supprimer();
                break;
            case 4:
                menuRechercher();
                break;
            case 5:
                afficheListe();
                break;
            case 6:
                sauverAnnuaire();
                printf("AU REVOIR\n");
                break;
            default:
                printf("Je n'ai pas compris votre choix\n");
                break;
        }
        getch(); // Attente de l'appui sur une touche. Est dans conio.h !
    }
    while (choix != 6);
}
int main()
{
    chargerAnnuaire();
    afficheMenu();
    return 0;
}


