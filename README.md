# Final_Project

Project 1:
Number_Guessing_Game
Overview

This Number Guessing Game allows players to test their guessing skills across different modes with a leaderboard system to track scores. Players can earn points, use hints, and manage lifelines while trying to guess numbers within a user-defined range.

Features

Multiple Game Modes: Choose from Easy, Medium, Hard, Expert, and Legendary modes, each with different difficulty levels and rules. Leaderboard: Track scores of all players, with points earned for correct guesses and game performance. Hints System: Players can use hints to help narrow down their guesses. Hints can be bought using points. Lifelines: Players start with a set number of lifelines, which can be lost during gameplay but can also be refilled for points.

Usage

Enter Your Name: When prompted, input your name to track your scores. Choose an Option: Select from the menu to play the game, view the leaderboard, buy hints, check player stats, or exit. Play the Game: Follow the prompts to guess numbers within your chosen range.

Game Modes

Easy: 8 tries, 5 hints available. Medium: 7 tries, 3 hints available. Hard: 5 tries, 1 hint available. Expert: 3 tries, no hints available. Legendary: 1 try, no hints available (with special rules for low ranges).

Game Logic

Players are required to guess numbers generated based on the selected mode. If the range is less than 20 and the mode is Legendary, only three numbers are generated, and the player must guess one of these. Players earn points for correct guesses and can lose lifelines for incorrect guesses. Leaderboard Management Player data is saved in 'leaderboard.txt'. The leaderboard includes player names, points, hints left for each mode, and lifelines


Project 2:
To-do_List
This is a simple command-line To-Do List application written in C++. It allows users to manage tasks with functionalities such as adding, removing, listing tasks, checking overdue tasks, and undoing last actions.

Features
Add Tasks: Create a new task with a description, category, priority, and due date.
List Tasks: View all tasks sorted by priority.
Remove Tasks: Delete a task from the list.
Undo Last Action: Revert the last task addition or removal.
Check Past Due Tasks: Display tasks that are overdue.
Persistent Storage: Tasks are saved to and loaded from a text file.
Usage Upon running the application, you'll be presented with a menu to choose from the following options:

Add Task List Tasks by Priority Remove Task Undo Last Action Check Past Due Tasks Exit


Project 3:
Social_Media_Simulation
This project is a simple console-based social media simulation that allows users to create accounts, send messages, manage friendships, and organize themselves into social groups.

Features User Management: Add new users with usernames, first names, last names, age, and gender. Friend Management: Users can become friends, unfriend each other, and view their friendships. Messaging: Users can send direct messages to one another and view their message history. Group Management: Create social groups, add or remove members, and send messages within groups. Display Information: View all users, friendships, and detailed group information.

Usage Once the program is running, you will be presented with a menu of options. You can choose an option by entering the corresponding number:

Add User: Create a new user account. Make Friends: Add another user as a friend. Unfriend: Remove a friend from your friend list. Send Message: Send a direct message to another user. Create Group: Create a new social group. Add Member to Group: Add an existing user to a group. Send Group Message: Send a message to all members of a group. Remove Member from Group: Remove a user from a group. Display All Users: Show a list of all registered users. Display All Friendships: View all friendships in the system. Display Group Info: Show information about a specific group. Exit: Exit the program. Code Structure Message Class: Handles the creation and display of messages between users. SocialGroup Class: Manages group creation, member addition/removal, and group messaging. User Class: Represents a user in the social media simulation. Global Data Structures: Maps and sets to store users, friendships, groups, and messages.

Contributions Contributions are welcome! If you have suggestions for improvements or new features, please open an issue or submit a pull request.
