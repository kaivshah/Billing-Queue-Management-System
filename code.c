#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int itm=1,token=0,waiting=0,total=0,counter=0;
int q[5],front=-1,rear=-1;
void red () {
 printf("\033[1;31m");
}
void yellow() {
 printf("\033[1;33m");
}
void blue() {
 printf("\033[1;34m");
}
void green() {
 printf("\033[1;32m");
}
void purple() {
 printf("\033[1;35m");
}
void reset () {
 printf("\033[0m");
}
// Structure for Cart items
struct Cart{
 int item_no;
 char name[20];
 int price;
 struct Cart *next;
} *m;
// Structure for Token no
struct User{
 int token_no;
 int count;
 int item_id[10];
 struct User *nextToken;
} *p;
//----------------------ADMIN---------------------------------------
// To insert an item in Cart
void create_Cart()
{
 struct Cart *temp, *newnode;
 int val;
 char item[20];
 blue();
 printf("\n\tADDING AN ITEM\n");
 printf("\tItem no : %d\n",itm);
 printf("\tEnter the name of item : ");
 scanf("%s",item);
 printf("\tEnter the price of item : ");
 scanf("%d",&val);
 reset();
 newnode = (struct Cart *)malloc(sizeof(struct Cart));
 newnode->item_no = itm;
 strcpy(newnode->name,item);
 newnode->price = val;
 newnode->next = NULL;
 if(m == NULL)
 m = newnode;
 else {
 temp = m;
 while(temp->next != NULL)
 temp = temp->next;
 temp->next = newnode;
 }
 ++itm;
}
//----------------------CUSTOMER------------------------
// To delete an item in Cart
void remove_from_cart()
{
 yellow();
 struct Cart *temp, *prev;
 int no;
 printf("\tREMOVING AN ITEM\n");
 if(m == NULL)
 printf("\tCart is Empty\n");
 else {
 printf("\tEnter the item no : ");
 scanf("%d",&no);
 temp = m;
 while(temp != NULL && temp->item_no != no) {
 prev = temp;
 temp = temp->next;
 }
 if(temp == m)
 m = temp->next;
 else if(temp != NULL)
 prev->next = temp->next;
 if(temp == NULL)
 printf("\tItem does not exist\n");
 else
 free(temp);
 }
 reset();
}
// To display the item in Cart
void display_Cart()
{
 struct Cart *temp;
 if(m == NULL)
 printf("\tCart is Empty\n");
 else {
 temp = m;
 purple();
 printf("\t****************************CART****************************\n");
 blue();
 printf("\tItem No\t\tItem Name\t\t\tItem Price\n");
 reset();
 while(temp != NULL) {
 yellow();
 printf("\t%d\t\t%-20s\t\t₹ %d\n",temp->item_no,temp->name,temp->price);
 reset();
 temp = temp->next;
 }
 }
}
/////-----------Waiting---------------
void insert_Wait(int token_id)
{
 if(front == (rear + 1)%5){
 yellow();
 printf("Counter is full, please wait!\n");
 reset();
 }
 else if(rear == -1)
 {
 front = rear = 0;
 q[rear] = token_id;
 }
 else
 {
 rear = (rear + 1)%5;
 q[rear] = token_id;
 }
}
int remove_Wait()
{
 int val;
 if(front == rear)
 {
 val = q[front];
 front = rear = -1;
 }
 else
 {
 val = q[front];
 front = (front + 1)%5;
 }
 return val;
}
void display_Wait()
{
 int i;
 if(rear == -1){
 yellow();
 printf("\tCurrently Empty\n");
 reset();
 }
 else
 {
 purple();
 printf("<-----Waiting List----->\n");
 blue();
 printf("\tToken No:");
 for(i = front; i != rear; i = (i+1)%5)
 yellow();
 printf("\t%d\n",q[i]);
 printf("\t%d\n",q[i]);
 reset();
 }
}
//----------------------CUSTOMER----------------------------------------
// To create a new token for the customer
void create_Token(int token_id)
{
 struct User *newnode,*temp;
 int val=0,count=0;
 newnode = (struct User *)malloc(sizeof(struct User));
 newnode->token_no = token_id;
 newnode->nextToken = NULL;
 if(counter < 5)
 {
 ++counter;
 blue();
 printf("\tCounter No: %d\n",counter);
 display_Cart();
 blue();
 printf("\tToken no: %d\n",token);
 blue();
 printf("\tEnter the no of items you wish to add (Press -1 to submit)\n\t");
 scanf("%d",&val);
 reset();
 while(val != -1 && val <= itm)
 {
 newnode->item_id[++count] = val;
 scanf("%d",&val);
 }
 newnode->count = count;
 if(p == NULL)
 p = newnode;
 else
 {
 temp = p;
 while(temp->nextToken != NULL)
 temp = temp->nextToken;
 temp->nextToken = newnode;
 }
 }
}
// To delete the token whenever a user checks out
void checkout_Token()
{
 struct User *temp;
 struct Cart *temp2;
 int total_price,count,token_id;
 //count = temp->count;
 total_price = 0;
 if(p == NULL){
 yellow();
 printf("\tYou can go to any counter!\n");
 reset();
 }
 else
 {
 temp = p;
 blue();
 printf("\tEnter the token id: ");
 scanf("%d",&token_id);
 while(temp != NULL && temp->token_no != token_id)
 temp = temp->nextToken;
 if(temp == NULL){
 yellow();
 printf("\tToken No does not exist\n");
 reset();
 }
 else
 {
 purple();
 printf("\t---------------------------BILL---------------------------\n");
 count = temp->count;
 blue();
 printf("\tItem No\t\tItem Name\t\t\tItem Price\n");
 reset();
 for(int i=1; i<=count; i++)
 {
 temp2 = m;
 while(temp2 != NULL && temp2->item_no != temp->item_id[i])
 temp2 = temp2->next;
 yellow();
 printf("\t%d\t\t%-20s\t\t₹ %d\n",temp2->item_no,temp2->name,temp2->price);
 total_price += temp2->price;
 }
 purple();
 printf("\t----------------------------------------------------------\n");
 red();
 printf("\tTotal amount to be paid: ₹ %d\n\n",total_price);
 total += total_price;
 --counter;
 }
 if(temp == p)
 p = p->nextToken;
 free(temp);
 }
}
int main()
{
 int ad,ch=0,ch1=0,ch2=0;
 red();
 printf("<--------WELCOME TO THE BILLING COUNTER-------->\n");
 reset();
 while(ch != 3)
 {
 green();
 printf("\t1. Admin \n\t2. Customer \n\t3. Exit \n\tEnter the choice: ");
 scanf("%d",&ch);
 reset();
 switch(ch)
 {
 case 1 : red();
 printf("\n<-------------ADMIN PORTAL------------->\n\n");
 blue();
 printf("\tEnter the admin id: ");
 scanf("%d",&ad);
 if(ad == 123 || ad == 124 || ad == 125 || ad == 126 || ad == 127)
 {
 yellow();
 printf("\n\tLogged in as ADMIN\n");
 reset();
 ch=0; //TO GO BACK TO ADMIN ADMIN
 while(ch1 != 4)
 {
 green();
 printf("\n\t1. Add an item \n\t2. Remove an item \n\t3. My Cart \n\t4. Back
\n\tEnter the choice : ");
 scanf("%d",&ch1);
 reset();
 printf("\n");
 switch(ch1)
 {
 case 1 : create_Cart();
 break;
 case 2 : remove_from_cart();
 break;
 case 3 : display_Cart();
 break;
 case 4 : break;
 default : yellow();
 printf("\tInvalid Response\n");
 reset();
 }
 }
 }
 else{
 yellow();
 printf("\tEnter correct Admin ID!\n\n");
 reset();
 }
 break;
 case 2 : red();
 printf("\n<--------------CUSTOMER PORTAL-------------->\n\n");
 reset();
 while(ch2 != 5)
 {
 green();
 printf("\t1. Item Menu \n\t2. Place Order \n\t3. Bill \n\t4. Display Waiting List
\n\t5. Back \n\tEnter the choice: ");
 scanf("%d",&ch2);
 reset();
 printf("\n");
 switch(ch2)
 {
 case 1 : display_Cart();
 break;
 case 2 : if(m == NULL){
 yellow();
 printf("\tMenu is Empty\n");
 reset();
 }
 else if(counter < 5)
 {
 create_Token(++token);
 }
 else
 {
 yellow();
 printf("\tYou are in waiting list\n");
 reset();
 ++waiting;
 insert_Wait(++token);
 }
 break;
 case 3 : checkout_Token();
 if(counter > 0 && counter < 5)
 {
 if(waiting > 0)
 {
 --waiting;
 create_Token(remove_Wait());
 }
 }
 break;
 case 4 : if(waiting>0)
 {display_Wait();}
 else{
 yellow();
 printf("\tThere's no waiting list!!\n\n");
 reset();
 }
 break;
 case 5 : break;
 default : yellow();
 printf("\tInvalid Response\n");
 reset();
 }
 if(ch1 == 1)
 break;
 }
 break;
 case 3 : red();
 printf("------------------------------------------------------------------");
 reset();
 break;
 default : printf("\tInvalid Response\n");
 }
 }
 return 0;
}
