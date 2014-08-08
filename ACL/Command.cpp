#include "Command.h"

void Command::createFile(AccessControlList &accessControlList, User &user){
	string fileName;
	cout << "Please input your file name: ";
	cin >> fileName;
	//Chack file name for avoid same name.
	cout << endl;
	if (accessControlList.searchFile(fileName)){
		cout << "This file name already exist, please change to others." << endl;
	}
	else{
		File newFile;
		newFile = user.creatFile(fileName);
		accessControlList.fileList.push_back(newFile);
	}
}

void Command::deleteFile(AccessControlList &accessControlList, User &user){
	cout << "Please input the file name you want to delete: ";
	string fileName;
	cin >> fileName;
	if (accessControlList.searchFile(fileName)){
		accessControlList.deleteFlie(user, *accessControlList.filePointer);
	}
	else{
		cout << "Sorry, no such file." << endl;
	}
}

void Command::deleteUser(AccessControlList &accessControlList, UserList &userList, User &user){
	cout << "Please input username you want to remove form system: ";
	string otherUsername;
	cin >> otherUsername;
	accessControlList.deleteAUserFromAllFile(user, otherUsername);
	userList.deleteUserFromUserList(user, otherUsername);
}

void Command::readFileInformation(AccessControlList &accessControlList){
	cout << "Please input a file name: ";
	string filename;
	cin >> filename;
	if (accessControlList.searchFile(filename)){
		cout << "File name: " << (*accessControlList.filePointer).getFileName() << endl;
		cout << "Users of this file: " << endl;
		(*accessControlList.filePointer).displayAllFileUser();
	}
	else{
		cout << "Cannot find this file." << endl;
	}
}

void Command::readFileContents(AccessControlList &accessControlList, User &user){
	cout << "Please input the file name you want to read: ";
	string fileName;
	cin >> fileName;
	if (accessControlList.searchFile(fileName)){
		accessControlList.readFile(user, *accessControlList.filePointer);
	}
}

void Command::readUserInformation(AccessControlList &accessControlList, User &user){
	cout << "Please input username which you want to read the information: ";
	string otherUsername;
	cin >> otherUsername;
	accessControlList.dispalyAUserInformation(user, otherUsername);
}

void Command::writeIntoFile(AccessControlList &accessControlList, User &user){
	cout << "Please input the file you want to write: ";
	string fileName;
	cin >> fileName;
	if (accessControlList.searchFile(fileName)){
		accessControlList.writeFile(user, *accessControlList.filePointer);
	}
}

void Command::changeFileUserRight(AccessControlList &accessControlList, User &user){
	cout << "Please input the username which you want to change it right: ";
	string otherUsername;
	cin >> otherUsername;
	cout << endl;
	cout << "Please input the file name which you want to change it file user right: ";
	string filename;
	cin >> filename;
	if (accessControlList.searchFile(filename)){
		accessControlList.setUserRightForAFile(user, *accessControlList.filePointer, otherUsername);
	}
	else{
		cout << "Sorry, no such file." << endl;
	}
}

void Command::changeUserRightLevel(UserList &userList, User &user){
	cout << "Please input the username which you want to change his right level: ";
	string otherUsername;
	cin >> otherUsername;
	userList.setUserRightLevel(user, otherUsername);
}

void Command::changeUsername(AccessControlList &accessControlList, UserList &userList, User &user){
	string tempUsername = user.getUsername();
	userList.changeUsername(user);
	vector<File>::iterator itrVec;
	for (itrVec = accessControlList.fileList.begin(); itrVec != accessControlList.fileList.end(); itrVec++){
		if ((*itrVec).searchAFileUser(tempUsername)){
			string tempUserRight = (*itrVec).tempUserRight;
			(*itrVec).usernameAndRight.erase(tempUsername);
			(*itrVec).usernameAndRight[userList.newUsername] = tempUserRight;
		}
	}
}

void Command::changePassword(UserList &userList, User &user){
	userList.changePassword(user);
}

void Command::searchAFile(AccessControlList &accessControlList){
	cout << "Please input a file name: ";
	string filename;
	cin >> filename;
	if (accessControlList.searchFile(filename)){
		cout << "System have this file." << endl;
	}
	else{
		cout << "Cannot find this file from system." << endl;
	}
}

void Command::searchAUser(UserList &userList, User &user){
	cout << "Please input the user you want to search: ";
	string otherUsername;
	cin >> otherUsername;
	if (userList.searchUser(user, otherUsername)){
		cout << "Sysem have record this user." << endl;
	}
	else{
		cout << "Cannot find this user." << endl;
	}
}