
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef char* string;

// Déclaration des données

    //Gestion des employés

        typedef struct celluleEmp {
            string val;
            struct celluleEmp* suiv;
        } celluleEmp;

        typedef struct celluleEmp* listEmp;
        listEmp tEmp;



    //Gestion des tâches

        // typedef struct date date; //dos.h
        // typedef struct tm tm; //time.h

        typedef enum {todo, in_progress, done} status;

        typedef struct celluleTask {
            string nom;
            status state;
            time_t deadline;
            char* responsables[10];

            struct celluleTask* suiv;
        } celluleTaskk;

        typedef struct celluleTask* listTask;

        listTask tTask;



        //responsables (tableau de 10 string)

    //Gestion des dates limites
        typedef struct celluleDeadline {
            string nom;
            struct celluleDeadline* suiv;
        } celluleDeadline;

        typedef struct celluleDeadline* listDeadline;

        listDeadline tDeadline;



    //Gestion des réclamations
        typedef struct celluleReclamation {
            char* val;
            struct celluleReclamation* suiv;
        } celluleReclamation;

        typedef struct celluleReclamation* listRec;

        listRec tRec;


// Fin de déclaration des types


int choix,e,length;

int main() {
    int choix;
    tEmp = NULL;
    tTask = NULL;
    tDeadline = NULL;
    tRec = NULL;

    do {
        puts("***MENU***");
        puts("1- Gestion des employés");
        puts("2- Gestion des tâches");
        puts("3- Gestion des dates limites");
        puts("4- Gestion des réclamations");
        puts("5- Quitter le Menu");
        printf("\n\t");
        scanf("%d",&choix);
        switch (choix) {
        case 1 :
                gestion_employs();
            break;
        case 2 :
                gestion_tasks();
            break;
        case 3 :
                gestion_deadlines();
            break;
        case 4 :
                gestion_reclamations();
            break;

        case 5 :
                puts("Merci pour votre visite");
            break;
        default :
            puts ("Votre choix est erronée !! ... veuillez réessayer");
        }
    }
    while (choix != 5);
}



// modules
    void gestion_employs() {
        char* name;
        int choix=NULL;
        do {
            puts("*Gestion des employés*");
            puts("1- Ajout d'un employés");
            puts("2- Consultation des employés de la société");
            puts("3- Suppression d'un employé");
            puts("4- Voir le nombre d'employés dans la société");
            puts("5- Retour au menu principale");
            printf("\n\t");
            scanf("%d",&choix);
            switch (choix) {
                case 1 :
                    remplirEmp();
                    puts("l'employé est ajouté avec succès \n\t");
                    break;
                case 2 :
                    printf("Il y a %d employé(s) dans la société\n", longueurEmp());
                    break;
                case 3 :
                    afficheEmp();
                    break;
                case 4 :
                    printf("Saisir le nom de l'employée à supprimer\t ");
                    scanf("%s",&name);
                    supp_emp(name);
                    puts("Employé supprimé avec succès");
                    break;
                case 5 :
                    puts("Retour au menu principale");
    //                return;
                    break;
                default :
                    puts ("Votre choix est erronée !! ... veuillez réessayer");
            }
        } while (choix != 5);
    }

void gestion_tasks() {
    int choix;
    do {
        puts("*Gestion des tâches*");
        puts("1- Empiler la liste des tâches");
        puts("2- Dépiler la liste des tâches");
        puts("3- Afficher toutes les tâches dans la pile");
        puts("4- Afficher les tâches dont les dâtes limites sont dépassés");
        puts("5- Afficher l'état d'une tâche");
        puts("6- changer l'état d'une tâche");
        puts("7- retour au menu principale");
        printf("\n\t");
        scanf("%d",&choix);
        switch (choix) {
            case 1 :
                empiler_tasks();
                break;
            case 2 :
                depiler_task();
                break;
            case 3 :
                afficheTasks();
                break;
            case 4 :
                expired_tasks();
                break;
            case 5 :
                // task_status(string name);
                break;
            case 6 :
                // edit_task_status();
                break;
            case 7 :
                return;
                break;
            default :
                puts ("Votre choix est erronée !! ... veuillez réessayer");
            }
        } while (choix != 7);
    }

    char* get_date_from_timestamp(time_t* typedtime) {
        return ctime(typedtime);
    }

    string FindState(status state) { // returne l'état de la tâche
        string s;
        s = (state==0) ? "à faire" : (state==1) ? "en progrès" : "accomplis";
        return s;
    }

    string get_current_date() {
        time_t curtime;
        time(&curtime);
        return (ctime(&curtime));
    }

    status setState(string str) {
        status state;
        printf("sélectionner le nouvel état de la tâche: todo, inprogress, done");
        state = (str=="todo") ? 0 : (str=="inprogress") ? 1 : 2;
        return state;
    }

    void remplir_champs(listTask cT) {
        int n = NULL;
        cT->state = 0; // lors de l'ajout d'une tâche son statut est automatiquement mis à "à faire"
        printf("\tSaisir le nom de la tâche\t");
        scanf("%s",&cT->nom);
        printf("\tSaisir le deadline de la tâche (en timestamp)\t");
        scanf("%lld",&cT->deadline);
        printf("\tSaisir le nombre des responsables\t");
        scanf("%d",&n);
        printf("\tSaisir les noms des responsables\n");
        for(int i = 0; i<n; i++) {
            string temp=NULL;
            printf("\t\tLe noms du responsable numéro %d:\t", i+1);
            scanf("%s",&temp);
            cT->responsables[i]=temp;
        }
    }

    void empiler_tasks() {
        listTask f = NULL;
            if (tTask==NULL) { // insertion du première case
                tTask= malloc(sizeof(struct celluleTask));
                remplir_champs(tTask);
                tTask->suiv=NULL;

            } else { // insertion de restes des cases
                // à remplir sous la structure de donnée pile
                f= malloc(sizeof(struct celluleTask));
                remplir_champs(f);
                f->suiv = tTask;
                tTask = f;
            }

            puts("\tLa tâche est ajoutée avec succès");
        }


    void depiler_task() {
        if(tTask != NULL) {
            listTask lt = tTask;
            tTask = tTask ->suiv;
            free(lt);
            puts("opération terminée avec succès");
        }
        puts("la pile des tâches est déjà vide");
    }

    void expired_tasks() { //si une tâches est expiré le reste est aussi expirer, système de la pile
        listTask lt = tTask;
        bool b = true; // vrai s'il n y a pas de taches expirées
        time_t* tim;
        long long int current, tasktime;
        time_t ttime, now;
        string str;
        current = time(&ttime);
        while(lt!=NULL) {
            ttime = lt->deadline;
            tim = &lt->deadline;
            if (current-ttime>=0) {
                b = false;
                str = ctime(tim);
                printf("\tLa tâche %s est supposé fait avant le %s\n",&lt->nom, str);
            }
            lt = lt->suiv;
        }
        if(b) {
            puts("\til n'y a pas de retard");
        }

    }

    listTask getTask(string name) {
        listTask lt = tTask;
        while(lt != NULL) {
            if(lt->nom == name) {
                return lt;
            }
            tTask = tTask->suiv;
        }
        return NULL;
    }

    void task_status() {
        string name;
        listTask lt = getTask(name);
        if(lt!=NULL) {
            printf("\tla status actuelle de la tache %s: %s", name, FindState(lt->state));
        } else {
            printf("\tla tâche %s n'est pas trouvée !!", name);
        }
    }

    void edit_task_state(string name) {
        int state;
        string str;
        listTask lt = getTask(name);
        printf("\tsélectionner le nouvel état de la tâche: todo, inprogress, done");
        scanf("%s",str);
        state = (str=="todo") ? 0 : (str=="inprogress") ? 1 : (str=="done")? 2 : NULL;
        if(state==NULL) {
            puts("\tLe choix n'est pas valide, l'opération a échoué");
        } else {
            lt->state = state;
            puts("\topération terminée avec succès");
        }


    }

    void  afficheTasks() {
        listTask l;
        string str1, str2;
        status state;
        time_t* tim;
        l=tTask;
            if(l==NULL) {
                puts("\tIl n'y a pas de tâches à faire pour le moment");
            } else {
                puts("\tVoilà les tâches dans la pile");
                while (l != NULL) {
                    state = l->state;
                    tim = &l->deadline;
                    str1 = ctime(tim);
                    str2 = FindState(state);
                    printf("\t\tDétails de la tâche %s:\n", &l->nom);
                    printf("\t\t\tdate limite: %s",str1);
                    printf("\t\t\tétat: %s\n",str2);
                    puts("\t\t\tresponsables:");
                    for(int i = 0; i<10; i++) {
                        if (l->responsables[i] != NULL) {
                            printf("\t\t\t\t%s\n", l->responsables+i);
                        }
                    }
                    l=l->suiv;
                }
            puts("");
            }
    }


void gestion_deadlines() {
    do {
        puts("*Gestion des dates limites*");
        puts("1- ");
        puts("2- ");
        puts("4- retour au menu principale");
        printf("\n\t");
        scanf("%d",&choix);
        switch (choix) {
            case 1 :

                break;
            case 2 :

                break;
            case 3 :
                return;
                break;
            default :
                puts ("Votre choix est erronée !! ... veuillez réessayer");
            }
        } while (choix != 3);
    }


void gestion_reclamations() {
    do {
        puts("*Gestion des tâches*");
        puts("1- ");
        puts("2- ");
        puts("3- ");
        puts("4- retour au menu principale");
        printf("\n\t");
        scanf("%d",&choix);
        switch (choix) {
            case 1 :

                break;
            case 2 :

                break;
            case 3 :

                break;
            case 4 :
                return;
                break;
            default :
                puts ("Votre choix est erronée !! ... veuillez réessayer");
            }
        } while (choix != 4);
    }


// fonctions élémentaires
    listEmp parcourir() {
        listEmp p;
        p = tEmp;
        while (p->suiv != NULL) {
            p=p->suiv;
        }
       return p;
    }

    // gestion des employés

        void afficheEmp () {
            listEmp l;
            l=tEmp;
            if(l==NULL) {
                puts("\tIl n'y a personne qui travaille ici");
            } else {
                puts("\tNos employées sont les suivants \n\t");
                while (l != NULL) {
                    printf("\t");
                    printf("| %s |",&l->val);
                    l=l->suiv;
                }
            puts("");
            }

        }

        void remplirEmp () {
            listEmp p,q;
            bool b = true; // vrai si la liste est non parcourue
            bool isUnset = true; // vrai si la liste est vide

            //création de la cellule
            p=malloc(sizeof(listEmp));

            printf("Saisir la valeur de l'employé\t");
            if (tEmp==NULL) { // insertion du première case
                tEmp= malloc(sizeof(listEmp));

                scanf("%s",&tEmp->val);

            } else { // insertion de restes des cases
                if(b) {
                    q = parcourir();
                    b = false;
                }

                scanf("%s",&p->val);
                p->suiv= NULL;

                q->suiv=p;
                q=q->suiv;
            }
        }


        void supp_emp(string name, status state) {
            listEmp q,p;
            int i =0;
            int length = longueurEmp();
            p=tEmp;
            while(p!=NULL && i<length) {

                if(p->val == name) {
                    if(i==0) { //suppression en tête
                        p = tEmp;
                        tEmp=tEmp->suiv;
                        free(p);
                        return;
                    } else { //suppression en queue et au milieu
                        q->suiv=p->suiv;
                        free(p);
                        return;
                    }
                }
                q=p;
                p=p->suiv;
                i++;

            }
            printf("\tL'employé n'existe pas\n");
        }

        int longueurEmp() {
                listEmp l;
                int n = 0;
                l=tEmp;
                while (l != NULL) {
                    n++;
                    l=l->suiv;
                }
                l=tEmp;
                return n;
            }
    // gestion des tâches



    // gestion des dates limites

    // gestion des réclamation
