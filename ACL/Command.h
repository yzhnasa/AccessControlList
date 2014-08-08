#ifndef Command_H
#define Command_H
#include "CommonHeader.h"
#include "AccessControlList.h"
#include "UserList.h"
#include "User.h"

class Command{
public:
	void createFile(AccessControlList &accessControlList, User &user);
	void deleteFile(AccessControlList &accessControlList, User &user);
	void deleteUser(AccessControlList &accessControlList, UserList &userList, User &user);
	void readFileInformation(AccessControlList &accessControlList);
	void readFileContents(AccessControlList &accessControlList, User &user);
	void readUserInformation(AccessControlList &accessControlList, User &user);
	void writeIntoFile(AccessControlList &accessControlList, User &user);
	void changeFileUserRight(AccessControlList &accessControlList, User &user);
	void changeUserRightLevel(UserList &userList, User &user);
	void changeUsername(AccessControlList &accessControlList, UserList &userList, User &user);
	void changePassword(UserList &userList, User &user);
	void searchAFile(AccessControlList &accessControlList);
	void searchAUser(UserList &userList, User &user);
};

#endif