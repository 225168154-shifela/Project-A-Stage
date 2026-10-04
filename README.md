# Municipal Financial Management System (MFMS)

## Project Information
- Course: PAP521S - Programming in Practice  
- Programming Language: C 
- Development Environment: Visual Studio Code + GCC  
- Version Control: Git & GitHub  
- Project Type: Group Project (7 members)  

## Group Members & Responsibilities
- Gina2402 - Employee Management  
- MrHays007 - Management  
- 225054523-Sefanya - Supplier Management  
- annataatsu06-ai - Asset Management  
- Vilho-Katamba - Reports  
- 220075700 Mpinge Godhard - Functions, Integration & Validation  
- 225168154-Shifela - Testing, Documentation & Git Coordination  

## Project Description
This project is the foundation version of a Municipal Financial Management System (MFMS).  
It demonstrates the use of C programming concepts such as input/output, variables, operators, decisions, loops, arrays, strings, and functions to solve a realistic municipal problem.

## System Features
- Employee Management: Add, display, search employees, calculate salary info  
- Budget Management: Enter budgets, expenditures, calculate remaining budget, check overspending  
- Supplier Management: Add, display, search suppliers  
- Asset Management: Register and search municipal assets  
- Reports: Generate employee, budget, supplier, and asset reports  
- Validation: Prevent invalid inputs (negative salary/budget, empty names, invalid menu choices)  

## Compilation Instructions
1. Open the project in Visual Studio Code.  
2. Ensure GCC is installed and available in your PATH.  
3. Compile using:  
   ```bash
   gcc main.c employees.c budget.c suppliers.c assets.c reports.c -o mfms
