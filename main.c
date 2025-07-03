#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5  // Maximum capacity of stack and queue

// Structure for a book
typedef struct {
    int id;
    char title[50];
} Book;

// Stack for issued books
typedef struct {
    Book books[MAX];
    int top;
} Stack;

// Queue for returned books
typedef struct {
    Book books[MAX];
    int front, rear, count;
} Queue;

// Function prototypes
void push(Stack *s, Book book);
Book pop(Stack *s);
void enqueue(Queue *q, Book book);
Book dequeue(Queue *q);
void displayIssuedBooks(Stack *s);
void displayReturnedBooks(Queue *q);
void menu();

int main() {
    Stack issuedBooks = {.top = -1};
    Queue returnedBooks = {.front = 0, .rear = -1, .count = 0};

    int choice;
    do {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        Book book;
        switch (choice) {
            case 1:
                if (issuedBooks.top == MAX - 1) {
                    printf("Issue limit reached! Cannot issue more books.\n");
                } else {
                    printf("Enter book ID: ");
                    scanf("%d", &book.id);
                    printf("Enter book title: ");
                    scanf(" %[^\n]", book.title); // Read string with spaces
                    push(&issuedBooks, book);
                    printf("Book issued successfully.\n");
                }
                break;

            case 2:
                if (issuedBooks.top == -1) {
                    printf("No books issued yet!\n");
                } else {
                    book = pop(&issuedBooks);
                    enqueue(&returnedBooks, book);
                    printf("Book '%s' returned successfully.\n", book.title);
                }
                break;

            case 3:
                displayIssuedBooks(&issuedBooks);
                break;

            case 4:
                displayReturnedBooks(&returnedBooks);
                break;

            case 5:
                printf("Exiting the system...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

// Function to issue a book (Push to Stack)
void push(Stack *s, Book book) {
    s->top++;
    s->books[s->top] = book;
}

// Function to return a book (Pop from Stack)
Book pop(Stack *s) {
    return s->books[s->top--];
}

// Function to add a returned book to Queue
void enqueue(Queue *q, Book book) {
    if (q->count == MAX) {
        printf("Return queue is full!\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX;
    q->books[q->rear] = book;
    q->count++;
}

// Function to remove a returned book from Queue
Book dequeue(Queue *q) {
    if (q->count == 0) {
        printf("No returned books available.\n");
        Book empty = {-1, "None"};
        return empty;
    }
    Book book = q->books[q->front];
    q->front = (q->front + 1) % MAX;
    q->count--;
    return book;
}

// Function to display issued books (Stack)
void displayIssuedBooks(Stack *s) {
    if (s->top == -1) {
        printf("No books issued yet.\n");
        return;
    }
    printf("Issued Books (Most recent first):\an");
    for (int i = s->top; i >= 0; i--) {
        printf("ID: %d, Title: %s\n", s->books[i].id, s->books[i].title);
    }
}

// Function to display returned books (Queue)
void displayReturnedBooks(Queue *q) {
    if (q->count == 0) {
        printf("No books returned yet.\n");
        return;
    }
    printf("Returned Books (Oldest first):\n");
    int index = q->front;
    for (int i = 0; i < q->count; i++) {
        printf("ID: %d, Title: %s\n", q->books[index].id, q->books[index].title);
        index = (index + 1) % MAX;
    }
}

// Function to display menu
void menu() {
    printf("\n=== Library Management System ===\n");
    printf("1. Issue a Book\n");
    printf("2. Return a Book\n");
    printf("3. View Issued Books\n");
    printf("4. View Returned Books\n");
    printf("5. Exit\n");
}
