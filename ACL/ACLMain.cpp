#include "CommonHeader.h"
#include "File.h"
#include "User.h"
#include "UserList.h"
#include "AccessControlList.h"
#include "Command.h"

int main(int argc, char **argv){
	if (argc != 2){
		cout << "Error in arguments." << endl;
		exit(1);
	}

	if (strcmp(argv[1], "-r") == 0){
		AccessControlList accessControlList;
		UserList userList;
		cout << "Please set your username: ";
		string username;
		cin >> username;
		cout << endl;
		cout << "Please set your password: ";
		string password;
		cin >> password;
		cout << endl;
		cout << "Please set your right level(s/a): ";//s is superuser; a is averageuser.
		string rightLevel;
		cin >> rightLevel;
		cout << endl;
		User user(username, password, rightLevel);
		if (userList.addNewUser(user)){
			cout << "Register new account success." << endl;
		}
		else{
			cout << "This username has been used, please change to other username." << endl;
		}
	}
	else if (strcmp(argv[1], "-l") == 0){
		AccessControlList accessControlList;
		UserList userList;
		Command commandExecution;
		cout << "Please input your username: ";
		string username;
		cin >> username;
		cout << endl;
		cout << "Please input your password: ";
		string password;
		cin >> password;
		cout << endl;
		User user;
		user.setUsername(username);
		user.setPassword(password);
		if (!userList.haveThisUser(user)){
			cout << "Sorry, there are some problem about your username or password." << endl;
			return 0;
		}
		string userRightLevel = userList.getUserRightLevel(username);
		user.setRightLevel(userRightLevel);
		cout << "Welcome User!" << endl;
		cout << "Please imput your command number." << endl;
		cout << "A:search a file." << endl;
		cout << "B:create a file." << endl;
		cout << "C:read information about a file." << endl;
		cout << "D:read contents from a file." << endl;
		cout << "E:write contents to a file." << endl;
		cout << "F:delete a file." << endl;
		cout << "G:change username." << endl;
		cout << "H:change password." << endl;
		cout << "I:search an user." << endl;
		cout << "J:read information about an user." << endl;
		cout << "K:change a user's right for a file." << endl;
		cout << "L:change user's right level." << endl;
		cout << "M:delete a user." << endl;
		cout << "N:exit the program." << endl;
		
		bool exitProgram = false;
		char command;
		while (!exitProgram){
			cout << "Please enter command: ";
			cin >> command;
			cout << endl;
			if (islower(command)){
				command = toupper(command);
			}
			if (command == 'A'){
				commandExecution.searchAFile(accessControlList);
			}
			else if (command == 'B'){
				commandExecution.createFile(accessControlList, user);
			}
			else if (command == 'C'){
				commandExecution.readFileInformation(accessControlList);
			}
			else if (command == 'D'){
				commandExecution.readFileContents(accessControlList, user);
			}
			else if (command == 'E'){
				commandExecution.writeIntoFile(accessControlList, user);
			}
			else if (command == 'F'){
				commandExecution.deleteFile(accessControlList, user);
			}
			else if (command == 'G'){
				commandExecution.changeUsername(accessControlList, userList, user);
			}
			else if (command == 'H'){
				commandExecution.changePassword(userList, user);
			}
			else if (command == 'I'){
				commandExecution.searchAUser(userList, user);
			}
			else if (command == 'J'){
				commandExecution.readUserInformation(accessControlList, user);
			}
			else if (command == 'K'){
				commandExecution.changeFileUserRight(accessControlList, user);
			}
			else if (command == 'L'){
				commandExecution.changeUserRightLevel(userList, user);
			}
			else if (command == 'M'){
				commandExecution.deleteUser(accessControlList, userList, user);
			}
			else if (command == 'N'){
				cout << "Good bye user!" << endl;
				exitProgram = true;
			}
			else{
				cout << "Please re-enter command number from A to N." << endl;
				break;
			}
		}
	}
	else{
		cout << "No such argument." << endl;
		exit(1);
	}
	return 0;
}