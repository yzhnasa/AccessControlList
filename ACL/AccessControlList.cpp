#include "AccessControlList.h"

AccessControlList::AccessControlList(){
	fileList.clear();
	initalizeAccessControlList();
}

void AccessControlList::initalizeAccessControlList(){
	fileList.clear();
	fstream readFileListLogFile("fileListLog.txt", ios::in);
	if (readFileListLogFile.good()){
		string fileName;
		while (!readFileListLogFile.eof()){
			getline(readFileListLogFile, fileName);
			if (fileName.empty())break;
			File tempFile(fileName);
			fileList.push_back(tempFile);
		}
	}
	readFileListLogFile.close();
}

bool AccessControlList::searchFile(string fileName){
	vector<File>::iterator itrVec;
	for (itrVec = fileList.begin(); itrVec != fileList.end(); itrVec++){
		if ((*itrVec).getFileName() == fileName){
			filePointer = &(*itrVec);
			return true;
		}
	}
	return false;
}

bool AccessControlList::readFile(User &user, File &file){
	fstream fileRead;
	string line;
	string username = user.getUsername();
	map<string, string>::iterator iterMap = file.usernameAndRight.find(username);
	if (user.getRightLevel() == "s"){
		fileRead.open(file.getFileName() + ".txt", ios::in);
		while (getline(fileRead, line)){
			cout << line << endl;
		}
		fileRead.close();
		return true;
	}
	else if (iterMap == file.usernameAndRight.end()){
		cout << "Sorry, you don't have right to read this file." << endl;
		return false;
	}
	else if (user.getRightLevel() == "a"){
		if ((*iterMap).second == "100"
			|| (*iterMap).second == "110"
			|| (*iterMap).second == "111"){
			fileRead.open(file.getFileName() + ".txt", ios::in);
			while (!fileRead.eof()){
				getline(fileRead, line);
				cout << line << endl;
			}
			fileRead.close();
			return true;
		}
		else{
			cout << "Sorry, you don't have right to read this file." << endl;
			return false;
		}
	}
	else{
		cout << "Sorry, you don't have right to read this file." << endl;
		return false;
	}
}

bool AccessControlList::writeFile(User &user, File &file){
	fstream fileWrite;
	string username = user.getUsername();
	map<string, string>::iterator iterMap = file.usernameAndRight.find(username);
	if (user.getRightLevel() == "s"){
		fileWrite.open(file.getFileName() + ".txt", ios::out);
		cout << "Now you can input your information, if you want to stop please use #." << endl;
		char inputChar;
		cin.get(inputChar);
		while (inputChar != '#'){
			cin.get(inputChar);
			if (inputChar != '#')
				fileWrite.put(inputChar);
		}
		fileWrite.close();
		return true;
	}
	else if (iterMap == file.usernameAndRight.end()){
		cout << "Sorry, you don't have right to write this file." << endl;
		return false;
	}
	else if (user.getRightLevel() == "a"){
		if ((*iterMap).second == "010"
			|| (*iterMap).second == "110"
			|| (*iterMap).second == "111"){
			cout << "Now you can input your information, if you want to stop please press ESC." << endl;
			char inputChar;
			cin.get(inputChar);
			while (inputChar != '#'){
				cin.get(inputChar);
				if (inputChar != '#')
					fileWrite.put(inputChar);
			}
			fileWrite.close();
			return true;
		}
		else{
			cout << "Sorry, you don't have right to write this file." << endl;
			return false;
		}
	}
	else{
		cout << "Sorry, you don't have right to write this file." << endl;
		return false;
	}
}
//Don't forget delete File object in AccessControlList fileList vector.
bool AccessControlList::deleteFlie(User &user, File &file){
	string username = user.getUsername();
	map<string, string>::iterator iterMap = file.usernameAndRight.find(username);
	if (user.getRightLevel() == "s"){
		string A = file.getFileName() + ".txt";
		string B = file.getFileName() + "Log.txt";
		if (remove((file.getFileName() + ".txt").c_str())){
			cout << "Failed to delete." << file.getFileName() << endl;
		}
		else{
			cout << "The file " << file.getFileName() << " have been removed." << endl;
			//_sleep(1000);
			//Sleep(10000);
			if (remove((file.getFileName() + "Log.txt").c_str())){
				cout << "Faile to delete log file." << endl;
			}
			else{
				//_sleep(1000);
				cout << "Log file have been removed." << endl;
				deleteFromAcccessControlList(file.getFileName());
				updateFileListLogFile();
			}
		}
		return true;
	}
	else if (iterMap == file.usernameAndRight.end()){
		cout << "Sorry, you don't have right to delete this file." << endl;
		return false;
	}
	else if (user.getRightLevel() == "a"){
		if ((*iterMap).second == "111"){
			remove(file.getFileName().c_str());
			string fileNameLog = file.getFileName() + "Log.txt";
			remove(fileNameLog.c_str());
			cout << "The " << file.getFileName() << " have been removed." << endl;
			delete this;
			return true;
		}
		else{
			cout << "Sorry, you don't have right to delete this file." << endl;
			return false;
		}
	}
	else{
		cout << "Sorry, you don't have right to delete this file." << endl;
		return false;
	}
}

bool AccessControlList::setUserRightForAFile(User &user, File &file, string otherUsername){
	string username = user.getUsername();
	map<string, string>::iterator iterMap = file.usernameAndRight.find(username);
	if (username == otherUsername){
		cout << "Illegal Operation." << endl;
		return false;
	}
	if (user.getRightLevel() == "s"){
		cout << "Please input " << otherUsername << " right for this file (R:100, W:010, O:111, RW:110):" << endl;
		string right;
		cin >> right;
		cout << endl;
		file.usernameAndRight[otherUsername] = right;
		return true;
	}
	else if (user.getRightLevel() == "a"){
		if ((*iterMap).second == "111"){
			cout << "Please input " << otherUsername << " right for this file (R:100, W:010, O:111, RW:110):" << endl;
			string right;
			cin >> right;
			cout << endl;
			file.usernameAndRight[otherUsername] = right;
			return true;
		}
		else{
			cout << "You don't have right to change others right for this file." << endl;
			return false;
		}
	}
	else{
		cout << "You don't have right to change others right for this file." << endl;
		return false;
	}
}

bool AccessControlList::deleteFromAcccessControlList(string fileName){
	vector<File>::iterator itrVec;
	for (itrVec = fileList.begin(); itrVec != fileList.end(); itrVec++){
		if ((*itrVec).getFileName() == fileName){
			fileList.erase(itrVec);
			return true;
		}
	}
	return false;
}

bool AccessControlList::deleteAUserFromAllFile(User &user, string otherUsername){
	if (user.getUsername() == otherUsername || user.getRightLevel() == "s"){
		vector<File>::iterator itrVec;
		for (itrVec = fileList.begin(); itrVec != fileList.end(); itrVec++){
			(*itrVec).deleteAFileUser(otherUsername);
		}
		return true;
	}
	return false;
}

void AccessControlList::dispalyAUserInformation(User &user, string otherUsername){
	vector<File>::iterator itrVec;
	for (itrVec = fileList.begin(); itrVec != fileList.end(); itrVec++){
		if ((*itrVec).searchAFileUser(otherUsername)){
			cout << "Filename: " << (*itrVec).getFileName() << endl;
			cout << "User Right: " << (*itrVec).displayAFileUser(otherUsername) << endl;
		}
	}
}

void AccessControlList::updateFileListLogFile(){
	fstream writeFileListLogFile("fileListLog.txt", ios::out);
	vector<File>::iterator itrVec;
	for (itrVec = fileList.begin(); itrVec != fileList.end(); itrVec++){
		writeFileListLogFile << (*itrVec).getFileName() << endl;
	}
	writeFileListLogFile.close();
}

AccessControlList::~AccessControlList(){
	updateFileListLogFile();
	filePointer = NULL;
	delete filePointer;
}