#include <stdio.h>
#include <stdbool.h>

// Function to check if a given year is a leap year
bool is_leap_year(int year);

// Array storing the number of days in each month
int days_in_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Function to add a specific number of days to a given date
void add_days_to_date(int* mm, int* dd, int* yy, int days_left_to_add);

int main() {
   int mm, dd, yy, days_left_to_add;

   // Prompt the user to enter a date and the number of days to add
   printf("Please enter a date between the years 1800 and 10000 in the format mm dd yy and provide the number of days to add to this date. For example, if you want to add 500 days to March 14, 2021, the input should be entered as follows 3 space 13 space 2021 space 500 enter:");

   // Read the user input
   scanf("%d %d %d %d", &mm, &dd, &yy, &days_left_to_add);

   // Call the function to add days to the date
   add_days_to_date(&mm, &dd, &yy, days_left_to_add);

   // Display the new date after adding the specified number of days
   printf("Your new date is %d %d %d\n", mm, dd, yy);

   /*int year;
   printf("Please type a year between 1800 and 10000 :");
   scanf("%d", &year);
   bool leap_Year = is_leap_year(year);
   if(leap_Year == true){
       printf("This %d year is a leap year", year);
   }else{
       printf("This %d is not a leap year", year);
   }*/

   return 0;
}

// Function to check if a given year is a leap year
bool is_leap_year(int year) {
   return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

// Function to add a specific number of days to a given date
void add_days_to_date(int* mm, int* dd, int* yy, int days_left_to_add){
   int days_left_in_month;

   // Continue adding days until the desired number is reached
   while (days_left_to_add > 0){
       days_left_in_month = days_in_month[*mm] - *dd + 1;

       // If it's February and the year is a leap year, increase the number of days in the month
       if(*mm == 2 && is_leap_year(*yy)){
           days_left_in_month += 1;
       }

       // If the remaining days to add is more than the days left in the current month,
       // move to the next month and update the remaining days accordingly
       if (days_left_to_add > days_left_in_month){
           days_left_to_add  -= days_left_in_month;
           *dd = 1;

           // If it's December, move to January of the next year
           if(*mm == 12){
               *mm = 1;
               *yy = *yy + 1;
           } else {
               *mm = *mm + 1;
           }
       } else {
           // If the remaining days to add is less than or equal to the days left in the current month,
           // simply add those days to the current date and exit the loop
           *dd = *dd + days_left_to_add;
           days_left_to_add = 0;
       }
   }
}
