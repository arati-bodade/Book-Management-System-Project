#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char name[200];
    float price;
    float rating;
    char author[200];
} typedef Book;

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

void addBook(Book** book, int* book_count, int* capacity) {
    printf(BLUE"\nHow many Books do you want to add? : \n"RESET);
    int n;
    scanf("%d",&n);
	

       while(*book_count + n >*capacity){
	      *capacity += 2;  
          printf(GREEN"\nReallocated"RESET);
        *book = realloc(*book, sizeof(Book)*(*capacity));
        if (*book == NULL) {
            printf(RED"Memory allocation failed!\n"RESET);
            exit(1);
        }
    }

 for (int i = 0; i < n; i++) {
        printf(CYAN"\nEnter Book ID: "RESET);
        scanf("%d", &(*book)[*book_count + i].id);

//    printf(CYAN"\nEnter Book ID: "RESET);
//    scanf("%d", &(*book)[*book_count].id);
    
    printf(MAGENTA"\nEnter Book Name: "RESET);
    getchar();
    fgets((*book)[*book_count +i].name, sizeof((*book)[*book_count +i].name), stdin);
    (*book)[*book_count +i].name[strcspn((*book)[*book_count +i].name, "\n")] = 0; 

    printf(CYAN"\nEnter Price: "RESET);
    scanf("%f", &(*book)[*book_count +i].price);
   
    printf(MAGENTA"\nEnter Rating: "RESET);
    scanf("%f", &(*book)[*book_count +i].rating);
    
    printf(CYAN"\nEnter Author Name: "RESET);
    getchar(); 
    fgets((*book)[*book_count +i].author, sizeof((*book)[*book_count +i].author), stdin);
    (*book)[*book_count +i].author[strcspn((*book)[*book_count +i].author, "\n")] = 0; 
}
 *book_count += n; 
//    (*book_count)++;
    printf(GREEN"\nBook added successfully!\n"RESET);
}

void displayAllBooks(Book* book, int book_count) {
    printf(GREEN"\n+++++++++++++ All books in the library: +++++++++++++\n"RESET);
   
    printf("\n ____________________________________________________________________________________________________________");
    printf("\n|  Book Id  |           Book Name               |   Book Price  |   Book Rating  |        Author Name        |");
    printf("\n|-----------|-----------------------------------|---------------|----------------|---------------------------|");
    for (int i = 0; i < book_count; i++) {
        printf("\n| %6d    |   %-31s | %.2f        | %.2f         |  %-24s |",
               book[i].id, book[i].name, book[i].price, book[i].rating, book[i].author);
    }
    printf("\n|___________|___________________________________|_______________|________________|___________________________|\n");
}

void searchBook(Book* book, int book_count) {
    int choice;
    printf(GREEN"Search by (1) ID or (2) Name: "RESET);
    scanf("%d", &choice);
    if (choice == 1) {
        int id;
        printf(MAGENTA"Enter Book ID: "RESET);
        scanf("%d", &id);
        for (int i = 0; i < book_count; i++) {
            if (book[i].id == id) {
                printf(YELLOW"\nBook found : "RESET);
                displayAllBooks(book, book_count);
                return;
            }
        }
    } else if (choice == 2) {
        char name[200];
        printf(MAGENTA"Enter Book Name: "RESET);
        getchar();
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0; 
        for (int i = 0; i < book_count; i++) {
            if (strcmp(book[i].name, name) == 0) {
                printf(YELLOW"\nBook found : "RESET);
                displayAllBooks(book, book_count);
                return;
            }
        }
    }
    printf(RED"Book not found!\n"RESET);
}

void updateBook(Book* book, int book_count) {
    int id;
    printf(MAGENTA"Enter Book ID to update: "RESET);
    scanf("%d", &id);
    for (int i = 0; i < book_count; i++) {
        if (book[i].id == id) {
            printf("Enter new Price:\n");
            scanf("%f", &book[i].price);
            printf("Enter new Rating: \n");
            scanf("%f", &book[i].rating);
            printf(GREEN"Book updated successfully!\n"RESET);
            return;
        }
    }
    printf(RED"Book not found!\n"RESET);
}

void removeBook(Book* book, int* book_count) {
    int id;
    printf(YELLOW"Enter Book ID to remove: "RESET);
    scanf("%d", &id);
    for (int i = 0; i < *book_count; i++) {
        if (book[i].id == id) {
            for (int j = i; j < *book_count - 1; j++) {
                book[j] = book[j + 1];
            }
            (*book_count)--;
            printf(GREEN"Book removed successfully!\n"RESET);
            return;
        }
    }
    printf(RED"Book not found!\n"RESET);
}

void sortBooks(Book* book, int book_count) {
    for (int i = 0; i < book_count - 1; i++) {
        for (int j = 0; j < book_count - i - 1; j++) {
            if (book[j].price > book[j + 1].price) {
                Book temp = book[j];
                book[j] = book[j + 1];
                book[j + 1] = temp;
            }
        }
    }
    printf(BLUE"\n-: Books sorted by Price :-\n"RESET);
    displayAllBooks(book, book_count);

    for (int i = 0; i < book_count - 1; i++) {
        for (int j = 0; j < book_count - i - 1; j++) {
            if (book[j].rating > book[j + 1].rating) {
                Book temp = book[j];
                book[j] = book[j + 1];
                book[j + 1] = temp;
            }
        }
    }
    printf(BLUE"\n-: Books sorted by Rating :-\n"RESET);
    displayAllBooks(book, book_count);
}

int main() {
    int size = 2;
    Book* book = (Book*)malloc(sizeof(Book) * size);
    if (book == NULL) {
        printf(RED"Memory allocation failed!\n"RESET);
        return 1;
    }

    int book_count = 0;
    int capacity = size;
    int choice = 0;

    while (choice != 7) {
        printf(MAGENTA"\n--------------------------------"RESET);
        printf(MAGENTA"\n|       Menu Driven            |"RESET);
        printf(MAGENTA"\n--------------------------------"RESET);
        printf("\n|       1. Add Book            |");
        printf("\n|       2. Display Books       |");
        printf("\n|       3. Search Book         |");
        printf("\n|       4. Update Book         |");
        printf("\n|       5. Remove Book         |");
        printf("\n|       6. Sort Books          |");
        printf("\n|       7. Exit                |");
        printf("\n--------------------------------");
        printf(YELLOW"\n Enter the choice: "RESET);
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(&book, &book_count, &capacity);
			 break;
            case 2: displayAllBooks(book, book_count);
			 break;
            case 3: searchBook(book, book_count);
			 break;
            case 4: updateBook(book, book_count);
			 break;
            case 5: removeBook(book, &book_count);
			 break;
            case 6: sortBooks(book, book_count);
			 break;
            case 7: exit(0);
            default: 
                printf(RED"\n+++++++++ Invalid choice! Please try again +++++++++\n"RESET);
        }
    }
    free(book);
    return 0;
}
