//============================================================================
// Name        : ProjectTwo
// Author      : Sirisa Chueainta
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <time.h>

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold course information
struct Course {
  string courseId;  // unique identifier
  string courseName;
  vector<string> prerequisites;
};

// Internal structure for tree node
struct Node {
  Course course;
  Node* left;
  Node* right;

  // default constructor
  Node() {
    left = nullptr;
    right = nullptr;
  }

  // initialize with a course
  Node(Course aCourse) : Node() { course = aCourse; }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {
 private:
  Node* root;

  void addNode(Node* node, Course course);
  void inOrder(Node* node);
  Node* removeNode(Node* node, string courseId);
  void deleteAll(Node* node);

 public:
  BinarySearchTree();
  virtual ~BinarySearchTree();
  void InOrder();
  void Insert(Course course);
  void Remove(string courseId);
  Course Search(string courseId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
  
  // root is equal to nullptr
  root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
  // recurse from root deleting every node
  deleteAll(root);
  root = nullptr;
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
  
  // call inOrder fuction and pass root
  inOrder(root);
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course) {
 
  // if root equarl to null ptr
  if (root == nullptr) {
    // root is equal to new node course
    root = new Node(course);
    return;
  }
  // else
  else {
    // add Node root and course
    addNode(root, course);
  }
  return;
}

/**
 * Remove a course
 */
void BinarySearchTree::Remove(string courseId) {
  
  // remove node root courseID
  root = removeNode(root, courseId);
  return;
}

/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseId) {
  
  // set current node equal to root
  Node* current = root;

  // keep looping downwards until bottom reached or matching courseId found
  while (current != nullptr) {
    // if match found, return current course
    if (current->course.courseId == courseId) {
      return current->course;
    }
    // if course is smaller than current node then traverse left
    if (courseId < current->course.courseId) {
      current = current->left;
    }
    // else larger so traverse right
    else {
      current = current->right;
    }
  }
  Course course;
  return course;
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param course course to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
  
  // if node is larger then add to left
  if (node->course.courseId > course.courseId) {
    // if no left node
    if (node->left == nullptr) {
      // this node becomes left
      node->left = new Node(course);
      return;
    }
    // else recurse down the left node
    else {
      addNode(node->left, course);
    }
  } else {
    // if no right node
    if (node->right == nullptr) {
      // this node becomes right
      node->right = new Node(course);
      return;
    } else {
      // recurse down the right node
      addNode(node->right, course);
    }
  }
}
Node* BinarySearchTree::removeNode(Node* node, string courseId) {
  // return root if root is null
  if (node == NULL) return node;

  // recurse to find node to delete
  if (node->course.courseId > courseId) {
    node->left = removeNode(node->left, courseId);
    return node;
  } else if (node->course.courseId < courseId) {
    node->right = removeNode(node->right, courseId);
    return node;
  }

  // if node has only one child
  if (node->left == NULL) {
    Node* temp = node->right;
    delete node;
    return temp;
  } else if (node->right == NULL) {
    Node* temp = node->left;
    delete node;
    return temp;
  }
  // else node has two children
  else {
    // initilize successor and its parent
    Node* succParent = node;
    Node* succ = node->right;

    // find successor
    while (succ->left != NULL) {
      succParent = succ;
      succ = succ->left;
    }

    // if successor's parent is not node
    if (succParent != node) {
      // set left node of successor's parent to right node of successor
      succParent->left = succ->right;
    } else {
      // set right node of successor's parent to right node of successor
      succParent->right = succ->right;
    }

    // replace course in node
    node->course = succ->course;

    // delete successor
    delete succ;
    return node;
  }
}
void BinarySearchTree::inOrder(Node* node) {
  
  // if node is not equal to null ptr
  if (node != nullptr) {
    // InOrder not left
    inOrder(node->left);
    // output courseID, title, amount, fund
    Course course = node->course;
    cout << course.courseId << ": " << course.courseName;
    if (course.prerequisites.size() > 0) {
      cout << " Prerequisites: ";
      for (int i = 0; i < course.prerequisites.size(); i++) {
        cout << course.prerequisites[i] << " ";
      }
      cout << endl;
    }
    // InOder right
    inOrder(node->right);
  }
}

void BinarySearchTree::deleteAll(Node* node) {
  
  // if node is not equal to null ptr
  if (node != nullptr) {
    // delete left
    deleteAll(node->left);
    // delete right
    deleteAll(node->right);
    // delete node
    delete node;
  }
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the course information to the console (std::out)
 *
 * @param course struct containing the course info
 */
void displayCourse(Course course) {
  cout << course.courseId << ": " << course.courseName;
  if (course.prerequisites.size() > 0) {
    cout << " Prerequisites: ";
    for (int i = 0; i < course.prerequisites.size(); i++) {
      cout << course.prerequisites[i] << " ";
    }
    cout << endl;
  }
  return;
}

vector<string> split(const string& s, char delim) {
  vector<string> result;
  stringstream ss(s);
  string item;

  while (getline(ss, item, delim)) {
    result.push_back(item);
  }

  return result;
}

// trim from end of string (right)
inline std::string rtrim(std::string s) {
  const char* t = " \t\n\r\f\v";
  s.erase(s.find_last_not_of(t) + 1);
  return s;
}

bool checkFileFormat(string fileName) {
  vector<string> courseList;
  // Read from the text file
  FILE* f;
  fopen_s(&f, fileName.c_str(), "r");
  if (f == nullptr) {
    cout << "file not found";
    return false;
  }
  // Use a while loop together with the getline() function to read the file line
  // by line
  char line[1024];
  while (fgets(line, sizeof line, f) != NULL) {
    // Output the text from the file
    vector<string> wordList = split(rtrim(line), ',');
    if (wordList.size() < 2) {
      cout << "file format error";
      fclose(f);
      return false;
    }
    string courseId = wordList[0];
    courseList.push_back(courseId);
  }
  fseek(f, 0, SEEK_SET);

  while (fgets(line, sizeof line, f) != NULL) {
    // Output the text from the file
    vector<string> wordList = split(rtrim(line), ',');
    for (int i = 2; i < wordList.size(); i++) {
      bool found = false;
      for (int j = 0; j < courseList.size(); j++) {
        if (courseList[j] == wordList[i]) {
          found = true;
          break;
        }
      }
      if (!found) {
        cout << "Prerequisite " << wordList[i] << " (" << wordList[i].size()
             << ") course not in course list" << endl;
        return false;
      }
    }
  }

  // Close the file
  fclose(f);
  return true;
}

/**
 * Load a CSV file containing courses into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the courses read
 */

void loadCourse(string csvPath, BinarySearchTree* bst) {
  FILE* f;
  fopen_s(&f, csvPath.c_str(), "r");

  char line[1024];
  while (fgets(line, sizeof line, f) != NULL) {
    // Output the text from the file
    vector<string> wordList = split(rtrim(line), ',');
    // Create a data structure and add to the collection of courses
    Course course;
    course.courseId = wordList[0];
    course.courseName = wordList[1];
    for (int i = 2; i < wordList.size(); i++) {
      course.prerequisites.push_back(wordList[i]);
    }
    // push this course to the end
    bst->Insert(course);
  }
  // Close the file
  fclose(f);
  return;
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
  str.erase(remove(str.begin(), str.end(), ch), str.end());
  return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {
  // process command line arguments
  string csvPath, courseKey;
  bool exit = false;

  // Define a binary search tree to hold all courses
  BinarySearchTree* bst;
  bst = new BinarySearchTree();
  Course course;

  int choice = 0;
  while (choice != 9) {
    cout << "Welcome to the course planner." << endl;
    cout << "  1. Load Data Structure" << endl;
    cout << "  2. Print Course List." << endl;
    cout << "  3. Print Course." << endl;
    cout << "  9. Exit" << endl;
    cout << "What would you like to do?" << endl;
    cin >> choice;

    switch (choice) {
      case 1: {
        cout << "Enter file name";
        cin >> csvPath;
        bool checkPass = checkFileFormat(csvPath);
        // Complete the method call to load the courses
        if (checkPass) {
          loadCourse(csvPath, bst);
        }
      } break;

      case 2:
        bst->InOrder();
        break;

      case 3:
        cout << "What course do you want to know about?";
        cin >> courseKey;

        course = bst->Search(courseKey);

        if (!course.courseId.empty()) {
          displayCourse(course);
        } else {
          cout << "Course Id " << courseKey << " not found." << endl;
        }

        break;

      case 9:
        exit = true;
        break;
      default:
        cout << choice << " is not a valid option" << endl;
    }
    if (exit) {
      break;
    }
  }

  cout << "Thank you for using the course planner!" << endl;
  delete bst;
  return 0;
}
