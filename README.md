# Week08_ProgrammingAssignment_BrittanyKennedy

This C++ program helps vegetarian weightlifters plan and evaluate their daily and weekly nutrition. It calculates macro targets, validates user input, logs weekly calories, generates formatted reports, and evaluates nutrition based on user goals.

New in Week 8: The entire program has been restrcutured into a class-based, encapsulated design.

*Key Features*
- Menu Navigation: View macros, generate reports, check nutrition + recipe, view weekly logs, view weekly struct summary, start new session.
- Input Validation: Clean string/int/double handling with buffer clearing.
- Console Colors: Highlights sections, headers, and errors.
- Macro Calculations: Daily grams, per meal breakdowns, and weekly totals.
- Report Generation: Creates a formatted report.txt.


*New This Week — Classes & Encapsulation*
nutritionTracker Class
- Replaced nearly all global variables and standalone functions
- Stores all:
  - User input
  - Macro targets
  - Arrays
  - Struct data
  - Weekly totals as private class members
- Program flow is now controlled through public class methods
