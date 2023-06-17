const int textColor = 15;
const int pink= COLOR(255,209,224);
const int green = COLOR(105,165,131);
const int blue = COLOR(108,126,225);
const int hardgreen = COLOR(107,203,149);
const int violet = COLOR(174,162,197);
const int red = COLOR(255,150,138);
void barhongcovien(int x1, int y1, int x2, int y2) {
	setcolor(0);
	setfillstyle(1,pink);
	bar(x1,y1,x2,y2);
	rectangle(x1,y1,x2,y2);
}
void bartrangcovien(int x1, int y1, int x2, int y2) {
	setcolor(0);
	setfillstyle(1,violet);
	bar(x1,y1,x2,y2);
	rectangle(x1,y1,x2,y2);
}
void message(char text[]) {
	settextstyle(10,0,1);
	setbkcolor(pink);
	outtextxy(30, 280, text);
	delay(1000);
	barhongcovien(20,230,310,520);
	settextstyle(10,0,3);
	setcolor(red);
	outtextxy(90,240," THONG BAO");
	setcolor(0);
}
void message2(char text1[], char text2[]) {
	settextstyle(10,0,1);
	setbkcolor(pink);
	outtextxy(30, 280, text1);
	outtextxy(30, 350, text2);
	delay(2000);
	barhongcovien(20,230,310,520);
	settextstyle(10,0,3);
	setcolor(red);
	outtextxy(90,240," THONG BAO");
	setcolor(0);
}
int MAP[1400][700];
void initMapID() {
	for (int i =0; i <1400; i++) {
		for (int j = 0; j < 700; j++) {
			MAP[i][j]=0;
		}
	}
}
void createID(int x1, int y1, int x2, int y2, int ID ) {
	for (int i =x1; i <x2; i++) {
		for (int j=y1; j<y2; j++)
			MAP[i][j]=ID;
	}
}

void createLine(int x1, int y1, int height, int widthArr[], int numOfColumn) {
	int x2, y2;
	y2=y1+height;
	setfillstyle(1,pink);
	for (int i = 1; i <= numOfColumn; i++ ) {
		x2=x1+widthArr[i];
		bar(x1,y1,x2,y2);
		rectangle(x1,y1,x2,y2);
		x1=x2;
	}
}


//height55
void createButton(int x1, int y1,int width, int height, char text[], int text_color, int ID) {
	setfillstyle(1,green);
	bar(x1,y1,x1+width,y1+height);
	setcolor(text_color);
	setbkcolor(green);
	outtextxy(x1+5,y1+14,text);
	createID(x1,y1,x1+width,y1+height,ID);
}


void chosenMenu(int x1, int y1,int width, int height, char text[], int text_color, int ID) {
	settextstyle(10,0,3);
	setfillstyle(1,hardgreen);
	bar(x1,y1,x1+width,y1+height);
	setcolor(text_color);
	setbkcolor(hardgreen);
	outtextxy(x1+5,y1+14,text);
	createID(x1,y1,x1+width,y1+height,ID);
}

//height70
void createButton2(int x1, int y1,int width, int height, char text[], int text_color, int ID) {
	setfillstyle(1,red);
	bar(x1,y1,x1+width,y1+height);
	setcolor(text_color);
	setbkcolor(red);
	outtextxy(x1+5,y1+20,text);
	createID(x1,y1,x1+width,y1+height,ID);
}
void createButton3(int x1, int y1,int width, int height, char text[], int text_color, int ID) {
	setfillstyle(1,blue);
	bar(x1,y1,x1+width,y1+height);
	setcolor(text_color);
	setbkcolor(blue);
	outtextxy(x1+5,y1+4,text);
	createID(x1,y1,x1+width,y1+height,ID);
}
void createButton4(int x1, int y1,int width, int height, char text[], int text_color, int ID) {
	setfillstyle(1,7);
	bar(x1,y1,x1+width,y1+height);
	setcolor(text_color);
	setbkcolor(7);
	outtextxy(x1+5,y1+4,text);
	createID(x1,y1,x1+width,y1+height,ID);
}
void createButton5(int x1, int y1,int width, int height, char text[], int text_color, int ID) {
	setfillstyle(1,green);
	bar(x1,y1,x1+width,y1+height);
	setcolor(text_color);
	setbkcolor(green);
	outtextxy(x1+5,y1+4,text);
	createID(x1,y1,x1+width,y1+height,ID);
}
void createButton6(int x1, int y1,int width, int height, char text[], int text_color, int ID) {
	setfillstyle(1,red);
	bar(x1,y1,x1+width,y1+height);
	setcolor(text_color);
	setbkcolor(red);
	outtextxy(x1+5,y1+4,text);
	createID(x1,y1,x1+width,y1+height,ID);
}
void createTableID(int x1,int y1,int height,int width, int ID, int n) {
	for (int i = 0; i <= n ; i++) {
		createID(x1,y1+height*i,x1+width,y1+height*i+height,ID+i);
	}
}

void highlightBox(int x1, int y1, int height, int widthArr[], int numOfColumn) {
	int temp=x1;
	int x2, y2;
	y2=y1+height;
	setcolor(12);
	for (int i = 1; i <= numOfColumn; i++ ) {
		x2=temp+widthArr[i];
		rectangle(temp,y1,x2,y2);
		temp=x2;
	}
	temp = x1;
	delay(500);
	setcolor(0);
}
void createTable(int x1, int y1, int height, int widthArr[], int numOfColumn, int numOfRow, char title[][50]) {
	setcolor(0);
	setbkcolor(pink);
	int sum = 0;
	for (int i = 0; i<sizeof(widthArr) / sizeof(int); i++) {
		sum+=widthArr[i];
	}
	for (int i = 0; i <= numOfRow; i++) {
		createLine(x1,y1+height*i,height,widthArr,numOfColumn);
	}
	setcolor(12);
	for (int i = 0; i < numOfColumn; i++) {
		outtextxy(x1+10,y1+10, title[i]);
		x1=x1+widthArr[i+1];
	}
	setcolor(0);
}

void showMenu() {
	setfillstyle(1,pink);
	settextstyle(10,0,3);
	bar(0,0,1400,700);
	int width=290;
	int height=55;
	int spacing=10;
	createButton(20,15,width,height," DANH SACH DAU SACH",textColor,1);
	createButton(20,80,width,height," DANH SACH DOC GIA", textColor,2);
	createButton(20,145,width,height,"  QUAN LI MUON TRA", textColor,3);
	setcolor(0);
	barhongcovien(20,230,310,520);
	setbkcolor(pink);
	setcolor(red);
	outtextxy(90,240," THONG BAO");
	createButton2(20,550,width,70+2,"    SAVE AND EXIT", textColor,4);
}
void inSoTrang(int page, int maxPage) {
	setbkcolor(pink);
	settextstyle(10,0,1);
	char tmp1[50];
	char tmp2[50];
	itoa(page,tmp1,10);
	strcat(tmp1,"/");
	strcat(tmp1,itoa(maxPage,tmp2,10));
	outtextxy(800,650,tmp1);
	settextstyle(10,0,3);
}
void inKhungDauSach() {
	settextstyle(10,0,2);
	int x1=330;
	int y1=180;
	int height = 40;
	int width[7]= {0,120,300,120,195,120,200};
	char title[][50]= {
		"  ISBN",
		"        Ten sach",
		"So trang",
		"   Tac gia",
		"Nam XB",
		"    The loai"
	};
	setcolor(0);
	createTable(x1,y1,height,width,6,10,title);
	createButton(400,630,140,55,"Trang truoc",0,114);
	createButton(1200,630,140,55," Trang sau",0,115);
}
void khungTopDS() {
	setbkcolor(pink);
	setfillstyle(1,pink);
	bar(330,15,1385,170);
	settextstyle(10,0,6);
	setcolor(12);
	outtextxy(650,70,"TOP 10 DAU SACH");
	setcolor(0);
	rectangle(330,15,1385,170);
	setbkcolor(pink);
	settextstyle(10,0,1);
	int x1=330;
	int y1=180;
	int height = 40;
//	int width[7]= {0,90,211,171,231,181,171};
	int width[7]= {0,90,231,181,171,211,171};
//	char title[][50]= {
//		"Hang",
//		"Nam xuat ban",
//		" So luot muon",
//		"    Ten sach",
//		"    Tac gia",
//		"  The loai",
//	};
	char title[][50]= {
		"Hang",
		"    Ten sach",
		"    Tac gia",
		"  The loai",
		"   Nam xuat ban",
		" So luot muon",
	};
	createTable(x1,y1,height,width,6,10,title);
	createButton(400,630,140,55,"Trang truoc",0,1131);
	createButton(1200,630,140,55," Trang sau",0,1132);
}
void inKhungDocGia() {
	settextstyle(10,0,2);
	int x1=330;
	int y1=180;
	int height = 40;
	int width[6]= {0,150,300,200,200,205};
	char title[][50]= {
		"  Ma the",
		"          Ho",
		"      Ten",
		"   Gioi tinh",
		" Trang thai the",
	};
	createTable(x1,y1,height,width,5,10,title);

	settextstyle(10,0,3);
}

void inTableDauSach(ListDauSach l, int page) {
	char tmp[50]= "";
	setbkcolor(pink);
	settextstyle(10,0,1);
	for (int i = 0; i < 10 && page*10-10+i<l.n; i++) {
		outtextxy(365,230+40*i,l.dausach[page*10-10+i]->ISBN);
		outtextxy(480,230+40*i,l.dausach[page*10-10+i]->ten);
		outtextxy(795,230+40*i,itoa(l.dausach[page*10-10+i]->sotrang,tmp,10));
		outtextxy(900,230+40*i,l.dausach[page*10-10+i]->tacgia);
		outtextxy(1100,230+40*i,itoa(l.dausach[page*10-10+i]->nxb,tmp,10));
		outtextxy(1230,230+40*i,l.dausach[page*10-10+i]->theloai);
	}
}



void inKhungDMS() {
	setfillstyle(1,pink);
	bar(330,15,1385,170);
	setcolor(0);
	settextstyle(10,0,6);
	setcolor(12);
	setbkcolor(pink);
	outtextxy(510,70,"QUAN LI DANH MUC SACH");
	settextstyle(10,0,1);
	setcolor(0);
	outtextxy(370,40,"*Nhan chuot trai de xoa ma sach!");
	rectangle(330,15,1385,170);
	settextstyle(10,0,2);
	int x1=330;
	int y1=180;
	int height = 40;
	int width[4]= {0,555,250,250};
	char title[][50]= {
		"                   Ma Sach",
		"       Vi Tri",
		"     Trang Thai",
	};
	int j = 0;
	createTable(x1,y1,height,width,3,10,title);
	outtextxy(370,140,"THEM SACH MOI:");
	bartrangcovien(550,136,650,160);
	createID(550,136,650,160,113);
	bartrangcovien(680,136,875,160);
	createID(680,136,875,160,114);
	setbkcolor(violet);
	setcolor(7);
	settextstyle(10,0,1);
	outtextxy(560,137,"Nhap SL");
	outtextxy(690,137,"Nhap vi tri sach");
	createButton(400,630,140,55,"Trang truoc",textColor,111);
	createButton(1200,630,140,55," Trang sau",textColor,112);
	createButton5(905,136,65,26," ADD",textColor,115);
	settextstyle(10,0,3);
}
void inTableDMS (ListDauSach l, int page, int i) {
	setbkcolor(pink);
	setcolor(0);
	settextstyle(10,0,1);
	NodeDMS temp = l.dausach[i]->FirstDMS;
	for (int i = 0; i < page*10-10 && temp!=NULL; i++) {
		temp=temp->next;
	}
	int j = 0;
	while (temp!=NULL && j<10) {
		outtextxy(365,230+40*j,temp->data.MaSach);
		outtextxy(900,230+40*j,temp->data.ViTri);
		if (temp->data.TrangThai==0) {
			outtextxy(1150,230+40*j,"Co the cho muon");
		} else if (temp->data.TrangThai==1) {
			outtextxy(1150,230+40*j,"Da cho muon");
		} else {
			outtextxy(1150,230+40*j,"Da thanh li");
		}
		j++;
		temp=temp->next;
	}
}
void InDocGia(NodeDocGia root_tmp,DocGia *&MangDocGia,int page,int loc) {
	setbkcolor(pink);
	settextstyle(10,0,1);
	MangDocGia=new DocGia[DemNut(root_tmp)];
	int n=0;
	char tmp[50]= "";
	DoCayVaoMang(root_tmp,MangDocGia,n);
	if (loc==1) quickSortTen(MangDocGia,0,n-1);
	setcolor(0);
	for (int i = 0; i < 10 && page*10-10+i<n; i++) {
		outtextxy(370,230+40*i,itoa(MangDocGia[page*10-10+i].mathe,tmp,10));
		outtextxy(567,230+40*i,MangDocGia[page*10-10+i].ho);
		outtextxy(855,230+40*i,MangDocGia[page*10-10+i].ten);
		if (MangDocGia[page*10-10+i].phai==0)
			outtextxy(1055,230+40*i,"Nam");
		else outtextxy(1055,230+40*i,"Nu");
		if (MangDocGia[page*10-10+i].trangthai==0)
			outtextxy(1240,230+40*i,"Hoat Dong");
		else outtextxy(1240,230+40*i,"Bi Khoa");
	}
	settextstyle(10,0,3);
}
void inTableSachDGMuon() {
	setbkcolor(pink);
	settextstyle(10,0,3);
	int x1=330;
	int y1=260;
	int height = 80;
	int width[5] = {0,200,385,235,235};
	char title[50][50] = {
		"   Ma Sach ",
		"         Ten Sach",
		"   Ngay Muon",
		"   Trang Thai"
	};
	createTable(x1,y1,height,width,4,3,title);
	createTableID(x1,y1+80,height,1055,27,2);
	settextstyle(10,0,1);
	createButton(800,600,110,55," Tro lai", 15,25);
	createButton4(950,200,70,30," DEN",0,0);
	createButton4(1050,200,70,30," TRA",0,0);
	createButton4(1150,200,70,30," HUY",0,0);
}
//void inSachDGMuon(DocGia *MangDocGia, int tt) {
//	setcolor(0);
//	setbkcolor(pink);
//	settextstyle(10,0,2);
//	outtextxy(350,205,"MUON SACH: ");
//	createID(500,200,800,230,26);
//	bartrangcovien(500,200,800,230);
//	settextstyle(10,0,1);
//	setbkcolor(violet);
//	setcolor(7);
//	outtextxy(510,205,"Nhap ten sach can muon");
//	settextstyle(10,0,3);
//	setbkcolor(pink);
//	setcolor(0);
//	if (MangDocGia[tt].slmuon==0) {
//		outtextxy(600,400,"Doc gia nay hien chua muon sach nao!");
//		settextstyle(10,0,1);
//		createButton(800,600,110,55," Tro lai", 15,25);
//		return;
//	}
//	inTableSachDGMuon();
//	NodeMuonTra tmp = MangDocGia[tt].First;
//	int i = 0;
//	setcolor(0);
//	setbkcolor(pink);
//	settextstyle(10,0,3);
//	while(tmp!=NULL) {
//		if (tmp->muontra.TrangThai==0) {
//			outtextxy(1350,360+80*i,"Dang Muon");
//			outtextxy(350,360+80*i,tmp->muontra.MaSach);
//			outtextxy(950,360+80*i,tmp->muontra.NgayMuon);
//			i++;
//		} else if (tmp->muontra.TrangThai==3)  {
//			setcolor(12);
//			outtextxy(1250,360+80*i,"Qua Han");
//			setcolor(0);
//			outtextxy(350,360+80*i,tmp->muontra.MaSach);
//			outtextxy(950,360+80*i,tmp->muontra.NgayMuon);
//			i++;
//		}
//		tmp=tmp->right;
//	}
//}
void inSachDGMuonTuCay(NodeDocGia node,ListDauSach l) {
	setcolor(0);
	setbkcolor(pink);
	settextstyle(10,0,2);
	outtextxy(350,205,"MUON SACH: ");
	createID(500,200,800,230,26);
	bartrangcovien(500,200,800,230);
	settextstyle(10,0,1);
	setbkcolor(violet);
	setcolor(7);
	outtextxy(510,205,"Nhap ma sach can muon");
	settextstyle(10,0,3);
	setbkcolor(pink);
	setcolor(0);
	if (node->member.slmuon==0) {
		outtextxy(600,400,"Doc gia nay hien chua muon sach nao!");
		settextstyle(10,0,1);
		createButton(800,600,110,55," Tro lai", 15,25);
		return;
	}
	inTableSachDGMuon();
	NodeMuonTra tmp = node->member.First;
	int i = 0;
	setcolor(0);
	setbkcolor(pink);
	settextstyle(10,0,3);
	while(tmp!=NULL) {
		std::cout<<"test: "<<tmp->muontra.quahan<<"\n";
		if (tmp->muontra.TrangThai==0 && tmp->muontra.quahan>0) {
//			outtextxy(1210,360+80*i,"Dang Muon");
//			outtextxy(600,360+80*i, layTenSachtuMaSach(tmp->muontra.MaSach,l));
//			outtextxy(390,360+80*i,tmp->muontra.MaSach);
//			outtextxy(970,360+80*i,tmp->muontra.NgayMuon);
//			i++;
			setcolor(12);
			outtextxy(1210,360+80*i,"Qua Han");
			outtextxy(600,360+80*i, layTenSachtuMaSach(tmp->muontra.MaSach,l));
			setcolor(0);
			outtextxy(390,360+80*i,tmp->muontra.MaSach);
			outtextxy(970,360+80*i,tmp->muontra.NgayMuon);
			i++;
		} else if (tmp->muontra.TrangThai==0)  {
			outtextxy(1210,360+80*i,"Dang Muon");
			outtextxy(600,360+80*i, layTenSachtuMaSach(tmp->muontra.MaSach,l));
			outtextxy(390,360+80*i,tmp->muontra.MaSach);
			outtextxy(970,360+80*i,tmp->muontra.NgayMuon);
			i++;
		}
		tmp=tmp->right;
	}
}
void fixkhunghoten() {
	setbkcolor(violet);
	setcolor(0);
	setfillstyle(1,violet);
	settextstyle(10,0,2);
	bar(345,55,840,82);
	outtextxy(348,58,"Ho: ");
	bar(345,88,840,115);
	outtextxy(348,91,"Ten: ");
}
void highlightred(int x1,int y1,int x2,int y2) {
	setlinestyle(0,0,1);
	setcolor(12);
	rectangle(x1,y1,x2,y2);
	setlinestyle(0,0,1);
	setcolor(0);
}
void xoahighlightredpink(int x1,int y1,int x2,int y2) {
	setlinestyle(0,0,1);
	setcolor(pink);
	rectangle(x1,y1,x2,y2);
	setlinestyle(0,0,1);
}
void xoahighlightred(int x1,int y1,int x2,int y2) {
	setlinestyle(0,0,1);
	setcolor(0);
	rectangle(x1,y1,x2,y2);
	setlinestyle(0,0,1);
}
void showDocGia() {
	setbkcolor(violet);
	setcolor(0);
	rectangle(330,15,1385,170);
	setfillstyle(1,violet);
	settextstyle(10,0,2);

	bar(345,22,840,49);
	outtextxy(348,25,"Ma the: ");

	bar(345,55,840,82);
	outtextxy(348,58,"Ho: ");
	createID(345,55,840,82,233);

	outtextxy(850,58,"Gioi tinh: ");


	bar(345,88,840,115);
	outtextxy(348,91,"Ten: ");
	createID(345,88,840,115,234);

	outtextxy(850,91,"Trang thai: ");

	createButton3(1050,53,70,30," Nam ",textColor,231);
	createButton3(1150,53,65,30," Nu",textColor,232);

	createButton3(1020,87,125,30,"  Active ",textColor,241);
	createButton3(1180,87,130,30," Inactive",textColor,242);

	createButton3(360,128,70,30," TEN",textColor,215);
	createButton3(440,128,70,30," ID",textColor,216);
	createButton(400,630,140,55,"Trang truoc",textColor,22);
	createButton(1200,630,140,55," Trang sau",textColor,23);
	createButton3(540,128,70,30," NEW",textColor,24);
	
//	createButton3(620,128,70,30," ADD",textColor,243);
	createButton4(620,128,70,30," ADD",0,0);
	inKhungDocGia();
	setcolor(0);
	setbkcolor(pink);
	settextstyle(10,0,2);
	outtextxy(725,128,"TIM DOC GIA:");
	bartrangcovien(900,124,1200,158);
	createID(900,124,1200,158,212);
	setbkcolor(violet);
	setcolor(7);
	settextstyle(10,0,1);
	outtextxy(910,129,"Tim kiem theo ID");
	settextstyle(10,0,3);
}
void ininfoDocGiaTuCay(NodeDocGia x) {
	settextstyle(10,0,1);
	char tmp[50]="";
	setbkcolor(violet);
	setcolor(0);
	outtextxy(438,25,itoa(x->member.mathe,tmp,10));
	outtextxy(386,58,x->member.ho);
	outtextxy(399,91,x->member.ten);
}
void xoaTableDocGia() {
	setbkcolor(pink);
	setcolor(pink);
	setfillstyle(1,pink);
	bar(380,128,452,158);
	bar(470,128,542,158);
	bar(570,128,642,158);
	bar(330,180,1387,700);
	settextstyle(10,0,2);
	bar(355,126,700,160);
	createButton3(380,128,70,30," SUA",textColor,21);
	createButton3(470,128,70,30," XOA",textColor,24);
	createButton3(570,128,70,30," LUU",textColor,214);
}
void ininfoDocGiatuMang(int tt,DocGia *MangDocGia) {
	settextstyle(10,0,1);
	char tmp[50]="";
	setbkcolor(violet);
	setcolor(0);
	outtextxy(438,25,itoa(MangDocGia[tt].mathe,tmp,10));
	outtextxy(386,58,MangDocGia[tt].ho);
	outtextxy(399,91,MangDocGia[tt].ten);
}
void inKhungMuonTra() {
	settextstyle(10,0,2);
	int x1=330;
	int y1=15;
	int height = 40;
	int width[7]= {0,110,260,120,260,145,140};
	char title[][50]= {
		" Ma the",
		"     Ho Ten",
		" Ma Sach",
		"       Ten Sach",
		" Ngay Muon",
		" Qua Han",
	};
//	bar(330,15,1385,15+40*15);
	createTable(x1,y1,height,width,6,14,title);
	createButton(400,630,140,55,"Trang truoc",textColor,31);
	createButton(1200,630,140,55," Trang sau",textColor,32);
}
void showMuonTra(DocGia *MangMuonTra,int page,int qh,ListDauSach l) {
	setbkcolor(pink);
	settextstyle(10,0,1);
	char tmp[50]= "";
	setcolor(0);
	
	for (int j=0; j < 14 && page*14-14+j<qh; j++) {
		outtextxy(350,65+40*j,itoa(MangMuonTra[page*14-14+j].mathe,tmp,10));
		char ho[50] = ""; 
		strcpy(ho,strcat(MangMuonTra[page*14-14+j].ho," "));
		outtextxy(470,65+40*j,strcat(ho, MangMuonTra[page*14-14+j].ten));
		outtextxy(737,65+40*j,MangMuonTra[page*14-14+j].First->muontra.MaSach);
		outtextxy(850,65+40*j,layTenSachtuMaSach(MangMuonTra[page*14-14+j].First->muontra.MaSach,l));
		outtextxy(1110,65+40*j,MangMuonTra[page*14-14+j].First->muontra.NgayMuon);
		outtextxy(1280,65+40*j,itoa(MangMuonTra[page*14-14+j].First->muontra.quahan,tmp,10));
	}
	std::cout<<"in xong mt ";
	settextstyle(10,0,3);
}
void scannerNums(int px, int py, char s[], int limit, int ID, int &chon, int MAP[1400][700]) {
	setcolor(0);
	setbkcolor(violet);
	settextstyle(10,0,2);
	int l = strlen(s);
	s[l] ='|';
	s[l+1]='\0';
	outtextxy(px, py ,s);
	char c;
	int x1,y1;
	while(1) {
		delay(1);
		if(kbhit()) {

			c = getch();
//	std::	cout << (int) c<<std::endl;

			if(l<limit) {

				if(c>='0' && c<='9') {
					if(l==0 && c=='0') {
						l--;
					} else {
						s[l] = c;
						l++;
					}
				}
				if(c==8) {
					s[l-1]=' ';
					if(l!=0) {
						s[l-1]=' ';
						s[l]=' ';
						s[l+1]=' ';
						s[l+2]='\0';
						outtextxy(px,py,s);
						l--;
					}
					if(l==0) {

						s[l]='|';
						delay(100);
						outtextxy(px,py,s);
						s[l]=' ';
						delay(100);
						outtextxy(px,py,s);
					}
				}
				if(c==13) {
					s[l]='\0';
					break;
				}
				s[l+1]='\0';
				outtextxy(px,py,s);
			} else {
				if(c==8) {
					s[l-1]=' ';
					if(l!=0) {
						s[l-1]=' ';
						s[l]=' ';
						s[l+1]=' ';
						s[l+2]='\0';
						outtextxy(px,py,s);
						l--;
					}
					if(l==0) {

						s[l]='|';
						delay(100);
						outtextxy(px,py,s);
						s[l]=' ';
						delay(100);
						outtextxy(px,py,s);
					}
				}
				if(c==13) {
					s[l]='\0';
					break;
				}
			}

		} else {

			s[l]='|';
			delay(100);
			outtextxy(px,py,s);
			s[l]=' ';
			delay(100);
			outtextxy(px,py,s);
		}
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x1, y1);
			if (MAP[x1][y1] != ID) {
				if (s[l-1] ==32) s[l-1] = '\0';
				else s[l] = '\0';
				chon=MAP[x1][y1];
				break;
			}
		}
	}
}
void scannerString( int px, int py, char s[], int limit, int ID, int &chon, int MAP[1400][700]) {
	setcolor(0);
	setbkcolor(violet);
	settextstyle(10,0,2);
	int l = strlen(s);
	s[l] ='|';
	s[l+1]='\0';
	int x1,y1;
	outtextxy(px, py ,s);
	while(1) {
		delay(1);
		if(kbhit()) {
			char c = getch();
			//	std::	cout << (int) c<<std::endl;

			if(l<limit) {
				if((l==0)) { // viet hoa o dau cau
					if(c<='z'&&c>='a')
						c=c+'A'-'a';
					else
						c=c;
				} else if(c<='Z'&&c>='A')
					c=c-'A'+'a';

				if(c>='a' && c<='z' || c>='A' && c<='Z' ||c>='0' && c<='9' || c=='_') {
					s[l] = c;
					l++;
				}
				if(c==8) {
					s[l-1]=' ';
					if(l!=0) {
						s[l-1]=' ';
						s[l]=' ';
						s[l+1]=' ';
						s[l+2]='\0';
						outtextxy(px,py,s);
						l--;
					}
					if(l==0) {
						s[l]='|';
						delay(100);
						outtextxy(px,py,s);
						s[l]=' ';
						delay(100);
						outtextxy(px,py,s);
					}
				}
				if(c==13) {
					if(s[l-1]==' ' ) {
						l--;
						s[l]='\0';
						break;
					} else {
						s[l]='\0';
						break;
					}
				}
				if(l>0) if(s[l-1]!=' ' && c == ' ') {
						s[l] = c;
						l++;
					}

				s[l+1]='\0';
				outtextxy(px,py,s);
			} else {
				if(c==8) {
					s[l-1]=' ';
					if(l!=0) {
						s[l-1]=' ';
						s[l]=' ';
						s[l+1]=' ';
						s[l+2]='\0';
						outtextxy(px,py,s);
						l--;
					}
					if(l==0) {

						s[l]='|';
						delay(100);
						outtextxy(px,py,s);
						s[l]=' ';
						delay(100);
						outtextxy(px,py,s);
					}
				}
				if(c==13) {
					s[l]='\0';
					break;
				}
			}
		} else {
			s[l]='|';
			delay(100);
			outtextxy(px,py,s);
			s[l]=' ';
			delay(100);
			outtextxy(px,py,s);
		}
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x1, y1);
			if (MAP[x1][y1] != ID) {
				if (s[l-1] ==32) s[l-1] = '\0';
				else s[l] = '\0';
				chon=MAP[x1][y1];
				break;
			}
		}
	}
}
void showDauSach() {
	setbkcolor(violet);
	setcolor(0);
	rectangle(330,15,1385,170);
	setfillstyle(1,violet);
	settextstyle(10,0,2);

	bar(345,22,680,49);
	outtextxy(348,25,"ISBN: ");
	createID(345,22,680,49,11);

	bar(687,22,1070,49);
	outtextxy(690,25,"Ten Sach: ");
	createID(687,22,1070,49,12);

	bar(345,55,680,82);
	outtextxy(348,58,"So Trang: ");
	createID(345,55,680,82,13);

	bar(687,55,1070,82);
	outtextxy(690,58,"Tac gia: ");
	createID(687,55,1070,82,14);

	bar(345,88,680,115);
	outtextxy(348,91,"Nam Xuat Ban: ");
	createID(345,88,680,115,15);

	bar(687,88,1070,115);
	outtextxy(690,91,"The Loai: ");
	createID(687,88,1070,115,16);

	bar(1077,22,1377,49);
	outtextxy(1080,25,"So luong: ");
	createID(1077,22,1377,49,17);

	bar(1077,55,1377,82);
	outtextxy(1080,58,"Vi tri: ");
	createID(1077,55,1377,82,18);
	createButton3(380,128,70,30," ADD",textColor,19);
	createButton3(470,128,92,30," CLEAR",textColor,111);
	createButton3(600,128,50,30,"TOP",textColor,113);
	createButton3(1220,128,150,30,"IN THE LOAI",textColor,1127);
	setcolor(0);
	setbkcolor(pink);
	outtextxy(725,128,"TIM DAU SACH:");
	bartrangcovien(900,124,1200,158);
	createID(900,124,1200,158,112);
	setbkcolor(violet);
	setcolor(7);
	settextstyle(10,0,1);
	outtextxy(910,129,"Tim kiem theo ten dau sach");
	inKhungDauSach();
	settextstyle(10,0,3);
}
int top10ds(ListDauSach l, int page, int &rank) {
	int i=page*10-10, vitri = 0, updateRank=1;;
	int quantity=0;
	khungTopDS();
	setbkcolor(pink);
	setfillstyle(1,pink);
	char tmp[50]="";
	for (; i < page*10-10+10 && rank<= 10 && i<l.n-1; i++) {
		std::cout<<l.dausach[i]->ten<<"\n";
		if (l.dausach[i]->soluotmuon==0) return quantity;
		outtextxy(345,230+40*vitri,itoa(rank,tmp,10));
//		outtextxy(515,230+40*vitri,itoa(l.dausach[i]->nxb,tmp,10));
//		outtextxy(710,230+40*vitri,itoa(l.dausach[i]->soluotmuon,tmp,10));
//		outtextxy(820,230+40*vitri,l.dausach[i]->ten);
//		outtextxy(1060,230+40*vitri,l.dausach[i]->tacgia);
//		outtextxy(1220,230+40*vitri,l.dausach[i]->theloai);
		
		outtextxy(440,230+40*vitri,l.dausach[i]->ten);
		outtextxy(670,230+40*vitri,l.dausach[i]->tacgia);
		outtextxy(850,230+40*vitri,l.dausach[i]->theloai);
		outtextxy(1085,230+40*vitri,itoa(l.dausach[i]->nxb,tmp,10));
		outtextxy(1290,230+40*vitri,itoa(l.dausach[i]->soluotmuon,tmp,10));
		quantity++;
		vitri++;
		updateRank++;
		if (l.dausach[i]->soluotmuon!=l.dausach[i+1]->soluotmuon) {
//			++rank;
			rank=updateRank;
		}
		
	}
	if (i==l.n-1 && i < page*10-10+10 && rank<=10 && l.dausach[i]->soluotmuon!=0) {
		outtextxy(345,230+40*vitri,itoa(rank,tmp,10));
		outtextxy(440,230+40*vitri,l.dausach[i]->ten);
		outtextxy(670,230+40*vitri,l.dausach[i]->tacgia);
		outtextxy(850,230+40*vitri,l.dausach[i]->theloai);
		outtextxy(1085,230+40*vitri,itoa(l.dausach[i]->nxb,tmp,10));
		outtextxy(1290,230+40*vitri,itoa(l.dausach[i]->soluotmuon,tmp,10));
		quantity++;
	}
	return quantity;
//	for (int i = 0; i < 10 && i<l.n; i++) {
//		outtextxy(365,230+40*i,itoa(l.dausach[i]->nxb,tmp,10));
//		outtextxy(610,230+40*i,itoa(l.dausach[i]->soluotmuon,tmp,10));
//		outtextxy(720,230+40*i,l.dausach[i]->ten);
//		outtextxy(970,230+40*i,l.dausach[i]->tacgia);
//		outtextxy(1220,230+40*i,l.dausach[i]->theloai);
//	}
}
int resetDauSach(int pageDS, int &maxPageDS, ListDauSach l) {
	maxPageDS = l.n==10 ? 1 : l.n/10+1;
	showMenu();
	chosenMenu(20,15,290,55," DANH SACH DAU SACH",textColor,1);
	showDauSach();
	inTableDauSach(l,pageDS);
	inSoTrang(pageDS,maxPageDS);
	createTableID(330,180,40,1055,100,10);
}
void scannerCapslock(int px, int py, char s[], int limit, int ID, int &chon, int MAP[1400][700]) {
	setcolor(0);
	setbkcolor(violet);
	settextstyle(10,0,2);
	int l = strlen(s);
	int x1,y1;
	s[l] ='|';
	s[l+1]='\0';
	outtextxy(px, py ,s);
	while(1) {
		delay(1);

		if(kbhit()) {
			char c = getch();
			std::cout << (int) c<<std::endl;

			if(l<limit) {
				if(c>='a'&& c<='z' || c>='A' && c<= 'Z' ) {
					if(c>='a'&&c<='z') {
						c=c+'A'-'a';
					}
					s[l]=c;
					l++;
				}
				if(c>='0' && c<='9' || c=='_') {
					s[l] = c;
					l++;
				}
				if(c==8) {
					s[l-1]=' ';
					if(l!=0) {
						s[l-1]=' ';
						s[l]=' ';
						s[l+1]=' ';
						s[l+2]='\0';
						outtextxy(px,py,s);
						l--;
					}
					if(l==0) {
						s[l]='|';
						delay(100);
						outtextxy(px,py,s);
						s[l]=' ';
						delay(100);
						outtextxy(px,py,s);
					}
				}
				if(c==13) {
					s[l]='\0';
					break;
				}
				s[l+1]='\0';
				outtextxy(px,py,s);
			} else {
				if(c==8) {
					s[l-1]=' ';
					if(l!=0) {
						s[l-1]=' ';
						s[l]=' ';
						s[l+1]=' ';
						s[l+2]='\0';
						outtextxy(px,py,s);
						l--;
					}
					if(l==0) {
						s[l]='|';
						delay(100);
						outtextxy(px,py,s);
						s[l]=' ';
						delay(100);
						outtextxy(px,py,s);
					}
				}
				if(c==13) {
					s[l+1]='\0';
					break;
				}
			}

		} else {
			s[l]='|';
			delay(100);
			outtextxy(px,py,s);
			s[l]=' ';
			delay(100);
			outtextxy(px,py,s);
		}
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x1, y1);
			if (MAP[x1][y1] != ID) {
				if (s[l-1] ==32) s[l-1] = '\0';
				else s[l] = '\0';
				chon=MAP[x1][y1];
				break;
			}
		}
	}

}
void scannerMaSach(int px, int py, char s[], int limit, int ID, int &chon, int MAP[1400][700]) {
	setcolor(0);
	setbkcolor(violet);
	settextstyle(10,0,2);
	int l = strlen(s);
	int x1,y1;
	s[l] ='|';
	s[l+1]='\0';
	outtextxy(px, py ,s);
	while(1) {
		delay(1);

		if(kbhit()) {
			char c = getch();
			std::cout << (int) c<<std::endl;

			if(l<limit) {
				if(c>='a'&& c<='z' || c>='A' && c<= 'Z' || c>='0' && c<='9' || c=='-') {
					if(c>='a'&&c<='z') {
						c=c+'A'-'a';
					}
					s[l]=c;
					l++;
				}
				if(c==8) {
					s[l-1]=' ';
					if(l!=0) {
						s[l-1]=' ';
						s[l]=' ';
						s[l+1]=' ';
						s[l+2]='\0';
						outtextxy(px,py,s);
						l--;
					}
					if(l==0) {
						s[l]='|';
						delay(100);
						outtextxy(px,py,s);
						s[l]=' ';
						delay(100);
						outtextxy(px,py,s);
					}
				}
				if(c==13) {
					s[l]='\0';
					break;
				}
				s[l+1]='\0';
				outtextxy(px,py,s);
			} else {
				if(c==8) {
					s[l-1]=' ';
					if(l!=0) {
						s[l-1]=' ';
						s[l]=' ';
						s[l+1]=' ';
						s[l+2]='\0';
						outtextxy(px,py,s);
						l--;
					}
					if(l==0) {
						s[l]='|';
						delay(100);
						outtextxy(px,py,s);
						s[l]=' ';
						delay(100);
						outtextxy(px,py,s);
					}
				}
				if(c==13) {
					s[l+1]='\0';
					break;
				}
			}

		} else {
			s[l]='|';
			delay(100);
			outtextxy(px,py,s);
			s[l]=' ';
			delay(100);
			outtextxy(px,py,s);
		}
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x1, y1);
			if (MAP[x1][y1] != ID) {
				if (s[l-1] ==32) s[l-1] = '\0';
				else s[l] = '\0';
				chon=MAP[x1][y1];
				break;
			}
		}
	}

}
void scannerHoTen( int px, int py, char s[], int limit, int ID, int &chon, int MAP[1400][700]) {
	setcolor(0);
	setbkcolor(violet);
	settextstyle(10,0,2);
	int l = strlen(s);
	s[l] ='|';
	s[l+1]='\0';
	outtextxy(px, py ,s);
	int x1,y1;
	while(1) {
		delay(1);

		if(kbhit()) {
			char c = getch();
			std::	cout << (int) c<<std::endl;

			if(l<limit) {
				if((l==0)||s[l-1]==' ') { // viet hoa o dau cau va sau khoang trang
					if(c<='z'&&c>='a')
						c=c+'A'-'a';
					else
						c=c;
				} else if(c<='Z'&&c>='A')
					c=c-'A'+'a';

				if(c>='a' && c<='z' || c>='A' && c<='Z' ) {
					s[l] = c;
					l++;
				}
				if(c==8) {
					s[l-1]=' ';
					if(l!=0) {
						s[l-1]=' ';
						s[l]=' ';
						s[l+1]=' ';
						s[l+2]='\0';
						outtextxy(px,py,s);
						l--;
					}
					if(l==0) {

						s[l]='|';
						delay(100);
						outtextxy(px,py,s);
						s[l]=' ';
						delay(100);
						outtextxy(px,py,s);
					}
				}
				if(c==13) {
					if(s[l-1]==' ' ) {
						l--;
						s[l]='\0';
						break;
					} else {
						s[l]='\0';
						break;
					}
				}
				if(l>0) if(s[l-1]!=' ' && c == ' ') {
						s[l] = c;
						l++;
					}
				s[l+1]='\0';
				outtextxy(px,py,s);
			} else {
				if(c==8) {
					s[l-1]=' ';
					if(l!=0) {
						s[l-1]=' ';
						s[l]=' ';
						s[l+1]=' ';
						s[l+2]='\0';
						outtextxy(px,py,s);
						l--;
					}
					if(l==0) {

						s[l]='|';
						delay(100);
						outtextxy(px,py,s);
						s[l]=' ';
						delay(100);
						outtextxy(px,py,s);
					}
				}
				if(c==13) {
					s[l]='\0';
					break;
				}
			}
		}

		else {

			s[l]='|';
			delay(100);
			outtextxy(px,py,s);
			s[l]=' ';
			delay(100);
			outtextxy(px,py,s);
		}
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x1, y1);
			if (MAP[x1][y1] != ID) {
				if (s[l-1] ==32) s[l-1] = '\0';
				else s[l] = '\0';
				chon=MAP[x1][y1];
				break;
			}
		}
	}

}

void clearDauSach(char ISBN[], int &sotrang, int &nxb, char ten[], char tacgia[], char theloai[],int &soluong,char vitri[]) {
	setbkcolor(violet);
	setcolor(0);
	rectangle(330,15,1385,170);
	setfillstyle(1,violet);
	settextstyle(10,0,2);
	bar(345,22,680,49);
	outtextxy(348,25,"ISBN: ");
	bar(687,22,1070,49);
	outtextxy(690,25,"Ten Sach: ");
	bar(345,55,680,82);
	outtextxy(348,58,"So Trang: ");
	bar(687,55,1070,82);
	outtextxy(690,58,"Tac gia: ");
	bar(345,88,680,115);
	outtextxy(348,91,"Nam Xuat Ban: ");
	bar(687,88,1070,115);
	outtextxy(690,91,"The Loai: ");
	bar(1077,22,1377,49);
	outtextxy(1080,25,"So luong: ");
	bar(1077,55,1377,82);
	outtextxy(1080,58,"Vi tri: ");
	strcpy(ISBN,"");
	sotrang=0;
	nxb=0;
	strcpy(ten,"");
	strcpy(tacgia,"");
	strcpy(theloai,"");
	soluong=0;
	strcpy(vitri,"");
}
void tabDauSach(int x, int y) {
	setcolor(0);
	setfillstyle(1,blue);
	settextstyle(10,0,1);
	if (x+300>=1400 && y>=500) {
		createButton3(x-200,y-80,175,30," Hieu chinh DS",0,116);
		createButton3(x-200,y-110,175,30," Hien thi DMS",0,117);
		createButton3(x-200,y-140,175,30," Xoa Dau Sach",0,118);
		rectangle(x-200,y-80,x-25,y-50);
		rectangle(x-200,y-110,x-25,y-80);
		rectangle(x-200,y-140,x-25,y-110);
	}
	else if (x+300>=1400) {
		createButton3(x-200,y,175,30," Hieu chinh DS",0,116);
		createButton3(x-200,y+30,175,30," Hien thi DMS",0,117);
		createButton3(x-200,y+60,175,30," Xoa Dau Sach",0,118);
		rectangle(x-200,y,x-25,y+30);
		rectangle(x-200,y+30,x-25,y+60);
		rectangle(x-200,y+60,x-25,y+90);
	}
	else if (y >= 500) {
		createButton3(x,y-80,175,30," Hieu chinh DS",0,116);
		createButton3(x,y-110,175,30," Hien thi DMS",0,117);
		createButton3(x,y-140,175,30," Xoa Dau Sach",0,118);
		rectangle(x,y-80,x+175,y-50);
		rectangle(x,y-110,x,y-80);
		rectangle(x,y-140,x+175,y-110);
	}
	else {
		createButton3(x,y,175,30," Hieu chinh DS",0,116);
		createButton3(x,y+30,175,30," Hien thi DMS",0,117);
		createButton3(x,y+60,175,30," Xoa Dau Sach",0,118);
		rectangle(x,y,x+175,y+30);
		rectangle(x,y+30,x,y+60);
		rectangle(x,y+60,x+175,y+90);
	}
	
//	createButton3(x,y,175,30," Hieu chinh DS",0,116);
//	createButton3(x,y+30,175,30," Hien thi DMS",0,117);
//	createButton3(x,y+60,175,30," Xoa Dau Sach",0,118);
//	rectangle(x,y,x+175,y+30);
//	rectangle(x,y+30,x+175,y+60);
//	rectangle(x,y+60,x+175,y+90);
}
void showHieuChinhDS() {
	rectangle(600,200,1075,600);
	setfillstyle(1,red);
	bar(600,200,1075,650);
	rectangle(600,200,1075,650);
	settextstyle(10,0,3);
	setbkcolor(red);
	outtextxy(725,220,"Hieu chinh dau sach");
	setbkcolor(violet);
	setfillstyle(1,violet);
	settextstyle(10,0,2);
	bar(690,275,1000,298);
	setcolor(9);
	outtextxy(700,275,"ISBN:");
	createID(690,275,1000,298,1161);
	
	bar(690,325,1000,348);
	outtextxy(700,325,"Ten:");
	createID(690,325,1000,348,1162);
	
	bar(690,375,1000,398);
	outtextxy(700,375,"Tac gia:");
	createID(690,375,1000,398,1163);
	
	bar(690,425,1000,448);
	outtextxy(700,425,"The loai:");
	createID(690,425,1000,448,1164);
	
	bar(690,475,1000,498);
	outtextxy(700,475,"NXB:");
	createID(690,475,1000,498,1165);
	
	bar(690,525,1000,548);
	outtextxy(700,525,"So trang:");
	createID(690,525,1000,548,1166);
	
	createButton5(720,575,100,35," SAVE",0,1167);
	createButton4(875,575,100,35," CLOSE",0,1168);
}
bool yesnoBox(char text[], int MAP[][700]) {
	setfillstyle(1,blue);
	settextstyle(10,0,1);
	bar(50,320,275,410);
	setbkcolor(blue);
	setcolor(0);
	outtextxy(55,350,text);
	createButton2(65,430,50,50,"YES",15,01);
	createButton(210,430,50,50,"NO",15,02);
	while(1) {
		int x = -1;
		int y = -1;
		delay(1);
		if(ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN,x,y);
			if (x!=-1 && y!=-1) {
				switch(MAP[x][y]) {
					case 01: {
						barhongcovien(20,230,310,520);
						settextstyle(10,0,3);
						setcolor(red);
						setbkcolor(pink);
						outtextxy(90,240," THONG BAO");
						setcolor(0);
						return true;
						break;
					}
					case 02: {
						barhongcovien(20,230,310,520);
						settextstyle(10,0,3);
						setcolor(red);
						setbkcolor(pink);
						outtextxy(90,240," THONG BAO");
						setcolor(0);
						return false;
						break;
					}
				}
			}
		}
	}
}
