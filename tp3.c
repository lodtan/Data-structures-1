#include "tp3.h"

T_Produit *creerProduit(char *marque, float prix, char qualite, int quantite)
{
    T_Produit *prod = NULL;
    prod = malloc(sizeof(T_Produit));
    strcpy(prod->marque, marque);
    prod->prix = prix;
    prod->qualite = qualite;
    prod->quantite_en_stock = quantite;
    prod->suivant = NULL;

    return prod;
}

T_Rayon *creerRayon(char *nom)
{
    T_Rayon *r = NULL ;
    r = malloc(sizeof(T_Rayon));
    strcpy(r->nom_rayon, nom);
    r->nombre_produits = 0;
    r->premier = NULL ;
    r->suivant = NULL ;


    return r;
}

T_Magasin *creerMagasin(char *nom)
{
    T_Magasin *mag = NULL;
    mag = malloc(sizeof(T_Magasin));
    strcpy(mag->nom, nom);
    mag->premier=NULL;

    return mag;
}


int ajouterRayon (T_Magasin *magasin, T_Rayon *rayon){
  T_Rayon *pCourant, *pPrecedent = NULL;
  if(magasin == NULL){
    printf("magasin NULL");
    return 0;
  }
  if (rayon == NULL){
    printf("Rayon NULL");
      return 0;
  }
  if(magasin->premier==NULL)
  {
      magasin->premier = rayon;
      return 1;
  }
  int cmp = 1;
    pCourant = magasin->premier;
  while((pCourant !=NULL) && (cmp=strcmp(pCourant->nom_rayon, rayon->nom_rayon))<0){
        pPrecedent = pCourant;
        pCourant = pCourant->suivant;
  }
  if(cmp ==0){
    printf("Rayon deja existant");
    return 0;
  }
  else{
    rayon->suivant = pCourant;
    if(pPrecedent==NULL){
        magasin->premier = rayon;
    }
    else
        pPrecedent->suivant=rayon;
    return 1;
  }
}


int ajouterProduit(T_Rayon *rayon, T_Produit *produit){
 T_Produit *pCourant , *pPrecedent = NULL;
 int cmp = 1;
 if (rayon == NULL){
  printf("\nLe rayon est inexistant");
  return 0;
 }
    else if (produit == NULL){
        printf("\nLe produit est NULL");
        return 0;
    }
 else{
  pCourant = rayon->premier;
  while (pCourant != NULL && (cmp = strcmp(pCourant->marque,produit->marque)) != 0)
   pCourant = pCourant->suivant;
  if (cmp == 0){
   printf("\nProduit deja exsitant\n");
   return 0;
  }
  else{
      rayon->nombre_produits = rayon->nombre_produits + 1;
            pCourant = rayon->premier;
            while (pCourant != NULL && (pCourant->prix < produit->prix)){
                pPrecedent = pCourant;
                pCourant = pCourant->suivant;
            }
        produit->suivant = pCourant;
        if (pPrecedent == NULL){
            rayon->premier = produit;
            return 1;
        }
        else{
            pPrecedent->suivant = produit;
            return 1;
        }
        }
    }
}


T_Rayon *rechercheRayon(T_Magasin *mag, char *nom)
{
    T_Rayon *pointeur = mag->premier;
    int cmp = 1;
    if (mag->premier==NULL)
    {
        return NULL;
    }
    else
    {
    while (pointeur!=NULL && ((cmp= strcmp(pointeur->nom_rayon, nom) != 0)))
        {
            pointeur = pointeur->suivant;
        }
    if (cmp==0)
        return pointeur;
    else
        return NULL;
    }
    return NULL;
}


void afficherMagasin(T_Magasin *magasin)
{
    T_Rayon *pCourant= magasin->premier;
    printf("| %-20s | %-20s |\n", "Nom", "Nb de produits");
    while (pCourant!=NULL)
    {
        printf("---------------------------------------------------------------------------\n");
        printf("| %-20s | %-20d |\n", pCourant->nom_rayon, pCourant->nombre_produits );
        pCourant = pCourant->suivant;
    }
}

void afficherRayon(T_Rayon *rayon)
{
    T_Produit *pCourant = rayon->premier;
    printf("| %-20s | %-13s | %-8s | %-10s |\n","Marque", "Prix","Qualite","Quantite en stock");
    while (pCourant!=NULL)
    {
        printf("---------------------------------------------------------------------------\n");
        printf("| %-20s | %-13f | %-8c | %-10d |\n", pCourant->marque, pCourant->prix, pCourant->qualite, pCourant->quantite_en_stock );
        pCourant = pCourant->suivant ;
    }
}



int supprimerProduit(T_Rayon *rayon, char* marque_produit)
{
    int cmp=1;
    T_Produit *pCourant= rayon->premier, *pPrecedent = NULL, *temp=NULL;

    if (pCourant==NULL)
    {
        printf("Pas de produit\n");
        return 0;
    }

    if (pPrecedent==NULL && ((cmp=strcmp(pCourant->marque, marque_produit))==0 ))
    {
        temp = pCourant;
        if (pCourant->suivant == NULL)
        {
            rayon->premier = NULL;
        }
        else
            rayon->premier = pCourant->suivant;
        free(temp);
        rayon->nombre_produits--;

        return 1;
    }
    else{
    while ((pCourant!=NULL) && ((cmp=strcmp(pCourant->marque, marque_produit))!=0))
    {
        pPrecedent = pCourant;
        pCourant = pCourant ->suivant;
    }

    if (cmp==0)
    {
        if (pCourant->suivant==NULL)
        {
           pPrecedent->suivant = NULL;
           free(pCourant);
           rayon->nombre_produits--;
           return 1;
        }
        else
        {
            pPrecedent->suivant = pCourant->suivant;
            free(pCourant);
            rayon->nombre_produits--;
            return 1;
        }
        }
    }
    return 0;
}

int supprimerRayon(T_Magasin *magasin, char *nom_rayon)
{
    int cmp=1;
    T_Rayon *pCourant= magasin->premier, *pPrecedent = NULL, *temp=NULL;



    if (pCourant==NULL)
    {
        printf("Pas de rayon");
        return 0;
    }

    while ((pCourant!=NULL) && ((cmp=strcmp(pCourant->nom_rayon, nom_rayon))!=0))
    {
        pPrecedent = pCourant;
        pCourant = pCourant ->suivant;
    }


    while(pCourant->premier!=NULL)
    {
        supprimerProduit(pCourant,pCourant->premier->marque);
    }

    if (pPrecedent==NULL && ((cmp=strcmp(pCourant->nom_rayon, nom_rayon))==0 ))
    {
        //free(pCourant);
        temp = pCourant;
        if (pCourant->suivant == NULL)
        {
            magasin->premier = NULL;
        }
        else
            magasin->premier = pCourant->suivant;
        free(temp);

        return 1;
    }
    else{
    while ((pCourant!=NULL) && ((cmp=strcmp(pCourant->nom_rayon, nom_rayon))!=0))
    {
        pPrecedent = pCourant;
        pCourant = pCourant ->suivant;
    }

    if (cmp==0)
    {
        if (pCourant->suivant==NULL)
        {
           pPrecedent->suivant = NULL;
           free(pCourant);
           return 1;
        }
        else
        {
            pPrecedent->suivant = pCourant->suivant;
            free(pCourant);
            return 1;
        }
        }
    }
    return 0;
}


void rechercheProduit(T_Magasin *magasin, float prix_min, float prix_max){
    T_Rayon *rCourant = magasin->premier;
    T_Produit *pCourant = rCourant->premier;
    nProd *Tri=malloc(sizeof(nProd)), *pTri=Tri, *pPrecedent=NULL;
    Tri=NULL;

    while (rCourant!=NULL){
            pCourant = rCourant->premier;
        while (pCourant!=NULL){
                nProd *new_prod=malloc(sizeof(nProd));
                strcpy(new_prod->nom_rayon, rCourant->nom_rayon);
                new_prod->produit=pCourant;
                pTri=Tri;
                if (Tri==NULL){
                    Tri=new_prod;
                    Tri->suivant=NULL;
                    pTri = Tri;
                }
                else {
                    while(pTri!=NULL && pTri->produit->prix < new_prod->produit->prix ){
                        pPrecedent = pTri;
                        pTri = pTri->suivant;
                    }
                new_prod->suivant = pTri;
                if (pPrecedent == NULL){
                    pTri->suivant = new_prod;
                    //printf("| %-20s | %-13f | %-8c | %-10d | %-20s |\n",pTri->produit->marque, pTri->produit->prix, pTri->produit->qualite, pTri->produit->quantite_en_stock, pTri->nom_rayon);

                }
                else{
                    pPrecedent->suivant = new_prod;
                    //printf("| %-20s | %-13f | %-8c | %-10d | %-20s |\n",pTri->produit->marque, pTri->produit->prix, pTri->produit->qualite, pTri->produit->quantite_en_stock, pTri->nom_rayon);
                    //free(new_prod);
                }
            }
            pCourant = pCourant->suivant;
    }
    rCourant = rCourant->suivant;
}
pTri = Tri;
pPrecedent=NULL;
printf("| %-20s | %-10s | %-10s | %-20s | %-20s |\n","Marque", "Prix", "Qualite", "Quantite en stock", "Rayon");
printf("\n----------------------------------------------------------------\n");
    while(pTri){
            if(pTri->produit->prix>=prix_min && pTri->produit->prix<=prix_max){
            printf("| %-20s | %-13f | %-8c | %-10d | %-20s |\n",pTri->produit->marque, pTri->produit->prix, pTri->produit->qualite, pTri->produit->quantite_en_stock, pTri->nom_rayon);
            }
            pPrecedent = pTri;
            pTri = pTri->suivant;
            free(pPrecedent);
    }
}

