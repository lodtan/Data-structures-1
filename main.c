#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"

char marque[MAX_prod], magasin[MAX_magasin], rayon[MAX_rayon], rayon2[MAX_rayon], rayon3[MAX_rayon], produit[MAX_prod], rayon4[MAX_rayon];
float prix, prix_min, prix_max;
char c, qualite;
int quantite, choix, sortir=0, reee=-1;
T_Rayon *res ;

int main()
{

    while (sortir==0)
    {
        printf("\t \t *****Magasin*****\n\n");
        printf("\n1.  Créer un magasin \n2.  Ajouter un rayon au magasin \n3.  Ajouter un produit dans un rayon \n4.  Afficher les rayons du magasin \n5.  Afficher les produits d'un rayon \n6.  Supprimer un produit \n7.  Supprimer un rayon \n8.  Rechercher un produit par prix \n9.  Quitter\n\n\n ");
        scanf("%d", &choix);
        switch(choix)
        {
            case 1 :
                //création magasin
                printf("\nEntrez le nom du magasin : ");
                scanf("%s", magasin);
                T_Magasin *mag = creerMagasin(magasin);
                printf("\n\n");
                break;

            case 2 :
                //création rayon
                printf("\nEntrez le nom du rayon : ");
                scanf("%s", rayon);

                T_Rayon *ray = creerRayon(rayon);
                reee = ajouterRayon(mag,ray);
                if (reee==1)
                    printf("Rayon ajoute\n\n");
                else
                    printf("\nProbleme, rayon non ajoute\n\n");
                break;

            case 3 :
                printf("Dans quel rayon voulez-vous mettre le produit ?");
                scanf("%s", rayon2);
                T_Rayon *ray2 = rechercheRayon(mag, rayon2);
                if (ray2==NULL)
                {
                    printf("\nLe rayon est inexistant");
                }
                else{
                // création du produit
                printf("\n\n\tEntrez la marque du produit : ");
                scanf("%s", marque);
                printf("\n\tEntrez le prix du produit : ");
                scanf("%f", &prix);
                printf("\n\tEntrez la qualite (A, B ou C) du produit : ");
                while((c = getchar()) != EOF && c != '\n');
                scanf("%c", &qualite);
                printf("\n\tEntrez la quantite du produit : ");
                scanf("%d", &quantite);
                T_Produit *prd = creerProduit(marque, prix, qualite, quantite);
                printf("\n %s %f %c %d", prd->marque, prd->prix, prd->qualite, prd->quantite_en_stock);
                ajouterProduit(ray2, prd);
                }
                break;

            case 4 :
                afficherMagasin(mag);
                printf("\n \tMagasin affiche\n");
                break;

            case 5 :
                printf("\tQuel rayon voulez-vous afficher\n ?");
                scanf("%s", rayon3);
                res = rechercheRayon(mag, rayon3);
                if (res !=NULL)
                {
                    afficherRayon(res);
                    printf("\nRayon affiché");
                }
                else
                {
                    printf("\nRayon non affiche");
                }
                break;

            case 6 :
                printf("Quel rayon ?\n");
                scanf("%s",rayon4);
                printf("Quel produit voulez-vous supprimer\n ?");
                scanf("%s", produit);
                T_Rayon *rRayon = rechercheRayon(mag, rayon4);
                supprimerProduit(rRayon, produit);
                break;

            case 7 :
                printf("Quel rayon voulez-vous supprimer\n ?");
                scanf("%s", rayon4);
                supprimerRayon(mag,rayon4);
                break;

            case 8 :
                printf("Donnez le prix minimum :");
                scanf("%f", &prix_min);
                printf("Donnez le prix maximum :");
                scanf("%f", &prix_max);
                rechercheProduit(mag, prix_min, prix_max);
                printf("\n");
                break;

            case 9 :
                sortir = 1 ;
                break ;

            default :
                sortir =1 ;
                break ;
        }

    }

    return 0;
}
