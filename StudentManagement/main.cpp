#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <conio.h>
#include "tabulate/table.hpp"
#include <regex>

using namespace tabulate;
using namespace std;

//forward declarations
class Student;
class User;

class User
{
private:
	string account;//Ψһ��ʶ
	string password;
	short role;//ѧ��0����ʦ1
public:
	//constructors
	User() {};
	User(string account, string password, short role)
		:account(account), password(password), role(role) {};
	User(const User& user)//����Ϊ������
		:account(user.account), password(user.password), role(user.role) {};
	//getters and setters
	string getAccount() { return account; }
	string getPassword() { return password; }
	inline string toString() const {
		return account + "," + password + "," + to_string(role);
	}
	short getRole() { return role; }
	void setAccount(string account) { this->account = account; }
	void setPassword(string password) { this->password = password; }
	void setRole(short role) { this->role = role; }
	//methods
	bool login();
	//��User��ص�
	bool addOneUser(User user);//����һ���û�����Ҫ����account��Ψһ��
	bool deleteOneUser(string account);//ɾ��һ���û�
	bool showOneUser(string account);//�鿴һ���û���Ϣ
	bool showAllUser();//�鿴�����û���Ϣ
	bool updateOneUser(User user);//�޸��û���Ϣ

	//��Student��ص�
	// ����Ȩ��
	bool updateOneStudent(Student student);//ѧ��ֻ���޸��Լ��ĵ绰�����գ���ʦ���������޸�
	//ѧ����Ȩ��
	bool showMyself();//ѧ�����Բ鿴�Լ�����Ϣ

	//��ʦ��Ȩ��
	bool showOneStudent();//��ʦ���Բ鿴һ��ѧ����Ϣ
	bool showAllStudent();//��ʦ���Բ鿴����ѧ����Ϣ
	bool addOneStudent();//��ʦ��������һ��ѧ��
	bool deleteOneStudent();//��ʦ����ɾ��һ��ѧ��
	bool signUp();//ֻ��ӵ�й���Ա�˺ź��������ʦ����ע������ʦ
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
	inline Student(string id, string name, string identityId, string sex, string phone, string birthday)
		:id(id), name(name), identityId(identityId), sex(sex), phone(phone), birthday(birthday) {
		//�������䲢��ֵ
		int birthYear = atoi(birthday.substr(0, 4).c_str());
		int birthMonth = atoi(birthday.substr(5, 2).c_str());
		time_t now;
		time(&now);
		tm* nowTime = localtime(&now);
		int nowYear = 1900 + nowTime->tm_year;
		int nowMonth = 1 + nowTime->tm_mon;
		age = nowYear - birthYear;
		if (nowMonth < birthMonth) {
			age--;
		}
	};
	Student(const Student& student)//������ǳ����ã���Ȼ�ᱨ��
		:id(student.id), name(student.name), identityId(student.identityId), sex(student.sex), phone(student.phone), birthday(student.birthday), age(student.age) {};
	//getters and setters
	inline string toString() const
	{
		return id + "," + name + "," + identityId + "," + sex + "," + phone + "," + birthday + "," + to_string(age);
	}
	inline vector<string> toVectorString() {
		vector <string> v;
		v.push_back(id);
		v.push_back(name);
		v.push_back(identityId);
		v.push_back(sex);
		v.push_back(phone);
		v.push_back(birthday);
		v.push_back(to_string(age));
	}
	string getId() { return id; }
	string getName() { return name; }
	string getSex() { return sex; }
	string getPhone() { return phone; }
	string getBirthday() { return birthday; }
	short getAge() { return age; }
	string getIdentityId() { return identityId; }
	void setId(string id) { this->id = id; }
	void setName(string name) { this->name = name; }
	void setSex(string sex) { this->sex = sex; }
	void setPhone(string phone) { this->phone = phone; }
	void setBirthday(string birthday) { this->birthday = birthday; }
	void setAge(short age) { this->age = age; }
	//methods
};

class Util
{
public:
	static vector<Student> loadAllStudent();//��������ѧ��
	static vector<User> loadAllUser();//���������û�
	static bool saveAllUser(vector<User> users);//���������û������ø��ǵķ�ʽʵ�֣������޸ġ�ɾ��������ʵ��
	static bool saveAllStudent(vector<Student> students);//��������ѧ�������ø��ǵķ�ʽʵ�֣������޸ġ�ɾ��������ʵ��
	static bool verifyStudent(string id, string name, string identityId, string sex, string phone, string birthday);
};

class Panel
{
public:
	static Table getStdOuterFrame();
	static Table getStdInnerFrame();
	inline static void pause(string message="ϵͳ��ܰ��ʾ������������Լ���...") {
		cout << message << endl;
		getchar();
		string temp;
		getline(cin, temp);
	};
	inline static string inputWithSecret() {
		string secret;
		char ch = _getch();
		while (ch != '\r') {
			if (ch == 8) {
				if (!secret.empty()) {
					secret.pop_back();
					cout << "\b \b";
				}
			}
			else {
				secret.push_back(ch);
				cout << '*';
			}
			ch = _getch();
		}
		return secret;
	}
	static void loading(string) ;//ͨ�ü���ҳ��
	static void menu();//������
	static bool login();//��½�Ŀ��ӻ�����
	static void updateOneUser(User user);
	static void signUp();//ע���ʦ�Ŀ��ӻ�����
	static void error(string);//ͨ�ô���ҳ��
	static void success(string);//ͨ�óɹ�ҳ��
	// static void studentOperation();//��ʾѧ����Ϣ�����ݵ�ǰ�û���ɫ��ͬ��ʾ��ͬ���ܣ�ѧ�����Ը����Լ������պ͵绰����ʦͬʱ�������¡�ɾ�������ӵĹ���
	static void addOneStudent();
	static void userOperation(vector<User> users);//��ʾ�û���Ϣ��ͬʱ�������¡�ɾ�������ӵĹ��ܡ�ֻ��ӵ�й���Ա�˺��������ʦ���Խ���
	static Table showStudent(vector<Student> const& students);//ֻ������ʾѧ����Ϣ�ı������һ�Ų���
	static Table showStudent(Student const& student);//ֻ������ʾ����ѧ����Ϣ�ı������һ�Ų���
	static Table showUser(vector<User> users);//ֻ������ʾ�û���Ϣ�ı������һ�Ų���
};

//global variables
vector<Student> allStudents;//����ѧ��
vector<Student> shownStudents;//������ʾ��ѧ���б�
vector<User> allUser;//�����û�
User nowUser("", "", -1);//��ǰ��¼���û�

vector<Student> Util::loadAllStudent() {
	vector<Student> students;
	ifstream infile("student.txt");
	if (!infile) {
		cerr << "Error opening file!" << endl;
		return students;
	}
	string line;
	while (getline(infile, line)) {
		istringstream iss(line);
		string id, name, identityId, sex, phone, birthday, ageStr;
		getline(iss, id, ',');
		getline(iss, name, ',');
		getline(iss, identityId, ',');
		getline(iss, sex, ',');
		getline(iss, phone, ',');
		getline(iss, birthday, ',');
		getline(iss, ageStr, '\n');
		Student student(id, name, identityId, sex, phone, birthday);
		students.push_back(student);
	}
	infile.close();
	return students;
}

// ���� saveAllStudent ����
bool Util::saveAllStudent(vector<Student> students) {
	ofstream outfile("student.txt");
	if (!outfile) {
		cerr << "Error opening file!" << endl;
		return false;
	}
	for (auto& student : students) {
		outfile << student.toString() << endl;
	}
	outfile.close();
	return true;
}

// ���������û�
vector<User> Util::loadAllUser() {
	vector<User> users;
	ifstream infile("user.txt");
	if (!infile) {
		cerr << "Error opening file!" << endl;
		return users;
	}
	string line;
	while (getline(infile, line)) {
		istringstream iss(line);
		string account, password, roleStr;
		getline(iss, account, ',');
		getline(iss, password, ',');
		getline(iss, roleStr, '\n');
		short role = stoi(roleStr);
		User user(account, password, role);
		users.push_back(user);
	}
	infile.close();
	return users;
}

// ���������û������ø��ǵķ�ʽʵ�֣������޸ġ�ɾ��������ʵ��
bool Util::saveAllUser(vector<User> users) {
	ofstream outfile("user.txt");
	if (!outfile) {
		cerr << "Error opening file!" << endl;
		return false;
	}
	for (auto& user : users) {
		outfile << user.toString() << endl;
	}
	outfile.close();
	return true;
}

Table Panel::showStudent(vector<Student> const& students) {
	Table table;
	table.add_row({ "ѧ��","����","���֤��","�Ա�","�绰","����","����" });
	for (auto student : students) {
		table.add_row({ student.getId(),student.getName(),student.getIdentityId(),student.getSex(),student.getPhone(),student.getBirthday(),to_string(student.getAge()) });
	}
	//��һ�е�����ֵ
	table[0].format()
		.font_style({ FontStyle::bold })
		.font_style({ FontStyle::underline })
		.font_background_color(Color::green)
		.font_color(Color::blue);
	//����������
	for (auto& row : table) {
		row.format().font_align(FontAlign::center);
	}
	//���߿�����
	table.format()
		.multi_byte_characters(true)
		// Font styling
		.font_style({ FontStyle::bold, FontStyle::dark })
		.font_align(FontAlign::center)
		.font_color(Color::red)
		.font_background_color(Color::yellow)
		// Corners
		.corner_top_left("x")
		.corner_top_right("x")
		.corner_bottom_left("x")
		.corner_bottom_right("x")
		.corner_top_left_color(Color::cyan)
		.corner_top_right_color(Color::yellow)
		.corner_bottom_left_color(Color::green)
		.corner_bottom_right_color(Color::red)
		// Borders
		.border_top("*")
		.border_bottom("*")
		.border_left("*")
		.border_right("*")
		.border_left_color(Color::yellow)
		.border_right_color(Color::green)
		.border_top_color(Color::cyan)
		.border_bottom_color(Color::red);
	return table;
}

Table Panel::showStudent(Student const& student) {
	vector<Student>temp = { student };
	return showStudent(temp);
}

Table Panel::showUser(vector<User> users) {
	Table table;
	table.add_row({ "�˺�","����","Ȩ��" });
	for (auto user : users) {
		table.add_row({ user.getAccount(),user.getPassword(),to_string(user.getRole()) });
	}
	//��һ�е�����ֵ
	table[0].format()
		.font_style({ FontStyle::bold })
		.font_style({ FontStyle::underline })
		.font_background_color(Color::green)
		.font_color(Color::blue);
	//����������
	for (auto& row : table) {
		row.format().font_align(FontAlign::center);
	}
	//���������е����е�Ԫ��
	for (auto& col_cell : table.column(2)) {
		if (col_cell.get_text() == "1") {
			col_cell.format().font_background_color(Color::red);
		}
	}
	//���߿�����
	table.format()
		.multi_byte_characters(true)
		// Font styling
		.font_style({ FontStyle::bold, FontStyle::dark })
		.font_align(FontAlign::center)
		.font_color(Color::red)
		.font_background_color(Color::yellow)
		// Corners
		.corner_top_left("x")
		.corner_top_right("x")
		.corner_bottom_left("x")
		.corner_bottom_right("x")
		.corner_top_left_color(Color::cyan)
		.corner_top_right_color(Color::yellow)
		.corner_bottom_left_color(Color::green)
		.corner_bottom_right_color(Color::red)
		// Borders
		.border_top("*")
		.border_bottom("*")
		.border_left("*")
		.border_right("*")
		.border_left_color(Color::yellow)
		.border_right_color(Color::green)
		.border_top_color(Color::cyan)
		.border_bottom_color(Color::red);
	return table;
}

void Panel::loading(string message="���ڼ�����>>>>>>") {
	for (int i = 0; i < 16; i++) {
		system("cls");

		Table outer_frame = Panel::getStdOuterFrame();
		Table inner_frame = Panel::getStdInnerFrame();
		inner_frame
			.format()
			.width(50);
		inner_frame.add_row({ message })
			.format()
			.font_color(Color::red);

		string loading_strip = "OOO";
		for (int j = 0; j < i; j++) {
			loading_strip += "OOO";
		}
		inner_frame.add_row({ loading_strip })
			.format()
			.font_align(FontAlign::left);

		outer_frame.add_row({ inner_frame });
		cout << outer_frame << endl;

		Sleep(100);
	}
	Sleep(200);

	system("cls");
}

void Panel::error(string message = "��������") {
	system("cls");

	Table outer_frame = Panel::getStdOuterFrame();
	outer_frame
		.format()
		.font_color(Color::red);
	outer_frame.add_row({ message });
	cout << outer_frame << endl;

	Panel::pause();

	system("cls");
}

void Panel::success(string message = "�����ɹ���") {
	system("cls");

	Table outer_frame = Panel::getStdOuterFrame();
	outer_frame
		.format()
		.font_color(Color::green);
	outer_frame.add_row({ message });
	cout << outer_frame << endl;

	Panel::pause();

	system("cls");
}

Table Panel::getStdOuterFrame() {
	Table mainTable;
	mainTable.add_row({ "ѧ����Ϣ����ϵͳ" });
	mainTable[0][0]
		.format()
		.font_align(FontAlign::center)
		.font_style({ FontStyle::bold })
		.font_background_color(Color::green)
		.font_color(Color::grey);
	return mainTable;
}

Table Panel::getStdInnerFrame() {
	Table table;
	table
		.format()
		.font_align(FontAlign::center);
	return table;
}

bool Panel::login() {
	Table outer_frame = Panel::getStdOuterFrame();

	string account, password;
	system("cls");
	cout << "�����������˺ţ�" << endl;
	cin >> account;

	system("cls");
	Table account_frame = Panel::getStdInnerFrame();
	account_frame.add_row({ "�˺ţ�" + account })
		.format()
		.width(50)
		.font_align(FontAlign::left)
		.font_color(Color::yellow);
	outer_frame.add_row({ account_frame });
	cout << outer_frame << endl;

	cout<< "�������������룺" << endl;
	password = Panel::inputWithSecret();

	system("cls");
	account_frame.add_row({ "���룺" + password })
		.format()
		.font_color(Color::yellow);
	outer_frame =Panel::getStdOuterFrame();
	outer_frame.add_row({ account_frame });
	cout << outer_frame << endl;

	Panel::pause();

	nowUser.setAccount(account);
	nowUser.setPassword(password);

	Panel::loading("���ڵ�½��...");

	if (nowUser.login()) {
		Panel::success("��ϲ���ɹ���¼��");
		return true;
	}
	else {
		Panel::error("�����û��������룡");
		return false;
	}
}

void Panel::signUp() {
	nowUser.signUp();
}

void Panel::updateOneUser(User user) {
	nowUser.updateOneUser(user);
}

bool cmpByStudentAge(Student& a, Student& b) {
	return a.getAge() < b.getAge();
}

bool cmpByStudentId(Student& a, Student& b) {
	return a.getId() < b.getId();
}

void Panel::menu() {
	system("cls");

	Table outer_frame = Panel::getStdOuterFrame();
	Table inner_frame = Panel::getStdInnerFrame();
	inner_frame.add_row({ "Ŀ¼" });
	inner_frame[0][0]
		.format()
		.background_color(Color::white)
		.font_color(Color::blue)
		.font_style({FontStyle::bold,FontStyle::underline})
		.width(50);

	short login_role_state = nowUser.getRole();

	if (login_role_state != -1) {
		inner_frame.add_row({ "�������������" });
		inner_frame.add_row({ "1.�鿴����ѧ��" });
		inner_frame.add_row({ "2.�鿴�����û�" });
		inner_frame.add_row({ "3.�鿴�Լ���ѧ����Ϣ" });
		inner_frame.add_row({ "4.����ѧ�Ų���һλͬѧ" });
		inner_frame.add_row({ "5.����ѧ��ɾ��һλͬѧ" });
		inner_frame.add_row({ "6.ע���ʦ�˺�" });
		inner_frame.add_row({ "7.�޸��˺�����" });
		inner_frame.add_row({ "8.���һ��ѧ��" });
		inner_frame.add_row({ "9.������������鿴����ѧ��" });
		inner_frame.add_row({ "10.����ѧ������鿴����ѧ��" });
		inner_frame.add_row({ "���������Զ��˳�" });

		outer_frame.add_row({ inner_frame });

		cout << outer_frame << endl;

		string command;
		cin >> command;
		if (command == "1") {
			nowUser.showAllStudent();
			Panel::menu();
		}
		else if (command == "2") {
			nowUser.showAllUser();
			Panel::menu();
		}
		else if (command == "3") {
			nowUser.showMyself();
			Panel::menu();
		}
		else if (command == "4") {
			nowUser.showOneStudent();
			Panel::menu();
		}
		else if (command == "5") {
			nowUser.deleteOneStudent();
			Panel::menu();
		}
		else if (command == "6") {
			Panel::signUp();
			Panel::menu();
		}
		else if (command == "7") {
			Panel::updateOneUser(nowUser);
			Panel::menu();
		}
		else if (command == "8") {
			nowUser.addOneStudent();
			Panel::menu();
		}
		else if (command == "9") {
			allStudents = Util::loadAllStudent();
			sort(allStudents.begin(), allStudents.end(), cmpByStudentAge);
			nowUser.showAllStudent();
			Panel::menu();
		}
		else if (command == "10") {
			allStudents = Util::loadAllStudent();
			sort(allStudents.begin(), allStudents.end(), cmpByStudentId);
			nowUser.showAllStudent();
			Panel::menu();
		}
		else {
			Panel::success("��л����ʹ�ú�������");
		}
		return;
	}
	inner_frame.add_row({ "���ȵ�¼" });
	inner_frame[0][0]
		.format()
		.color(Color::red);
	outer_frame.add_row({ inner_frame });
	cout << outer_frame << endl;

	Panel::pause("��������Ե�¼...");

	while (!Panel::login());
	Panel::menu();
}


bool Util::verifyStudent(string id, string name, string identityId, string sex, string phone, string birthday) {
	if (regex id_reg("^\\d{12}$"); !regex_match(id, id_reg)) {
		Panel::error("ѧ�Ÿ�ʽ����");
		return false;
	}

	if (regex identity_id_reg("^([1-6][1-9]|50)\\d{4}(18|19|20)\\d{2}((0[1-9])|10|11|12)(([0-2][1-9])|10|20|30|31)\\d{3}[0-9Xx]$"); !regex_match(identityId, identity_id_reg)) {
		Panel::error("���֤�Ÿ�ʽ����");
		return false;
	}

	if (regex sex_reg("^(��|Ů){1}$"); !regex_match(sex, sex_reg)) {
		Panel::error("�Ա��������");
		return false;
	}

	if (regex phone_reg("^1(3|4|5|7|8)\\d{9}$"); !regex_match(phone, phone_reg)) {
		Panel::error("�ֻ��Ÿ�ʽ����");
		return false;
	}

	if (regex birthday_reg("^\\d{4}-\\d{2}-\\d{2}$"); !regex_match(birthday, birthday_reg)) {
		Panel::error("���ڸ�ʽ����");
		return false;
	}

	return true;
}

void Panel::addOneStudent()
{
	system("cls");

	Table inner_frame = Panel::getStdInnerFrame();
	inner_frame
		.format()
		.font_align(FontAlign::left)
		.width(50);

	string id, name, identityId, sex, phone, birthday;
	cout << "������ѧ�ţ�";
	cin >> id;
	system("cls");
	cout << Panel::getStdOuterFrame().add_row({ inner_frame.add_row({"ѧ�ţ�" + id}) }) << endl;

	cout << "������������";
	cin >> name;
	system("cls");
	cout << Panel::getStdOuterFrame().add_row({ inner_frame.add_row({"������" + name }) }) << endl;

	cout << "���������֤�ţ�";
	cin >> identityId;
	system("cls");
	cout << Panel::getStdOuterFrame().add_row({ inner_frame.add_row({"���֤�ţ�" + identityId }) }) << endl;

	cout << "�������Ա���/Ů����";
	cin >> sex;
	system("cls");
	cout << Panel::getStdOuterFrame().add_row({ inner_frame.add_row({"�Ա�" + sex }) }) << endl;

	cout << "������绰���룺";
	cin >> phone;
	system("cls");
	cout << Panel::getStdOuterFrame().add_row({ inner_frame.add_row({"�绰���룺" + phone }) }) << endl;

	cout << "���������գ�xxxx-xx-xx����";
	cin >> birthday;
	system("cls");
	cout << Panel::getStdOuterFrame().add_row({ inner_frame.add_row({"���գ�" + birthday }) }) << endl;

	if (!Util::verifyStudent(id, name, identityId, sex, phone, birthday)) {
		Panel::addOneStudent();
		return;
	}

	for (auto& s : Util::loadAllStudent()) {
		if (s.getId() == id) {
			Panel::error("ѧ���Ѵ���");
			Panel::addOneStudent();
			return;
		}
		if (s.getIdentityId() == identityId) {
			Panel::error("���֤���Ѵ���");
			Panel::addOneStudent();
			return;
		}
	}

	vector<Student>student_vector= Util::loadAllStudent();
	student_vector.emplace_back(id, name, identityId, sex, phone, birthday);

	vector<User>user_vector = Util::loadAllUser();
	user_vector.emplace_back(id, identityId.substr(12), 0);

	Util::saveAllStudent(student_vector);
	Util::saveAllUser(user_vector);
}
 
bool User::login()
{
	for (auto& user : Util::loadAllUser()) {
		if (user.getAccount() == account && user.getPassword() == password) {
			this->role = user.getRole();
			return true;
		}
	}
	return false;
}

bool User::addOneUser(User user)//����һ���û�����Ҫ����account��Ψһ��
{
	for (auto& u : allUser) {
		if (u.getAccount() == user.getAccount()) {
			cout << "�˺��Ѵ���" << endl;
			return false;
		}
	}
	allUser.push_back(user);
	return true;
}

bool User::deleteOneUser(string account) {
    for (auto it = allUser.begin(); it != allUser.end(); ++it) {
        if (it->getAccount() == account) {
            allUser.erase(it);
            return true;
        }
    }
    cout << "�˺Ų�����" << endl;
    return false;
}

bool User::updateOneStudent(Student student)//ѧ��ֻ���޸��Լ��ĵ绰�����գ���ʦ���������޸�
// ����nowUser��role�������0˵����ѧ����ֻ���޸��Լ��ĵ绰�����գ������1˵������ʦ�����޸�����ѧ��������Ϣ��
{
	if (nowUser.getRole() == 0) {
		// �����ѧ����ֻ���޸��Լ��ĵ绰������
		for (auto& s : allStudents) {
			if (s.getId() == student.getId()) {
				if (s.getId() != nowUser.getAccount()) {
					Panel::error("��ֻ���޸��Լ�����Ϣ");
					return false;
				}
				s.setPhone(student.getPhone());
				s.setBirthday(student.getBirthday());
				Panel::success("�޸ĳɹ�");
				return true;
			}
		}
		Panel::error("ѧ�Ų�����");
		return false;
	}
	else if (nowUser.getRole() == 1) {
		// �������ʦ�������޸�����ѧ��������Ϣ
		for (auto& s : allStudents) {
			if (s.getId() == student.getId()) {
				s.setName(student.getName());
				s.setSex(student.getSex());
				s.setPhone(student.getPhone());
				s.setBirthday(student.getBirthday());
				s.setAge(student.getAge());
				Panel::success("�޸ĳɹ�");
				return true;
			}
		}
		Panel::error("ѧ�Ų�����");
		return false;
	}
	else {
		// ����������û�����Ȩ�޸�
		Panel::error("����Ȩ�޸�");;
		return false;
	}
}

//�鿴һ���û���Ϣ
bool User::showOneUser(string account) 
{
    for (auto& user : allUser) 
	{
        if (user.getAccount() == account)
		{ 
			vector<User> tempvector;
			tempvector.push_back(user);
			Panel::showUser(tempvector);
			return true;
		}
    }
    cout << "�˺Ų�����" << endl;
    return false;
}

bool User::showAllUser()//�鿴�����û���Ϣ
{
	if (role != 1) {
		Panel::error("����Ȩ�޲��㣡");
		return false;
	}
	system("cls");
	cout << Panel::getStdOuterFrame().add_row({ Panel::showUser(Util::loadAllUser()) }) << endl;
	Panel::pause();
	return true;
}

//�޸��û�����
bool User::updateOneUser(User user) {
	system("cls");
	allStudents = Util::loadAllStudent();
	allUser = Util::loadAllUser();
	
    for (auto& u : allUser) {
        if (u.getAccount() == user.getAccount()) {
            // Ҫ���û�����ԭ����
            string old_password;
            cout << "������ԭ���룺";
            // ��������ַ��滻Ϊ'*'
            char ch;
            while ((ch = _getch()) != '\r') {
                if (ch == '\b') {
                    if (!old_password.empty()) {
                        old_password.pop_back();
                        cout << "\b \b";
                    }
                } else {
                    old_password.push_back(ch);
                    cout << "*";
                }
            }
            cout << endl;
            if (old_password != u.getPassword()) {
				Panel::error("�������");
                return false;
            }
            // Ҫ���û�����������
            string new_password;
            cout << "�����������룺";
            // ��������ַ��滻Ϊ'*'
            while ((ch = _getch()) != '\r') {
                if (ch == '\b') {
                    if (!new_password.empty()) {
                        new_password.pop_back();
                        cout << "\b \b";
                    }
                } else {
                    new_password.push_back(ch);
                    cout << "*";
                }
            }
            cout << endl;
            u.setPassword(new_password);
			
			Util::saveAllStudent(allStudents);
			Util::saveAllUser(allUser);
			Panel::success("�����޸ĳɹ�");
            return true;
        }
    }
	Panel::error("�˺Ų�����");
    return false;
}

bool User::showMyself()//��ѧ�����м���now_user�˺ţ������������ʾ��ѧ����Ϣ
{
	if (role != 0) {
		Panel::error("������ѧ������ѧ����Ϣ");
		return false;
	}
	for (auto& student : Util::loadAllStudent()) {
		if (student.getId() == nowUser.getAccount()) {
			vector<Student> tempvector;
			tempvector.push_back(student);
			cout << Panel::getStdOuterFrame().add_row({ Panel::showStudent(tempvector) }) << endl;
			Panel::pause();
			return true;
		}
	}
	Panel::error("�޵�ǰ�û���Ϣ��");
	return false;
}


bool User::showOneStudent()//��ʦ���Բ鿴һ��ѧ����Ϣ
{
	system("cls");

	if (role != 1) {
		Panel::error("����Ȩ�޲��㣡");
		return false;
	}
	cout << "��������Ҫ��ѯ��ѧ�ţ�" << endl;
	string id;
	cin >> id;
	for (auto& student : Util::loadAllStudent()) {
		if (student.getId() == id) {
			vector<Student> tempvector;
			tempvector.push_back(student);
			cout << Panel::getStdOuterFrame().add_row({ Panel::showStudent(tempvector) }) << endl;
			Panel::pause();
			return true;
		}
	}
	Panel::error("ѧ�Ų����ڣ�");
	return false;
}

bool User::showAllStudent()//��ʦ���Բ鿴����ѧ����Ϣ
{
	if (role != 1) {
		Panel::error("����Ȩ�޲��㣡");
		return false;
	}
	system("cls");
	cout << Panel::getStdOuterFrame().add_row({ Panel::showStudent(allStudents) }) << endl;
	Panel::pause();
	return true;
}

bool User::addOneStudent()//��ʦ��������һ��ѧ��
{
	if (role != 1) {
		Panel::error("����Ȩ�޲��㣡");
		return false;
	}
	system("cls");
	Panel::addOneStudent();
	Panel::success("ѧ����ӳɹ���");
	return true;
}

bool User::deleteOneStudent()//��ʦ����ɾ��һ��ѧ��
{
	system("cls");

	if (role != 1) {
		Panel::error("����Ȩ�޲��㣡");
		return false;
	}
	cout << "��������Ҫɾ����ѧ��ѧ�ţ�" << endl;
	string id;
	cin >> id;
	vector<Student> tempvector = Util::loadAllStudent();
	for (auto it = tempvector.begin(); it != tempvector.end(); ++it) {
		if (it->getId() == id) {
			tempvector.erase(it);
			Util::saveAllStudent(tempvector);
			Panel::success("ɾ���ɹ���");
			return true;
		}
	}
	Panel::error("ѧ�Ų����ڣ�");
	return false;
}

//����ָ������Ա�˺ţ�admin��������(admin)��֮�����ע������ʦ
bool User::signUp() {
	system("cls");
	allStudents = Util::loadAllStudent();
	allUser = Util::loadAllUser();

	// �������Ա�˺ź�����
	string admin_account = "admin";
	string admin_password = "admin";
	string input_account, input_password;
	cout << "���������Ա�˺ţ� ";
	cin >> input_account;

	cout << "���������Ա���룺 ";
	input_password = "";
	char ch;
	while ((ch = _getch()) != '\r') {
		if (ch == '\b') { // ����ǻ��˼�
			if (!input_password.empty()) {
				input_password.pop_back();
				cout << "\b \b";
			}
		}
		else {
			input_password.push_back(ch);
			cout << "*";
		}
	}
	cout << endl;

	// �ж�������˺ź������Ƿ���ȷ
	if (admin_account == input_account && admin_password == input_password) {
		Panel::success("��ϲ���ɹ���¼��");
		
		// ��������ʦ���˺ź�����
		string new_account, new_password;
		cout << "�������µĽ�ʦ�˺ţ� ";
		cin >> new_account;

		cout << "�������µĽ�ʦ���룺 ";
		new_password = "";
		while ((ch = _getch()) != '\r') {
			if (ch == '\b') { // ����ǻ��˼�
				if (!new_password.empty()) {
					new_password.pop_back();
					cout << "\b \b";
				}
			}
			else {
				new_password.push_back(ch);
				cout << "*";
			}
		}
		cout << endl;

		// ����Ƿ������ͬ���˺�
		for (auto& u : allUser) {
			if (u.getAccount() == new_account) {
				Panel::error("�˺��Ѵ���");
				return false;
			}
		}
		// �������ʦ
		User new_teacher(new_account, new_password, 1);
		allUser.push_back(new_teacher);
		Util::saveAllUser(allUser);
		Panel::success("�½�ʦ�˺Ŵ����ɹ�");
		return true;
	}
	else {
		Panel::error("����Ա�˺Ż��������");
		return false;
	}

	Util::saveAllStudent(allStudents);
	Util::saveAllUser(allUser);
}

int main() {

	/*���Ա��
	Panel::showStudent(shown_students = FileUtil::loadAllStudent());
	FileUtil::saveAllStudent(shown_students);

	Panel::showUser(allUser = FileUtil::loadAllUser());
	FileUtil::saveAllUser(allUser);*/


	//���Ե�¼
	/*allUser = FileUtil::loadAllUser();
	User user1;
	if (user1.login())
		cout << "��¼�ɹ�" << endl;*/
	
	/*��������˻�
	allUser = FileUtil::loadAllUser();
	User testUser1("20210080000", "00000000", 1); 
	if (now_user.addOneUser(testUser1))
		cout << "�ɹ����" << endl;
	User testUser2("20210080000", "00000000", 1);
	if (now_user.addOneUser(testUser2))
		cout << "�ɹ����" << endl;*/

	/*����ɾ���˺�
	allUser = FileUtil::loadAllUser();
	if (now_user.deleteOneUser("202100810120"))
		cout << "�ɹ�ɾ��" << endl;
	now_user.deleteOneUser("202100810120");*/

	/*������ʾ�����û���Ϣ
	allUser = FileUtil::loadAllUser();
	now_user.showOneUser("202100810120");
	now_user.showOneUser("20210081020");*/

	/*��ʾ�����û���Ϣ
	allUser = FileUtil::loadAllUser();
	now_user.showAllUser();*/

	/*�޸�����
    allUser = FileUtil::loadAllUser();
    User user;
    user.setAccount("202100800000");
    user.updateOneUser(user);
	Panel::showUser(allUser);*/
	
	/*ѧ����ʾ�Լ���Ϣ
	allUser = FileUtil::loadAllUser();
	allStudengs = FileUtil::loadAllStudent();
	allStudengs = FileUtil::loadAllStudent();
	Panel::showStudent(allStudengs);
	nowUser.login();
	nowUser.showMyself();*/

	/*��ʦ�鿴һ��ѧ����Ϣ
	allUser = FileUtil::loadAllUser();
	allStudengs = FileUtil::loadAllStudent();
	nowUser.showOneStudent("202100810120");*/
	
	//��ʦ�鿴����ѧ����Ϣ
	/*allUser = FileUtil::loadAllUser();
	allStudengs = FileUtil::loadAllStudent();
	nowUser.showAllStudent();*/

	//��ʦ���һ��ѧ��
	/*allUser = FileUtil::loadAllUser();
	allStudengs = FileUtil::loadAllStudent();
	Student student("2021008101112", "����", "123456789012345633", "��", "12345678802", "2000-03");
	nowUser.addOneStudent(student);
	nowUser.addOneStudent(student);*/
	
	//��ʦɾ��һ��ѧ��
	/*allUser = FileUtil::loadAllUser();
	allStudengs = FileUtil::loadAllStudent();
	if(nowUser.deleteOneStudent("202100810120"))
		cout <<  "�ɹ�ɾ��" << endl;
	nowUser.deleteOneStudent("2021008101112");*/
	
	//��ʦע������ʦ
	/*allUser = FileUtil::loadAllUser();
	allStudengs = FileUtil::loadAllStudent();
	nowUser.signUp();*/
	
	//ѧ���޸��Լ���Ϣ
	/*allUser = FileUtil::loadAllUser();
	allStudengs = FileUtil::loadAllStudent();
	nowUser.login();
	Student student("202100810120", "����", "123456789012345633", "��", "12345678802", "2000-03");
	nowUser.updateOneStudent(student);*/
	
	nowUser.setAccount("111");
	nowUser.setPassword("111");
	nowUser.setRole(1);
	Panel::menu();

	return 0;
}