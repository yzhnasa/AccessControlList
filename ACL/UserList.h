#ifndef UserList_H
#define UserList_H
#include "CommonHeader.h"
#include "User.h"

class UserList{
private:
	map<string, string> usernameAndPassword;
	map<string, string> usernameAndRightLevel;
	void initializeUserList();
	bool chackWhetherThisUsernameExist(string username);
	void updateUserListFile();
public:
	string newUsername;
	explicit UserList();
	bool haveThisUser(User &user);//For a user login.
	bool searchUser(User &thisUser, string otherUsername);//For superUser.
	bool addNewUser(User &user);
	bool setUserRightLevel(User &thisUser, string otherUsername);
	string getUserRightLevel(string username);
	void changeUsername(User &user);
	void changePassword(User &user);
	bool deleteUserFromUserList(User &thisUser, string otherUsername);
	~UserList();
};

#endif