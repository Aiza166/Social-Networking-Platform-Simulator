#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
using namespace std;

class Entity;
class User;
class Account;
class CommentsAndLikes;

class CommentsAndLikes
{
protected:
    int likes = 0;
    static const int MAX_COMMENTS = 10;
    string comments[MAX_COMMENTS];
    int comment_Count = 0;

public:
    virtual void display() = 0;
    virtual ~CommentsAndLikes() {}

    void addLike()
    {
        likes++;
    }

    void addComment(string comment)
    {
        if (comment_Count < MAX_COMMENTS)
        {
            comments[comment_Count++] = comment;
        }
    }
};

class Story : public CommentsAndLikes
{
    string content;
    string author;

public:
    Story(string _content, string _author) : content(_content), author(_author) {}

    void display()
    {
        cout << "Author: " << author << endl;
        cout << "Content: " << content << endl;
        cout << "Likes: " << likes << endl;
        cout << "Comments:" << endl;
        for (int i = 0; i <= comment_Count; i++)
        {
            cout << comments[i] << endl;
        }
    }
};

class Post : public CommentsAndLikes
{
    string content;
    string author;

public:
    Post(string _content, string _author) : content(_content), author(_author) {}

    void display()
    {
        cout << "Author: " << author << endl;
        cout << "Content: " << content << endl;
        cout << "Likes: " << likes << endl;
        cout << "Comments:" << endl;
        for (int i = 0; i <= comment_Count; i++)
        {
            cout << comments[i] << endl;
        }
    }
};

// Abstract class representing an Enity (User or Account)
class Entity
{
protected:
    string name;

public:
    Entity(string _name) : name(_name) {}
    virtual ~Entity() {}

    virtual void displayContent() = 0;
    virtual void addPost(Post *post) = 0;
    virtual void addStory(Story *story) = 0;
    virtual string getName()
    {
        return name;
    }
};

// Class representing a User
class User : public Entity
{
private:
    static const int MAX_FOLLOWERS = 10;
    static const int MAX_CONTENT = 10;

    User *followers[MAX_FOLLOWERS];
    Post *posts[MAX_CONTENT];
    Story *stories[MAX_CONTENT];
    int follower_Count = 0;
    int posts_Count = 0;
    int story_Count = 0;
    string encrytedPassword;

string encryptPassword(string password)
{
    string encrypted = password;
    string key = "secretkey"; 

    for (int i = 0; i < encrypted.length(); i++)
    {
        encrypted[i] = encrypted[i] + key[i % key.length()];
    }
    return encrypted;
}


public:
    User(string _name, string _password) : Entity(_name)
    {
        encrytedPassword = encryptPassword(_password);
    }

    bool authenticate(string password)
    {
        return (encryptPassword(password) == encrytedPassword) ? true : false;
    }

    void addFollower(User *follower)
    {
        for (int i = 0; i <= follower_Count; i++)
        {
            if (followers[i] == follower)
            {
                cout << followers[i]->getName() << " is already in the following list" << endl;
                return;
            }
        }
        if (follower_Count < MAX_FOLLOWERS)
        {
            followers[follower_Count++] = follower;
            cout << follower->getName() << " added to the following list" << endl;
        }
        else
        {
            cout << "Following list is fully occupied. Can not add more" << endl;
        }
    }

    void addPost(Post *post)
    {
        if (posts_Count < MAX_CONTENT)
        {
            posts[posts_Count++] = post;
            cout << "Post number " << posts_Count << " has been added" << endl;
        }
        else
        {
            cout << "Can not add more than 10 posts" << endl;
        }
    }
    void addStory(Story *story)
    {
        if (story_Count < MAX_CONTENT)
        {
            stories[story_Count++] = story;
            cout << "Story number " << story_Count << " has been added" << endl;
        }
        else
        {
            cout << "Can not add more than 10 stories" << endl;
        }
    }


    void displayContent()
    {
        cout << "Content by User " << getName() << ":" << endl;
        cout << "Posts:" << endl;
        for (int i = 0; i <= posts_Count; i++)
        {
            cout << "Post " << i + 1 << endl;
            posts[i]->display();
        }
        cout << "Stories:" << endl;
        for (int i = 0; i <= story_Count; i++)
        {
            cout << "Story " << i + 1 << endl;
            stories[i]->display();
        }
    }
    void setName(string username){
        name = username;
    }
    void setEncryptedPassword(string encrypted_pass){
        encrytedPassword = encrypted_pass;
    }
    static void saveInfoToFile(ofstream &file, User *user)
    {
        file<<user->getName()<<endl;
        file<<user->encrytedPassword<<endl;
    }
    static void readInfoFromFile(ifstream &file, User *user) {
        string name, encrypted_pass;
        getline(cin,name);
        getline(cin,encrypted_pass);
        user->setName(name);
        user->setEncryptedPassword(encrypted_pass);
    }
    int getFollowerCount()
    {
        return follower_Count;
    }

    int PostsCount()
    {
        return posts_Count;
    }

    int StoriesCount()
    {
        return story_Count;
    }

    // Getter for post
    Post *getPost(int index)
    {
        if (index >= 0 && index < MAX_CONTENT)
        {
            return posts[index];
        }
        else
        {
            return NULL;
        }
    }

    // Getter for story
    Story *getstory(int index)
    {
        if (index >= 0 && index < MAX_CONTENT)
        {
            return stories[index];
        }
        else
        {
            return NULL;
        }
    }

    void createPost()
    {
        string postContent;
        cout << "Enter your post content: ";
        getline(cin, postContent);
        Post *post = new Post(postContent, getName());
        addPost(post);
    }

    void createStory()
    {
        string storyContent;
        cout << "Enter your story content: ";
        getline(cin, storyContent);
        Story *story = new Story(storyContent, getName());
        addStory(story);
    }

    void likePost(int postindex)
    {
        if (postindex >= 0 && postindex < MAX_CONTENT)
        {
            posts[postindex]->addLike();
            cout << "Post " << postindex + 1 << " has been liked" << endl;
        }
        else
        {
            cout << "Post number is not valid" << endl;
        }
    }
    void CommentOnPost(string comment, int postindex)
    {
        if (postindex >= 0 && postindex < MAX_CONTENT)
        {
            posts[postindex]->addComment(comment);
            cout << "Comment on post " << postindex + 1 << " has been added" << endl;
        }
        else
        {
            cout << "Post number is not valid" << endl;
        }
    }

    void likeStory(int storyindex)
    {
        if (storyindex >= 0 && storyindex < MAX_CONTENT)
        {
            stories[storyindex]->addLike();
            cout << "Story " << storyindex + 1 << " has been liked" << endl;
        }
        else
        {
            cout << "Story index is not valid" << endl;
        }
    }
    void UpdatePassword(string new_password)
    {
        encrytedPassword = encryptPassword(new_password);
    }
};

// class representing an Account (page)
class Account : public Entity
{
    static const int MAX_FOLLOWERS = 10;
    static const int MAX_CONTENT = 10;

    User *followers[MAX_FOLLOWERS];
    Post *posts[MAX_CONTENT];
    Story *stories[MAX_CONTENT];
    int follower_Count = 0;
    int posts_Count = 0;
    int story_Count = 0;

public:
    Account(string _name) : Entity(_name) {}

    void addFollower(User *follower)
    {
        for (int i = 0; i <= follower_Count; i++)
        {
            if (followers[i] == follower)
            {
                cout << followers[i]->getName() << " is already in the following list" << endl;
                return;
            }
        }
        if (follower_Count < MAX_FOLLOWERS)
        {
            followers[follower_Count++] = follower;
            cout << follower->getName() << " added to the following list" << endl;
        }
        else
        {
            cout << "Following list is fully occupied. Can not add more" << endl;
        }
    }

    void addPost(Post *post)
    {
        if (posts_Count < MAX_CONTENT)
        {
            posts[posts_Count++] = post;
            cout << "Post number " << posts_Count << " has been added" << endl;
        }
        else
        {
            cout << "Can not add more than 10 posts" << endl;
        }
    }
    void addStory(Story *story)
    {
        if (story_Count < MAX_CONTENT)
        {
            stories[story_Count++] = story;
            cout << "Story number " << story_Count << " has been added" << endl;
        }
        else
        {
            cout << "Can not add more than 10 stories" << endl;
        }
    }

    void displayContent()
    {
        cout << "Content by User " << getName() << ":" << endl;
        cout << "Posts:" << endl;
        for (int i = 0; i <= posts_Count; i++)
        {
            cout << "Post " << i + 1 << endl;
            posts[i]->display();
        }
        cout << "Stories:" << endl;
        for (int i = 0; i <= story_Count; i++)
        {
            cout << "Story " << i + 1 << endl;
            stories[i]->display();
        }
    }

    int getFollowerCount()
    {
        return follower_Count;
    }

    int PostsCount()
    {
        return posts_Count;
    }

    int StoriesCount()
    {
        return story_Count;
    }

    // Getter for post
    Post *getPost(int index)
    {
        if (index >= 0 && index < MAX_CONTENT)
        {
            return posts[index];
        }
        else
        {
            return NULL;
        }
    }

    // Getter for story
    Story *getstory(int index)
    {
        if (index >= 0 && index < MAX_CONTENT)
        {
            return stories[index];
        }
        else
        {
            return NULL;
        }
    }

    void createPost()
    {
        string postContent;
        cout << "Enter your post content: ";
        getline(cin, postContent);
        Post *post = new Post(postContent, getName());
        addPost(post);
    }

    void createStory()
    {
        string storyContent;
        cout << "Enter your story content: ";
        getline(cin, storyContent);
        Story *story = new Story(storyContent, getName());
        addStory(story);
    }

    void likePost(int postindex)
    {
        if (postindex >= 0 && postindex < MAX_CONTENT)
        {
            posts[postindex]->addLike();
        }
    }
    void CommentOnPost(string comment, int postindex)
    {
        if (postindex >= 0 && postindex < MAX_CONTENT)
        {
            posts[postindex]->addComment(comment);
        }
    }

    void likeStory(int storyindex)
    {
        if (storyindex >= 0 && storyindex < MAX_CONTENT)
        {
            stories[storyindex]->addLike();
        }
    }
};
void saveUserInfoToFile(User *users[], int numUsers) {
    ofstream file("UserInfo.txt",ios::app);
    if (!file) {
        cout << "File creation Failed" << endl;
        return;
    }
    
    for (int i = 0; i < numUsers; i++) {
        User::saveInfoToFile(file, users[i]);
    }
    file.close();
}
void readUserInfoFromFile(User *users[], int &numUsers) {
    ifstream file("UserInfo.txt");
    if (!file) {
        cout << "File reading failed" << endl;
        return;
    }
    
    numUsers = 0;
    while (!file.eof()) {
        string username,password;
        getline(file,username);
        getline(file,password);
        users[numUsers] = new User("", "");
        users[numUsers]->setName(username);
        users[numUsers]->setEncryptedPassword(password);
        //User::readInfoFromFile(file,users[numUsers]);
        numUsers++;
    }
    file.close();
}
int main()
{
    const int MAX_USERS = 10;
    User *users[MAX_USERS];
    int numUsers = 0;
    //readUserInfoFromFile(users, numUsers);
    int z = 1;
    while (z == 1)
    {
        cout << "\nChoose an action\n";
        cout << "1. Login\n";
        cout << "2. Create a new account" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
        {               
            readUserInfoFromFile(users, numUsers);
            string username, password;
            cout << "Enter username: ";
            getline(cin,username);
            //cin.ignore();
            //sleep(3);
            cout << "Enter password: ";
            getline(cin,password);
            cout << "\nPlease wait..." << endl;
            //cin.ignore();
			sleep(3);
            

            int found = 0;
            for (int i = 0; i < numUsers; i++)
            {
                if (users[i]->getName() == username)
                {
                    found=1;
                    if (users[i]->authenticate(password))
                    {
                        cout << "Login Successfull" << endl;
                        sleep(1);
                        //users[i]->displayContent();

                        
                        int m = 1;
                        while (m == 1)
                        {
                            
                            cout << "Choose an action:" << endl;
                            cout << "1. Create Post" << endl;
                            cout << "2. Create Story" << endl;
                            cout << "3. Like a post" << endl;
                            cout << "4. Comment on a post" << endl;
                            cout << "5. Like a story" << endl;
                            cout << "6. Change password" << endl;
                            cout << "7. Delete Account" << endl;
                            cout<<  "8. Display content"<<endl;
                            cout << "9. Follow a user" << endl;
                            cout << "10. Exit" << endl; 
                            
                            cout << "Enter your choice: ";
                            int actionChoice;
                            cin >> actionChoice;
                            cin.ignore();

                            system("cls");
                            switch (actionChoice)
                            {
                            case 1:
                                users[i]->createPost();
                                break;

                            case 2:
                                users[i]->createStory();
                                break;

                            case 3:
                                int post_index;
                                cout << "Enter post number: " << endl;
                                cin >> post_index;
                                users[i]->likePost(post_index - 1);
                                break;

                            case 4:
                            {
                                int post_index;
                                cout << "Enter post number: ";
                                cin >> post_index;
                                string comment;
                                cout << "Enter the comment: ";
                                getline(cin, comment);
                                users[i]->CommentOnPost(comment, post_index - 1);
                                break;
                            }

                            case 5:
                                int story_index;
                                cout << "Enter story number: ";
                                cin >> story_index;
                                users[i]->likeStory(story_index - 1);
                                break;

                            case 6:
                            {
                                string oldPassword, newPassword;
                                cout << "Enter current password: ";
                                getline(cin, oldPassword);
                                if (users[i]->authenticate(oldPassword))
                                {
                                    cout << "Enter new password: ";
                                    getline(cin, newPassword);
                                    users[i]->UpdatePassword(newPassword);
                                    cout << "Please wait..." << endl;
                                    sleep(3);
                                    cout << "Password has been successfully changed" << endl;
                                }
                                else
                                {
                                    cout << "Incorrect password.Please try again" <<endl;
                                }
                                break;
                            }

                            case 7:
                            {
                                char confirmDelete;
                                cout<<"Are you sure you want to delete your account? (Y/n): ";
                                cin>>confirmDelete;
                                cin.ignore();
                                
                                if(confirmDelete == 'Y' || confirmDelete == 'y')
                                {
                                    delete users[i];

                                    for(int k=i;k<numUsers-1;k++)
                                    {
                                        users[k] = users[k+1];
                                    }
                                    numUsers--;
                                    cout<<"Please wait..."<<endl;
                                    sleep(2);
                                    cout<<"Account deleted successfully"<<endl;
                                    sleep(1);
                                }
                                m=0;
                                break;
                            }
                            case 8:
                            users[i]->displayContent();
							break;
							
							case 9:
							cout << "Choose a user to follow:" << endl;
	                        for (int j = 0; j < numUsers; j++)
	                        {
	                            if (users[j]->getName() != username)
	                            {
	                                cout << j + 1 << ". " << users[j]->getName() << endl;
	                            }
	                        }
	
	                        int followChoice;
	                        cout << "Enter the number of the user you want to follow: ";
	                        cin >> followChoice;
	                        cin.ignore();
	
	                        if (followChoice > 0 && followChoice <= numUsers)
	                        {
	                            users[i]->addFollower(users[followChoice - 1]);
	                            cout << "You are now following " << users[followChoice - 1]->getName() << endl;
	                        }
	                        else
	                        {
	                            cout << "Invalid choice. Please enter a valid user number." << endl;
	                        }
	                        
                        
                            case 10:
                            cout<<"Exiting...\n";
                            sleep(2);
                            z=0;
                            m=0;
                            break;

                            default:
                            cout<<"Invalid choice.Please try again"<<endl;
                            sleep(1);
                            }
                        }
                    }
                }
            }
            if(found==0)
            {
                cout<<"Invalid Password. Please try again."<<endl;
                sleep(1);
            }
            break;
        }

            case 2:{

            
            //readUserInfoFromFile(users,numUsers);
            
            string newUsername,newPassword;
            cout<<"Enter username: ";
            getline(cin,newUsername);
            cout<<"Enter password: ";
            getline(cin,newPassword);

            if(numUsers<MAX_USERS){
                User *user = new User(newUsername,newPassword);

                users[numUsers++] = user; 
                cout<<"Account created successfully"<<endl;
            }
            else{
                cout<<"More than 10 accounts can not be created"<<endl;
            }
            break;
            }
            case 3:
            cout<<"Exiting..."<<endl;
            sleep(2);
            z=0;
            break;
        }
    }
    
    saveUserInfoToFile(users,numUsers);

    for(int i=0;i<numUsers;i++){
        delete users[i];
    }

    return 0;
}
