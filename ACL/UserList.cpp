#include "UserList.h"

UserList::UserList(){
	usernameAndPassword.clear();
	initializeUserList();
}

void UserList::initializeUserList(){
	usernameAndPassword.clear();
	fstream inputFile("UserListLog.txt", ios::in);
	if (inputFile.good()){
		string tempUsername;
		string tempPassword;
		string tempRightLevel;
		while (!inputFile.eof()){
			getline(inputFile, tempUsername);
			if (tempUsername.empty())break;
			getline(inputFile, tempPassword);
			getline(inputFile, tempRightLevel);
			usernameAndPassword[tempUsername] = tempPassword;
			usernameAndRightLevel[tempUsername] = tempRightLevel;
		}
	}
	inputFile.close();
}

bool UserList::haveThisUser(User &user){
	string username = user.getUsername();
	string password = user.getPassword();
	map<string, string>::iterator itrMap = usernameAndPassword.find(username);
	if (itrMap == usernameAndPassword.end()){
		cout << "Cannot find this user." << endl;
		return false;
	}
	if ((*itrMap).second != password){
		cout << "Passord wrong." << endl;
		return false;
	}
	return true;
}

bool UserList::searchUser(User &thisUser, string otherUsername){
	if (thisUser.getRightLevel() == "s"){
		map<string, string>::iterator itrMap = usernameAndPassword.find(otherUsername);
		if (itrMap == usernameAndPassword.end()){
			return false;
		}
		cout << "This user's password is: " << (*itrMap).second << endl;
		return true;
	}
	else{
		cout << "Sorry, you don't have right to search user list" << endl;
		return false;
	}
}

bool UserList::chackWhetherThisUsernameExist(string username){
	map<string, string>::iterator itrMap = usernameAndPassword.find(username);
	if (itrMap == usernameAndPassword.end()){
		return true;
	}
	return false;
}

bool UserList::addNewUser(User &user){
	string username = user.getUsername();
	string password = user.getPassword();
	string rightLevel = user.getRightLevel();
	if (chackWhetherThisUsernameExist(username)){
		usernameAndPassword[username] = password;
		usernameAndRightLevel[username] = rightLevel;
		return true;
	}
	return false;
}

bool UserList::setUserRightLevel(User &thisUser, string otherUsername){
	if (thisUser.getRightLevel() == "a"){
		cout << "Sorry, you don't have right to Change user right." << endl;
		return false;
	}
	else if (thisUser.getRightLevel() == "s"){
		cout << "Please input right leve: ";
		string level;
		cin >> level;
		map<string, string>::iterator itrMap = usernameAndRightLevel.find(otherUsername);
		(*itrMap).second = level;
		updateUserListFile();
		return true;
	}
	return false;
}

string UserList::getUserRightLevel(string username){
	map<string, string>::iterator itrMap = usernameAndRightLevel.find(username);
	return (*itrMap).second;
}

bool UserList::deleteUserFromUserList(User &thisUser, string otherUsername){
	if (thisUser.getRightLevel() == "a"){
		cout << "Sorry, you don't have right to delete user from user list" << endl;
		return false;
	}
	else if (thisUser.getRightLevel() == "s"){
		map<string, string>::iterator itrMap1 = usernameAndPassword.find(otherUsername);
		usernameAndPassword.erase(itrMap1);
		map<string, string>::iterator itrMap2 = usernameAndRightLevel.find(otherUsername);
		usernameAndRightLevel.erase(itrMap2);
		cout << "User " << otherUsername << " have been delete successfully." << endl;
		return true;
	}
	else{
		cout << "Sorry, you don't have right to delete user from user list" << endl;
		return false;
	}
}

void UserList::changeUsername(User &user){
	cout << "Please input password: ";
	string currentPassword;
	cin >> currentPassword;
	map<string, string>::iterator itrMap1 = usernameAndPassword.find(user.getUsername());
	if (currentPassword == (*itrMap1).second){
		map<string, string>::iterator itrMap2 = usernameAndRightLevel.find(user.getUsername());
		cout << "Please input new username: ";
		cin >> newUsername;
		string tempPassword = (*itrMap1).second;
		string tempRightLevel = (*itrMap2).second;
		usernameAndPassword.erase(itrMap1);
		usernameAndRightLevel.erase(itrMap2);
		usernameAndPassword[newUsername] = tempPassword;
		usernameAndRightLevel[newUsername] = tempRightLevel;
		cout << "Reset username success." << endl;
	}
	else{
		cout << "Reset username fail." << endl;
	}
}

void UserList::changePassword(User &user){
	cout << "Please input password: ";
	string currentPassword;
	cin >> currentPassword;
	map<string, string>::iterator itrMap1 = usernameAndPassword.find(user.getUsername());
	if (currentPassword == (*itrMap1).second){
		cout << "Please input new password: ";
		string newPassword;
		cin >> newPassword;
		usernameAndPassword[user.getUsername()] = newPassword;
		cout << "Reset password success." << endl;
	}
	else{
		cout << "Reset password fail." << endl;
	}
}

void UserList::updateUserListFile(){
	fstream outFile("UserListLog.txt", ios::out);
	map<string, string>::iterator itrMap1;
	map<string, string>::iterator itrMap2 = usernameAndRightLevel.begin();
	for (itrMap1 = usernameAndPassword.begin(); itrMap1 != usernameAndPassword.end(); itrMap1++){
		outFile << (*itrMap1).first << endl;
		outFile << (*itrMap1).second << endl;
		outFile << (*itrMap2).second << endl;
		itrMap2++;
	}
}

UserList::~UserList(){
	updateUserListFile();
}