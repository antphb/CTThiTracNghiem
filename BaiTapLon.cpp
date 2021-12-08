#include <bits/stdc++.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <unistd.h>
#include <conio.h>
#include <dos.h>
#include <ctime>
using namespace std;

typedef struct TRACNGHIEM
{
	int stt;
	char cauHoi[256];
	char dapAnA[256];
	char dapAnB[256];
	char dapAnC[256];
	char dapAnD[256];
	char ketQua;
} tracnghiem;

struct Node
{
	TRACNGHIEM data;
	Node *pNext;
};
struct List
{
	Node *lHead;
	Node *lTail;
};

struct login
{
	string hoten;
	string diachi;
	string namsinh;
	string taikhoan;
	string matkhau;
	string isAdmin;
};

struct NodeLogin
{
	login info;
	NodeLogin *next;
};

struct ListLogin
{
	NodeLogin *head;
	NodeLogin *tail;
};

void INIT(List &l)
{
	l.lHead = l.lTail = NULL;
}

Node *getNode(TRACNGHIEM x)
{
	Node *p = new Node;
	if (p == NULL)
	{
		cout << "Khong the cap phat bo nho!";
		return NULL;
	}
	p->data = x;
	p->pNext = NULL;
	return p;
}

bool kiemTraTrungCauHoi(List l, TRACNGHIEM x)
{
	Node *p = l.lHead;
	while (p != NULL)
	{
		if (strcmpi(p->data.cauHoi, x.cauHoi) == 0)
		{
			return true;
		}
		p = p->pNext;
	}
	return false;
}

bool addLast(List &l, Node *p)
{
	if (l.lHead == NULL)
	{
		l.lHead = l.lTail = p;
	}
	else
	{
		l.lTail->pNext = p;
		l.lTail = p;
	}
	return true;
}

// ham nay goi den ham kiemTraTrungCauHoi, va ham addLast // Hieu, 4/12/2021
bool insertNode(List &l, TRACNGHIEM x)
{
	Node *p = getNode(x);
	if (p == NULL)
	{
		return false;
	}
	// kiem tra cau hoi co trung voi cau hoi da co trong danh sach hay chua? // Hieu, 4/12/2021
	if (kiemTraTrungCauHoi(l, x) == true)
	{
		return false;
	}
	return addLast(l, p);
}


void initLogin(ListLogin &l)
{
	l.head=l.tail= NULL;
}

NodeLogin *getnodelogin(login info)
{
	NodeLogin *p;
	p=new NodeLogin;
	if (p==NULL)
	{
		return NULL;
	}
	p->info=info;
	p->next=NULL;
	return p;
}

void addlastLogin(ListLogin &l, NodeLogin *new_node)
{
	if (l.head==NULL)
	{
		l.head=l.tail=new_node;
	}
	else
	{
		l.tail->next=new_node;
		l.tail=new_node;
	}
}

void insertlogin(ListLogin &l, login info)
{
	NodeLogin *new_node= getnodelogin(info);
	if (new_node == NULL)
	{
		return;
	}
	addlastLogin(l,new_node);
}

// Doc file cau hoi trac nghiem
void docFileTracNghiem(List &l)
{
	ifstream docFile("cauhoi.txt");

	if (!docFile)
	{
		cout << "Khong the mo file de doc!";
		return;
	}
	TRACNGHIEM data;
	int count = 0;
	while (!docFile.eof())
	{
		docFile>> data.stt;
		docFile.ignore();
		docFile.getline(data.cauHoi, sizeof(data.cauHoi));
		docFile.getline(data.dapAnA, sizeof(data.dapAnA));
		docFile.getline(data.dapAnB, sizeof(data.dapAnB));
		docFile.getline(data.dapAnC, sizeof(data.dapAnC));
		docFile.getline(data.dapAnD, sizeof(data.dapAnD));
		docFile >> data.ketQua;
		docFile.ignore();
		if (!docFile.eof())
		{
			bool check = insertNode(l, data);
			if (check == false)
			{
				count++;
			}
		}
	}
	if (count != 0){
		cout << "Khong the them duoc " << count << " cau hoi trong file!" << endl;
	}
	docFile.close();
}
// ghi 1 cau hoi trac nghiem trac nghiem moi bo sung vao file
bool ghiCauTracNghiemVaoFile(TRACNGHIEM data){
	ofstream ghiFile("cauhoi.txt", ios::app);
	if (ghiFile.bad()){
		cout<<"Khong the mo file de ghi!";
		return false;
	}
	ghiFile<<data.stt<<endl;
	ghiFile<<data.cauHoi<<endl;
	ghiFile<<data.dapAnA<<endl;
	ghiFile<<data.dapAnB<<endl;
	ghiFile<<data.dapAnC<<endl;
	ghiFile<<data.dapAnD<<endl;
	ghiFile<<data.ketQua<<endl;
	ghiFile.close();
	return true;
}

// xoa ki tu trong chuoi theo vi tri
void xoaTaiViTri(char str[], int index){
	for (int i = index; i < strlen(str); i++){
		str[i] = str[i+1];
	}
}

// chuan hoa chuoi, loai bo khoang cach du thua, in hoa dau dong
char* chuanHoaChuoi(char str[])
{
	// xoa khoang trang o dau
	while (strlen(str) > 1 && str[0] == ' '){
		xoaTaiViTri(str, 0);
	}
	// xoa khoang trang ben trong cau
	for (int i = 0; i < strlen(str)-1; i++){
		if (str[i] == ' ' && str[i+1] == ' '){
			xoaTaiViTri(str, i);
			i--;
		}
	}
	// xoa o cuoi cau
	while (str[strlen(str)-1] == ' '){
		str[strlen(str)-1] = '\0';
	}
	// in hoa ki tu dau dong
	if (str[0] >= 'a' && str[0] <= 'z'){
		str[0] = str[0] - 32;
	}
	// in hoa ki tu sau dau cach
	for (int i = 0; i < strlen(str)-1; i++){
		if (str[i] == ' ' && str[i+1] >= 'a' && str[i+1] <= 'z'){
			str[i+1] = str[i+1] - 32;
		}
	}
	char *tempS = str;
	return tempS;
}

// them cau hoi vao danh sach va ghi cau hoi do vao file
bool themCauHoi(List &l){
	TRACNGHIEM data;
	char s1[253];
	cout<<"Nhap vao cau hoi day du: ";
	gets(data.cauHoi);
	strcpy(data.cauHoi, chuanHoaChuoi(data.cauHoi));
	cout<<"Nhap vao dap an A: ";
	gets(s1);
	sprintf(data.dapAnA, "%s %s","A)", s1);
	strcpy(data.dapAnA, chuanHoaChuoi(data.dapAnA));
	cout<<"Nhap vao dap an B: ";
	gets(s1);
	sprintf(data.dapAnB, "%s %s", "B)", s1);
	strcpy(data.dapAnB, chuanHoaChuoi(data.dapAnB));
	cout<<"Nhap vao dap an C: ";
	gets(s1);
	sprintf(data.dapAnC, "%s %s", "C)", s1);
	strcpy(data.dapAnC, chuanHoaChuoi(data.dapAnC));
	cout<<"Nhap vao dap an D: ";
	gets(s1);
	sprintf(data.dapAnD, "%s %s", "D)", s1);
	strcpy(data.dapAnD, chuanHoaChuoi(data.dapAnD));
	do{
		cout<<"Nhap vao dap an dung(a, b, c, d): ";
		cin>>data.ketQua;
	} while (data.ketQua != 'a' && data.ketQua != 'b' && data.ketQua != 'c' && data.ketQua != 'd');
	cin.ignore();
	data.stt = l.lTail->data.stt+1;
	if (insertNode(l, data) == false){
		return false;
	}
	return ghiCauTracNghiemVaoFile(data);
}

// ham tra ve so luong node trong list
int sizeOfList(List l){
	int length = 0;
	Node *p = l.lHead;
	while (p != NULL){
		length++;
		p = p->pNext;
	}
	return length;
}

void createRandomList(List l, List &l2, int soLuongCauHoi)
{
	int soLuongList = sizeOfList(l);
	int max = soLuongList/soLuongCauHoi;
	srand(time(NULL));
	Node *p = l.lHead;
	while (p != NULL)
	{
		int values = rand() % (max+max - 1 + 1) + 1;
		for (int i = 0; i < values; i++){
			p = p->pNext;
			if (p == NULL && sizeOfList(l2) < soLuongCauHoi){
				p = l.lHead;
			}
		}
		insertNode(l2, p->data);
		if (sizeOfList(l2) == soLuongCauHoi){
			break;
		}
	}
}

void Enter()
{
	cout<<"Nhan Enter de tiep tuc"<<endl;
	getch();
}

bool kiemtradapanchuan(char x)
{
	char str[]="abcdABCD";
	for (int i=0; i<strlen(str); i++)
	{
		if (x==str[i])
			return true;
	}
	return false;
}

double ThiTracNghiem(List l2, List lichsu, double soPhutLamBai)
{
	time_t now = time(0);
	 tm *ltm = localtime(&now);
    cout << "Co  "<<soPhutLamBai<<" phut tinh tu luc: "<< ltm->tm_hour << ":";
	cout << ltm->tm_min << ":";
	cout << ltm->tm_sec << endl;
	clockid_t t1,t2;	
	t1 = clock();


	int diemmax=10;
	int socauhoi;
	socauhoi= sizeOfList(l2);
	double diem=double(diemmax)/double(socauhoi),sum =0;
	char dapan;
	Node *p=l2.lHead;
	Node *ls=lichsu.lHead;
	while (p && ls)
	{
		t2 = clock();
		double time_use = (double)(t2 - t1)/CLOCKS_PER_SEC;
		if (time_use/60.0 > soPhutLamBai){
			break;
		}
		cout<<p->data.stt<<": "<<p->data.cauHoi<<endl;
		cout<<left<<setw(30)<<p->data.dapAnA<<left<<setw(30)<<p->data.dapAnB<<endl;
		cout<<left<<setw(30)<<p->data.dapAnC<<left<<setw(30)<<p->data.dapAnD<<endl;
		cout<<"Dap an: ";
		cin>>dapan;
		while (kiemtradapanchuan(dapan) == false)
		{
			cout<<"Nhap lai dap an: ";
			cin>>dapan;
		}
		dapan=tolower(dapan);
		if (dapan == p->data.ketQua)
		{
			sum += diem;
		}
		ls->data.ketQua=dapan;
		cout<<endl;
		ls=ls->pNext;
		p=p->pNext;
	}
	return sum;
}

void printList(List l)
{
	Node *p = l.lHead;
	while (p != NULL)
	{
		cout << p->data.stt << endl;
		cout << p->data.cauHoi << endl;
		cout << p->data.dapAnA << endl;
		cout << p->data.dapAnB << endl;
		cout << p->data.dapAnC << endl;
		cout << p->data.dapAnD << endl;
		cout <<"Dap an: "<<p->data.ketQua << endl;
		cout << endl;
		p = p->pNext;
	}
}

// doc file tai khoan mk;
void DocFileTKMK(ListLogin &lg)
{
	ifstream ip("tk.csv");
	login info;
	if (!ip.is_open())
	{
		cout<<"Loi mo file"<<endl;
		return;
	}
	string line;
	getline(ip,line);
	while(ip.good())
	{
		getline(ip,info.hoten,',');
		getline(ip,info.diachi,',');
        getline(ip,info.namsinh,',');
        getline(ip,info.taikhoan,',');
        getline(ip,info.matkhau,',');
		getline(ip,info.isAdmin,'\n');
		insertlogin(lg,info);
	}
	ip.close();
}

// tim kiem tai khoang da co trong list
NodeLogin *searchtk(ListLogin l, string tk)
{
	NodeLogin *p=l.head;
	while (p)
	{ 
		if (p->info.taikhoan==tk)
			return p;
		p=p->next;
	}
	return NULL;
}
// ham kiem tra tai khoang da duoc dang ki chua, neu chua thi them vao list
int check_dangki_tk(ListLogin &l, login data)
{
	NodeLogin *p = searchtk(l,data.taikhoan);
	if (p!= NULL)
	{
		return 0;
	}
	insertlogin(l,data);
	return 1;
}

void Luutk_vaofile(ListLogin l)
{
	ofstream op("tk.csv",ios::out);
	if (!op.is_open())
	{
		cout<<"Loi mo file"<<endl;
		return;
	}
	op<<"Ho va Ten,Que Quan,Nam Sinh,Tai Khoan,Mat Khau,isAdmin\n";
	for (NodeLogin *p=l.head; p!=NULL;p=p->next)
	{
		op<<p->info.hoten<<","<<p->info.diachi<<","<<p->info.namsinh<<","<<p->info.taikhoan<<","<<p->info.matkhau<<","<<p->info.isAdmin;
		if (p != l.tail)
			op<<endl;
	}
	op.close();
}

// input password, hien thi mat khau vua nhap an voi *******
string inputPassword(int maxLength){
	string password;
	for (char c; (c = getch()); ){
		if (c == '\n' || c == '\r') { 
            std::cout << "\n";
            break;
        } else if (c == '\b') {
            std::cout << "\b \b";
            if (!password.empty()) password.erase(password.size()-1);
        } else if (c == -32) { 
            _getch(); 
        } else if (isprint(c) && password.size() < maxLength) { 
            std::cout << '*';
            password += c;
        }
	}
	return password;
}

bool questionyn()
{
	string luachon;
	cout<<"Nhan phim bat ki de lam lai (Nhan phim N de dung lai!!) ";
	cin>>luachon;
	if (luachon == "n" || luachon == "N")
	{
		return 0;
	}
	return 1;
}

void Dangki_taikhoan(ListLogin &lg)
{
	login info;
	string mk;
	while (true)
	{
		system("cls");
		sleep(1);
		cout<<"\t DANG KI TAI KHOAN "<<endl;
		cin.ignore();
		cout<<"Ho ten: ";
		getline(cin,info.hoten);
		cout<<"Dia chi: ";
		getline(cin,info.diachi);
		cout<<"Nam sinh: ";
		getline(cin,info.namsinh);
		cout<<"Tai khoan: ";
		getline(cin,info.taikhoan);
		info.isAdmin="0";
		cout<<"Mat khau: ";
		getline(cin,info.matkhau);
		cout<<"Nhap lai mat khau: ";
		getline(cin,mk);
		if (mk.compare(info.matkhau)==0)
		{
			if (check_dangki_tk(lg,info)==1)
			{
				cout<<"Tai khoan dang ki thanh cong\n";
				Luutk_vaofile(lg);
				break;
			}
			else
			{
				cout<<"Tai khoan da ton tai \n";
				if (questionyn()==0)
					break;
			}
		}
		else
		{
			cout<<"Mat khau khong khop!!!"<<endl;
			if (questionyn()==0)
				break;
		}
	}
	Enter();
	system("cls");
}


NodeLogin *Dangnhap_tk(ListLogin lg, string tk, string mk)
{
	DocFileTKMK(lg);
	NodeLogin *p=searchtk(lg,tk);
	string luachon;
	if (p!=NULL)
	{
		while (true)
		{	
			if (p->info.matkhau == mk && p->info.taikhoan==tk && p->info.isAdmin=="0")
			{
				cout<<"Dang nhap thanh cong!"<<endl;
				return p;
			}
			else
			{
				cout<<"Tai khoan hoac mat khau sai!"<<endl;
				cout<<"Nhan phim bat ki de dang nhap lai (Nhan phim N khong dang nhap lai!!) ";
				cin>>luachon;
				if (luachon == "n" || luachon == "N")
				{
					return NULL;
				}
				else
				{
					cout<<"Tai khoan: ";
					cin>>tk;
					cout<<"Mat khau: ";
					mk = inputPassword(256);
				}
			} 
		}
	}
	else
	{
		cout<<"Tai khoan chua dang ki!"<<endl;
		return NULL;
	}
}

void printListlogin(ListLogin l)
{
	NodeLogin *p = l.head;
	while (p != NULL)
	{
		cout << p->info.hoten<<endl;
		cout << p->info.diachi << endl;
		cout << p->info.namsinh << endl;
		cout << p->info.taikhoan << endl;
		cout << p->info.matkhau << endl;
		cout << p->info.isAdmin << endl;
		cout << endl;
		p = p->next;
	}
}

// Có thể chọn số lượng câu hỏi cho bài làm
int soluongcauhoi(int n)
{
	return n;
}
//giới hạn thời gian làm bài


void search (List l, char cauhoi_tk[])
{
	Node *p = l.lHead;
	while (p != NULL)
	{
		// strstr dung de kiem tra chuoi chua chuoi tra ve NULL la khong chua
		if (strstr(p->data.cauHoi, chuanHoaChuoi(cauhoi_tk)) != NULL)
			cout<<p->data.stt<<": "<<p->data.cauHoi<<endl;
		p = p->pNext;
	}
}

int searchSTT(List l, int stt)
{
	Node *p = l.lHead;
	while (p != NULL)
	{
		if (p->data.stt == stt)
			return 1;
		p = p->pNext;
	}
	return 0;
}

// Ham Cap Nhat Theo So Thu Tu
bool capNhatTheoSTT(List &l, int stt, TRACNGHIEM data)
{
	Node *p = l.lHead;
	while (p != NULL)
	{
		if (p->data.stt == stt)
		{
			// strcpy: gán giá trị của chuỗi này cho chuỗi khác thay vì dùng "="
			strcpy(p->data.cauHoi, data.cauHoi);
			strcpy(p->data.dapAnA, data.dapAnA);
			strcpy(p->data.dapAnB, data.dapAnB);
			strcpy(p->data.dapAnC, data.dapAnC);
			strcpy(p->data.dapAnD, data.dapAnC);
			p->data.ketQua= data.ketQua;
			return true;
		}
		p = p->pNext;
	}
	return false;
}

// Ham Xoa Theo So Thu Tu
bool xoaTheoSTT(List &list, int stt)
{
	Node *pdel = list.lHead;
	if (pdel == NULL)
		return false;
	else
	{
		Node *pPre = NULL;
		while (pdel != NULL)
		{
			if (pdel->data.stt == stt)
				break;
			pPre = pdel;
			pdel = pdel->pNext;
		}
		if (pdel == NULL)
			return false;
		else
		{
			if (pdel == list.lHead)
			{
				list.lHead = list.lHead->pNext;
				pdel->pNext = NULL;
				delete pdel;
				pdel = NULL;
				return true;
			}
			else if (pdel->pNext == NULL)
			{
				list.lTail = pPre;
				pPre->pNext = NULL;
				delete pdel;
				pdel = NULL;
				return true;
			}
			else
			{
				pPre->pNext = pdel->pNext;
				pdel->pNext = NULL;
				delete pdel;
				pdel = NULL;
				return true;
			}
		}
	}
}

void SapXepSTT(List &l2)
{
	int stt=1;
	Node *p=l2.lHead;
	while (p)
	{
		p->data.stt=stt;
		stt++;
		p=p->pNext;
	}
}

void menu()
{
	cout<<"\tCHUONG TRINH THI TRAC NGHIEM\t\t"<<endl;
	cout<<"|----------------------------------------------|"<<endl;
	cout<<"|   1: Dang nhap thi trac nghiem (thi sinh)    |"<<endl;
	cout<<"|   2: Dang ki thi trac nghiem (thi sinh)      |"<<endl;
	cout<<"|   3: Admin (Thay/co)                         |"<<endl;
	cout<<"|   4: Thoat khoi chuong trinh                 |"<<endl;
	cout<<"|----------------------------------------------|"<<endl;
}

void menu_thitracnghiem()
{
	cout<<"  CHUONG TRINH THI TRAC NGHIEM"<<endl;
	cout<<"|------------------------------|"<<endl;
	cout<<"|   1: Xem diem thi            |"<<endl;
	cout<<"|   2: Xem dap an trac nghiem  |"<<endl;
	cout<<"|   3: Thoat                   |"<<endl;
	cout<<"|------------------------------|"<<endl;
}

void menu_admin()
{
	cout<<"\tCHUONG TRINH THI TRAC NGHIEM\t\t"<<endl;
	cout<<"|------------------------------------------------|"<<endl;
	cout<<"|   1: Tim kiem cau hoi						    |"<<endl;
	cout<<"|   2: Cap nhat cau hoi						    |"<<endl;
	cout<<"|   3: Them cau hoi  					        |"<<endl;
	cout<<"|   4: Xoa cau hoi	                            |"<<endl;
	cout<<"|   5: Cap nhat so luong cau hoi thi trac nghiem |"<<endl;
	cout<<"|   6: Thoat va luu lai						    |"<<endl;
	cout<<"|------------------------------------------------|"<<endl;
}

void copycauhoi(List l2, List &lichsu)
{
	Node *p=l2.lHead;
	while (p)
	{
		insertNode(lichsu,p->data);
		p=p->pNext;
	}
}

void sosanhcauhoi(List l2, List lichsu)
{
	Node *p=l2.lHead;
	Node *ls=lichsu.lHead;
	while (p && ls)
	{
		cout<<p->data.stt<<": "<<p->data.cauHoi<<endl;
		cout<<left<<setw(30)<<p->data.dapAnA<<left<<setw(30)<<p->data.dapAnB<<endl;
		cout<<left<<setw(30)<<p->data.dapAnC<<left<<setw(30)<<p->data.dapAnD<<endl;
		cout<<"Dap an cua giao vien: "<<p->data.ketQua<<"\t\tDap an cua ban: "<<ls->data.ketQua<<endl;
		ls=ls->pNext;
		p=p->pNext;
		cout<<endl;
	}
}

void lichsuthicuathisinh(List l2,List lichsu, string hoten, string namsinh, double diemthi)
{
	ofstream op("lichsuthi.txt",ios::app);
	Node *h=lichsu.lHead;
	Node *p=l2.lHead;
	if (!op.is_open())
    {
		cout<<"Loi mo file"<<endl;
		return;
	}
	ostringstream convert;
	convert << diemthi ; 
	string thongtin="Ho Ten: "+ hoten+"\n"+"Nam sinh: "+namsinh+"\n" +"Diem thi: "+ convert.str()+"/10 " + "\n";
	op<<thongtin;
	while (h && p)
	{
		op<<h->data.stt<<":"<<h->data.cauHoi<<endl;
		op<<"Dap an dung: "<<p->data.ketQua<<endl;
		op<<"Dap an TS: "<<h->data.ketQua<<endl;
		h=h->pNext;
		p=p->pNext;
	}
	op<<"---------------------------------------------------"<<endl;
	op.close();
}

void dangnhapkiemtraTN(List l, List l2, ListLogin lg, int cauhoi, List lichsu)
{
	string tk,mk;
	double diem;
	int lctn;
	cout<<"\tDANG NHAP"<<endl;
	cout<<"Tai khoan: ";
	cin>>tk;
	cout<<"Mat khau: ";
	mk = inputPassword(256);
	NodeLogin *dn=Dangnhap_tk(lg,tk,mk);
	if (dn!=NULL)
	{
		int soPhutLamBai;
		do{
			cout<<"\t\tNhap vao so phut can lam(nhap 0 thi lam theo so phut thi thuc): ";
			cin>>soPhutLamBai;
			if (soPhutLamBai == 0){
				soPhutLamBai = 30;
				break;
			}
		} while (soPhutLamBai <= 0);
		sleep(1);
		system("cls");
		cout<<"\t\t BAT DAU LAM BAI THI"<<endl;
		Enter();
		createRandomList(l, l2, cauhoi);
		SapXepSTT(l2);
		copycauhoi(l2,lichsu);
		diem=ThiTracNghiem(l2,lichsu,soPhutLamBai);
		cout<<"\t\tKET THUC BAI THI"<<endl;
		lichsuthicuathisinh(l2,lichsu,dn->info.hoten,dn->info.namsinh,diem);
		Enter();
		while (true)
		{
			system("cls");
			menu_thitracnghiem();
			cout<<"Lua chon cua ban: ";
			cin>>lctn;
			switch (lctn)
			{
				case 1:
				{
					cout<<"Diem thi cua ban: "<<diem<<"/10 diem"<<endl;
					Enter();
					break;
				}
				case 2:
				{
					cout<<"\tDAP AN CHI TIET"<<endl;
					sosanhcauhoi(l2,lichsu);
					Enter();
					break;
				}
				case 3:
				{
					cout<<"\t\tHOAN THANH BAI THI"<<endl;
					exit(0);
				}
			}
		}
		
	}
}

int main()
{
	List l,l2,lichsu;
	INIT(l);
	INIT(l2);
	INIT(lichsu);
	docFileTracNghiem(l);
	ListLogin lg;
	initLogin(lg);
	DocFileTKMK(lg);
	login info;
	int cauhoi;
	int luachon;
	cauhoi=10;
	system("cls");
	while (true)
	{
		menu();
		cout<<"Lua chon cua ban: ";
		cin>>luachon;
		sleep(1);
		system("cls");
		switch (luachon)
		{
			case 1:
			{
				dangnhapkiemtraTN(l,l2,lg,cauhoi,lichsu);
				break;
			}
			case 2:
			{
				Dangki_taikhoan(lg);
				break;
			}
			case 3:
			{
				// cout<<"Ban chon dang nhap voi quyen quan tri vien!"<<endl;
				// cin.ignore();
				// string account;
				// cout<<"Tai Khoan: ";
				// getline(cin, account);
				// cout<<"Mat Khau: ";
				// string password = inputPassword(256); 
			}
			case 4:
				exit(0);
		}
	}
}

//int main()
//{
//	List l;
//	INIT(l);
//	docFileTracNghiem(l);
//	printList(l);
//search
	// cout<<"Nhap Tu Khoa Muon Tim: "; char a[255]; cin.getline(a,255);
	// search(l,a);
	//cap nhat
//	cout<<"Nhap tu khoa: "; char b[255]; cin.getline(b,255);
//	search(l,b);
//	cout<<"Nhap STT: "; int stt; cin>>stt;
//	cin.ignore();
//		
//	if( stt>sizeOfList(l) || stt<1)
//		cout<<"Khong tim thay";
//	else
//	{	
//		Node *p;
//		cout << "\nNhap Cau Hoi Moi: ";
//		cin.getline(p->data.cauHoi, 255);
//		cout << "Nhap Dap An A Moi: ";
//		cin.getline(p->data.dapAnA, 255);
//		cout << "Nhap Dap An B Moi: ";
//		cin.getline(p->data.dapAnB, 255);
//		cout << "Nhap Dap An C Moi: ";
//		cin.getline(p->data.dapAnC, 255);
//		cout << "Nhap Dap An D Moi: ";
//		cin.getline(p->data.dapAnD, 255);
//		cout << "Nhap Ket Qua Moi: ";
//		cin >> p->data.ketQua;
//		if (capNhatTheoSTT(l, stt, p->data) == true)
//		{
//			cout << "Cap Nhat Thanh Cong";
//			while(p){
//				if(p->data.stt==1)
//					ghiMoiFile(p->data);	
//				else
//					ghiCauTracNghiemVaoFile(p->data);
//				p = p->pNext;
//			}
//		}
//		else
//			cout << "Cap Nhat That Bai";
//	}
//	printList(l);
	//Xoa
//	cout<<"Nhap STT Muon Xoa: "; int stt;cin>>stt;
//	if(xoaTheoSTT(l,stt)==true)
//	{
//		cout<<"Xoa Thanh Cong";
//		SapXepSTT(l);
//		Node *p = l.lHead;
//		while(p!=NULL)
//		{
//			if(p->data.stt==1)
//				ghiMoiFile(p->data);
//			else
//				ghiCauTracNghiemVaoFile(p->data);
//			p=p->pNext;
//		}
//	}
//	else
//		cout<<"Xoa That Bai";
//	printList(l);