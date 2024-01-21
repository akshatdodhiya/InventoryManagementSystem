/*
Description: Inventory management system. Maximum of 12 different items can be tracked together. The program will allow the user to enter the name,
identification number, cost and quantity of each item. Using which the program keeps track of sales, profit on each item and total store profit.
Programmer: Akshat Dodhiya
Date: December 7, 2023
Version: 1.0
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_SIZE 26  // 25 characters + 1 for null character [Can be changed to any value]
#define MAX_ITEMS 12  // Maximum number of items that can be tracked [Can be changed to any value]

struct Inventory
{
	char itemName[MAX_NAME_SIZE];
	int itemID;
	float itemCost;
	int itemQuantity;
	int itemSold;
	float itemProfit;
};

void ExplainProg(void);
void ShowMenu(void);
int ReadFile(struct Inventory *pitem);
void WriteFile(struct Inventory *pitem, int totalItems);
void ShowInventory(struct Inventory items[], int totalItems);
int findItem(struct Inventory items[], int totalItems, int itemID);
void AddSale(struct Inventory items[], int totalItems);
void ShowSales(struct Inventory items[], int totalItems);
void OrderExisting(struct Inventory items[], int totalItems);
int OrderNew(struct Inventory items[], int totalItems);

int main(void)
{
	ExplainProg();
	ShowMenu();	

	return 0;
}

void ExplainProg(void)
{
	printf("\n\n\n\t\t\t\t\t\t**** Welcome to the program ****");
	printf("\n\n\t\t\tThis is an inventory management system. Maximum of 12 different items can be tracked together.");
	printf("\n\t\t\tThe program will allow the user to enter the name, identification number, cost and quantity of each item.");
	printf("\n\t\t\tUsing which the program keeps track of sales, profit on each item and total store profit.");

	printf("\n\n\t\t\t");
	system("pause");
	system("cls");

	return;
}

void ShowMenu(void)
{
	char userChoice;
	int totalItems;
	totalItems = 0;

	struct Inventory items[MAX_ITEMS];
	totalItems = ReadFile(items);

	do
	{
		userChoice = ' ';

		printf("\n\n\n\t\t\t\t\t\tInventory Control System");
		printf("\n\n\n\t\t\t\t\tTo choose a function, enter its letter label:");

		printf("\n\n\t\t\ta) Show the name, identification number and number of each item in stock,\n\t\t\tincluding the cost of each item and total value of each item in stock.");
		printf("\n\t\t\tb) Enter the sale of an item.");
		printf("\n\t\t\tc) Show the number of units sold, the profit for each item and the total store profit.");
		printf("\n\t\t\td) Order more of an existing item.");
		printf("\n\t\t\te) Order new items.");
		printf("\n\t\t\tf) Quit.");

		printf("\n\n\t\t\tEnter your choice: ");
		scanf(" ");  // To clear the input buffer
		fflush(stdin);
		userChoice = getchar();
		userChoice = tolower(userChoice);

		switch (userChoice)
		{
		case 'a':
			ShowInventory(items, totalItems);
			break;
		case 'b':
			AddSale(items, totalItems);
			WriteFile(items, totalItems);
			break;
		case 'c':
			ShowSales(items, totalItems);
			break;
		case 'd':
			OrderExisting(items, totalItems);
			WriteFile(items, totalItems);
			break;
		case 'e':
			totalItems = OrderNew(items, totalItems);
			WriteFile(items, totalItems);
			break;
		case 'f':
			WriteFile(items, totalItems);
			system("cls");
			printf("\n\n\n\t\t\t\t\t\t**** Thank you for using the program ****\n");
			break;
		default:
			printf("\n\n\t\t\tInvalid choice! Please try again.");
			break;
		}

		printf("\n\t\t\t===========================================================================================================\n\n");
		printf("\n\t\t\t");
		system("pause");
		system("cls");
	} while (userChoice != 'f');

	return;
}

int ReadFile(struct Inventory *pitem)
{
	int totalItems = 0;
	FILE *filePointer;

	// Import data from file
	filePointer = fopen("inventory.dat", "rb+");
	if (!filePointer)
	{
		filePointer = fopen("inventory.dat", "wb+");
		if (!filePointer)
		{
			printf("\n\n\t\t\tError opening file! The data might not have been retrieved properly!");
			system("pause");
			return 0;
		}
	}

	// Read data from file
	totalItems = fread(pitem, sizeof(struct Inventory), MAX_ITEMS, filePointer);

	fclose(filePointer);

	return totalItems;
}

void WriteFile(struct Inventory *pitem, int totalItems)
{
	FILE *filePointer;

	filePointer = fopen("inventory.dat", "wb+");
	if (!filePointer)
	{
		printf("\n\n\t\t\tError opening file! The data might not have been saved properly!");
		system("pause");
		return;
	}

	fwrite(pitem, sizeof(struct Inventory), totalItems, filePointer);
	fclose(filePointer);

	return;
}

void ShowInventory(struct Inventory items[], int totalItems)
{
	int index;

	system("cls");
	printf("\n\n\n\t\t\t\t\t\t\t***** Inventory Control System *****");
	printf("\n\n\t\t\tItem Name\t\tID Number\t\tQuantity\t\tUnit Cost\t\tValue");
	for(index = 0; index < totalItems; index++)
	{
		printf("\n\n\t\t\t%s\t\t\t%d\t\t\t%d\t\t\t$%.2f\t\t\t$%.2f", items[index].itemName, items[index].itemID,
			items[index].itemQuantity, items[index].itemCost, (items[index].itemCost * items[index].itemQuantity));
	}
	printf("\n\n");

	return;
}

int findItem(struct Inventory items[], int totalItems, int itemID)
{
	int index;

	// Search for item
	for(index = 0; index < totalItems; index++)
	{
		if(items[index].itemID == itemID)
		{
			return index;
		}
	}

	return -1;
}

void AddSale(struct Inventory items[], int totalItems)
{
	int itemID, itemPos, unitsSold, isValid;

	system("cls");
	ShowInventory(items, totalItems);
	printf("\n\n\t\t\t\t\t\t\t***** Add Sale *****");

	do
	{
		printf("\n\n\t\t\t\t\tEnter the ID number of the item: ");
		fflush(stdin);
		isValid = scanf("%d", &itemID);

		if (isValid != 1)
		{
			printf("\n\n\t\t\t\t\tInvalid input! Please enter only integer value and try again.");
			fflush(stdin);
		}
		if(itemID < 0)
		{
			printf("\n\n\t\t\t\t\tInvalid input! Please enter only positive integers and try again.");
			fflush(stdin);
			isValid = 0;
		}

		itemPos = findItem(items, totalItems, itemID);

		if (itemPos == -1 && isValid == 1)
		{
			printf("\n\n\t\t\t\t\tItem not found! Please try again!");
			fflush(stdin);
			isValid = 0;
		}
	} while (isValid != 1);
	
	do
	{
		printf("\n\n\t\t\t\t\tEnter the number of units sold: ");
		fflush(stdin);
		isValid = scanf("%d", &unitsSold);

		if (isValid != 1)
		{
			printf("\n\n\t\t\t\t\tInvalid input! Please enter only integer value and try again.");
			fflush(stdin);
		}

		if(unitsSold > items[itemPos].itemQuantity)
		{
			printf("\n\n\t\t\t\t\tNot enough units in stock! Please try again.");
			fflush(stdin);
			isValid = 0;
		}
		else if (unitsSold < 1)
		{
			printf("\n\n\t\t\t\t\tInvalid input! Units Sold cannot be less than 1! Please try again!");
			fflush(stdin);
			isValid = 0;
		}
	} while (isValid != 1);

	items[itemPos].itemQuantity -= unitsSold;
	items[itemPos].itemSold += unitsSold;
	items[itemPos].itemProfit += ((items[itemPos].itemCost * items[itemPos].itemSold * 1.5f)
		- (items[itemPos].itemSold * items[itemPos].itemCost));

	printf("\n\n\t\t\t\t\tSale added successfully!");

	return;
}

void ShowSales(struct Inventory items[], int totalItems)
{
	int index;
	float totalProfit = 0.0f;

	system("cls");

	printf("\n\n\n\t\t\t\t\t\t\t***** Inventory Control System *****");
	printf("\n\n\t\t\tItem Name\t\t\tID Number\t\t\tQuantity Sold\t\t\tItem Profit");
	for (index = 0; index < totalItems; index++)
	{
		printf("\n\n\t\t\t%s\t\t\t\t%d\t\t\t\t%d\t\t\t\t$%.2f", items[index].itemName,
			items[index].itemID, items[index].itemSold, items[index].itemProfit);
		totalProfit += items[index].itemProfit;
	}

	printf("\n\n\n\t\t\t --> Total Store Profit: \t\t\t\t\t\t\t\t\t$%.2f", totalProfit);
	printf("\n\n");

	return;
}

void OrderExisting(struct Inventory items[], int totalItems)
{
	int itemID, itemPos, unitsOrdered, isValid;

	system("cls");
	ShowInventory(items, totalItems);

	printf("\n\t\t\t\t\t\t\t***** Order Existing Item *****");
	
	do
	{
		printf("\n\n\t\t\t\t\tEnter the ID number of the item: ");
		fflush(stdin);
		isValid = scanf("%d", &itemID);

		if (isValid != 1 || itemID < 0)
		{
			printf("\n\n\t\t\t\t\tInvalid input! Please enter only positive integers and try again.");
			fflush(stdin);
			isValid = 0;
		}

		itemPos = findItem(items, totalItems, itemID);

		if (itemPos == -1 && isValid == 1)
		{
			printf("\n\n\t\t\t\t\tItem not found! Please check the ID!");
			fflush(stdin);
			isValid = 0;
		}
	} while (isValid != 1);

	do
	{
		printf("\n\n\t\t\t\t\tEnter the number of units ordered: ");
		fflush(stdin);
		isValid = scanf("%d", &unitsOrdered);

		if (isValid != 1 || unitsOrdered < 1)
		{
			printf("\n\n\t\t\t\t\tInvalid input! Please enter only positive integer values and try again.");
			fflush(stdin);
			isValid = 0;
		}
	} while (isValid != 1);

	items[itemPos].itemQuantity += unitsOrdered;

	printf("\n\n\t\t\t\t\tOrder added successfully!");

	return;
}

int OrderNew(struct Inventory items[], int itemIndex)
{
	int isValid, itemPos;

	if (itemIndex < MAX_ITEMS)
	{
		printf("\n\t\t\t\t\t***** Order New Item *****");
		printf("\n\n\t\t\tEnter the name of the item: ");
		scanf(" ");
		gets(items[itemIndex].itemName);

		do
		{
			printf("\n\n\t\t\tEnter the ID number of the item: ");
			fflush(stdin);
			isValid = scanf("%d", &items[itemIndex].itemID);

			if (isValid != 1 || items[itemIndex].itemID < 0)
			{
				printf("\n\n\t\t\tInvalid input! Please enter only integer and try again.");
				fflush(stdin);
				isValid = 0;
			}

			itemPos = findItem(items, itemIndex, items[itemIndex].itemID);

			if (itemPos != -1 && isValid == 1)
			{
				printf("\n\n\t\t\tItem ID already exists! Please try again with a different ID.");
				fflush(stdin);
				isValid = 0;
			}

		} while (isValid != 1);

		do
		{
			printf("\n\n\t\t\tEnter the cost of the item: ");
			fflush(stdin);
			isValid = scanf("%f", &items[itemIndex].itemCost);

			if (isValid != 1)
			{
				printf("\n\n\t\t\tInvalid input! Please enter only decimal numbers and try again.");
				fflush(stdin);
			}
			if (items[itemIndex].itemCost < 0)
			{
				printf("\n\n\t\t\tInvalid input! Cost cannot be less than 0! Please try again.");
				fflush(stdin);
				isValid = 0;
			}
		} while (isValid != 1);

		do
		{
			printf("\n\n\t\t\tEnter the quantity of the item: ");
			fflush(stdin);
			isValid = scanf("%d", &items[itemIndex].itemQuantity);

			if (isValid != 1)
			{
				printf("\n\n\t\t\tInvalid input! Please enter only integer and try again.");
				fflush(stdin);
			}
			if (items[itemIndex].itemQuantity < 0)
			{
				printf("\n\n\t\t\tInvalid input! Quantity cannot be less than 0! Please try again.");
				fflush(stdin);
				isValid = 0;
			}
		} while (isValid != 1);

		items[itemIndex].itemSold = 0;
		items[itemIndex].itemProfit = 0;

		itemIndex++;

		printf("\n\n\t\t\tItem added successfully!");

	}
	else
	{
		printf("\n\n\t\t\tMaximum number of items reached!");
	}

	return itemIndex;
}