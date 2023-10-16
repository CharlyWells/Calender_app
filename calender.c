#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Event {
    char description[100];
    struct Event* next;
};

struct CalendarDay {
    int day;
    int month;
    int year;
    struct Event* events;
};

void addEvent(struct CalendarDay* day) {
    struct Event* newEvent = (struct Event*)malloc(sizeof(struct Event));
    newEvent->next = NULL;
    printf("Enter event description: ");
    scanf("%s", newEvent->description);

    if (day->events == NULL) {
        day->events = newEvent;
    } else {
        struct Event* currentEvent = day->events;
        while (currentEvent->next != NULL) {
            currentEvent = currentEvent->next;
        }
        currentEvent->next = newEvent;
    }
}

void printEvents(struct CalendarDay* day) {
    struct Event* currentEvent = day->events;
    while (currentEvent != NULL) {
        printf("- %s\n", currentEvent->description);
        currentEvent = currentEvent->next;
    }
}

void searchEvents(struct CalendarDay calendar[], int day, int month, int year) {
    for (int i = 0; i < 31; i++) {
        if (calendar[i].day == day && calendar[i].month == month && calendar[i].year == year) {
            printf("%d/%d/%d:\n", calendar[i].day, calendar[i].month, calendar[i].year);
            printEvents(&calendar[i]);
        }
    }
}

int main() {
    struct CalendarDay calendar[31];
    for (int i = 0; i < 31; i++) {
        calendar[i].day = 0;
    }

    int choice;
    while (1) {
        printf("\nCalendar Menu:\n");
        printf("1. Add Event\n");
        printf("2. Print Calendar\n");
        printf("3. Search Events\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int day;
            printf("Enter day (1-31): ");
            scanf("%d", &day);

            if (day < 1 || day > 31) {
                printf("Invalid day. Day should be between 1 and 31.\n");
            } else {
                struct CalendarDay* selectedDay = &calendar[day - 1];
                printf("Enter month (1-12): ");
                scanf("%d", &selectedDay->month);
                printf("Enter year: ");
                scanf("%d", &selectedDay->year);
                addEvent(selectedDay);
                printf("Event added for %d/%d/%d.\n", selectedDay->day, selectedDay->month, selectedDay->year);
            }
        } else if (choice == 2) {
            printf("\nCalendar:\n");
            for (int i = 0; i < 31; i++) {
                if (calendar[i].day != 0) {
                    printf("%d/%d/%d:\n", calendar[i].day, calendar[i].month, calendar[i].year);
                    printEvents(&calendar[i]);
                }
            }
        } else if (choice == 3) {
            int searchDay, searchMonth, searchYear;
            printf("Enter day (1-31): ");
            scanf("%d", &searchDay);
            printf("Enter month (1-12): ");
            scanf("%d", &searchMonth);
            printf("Enter year: ");
            scanf("%d", &searchYear);
            searchEvents(calendar, searchDay, searchMonth, searchYear);
        } else if (choice == 4) {
            break;
        } else {
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    for (int i = 0; i < 31; i++) {
        struct Event* currentEvent = calendar[i].events;
        while (currentEvent != NULL) {
            struct Event* nextEvent = currentEvent->next;
            free(currentEvent);
            currentEvent = nextEvent;
        }
    }

    return 0;
}

