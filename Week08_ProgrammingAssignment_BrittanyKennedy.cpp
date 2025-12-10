/*
======================================================================
Program: Vegetarian Nutrition for Weightlifting
Author : Brittany Kennedy
Date   : 12/9/2025
Section: ITCS 2530 H0801 2025FA - C++ Programming 1
======================================================================
Description:
    This program assists vegetarian weightlifters in calculating their
    recommended daily and per-meal macronutrient targets (protein,
    carbohydrates, and fats). The program uses user-provided input and
    applies nutrition-based formulas to generate accurate results.
======================================================================
*/


// ===================== INCLUDES =====================
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <windows.h>   // Used to change console text color (Windows only)

using namespace std;


// ===================== CONSTANTS =====================
const double PROTEIN_PERCENT = 0.30;
const double CARB_PERCENT = 0.40;
const double FAT_PERCENT = 0.30;

const int CALORIES_PER_GRAM_PROTEIN = 4;
const int CALORIES_PER_GRAM_CARBS = 4;
const int CALORIES_PER_GRAM_FAT = 9;

const int NUMBER_OF_DAYS = 7;

const double ACTIVITY_HIGH = 5.0;
const double ACTIVITY_MEDIUM = 3.0;

const int CAL_EXCESS = 2500;
const int CAL_HIGH = 2200;
const int CAL_MEDIUM = 2000;
const int CAL_LOW = 1800;

const int MEALS_PER_DAY_HIGH = 6;
const int MEALS_PER_DAY_MEDIUM = 4;
const int MEALS_PER_DAY_LOW = 2;

const int MEALS_PER_WEEK_HIGH = MEALS_PER_DAY_HIGH * NUMBER_OF_DAYS;
const int MEALS_PER_WEEK_MEDIUM = MEALS_PER_DAY_MEDIUM * NUMBER_OF_DAYS;
const int MEALS_PER_WEEK_LOW = MEALS_PER_DAY_LOW * NUMBER_OF_DAYS;

const int CONSOLE_WIDTH = 75;
const int INPUT_IGNORE_LIMIT = 1000;

const int COLOR_DEFAULT = 15;  // White
const int COLOR_HEADER = 3;   // Aqua
const int COLOR_SUB_HEADING = 2;   // Green
const int COLOR_RECIPE = 14;  // Yellow
const int COLOR_ERROR = 12;  // Red


// ===================== ENUM =====================
// Goal type for the lifter
enum GoalType { FAT_LOSS, MAINTENANCE, MUSCLE_GAIN };


// ===================== STRUCT =====================
// Represents a daily nutrition session, including calories and macro totals.
struct nutritionSession
{
    string date;           // Day label (e.g., "Day 1")
    int calories;          // Actual calories for that day
    int protein;           // Daily protein grams (target)
    int carbs;             // Daily carb grams (target)
    int fats;              // Daily fat grams (target)
    bool metCalorieGoal;   // True if daily calories <= target
};


// ===================== UTILITY FUNCTION PROTOTYPES =====================
void setConsoleColor(int color);
void clearInputStream();
void printSectionBreakLine();


// ===================== CLASS DEFINITION =====================
// Treating the class as the Owner of all the data and logic rather than main
class nutritionTracker
{
public:
    // Constructor
    nutritionTracker();

    // ***** Program Flow *****
    void displayIntroBanner();
    void collectUserInput();   // New function to gather all user input for 1 session & store it inside the class obj
    void calculateMacros();

    // ***** Data Population *****
    void fillDailyCaloriesArray();
    void fillSessionsFromCalories();
    void fillMacrosPerMeal2D();  // New function to fill 2D arrray added to program

    // ***** Menu & Display *****
    void displayMenu() const;
    void displayDailyMacros() const;
    void generateReport() const;
    void displayWeeklyCalorieLog() const;
    void displayWeeklySessions() const;
    void displayNutritionCheckAndRecipe() const;
    void displayMacrosPerMeal2D() const;

private:
    // ***** User Info *****
    string name;
    string favoriteProtein;
    GoalType goal;

    // ***** Core User Targets *****
    int dailyCalories;
    int weeklyCalories;
    int mealsPerDay;
    double weeklyWorkoutHours;

    // ***** Daily Macro Targets *****
    int dailyProteinGrams;
    int dailyCarbGrams;
    int dailyFatGrams;

    // ***** Weekly Macro Totals *****
    int totalProteinGrams;
    int totalCarbGrams;
    int totalFatGrams;

    // ***** Per-Meal Targets *****
    int proteinPerMeal;
    int carbsPerMeal;
    int fatsPerMeal;

    // ***** Data Structures *****
    int dailyCaloriesLog[NUMBER_OF_DAYS];   // Weekly calorie log array (one entry per day)
    nutritionSession weeklySessions[NUMBER_OF_DAYS];   // Struct array (one entry per day) to complement dailyCaloriesLog
    int macrosPerMeal2D[3][NUMBER_OF_DAYS];   // New 2D Array display option

    // ***** Private Helper Functions *****
    string getValidatedStringInput(string requestInput);
    int getValidatedIntInput(string requestInput);
    double getValidatedDoubleInput(string requestInput);
    GoalType getUserGoal();
    double calculateAverageCalories() const;
    double calculateAverageFromArray(const int values[], int size) const;
    int findHighestCalories() const;
    void evaluateMealFrequency(int mealsPerWeek) const;
    void displaySmoothieRecipe() const;
    void evaluateNutrition() const;
};


// ===================== MAIN =====================
// Main function controlling program flow and user interaction
int main()
{
    nutritionTracker tracker;

    char startNewSession = 'n';

    // Main session loop so user can restart with new inputs
    do
    {
        tracker.displayIntroBanner();

        tracker.collectUserInput();
        tracker.fillDailyCaloriesArray();

        tracker.calculateMacros();

        tracker.fillSessionsFromCalories();
        tracker.fillMacrosPerMeal2D();

        int menuChoice = 0;

        // ------------------------ Menu Loop -----------------------------
        // Displays the main menu and allows the user to explore all features
        //    until they choose to exit or start a new session
        do
        {
            tracker.displayMenu();
            cin >> menuChoice;
            cout << endl;

            // If menu input is invalid, clear the stream and continue
            if (cin.fail())
            {
                clearInputStream();
                setConsoleColor(COLOR_ERROR);
                cout << "Invalid choice. Please enter a number from 1 to 8.\n\n";
                setConsoleColor(COLOR_DEFAULT);
                continue;   
            }


            switch (menuChoice)
            {
            case 1:
                // Show suggested daily macros and per meal breakdown
                tracker.displayDailyMacros();
                break;

            case 2:
                // Write a formatted report to report.txt
                tracker.generateReport();
                break;

            case 3:
                // Check calorie intake vs activity and show smoothie recipe
                tracker.displayNutritionCheckAndRecipe();
                break;

            case 4:
                // View weekly calorie log (array)
                tracker.displayWeeklyCalorieLog();
                break;

            case 5:
                // View weekly nutrition sessions (using struct array)
                tracker.displayWeeklySessions();
                break;

            case 6:
                // Display macros per meal as a grid
                tracker.displayMacrosPerMeal2D();
                break;

            case 7:
                // Start a new session with fresh inputs
                setConsoleColor(COLOR_SUB_HEADING);
                cout << "Starting a new session...\n\n";
                setConsoleColor(COLOR_DEFAULT);
                break;

            case 8:
                // Exit the program
                setConsoleColor(COLOR_SUB_HEADING);
                cout << "Thanks for using the program! Keep lifting strong!\n";
                printSectionBreakLine();
                setConsoleColor(COLOR_DEFAULT);
                break;

            default:
                setConsoleColor(COLOR_ERROR);
                cout << "Invalid choice. Please select 1–8.\n\n";
                setConsoleColor(COLOR_DEFAULT);
                break;
            }

        } while (menuChoice != 7 && menuChoice != 8);

        // Clear leftover newline from menu input
        clearInputStream();

        // Check if user decided to start a new session (6 = new session)
        startNewSession = (menuChoice == 7) ? 'y' : 'n';

    } while (startNewSession == 'y');

    cout << "\nProgram ended. Have a great day!\n";

    return 0;
}


// ================================= FUNCTION DEFINITIONS ==============================================

// --------------------- Utility Functions ---------------------
void setConsoleColor(int color)
{
    // Handle is a Windows data type that references the console
    // GetSTDHandle is a Windows function that retrieves the console/output device
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // SetConsoleTextAttribute is a Windows function to allow changing the text color in the console
    SetConsoleTextAttribute(hConsole, color);
}

void clearInputStream()
{
    cin.clear();
    cin.ignore(INPUT_IGNORE_LIMIT, '\n');
}

void printSectionBreakLine()
{
    cout << setfill('*') << setw(CONSOLE_WIDTH) << '*' << "\n";
    cout << setfill(' ');
}


// --------------------- Constructor ---------------------
nutritionTracker::nutritionTracker()
{
    name = "";
    favoriteProtein = "";
    dailyCalories = 0;
    weeklyCalories = 0;
    mealsPerDay = 0;
    weeklyWorkoutHours = 0.0;

    dailyProteinGrams = 0;
    dailyCarbGrams = 0;
    dailyFatGrams = 0;

    totalProteinGrams = 0;
    totalCarbGrams = 0;
    totalFatGrams = 0;

    proteinPerMeal = 0;
    carbsPerMeal = 0;
    fatsPerMeal = 0;

    goal = MAINTENANCE;

    for (int i = 0; i < NUMBER_OF_DAYS; i++)
    {
        dailyCaloriesLog[i] = 0;
    }

    for (int i = 0; i < NUMBER_OF_DAYS; i++)
    {
        weeklySessions[i].date = "";
        weeklySessions[i].calories = 0;
        weeklySessions[i].protein = 0;
        weeklySessions[i].carbs = 0;
        weeklySessions[i].fats = 0;
        weeklySessions[i].metCalorieGoal = false;
    }

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < NUMBER_OF_DAYS; col++)
        {
            macrosPerMeal2D[row][col] = 0;
        }
    }
}


// --------------------- Input ---------------------
void nutritionTracker::collectUserInput()
{
    name = getValidatedStringInput("What is your name? ");
    cout << "Hi " << name << "!\n\n";

    favoriteProtein = getValidatedStringInput("What is your favorite vegetarian protein source? ");
    dailyCalories = getValidatedIntInput("How many calories are you targeting each day? ");
    mealsPerDay = getValidatedIntInput("How many meals do you eat per day? ");
    weeklyWorkoutHours = getValidatedDoubleInput("How many hours per week do you weightlift? ");
    goal = getUserGoal();
}

string nutritionTracker::getValidatedStringInput(string requestInput)
{
    string value;

    cout << requestInput;
    getline(cin, value);
    cout << endl;

    // Repeat until the user enters a non-empty string
    while (value.length() == 0)
    {
        setConsoleColor(COLOR_ERROR);
        cout << "That is not a valid answer. Please try again: ";
        setConsoleColor(COLOR_DEFAULT);

        getline(cin, value);
        cout << endl;
    }

    return value;
}

int nutritionTracker::getValidatedIntInput(string requestInput)
{
    int value;

    cout << requestInput;
    cin >> value;
    cout << endl;

    // Loop continues until the user enters a valid positive integer
    while (cin.fail() || value <= 0)
    {
        clearInputStream();
        setConsoleColor(COLOR_ERROR);
        cout << "That is not a valid answer. Please enter a positive number: ";
        setConsoleColor(COLOR_DEFAULT);

        cin >> value;
        cout << endl;
    }

    clearInputStream();   // Clear newline left in the buffer
    return value;
}

double nutritionTracker::getValidatedDoubleInput(string requestInput)
{
    double value;

    cout << requestInput;
    cin >> value;
    cout << endl;

    // Loop continues until the user enters a valid nonnegative double
    while (cin.fail() || value < 0.0)
    {
        clearInputStream();
        setConsoleColor(COLOR_ERROR);
        cout << "That is not a valid answer. Please enter a nonnegative number: ";
        setConsoleColor(COLOR_DEFAULT);

        cin >> value;
        cout << endl;
    }

    clearInputStream();   // Clear newline left in the buffer
    return value;
}

GoalType nutritionTracker::getUserGoal()
{
    int goalChoice = 0;

    cout << "Select your primary goal:\n"
        << "  1. Fat loss\n"
        << "  2. Maintenance\n"
        << "  3. Muscle gain\n\n";
    cout << "Enter 1, 2, or 3: ";
    cin >> goalChoice;
    cout << endl;

    while (cin.fail() || goalChoice < 1 || goalChoice > 3)
    {
        clearInputStream();
        setConsoleColor(COLOR_ERROR);
        cout << "That is not a valid choice. Please enter 1, 2, or 3: ";
        setConsoleColor(COLOR_DEFAULT);

        cin >> goalChoice;
        cout << endl;
    }

    clearInputStream();

    // Convert user's goal choice to the enum value (0-2)
    return static_cast<GoalType>(goalChoice - 1);
}


// --------------------- Core Processing ---------------------
void nutritionTracker::calculateMacros()
{
    // Daily macro grams based on percentage of calories
    dailyProteinGrams = static_cast<int>((dailyCalories * PROTEIN_PERCENT) /
        CALORIES_PER_GRAM_PROTEIN);
    dailyCarbGrams = static_cast<int>((dailyCalories * CARB_PERCENT) /
        CALORIES_PER_GRAM_CARBS);
    dailyFatGrams = static_cast<int>((dailyCalories * FAT_PERCENT) /
        CALORIES_PER_GRAM_FAT);

    // Per meal targets.
    proteinPerMeal = dailyProteinGrams / mealsPerDay;
    carbsPerMeal = dailyCarbGrams / mealsPerDay;
    fatsPerMeal = dailyFatGrams / mealsPerDay;

    // Accumulates weekly macro totals based on daily values
    weeklyCalories = 0;
    totalProteinGrams = 0;
    totalCarbGrams = 0;
    totalFatGrams = 0;

    for (int day = 1; day <= NUMBER_OF_DAYS; ++day)
    {
        totalProteinGrams += dailyProteinGrams;
        totalCarbGrams += dailyCarbGrams;
        totalFatGrams += dailyFatGrams;
    }
}

void nutritionTracker::fillDailyCaloriesArray()
{
    cout << "Now let's log your actual calories for each day this week.\n";
    cout << "(Enter a positive number for each day.)\n\n";

    int caloriesDayTotal = 0;

    for (int day = 0; day < NUMBER_OF_DAYS; ++day)
    {
        cout << "Enter your total calories for day " << (day + 1) << ": ";
        cin >> caloriesDayTotal;

        // Repeat until the user enters a valid answer
        while (cin.fail() || caloriesDayTotal < 0)
        {
            clearInputStream();
            setConsoleColor(COLOR_ERROR);
            cout << "Please enter a positive number for the day " << (day + 1) << ": ";
            setConsoleColor(COLOR_DEFAULT);

            cin >> caloriesDayTotal;
        }

        clearInputStream();
        dailyCaloriesLog[day] = caloriesDayTotal;
    }

    // Compute actual weekly calorie total from the array
    weeklyCalories = 0;

    for (int i = 0; i < NUMBER_OF_DAYS; i++)
    {
        weeklyCalories += dailyCaloriesLog[i];
    }

    cout << "Thank you! Your weekly calorie log has been recorded.\n\n";
}

void nutritionTracker::fillSessionsFromCalories()
{
    string dayNames[NUMBER_OF_DAYS] = { "Day 1", "Day 2", "Day 3", "Day 4",
            "Day 5", "Day 6", "Day 7" };

    for (int i = 0; i < NUMBER_OF_DAYS; i++)
    {
        weeklySessions[i].date = dayNames[i];
        weeklySessions[i].calories = dailyCaloriesLog[i];

        weeklySessions[i].protein = dailyProteinGrams;
        weeklySessions[i].carbs = dailyCarbGrams;
        weeklySessions[i].fats = dailyFatGrams;

        // True if the user did not exceed their calorie target
        weeklySessions[i].metCalorieGoal = (dailyCaloriesLog[i] <= dailyCalories);
    }
}

// New function to fill 2D arrray added to program
void nutritionTracker::fillMacrosPerMeal2D()
{
    for (int day = 0; day < NUMBER_OF_DAYS; day++)
    {
        macrosPerMeal2D[0][day] = proteinPerMeal;
        macrosPerMeal2D[1][day] = carbsPerMeal;
        macrosPerMeal2D[2][day] = fatsPerMeal;
    }
}


// --------------------- Helpers ---------------------
double nutritionTracker::calculateAverageCalories() const
{
    return calculateAverageFromArray(dailyCaloriesLog, NUMBER_OF_DAYS);
}

double nutritionTracker::calculateAverageFromArray(const int values[], int size) const
{
    int sum = 0;

    for (int i = 0; i < size; i++)
        sum += values[i];

    return static_cast<double>(sum) / size;
}

int nutritionTracker::findHighestCalories() const
{
    int highest = dailyCaloriesLog[0];

    for (int day = 0; day < NUMBER_OF_DAYS; ++day)
    {
        if (dailyCaloriesLog[day] > highest)
            highest = dailyCaloriesLog[day];
    }
    return highest;
}

void nutritionTracker::evaluateMealFrequency(int mealsPerWeek)  const
{
    if (mealsPerWeek >= MEALS_PER_WEEK_MEDIUM &&
        mealsPerWeek <= MEALS_PER_WEEK_HIGH &&
        weeklyWorkoutHours >= ACTIVITY_HIGH)
    {
        cout << "Excellent meal frequency for muscle recovery! Try the smoothie below!\n\n";
    }
    else if (mealsPerWeek < MEALS_PER_WEEK_MEDIUM &&
        weeklyWorkoutHours >= ACTIVITY_MEDIUM)
    {
        cout << "Consider eating more often to support your training. Try the smoothie below!\n\n";
    }
    else if (mealsPerWeek > MEALS_PER_WEEK_HIGH)
    {
        cout << "You might be eating more than necessary — ensure portion sizes are balanced. Try the smoothie below!\n\n";
    }
    else
    {
        cout << "Your meal frequency seems appropriate for your activity level. Try the smoothie below!\n\n";
    }
}

void nutritionTracker::evaluateNutrition() const
{
    if (weeklyWorkoutHours >= ACTIVITY_HIGH && dailyCalories >= CAL_HIGH)
        cout << "Your intake is sufficient for a high activity week. Keep it up!\n\n";
    else if (weeklyWorkoutHours >= ACTIVITY_MEDIUM && dailyCalories >= CAL_MEDIUM)
        cout << "Your intake is decent for your activity level, but you could increase protein slightly.\n\n";
    else if (weeklyWorkoutHours < ACTIVITY_MEDIUM && dailyCalories < CAL_LOW)
        cout << "You might be under fueling. Consider adding extra calories per day.\n\n";
    else if (weeklyWorkoutHours < ACTIVITY_MEDIUM && dailyCalories > CAL_EXCESS)
        cout << "You may be eating more than your activity requires. Consider slightly reducing calories per day.\n\n";
    else
        cout << "Your calorie intake seems balanced for your activity level.\n\n";

    // Additional guidance based on goal(enum used in switch)
    switch (goal)
    {
    case FAT_LOSS:
        cout << "Goal: Fat loss\n";
        cout << "Aim for a small, sustainable calorie deficit and prioritize protein.\n\n";
        break;
    case MAINTENANCE:
        cout << "Goal: Maintenance\n";
        cout << "Keep your calorie intake steady and focus on consistency.\n\n";
        break;
    case MUSCLE_GAIN:
        cout << "Goal: Muscle gain\n";
        cout << "Make sure you're in a slight calorie surplus and hitting your protein target.\n\n";
        break;
    default:
        break;
    }
}


// --------------------- Display / Output ---------------------
void nutritionTracker::displayIntroBanner()
{
    setConsoleColor(COLOR_HEADER);
    printSectionBreakLine();

    cout << left << setw(5) << " "
        << " Welcome to the Vegetarian Nutrition for Weightlifters Program! "
        << right << setw(5) << " " << "\n";

    printSectionBreakLine();
    cout << "\nLet's learn more about you!\n\n";

    setConsoleColor(COLOR_DEFAULT);
}

void nutritionTracker::displayMenu() const
{
    setConsoleColor(COLOR_HEADER);
    printSectionBreakLine();
    cout << "1. View Daily Macro Targets\n"
        << "2. Generate Full Nutrition Report\n"
        << "3. Nutrition Check & Recipe Unlock\n"
        << "4. View Weekly Calorie Log\n"
        << "5. View Weekly Nutrition Sessions\n"
        << "6. View Macros Per Meal (2D Table)\n"   // New menu option
        << "7. Start a New User Session\n"
        << "8. Exit Program\n\n";
    setConsoleColor(COLOR_DEFAULT);
}

void nutritionTracker::displayDailyMacros() const
{
    setConsoleColor(COLOR_SUB_HEADING);
    printSectionBreakLine();
    cout << "You chose to view your suggested daily macros!\n\n";
    setConsoleColor(COLOR_DEFAULT);

    cout << "Here is the information you provided:\n";
    cout << left << setw(50) << setfill('.') << "Favorite protein source: " << right << favoriteProtein << "\n";
    cout << left << setw(50) << setfill('.') << "Daily calorie target: " << right << dailyCalories << "\n";
    cout << left << setw(50) << setfill('.') << "Meals per day: " << right << mealsPerDay << "\n";
    cout << left << setw(50) << setfill('.') << "Weekly workout hours: " << right << weeklyWorkoutHours << "\n\n";

    cout << "Suggested daily macros:\n";
    cout << left << setw(50) << setfill('.') << "Protein: " << right << dailyProteinGrams << " grams\n";
    cout << left << setw(50) << setfill('.') << "Carbs: " << right << dailyCarbGrams << " grams\n";
    cout << left << setw(50) << setfill('.') << "Fats: " << right << dailyFatGrams << " grams\n\n";

    cout << "Per meal macro targets:\n";
    cout << left << setw(50) << setfill('.') << "Protein grams per meal: " << right << proteinPerMeal << "\n";
    cout << left << setw(50) << setfill('.') << "Carbs grams per meal: " << right << carbsPerMeal << "\n";
    cout << left << setw(50) << setfill('.') << "Fats grams per meal: " << right << fatsPerMeal << "\n";
    cout << setfill(' ');

    setConsoleColor(COLOR_SUB_HEADING);
    printSectionBreakLine();
    cout << "Keep fueling with " << favoriteProtein << " to hit " << dailyProteinGrams << " grams of protein daily!\n";
    cout << "Remember your " << weeklyWorkoutHours << " hours of weightlifting per week...\n";
    cout << "Keep lifting heavy, " << name << "!\n\n";
    setConsoleColor(COLOR_DEFAULT);
}
 
void nutritionTracker::generateReport() const
{
    // Abosrbed previous previous programming assignment's 
    //    processReportGeneration function for simplification
    setConsoleColor(COLOR_SUB_HEADING);
    printSectionBreakLine();
    cout << "You chose to generate a report of your suggested " << "daily and weekly macros!\n";
    cout << "Open 'report.txt' to view, save, or print it.\n\n";
    printSectionBreakLine();
    setConsoleColor(COLOR_DEFAULT);


    // File writing
    ofstream outFile("report.txt");

    if (!outFile)
    {
        setConsoleColor(COLOR_ERROR);
        cout << "Error: Unable to open report.txt\n";
        setConsoleColor(COLOR_DEFAULT);
        return;
    }

    // Calculate macro calories per day for the report
    int dailyProteinCalories = dailyProteinGrams * CALORIES_PER_GRAM_PROTEIN;
    int dailyCarbCalories = dailyCarbGrams * CALORIES_PER_GRAM_CARBS;
    int dailyFatCalories = dailyFatGrams * CALORIES_PER_GRAM_FAT;

    // Report header
    outFile << setfill('*') << setw(CONSOLE_WIDTH) << '*' << "\n";
    outFile << "Vegetarian Nutrition for Weightlifters Report\n";
    outFile << setfill('*') << setw(CONSOLE_WIDTH) << '*' << "\n\n";

    outFile << "Information you provided:\n";
    outFile << left << setw(50) << setfill('.') << "Favorite protein source: " << right << favoriteProtein << "\n";
    outFile << left << setw(50) << setfill('.') << "Daily calorie target: " << right << dailyCalories << "\n";
    outFile << left << setw(50) << setfill('.') << "Weekly calorie target: " << right << weeklyCalories << "\n";
    outFile << left << setw(50) << setfill('.') << "Meals per day: " << right << mealsPerDay << "\n";
    outFile << fixed << showpoint << setprecision(2);
    outFile << left << setw(50) << setfill('.') << "Weekly workout hours: " << right << weeklyWorkoutHours << "\n\n";

    // Weekly totals
    outFile << "Suggested weekly macros:\n";
    outFile << left << setw(50) << setfill('.') << "Protein: " << right << totalProteinGrams << " grams\n";
    outFile << left << setw(50) << setfill('.') << "Carbs: " << right << totalCarbGrams << " grams\n";
    outFile << left << setw(50) << setfill('.') << "Fats: " << right << totalFatGrams << " grams\n\n";

    // Daily macros
    outFile << "Suggested total daily macros:\n";
    outFile << left << setw(50) << setfill('.') << "Protein: " << right << dailyProteinGrams << " grams (" << dailyProteinCalories << " cal)\n";
    outFile << left << setw(50) << setfill('.') << "Carbs: " << right << dailyCarbGrams << " grams (" << dailyCarbCalories << " cal)\n";
    outFile << left << setw(50) << setfill('.') << "Fats: " << right << dailyFatGrams << " grams (" << dailyFatCalories << " cal)\n\n";

    // Per-meal macros
    outFile << "Per meal macro targets:\n";
    outFile << left << setw(50) << setfill('.') << "Protein grams per meal: " << right << proteinPerMeal << "\n";
    outFile << left << setw(50) << setfill('.') << "Carbs grams per meal: " << right << carbsPerMeal << "\n";
    outFile << left << setw(50) << setfill('.') << "Fats grams per meal:  " << right << fatsPerMeal << "\n\n";

    outFile << setfill('*') << setw(CONSOLE_WIDTH) << '*' << "\n";
    outFile << "Keep fueling with " << favoriteProtein << " to hit " << dailyProteinGrams << " grams of protein daily!\n";
    outFile << "Remember your " << weeklyWorkoutHours << " hours of weightlifting per week...\n";
    outFile << "Keep lifting heavy, " << name << "!\n\n";

    outFile.close();

    // Confirm report generation in console using green success message
    setConsoleColor(COLOR_SUB_HEADING);
    cout << "Report successfully generated: report.txt\n\n";
    setConsoleColor(COLOR_DEFAULT);
}

void nutritionTracker::displayWeeklyCalorieLog() const
{
    setConsoleColor(COLOR_SUB_HEADING);
    printSectionBreakLine();
    cout << "Your Weekly Calorie Log:\n\n";
    setConsoleColor(COLOR_DEFAULT);

    if (dailyCaloriesLog[0] == 0)
    {
        cout << "No calorie data entered yet.\n";
        return;
    }

    cout << left << setw(10) << "Day" << right << setw(19) << "Calories\n";
    printSectionBreakLine();

    for (int day = 0; day < NUMBER_OF_DAYS; ++day)
    {
        cout << left << setw(10) << (day + 1) << right << setw(15) << dailyCaloriesLog[day] << endl;
    }

    cout << endl << endl;

    double averageCalories = calculateAverageCalories();
    int highestCalories = findHighestCalories();

    cout << "Average daily calories this week: " << static_cast<int>(averageCalories) << "\n";
    cout << "Highest daily calories this week: " << highestCalories << "\n\n";

    setConsoleColor(COLOR_SUB_HEADING);
    printSectionBreakLine();
    setConsoleColor(COLOR_DEFAULT);
    cout << endl;

}

void nutritionTracker::displayWeeklySessions() const
{
    setConsoleColor(COLOR_SUB_HEADING);
    printSectionBreakLine();
    cout << "Your Weekly Nutrition Summary:\n\n";
    setConsoleColor(COLOR_DEFAULT);

    cout << left << setw(10) << "Day"
        << setw(12) << "Calories"
        << setw(10) << "Protein"
        << setw(10) << "Carbs"
        << setw(10) << "Fats"
        << setw(15) << "Calorie Goal?\n";

    printSectionBreakLine();

    for (int i = 0; i < NUMBER_OF_DAYS; i++)
    {
        cout << left << setw(10) << weeklySessions[i].date
            << setw(12) << weeklySessions[i].calories
            << setw(10) << weeklySessions[i].protein
            << setw(10) << weeklySessions[i].carbs
            << setw(10) << weeklySessions[i].fats
            << setw(15) << (weeklySessions[i].metCalorieGoal ? "Yes" : "No")   // If bool is true, returns yes, otherwise returns No
            << endl;
    }

    cout << endl;
    setConsoleColor(COLOR_SUB_HEADING);
    printSectionBreakLine();
    setConsoleColor(COLOR_DEFAULT);
    cout << endl;
}

void nutritionTracker::displayNutritionCheckAndRecipe() const
{
    setConsoleColor(COLOR_SUB_HEADING);
    printSectionBreakLine();
    cout << "Checking your calorie intake vs activity level...\n\n";
    setConsoleColor(COLOR_DEFAULT);

    // Calories vs. activity and goal guidance
    evaluateNutrition();

    // Calculate meals per week before evaluating meal frequency
    int mealsPerWeek = mealsPerDay * NUMBER_OF_DAYS;
    evaluateMealFrequency(mealsPerWeek);

    // Display recipe
    displaySmoothieRecipe();
}

// New function to display menu option 4 (2D array of per meal macros)
void nutritionTracker::displayMacrosPerMeal2D() const
{
    setConsoleColor(COLOR_SUB_HEADING);
    printSectionBreakLine();
    cout << "Per-Meal Macros by Day (grams per meal)\n\n";
    cout << "All values below represent how your daily macros are\n";
    cout << "distributed evenly across each meal.\n\n";
    setConsoleColor(COLOR_DEFAULT);

    // ----- Header Row -----
    cout << left << setw(10) << "Macro";
    for (int day = 1; day <= NUMBER_OF_DAYS; day++)
        cout << setw(8) << day;
    cout << endl;

    printSectionBreakLine();

    // ----- Protein Row -----
    cout << left << setw(10) << "Protein";
    for (int day = 0; day < NUMBER_OF_DAYS; day++)
        cout << setw(8) << macrosPerMeal2D[0][day];
    cout << endl;

    // ----- Carb Row -----
    cout << left << setw(10) << "Carbs";
    for (int day = 0; day < NUMBER_OF_DAYS; day++)
        cout << setw(8) << macrosPerMeal2D[1][day];
    cout << endl;

    // ----- Fat Row -----
    cout << left << setw(10) << "Fats";
    for (int day = 0; day < NUMBER_OF_DAYS; day++)
        cout << setw(8) << macrosPerMeal2D[2][day];
    cout << endl << endl;

    // ----- Goal-Based Messaging Using Enum -----
    switch (goal)
    {
    case FAT_LOSS:
        cout << "Fat Loss Tip: Keep protein consistent at each meal\n";
        cout << "to support muscle retention while in a calorie deficit.\n";
        break;

    case MAINTENANCE:
        cout << "Maintenance Tip: These balanced macros support steady\n";
        cout << "energy and recovery throughout the week.\n";
        break;

    case MUSCLE_GAIN:
        cout << "Muscle Gain Tip: Try placing higher-carb meals around\n";
        cout << "your workouts to support strength and recovery.\n";
        break;
    }

    cout << "\nBased on " << mealsPerDay << " meals per day.\n\n";
}

void nutritionTracker::displaySmoothieRecipe() const
{
    setConsoleColor(COLOR_RECIPE);
    cout << "Oatmeal Smoothie Recipe:\n"
        << "- 1/4 cup rolled oats\n"
        << "- 2 tbsp cocoa powder\n"
        << "- 1/4 cup protein powder\n"
        << "- 1 tbsp maple syrup\n"
        << "- 1 tbsp chia seeds\n"
        << "- 1 tbsp peanut butter\n"
        << "- 3/4 cup almond milk\n\n"
        << "Blend all ingredients until smooth.\n"
        << "Protein: 30g | Carbs: 37g | Fat: 13g\n\n";
    setConsoleColor(COLOR_SUB_HEADING);
    printSectionBreakLine();
    setConsoleColor(COLOR_DEFAULT);
    cout << endl;
}