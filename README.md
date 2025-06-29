# 📱 Social Networking Platform Simulator

A simplified **social media platform simulator** built using **C++** and core **object-oriented programming (OOP)** principles. This university project demonstrates user authentication, content creation (posts and stories), social interactions (likes, comments, following), and file handling for persistent storage.


## 📌 Features

- 👤 **User Account Management**
  - Create new accounts with encrypted password authentication.
  - Login and password update functionality.
  - Delete user account along with associated content.

- 📝 **Content Creation**
  - Create **posts** and **stories** with text content.
  - Like and comment on posts and stories.
  - View a personal feed of your created content.

- 🤝 **Social Interactions**
  - Follow other users.
  - View list of followers (limited to 10).
  - Interact with other users’ posts and stories.

- 💾 **Data Persistence**
  - All user credentials and encrypted passwords are saved using file handling.
  - Data persists across sessions through `UserInfo.txt`.

- 🧠 **OOP Concepts Used**
  - Abstraction through base classes like `Entity` and `CommentsAndLikes`.
  - Inheritance and polymorphism for `User`, `Account`, `Post`, and `Story`.
  - Encapsulation in user management and authentication logic.



## 🧱 Project Structure

- `Entity` (Abstract class): Base for `User` and `Account`.
- `CommentsAndLikes` (Abstract class): Base for `Post` and `Story`, includes likes/comments logic.
- `User` and `Account`: Entities with their own content and social graph.
- `Post` and `Story`: Shareable content with interaction features.
- `main()`: CLI interface for interaction with the platform.



## 🛠️ How It Works

1. **On First Run:**
   - Create a user account.
   - Enter a username and password.
   - Password is encrypted and stored in a file.

2. **On Future Runs:**
   - Login with your username and password.
   - Access your content or interact with other users.

3. **CLI Menu Options:**
   - Create Post / Story
   - Like or Comment on a Post / Story
   - View Your Content
   - Follow Other Users
   - Update Password
   - Delete Account
   - Exit & Save Data



## 🚫 Limitations

- Max 10 users, 10 posts, 10 stories, and 10 followers per user.
- Basic command-line interface.
- Password encryption is only for demo purposes and not secure for production.


