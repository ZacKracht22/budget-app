# Budget App
The Budget App is a tool for creating, editing, and managing personal budgets. Budgets in this app consist of an income value, a list of expenses, and a list of weights. The weights are to set a percentage of the remaining income, after the expenses have been subtracted, to specific categories.

## Getting Started
These instructions will get you a copy of the project up and running on your local machine for testing purposes.

### Prerequisites
What you'll need at minimum to run the project

```
CMake 3.5
Qt 5.13
C++ 11 Compiler
```

### Downloading the Project
To download the project to your computer, either download from GitHub or in the command prompt clone the repository

```
git clone https://github.com/ZacKracht22/budget-app.git
```

## Building the Project
To build the project from the command prompt, go into the project directory and run the following commands

```
mkdir build
cd build
cmake ..
cmake --build.
```

## Usage

### Running the GUI
To run the GUI from the Budget Creator page, type the following command

```
./Debug/budget_app
```

### Example use
Say you want to build a budget for each month with the following income and known expenses

```
Name: Example
Income: $1000.00
Expenses:
	car payment: $145.50
	music streaming: $5.99
	gas: $120.00
	gym membership: $30.00
```
Then you decide you want to use the rest of your money on food, clothing, and sports, but mostly on food. That might look something like this
```
Weights:
	food: 60%
	clothing: 20%
	sports: 20%
```
* First start by setting the name of the budget by typing out "Example"
* Set the income to $1000.00 by hitting the up arrow 10 times on the income line
* Then, for each expense, enter the cost in the cost box using either the arrows or manually typing, and then write the name of the expense in the description box.
* Press Add to add the expense to the list.
* Repeat this process for each weight in the weights section.
* You can edit or delete any of these items, or reset a whole list using the cooresponding buttons
* Press Create when you are ready to create your budget

### Running Unit Tests
To run the unit tests executable for the Budget Class, type the following command

```
./Debug/budget_tests
```
To run the unit tests executable for the util namespace, type the following command

```
./Debug/util_tests
```