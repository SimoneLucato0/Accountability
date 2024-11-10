# Accountability

![image](https://github.com/user-attachments/assets/d1f75365-0d0d-4dcb-9caf-bb0971f239dc)

This project was conducted as the final assignment for the 2020/2021 Object-Oriented Programming course, led by Prof. Francesco Ranzato at the University of Padova.

## Authors
Simone Lucato, University of Padua, Italy

Elia Scandaletti, University of Padua, Italy

## Purpose
The application deals with modelling an account management system, both personal and non-personal. The user, after logging in login or registration, will find his personal accounts on the one hand, and the groups to which he/she belongs on the other, both sorted by last activity. The personal accounts include registers in which sources of income and expenses can be entered. In both cases it is possible to add transactions, alongside with the description, amount and any notes. Groups consist of a set of users and can give rise to common tills, for the management of money within a group of people. This is where "fundraising" can take place (to collect a sum of money from each member of the common till) or common expenses (of common interest, with additional parameters for personal expenses or adding from one's own pocket to the expenditure), as well as keeping track of the budget of each individual, the key point of the application.

## Key features
- **MVC Architecture**: The project is built using the Model-View-Controller (MVC) pattern. By isolating data handling (Model), UI rendering (View), and user input processing (Controller), it enables easier updates, testing, and collaboration. This structure enhances scalability, code clarity, and allows independent development of each component.
- **Template usage**: In the project there is vast usage of templates. They allow for generic programming, enabling code reuse for different data types without duplication. They provide type safety and flexibility, allowing functions and classes to operate on any data type. In addition, they enhance performance through compile-time polymorphism, reducing runtime overhead and improving code maintainability and efficiency.
- **Lambda functions**: In the handling of views lambda functions are widely used. The main purpose is to emit signals with them, avoiding adding a slot to the components, making the logic lighter, more maintainable and more readable. 

## Technical limitations
The application was developed and tested in the following environment:
- Qt Creator 4.5.2 based on Qt 5.9.5
- OS: Ubuntu 18.04
- Compiler: gcc 7.5.0

## Compile instructions

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/SimoneLucato0/Accountability.git
   cd Accountability
   ```
   
3. **Compile the application**:

   ```bash
   qmake
   make
   ```
   
5. **Run the application**

    ```bash
    ./accountability
    ```
