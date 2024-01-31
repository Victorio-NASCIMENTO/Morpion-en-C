/*
Nom du projet : Jeu de morpion deux joueurs, cases nomées comme dans Excel
Auteur : Victorio NASCIMENTO
Projet terminé le 01/01/2023
Problèmes : Affichage de la case jouée  ou des cases gagnantes en couleur après erreur de saisie
Bonne lecture
*/


#include <stdio.h>
#include <stdlib.h>

typedef struct Joueur Joueur;
struct Joueur
{
    char signe; // Le signe ( X ou O)
    char choix[2]; // Les cases sont representees par une lettre et un chiffre
    int victoires;  //Le nombre de victoires du joueur
};

typedef struct Jeu Jeu;
struct Jeu
{
    Joueur j1; Joueur j2;
    int joues[9][9];  //Stocke tout ce qui est joué. Sert à connaître les cases occupées.
    int tour, gagnant, nbre_tours; // gagnant prend i si le joueur i gagne, 0 quand on ne sait pas encore et 3  quand il y a égalité
    char table[4][4]; // C'est la grille de jeu
    int nbre_parties, gagnants[6]; //gagnants prend les 3 cases avec lesquelles le joueur gagne
    //C'est pour pouvoir mettre le contenu de ces cases en couleur à la fin
};

void init (Jeu *J)
{
    J->nbre_parties=0; // Normal. On est au début.
    J->j1.signe='X'; J->j2.signe='O'; J->gagnant=0; J->tour=1, J->nbre_tours=0;
    /*On doit maintenant initialiser la grille
    Première ligne : on laisse une case vide puis on met A. B et C
    Première colonne : pareil sauf que maintenant,  c'est 1, 2, 3
    Le reste est vide
    */
    J->table[0][0]=' ';
    for(int i=1; i<4; i++)
    {
        for(int j=1; j<4; j++) J->table[i][j]=' ';
    }
    J->table[0][1]='A'; J->table[0][2]='B'; J->table[0][3]='C';
    J->table[1][0]='1'; J->table[2][0]='2'; J->table[3][0]='3';
}


void show(Jeu J) //Pour afficher la grille de jeu
{
    /* Quand on est pas au premier tour, il y a eu un tour precedent
    Donc, il faut sauter beaucoup de lignes pour que l'utilisateur ne voit pas 
    la ou les précédentes grilles.*/
    
     if(J.nbre_tours!=0)   printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
     if(J.gagnant==0 || J.gagnant==3) //Si on ne connait pas encore le gagnant ou s'il y a égalité
     {
    for(int i=0; i<4; i++)
    {
        printf("|");//Pour encadrer le tableau
        for(int j=0; j<4; j++)
        {
            if(J.joues[J.nbre_tours-1][0]==J.table[0][j] && J.joues[J.nbre_tours-1][1]==J.table[i][0])
            //(Condition que verifie la derniere case  choisie)
            printf("\033[31m %c \033[0m", J.table[i][j]);
            //(Instruction pour mettre son contenu en couleur)
            else if(j==0 || i==0) 
            printf("\033[34m %c \033[0m", J.table[i][j]);
            //Instruction pour mettre la première ligne et la première colonne en couleur
            else
            printf(" %c ", J.table[i][j]);
            //Le reste est affiché en blanc-noir
        }
        printf("|\n");
    }
    }
    else //Sinon, on connaît le gagnant et on va afficher comment il gagne
    {
    for(int i=0; i<4; i++)
    {
        printf("|");
        for(int j=0; j<4; j++)
        {
            if((i==J.gagnants[0] && j==J.gagnants[1]) || (i==J.gagnants[2] && j==J.gagnants[3]) || (i==J.gagnants[4] && j==J.gagnants[5])) 
            //Conditions pour trouver les indices des cases gagnantes pour l'affichage du contenu en couleur
            printf("\033[31m %c \033[0m", J.table[i][j]);
            else if(j==0 || i==0) 
            printf("\033[34m %c \033[0m", J.table[i][j]);
            else
            printf(" %c ", J.table[i][j]);
        }
        printf("|\n");
    }
    }
    
    
}

void check(Jeu* J)  //Pour vérifier s'il y a un gagnant
 {
 //J'ai recensé les possibilités pour qu'un joueur gagne (Il y en a 8)
 // Ainsi, je les vérifie toutes pour chaque joueur et si l'un réussit, je profite pour
 //stocker les cases gagnantes
  if (J->table[1][1] == 'X' && J->table[1][2] == 'X' && J->table[1][3] == 'X') {
  J->gagnant = 1;
  J->gagnants[0] = 1; J->gagnants[1] = 1; J->gagnants[2] = 1; J->gagnants[3] = 2; J->gagnants[4] = 1; J->gagnants[5] = 3;  
}
else if (J->table[2][1] == 'X' && J->table[2][2] == 'X' && J->table[2][3] == 'X') {
  J->gagnant = 1;
  J->gagnants[0] = 2; J->gagnants[1] = 2; J->gagnants[2] = 2; J->gagnants[3] = 1; J->gagnants[4] = 2; J->gagnants[5] = 3;
}
else if (J->table[3][1] == 'X' && J->table[3][2] == 'X' && J->table[3][3] == 'X') {
  J->gagnant = 1;
  J->gagnants[0] = 3; J->gagnants[1] = 3; J->gagnants[2] = 3; J->gagnants[3] = 2; J->gagnants[4] = 3; J->gagnants[5] = 1;  
}
else if (J->table[1][1] == 'X' && J->table[2][1] == 'X' && J->table[3][1] == 'X') {
  J->gagnant = 1;
  J->gagnants[0] = 1; J->gagnants[1] = 1; J->gagnants[2] = 2; J->gagnants[3] = 1; J->gagnants[4] = 3; J->gagnants[5] = 1;
}
else if (J->table[1][2] == 'X' && J->table[2][2] == 'X' && J->table[3][2] == 'X') {
  J->gagnant = 1; 
  J->gagnants[0] = 1; J->gagnants[1] = 2; J->gagnants[2] = 2; J->gagnants[3] = 2; J->gagnants[4] = 3; J->gagnants[5] = 2;  
}
else if (J->table[1][3] == 'X' && J->table[2][3] == 'X' && J->table[3][3] == 'X') {
  J->gagnant = 1;
  J->gagnants[0] = 1; J->gagnants[1] = 3; J->gagnants[2] = 2; J->gagnants[3] = 3; J->gagnants[4] = 3; J->gagnants[5] = 3;
}
else if (J->table[1][1] == 'X' && J->table[2][2] == 'X' && J->table[3][3] == 'X') {
  J->gagnant = 1;
  J->gagnants[0] = 1; J->gagnants[1] = 1; J->gagnants[2] = 3; J->gagnants[3] = 3; J->gagnants[4] = 2; J->gagnants[5] = 2;  
}
else if (J->table[3][1] == 'X' && J->table[2][2] == 'X' && J->table[1][3] == 'X') {
  J->gagnant = 1;
  J->gagnants[0] = 3; J->gagnants[1] = 1; J->gagnants[2] = 1; J->gagnants[3] = 3; J->gagnants[4] = 2; J->gagnants[5] = 2;
}
else if (J->table[1][1] == 'O' && J->table[1][2] == 'O' && J->table[1][3] == 'O') {
  J->gagnant = 2;
  J->gagnants[0] = 1; J->gagnants[1] = 1; J->gagnants[2] = 1; J->gagnants[3] = 2; J->gagnants[4] = 1; J->gagnants[5] = 3;  
}
else if (J->table[2][1] == 'O' && J->table[2][2] == 'O' && J->table[2][3] == 'O') {
  J->gagnant = 2;
  J->gagnants[0] = 2; J->gagnants[1] = 1; J->gagnants[2] = 2; J->gagnants[3] = 2; J->gagnants[4] = 2; J->gagnants[5] = 3;
}
else if (J->table[3][1] == 'O' && J->table[3][2] == 'O' && J->table[3][3] == 'O') {
  J->gagnant = 2;
  J->gagnants[0] = 3; J->gagnants[1] = 3; J->gagnants[2] = 3; J->gagnants[3] = 2; J->gagnants[4] = 3; J->gagnants[5] = 1;  
}
else if (J->table[1][1] == 'O' && J->table[2][1] == 'O' && J->table[3][1] == 'O') {
  J->gagnant = 2;
  J->gagnants[0] = 1; J->gagnants[1] = 1; J->gagnants[2] = 2;  J->gagnants[3] = 1;  J->gagnants[4] = 3; J->gagnants[5] = 1;
}
else if (J->table[1][2] == 'O' && J->table[2][2] == 'O' && J->table[3][2] == 'O') {
  J->gagnant = 2;
  J->gagnants[0] = 1; J->gagnants[1] = 2; J->gagnants[2] = 2; J->gagnants[3] = 2; J->gagnants[4] = 3; J->gagnants[5] = 2;  
}
else if (J->table[1][3] == 'O' && J->table[2][3] == 'O' && J->table[3][3] == 'O') {
  J->gagnant = 2;
  J->gagnants[0] = 1; J->gagnants[1] = 3; J->gagnants[2] = 3; J->gagnants[3] = 3; J->gagnants[4] = 2; J->gagnants[5] = 3;
}
else if (J->table[1][1] == 'O' && J->table[2][2] == 'O' && J->table[3][3] == 'O') {
  J->gagnant = 2; 
  J->gagnants[0] = 1; J->gagnants[1] = 1; J->gagnants[2] = 3; J->gagnants[3] = 3; J->gagnants[4] = 2; J->gagnants[5] = 2;
}
else if (J->table[3][1] == 'O' && J->table[2][2] == 'O' && J->table[1][3] == 'O') {
  J->gagnant = 2;
  J->gagnants[0] = 3; J->gagnants[1] = 1; J->gagnants[2] = 1; J->gagnants[3] = 3; J->gagnants[4] = 2; J->gagnants[5] = 2;  
}
  else J->gagnant = 0;
  
  //Petit complement : La fonction gère le changement de tour
  if(J->nbre_tours%2==1) J->tour=2; 
  //(Si le nombre de tours est impaire, c'est qu'on est au tour de J1 donc, on passe à J2
  else J->tour=1;
  
}


void erreur(Jeu *J) //Pour détecter les erreurs de l'utilisateur de l'application
{
//D'abord les cases qui n'existent pas.
    while((J->j1.choix[0]!='A' && J->j1.choix[0]!='B' && J->j1.choix[0]!='C') || (J->j1.choix[1]!='1' && J->j1.choix[1]!='2' && J->j1.choix[1]!='3'))
    {
        printf("\n\033[31mMauvaise saisie. Reessayez : \033[0m");
        scanf("%s", J->j1.choix);
    }
    
    if(J->nbre_tours!=1)
    {
    while((J->j2.choix[0]!='A' && J->j2.choix[0]!='B' && J->j2.choix[0]!='C') || (J->j2.choix[1]!='1' && J->j2.choix[1]!='2' && J->j2.choix[1]!='3'))
    {
        printf("\n\033[31mMauvaise saisie. Reessayez : \033[0m");
        scanf("%s", J->j2.choix);
    }
    }
//Puis les case occupées    
    if(J->tour==1)
    {
    for(int i=0; i<J->nbre_tours-1; i++)
    {
        if(J->joues[i][0]==J->j1.choix[0] && J->joues[i][1]==J->j1.choix[1])
        {
            printf("\n\033[31mCase occupee. Reessayez : \033[0m");
            scanf("%s", J->j1.choix);
            i=-1;
        }
     }   
    }
    
    else
    {
    for(int i=0; i<J->nbre_tours-1; i++)
    {
        if(J->joues[i][0]==J->j2.choix[0] && J->joues[i][1]==J->j2.choix[1])
        {
            printf("\n\033[31mCase occupee. Reessayez : \033[0m");
            scanf("%s", J->j2.choix);
            i=-1;
        }
    }
    }
    
}


void jouer(Jeu *J, char nom[2][30]) //Pour lancer une partie.
{
    init(J); //On initialise le jeu.
    J->nbre_parties+=1; //Une partie de plus
    show(*J);//On affiche la grille
    while(J->gagnant==0)// Tant qu'on ignore le gagnant
    {
        if(J->tour==1) //Premier tour
        {
            printf("\nJouez %s : ", nom[0]); //Jouez J1 : 
            scanf("%s", J->j1.choix); 
            J->joues[J->nbre_tours][0]=J->j1.choix[0]; J->joues[J->nbre_tours][1]=J->j1.choix[1];
            //On le met dans les cases occupées
            J->nbre_tours+=1; erreur(J); 
            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4; j++)
                {
                    if(J->table[0][j]==J->j1.choix[0] && J->table[i][0]==J->j1.choix[1]) J->table[i][j]='X';
                    //On trouve les vrais indices de ma ca case choisie et on y met dpn signe
                }
            }
            //Maintenant, on vérifi3 s'il y a un gagnant puis on affiche la girlle
            check(J); show(*J); 
            if(J->nbre_tours==9 && J->gagnant==0) J->gagnant=3;
            //Si on est au 9e tour donc dernier tour et que personne n"a gagné, il y a égalité
        }
        else //On gère  J2 ici
        {
            printf("\nJouez %s : ", nom[1]);
            scanf("%s", J->j2.choix); J->joues[J->nbre_tours][0]=J->j2.choix[0]; J->joues[J->nbre_tours][1]=J->j2.choix[1];
            J->nbre_tours+=1; erreur(J);
            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4; j++)
                {
                    if(J->table[0][j]==J->j2.choix[0] && J->table[i][0]==J->j2.choix[1]) J->table[i][j]='O';
                }
            }
            check(J); show(*J);
        }
    }
    if(J->gagnant==1) 
    {
        printf("\n%s remporte la manche.", nom[0]);
        J->j1.victoires+=1;
    }
    else if (J->gagnant==2) 
    {
        printf("\n%s remporte la manche.", nom[1]);
        J->j2.victoires+=1;
    }
    else printf("\n\nAh Egalite.\n\n");
}

void scores(Jeu J, int final, char nom[2][30]) //Pour afficher le score après chaque partie
{
    printf("\n\n");
    printf("Joueur %s : %d parties gagnees.\n", nom[0], J.j1.victoires);
    printf("Joueur %s : %d parties gagnees.\n", nom[1], J.j2.victoires);
    
    if(final==1)
    {
        if(J.j1.victoires>J.j2.victoires) printf("\n\n\033[36mFelicitations %s. Vous avez gagne.\033[0m\n\n", nom[0]);
        else if(J.j2.victoires>J.j1.victoires) printf("\n\n\033[36mFelicitations %s. Vous avez gagne.\033[0m\n\n", nom[1]);
        else printf("\n\n\033[36mAh Egalite.\033[0m \n\n");
    }
}

int main()
{
    char nom[2][30]; int final=0;
    printf("\n\n\033[33mBienvenue dans le jeu de Morpion de Victorio !\033[0m\n\n");  
    printf("\nJoueur 1, entrez votre nom : ");
    scanf("%s", nom[0]);
    printf("\nJoueur 2, entrez votre nom : ");
    scanf("%s", nom[1]);
    printf("\nNoms enregistres. La partie peut commencer.\n\n");
    printf("\n\033[35mNB : Jouez en mettant l'indice de la case.\n(Exemples : A1, B2, C3)\033[0m\n\n");
    Jeu J;
    J.j1.victoires=0; J.j2.victoires=0;
    jouer(&J, nom);
     scores(J, final, nom);
     
    char reponse[3];
    while(1) 
    {
        printf("\n\n\033[32mVoulez vous jouer une autre partie ? (Oui ou Non)\033[0m\n\nDecision : ");
        scanf("%s", reponse);
        if(reponse[0] == 'o' || reponse[0] == 'O')  
        {
            printf("\nOk. Nouvelle manche.\n\n");
           jouer(&J, nom);
           scores(J, final, nom); 
        }
        else if(reponse[0] == 'n' || reponse[0] == 'N')  
        {
            printf("\nOk. Fin de partie.\n\n");
           final=1; scores(J, final, nom);
           printf("\nOk. Au revoir\n");
           break; 
        }
        else  
        {
             printf("\nVous deviez entrer Oui ou Non. Dsl, mais nous choisirons non pour vous, alors.\n");
            final=1; scores(J, final, nom);
            break;
         }   
    }
    return 0;
}
