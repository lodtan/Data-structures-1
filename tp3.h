#ifndef TP3_H_INCLUDED
#define TP3_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_prod 100
#define MAX_rayon 100
#define MAX_magasin 100

//Déclaration des structures

typedef struct Produit
{
    char marque[MAX_prod];
    float prix;
    char qualite;
    int quantite_en_stock;
    struct Produit *suivant;
}T_Produit;

typedef struct Rayon
{
    char nom_rayon[MAX_rayon];
    int nombre_produits;
    struct Produit *premier;
    struct Rayon *suivant;
}T_Rayon;

typedef struct Magasin
{
    char nom[MAX_magasin];
    T_Rayon *premier;
}T_Magasin;

typedef struct nProd
{
    T_Produit *produit;
    char nom_rayon[MAX_rayon];
    struct nProd *suivant;
}nProd;

//Déclaration des variables



//Prototypes des fonctions

T_Produit *creerProduit(char *marque, float prix, char qualite, int quantite);
T_Rayon *creerRayon(char *nom);
T_Magasin *creerMagasin(char *nom);
int ajouterRayon(T_Magasin *magasin, T_Rayon *rayon);
int ajouterProduit(T_Rayon *rayon, T_Produit *produit);
void afficherMagasin(T_Magasin *magasin);
void afficherRayon(T_Rayon *rayon);
int supprimerProduit(T_Rayon *rayon, char* marque_produit);
int supprimerRayon(T_Magasin *magasin, char *nom_rayon);
T_Rayon *rechercheRayon(T_Magasin *mag, char *nom);
void rechercheProduit(T_Magasin *magasin, float prix_min, float prix_max);



#endif // TP3_H_INCLUDED
