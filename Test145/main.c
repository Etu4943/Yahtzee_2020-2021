//
//  main.c
//  Yatsee
//
//  Created by Clément Potier on 09/12/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>
void afficherMenu(int*);
void des(int*);
void des2(int *,int);
void encodage(char *,int*, int *, int *,int*,int*);
void encodageChoix(char*,int*,int*,int*,int*,int*);
void resultat(int*,int*,int*,int*,int*);
void incrementation(int *,int *,int,int*,int*);
int brelan(int*,int*);
int carre(int*,int*);
int full(int*,int*);
int petite_Suite(int*,int*);
int grande_Suite(int*,int*);
int yahtsee(int*,int*);
void delay(int);
int contrat_421(int*);
int main(int argc, const char * argv[]) {
    // insert code here...
    FILE* fichier = NULL;                        /// on initialiser un fichier
    fichier = fopen("yahtzee.txt", "r+");        /// ouverture du fichier en mode "r+" qui permet de lire et écrire dans ce fichier
    if(fichier != NULL){                         /// si l'ouverture du fichier s'efectue sans encombre
    int i,j,t,k;
    char rep='a';
    char tab[5];
        int count=0;
        char countrep='a';
    int lance[5];
    int tableau[14]={0};
        for(i=0;i<14;i++){
            fscanf(fichier,"%d",&tableau[i]);     /// On va aller récupérer chaque valeur du fichier et ainsi remplir notre tableau des valeur déja existante.
            if(tableau[i]<=-1){                   /// On va vérifier qu'il y ai d'autre valeur que les valeurs initiales
                count ++;
//                printf("%d\n", tableau[i]);
//                printf("count : %d\n", count);
            }
            
        }
        
        if(count!=0 && count !=14){              /// Si "count" vaut 13, cela signifie que rien n'est joué. Si il vaut 0, cela signifie que tout est joué, que la partie est finie. En dehors de ces 2 cas, une partie est en cours.
            while(countrep != 'r' && countrep != 'R' && countrep != 'C' && countrep != 'c'){
            system("clear");
            printf("\n\tUne partie est en cours... \n\tvoulez-vous continuer la partie en cours ou recommencer ?");
            fflush(stdin);
            scanf("%c", &countrep);
        
                    switch(countrep){                         /// On récupere le choix de l'utilisateur dans un switch.
                        case 'c':
                        case 'C':                            ///Le choix de continuer va fermer le fichier pour le réouvrir en mode "w+" qui ne permet pas de lire, mais de réécrire sur d'autres valeur déja inscrite.
                            fclose(fichier);
                            fopen("yahtzee.txt","w+");
                            break;
                        case 'R':
                        case 'r':                             ///Le choix de recommencer va fermer le fichier et le réouvrir en mode "w+" afin de réécrire à l'aide d'une boucle toutes les valeurs et les initialiser à -1. Donc recommencer le jeu.
                            fclose(fichier);
                            fopen("yahtzee.txt","w+");
                            for(k=0;k<14;k++){
                                tableau[k]=-1;
                                }
                            break;
                        default:
                            break;
                    }
        }
    }
        if(count == 14 || count == 0){           /// Si la partie est finie (0) ou que la partie n'a pas encore commencée(13), le jeu se lance automatiquement. Il fermer le fichier pour le réouvrir en mode w+ et initialise toutes les contrats à -1 au cas où ils seraient tous remplis.
            fclose(fichier);
            fopen("yahtzee.txt","w+");
            for(k=0;k<14;k++){
                tableau[k]=-1;
            }
        }
        
        

    int essais[2];
    essais[0]=2;
    int perdu[2];
    perdu[0]=0;
    int verif[2];
    int sommeFinJeu=0;
    int sommeResultatFinJeu = 0;
    int compteurBonus = 0;
    verif[0]=0;
    //int cmp1=0,cmp2=0;
    des(lance);                                  /// Le jeu commence par appeler la fonction "des" qui envoie en argument le tableau de int (lancés) déclaré en ligne 37.
    system("clear");
    do{                                                                      // Le jeu repose sur cette boucle do..while qui ne se termine qu'une fois qu'on choisi "s" (perssonel, util pour le debogage) ou bien qu'il n'y a plus de contrats à remplir
        
        sommeFinJeu=0;                           ///Tout d'abord on initialiser un compteur "sommeFinJeu" à 0 et qui prendre +1 à chaque contrat détécté comme rempli lors de la boucle d'après.
        for(i=0;i<14;i++){                       /// On fait de cette manière et pas seulement à chaque tour de la boucle while, car si on ferme et qu'on relance le jeu par après, le compteur recommence à 0 même si on a rempli des contrats.
            if(tableau[i]>-1){
                sommeFinJeu++;
            }
        }
        if(sommeFinJeu==14){                    ///On ajoute la condition de terminer le jeu si ce compteur vaut 13, soit si tout les contrats sont remplis.
            for(i=0;i<6;i++){
                compteurBonus += tableau[i];
            }
            if(compteurBonus >= 63){
                
                for(j=0;j<13;j++){
                sommeResultatFinJeu += tableau[j];     /// On calcul la somme obtenu pour la donner à l'utilisateur. Elle est recalculé entièrement à ce moment là
                }
                
                sommeResultatFinJeu += 35;
            
            }
            else{
                for(j=0;j<14;j++){
                sommeResultatFinJeu += tableau[j];     /// On calcul la somme obtenu pour la donner à l'utilisateur. Elle est recalculé entièrement à ce moment là
                }
            }
            printf("\n\n La partie est fini, vous avez obetnu : %d points.\n\n",sommeResultatFinJeu);      ///On affiche un message avec le résultats obtenu et on ferme le programme en retournant 5.
            return 5;
        }
        afficherMenu(tableau);                 /// Tant qu'on a pas remlpi tout les contrats, on commence par afficher le menu des contrats. On envoie le tableau des valeur en arguments.
        for(i=0;i<5;i++){                     /// Ceci est un algorithme permettant d'animer un peu le lancer des dés. 
            for(t=0;t<2;t++){
                printf("/");
                printf("\b");
                delay(100);
                printf("\\");
                printf("\b");
                delay(100);
                printf("-");
                printf("\b");
                delay(100);
            }
        printf("%d ", lance[i]);            /// Après chaque animation, on affiche le résultat du dé.
        delay(500);
        }
        encodage(tab,essais,tableau,lance,perdu,verif);   /// Ensuite on va chercher la fonction "encodage" qui est un petit menu me demandant quoi faire
        rep = tab[0];
        encodageChoix(tab,lance,tableau,essais,perdu,verif); /// Ici, on s'occupe de traiter la réponse enregistrée
        essais[0] --;
        printf("\n\n nbr essais = %d \n\n",essais[0]);
        fflush(stdin);
        system("clear");
        
    }while(rep!='s' && perdu[0]==0);                                          // Concrétement, le jeu s'arrete ici, tout se passe à l'intérieur.
        
        
        for(i=0;i<14;i++){                                                    ///Quand le jeu s'arrète, on refait un tour des contrat pour les inscrire dans le fichier externe.
            fprintf(fichier,"%i",tableau[i]);

            fputc('\n', fichier);
        }
        fclose(fichier);                                                    /// On termine par fermer le fichier
        
        
        
    return 0;                                                  /// Le programme s'arrète et retourne 0.
    }
    
    
    else{
        printf("Imposssible d'ouvrir le fichier yahtzee.txt");            /// C'est la suite de la vérification d'ouverture du fichier. Dans le cas où il y a eu un problème.
        return 255;
    }
    
}

void delay(int number_of_seconds)                         ///Fonction particulière à Macos permettant un "_SLEEP"
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
  
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

void afficherMenu(int *(tableau)){
    int total=0, totalgeneral=-1,somme=0,somme2=0,bonus=-1;
    int i;
    for(i=0;i<6;i++){                  ///Calcul à chaque tour le total des 6 premiers contats.
        if(tableau[i]>=0){
            somme += tableau[i];
        }
    }
    total = somme;
    for(i=0;i<14;i++){                 /// Calcul à chaque fois également la somme de tout les contrat pour afficher le total général
        if(tableau[i]>=0){
            somme2 += tableau[i];
        }
    }
    if(total>=63){                     /// Utilise le premier calcul de somme pour vérifier si le premier total est plus grand ou égal à 63 et dans ce cas ajouter  35 à bonus
        bonus = 35;
    }
    totalgeneral = somme2+bonus;
    if(tableau[0]<0){                                /// Comme tout est initialisé à -1, le -1 signifie "vide", et dans ce cas on affiche "-". Mais le contrat peut valoir 0 !.
    printf("1.  AS              :       -\n");
    }else{
    printf("1.  AS              :       %d\n", tableau[0]);
    }
    if(tableau[1]<0){
    printf("2.  Deux            :       -\n");

    }else{
    printf("2.  Deux            :       %d\n", tableau[1]);
    }
    if(tableau[2]<0){
    printf("3.  TROIS           :       -\n");
    }else{
    printf("3.  TROIS           :       %d\n", tableau[2]);
    }
    if(tableau[3]<0){
    printf("4.  Quatre          :       -\n");
    }else{
    printf("4.  Quatre          :       %d\n", tableau[3]);
    }
    if(tableau[4]<0){
    printf("5.  CINQ            :       -\n");
    }else{
    printf("5.  CINQ            :       %d\n", tableau[4]);
    }
    if(tableau[5]<0){
    printf("6.  SIX             :       -\n");
    }else{
    printf("6.  SIX             :       %d\n", tableau[5]);
    }
    if(total==0){
    printf("    TOTAL           :       -\n");
    }else{
    printf("    TOTAL           :       %d\n", total);
    }
    if(bonus<0){
    printf("    BONUS           :       -\n");
    }else{
    printf("    BONUS           :       %d\n", bonus);
    }
    if(tableau[6]<0){
    printf("7.  BRELAN          :       -\n");
    }else{
    printf("7.  BRELAN          :       %d\n", tableau[6]);
    }
    if(tableau[7]<0){
    printf("8.  CARRE           :       -\n");
    }else{
    printf("8.  CARRE           :       %d\n", tableau[7]);
    }
    if(tableau[8]<0){
    printf("9.  FULL HOUSE      :       -\n");
    }else{
    printf("9.  FULL HOUSE      :       %d\n", tableau[8]);
    }
    if(tableau[9]<0){
    printf("10. PETITE SUITE    :       -\n");
    }else{
    printf("10. PETITE SUITE    :       %d\n", tableau[9]);
    }
    if(tableau[10]<0){
    printf("11. GRANDE SUITE    :       -\n");
    }else{
    printf("11. GRANDE SUITE    :       %d\n", tableau[10]);
    }
    if(tableau[11]<0){
    printf("12. YAHTSEE         :       -\n");
    }else{
    printf("12. YAHTSEE         :       %d\n", tableau[11]);
    }
    if(tableau[12]<0){
    printf("13. CHANCE          :       -\n");
    }else{
    printf("13. CHANCE          :       %d\n", tableau[12]);
    }
    if(tableau[13]<0){
    printf("14. 421             :       -\n");
    }else{
    printf("14. 421             :       %d\n", tableau[13]);
    }
    if(totalgeneral<0){
    printf("    TOTAL GENERAL   :       -\n");
    }else{
        totalgeneral ++;
    printf("    TOTAL GENERAL   :       %d\n", totalgeneral);
    }
    //printf("    TOTAL GENERAL   :      %d\n", totalgeneral);
}

void des(int *(lance)){                    ///Algoritme permettant de piocher 5 valeur aux hasard entre 1 et 6.
    int i=0,j;
    for(j=0;j<5;j++){
        i = arc4random_uniform(6);
        lance[j]=i+1;
    }
//    lance[0]=4;                          //Deboguage en mettant le code aleatoir en commentaire
//    lance[1]=1;
//    lance[2]=4;
//    lance[3]=2;
//    lance[4]=1;
    
}

void des2(int *(lance), int indice){        ///Second algorithme qui permet de tiré un seul dé. Cette fonction prend en argument un int (référent du dée) et évidemment le tableau de dés.
    int i=0;
    i = arc4random_uniform(6);
    lance[indice-1]= i+1;
}

void encodage(char*(tab),int *(essais),int*(tableau), int*(lance),int*(perdu),int*(verif)){ /// Fonction void qui s'occupe de recevoir la réponse de l'utilisateur.
    if(essais[0]>0){

    printf("\nEncodage des des a rejouer (A=aucun T=tous 135=le un, le trois et le cinq)");
    printf("\nIl reste %d lances", essais[0]);
    printf("\nRelancer ?");
    fflush(stdin);
    gets(tab);
    fflush(stdin);
    
    }
    else{
        printf("\n Vous ne pouvez plus lancer les des");    /// Si l'utilisateur à déjà lancé 2x, il n'a plus le choix.
        resultat(tableau,lance, essais,perdu,verif);
    }
}

void encodageChoix(char *(tab), int *(lance), int*(tableau), int *(essais),int*(perdu),int*(verif)){
    int i;
    int indice[5]={0};                            ///Cette fonction recois en argument ce que l'utilisateur à rentré avant et va traiter cette info.
        if(tab[0]>'0' && tab[0]<='6'){            /// Si ce sont des chiffres, on va relancer les dés concercnés
            for(i=0;i<strlen(tab);i++){
                printf("Je relance le des indice : %d \n", tab[i]-48);
                indice[i]=tab[i]-48;
                des2(lance,indice[i]);
            }
             
        }
        else{                                   /// Si c'est autre chose, on va agir en fonction de son choix dans un switch.
            switch(tab[0]){
                case 'a':
                case 'A':
                    resultat(tableau,lance,essais,perdu,verif); /// Si on ne relance rien, on est envoyé dans une fonction pour choisir quel contrat remplir.
                break;
                    
                case 't':
                case 'T':
                    des(lance);             /// Soit relancer completmeent les des à l'aide de la premiere fonction de tirage aléatoire.
                break;
                    
                default:
                    //printf("Veuillez introduire une reponse valable");
                    essais[0]++;           /// Soit ne rien faire en cas de mauvaise entrée et dans ce cas augmenter le nombre de tour de +1 pour ne pas qu'il descende à cause de la boucle alors qu'on a rien fait.
                    break;
                }
        }
}

void resultat(int*(tableau),int*(lance),int *(essais),int*(perdu),int*(verif)){
    int choix;
    verif[0]=0;
    int verif_resultat=0;
//    int i;
//    int somme;
    do {
//        somme =0;
//        for(i=0;i<5;i++){
//            if(tableau[lance[i]-1]>0){
//                somme ++;
//            }
//        }
        /*if(somme==5 && tableau[13]!=0){
            printf("Vous avez perdus");
            perdu[0]=7;
            verif_resultat +=1;
        }*/
        //else{
            printf("\nQuelle combinaison choisissez-vous ?");
            fflush(stdin);
            scanf("%d", &choix);///Ici on recupere le choix du contrat
        if(choix > 14){
            printf("Ce contrat n'existe pas");                  /// On s'asure qu'on rempli bien un contrat existant
            verif_resultat = 0;
        }
            else if(tableau[choix-1]<0){                                /// On s'assure que le contrat est vide (contient la valeur "-1")
                incrementation(tableau,lance,choix,essais,verif);      ///Si oui, on va dans la fonction incrementation.
//                if(tableau[choix-1]>=-1 || tableau[0]==0){
//                    verif_resultat +=1;
//                }
                if(tableau[choix-1]>-1){                        ///Si on a pu remplir la valeur du tableau avec succes, on ajoute 1 à "verif_resultat" pour sortir de la boucle
                      verif_resultat +=1;
                  }
            }
            else if(tableau[choix-1]>=0){                                  ///Si le champ qu'on veut remplir  est déjà rempli par autre chose (donc 0 ou plus), alors on demande à nouveau quelle contrat on souhaite remplir. On laisse défini par sécurité "verif_resultat" à 0 pour rester dans  la boucle
                printf("\n Vous avez deja rempli le champ num %d", choix);
                verif_resultat=0;
            }
//            else{
//                verif_resultat +=1;
//            }
        //}
    } while (verif_resultat==0 && choix!=15);
    des(lance);              /// Quand on a reussi à remplir un champ, on relance les dés et on repars dans la suite du main
}

void incrementation(int*(tableau),int*(lance), int choix,int *(essais),int*(verif)){
    int i;
    int somme=0;
    verif[0]=0;
    switch(choix){                           ///Switch permettant de traiter la réponse du contrat à remplire
        case 1:
            for(i=0;i<6;i++)
            {
                if(lance[i]==1){
                    tableau[0]+=1;          /// Jusqu'au 6, on ne fait que compter le nombre de(1...6) dans les dés et faire + ce chiffre à chaque fois qu'il apparait
                    verif[0]=2;             /// Si il y a un moins un seul "1", on dit que verif[0] = 2
                }
            }
            if(verif[0]>0){
                tableau[0]++;         /// Ce code repere si on a rempli le contrat, avec "verif[0]" et si oui, s'il y avait au moins un chiffre bon, on rajoute 1 au contrat, car celui-ci commençais à -1
            }
            else{
                tableau[0]=0;        /// Au contraire, si il n'y avait aucun "1", c'est qu'on joue à vide, donc on dit que le contrat vaut 0 et on dis que verif[0] = 2.
                verif[0]=2;
            }
        break;
        case 2:
            for(i=0;i<6;i++)
            {
                if(lance[i]==2){
                    tableau[1]+=2;
                    verif[0]=2;
                }
            }
            if(verif[0]>0){
                tableau[1]++;
            }
            else{
                tableau[1]=0;
                verif[0]=2;
            }
        break;
        case 3:
            for(i=0;i<6;i++)
            {
                if(lance[i]==3){
                    tableau[2]+=3;
                    verif[0]=2;
                }
            }
            if(verif[0]>0){
                tableau[2]++;
            }
            else{
                tableau[2]=0;
                verif[0]=2;
            }
        break;
        case 4:
            for(i=0;i<6;i++)
            {
                if(lance[i]==4){
                    tableau[3]+=4;
                    verif[0]=2;
                }
            }
            if(verif[0]>0){
                tableau[3]++;
            }
            else{
                tableau[3]=0;
                verif[0]=2;
            }
        break;
        case 5:
            for(i=0;i<6;i++)
            {
                if(lance[i]==5){
                    tableau[4]+=5;
                    verif[0]=2;
                }
            }
            if(verif[0]>0){
                tableau[4]++;
            }
            else{
                tableau[4]=0;
                verif[0]=2;
            }
        break;
        case 6:
            for(i=0;i<6;i++)
            {
                if(lance[i]==6){
                    tableau[5]+=6;
                    verif[0]=2;
                }
            }
            if(verif[0]>0){
                tableau[5]++;
            }
            else{
                tableau[5]=0;
                verif[0]=2;
            }
        break;
        case 7:
            tableau[6] = brelan(lance,verif);
//            if(tableau[6]==-1){
//                tableau[6]=0;
//            }
        break;
            
        case 8:
            tableau[7] = carre(lance,verif);   ///Pour les contrats de 7 à 12, le switch renvois à chaque fois vers des fonctions externes en envoyant en argument les dés, et le tableau de vérif.
        break;
            
        case 9:
            tableau[8] = full(lance,verif);
        break;
            
        case 10:
            tableau[9] = petite_Suite(lance, verif);
        break;
            
        case 11:
            tableau[10] = grande_Suite(lance, verif);
        break;
            
        case 12:
            tableau[11] = yahtsee(lance, verif);
        break;
        
        case 13:
            for(i=0;i<5;i++){
                somme += lance[i];                ///Pour le contrat 13, on fait uniquement la somme de tous les dés.
            }
            tableau[12]=somme;
        break;
            
        case 14:
            tableau[13] = contrat_421(lance);
            break;
        default:
            
            verif[0]=2;                       /// En défault, il ne se passe rien et on égale à 2 verif[0]
            break;
    }
    //des(lance);
    essais[0]=3;
}

int brelan(int*(lance),int*(verif)){
    int i,j;
    int somme=0;
    for(i=1;i<7;i++){
        somme=0;
        for(j=0;j<6;j++){              ///Algorithme permettant de regarder combien de fois sur 5 dés apparait les nombres de 1 à 7.
            if(lance[j]==i){
                somme ++;            ///Chaque fois que le nombre de la boucle est rencontré, on incrémente la somme
            }
            if(somme>=3){
                verif[0]=2;           /// Si la somme est de 3 ou plus, cela signifie qu'on a bien un brelan, et on retourne 3 fois le nombre qui apparait 3 fois ou plus.
                return 3*i;
            }
        }
    }
    if(verif[0]<2){
        verif[0]+=2;
    }
    return 0;                  /// Si aucun brelan n'est détecté, on retourne 0
}

int carre(int*(lance),int*(verif)){
    int i,j;
    int somme=0;
    for(i=1;i<=6;i++){
        somme=0;
        for(j=0;j<5;j++){
            if(lance[j]==i){
                somme ++;
            }
            if(somme>=4){            /// Même principe que le brelan sauf qu'on vérifie qu'un nombre est présent 4 fois au minimum
                verif[0]=2;
                return 4*i;           /// Dans ce cas, on retourne 4 fois le nombre présent 4 fois ou plus
            }
        }
    }
    return 0;                   /// Si aucun carre n'est détecté, on retourne 0.
}

int full(int*(lance),int*(verif)){
    int i,j,k,l;
    int egal_i=0;
    int somme=0;      // On déclare une premire somme
    int somme2=0;     // On délcare une deuxième somme
    for(i=1;i<7;i++){ ///On analyse pour chaqque chiffre...
        somme=0;
        for(j=0;j<6;j++){       /// On regarde et on incrémente la première somme si un chiffre apparait plusieur fois
            if(lance[j]==i){
                somme ++;
                printf("\t\n somme = %d", somme);  ///Deboguage
            }
            
        if(somme==3){       /// Si un des chiffre apparait 3 fois, on continue
            egal_i=i;
            for(k=1;k<7;k++){
                for(l=0;l<6;l++){
                    if(lance[l]==k && lance[l]!=egal_i){   /// Si un AUTRE QUE i chiffre apparait 2 fois, cela signifie qu'on à un full
                        somme2 ++;
                        printf("\t\n somme2 = %d", somme2);
                    }
                    if(somme2==2){
                        verif[0]=2;   ///Dans ce cas c'est gagné et on a 25 points
                        return 25; ///Retourne 25
                    }
                }
            }
        }
        
    }
    
    }
    return 0; /// Si ca n'a pas été fait, on retourne 0.
}

int petite_Suite(int*(lance),int*(verif)){
    int i,j;
    int somme1=0,somme2=0,somme3=0;
    int num[6]={0};       ///Déclaration d'un tableau de 6 cases qu'on initialise à 0.
    for(i=1;i<7;i++){
        for(j=0;j<6;j++){
            if(lance[j]==i){
                num[i-1]++;    ///Incrémenter le tableau du nombre de fois qu'un nombre "i" est apparut.
            }
    }
    }
    for(i=0;i<6;i++){
        printf("\t\nNombre de %d = %d",i+1,num[i]);  ///Impression pour deboguage pour comprendre commentle code à calculer
    }
    for(i=0;i<4;i++){
        if(num[i]>0){
            somme1 ++;      ///On ajoute 1 à chaque fois que la case "i" du tableau est plus grande que 1 pour les cases du tableau de 0 à 3 (1234)
        }
    }
    for(i=1;i<5;i++){
        if(num[i]>0){
            somme2 ++;      ///Pareil pour les cases du tableau de 1 à 4    (2345)
        }
    }
    for(i=2;i<6;i++){
        if(num[i]>0){
            somme3 ++;       ///Pareil pour les cases de 2 à 5 (3456)
        }
    }
//    if(somme1>=4 || somme2>=4 || somme3>=4){
//        verif[0]=2;              /// Si l'une de ces 3 sommes vaut 4, cela signifie qu'on est en face d'une petite suite, ou d'un grande mais ça on ne sait pas encore.
//        return 30;
//    }
    if(somme3==4){
        return 35;
    }
    if(somme2==4){
        return 30;
    }
    if(somme1==4){
        return 25;
    }
 
    return 0;           /// Si rien de tout ça n'est fait, on retourne 0.
}


int grande_Suite(int*(lance),int*verif){
    int i,j;
    int somme1=0,somme2=0;
    int num[6]={0};
    for(i=1;i<7;i++){
        for(j=0;j<6;j++){
            if(lance[j]==i){
                num[i-1]++;          ///Boucle permettant de compter le nombre de fois que les nombre de1à 6 apparaissent dans le code
            }
    }
    }
    for(i=0;i<6;i++){
        printf("\t\nNombre de %d = %d",i+1,num[i]);   ///Deboguage
    }
    for(i=0;i<5;i++){
        if(num[i]>0){
            somme1 ++;   /// Compte le nombre de numéro apparant de 1 à 5. (12345)
        }
    }
    for(i=1;i<6;i++){
        if(num[i]>0){   /// Pareil pour les nombre de 2 à 6 (23456)
            somme2 ++;
        }
    }
    if(somme1>=5 || somme2>=5){
        verif[0]=2;     /// Si l'un de ces sommes vaut 5 alors on est en face d'une grande suite. On accorde 40 points et on donne la valeur 2 à verif[0]
        return 40;
    }
    return 0; ///Si rien n'a pu être fait, on retourn 0.
}

int yahtsee(int*(lance),int*(verif)){
    int i,j;
    int somme=0;
    for(i=1;i<7;i++){
        somme=0;
        for(j=0;j<5;j++){
            if(lance[j]==i){
                somme ++;     /// Pour tout les nombres de 1 à 6, on compte le nombre de fois qu'il est présent et on augmente "somme" de 1 à chaque fois.
                }
            if(somme==5){      /// Si une fois "somme" vaut 5, alors on a un yahtsee et on accorde les 50 points promis.
                verif[0]=2;   ///On donne la valeur 2 à verif[0]
                return 50;
            }
        }
    }
    return 0; /// Si somme n'a jamais été égal à 5, alors on retourne0.
    
}

int contrat_421(int *(lance)){
    bool un = false;
    bool deux = false;
    bool quatre = false;
    int i;
    int rep_somme=0;
    
    for(i=0;i<5;i++){
        if(lance[i]==1){
            un = true;
        }
        if(lance[i]==2){
            deux = true;
        }
        if(lance[i]==4){
            quatre = true;
        }
    }
    
    if(un == true && deux == true && quatre ==true){
        
        for(i=0;i<5;i++){
            rep_somme += lance[i];
        }
        return rep_somme;
    }
    else{
        return 0;
    }
    
}
