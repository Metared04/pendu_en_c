#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definition variables globales

char nom_joueur[30]; // Le nom du joueur, pour l'avoir sous la main en permance
char mot_a_deviner[50]; // Idem pour le mot a deviner

// Definition fonctions

// Prend en parametre un entier, ne revient rien et fait un nombre 'nombre_de_retour' a la ligne
void retour_a_la_ligne(int nombre_de_retour){
	if(nombre_de_retour <= 0){ // Si la valeur en parametre et nul on quitte par securite
		return;
	} else { // Sinon on fait des retours a la ligne
		for(int i = 0; i < nombre_de_retour; i++){
			printf("\n");
		}
	}
}

// Ne prend rien parametre, renvoit un entier qui correspond au nombre de mots dans le fichier texte 
int obtenir_nombre_de_mots(void){
	// On cree un compteur de mots
	int compteur = 0;
	// On cree une chaine de caractere de tres grande taille pour etre sur de lire tous les mots du dictionnaire
	char texte[250];
	// On ouvre le fichier contenant les mots en lecture uniquement
	FILE *fic = fopen("words.txt", "r");
	//Tant qu'on peut lire mots, on augmente le compteur
	while(fgets(texte, 250, fic) != NULL){
		compteur++;
	}
	// On oublie pas de fermer le fichier
	fclose(fic);
	// On renvoit le compteur
	return compteur;
}

// Prend en parametre la valeur maximale m, renvoit un entier aleatoire dans l'intervalle [0, m]
int valeur_aleatoire(int valeur_maximum){
	return 1 + rand() % valeur_maximum;
}

// Prend en parametre un valeur, ne renvoit rien, parcours le dictionnaire jusqu'a atteindre la valeur prise en parametre
void obtenir_mot_a_deviner(int indice){
	// On cree le compteur
	int compteur = 0;
	// On ouvre le fichier qui fait office de dictionnaire
	FILE *fic = fopen("words.txt", "r");
	// Tant que le compteur est inferieur a la valeur prise en parametre
	while(compteur < indice){
		// On dit que mot_a_deviner est le mot lu
		fscanf(fic, "%s", mot_a_deviner);
		// On incremente le compteur
		compteur++;
	}
	// On ferme le fichier
	fclose(fic);
}

// Prend en parametre un mot, ne renvoit rien, ecrit le mot pris en parametre avec des espaces
void affichage_mot(char mot[]){
	// Un peu de mises en pages ...
	printf("\n");
	printf("\n");
	// Tant que notre indice de parcours a pas depasse la taille du taille du mot
	for(int i = 0; i < strlen(mot); i++){
		// On ecrit un espace puis la lettre a l'indice correspondant
		printf(" %c",mot[i]);
	}
}

// Ne prend rien en parametre et ne renvoit rien, sert seulement a de la mise en page
void mise_en_page(void){
	printf("\n");
	printf("---------------------------------------------------------------------------------------------------\n");
	printf("\n");
}

// Prend un entier en parametre, ne renvoit rien affiche le nombre d'erreur
void affichage_erreur(int nombre_erreur){
	printf("\t=>\t%d / 8 erreur(s)\n", nombre_erreur);
}

// Prend une chaine de caractere et un entier en parametre, ne renvoit rien, appelle deux autres fonctions
void affichage_etat_jeu(char mot[], int nombre_erreur){
	affichage_mot(mot);
	affichage_erreur(nombre_erreur);
}

// Ne prend rien en parametre, renvoit un caractere
char demander_lettre_pendu(void){
	// On cree un mot vide de taille 250 pour eviter le plus possible le depassement de memoire
	char entrer_utilisateur[250];
	// On recupere ce mot grace a fgets
	fgets(entrer_utilisateur,250,stdin);
	// On remplace le caractere retour a la ligne par le caractere speciale \0
	entrer_utilisateur[strcspn(entrer_utilisateur,"\n")] = '\0';
	
	// On renvoit le premier caractere
	return entrer_utilisateur[0];
}

// Prend un caractere en parametre, renvoit un entier, permet de confirmer si l'utilisateur veut voir l'historique des lettres deja ecrite ou pas
int demande_historique(char caractere){
	// Pour afficher l'historique, l'utilisateur doit taper '<' ou '>'
	// Si le code ascii du caractere pris en parametre correspond au code ascii de l'un des deux caracteres cites avant
	if((int)caractere == 60 || (int)caractere == 62){
		// On renvoit 1
		return 1;
	}
	// 0 Sinon
	return 0;
}

// Prend un caractere en parametre, renvoit un entier, permet de confirmer si l'utilisateur a ecrit une majuscule ou pas
int est_une_majuscule(char caractere){
	// De la meme facon que pour la fonction precedente,
	// Si le code ascii du caractere pris en parametre correspond au code ascii d'une lettre en majuscule
	if((int)caractere >= 65 && (int)caractere <= 90){
		// On renvoit 1
		return 1;
	}
	
	// 0 sinon
	return 0;
}

// Prend un caractere en parametre, renvoit un entier, permet de confirmer si l'utilisateur a ecrit une majuscule ou pas
int est_une_minuscule(char caractere){
	// De la meme facon que pour la fonction precedente,
	// Si le code ascii du caractere pris en parametre correspond au code ascii d'une lettre en minuscule
	if((int)caractere >= 97 && (int)caractere <= 122){
		// On renvoit 1
		return 1;
	}
	
	// 0 sinon
	return 0;
}

// Prend un caractere, un tableau de caractere, un entier, renvoit un entier, si le caractere pris en parametre est dans l'historique on agit en fonction
int historique(char lettre, char tab[], int taille_tab){
	// Si le caractere pris en parametre et une majuscule
	if(est_une_majuscule(lettre) == 1){
		// On le convertit en minuscule
		lettre = lettre + 32;
	}
	// On parcours le tableau de caractere
	for(int i = 0; i < taille_tab; i++){
		// Si un caractere du tableau correspond au caractere pris en parametre
		if(tab[i]==lettre){
			// On renvoit 1
			return 1;
		}
	}
	// 0 sinon
	return 0;
}

// Prend un tableau de caractere et sa taille en parametre, ne renvoit rien, permet d'afficher l'historique des lettres deja utilisees dans le terminal
void afficherHistorique(char tab[], int taille_tab){
	// Mise en page
	printf("Voici les lettres deja utilisees : ");
	// Tant qu'on a pas atteint la taille du tableau
	for(int i = 0; i < taille_tab; i++){
		// On affiche la lettre
		printf(" %c ", tab[i]);
	}
	// Mise en page
	printf("\n");
}

// Prend un entier en parametre, ne renvoit rien permet de dessiner l'echaffaut
void affichagePendu(int nbEchecs){
	// On cree le tableau de chaine de caractere contenant les echaffauts
	char pendu[][300] = {
		" \n",
		"\n    |   \n    |  \n    | \n    | \n    | \n    | \n    | \n   /|\\ \n__/_|_\\__ \n",
		"    +--+---------------------------+\n    | / \n    |/ \n    | \n    | \n    | \n    | \n    | \n   /|\\ \n__/_|_\\__ \n",
		"    +--+---------------------------+\n    | /                            | \n    |/ \n    | \n    | \n    | \n    | \n    | \n   /|\\ \n__/_|_\\__ \n",
		"    +--+---------------------------+\n    | /                            | \n    |/                             O \n    | \n    | \n    | \n    | \n    | \n   /|\\ \n__/_|_\\__ \n",
		"    +--+---------------------------+\n    | /                            | \n    |/                             O \n    |                              |  \n    | \n    | \n    | \n    | \n   /|\\ \n__/_|_\\__ \n",
		"    +--+---------------------------+\n    | /                            |\n    |/                             O \n    |                             \\|/\n    |                              |\n    |\n    |\n    |\n   /|\\\n__/_|_\\__",
		"    +--+---------------------------+\n    | /                            |\n    |/                             O\n    |                             \\|/\n    |                              |\n    |                             /\n    |\n    |\n   /|\\\n__/_|_\\__",
		"    +--+---------------------------+\n    | /                            | \n    |/                             O \n    |                             \\|/ \n    |                              | \n    |                             / \\ \n    | \n    | \n   /|\\ \n__/_|_\\__ \n"
	};
	// Mise en page
	printf("\n");
	// Dependant du nombre d'erreurs on affiche l'echaffaut correspondant
	printf("%s", pendu[nbEchecs]);
}

// Prend un caractere en parametre, renvoit un entier permet de voir si l'utilisateur veut relancer une partie
int demande_relancer_jeu(char caractere){
	// Selon le code ascii du caractere pris en parametre, on va renvoyer un entier different
	// Cas 1 : le code ascii du caractere pris en parametre correspond a 't' ou 'T'
	// Cas 2 : le code ascii du caractere pris en parametre correspond a 'y' ou 'Y' ou 'o' ou 'O' equivalent de 'yes' ou 'oui'
	// Cas 3 : le code ascii du caractere pris en parametre correspond a 'n' ou 'N' equivalent de 'no' ou 'non'
	// Cas 4 : on a aucun des cas precedent
	if((int)caractere == 116 || (int)caractere == 84){
		// On renvoit 2
		return 2;
	} else if((int)caractere == 121 || (int)caractere == 89 || (int)caractere == 111 || (int)caractere == 79){
		// On renvoit 1
		return 1;
	} else if((int)caractere == 110 || (int)caractere == 78){
		// On renvoit 0
		return 0;
	} else {
		// -1 sinon
		return -1;
	}
}

// Prend une chaine de caractere, un reel positif, ne renvoit rien permet d'ecrire le nom et le score du joueur dans le fichier texte correspondant
void entrer_les_stats_dans_le_bon_txt(char nom[], float le_score_final){
	// On ouvre le fichier contenant les stats des joueurs en ecriture a la fin du fichier
	FILE *fic_stats = fopen("listeStats.txt", "a");
	// Si on arrive pas a ouvrir le txt, c'est les problemes
	if(fic_stats == NULL){
		printf("Probleme avec le txt\n");
		exit(1);
	}
	// On fait un retour a la ligne dans le fichier texte pour faire de la mise en page
	fputs("\n", fic_stats);
	// On ecrit grace a fprintf les valeurs prises en parametre
	fprintf(fic_stats,"%s %.1f", nom, le_score_final);
	// On ferme le fichier
	fclose(fic_stats);
}

// Prend en parametre un entier, renvoit un reel positif, selon le nombre d'erreur commis par l'utilisateur, on renvoit un coeficient (si il gagne)
float calc_coef(int nb_d_Erreur){
	if(nb_d_Erreur == 0){
		return 2.0;
	} else if(nb_d_Erreur == 1){
		return 1.7;
	} else if(nb_d_Erreur == 2){
		return 1.5;
	} else if(nb_d_Erreur == 3){
		return 1.4;
	} else if(nb_d_Erreur == 4){
		return 1.3;
	} else if(nb_d_Erreur == 5){
		return 1.2;
	} else if(nb_d_Erreur == 6){
		return 1.1;
	} else {
		return 1.0;
	}
	
	return 1.0;
}

// Prend en parametre 2 entiers, renvoit un reel positif, permet de calculer le score que l'utilisateur a obtenue
float calc_score(int taille_du_mot, int nombre_d_erreur){
	// On cree un reel qui est un appelle a la fonction calc_coef pour avoir le coeficient
	float coeficient = calc_coef(nombre_d_erreur);
	
	// On renvoit le score calculer
	return ((float)taille_du_mot * 10.0) * coeficient;
}

// Ne prend rien en parametre et ne renvoit rien, prend notre fichier contenant les statistiques des joueurs et en fait une copie modifiable a notre guise
void copie_du_fichier_stats(void){
	// On definit une chaine de caractere correspondant au nom du joueur lu
	char nom_joueur[30];
	// Et un reel pour son score
	float leur_score;
	// On ouvre le fichier stats en lecteur uniquement
	FILE *fic_stats = fopen("listeStats.txt", "r");
	// On ouvre un fichier temporaire en ecriture uniquement, or comme il n'existe pas a ce stade, il sera creer
	FILE *fic_temporaire = fopen("stats_temporaire.txt", "w");
	// Si on arrive pas a ouvrir le txt, c'est les problemes
	if(fic_stats == NULL){
		printf("Probleme avec le txt\n");
		exit(1);
	}
	// Idem
	if(fic_temporaire == NULL){
		printf("Probleme avec le txt\n");
		exit(1);
	}
	// Tant qu'on lit des noms de joueur ainsi que leur score (ou tant qu'on n'est pas a la fin du fichier)
	while(fscanf(fic_stats, "%s %f", nom_joueur, &leur_score) != EOF){
		// On ecrit dans le fichier temporaire les données qu'on lit
		fprintf(fic_temporaire, "%s %.1f", nom_joueur, leur_score);
		// Avec un retour a la ligne
		fputs("\n", fic_temporaire);
	}
	// On ferme les 2 fichiers
	fclose(fic_stats);
	fclose(fic_temporaire);
}

// Prend un entier en parametre, ne revoit rien, cette fonction efface une ligne donnée du fichier temporaire
void effacer_ligne(int ligne){
	// On cree un compteur de ligne
	int compteur = 0;
	// Un chaine de caractere qui correspond au nom du joueur lu
	char nom_joueur[30];
	// Et un reel pour son score
	float leur_score;
	// On ouvre en lecture simple le fichier temporaire
	FILE *fic_a_remplacer = fopen("stats_temporaire.txt", "r");
	// On ouvre en ecriture simple le fichier qui va remplacer le fichier temporaire qu'on va supprimer
	FILE *fic_qui_va_remplacer = fopen("stats_temporaire_temporaire.txt", "w");
	
	// Si on arrive pas a ouvrir le txt, c'est les problemes
	if(fic_a_remplacer == NULL){
		printf("Probleme avec le txt\n");
		exit(1);
	}
	// Idem
	if (fic_qui_va_remplacer == NULL) {
        printf("Probleme avec le txt\n\n");
        exit(1);
    }
	
	// Tant qu'on lit des lignes
	while(fscanf(fic_a_remplacer, "%s %f", nom_joueur, &leur_score) != EOF){
		// Si notre compteur est different de la ligne qu'on va supprimer
		if(compteur != ligne){
			// On ecrit les valeurs qu'on lit dans le nouveau fichier temporaire
			fprintf(fic_qui_va_remplacer, "%s %.1f", nom_joueur, leur_score);
			// Avec un retour a la ligne pour un peu de forme
			fputs("\n", fic_qui_va_remplacer);
		}
		// Ce qui permet ainsi de NE PAS conserver la ligne voulue
		// On incremente le compteur pour signifier qu'on passe a la ligne suivante
		compteur++;
	}
	// On ferme les deux fichiers
	fclose(fic_a_remplacer);
	fclose(fic_qui_va_remplacer);
	
	// Avec la fonction remove on supprime le premier fichier temporaire
	// Si la fonction remove ne marche pas correctement, on a un probleme
	if (remove("stats_temporaire.txt") != 0) {
        printf("Probleme de suppression avec le txt\n");
        exit(1);
    }
	// Avec la fonction rename le fichier avec une ligne en moins devient le fichier temporaire
	// Idem avec la fonction rename, on a un probleme
    if (rename("stats_temporaire_temporaire.txt", "stats_temporaire.txt") != 0) {
        printf("Probleme de suppression avec le txt\n");
        exit(1);
    }
}

int nombre_de_joueur(void){
	int compteur_de_joueur = 0;
	char nom_joueur[30];
	float leur_score;
	FILE *fic_stats = fopen("listeStats.txt", "r");
	if(fic_stats == NULL){
		printf("Probleme avec le txt mdr\n");
		exit(1);
	}
	while(fscanf(fic_stats, "%s %f", nom_joueur, &leur_score) != EOF){
		compteur_de_joueur++;
	}
	fclose(fic_stats);
	return compteur_de_joueur;
}

// Ne prend rien en parametre et ne revoit rien, cette fonction liste le fichier top 10 dans lequel les 10 meilleurs scores sont ordonnees
// du plus grand au plus petit
void lecture_top_10(void){
	// On cree un compteur qui va faire office de classement
	int compteur = 1;
	// Un chaine de caractere qui correspond au nom du joueur lu
	char nom_joueur[30];
	// Un reel pour le score
	float leur_score;
 	// On ouvre notre fichier top 10 en lecture uniquement
	FILE *fic_top_10 = fopen("top_10.txt", "r");
	// Si on arrive pas a l'ouvrir, les problemes
	if(fic_top_10 == NULL){
		printf("Probleme avec le txt mdr\n");
		exit(1);
	}
	// De la mise en page ...
	printf("\n");
	printf("\n");
	printf("+---------------------------------------------------------------------------------------------------+");
	printf("\n");
	printf("\n");
	printf("------------>  Voici le top 10 des meilleurs joueurs :\n\n\n");
	// Tant qu'on est pas a la fin du fichier
	while(fscanf(fic_top_10, "%s %f", nom_joueur, &leur_score) != EOF){
		// On ecrit ce qu'on lit sous la forme classement du joueur -> son nom et son score
		printf("    Numero %d -> %s avec %.1f point(s)\n\n", compteur, nom_joueur, leur_score);
		// On augmente le compteur pour passer a la place suivante
		compteur++;
	}
	// De la mise en page ...
	printf("\n");
	printf("+---------------------------------------------------------------------------------------------------+");
	printf("\n");
	// On ferme le ficher
	fclose(fic_top_10);
}

// Ne prend rien en parametre et ne revoit rien, cette fonction identifie le score le plus eleve du fichier temporaire
void plus_grand_chiffre(void){	
	// Compteur d'iteration de la boucle while
	int i = 0;
	
	// On compte le nombre de ligne
	int compteur_de_joueur_dans_txt = nombre_de_joueur();
	
	// Si le compteur de ligne est inferieur ou egal a 0 c'est pas normal
	if(compteur_de_joueur_dans_txt <= 0){
		printf("Il n'y a pas encore assez de joueurs pour creer un Top.\n");
		return;
	} else if(compteur_de_joueur_dans_txt > 10){
		compteur_de_joueur_dans_txt = 10;
	}
	// On ouvre le fichier qui va noter notre top 10 donc en ecriture uniquement
	FILE *fic_top_10 = fopen("top_10.txt", "w");
	// Tant que notre indice est inferieur au nombre de joueur dans notre fichier
	while(i<compteur_de_joueur_dans_txt){
		// On definit un chaine de caractere comme etant un nom de joueur lu
		char nom_joueur[30];
		// On definit un chaine de caractere comme etant le nom du meilleur joueur lu
		char nom_meilleur_joueur[30];
		// On definit un reel comme etant le score du joueur lu
		float leur_score;
		// On definit un reel comme etant le plus grand score lu
		float plus_grand_score = -1.0;
		// On definit un reel comme etant un curseur du potentiel meilleur score lu
		float plus_grand_score_temporaire;
		// On definit un entier qui servira de compteur de ligne
		int compteur = 0;
		// On definit un entier qui servira a reperer la ligne du meilleur score lu
		int compteur_indice_du_meilleur_joueur = 0;
		// On ouvre notre fichier temporaire en lecture uniquement
		FILE *fic_temporaire = fopen("stats_temporaire.txt", "r");
		// Si on arrive pas a l'ouvrir, les problemes encore et toujours
		if(fic_temporaire == NULL){
			printf("Probleme avec le txt\n");
			exit(1);
		}
		// Tant qu'on peut lire des lignes dans ce fichier
		while(fscanf(fic_temporaire, "%s %f", nom_joueur, &leur_score) != EOF){
			// Plus_grand_score_temporaire devient la valeur lu
			plus_grand_score_temporaire = leur_score;
			// Si la valeur lu est plus grande que la suppose plus grande valeur
			if(plus_grand_score_temporaire >= plus_grand_score){
				// La suppose plus grande valeur devient la nouvelle plus grande valeur
				plus_grand_score = plus_grand_score_temporaire;
				// On retient le nom du joueur qui a cette valeur
				strcpy(nom_meilleur_joueur, nom_joueur);
				// On retient la position dans le fichier txt (compte en nb de ligne ici)
				compteur_indice_du_meilleur_joueur = compteur;
			}
			// On incremente ce compteur pour dire que l'on passe a la ligne suivante
			compteur++;
		}
		// On l'entre dans le fichier txt top 10
		fprintf(fic_top_10, "%s %.1f", nom_meilleur_joueur, plus_grand_score);
		// On ajoute a retour a la ligne
		fputs("\n", fic_top_10);
		// On ferme le fiochier pour pouvoir l'utiliser dans la fonction effacer_ligne
		fclose(fic_temporaire);
		// On appelle la fonction qui va supprimer une ligne de notre txt stats_temporaire
		effacer_ligne(compteur_indice_du_meilleur_joueur);
		// On recomme toutes ses operations jusqu'a ce qu'on ait i = 10 donc qu'on ait notre top 10
		i++;
	}
	// On ferme le fichier top 10 pour pouvoir l'utiliser dans la fonction lecture top 10
	fclose(fic_top_10);
	
	// On lit le fichier top 10
	lecture_top_10();
}

// Ne prend rien en parametre et ne renvoit rien, cette fonction supprime les fichiers temporaires que j'ai creer pour manipuler des donnees
void supprimer_fichier_tempo(void){
	// Si on arrive pas a le supprimer, bah c'est embetant...
	if (remove("stats_temporaire.txt") != 0) {
        printf("Probleme de suppression avec le txt\n");
        exit(1);
    }
	// Idem
	if (remove("top_10.txt") != 0) {
        printf("Probleme de suppression avec le txt\n");
        exit(1);
    }
}

// Ne prend rien en parametre et ne renvoit rien, cette fonction lit le fichier top 10 et affiche ces donnees
void afficher_top_10(void){
	// On compte le nombre de ligne
	int compteur_de_joueur_dans_txt = nombre_de_joueur();
	
	// Si le compteur de ligne est inferieur ou egal a 0 c'est pas normal, on doit donc imperativement quitter la fonction
	if(compteur_de_joueur_dans_txt <= 0){
		printf("Il n'y a pas encore assez de joueurs pour creer un Top.\n");
		return;
	}
	// On appelle les fonctions necessaires
	copie_du_fichier_stats();
	plus_grand_chiffre();
	supprimer_fichier_tempo();
}

// Ne prend rien en parametre et ne renvoit rien, cette fonction demande le nom du joueur
void demander_nom(void){
	// 'booleen' qui servira a verifier si le nom rentre est valide
	// Pour qu'il soit valide il suffit d'au moins un caractere
	int pseudo_valide = 0;
	do{
		// On demande au joueur son nom, avec les formes
		printf("\n------------>  Bienvenue dans le pendu d'Enzo, entrez votre nom pour commencer.\n------------>  Si vous voulez consulter le top 10 tapez 'Top 10'.\n\n>>>>>>>  ");
		// On utilise fgets pour eviter des problemes avec les noms contenant des espaces
		fgets(nom_joueur,30,stdin);
		// Meme chose qu'avec la demande de caractere on met le caractere \0
		nom_joueur[strcspn(nom_joueur,"\n")] = '\0';
		// Cas 1 : si le nom du joueur est 'Top 10' ou 'top 10'
		// Cas 2 : si le nom du joueur est un espace donc un champ vide
		if(strcmp(nom_joueur, "Top 10") == 0 || strcmp(nom_joueur, "top 10") == 0){
			// On affiche le top 10
			afficher_top_10();
		} else if(strcmp(nom_joueur, " ") == 0){
			// On peut pas valider donc on boucle en affichant un probleme
			printf("\n              /!\\ Veillez entrer un nom /!\\\n");
		} else {
			// Le nom est donc valide.
			pseudo_valide = 1;
		}
		// Tant que le pseudo n'est pas valide on boucle
	}while(pseudo_valide == 0);
	// Sinon la partie peut commencer
	printf("\n");
	printf("------------>  Bonjour %s, que la partie commence !\n\n", nom_joueur);
}

int main(void){
	
	// Creation d'un joueur en demandant son nom
	demander_nom();
	mise_en_page();
	
	// On cree un reel qui sera le score total du joueur
	float score_total = 0.0;
	// On cree un reel qui sera le score temporaire du joueur
	float score = 0.0;
	// 'booleen' qui servira a verifier si le verifier souhaite refaire une partie
	int relancer_jeu = 0;
	// 'booleen' qui servira a verifier si la lettre rentree est correct
	int lettre_correct = 0;
	do{
		// On initialise le generateur de nombre aleatoire
		srand(time(NULL));
		// On recupere le nombre de mots dans le dico
		int nombre_mots_du_txt = obtenir_nombre_de_mots();
		// On choisit une valeur aleatoire entre 0 et le nombre de mots
		int indice_aleatoire = valeur_aleatoire(nombre_mots_du_txt);
		// On recupere a quel mot correspond le chiffre
		obtenir_mot_a_deviner(indice_aleatoire);
		
		//printf("Voici le mot a deviner => %s\n", mot_a_deviner);
		// On recupere la taille du mot a deviner grace a strlen
		const int taille_de_mot_a_deviner = strlen(mot_a_deviner);
		// On cree un mot vide de la taille du mot a deviner
		char mot_en_cours[taille_de_mot_a_deviner];
		// On cree un tableau de caractere dans lequel on met les lettres deja utilisees par l'utilisateur
		char histo[26];
		// On compte le nombre de lettres dans ce tableau
		int nb_lettre_dans_histo = 0;
		
		// On remplace les caracteres par des '_' pour pouvoir l'afficher par la suite
		for(int i=0; i<=taille_de_mot_a_deviner-1; i++){
			mot_en_cours[i] = '_';
		}
		// On s'assure qu'il y a bien de caractere '\0'
		mot_en_cours[taille_de_mot_a_deviner] = '\0';
		
		// On lance la boucle de jeu, si elle est a 1 ca veut que le jeu est en cours et 0 a il n'y a pas de partie :
		int boucle_jeu = 1;
		
		// On initialise le nombre d'erreur a 0
		int nb_erreur = 0;
		// On affiche le jeu
		affichage_etat_jeu(mot_en_cours, nb_erreur);
		
		do{
			// 'booleen' qui servira a verifier si la lettre rentree est correct
			int lettre_valide = 0;
			// Caractere qui recuperera la caractere entrer par le joueur
			char lettre;
			
			do{
				printf("\n------------>  Ecrit une lettre :\n\n>>>>>>>  ");
				lettre = demander_lettre_pendu();
				mise_en_page();
				if(historique(lettre, histo, nb_lettre_dans_histo) == 1){
					printf("       Vous avez deja ecrit cette lettre !\n");
				} else if(demande_historique(lettre) == 1){
					printf("------------>  Voici l'historique :\n");
					afficherHistorique(histo, nb_lettre_dans_histo);
				} else if(est_une_majuscule(lettre) == 1){
					lettre = lettre + 32;
					printf("%c\n", lettre);
					histo[nb_lettre_dans_histo] = lettre;
					nb_lettre_dans_histo++;
					lettre_valide = 1;
				} else if(est_une_minuscule(lettre) == 1){
					histo[nb_lettre_dans_histo] = lettre;
					nb_lettre_dans_histo++;
					lettre_valide = 1;
				} else {
					printf("------------>  Veuillez entrer une lettre.\n\n>>>>>>>  ");
				}
			}while(lettre_valide == 0);
			lettre_valide = 0;
			
			// Verification si la lettre est dans le mot
			int lettre_correct = 0;
			for(int i = 0; i<=taille_de_mot_a_deviner; i++){
				if(mot_a_deviner[i]==lettre){
					mot_en_cours[i] = lettre;
					lettre_correct = 1;
				}
			}
			// affichage_etat_jeu(mot_en_cours, nb_erreur);
			
			if(lettre_correct==0){
				printf("\n       Vous avez fait une erreur !\n");
				nb_erreur++;
				affichagePendu(nb_erreur);
				affichage_etat_jeu(mot_en_cours, nb_erreur);
			} else {
				printf("\n       Bien jouer !\n");
				affichagePendu(nb_erreur);
				affichage_etat_jeu(mot_en_cours, nb_erreur);
			}
			
			if(strcmp(mot_a_deviner, mot_en_cours) == 0){
				boucle_jeu = 0;
				printf("       Victoire !\n");
				score = calc_score(taille_de_mot_a_deviner, nb_erreur);
				score_total = score + score_total;
				printf("------------>  Vous gagnez %.1f points,\n------------>  Vous score total est %.1f\n\n", score, score_total);
			}
			
			if(nb_erreur >= 8){
				boucle_jeu = 0;
				printf("\n       Vous avez perdu, voici la bonne reponse : %s\n",mot_a_deviner);
				printf("\n------------>  Votre score total est de : %.1f\n\n",score_total);
			}
			
		}while(boucle_jeu == 1);
		
		do{
			printf("------------>  Pour rejouer appuyer sur 'y',\n------------>  sinon 'n',\n------------>  pour voir le top 10 't'\n\n>>>>>>>  ");
			char lettre = demander_lettre_pendu();
			if(demande_relancer_jeu(lettre) == 2){
				//printf("       Voici le top 10 :\n");
				afficher_top_10();
			} else if(demande_relancer_jeu(lettre) == 1){
				lettre_correct = 1;
				relancer_jeu = 1;
				printf("\nLe jeu continue !\n");
			} else if(demande_relancer_jeu(lettre) == 0){
				lettre_correct = 1;
				relancer_jeu = 0;
				printf("\nBye\n");
				// Ajouter le nom, le nb de parties, les victoires dans le VRAI txt donc dans listeStats
			} else {
				lettre_correct = 0;
			}
		}while(lettre_correct == 0);
		
	}while(relancer_jeu == 1);
	// recupere mot aleatoire
	
	// on entre le nom du joueur son nb de parties et de victoires dans le bon txt
	// fait deviner
	//printf("Avant entrer : %.1f", score_total);
	entrer_les_stats_dans_le_bon_txt(nom_joueur, score_total);
	
	return 0;
}