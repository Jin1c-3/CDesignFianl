#include<iostream>
#include<string>
#include<list>
#include<ctime>

using namespace std;

class User
{
private:
	string account;
	string password;
	short role;//ѧ��0����ʦ1
public:
	//constructors
	User() {};
	User(string account, string password, short role) :account(account), password(password), role(role) {};
	//getters and setters
	string getAccount() { return account; }
	string getPassword() { return password; }
	short getRole() { return role; }
	void setAccount(string account) { this->account = account; }
	void setPassword(string password) { this->password = password; }
	void setRole(short role) { this->role = role; }
	//methods
	bool login();
	bool signUp();
	bool save(list<User> users);
	list<User> load();
};

class Student
{
private:
	string id;
	string name;
	string identityId;
	string sex;
	string phone;
	string birthday;
	short age;
public:
	//construtors
	Student() {};
	Student(string id, string name, string sex, string birthday, short age) :id(id), name(name), sex(sex), birthday(birthday), age(age) {};
	//getters and setters
	string getId() { return id; }
	string getName() { return name; }
	string getSex() { return sex; }
	string getPhone() { return phone; }
	string getBirthday() { return birthday; }
	short getAge() { return age; }
	void setId(string id) { this->id = id; }
	void setName(string name) { this->name = name; }
	void setSex(string sex) { this->sex = sex; }
	void setPhone(string phone) { this->phone = phone; }
	void setBirthday(string birthday) { this->birthday = birthday; }
	void setAge(short age) { this->age = age; }
	//methods
	bool show(string id);//ֻ�ܲ鿴�Լ���ѧ����Ϣ
	bool update(string id);//ֻ���޸��Լ��Ĳ���ѧ����Ϣ�������绰������
};