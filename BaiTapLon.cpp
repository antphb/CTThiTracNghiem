#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
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
	l.head = l.tail = NULL;
}

NodeLogin *getnodelogin(login info)
{
	NodeLogin *p;
	p = new NodeLogin;
	if (p == NULL)
	{
		return NULL;
	}
	p->info = info;
	p->next = NULL;
	return p;
}

void addlastLogin(ListLogin &l, NodeLogin *new_node)
{
	if (l.head == NULL)
	{
		l.head = l.tail = new_node;
	}
	else
	{
		l.tail->next = new_node;
		l.tail = new_node;
	}
}

void insertlogin(ListLogin &l, login info)
{
	NodeLogin *new_node = getnodelogin(info);
	if (new_node == NULL)
	{
		return;
	}
	addlastLogin(l, new_node);
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
		docFile >> data.stt;
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
	if (count != 0)
	{
		cout << "Khong the them duoc " << count << " cau hoi trong file!" << endl;
	}
	docFile.close();
}
// ghi 1 cau hoi trac nghiem trac nghiem moi bo sung vao file
bool ghiCauTracNghiemVaoFile(TRACNGHIEM data)
{
	ofstream ghiFile("cauhoi.txt", ios::app);
	if (ghiFile.bad())
	{
		cout << "Khong the mo file de ghi!";
		return false;
	}
	ghiFile << data.stt << endl;
	ghiFile << data.cauHoi << endl;
	ghiFile << data.dapAnA << endl;
	ghiFile << data.dapAnB << endl;
	ghiFile << data.dapAnC << endl;
	ghiFile << data.dapAnD << endl;
	ghiFile << data.ketQua << endl;
	ghiFile.close();
	return true;
}
// ghi 1 cau hoi trac nghiem vao file trong
bool ghiMoiFile(TRACNGHIEM data)
{
	ofstream ghiFile("cauhoi.txt");
	if (ghiFile.bad())
	{
		cout << "Khong the mo file de ghi!";
		return false;
	}
	ghiFile << data.stt << endl;
	ghiFile << data.cauHoi << endl;
	ghiFile << data.dapAnA << endl;
	ghiFile << data.dapAnB << endl;
	ghiFile << data.dapAnC << endl;
	ghiFile << data.dapAnD << endl;
	ghiFile << data.ketQua << endl;
	ghiFile.close();
	return true;
}

// xoa ki tu trong chuoi theo vi tri
void xoaTaiViTri(char str[], int index)
{
	for (int i = index; i < strlen(str); i++)
	{
		str[i] = str[i + 1];
	}
}

// chuan hoa chuoi, loai bo khoang cach du thua, in hoa dau dong
char *chuanHoaChuoi(char str[])
{
	// xoa khoang trang o dau
	while (strlen(str) > 1 && str[0] == ' ')
	{
		xoaTaiViTri(str, 0);
	}
	// xoa khoang trang ben trong cau
	for (int i = 0; i < strlen(str) - 1; i++)
	{
		if (str[i] == ' ' && str[i + 1] == ' ')
		{
			xoaTaiViTri(str, i);
			i--;
		}
	}
	// xoa o cuoi cau
	while (str[strlen(str) - 1] == ' ')
	{
		str[strlen(str) - 1] = '\0';
	}
	// in hoa ki tu dau dong
	if (str[0] >= 'a' && str[0] <= 'z')
	{
		str[0] = str[0] - 32;
	}
	// in hoa ki tu sau dau cach
	for (int i = 0; i < strlen(str) - 1; i++)
	{
		if (str[i] == ' ' && str[i + 1] >= 'a' && str[i + 1] <= 'z')
		{
			str[i + 1] = str[i + 1] - 32;
		}
	}
	char *tempS = str;
	return tempS;
}

// them cau hoi vao danh sach va ghi cau hoi do vao file
bool themCauHoi(List &l)
{
	TRACNGHIEM data;
	char s1[253];
	cout << "Nhap vao cau hoi day du: ";
	gets(data.cauHoi);
	strcpy(data.cauHoi, chuanHoaChuoi(data.cauHoi));
	cout << "Nhap vao dap an A: ";
	gets(s1);
	sprintf(data.dapAnA, "%s %s", "A)", s1);
	strcpy(data.dapAnA, chuanHoaChuoi(data.dapAnA));
	cout << "Nhap vao dap an B: ";
	gets(s1);
	sprintf(data.dapAnB, "%s %s", "B)", s1);
	strcpy(data.dapAnB, chuanHoaChuoi(data.dapAnB));
	cout << "Nhap vao dap an C: ";
	gets(s1);
	sprintf(data.dapAnC, "%s %s", "C)", s1);
	strcpy(data.dapAnC, chuanHoaChuoi(data.dapAnC));
	cout << "Nhap vao dap an D: ";
	gets(s1);
	sprintf(data.dapAnD, "%s %s", "D)", s1);
	strcpy(data.dapAnD, chuanHoaChuoi(data.dapAnD));
	do
	{
		cout << "Nhap vao dap an dung(a, b, c, d): ";
		cin >> data.ketQua;
	} while (data.ketQua != 'a' && data.ketQua != 'b' && data.ketQua != 'c' && data.ketQua != 'd');
	cin.ignore();
	data.stt = l.lTail->data.stt + 1;
	if (insertNode(l, data) == false)
	{
		return false;
	}
	return ghiCauTracNghiemVaoFile(data);
}

// doc file tai khoan mk;
void DocFileTKMK(ListLogin &lg)
{
	ifstream ip("tk.csv");
	login info;
	if (!ip.is_open())
	{
		cout << "Loi mo file" << endl;
		return;
	}
	while (ip.good())
	{
		getline(ip, info.hoten, ',');
		getline(ip, info.diachi, ',');
		getline(ip, info.namsinh, ',');
		getline(ip, info.taikhoan, ',');
		getline(ip, info.matkhau, '\n');
		insertlogin(lg, info);
	}
	ip.close();
}

// ham tra ve so luong node trong list
int sizeOfList(List l)
{
	int length = 0;
	Node *p = l.lHead;
	while (p != NULL)
	{
		length++;
		p = p->pNext;
	}
	return length;
}

void createRandomList(List l, List &l2, int soLuongCauHoi)
{
	int soLuongList = sizeOfList(l);
	int max = soLuongList / soLuongCauHoi;
	srand(time(NULL));
	Node *p = l.lHead;
	while (p != NULL)
	{
		int values = rand() % (max + max - 1 + 1) + 1;
		for (int i = 0; i < values; i++)
		{
			p = p->pNext;
			if (p == NULL && sizeOfList(l2) < soLuongCauHoi)
			{
				p = l.lHead;
			}
		}
		insertNode(l2, p->data);
		if (sizeOfList(l2) == soLuongCauHoi)
		{
			break;
		}
	}
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
		cout << "Dap an: " << p->data.ketQua << endl;
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
	while(ip.good())
	{
		getline(ip,info.hoten,',');
		getline(ip,info.diachi,',');
        getline(ip,info.namsinh,',');
        getline(ip,info.taikhoan,',');
        getline(ip,info.matkhau,'\n');
		insertlogin(lg,info);
	}
	ip.close();
}

void printListlogin(ListLogin l)
{
	NodeLogin *p = l.head;
	while (p != NULL)
	{
		cout << p->info.hoten << endl;
		cout << p->info.diachi << endl;
		cout << p->info.namsinh << endl;
		cout << p->info.taikhoan << endl;
		cout << p->info.matkhau << endl;
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

// Ham Tim Kiem Theo Cau Hoi Neu Co Thi Se Tra ve So Thu Tu
void search(List l, char cauhoi_tk[])
{
	Node *p = l.lHead;
	while (p != NULL)
	{
		// strstr dung de kiem tra chuoi chua chuoi tra ve NULL la khong chua
		// strlwr dung de dua chuoi ve chu thuong (ngoai le: tolower chi chuyen chuoi chua 1 ky tu)
		if (strstr(strlwr(p->data.cauHoi), strlwr(cauhoi_tk)) != NULL)
			cout<< p->data.stt<<". "<<p->data.cauHoi<<endl;
		p = p->pNext;
	}
}

int searchSTT(List l, int stt)
{
	Node *p = l.lHead;
	while (p != NULL)
	{
		if (p->data.stt == stt)
			return p->data.stt;
		p = p->pNext;
	}
	return 0;
}
/*

// Ham Cap Nhat Theo So Thu Tu
bool capNhatTheoSTT(List &l, int stt, TRACNGHIEM data)
{
	Node *p = l.lHead;
	while (p != NULL)
	{
		if (p->data.stt == stt)
		{
			// strcpy: gan gia tri cua chuoi nay cho chuoi khac thay vi dung "="
			strcpy(p->data.cauHoi, cauHoiNew);
			strcpy(p->data.dapAnA, a);
			strcpy(p->data.dapAnB, b);
			strcpy(p->data.dapAnC, c);
			strcpy(p->data.dapAnD, d);
			strcpy(p->data.ketQua, kq);
			return true;
		}
		//ghi lai toan bo cau hoi vao file
		if (stt == 1 || p->data.stt == 1)
			ghiMoiFile(p->data);
		else
			ghiCauTracNghiemVaoFile(p->data);
			strcpy(p->data.cauHoi, data.cauHoi);
			strcpy(p->data.dapAnA, data.dapAnA);
			strcpy(p->data.dapAnB, data.dapAnB);
			strcpy(p->data.dapAnC, data.dapAnC);
			strcpy(p->data.dapAnD, data.dapAnD);
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
	if (stt <= sizeOfList(list) || stt > 0)
	{
		Node *pdel = list.lHead;
		if (pdel != NULL)
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
		//cap nhat lai stt
		Node *p = list.lHead;
		for (int i = 1; i <= sizeOfList(list); i++)
		{
			if (p != NULL)
			{
				p->data.stt = i;
				//cap nhat lai file moi
				if (i == 1)
					ghiMoiFile(p->data);
				else
					ghiCauTracNghiemVaoFile(p->data);
				p = p->pNext;
			}
		}
	}
	return false;
}
**/

// Ham Xoa Theo So Thu Tu
int main()
{
	List l;
	INIT(l);
	ListLogin lg;
	initLogin(lg);
	docFileTracNghiem(l);

	/* List l2;
	INIT(l2);
	createRandomList(l, l2, 20);
	printList(l2);*/

	/*DocFileTKMK(lg);
	printListlogin(lg);*/
	// them cau hoi vao danh sach, va them vao file
	// themCauHoi(l);
	printList(l);
	int chon;
	do
	{
		cout << "\t\n____MENU____";
		cout << "\n1.Tim Kiem Cau Hoi";
		cout << "\n2.Cap Nhat Cau Hoi";
		cout << "\n3.Xoa Cau Hoi Theo STT";
		cout << "\n4.In Danh Sach Cau Hoi";
		cout << "\nMoi Chon:";
		cin >> chon;
		cin.ignore();
		switch (chon)
		{
		case 1:
			char x[255];
			cout << "Nhap Tu Khoa Cau Hoi Can Tim: ";
			cin.getline(x, 255);
			search(l, x);
			break;
		/**case 2:{
			char cauHoi[255], a[255], b[255], c[255], d[255], ketQua, cauHoiHoi[255], yn, yn1;
			int stt, luaChon, flag;
			cout << "Ban muon cap nhat theo so thu tu hay cau hoi? (1_stt/2_cau hoi)";
			cin >> luaChon;
			cin.ignore();
			if (luaChon == 1)
			{
				cout << "Nhap So Thu Tu Can Cap Nhat: ";
				cin >> stt;
				cin.ignore();
				cout << "Nhap Cau Hoi Moi: ";
				cin.getline(cauHoi, 255);
				cout << "Nhap Dap An A Moi: ";
				cin.getline(a, 255);
				cout << "Nhap Dap An B Moi: ";
				cin.getline(b, 255);
				cout << "Nhap Dap An C Moi: ";
				cin.getline(c, 255);
				cout << "Nhap Dap An D Moi: ";
				cin.getline(d, 255);
				cout << "Nhap Ket Qua Moi: ";
				cin >> ketQua;
				if (capNhatTheoSTT(l, stt, cauHoi, a, b, c, d, ketQua) == true)
					cout << "Cap Nhat Thanh Cong";
				else
					cout << "Cap Nhat That Bai";
			}
			else if (luaChon == 2)
			{
				while (flag == 1)
				{
					cout << "Nhap cau hoi ban muon cap nhat: ";
					cin.getline(cauHoiHoi, 255);
					if (search(l, cauHoiHoi) == 0)
						cout << "Khong the tim duoc cau hoi ban can!";
					else
					{
						cout << "Co phai ban can cap nhat cau hoi so " << search(l, cauHoiHoi) << " khong?(y/n)";
						cin >> yn;
						if (strcmp(yn, "y") == 0)
						{
							stt = search(l, cauHoiHoi);
							cout << "Nhap Cau Hoi Moi: ";
							cin.getline(cauHoi, 255);
							cout << "Nhap Dap An A Moi: ";
							cin.getline(a, 255);
							cout << "Nhap Dap An B Moi: ";
							cin.getline(b, 255);
							cout << "Nhap Dap An C Moi: ";
							cin.getline(c, 255);
							cout << "Nhap Dap An D Moi: ";
							cin.getline(d, 255);
							cout << "Nhap Ket Qua Moi: ";
							cin >> ketQua;
							if (capNhatTheoSTT(l, stt, cauHoi, a, b, c, d, ketQua) == true)
								cout << "Cap Nhat Thanh Cong";
							else
								cout << "Cap Nhat That Bai";
							flag = 0;
						}
						else if (strcmp(yn, "n") == 0)
						{
							cout << "Ban co muon tim lai khong?(y/n)";
							cin >> yn1;
							if (strcmp(yn, "y") == 0)
								flag = 1;
							else if (strcmp(yn, "n") == 0)
								flag = 0;
							else
								cout << "khong hop le!";
						}
						else
							cout << "Khong hop le!";
					}
				}
			}
			else
				cout << "khong hop le!";
		}
			break;
		case 3:{
			char cauHoiHoi[255], yn, yn1;
			int stt, luaChon, flag;
			cout << "Ban muon cap nhat theo so thu tu hay cau hoi? (1_stt/2_cau hoi)";
			cin >> luaChon;
			cin.ignore();
			if (luaChon == 1)
			{
				cout << "Nhap So Thu Tu Can xoa: ";
				cin >> stt;
				cin.ignore();
				xoaTheoSTT(l, stt);
				if (xoaTheoSTT(l, stt) == true)
					cout << "xoa Thanh Cong";
				else
					cout << "xoa That Bai";
			}
			else if (luaChon == 2)
			{
				while (flag == 1)
				{
					cout << "Nhap cau hoi ban muon xoa: ";
					cin.getline(cauHoiHoi, 255);
					if (search(l, cauHoiHoi) == 0)
						cout << "Khong the tim duoc cau hoi ban can!";
					else
					{
						cout << "Co phai ban can xoa cau hoi so " << search(l, cauHoiHoi) << " khong?(y/n)";
						cin >> yn;
						if (strcmp(yn, "y") == 0)
						{
							xoaTheoSTT(l, stt);
							if (xoaTheoSTT(l, stt) == true)
								cout << "xoa Thanh Cong";
							else
								cout << "xoa That Bai";
							flag = 0;
						}
						else if (strcmp(yn, "n") == 0)
						{
							cout << "Ban co muon xoa lai khong?(y/n)";
							cin >> yn1;
							if (strcmp(yn, "y") == 0)
								flag = 1;
							else if (strcmp(yn, "n") == 0)
								flag = 0;
							else
								cout << "khong hop le!";
						}
						else
							cout << "Khong hop le!";
					}
				}
			}
			else
				cout << "khong hop le!";
		}
			break;**/
		case 4:
			printList(l);
			break;
		}

	} while (chon < 10);

	// printList(l);

	// tim kiem
}
