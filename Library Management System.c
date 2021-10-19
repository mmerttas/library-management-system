#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define MAX_USER_NUMBER 500 //For random number generation, the numbers are used to be able to generate good-looking numbers.
#define MAX_BOOK_NUMBER 3000

#define NAME_LEN 75
#define PASS_LEN 75

typedef struct _borrower {

   int userID;
   int bookID;
   struct _borrower *next;
}borrower;

typedef struct _user {

   char name[NAME_LEN];
   int ID;
   char password[PASS_LEN];
   struct _user *next;

}user;

typedef struct _admin {

   char name[NAME_LEN];
   int ID;
   char password[PASS_LEN];
   struct _admin *next;
}admin;

typedef struct _book {

   char name[NAME_LEN];
   char writer[NAME_LEN];
   char publisher[NAME_LEN];
   int ID;
   int pages;
   char type[30];
   int howMany;
   char where[5];
   struct _book *next;
}book;

int getData();
void start();

void showAdmin();
void addAdmin (char *name, int ID, char *password);
void delAdmin ();
int isAdmin (int ID, char *password);
void changePwAd(int ID, char *password);
int isIDTaken(int ID);

void borrowBook(int userID);
void addBorrower(int userID,int bookID);
void returnBook(int userID);
void delBorrower(int userID,int bookID);
void showBorrower();
int findBorrower(int ID);
void showBorrowed(int userID);

void addBook(char *name, char *writer, char *publisher,int ID, int pages, char *type, int howMany,char *where);
int delBook();
int isBorrowed(int bookID);
void showBooks();
void changeBook();
void booksPlace();
void findBook();

void showUsers();
void addUser (char *name,int ID, char *password);
int delUser();
void findUser();
int isUser(int ID,char *password);
void changePwUs(int ID, char *password);

int idGenUser();
int idGenBook();

void saveBook();
void saveUser();
void saveBorrower();
void saveAdmin();

void welcome();
void menu ();

void getstr(char *str, int readMax);
void key();

book *books = NULL;
user *users = NULL;
borrower *borrowers = NULL;
admin *admins = NULL;

char notUsed[3]; //This is used to avoid '\n' characters with the use of fgets function when we are taking multiple strings from user
int main()
{
   start();
   welcome();
   menu();
   return 0;

}

int getData() { //Mert

   char data[256];

   FILE *file1 = fopen("dataBooks.txt","r+"); // Opens the file which contains the data of books
   rewind(file1); // Sets the position of the file1 to the beginning of the file

   // If it doesn't exist, create one
   if (!file1) {
      printf("\nBooks Data was not found. It has been created.\n");
      fopen("dataBooks.txt","a+");
   }

   // If it exists, break the string using "," into name,writer,publisher etc.
   if(file1){
      while (fgets(data,sizeof(data),file1)) {
         char *name = strtok(data,",");
         char *writer = strtok(NULL,",");
         char *publisher = strtok(NULL,",");
         int ID = atoi(strtok(NULL,","));
         int pages = atoi(strtok(NULL,","));
         char *type = strtok(NULL,",");
         int howMany = atoi(strtok(NULL,","));
         char *where = strtok(NULL,",");

         addBook(name,writer,publisher,ID,pages,type,howMany,where);
       }
       fclose(file1); // Close the file1
   }
   FILE *file2 = fopen("dataUsers.txt","r+"); // Open the file that contains the data of the users
   rewind(file2); // Sets the position of the file2 to the beginning of the file

   // If it doesn't exist, create one
   if (!file2) {
      printf("\nUsers Data was not found. It has been created.\n");
      fopen("dataUsers.txt","a+");
   }

   // If it exists, break the string using "," into name,id and the password of the user
   if (file2){
      while (fgets(data,sizeof(data),file2)) {
         char *name = strtok(data,",");
         int ID = atoi(strtok(NULL,","));
         char *password = strtok(NULL,",");

         addUser(name,ID,password); // calls the addUser function and saves the user infos.
      }
      fclose(file2); // Close the file2
   }
   FILE *file3 = fopen("dataBorrowers.txt","r+"); // Open the file that contains the data of the borrowers
   rewind(file3); // Sets the position of the file3 to the beginning of the file

   // If it doesn't exist, create one
   if (!file3) {
      printf("\nBorrowers Data was not found. It has been created.\n");
      fopen("dataBorrowers.txt","a+");
   }

   // If it exists, break the string using "," into user id and the book id.
   while(fgets(data,sizeof(data),file3)) {
      int userID = atoi(strtok(data,","));
      int bookID = atoi(strtok(NULL,","));

      addBorrower(userID,bookID); // Calls the addBorrower function and saves the borrower and the taken books.
   }
   fclose(file3); // Close file3

   FILE *file4 = fopen("dataAdmins.txt","r+"); //Open the file that contains the data of the admins
   rewind(file4); // Sets the position of the file3 to the beginning of the file

   // If it doesn't exist, create one
   if (!file4) {
      printf("\nAdmins Data was not found. It has been created.\n");
      fopen("dataAdmins.txt","a+");
   }

   // If it exists, break the string using "," into admin name, admin id and the admin password.
   if (file4){
   while (fgets(data,sizeof(data),file4)) {
      char *adminName = strtok(data,",");
      int adminID = atoi(strtok(NULL,","));
      char *adminPW = strtok(NULL,",");

      addAdmin(adminName,adminID,adminPW); //Calls the addAdmin function and saves the information of the admins.
   }
   fclose(file4); // Close file4
   }
   printf("\n\n\n\n%70s","Press a key to start the program.");
   getch(); // gets the key value.
   return 0;
}

void start(){ //Ahmet

   addAdmin("Principal",10,"1234asd"); //To be able to start with an admin when there is no data of admins, there is a principal who has the whole authority of
   srand(time(NULL));                                                                                                                     //the library.
   system("chcp 65001");
   system("CLS");
   getData(); //Program starts with the previous data

   return;
}

void showAdmin(){ //Ahmet

   admin *iter = admins;
   //If iter is null, which means there are no admins:
   if(!iter){
      printf("There are no admins other that you in the library now \u2573 \u2573\n\n");
   }
   printf("\nADMINS INFORMATION\n\n");
   //Iteration of admins continues until iter is null
   while (iter !=NULL) {
      for(int i=0;i<40;i++){
         printf("\uFFEE"); //To have a better visuality, unicodes.
      }
      //Prints the admin's information
      printf("\n\nName: %s\n",iter->name);
      printf("ID: %d\n\n",iter->ID);
      iter = iter->next; //Goes next admin
   }
   for(int i=0;i<40;i++){
         printf("\uFFEE");
   }
   return;
}

void addAdmin (char *name, int ID, char *password) { //Ahmet

   admin *temp = (admin *)malloc(sizeof(admin)); //Allocates memory for the new admin
   //Copies the given name, ID and password to the new admin
   strcpy(temp->name,name);
   temp->ID = ID;
   strcpy(temp->password,password);
   //Adds the admin to linkedlist
   temp->next = admins;
   admins = temp;
}

void delAdmin(){ //Ahmet

   int ID;
   printf("\nEnter the ID of the administrator that you want to delete: ");
   scanf("%d",&ID);

   admin *iter = admins;
   admin *former = NULL;
   //If iter is null, which means there are no admins:
   if (iter == NULL) {
      printf("\nThere are no admins other than you \u2573 \u2573\n");
      return;
   }
   //The iteration of admins continues until the pointer is null
   while (iter) {
      if (iter->ID == ID) { //When the given ID and iteration's ID are matched:
         if (former != NULL) {
            former->next = iter->next; //Deletes the admin who is in the middle of the linked list
         }
         else {
            admins = iter->next; //Deletes the admin who is first item of the linked list
         }
         free(iter); //Frees the memory
         printf("\nAdmin with the ID %d has been deleted \u2713\n",ID);
         return;
      }
      former = iter; //Iteration continues until the pointer iter is null..
      iter = iter -> next;
   }

   printf("\nThere is no admin with the ID %d \u2573 \u2573\n",ID); //If there are no matching admins, this line works.

   return;
}

int isAdmin (int ID, char *password) { //Ahmet

   admin *iter = admins;
   //Tries to find the ID in the iteration of admins
   while (iter->ID != ID && iter->next != NULL){
      iter = iter->next;
   }
   if (iter->ID == ID){ //When the IDs are matched,
      if(!strcmp(password,iter->password)){ //Passwords are compared each other. If they are matching, admin is now entered to the managing system.
         printf("\n%55s %s\n\n","Welcome",iter->name);
         printf("%75s","Please press a key to continue.\n");
         getch();
         return 1;
      }
      printf("%75s","\nWrong password. Please press a key \u2573 \u2573\n"); //If passwords do not match, this line works.
      getch();
      return 0;
   }
   else { //If the ID is not found in the iteration
      printf("%75s","\nNo admins with the ID. Please press a key \u2573 \u2573\n");
      getch();
      return 0;
   }

}

void changePwAd(int ID, char *password){ //Ahmet
   char pass[PASS_LEN];
   printf("Enter your current password: ");
   scanf("%s",pass);
   if(!strcmp(password,pass)){ //If the admin enters password truly, s/he can change the password. Else, s/he is warned and turned back to menu
      char newPw1[PASS_LEN],newPw2[PASS_LEN];
      printf("\nSPACE IS NOT ALLOWED\n");
      printf("\nEnter your new password: ");
      scanf("%s",newPw1);
      printf("\nEnter your new password again: ");
      scanf("%s",newPw2);
      if(!strcmp(newPw1,newPw2)){ //Compares the two given passwords. If they are not matching, warns the admin.
         admin *iter = admins;
         while(iter->ID != ID){ //Iteration starts and continues until it finds the admin in the linked list of admins
            iter = iter->next;
         }

         strcpy(iter->password,newPw1); //Changes the password.

         printf("\nYour password will be changed successfully after you save and exit.");
         return;
      }
      printf("\nYour passwords do not match each other.\n"); //If the two given passwords do not match, this line works.
   }
   else{
      printf("\nYou have entered your current password wrong.\n");
   }
   return;
}

int isIDTaken(int ID){ //Ahmet
   //The function to use at registering new admin, admins are able to take their own IDs. However, there must be a restriction: It should not be taken.
   admin *iter = admins;

   while(iter != NULL && iter->ID != ID){ //Checks the given ID if it is taken or not
      iter = iter->next;
   }

   if(iter){
      return 1; //If iter is not null, it means the ID is taken. Returns 1.
   }

   return 0; //The given ID is not taken, returns 0.
}

void borrowBook(int userID){ //Mert

   book *list=books;
   user *listu=users;


   while(listu){
      //If ID in the user list is same with the userID exit the loop
      if(listu->ID == userID){
         break;
      }
      //In case of not, check the next one
      listu = listu->next;
   }

  int idb=0;
  printf("Please write the ID of the book that you want to borrow: ");
  scanf("%d",&idb); //Gets the book id that want to be borrowed

  // If books in the list are null call the key function and warn the user
  if (books == NULL) {
      printf("\nNo book in the library.");
      key();
      return;
   }

   while(list){
      //If book id is same with the one in the book list decrease the number of the book.
      if(list->ID==idb){

         int newNum = list->howMany;
         //If the number of the book is different than zero.
         if(newNum){
            newNum--;
            list->howMany = newNum;
            addBorrower(listu->ID,list->ID); //Calls addBorrower function to add a new borrower.
            printf("\nThe book has been assigned to you, you can get it after you save and exit.");
            key();//Calls the key function and wants user to press any key.
            return;
         }
         else{//If the number of the available book is zero warn the user.
            printf("\nThe book with the ID is not available now. (Zero count).");
            key();//Calls the key function and wants user to press any key.
            return;
         }
      }
      else{// If the ids are different check the next one.
         list = list->next;
      }
   }
   printf("\nThere is no book with the ID that you have entered.\n"); // Warn the user in case of no same id with the entered one
   key();//Calls the key function and wants user to press any key.
   return;
}

void addBorrower(int userID, int bookID){ //Mert

   borrower *list = (borrower *)malloc(sizeof(borrower));

   list->bookID = bookID;
   list->userID = userID;

   list->next = borrowers;
   borrowers = list;
   return;
}

void returnBook(int userID){ //Mert

   book *list=books;
   borrower *listborr=borrowers;

   while(listborr){
      //If ID is same with user id leave the loop
      if(listborr->userID == userID){
         break;
      }

      //In case of not being same check the next one
      listborr = listborr->next;
   }
   if(!listborr){ //If the user is not a borrower:
      printf("\nYou are not a borrower.\n");
      key();
      return;
   }

   int idb=0;
   printf("Please write the ID of the book that you want to return: ");
   scanf("%d",&idb); //Scan the id of the book that want to be returned

   // In case of book list to be null
   if (books == NULL) {
      printf("\nNo book in the library.");
      key(); //Calls the key function and wants user to press any key
      return;
   }

   while(list){

      //If ID is same with the book id that wants to be returned increase the number of it
      if(list->ID==idb){
         int newNum = list->howMany;
         newNum++;
         list->howMany = newNum;
         delBorrower(listborr->userID,list->ID); // delete the borrower from the borrower list
         printf("\nThanks for returning the book. The book will be returned after you save and exit.\n");
         key(); //Calls the key function and wants user to press any key
         return;
      }
      else{
         list = list->next; //If ids are not same check the next one
      }
   }

   printf("\nThere is no book with the ID that you have entered.\n"); //In case of entered id doesn't exist warn the user
   key(); //Calls the key function and wants user to press any key
   return;
}

void delBorrower(int userID,int bookID){ //Mert

   borrower *list = borrowers;
   borrower *former = NULL;

   // Checks the borrower list is null or not
   if (borrowers == NULL) {
      printf("\nThere are no borrowers \u2573 \u2573\n");
      return;
   }

   while (list) {

      //If userID is same with the userID in the list and the former is not Null
      if (list->userID == userID) {

         if (former != NULL) {
            former->next = list->next;
         }
         else {///////////////////////////////////////
            borrowers = list->next;
         }
         free(list);
         printf("\nProcess is successful \u2713\n");
         return;
      }
      former = list;
      list = list -> next;
   }

   printf("\nThere is no borrower with the ID %d \u2573 \u2573\n",userID);

   return;
}

void showBorrower(){ //Ahmet
   borrower *iter = borrowers;
   if(!borrowers){  //If the pointer iter is null, which means there are no borrowers:
      printf("There are no borrowers in the library now \u2573 \u2573\n\n");
   }
   printf("\nBORRROWER ID - BOOK ID\n\n");
   //Prints the borrower's information and iteration of borrowers goes next until it is null
   while (iter !=NULL) {
      for(int i=0;i<20;i++){
         printf("\u2510\u2514");
      }
      printf("\n\nBorrower ID: %d - ",iter->userID);
      printf("Book ID: %d\n\n",iter->bookID);
      iter = iter->next;
   }
   for(int i=0;i<20;i++){
         printf("\u2510\u2514");
   }
   return;
}

int findBorrower(int ID){ //Ahmet

   int flag = 1;
   borrower *iter = borrowers;
   //Starts the iteration of borrowers and continues until iter is null
   while(iter!=NULL){
      if(iter->userID == ID){ //When the given ID matched the usedID of the pointer iter:
         printf("\nUser with the ID has borrowed the book with the ID: %d",iter->bookID);
         flag = 0;
      }
      iter = iter->next;
   }
   if(flag){ //If flag value has not been changed to 0, this means the user with the ID did not borrow any books.
      printf("\nThere is no borrower with the ID.");

      return 1;
   }
   return 0;
}

void showBorrowed(int userID){ //Mert
   borrower *borrowedlist = borrowers;
   int flag = 0; //control flag

   while(borrowedlist){ //searchs borrowers

      if(borrowedlist->userID == userID){// when finds the searched borrower print the borrowed book

         printf("You have borrowed the book with the ID: %d\n",borrowedlist->bookID);
         flag = 1; //change the flag to 1
      }
      borrowedlist=borrowedlist->next; // go to the next borrower
   }
   if (flag==0){ // if the flag has not changed that means the user with the userID is not a borrower
      printf("\nYou have not borrowed any book yet!\n");
   }
   return;
}

void addBook(char *name, char *writer, char *publisher,int ID, int pages, char *type, int howMany,char *where) { //Ahmet

   book *temp = (book*)malloc(sizeof(book)); //Memory is allocated for the new book

   //The books given information name, writer, publisher, ID, pages, type, how many and location of the books are copied to the item
   strcpy(temp->name,name);
   strcpy(temp->writer,writer);
   strcpy(temp->publisher,publisher);
   temp->ID = ID;
   temp->pages = pages;
   strcpy(temp->type,type);
   temp->howMany = howMany;
   strcpy(temp->where,where);

   //It is added to linked list of books
   temp->next = books;
   books = temp;
   return;
}

int delBook() { //Ahmet
   int ID;
   printf("\nEnter the ID of the book that you want to delete:");
   scanf("%d",&ID); //Gets the ID of the book to delete

   book *iter = books;
   book *former = NULL;

   //If iter is null, which means no book in the library:
   if (iter == NULL) {
      printf("\nNo book in library \u2573 \u2573");
      return 0;
   }
   //The iteration of books continues until the pointer is null
   while (iter) {
      if (iter->ID == ID) { //Finds the ID of the book
         if(isBorrowed(ID)){ //Checks if it was borrowed with the function isBorrowed. If it is borrowed, the book cannot be deleted.
            if (former != NULL) {
               former->next = iter->next; //Deletes the book in-between the pointers.
            }
            else {
               books = iter->next; //Deletes the first item of the iteration.
            }
            free(iter); //Free's the memory, it has been deleted.
            printf("\nThe book with the ID %d has been deleted \u2713",ID);
            return 0;
         }
         else{
            return 0;
         }
      }
      former = iter; //If it cannot be found, tries the next books
      iter = iter -> next;
   }

   printf("\nThere is no book which has the ID %d \u2573 \u2573\n",ID);
   return 0;
}

int isBorrowed(int bookID){ //Ahmet
   borrower *iter = borrowers;
   //Iteration of borrowers continues until it finds the bookID in an element of borrowed books
   while(iter != NULL && iter->bookID != bookID){
      iter = iter->next;
   }
   //If the pointer is not null, it means the book with the bookID is borrowed by someone, which means it cannot be deleted.
   if(iter){
      printf("\nThe book is now borrowed by the user with the ID %d",iter->userID); //Prints the message, it cannot be deleted.
      return 0;
   }

   return 1;
}

void showBooks() { //Mert

   book *list = books;
   printf("\nALL BOOKS:\n");

   // while list is not null show the data of all of the books.
   while (list != NULL) {
      for (int i=0;i<40;i++){
      printf("\u2583"); // unicode design of user interface
      }
      printf("\n\nID: %d\n"
             "\nName: %s\n"
             "Writer: %s\n"
             "Publisher: %s\n"
             "Pages: %d\n"
             "Type: %s\n"
             "Available to use: %d\n"
             "The book/s are in %s\n\n",list->ID,list->name,list->writer,list->publisher,list->pages,list->type,list->howMany,list->where);
      list = list->next;
   }
   for (int i=0;i<40;i++){
      printf("\u2583"); // unicode design of user interface
   }
   return;
}

void changeBook(){ //Ahmet
   char where[5];
   int ID;
   booksPlace(); //Shows all books' place
   printf("\nEnter the book's ID that you want to replace: ");
   scanf("%d",&ID); //Gets the ID of the book to be replaced
   printf("\nEnter the books new place: ");
   scanf("%s",where); //Gets the new place of the book
   book *iter = books;
   //Tries to find the book in the book list
   while (iter != NULL && iter->ID != ID){
      iter = iter->next;
   }
   //If the book with the given ID is not found:
   if (!iter){
      printf("\nYou have entered a false ID \u2573 \u2573\n");
      return;
   }
   strcpy(iter->where,where); //Replaces the book
   printf("\nThe book has been placed to %s\n \u2713\n",iter->where);
   return;

}

void booksPlace() { //Ahmet
   book *iter = books;
   printf("\nBOOKS:\n\nID - BOOK - PLACE - COUNT\n\n");
   for(int i=0;i<25;i++){
      printf("\u259A\u259E"); //Characters to have a better visuality
   }
   printf("\n");
   //The loop runs until the last book
   while (iter != NULL) {
      printf("\n%d - %s - %s - %d\n",iter->ID, iter->name, iter->where, iter->howMany); //Prints the information of the books' place
      iter = iter->next;
   }
   for(int i=0;i<25;i++){
      printf("\u259A\u259E");
   }
   return;
}

void findBook(){ //Mert
   char name[NAME_LEN];
   fgets(notUsed,3,stdin); //to be able to use the function getstr
   printf("\nPlease write a keyword for the book:");
   getstr(name,NAME_LEN); // scan the keyword (name)
   book *list = books;
   char *ptr = NULL;
   int flag = 1; // error recognition flag

   // while list is not null.
   while (list != NULL){
      char temp[NAME_LEN];
      strcpy(temp,list->name); // copy the name in list to temp
      ptr = strstr(strupr(temp),strupr(name)); // with strstr function tries to find the sequence of characters that match with each other.
                                               // make uppercase both of temp and name (to deal with uppcs,lwrcs issue)

      // if they match print the data of the matched book
      if (ptr) {
         for(int i=0;i<20;i++){
            printf("\u2571\u2572"); // unicode design of user interface
         }
         printf("\n\nName: %s\n"
                "Writer: %s\n"
                "Publisher: %s\n"
                "ID: %d\n"
                "Pages: %d\n"
                "Type: %s\n"
                "Available to use: %d\n"
                "The book/s are in %s\n\n",list->name,list->writer,list->publisher,list->ID,list->pages,list->type,list->howMany,list->where);
         flag = 0; // flag equals zero (there are matched values)
      }

      list = list->next;
   }

   // if flag is 1 (there are no matched value)
   if(flag){
      printf("\nThere are no books contains the word/s \u2573 \u2573\n");
   }
   for(int i=0;i<20;i++){
      printf("\u2571\u2572"); // unicode design of user interface
   }

   return;
}

void showUsers(){ //Ahmet
   user *iter = users;
   if(!users){      //If the pointer iter is null, which means no user:
      printf("There are no users in the library now \u2573 \u2573\n\n");
   }
   printf("\nUSER INFORMATION\n\n");

   //Prints the information of users and iteration of users goes to the next one until it is null
   while (iter !=NULL) {
      for(int i=0;i<20;i++){
         printf("\u256D\u256E");
      }
      printf("\n\nName: %s\n",iter->name);
      printf("ID: %d\n\n",iter->ID);
      iter = iter->next;
   }
   for(int i=0;i<20;i++){
         printf("\u256D\u256E");
   }
   return;
}

void addUser (char *name,int ID, char *password) { //Ahmet

   user *temp = (user *)malloc(sizeof(user)); //Allocates memory for the new user

   //Copies the given name, ID and password
   strcpy(temp->name,name);
   temp->ID=ID;
   strcpy(temp->password,password);

   //Adds the new user to linked list
   temp->next = users;
   users = temp;

   return;
}

int delUser() { //Ahmet
   int ID;
   printf("\n\nEnter the ID of the user that you want to delete.\n");
   scanf("%d",&ID);
   user *iter = users;
   user *former = NULL;
   //If there are no users, iter is null:
   if (iter == NULL) {
      printf("\nThere are no users \u2573 \u2573\n");
      return 0;
   }
   //This loop runs until iteration of users is null
   while (iter) {
      if (iter->ID==ID) { //If the
         if(findBorrower(ID)){ //Checks if the user is a borrower. If s/he is a borrower, it is not possible to delete the account.
            if (former != NULL) {
               former->next = iter->next; //Deletes the user if s/he is in the middle of somewhere in the linked list.
            }
            else {
               users = iter->next;  //Deletes the user if s/he is the first item of the linked list
            }
            free(iter); //Frees the memory
            printf("\nUser with the ID %d has been deleted \u2713\n",ID);
            return 0;
         }
         else{
            return 0;
         }
      }
      former = iter; //Iteration continues until it finds the ID
      iter = iter -> next;
   }

   printf("\nThere is no user with the ID %d \u2573 \u2573\n",ID); //If the ID is not found, this line works.

   return 0;
}

void findUser(){ //Ahmet

   char name[NAME_LEN];
   fgets(notUsed,3,stdin); //To be able to use getstr
   printf("\nEnter a Name: ");
   getstr(name,NAME_LEN); //Gets the name of the user to find him/her
   user *iter = users;
   char *ptr = NULL;
   int flag = 1;
   //Iteration of users starts and continues until the pointer is null
   while (iter != NULL){
      char temp[NAME_LEN];
      strcpy(temp,iter->name); //Copies the name of the user to temp
      ptr = strstr(strupr(temp),strupr(name)); //Tries to find the given name in the user name. They are converted to uppercase to be able to find better when it is
      if (ptr) {                                                                                                        //entered like charles, CHARLES, chArlEs etc.
         ////If pointer is not null, it means there are some matching characters in the given name, prints the names and IDs.
         printf("Name: %s\n"
                "ID: %d\n\n",iter->name,iter->ID);
         flag = 0;
      }

      iter = iter->next;
   }

   if(flag){ //If there are no users matching, flag value is still 1, which means:
      printf("\nThere are no users who have the name \u2573 \u2573\n");
   }
   return;
}

int isUser(int ID,char *password){ //Mert
   user *list = users;

   //While ID is not equal to the id in the users, go to the next
   while (list->ID != ID && list->next != NULL){
      list = list->next;
   }
   //If ID is equal to the id in the user list
   if (list->ID == ID){
      //Compares the password and the user password if they are same prints welcome...
      if(!strcmp(password,list->password)){
         printf("\n%55s %s","Welcome",list->name);
         printf("\nPlease press a key to continue.\n");
         getch(); //Gets the pressed key
         return 1;

      }else{ //if they don't match warn the user about it
         printf("%75s","\nWrong password. Please press a key \u2573 \u2573\n");
         getch();
         return 0;}
   }
   else{
      //if they don't match warn the user about it
      printf("%75s","\nNo users with the ID. Please press a key \u2573 \u2573\n");
      getch();
      return 0;
   }
   return 0;
}

void changePwUs(int ID, char *password){ //Mert
   char userPW[PASS_LEN];
   printf("\nEnter your password which you are using now: ");
   scanf("%s",userPW); //Gets the user's password
   if(strcmp(userPW,password)){ //If user enters wrong password, process is finished. He or she turns back to menu.
      printf("\nYou have entered your password wrong.\n");
      return;
   }
   char newPw1[PASS_LEN],newPw2[PASS_LEN]; // 2 char arrays for passwords one of them is for new password and the other one is for confirmation.
   printf("\nSPACE IS NOT ALLOWED\n"); // User warning.
   printf("\nEnter your new password: ");
   scanf("%s",newPw1); // Get the new password.
   printf("\nEnter your new password again: ");
   scanf("%s",newPw2); // Get the new password again.

   // if newPw1 and newPw2 matches with each other.
   if(!strcmp(newPw1,newPw2)){
      user *list = users;

      //It goes through the list until it finds the user id.
      while(list->ID != ID){
         list = list->next;
      }

      strcpy(list->password,newPw1); //Changes the password (string) with new one.

      printf("\nYour password will be changed successfully after you save and exit.");

   }else{
     printf("\nYour passwords do not match each other."); // If newPw1 and newPw2 don't match with each other, it warns the user
     return;
   }
}

int idGenUser() { //Ahmet
   user *iter = users;
   int number;

   do {
      number = 2001 + rand() % (MAX_USER_NUMBER); //Creates a number for the new user
      while (iter != NULL && iter->ID != number) { //Tries to find the ID in the other users. If it finds, generates a new number for the user in the loop.
         iter = iter->next;
      }
   } while (iter);

   return number; //Returns the generated number as ID
}

int idGenBook() { //Ahmet
   book *iter = books;
   int number;
   do {
      number = 10001 + rand() % (MAX_BOOK_NUMBER); //Generates a number for the new book
      while (iter != NULL && iter->ID != number) { //Tries to find the number in the other books' IDs. If there is a matching ID, creates new one in the loop.
         iter = iter->next;
      }
   } while (iter);

   return number; //Returns the ID
}

void saveBook(){ //Ahmet
   book *bookiter = books;
   FILE *fileSave1 = fopen("dataBooks.txt","w"); //The file is opened in write mode to save everything
   //Iteration of books continues until the pointer is null
   while (bookiter != NULL) {
      char ID[20]="0", pages[10]="0", howMany[10]="0";
      //Copies the integer values as a string to the given buffers.
      sprintf(ID,"%d",bookiter->ID);
      sprintf(pages,"%d",bookiter->pages);
      sprintf(howMany,"%d",bookiter->howMany);
      char *data1[8] = {bookiter->name,bookiter->writer,bookiter->publisher,ID,pages,bookiter->type,howMany,bookiter->where}; //The array of pointers takes the
      for (int i=0; i<8; i++) {                                                                                               //information of the books' in it
         fputs(data1[i],fileSave1); //Writes the string to the file
         fputs(",",fileSave1);    //Puts "," to be able to read when we are tokenizing the string
      }
      fputs("\n",fileSave1);  //Creates a new line for the new book
      bookiter = bookiter->next; //Continues with the new book
   }
   fclose(fileSave1); //Closes the file
   return;
}

void saveUser(){ //Mert
   user *userlist = users; //

   FILE *fileSave2 = fopen("dataUsers.txt","w"); // Open dataUsers file in write mode

   // While userlist is not null
   while (userlist!= NULL) {
      char ID[20];
      sprintf(ID,"%d",userlist->ID); /////////////////////////////////////////////
      char *data2[3] = {userlist->name,ID,userlist->password}; //Put id, name and password in userlist onto data2 char array

      //Save id,name and password informations in data2 to dataUsers
      for (int j=0; j<3; j++) {
         fputs(data2[j],fileSave2);
         fputs(",",fileSave2); // Separate them with comma
      }
      fputs("\n",fileSave2); // Go to the next line in the file
      userlist = userlist->next;
   }
   fclose(fileSave2); // Close the dataUsers file
   return;
}

void saveBorrower(){ //Mert
   borrower *borrowlist = borrowers;

   FILE *fileSave3 = fopen("dataBorrowers.txt","w"); // Open dataBorrowers file in write mode

   // While borrowlist is not null
   while (borrowlist != NULL) {
      char userID[20], bookID[20];
      sprintf(userID,"%d",borrowlist->userID);
      sprintf(bookID,"%d",borrowlist->bookID);
      char *data3[2] = {userID,bookID}; // Put user and book id's onto data3 char array

      // Save user and book id's onto dataBorrowers file
      for (int k=0; k<2; k++) {
         fputs(data3[k],fileSave3);
         fputs(",",fileSave3); // Separate them with commas
      }
      fputs("\n",fileSave3); // Go to the next line in the file
      borrowlist = borrowlist->next;
   }
   fclose(fileSave3); //Close the dataBorrowers file
   return;
}

void saveAdmin() { //Ahmet
   admin *adminiter = admins;

   FILE *fileSave4 = fopen("dataAdmins.txt","w"); //Opens the file in write mode

   //The iteration of admins continues until the pointer is null
   while (adminiter!=NULL) {
      if ( adminiter->ID == 10){ //When it comes to principal's information, it is passed. Because we do not want it to be written again and again.
         adminiter = adminiter->next;
         continue;
      }
      char ID[20];
      sprintf(ID,"%d",adminiter->ID); //Copies the admin's ID to the buffer
      char *data4[3] = {adminiter->name,ID,adminiter->password}; //The array of pointers takes the information in it
      for (int l=0; l<3; l++) {
         fputs(data4[l],fileSave4); //Writes it to the file
         fputs(",",fileSave4);  //To be able to read, puts "," at the end of every string
      }
      fputs("\n",fileSave4); //Goes to a new line for the new book
      adminiter = adminiter->next; //Goes to the following admin's info
   }
   fclose(fileSave4); //Closes the file
   return;
}

//General interface.
void welcome() { //Mert
   char *uc = "\u2551";
   printf("%45s","\u2554");
   for (int k=0; k<35; k++) {
      printf("\u2550");  // Welcome menu frame design with unicode u2550.
   }
   printf("\u2557");
   printf("\n");
   for (int i=0;i<3;i++) {
      printf("%45s%38s\n",uc,uc);
      if (i==0) {
         printf("%45s%s\n%45s%s\n%45s%s\n%45s%s\n%45s%s",
                uc,"    Welcome to The Library.        \u2551",
                uc,"    1 --> Administrator Login      \u2551",
                uc,"    2 --> User Login               \u2551",
                uc,"    3 --> Sign Up                  \u2551",
                uc,"    Q --> Exit                     \u2551\n");
      }
   }
   printf("%45s","\u255A");
   for (int j=0; j<35; j++) {
      printf("\u2550");  // Welcome menu frame design with unicode u2550
   }
   printf("\u255D\n");
   return;
}

void menu () { //Admin ---> Ahmet       User ---> Mert           New User ---> Mert
   menu1: //General Menu label
   system("CLS");
   welcome();
   char a = getch();
   if(a == 'q'){ //In case of pressing 'q', converts it to 'Q'
      a = 'Q';
   }
   if ((a<'1' || a>'3') && a!='Q' ){ //In case of pressing other than the keys 1,2,3 and Q, the program warns the user
         printf("You have entered wrong.\n");
         key();
         goto menu1;
      }
   if (a == '1') { //If admin menu is chosen by the enterer
      system("CLS");
      welcome();
      int enteredID; //ID and password are kept here
      char password[PASS_LEN];
      printf("%71s","Enter your ID (Only digits): ");
      scanf("%d",&enteredID); //Gets ID
      printf("%63s","Enter your password: ");
      scanf("%s",password); //Gets password

      if(isAdmin(enteredID,password)){ //Checks if the enterer is an admin. If s/he is not, turns back to label menu1 (General Menu)
         menu2: //Label of Administrator Menu
         system("CLS");
         //Admin menu interface
         printf("\n%80s","Welcome To The Library Management System\n\n");
         printf("\u2591\u2591\u2591\u2591\u2591\u2591\u2592\u2592\u2592\u2592\u2592\u2592\u2593\u2593\u2593\u2593\u2593\u2593"
                   "\u2593\u2593\u2593\u2592\u2592\u2592\u2592\u2592\u2592\u2592\u2592\u2592\u2591\u2591\u2591\u2591\u2591\u2591\n\n"
                   " 1 ---> Manage Admins\n\n"
                   " 2 ---> Manage Users\n\n"
                   " 3 ---> Manage Borrowers\n\n"
                   " 4 ---> Manage Books\n\n"
                   " 5 ---> Change Your Password\n\n"
                   " Q ---> Save and Exit\n\n\n"
                   "\u2591\u2591\u2591\u2591\u2591\u2591\u2592\u2592\u2592\u2592\u2592\u2592\u2593\u2593\u2593\u2593\u2593\u2593"
                   "\u2593\u2593\u2593\u2592\u2592\u2592\u2592\u2592\u2592\u2592\u2592\u2592\u2591\u2591\u2591\u2591\u2591\u2591\n");
         printf("Your Choice: ");
         /* In this function "menu", we have used the choices like strings to be able to quit with Q. Also, we have faced some problems when we use the functions
         scanf, getchar, getch. Because we use the function fgets in our getstr function to be able to get multiple strings , the enter keys that have been
         pressed before are leading some problems like not letting us to get first string, it passes empty. We could find the solution as taking the choices like
         strings, if the string is longer than 1 character (the choice is something like 12,20,1a,2g...) we warn the user. Later on this code, there are some lines
         as "fgets(notUsed,3,stdin)" to be able to use getstr function, avoiding the previously pressed enter keys is possible with it*/

         char adminChoice[2]; //Gets the choice of admin
         scanf("%s",adminChoice);
         if(strlen(adminChoice) > 1 ){ //If admin enters longer than 1 character
            printf("\nYou have entered wrong.\n");
            key();
            goto menu2;
         }
         if (adminChoice[0] == 'q'){ //If the choice is 'q', convert it to 'Q'
            adminChoice[0] = 'Q';
         }
         switch (adminChoice[0]){
            case '1': ; //"Managing Admins" interface label
               adminsm: ;
               system("CLS");
               printf("\n%70s","MANAGE ADMINS\n\n");
               for(int i=0;i<45;i++){
                  printf("\u25CD");
               }
               printf("\n\n 1 ---> See All Admins\n\n"
                   " 2 ---> Add Administrator (PRINCIPAL ONLY)\n\n"
                   " 3 ---> Delete Administrator (PRINCIPAL ONLY)\n\n"
                   " M ---> Back to Main Menu\n\n");
               for(int j=0;j<45;j++){
                  printf("\u25CD");
               }
               printf("\nYour Choice: ");
               char c1[2];
               scanf("%s",c1); //Admin's choice is taken
               if(strlen(c1)>1){ //If admin enters longer than 1 char
                  printf("\nYou have entered wrong.\n");
                  key();
                  goto adminsm;
               }
               if(c1[0] == 'm'){ //If it is 'm', it is converted to 'M'
                  c1[0] = 'M';
               }
               switch(c1[0]){
                  case '1': ; //Shows all admins with the function showAdmin
                     showAdmin();
                     key(); //Gets a key to turn back
                     goto adminsm;
                     break;
                  case '2': ;
                     //In this program, adding and deleting admins are only in responsibility of the principal. His/her ID is 10 and it is controlled if the entered
                     //admin is principal or not
                     if (enteredID != 10){
                        printf("\nYou are not able to add administrator account, please contact your principal.");
                        key(); //Gets a key to turn back
                        goto adminsm;
                        break;
                     }
                     char nameAdmin[NAME_LEN],pwAdmin1[PASS_LEN],pwAdmin2[PASS_LEN];
                     int newID;
                     printf("\nPlease let the new administrator enter his/her own information.\n");
                     ID: ;
                     //New admins are avaliable to choose their IDs.
                     printf("\nEnter your ID, it should be 0 < ID < 2000: ");
                     scanf("%d",&newID); //Gets the ID of the admin
                     if(isIDTaken(newID)){ //If the ID that the new admin has tried to take is taken, s/he is warned about it and turns back to choosing ID
                        printf("\nThis ID has already been taken, please choose another ID.\n");
                        goto ID;
                     }
                     fgets(notUsed,3,stdin); //To be able to use getstr
                     printf("\nEnter your name: ");
                     getstr(nameAdmin,NAME_LEN); //Admin's name is taken
                     pw: ;
                     printf("\nEnter your password: ");
                     getstr(pwAdmin1,PASS_LEN); //Password1 is taken
                     printf("\nEnter your password again: ");
                     getstr(pwAdmin2,PASS_LEN); //Password2 is taken
                     if(strcmp(pwAdmin1,pwAdmin2)){ //If passwords are not the same
                        printf("\nYour Passwords Do Not Match Each Other, Please Enter Again.\n");
                        goto pw;
                     }
                     addAdmin(nameAdmin,newID,pwAdmin1); //New admin is added to admins' linked list
                     printf("\nYou have been an administrator successfully.");
                     key(); //Gets a key to turn back
                     goto adminsm;
                     break;
                  case '3': ;
                     if (enteredID != 10){ //As it was mentioned, it is checked if the admin is principal or not
                        printf("\nYou are not able to delete administrator account, please contact your principal.");
                        key(); //Gets a key to turn back
                        goto adminsm;
                        break;
                     }
                     delAdmin(); //Delete admin function is called to get the ID of the admin that is going to be deleted
                     printf("Process has been finished.\n");
                     key(); //Gets a key to turn back
                     goto adminsm;
                     break;
                  case 'M': ;
                     goto menu2; //If 'm' or 'M' is pressed, turns back to admins menu
                     break;
                  default: ;
                     printf("\nYou have entered wrong.\n");
                     key();
                     goto adminsm;
               }
            break;

            case '2': ; //If admin wants to manage users menu, this case starts.
               usersm: ;
               system("CLS");
               //"Managing Users" interface
               printf("\n%70s","MANAGE USERS\n\n");
               for(int i=0;i<45;i++){
                  printf("\u25C9");
               }
               printf("\n\n 1 ---> See All Users\n\n"
                   " 2 ---> Find a User\n\n"
                   " 3 ---> Delete User\n\n"
                   " M ---> Back to Main Menu\n\n");
               for(int j=0;j<45;j++){
                  printf("\u25C9");
               }
               printf("\nYour Choice: ");
               char c2[2]; //Gets the choice of the admin
               scanf("%s",c2);
               if(strlen(c2)>1){ //If admin enters longer than 1 char
                  printf("\nYou have entered wrong.\n");
                  key();
                  goto usersm;
               }
               if(c2[0] == 'm'){ //If it is 'm', it is converted to 'M'
                  c2[0] = 'M';
               }
               switch(c2[0]){
                  case '1': ; //Pressing 1, shows all the users of the library
                     showUsers();
                     key(); //Gets a key to turn back
                     goto usersm;
                     break;
                  case '2': ; //Pressing 2, calls the function findUser. Admin enters a name
                     findUser();
                     key(); //Gets a key to turn back
                     goto usersm;
                     break;
                  case '3': ; //Pressing 3, calls the function delUser. It is checked that if the user has borrowed a book. If s/he has, s/he cannot be deleted
                     delUser();
                     key(); //Gets a key to turn back
                     goto usersm;
                     break;
                  case 'M': ; //If 'm' or 'M' is pressed, admin goes to
                     goto menu2;
                     break;
                  default: //Wrong enter:
                     printf("You have entered wrong.\n");
                     key();
                     goto usersm;
                     break;
               }
            break;

            case '3': ; //If admin chooses the 3rd menu, it comes to manage borrowers
            borrowersm: ;
               system("CLS");
               //"Managing Borrowers" interface
               printf("\n%70s","MANAGE BORROWERS\n\n");
               for(int i=0;i<45;i++){
                  printf("\u25A9");
               }
               printf("\n\n 1 ---> See All Borrowers\n\n"
                   " 2 ---> Find a Borrower\n\n"
                   " M ---> Back to Main Menu\n\n");
               for(int j=0;j<45;j++){
                  printf("\u25A9");
               }
               printf("\nYour Choice: ");
               char c3[2]; //Gets the choice
               scanf("%s",c3);
               if(strlen(c3)>1){ //If admin enters longer than 1 char
                  printf("\nYou have entered wrong.\n");
                  key();
                  goto borrowersm;
               }
               if(c3[0] == 'm'){ //If the choice is 'm', it is converted to 'M'
                  c3[0] = 'M';
               }
               switch(c3[0]){
                  case '1': ; //Pressing 1, shows all the borrowers of the library
                     showBorrower();
                     key(); //Gets a key to turn back
                     goto borrowersm;
                     break;

                  case '2': ; //Pressing 2, admin is wanted to enter an ID of a user to find if s/he is a borrower
                     int borrID;
                     printf("\nEnter the ID of the user that you want to check: ");
                     scanf("%d",&borrID);
                     findBorrower(borrID); //Tries to find if s/he is a borrower
                     key(); //Gets a key to turn back
                     goto borrowersm;
                     break;

                  case 'M': ; //If the admin presses 'm' or 'M', turns back to admin menu
                     goto menu2;
                     break;
                  default: //Wrong enter
                     printf("You have entered wrong.\n");
                     key();
                     goto borrowersm;
                     break;
               }
            break;


            case '4': ;
               booksm: ;
               system("CLS");
               //"Managing Books" interface
               printf("\n%70s","MANAGE BOOKS\n\n");
               for(int i=0;i<45;i++){
                  printf("\u25D9");
               }
               printf("\n\n 1 ---> See All The Books in The Library\n\n"
                   " 2 ---> Delete Book\n\n"
                   " 3 ---> Find Book\n\n"
                   " 4 ---> Add Book\n\n"
                   " 5 ---> Change a Book's Place\n\n"
                   " M ---> Back to Main Menu\n\n");
               for(int j=0;j<45;j++){
                  printf("\u25D9");
               }
               printf("\nYour Choice: ");

               char c4[2]; //Gets the choice of the admin
               scanf("%s",c4);
               if(strlen(c4)>1){ //If admin enters longer than 1 char
                  printf("\nYou have entered wrong.\n");
                  key();
                  goto booksm;
               }
               if(c4[0] == 'm'){ //If the pressed key is 'm', it is converted to 'M'
                  c4[0] = 'M';
               }
               switch(c4[0]){

                  case '1': ; //Pressing 1, shows all the book in the library
                     showBooks();
                     key(); //Gets a key to turn back
                     goto booksm;
                     break;
                  case '2': ; //Pressing 2, calls the function delBook. It is checked in the function if the book has been borrowed or not. If it is, book cannot
                     delBook();                                                                                                                    //be deleted.
                     key(); //Gets a key to turn back
                     goto booksm;
                     break;
                  case '3': ; //Pressing 3, admin is wanted to enter a keyword for a book to find
                     findBook();
                     key(); //Gets a key to turn back
                     goto booksm;
                     break;
                  case '4': ;
                     char name[NAME_LEN],writer[NAME_LEN],publisher[NAME_LEN],type[30],where[5];
                     int pages,howMany;
                     int bookID = idGenBook(); //For every book, an ID is generated which is different than the previous books in the library and it is printed to
                                               //the screen at the end of registering section
                     fgets(notUsed,3,stdin); //To be able to use the function getstr
                     printf("Enter the book's\nName: ");
                     getstr(name,NAME_LEN); //Books name is scanned with it space characters
                     printf("\nWriter: ");
                     getstr(writer,NAME_LEN); //Writer name is scanned with it space characters
                     printf("\nPublisher: ");
                     getstr(publisher,NAME_LEN); //Publisher name is scanned with it space characters
                     printf("\nCategory: ");
                     getstr(type,30); //Type is scanned with it space characters
                     printf("\nLocation: ");
                     getstr(where,5); //Location of the books is scanned. It must be a roof name like A1, A2, ..., Z5
                     printf("\nPages:");
                     scanf("%d",&pages); //Pages of the book is taken
                     printf("\nCount:");
                     scanf("%d",&howMany); //How many books are being added to the library
                     printf("The book has been added to library with the ID: \uFFEB %d \uFFE9\n \u2713",bookID);
                     addBook(name,writer,publisher,bookID, pages,type,howMany,where); //Adds the book with the given information
                     key(); //Gets a key to turn back to menu
                     goto booksm;
                     break;
                  case '5': ; //Pressing 5, allows the administrator to replace a book's place. All the books and locations' are shown in the function changeBook
                     changeBook();
                     key(); //Gets a key to turn back to menu
                     goto booksm;
                     break;
                  case 'M': ; //If 'm' or 'M' is pressed, turns back to admins menu
                     goto menu2;
                     break;
                  default: ;
                     printf("You have entered wrong.\n");
                     key();
                     goto booksm;
                     break;
               }
            break;

            case '5': ; //Pressing 5, calls the function changePwAd. The new passwords should match each other
               changePwAd(enteredID,password);
               key(); //Gets a key to turn back to menu
               goto menu2;
               break;

            case 'Q': ; //Pressing Q wants the admin to press Q again.
               char choice;
               printf("\nPress Q again if you want to quit (All data will be saved)\n");
               choice = getch();
               if (choice == 'q' || choice == 'Q'){ //If admin presses 'q' or 'Q' all the changes are saved and program turns to the general entering menu
                  saveAdmin();
                  saveBook();
                  saveUser();
                  saveBorrower();
                  goto menu1;
                  break;
               }
               goto menu2; //If second key is different than 'q' or 'Q', it turns back to admins menu
               break;
            default: ; //If wrong key is pressed
               printf("You have entered wrong.");
               key();//Calls the key function and wants user to press any key.
               goto menu2;
               break;
         }

      }
      else{
         goto menu1; //If the isAdmin function turns 0, this line works.
      }
   }

   if(a == '2') {
      int enteredID;
      char password[PASS_LEN];
      system("CLS");
      welcome();//Calls the welcome function.
      printf("%71s","Enter your ID (Only digits): ");
      scanf("%d",&enteredID); //Gets the id that is entered by user.
      printf("%63s","Enter your password: ");
      scanf("%s",password);//Gets the password that is entered by the user.
         //If user exists create the user interface (menu3).
         if(isUser(enteredID,password)){
            menu3:
            system("CLS");
            printf("\n%80s","Welcome To The Library\n\n");
            //Draw the frame with unicode u04DC.
            printf("\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC"
                   "\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\n\n"
                   " 1 ---> See All The Books in The Library\n\n"
                   " 2 ---> See Your Borrowed Books\n\n"
                   " 3 ---> Find Book\n\n"
                   " 4 ---> Borrow Book\n\n"
                   " 5 ---> Return Book\n\n"
                   " 6 ---> Change Your Password\n\n"
                   " Q ---> Save and Exit\n\n"
                   "\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC"
                   "\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\u04DC\n");
            printf("\nYour Choice: ");
            //Get user choice
            char userChoice[2];
            scanf("%s",userChoice);
            if(strlen(userChoice)>1){ //If user enters longer than 1 character
               printf("\nYou have pressed a wrong key.\n");
               key();
               goto menu3;
            }
            //If it's lowercase q make it uppercase
            if (userChoice[0] == 'q'){
               userChoice[0] = 'Q';
            }

            switch(userChoice[0]){
               case '1': ; //If userchoice is 1 show all the relevant books with using the showBooks function
                  showBooks();
                  key();
                  goto menu3; //Return to user menu after the process is done
                  break;
               case '2': ;
                  showBorrowed(enteredID); //If userchoice is 2 show the books that is borrowed by the user
                  key();
                  goto menu3; //Return to user menu after the process is done
                  break;
               case '3': ; //If userchoice is 2 get the find book option with findBook function
                  findBook();
                  key();
                  goto menu3; //Return to user menu after the process is done
                  break;

               case '4': ;//If userchoice is 3 get the borrow book option with borrowBook function
                  borrowBook(enteredID);
                  goto menu3; //Return to user menu after the process is done
                  break;

               case '5': ;
                  returnBook(enteredID);//If userchoice is 4 get the return book option with returnBook function
                  goto menu3; //Return to user menu after the process is done
                  break;

               case '6': ;//Change the user password with a new one using the changePwUs function
                  changePwUs(enteredID,password);
                  key();
                  goto menu3;//Return to user menu after the process is done
                  break;

               case 'Q': ;//Quit option
                  printf("\nDo you want to exit? (Y/N) (All data will be saved)\n");
                  char exitChoice = getch();
                  //If the answer is yes (Y/y) save the borrower and return to menu1.
                  if (exitChoice == 'y' || exitChoice == 'Y'){
                     saveBorrower();
                     saveBook();
                     goto menu1; //Return to main menu after the process is done.
                     break;
                  }
                  //If the answer is no (N/n) go back to user menu.
                  else if(exitChoice == 'n' || exitChoice == 'N') {
                     goto menu3;
                     break;
                  }
                  //If the answer is invalid warn the user.
                  else{
                     printf("\nInvalid Choice !");
                     key();
                     goto menu3;//Return to user menu after the process is done
                     break;
                  }
               default: //If user enters a wrong choice
                  printf("You have entered wrong.");
                  key();//Calls the key function and wants user to press any key.
                  goto menu3;
                  break;
            }
         }
         else{//If the user id and password is invalid return to main menu
            goto menu1;
         }
   }
   //Sign up option
   if(a == '3') {
      system("CLS");
      welcome();//Calls the welcome function
      char name1[NAME_LEN],password1[PASS_LEN],password2[PASS_LEN]; //Declare char arrays for user name,password and the confirmation of the password
      printf("\n%78s","Welcome to the sign up system.\n\n");
      int number = 1000 + rand() % 9000;
      int enteredNum;
      printf("%68s\n%72s %d\n%73s","I am not a robot","Enter the number that you see:",number," ");
      scanf("%d",&enteredNum);
      if(enteredNum!=number){ //If generated number and entered number do not match
         printf("\n%73s","Please try again later..");
         key();
         goto menu1;
      }
      fgets(notUsed,3,stdin); //To be able to use getstr
      printf("%65s","Please enter your name: ");
      getstr(name1,NAME_LEN);//Get the user name
      printf("\n%82s","Please do not use SPACE in your passwords.\n\n");
      printf("%65s","Please enter your password: ");
      getstr(password1,PASS_LEN);//Get the password
      printf("%65s","Please enter your password again: ");
      getstr(password2,PASS_LEN);//Get the password again
      //Compare the password1 and password2 with strcmp function
      if (!strcmp(password1,password2)){
         int IDnew = idGenUser(); //Create a new Id with idGenUser function which is different than the previous users of the library
         addUser(name1,IDnew,password1); //Add a new user with addUser function contains name,Id and the password.
         printf("\nYou have been signed up successfully. Your ID that you will use when you enter the library: \uFFEB %d \uFFE9",IDnew);
         printf("\nPress a key to turn back.");
         saveUser();//Save the user with saveUser function.
         getch();
         goto menu1;//Turn back to main menu.
      }

      //If the passwords don't match with each other warn the user
      else{
         printf("%65s","\nThe passwords do not match each other, please try again after pressing a key.");
         getch();//Get the pressed key
         goto menu1;//Turn back to main menu
      }
   }

   //If the choice is Q quit from the system
   else if(a == 'Q'){
      system("CLS");
      welcome();
      //Frees the memory
      free(admins);
      free(borrowers);
      free(users);
      free(books);
      printf("%72s","Have a Good Day...\n\n");
   }
   return;
}

void getstr(char *str,int readMax){ //Ahmet
   //To be able to take multiple strings from user, we use the function fgets with an array of chars: char notUsed[3] to avoid the '\n' chars
   fgets(str,readMax,stdin);
   str[strlen(str)-1] = '\0'; //To be able to add to the booksData.txt as a line, the char '\n' is removed with the line
   return;
}

void key(){ //Mert
   printf("\n\n");
   printf("%70s","Press any key to turn back to menu."); // Asks user to press a key to confirm that he/she wants to turn back to menu
   getch(); // get the pressed value
   return;
}
