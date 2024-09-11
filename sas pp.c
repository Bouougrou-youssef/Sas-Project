#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100 //constant
#define MAX_NAME 50
#define MAX_DEPARTMENTS 5

int num_students = 0;
int student_ids[MAX_STUDENTS];
char first_names[MAX_STUDENTS][MAX_NAME];
char last_names[MAX_STUDENTS][MAX_NAME];
char birth_dates[MAX_STUDENTS][11];
int departments[MAX_STUDENTS];
float grades[MAX_STUDENTS];

char department_names[MAX_DEPARTMENTS][MAX_NAME] = {"Informatique", "Mathematiques", "Physique", "Chimie", "Biologie"};

void add_student()
{
    if (num_students >= MAX_STUDENTS)
    {
        printf("Nombre maximum d'etudiants atteint.\n");
        return;
    }
    system ("cls");
    printf("Entrez le numero unique: ");
    scanf("%d", &student_ids[num_students]);

    printf("Entrez le prenom: ");
    scanf("%s", first_names[num_students]);

    printf("Entrez le nom: ");
    scanf("%s", last_names[num_students]);

    printf("Entrez la date de naissance (JJ/MM/AAAA): ");
    scanf("%s", birth_dates[num_students]);

    printf("Entrez le departement : ");
    scanf("%d", &departments[num_students]);

    printf("Entrez la note generale: ");
    scanf("%f", &grades[num_students]);

    num_students++;
    printf("Etudiant ajoute avec succes.\n");


}

void modify_or_delete_student()
{
    int id, i, choice;
    printf("Entrez le numero unique de l'etudiant: ");
    scanf("%d", &id);

    for (i = 0; i < num_students; i++)
    {
        if (student_ids[i] == id)
        {
            printf("1. Modifier\n2. Supprimer\nChoix: ");
            scanf("%d", &choice);

            if (choice == 1)
            {


                printf("Entrez le nouveau prenom: ");
                scanf("%s", first_names[i]);
                printf("Entrez le nouveau nom: ");
                scanf("%s", last_names[i]);
                printf("Entrez la nouvelle date de naissance: ");
                scanf("%s", birth_dates[i]);
                printf("Entrez le nouveau departement (0-4): ");
                scanf("%d", &departments[i]);
                printf("Entrez la nouvelle note: ");
                scanf("%f", &grades[i]);
                printf("Etudiant modifie.\n");
            }
            else if (choice == 2)
            {
                for (int j = i; j < num_students - 1; j++)
                {
                    student_ids[j] = student_ids[j+1];
                    strcpy(first_names[j], first_names[j+1]);
                    strcpy(last_names[j], last_names[j+1]);
                    strcpy(birth_dates[j], birth_dates[j+1]);
                    departments[j] = departments[j+1];
                    grades[j] = grades[j+1];
                }
                num_students--;
                printf("Etudiant supprime.\n");
            }
            return;
        }
    }
    printf("Etudiant non trouve.\n");
}

void display_student()
{
    int id, i;
    printf("Entrez le numero unique de l'etudiant: ");
    scanf("%d", &id);

    for (i = 0; i < num_students; i++)
    {
        if (student_ids[i] == id)
        {
            printf("Numero: %d\n", student_ids[i]);
            printf("Nom: %s %s\n", first_names[i], last_names[i]);
            printf("Date de naissance: %s\n", birth_dates[i]);
            printf("Departement: %s\n", department_names[departments[i]]);
            printf("Note: %.2f\n", grades[i]);
            return;
        }
    }
    printf("Etudiant non trouve.\n");
}

void calculate_averages()
{
    float total = 0, dept_total[MAX_DEPARTMENTS] = {0};
    int dept_count[MAX_DEPARTMENTS] = {0};

    for (int i=0; i < num_students; i++)
    {
        total += grades[i];
        dept_total[departments[i]] += grades[i];
        dept_count[departments[i]]++;
    }

    printf("Moyenne generale de l'universite: %.2f\n", total / num_students);

    for (int i = 0; i < MAX_DEPARTMENTS; i++)
    {
        if (dept_count[i] > 0)
        {
            printf("Moyenne du departement %s: %.2f\n", department_names[i], dept_total[i] / dept_count[i]);
        }
    }
}

void display_statistics()
{
    printf("Nombre total d'etudiants: %d\n", num_students);

    int dept_count[MAX_DEPARTMENTS] = {0};
    for (int i = 0; i < num_students; i++)
    {
        dept_count[departments[i]]++;
    }

    for (int i = 0; i < MAX_DEPARTMENTS; i++)
    {
        printf("Nombre d'etudiants en %s: %d\n", department_names[i], dept_count[i]);
    }

    float threshold;
    printf("Entrez le seuil pour afficher les etudiants: ");
    scanf("%f", &threshold);

    printf("Etudiants avec une moyenne superieure a %.2f:\n", threshold);
    for (int i = 0; i < num_students; i++)
    {
        if (grades[i] > threshold)
        {
            printf("%s %s: %.2f\n", first_names[i], last_names[i], grades[i]);
        }
    }

    int top1 = 0, top2 = 0, top3 = 0;
    for (int i = 1; i < num_students; i++)
    {
        if (grades[i] > grades[top1])
        {
            top3 = top2;
            top2 = top1;
            top1 = i;
        }
        else if (grades[i] > grades[top2])
        {
            top3 = top2;
            top2 = i;
        }
        else if (grades[i] > grades[top3])
        {
            top3 = i;
        }
    }

    printf("Les 3 meilleurs etudiants:\n");
    printf("1. %s %s: %.2f\n", first_names[top1], last_names[top1], grades[top1]);
    if (num_students > 1) printf("2. %s %s: %.2f\n", first_names[top2], last_names[top2], grades[top2]);
    if (num_students > 2) printf("3. %s %s: %.2f\n", first_names[top3], last_names[top3], grades[top3]);

    for (int i = 0; i < MAX_DEPARTMENTS; i++)
    {
        int passed = 0;
        for (int j = 0; j < num_students; j++)
        {
            if (departments[j] == i && grades[j] >= 10)
            {
                passed++;
            }
        }
        printf("Etudiants ayant reussi en %s: %d\n", department_names[i], passed);
    }
}

void search_student()
{
    char name[MAX_NAME];
    printf("Entrez le nom de l'etudiant: ");
    scanf("%s", name);

    for (int i = 0; i < num_students; i++)
    {
        if (strcmp(last_names[i], name) == 0 || strcmp(first_names[i], name) == 0)
        {
            printf("%s %s, Departement: %s, Note: %.2f\n", first_names[i], last_names[i], department_names[departments[i]], grades[i]);
        }
    }
}

void list_department_students()
{
    int dept;
    printf("Entrez le numero du departement (0-4): ");
    scanf("%d", &dept);

    printf("Etudiants du departement %s:\n", department_names[dept]);
    for (int i = 0; i < num_students; i++)
    {
        if (departments[i] == dept)
        {
            printf("%s %s\n", first_names[i], last_names[i]);
        }
    }
}

void sort_students()
{
    int choice;
    printf("1. Tri par nom (A-Z)\n2. Tri par nom (Z-A)\n");
    printf("3. Tri par note (decroissant)\n4. Tri par note (croissant)\n");
    printf("5. Tri par reussite\nChoix: ");
    scanf("%d", &choice);

    for (int i = 0; i < num_students - 1; i++)
    {
        for (int j = 0; j < num_students - i - 1; j++)
        {
            int swap = 0;
            if (choice == 1)
            {
                swap = strcmp(last_names[j], last_names[j+1]) > 0;
            }
            else if (choice == 2)
            {
                swap = strcmp(last_names[j], last_names[j+1]) < 0;
            }
            else if (choice == 3)
            {
                swap = grades[j] < grades[j+1];
            }
            else if (choice == 4)
            {
                swap = grades[j] > grades[j+1];
            }
            else if (choice == 5)
            {
                swap = (grades[j] >= 10) < (grades[j+1] >= 10);
            }

            if (swap)
            {
                int temp_id = student_ids[j];
                student_ids[j] = student_ids[j+1];
                student_ids[j+1] = temp_id;

                char temp_first[MAX_NAME];
                strcpy(temp_first, first_names[j]);
                strcpy(first_names[j], first_names[j+1]);
                strcpy(first_names[j+1], temp_first);

                char temp_last[MAX_NAME];
                strcpy(temp_last, last_names[j]);
                strcpy(last_names[j], last_names[j+1]);
                strcpy(last_names[j+1], temp_last);

                char temp_birth[11];
                strcpy(temp_birth, birth_dates[j]);
                strcpy(birth_dates[j], birth_dates[j+1]);
                strcpy(birth_dates[j+1], temp_birth);

                int temp_dept = departments[j];
                departments[j] = departments[j+1];
                departments[j+1] = temp_dept;

                float temp_grade = grades[j];
                grades[j] = grades[j+1];
                grades[j+1] = temp_grade;
            }
        }
    }

    for (int i = 0; i < num_students; i++)
    {
        printf("%s %s: %.2f\n", first_names[i], last_names[i], grades[i]);
    }
}

int main()
{
    int choice;

    do
    {
      system ("cls") ;
        printf("\n----------|main menu|------------\n");
        printf("\n1. Ajouter un etudiant\n");
        printf("2. Modifier ou supprimer un etudiant\n");
        printf("3. Afficher les details d'un etudiant\n");
        printf("4. Calculer la moyenne generale\n");
        printf("5. Afficher les statistiques\n");
        printf("6. Rechercher un etudiant\n");
        printf("7. Afficher les etudiants d'un departement\n");
        printf("8. Trier les etudiants\n");
        printf("0. Quitter\n");
        printf("Choix: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            add_student();
            break;
        case 2:
            modify_or_delete_student();
            break;
        case 3:
            display_student();
            break;
        case 4:
            calculate_averages();
            break;
        case 5:
            display_statistics();
            break;
        case 6:
            search_student();
            break;
        case 7:
            list_department_students();
            break;
        case 8:
            sort_students();
            break;
        case 0:
            printf("Au revoir!\n");
            break;
        default:
            printf("Choix invalide.\n");
        }
    }
    while (choice != 0);

    return 0;
}
