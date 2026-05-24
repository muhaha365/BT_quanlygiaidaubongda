#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class DoiBong; 

class CauThu
{
private:
    string tenCT, ViTri;
    int soao;
public:
    CauThu(string ten = "", string vitri = "", int so = 0): tenCT(ten), ViTri(vitri), soao(so) {}
    void Xuat()
    {
        cout << "Ten cau thu: " << tenCT << " | " << ViTri << " | " << soao;
    }
    void Nhap()
    {
        cout << "Ten cau thu: ";
        getline(cin, tenCT);
        cout << "Vi tri: ";
        getline(cin, ViTri);
        cout << "So ao: ";
        cin >> soao;
        cin.ignore();
    }
};

class DoiBong
{
private:
    string tendoi;
    string tenHLV;
    vector <CauThu> dsCT;
    int tong_diem, sotran, thang, hoa, thua, banThang, banThua;
public:
    DoiBong(string ten = "", string hlv =""): tendoi(ten), tenHLV(hlv)
    {
        tong_diem = sotran = thang = hoa = thua = banThang = banThua = 0;
    }
    void Nhap()
    {
        cout << "Ten doi: ";
        getline(cin, tendoi);
        cout << "Ten HVL: ";
        getline(cin, tenHLV);
        int n;
        cout << "So luong cau thu: ";
        cin >> n;
        cin.ignore();
        dsCT.resize(n);
        for(int i = 0; i < dsCT.size(); i++)
        {
            dsCT[i].Nhap();
        }
    }
    void CapNhat(int sobanthang, int sobanthua)
    {
        sotran++;
        banThang += sobanthang;
        banThua += sobanthua;
        if(sobanthang > sobanthua)
        {
            thang++;
            tong_diem += 3;
        }
        else if(sobanthang == sobanthua)
        {
            hoa++;
            tong_diem += 1;
        }
        else
        {
            thua++;
        }
    }
    int getHieuSo() const { return banThang - banThua; }
    int gettong_diem() const { return tong_diem; }
    int getbanThang() const { return banThang; }
    string gettenDoi() const { return tendoi; }
    void Xuat() 
    {
        cout << "Doi: " << tendoi << " | Diem: " << tong_diem 
             << " | Tran: " << sotran << " | T-H-B: " << thang << "-" << hoa << "-" << thua 
             << " | BT-BB: " << banThang << "-" << banThua 
             << " | Hieu so: " << getHieuSo() << endl;
        for(int i = 0; i < dsCT.size(); i++)
        {
            cout << "  "; 
            dsCT[i].Xuat(); cout << endl;
        }
    }
};

bool SoSanhDoi(DoiBong *a, DoiBong *b)
{
    if(a->gettong_diem() != b->gettong_diem()) {
        return a->gettong_diem() > b->gettong_diem();
    }
    if(a->getHieuSo() != b->getHieuSo()) {
        return a->getHieuSo() > b->getHieuSo();
    }
    return a->getbanThang() > b->getbanThang();
}

class TranDau
{
protected:
    DoiBong* a;
    DoiBong* b;
public:
    TranDau(DoiBong* doiA, DoiBong* doiB): a(doiA), b(doiB){}
    virtual DoiBong* ThiDau(int banA, int banB, int penA = 0, int penB = 0) = 0;
}; 

class VongBang : public TranDau
{
public:
    VongBang(DoiBong* doiA, DoiBong* doiB): TranDau(doiA, doiB) {}
    DoiBong* ThiDau(int banA, int banB, int penA = 0, int penB = 0) override
    {
        a->CapNhat(banA, banB);
        b->CapNhat(banB, banA);
        if (banA > banB) return a;
        if (banB > banA) return b;
        return nullptr;
    }
};

class VongKnockout : public TranDau
{
public:
    VongKnockout(DoiBong* doiA, DoiBong* doiB): TranDau(doiA, doiB) {}
    DoiBong* ThiDau(int banA, int banB, int penA = 0, int penB = 0) override
    {
        if(banA > banB) return a;
        if(banB > banA) return b;
        if(banA == banB)
        {
            if(penA > penB) return a;
            else return b;
        }
        return nullptr;
    }
};

class GiaiDau
{
private:
    vector <DoiBong*> dsDoi;

    // --- HÀM MỚI BỔ SUNG: Chạy 1 trận Knockout nhập từ bàn phím ---
    DoiBong* ToChuc1TranKnockout(DoiBong* d1, DoiBong* d2, string tenVong) {
        cout << "\n>>> " << tenVong << ": " << d1->gettenDoi() << " vs " << d2->gettenDoi() << " <<<\n";
        int ban1, ban2, pen1 = 0, pen2 = 0;
        
        cout << "Ty so cua " << d1->gettenDoi() << ": "; cin >> ban1;
        cout << "Ty so cua " << d2->gettenDoi() << ": "; cin >> ban2;
        
        if (ban1 == ban2) {
            cout << "=> KET QUA HOA! 2 doi da Penalty:\n";
            do {
                cout << "  + Pen " << d1->gettenDoi() << ": "; cin >> pen1;
                cout << "  + Pen " << d2->gettenDoi() << ": "; cin >> pen2;
                if(pen1 == pen2) cout << "  [!] Penalty khong duoc hoa!\n";
            } while (pen1 == pen2);
        }
        
        VongKnockout tran(d1, d2);
        DoiBong* thang = tran.ThiDau(ban1, ban2, pen1, pen2);
        cout << "=> DOI DI TIEP: " << thang->gettenDoi() << "\n";
        return thang;
    }

public:
    void ThemDoiBong(DoiBong* doimoi)
    {
        dsDoi.push_back(doimoi);
    }
    void XemDanhSachDoi()
    {
        cout << "\n============= DANH SACH DOI BONG =============\n";
        for(int i = 0; i < dsDoi.size(); i++)
        {
            dsDoi[i]->Xuat();
        }
    }
    void TaoLichThiDau()
    {
        if(dsDoi.size() < 2) {
            cout << "Khong du doi de thi dau!\n"; return;
        }
        cout << "\n============== LICH THI DAU VONG BANG ==============\n";
        for(int i = 0; i < dsDoi.size() - 1; i++)
        {
            for(int j = i + 1; j < dsDoi.size(); j++)
            {
                cout << "\n--- Tran: " << dsDoi[i]->gettenDoi() << " vs " << dsDoi[j]->gettenDoi() << " ---\n";
                int banA, banB;
                cout << "Nhap ban thang cua " << dsDoi[i]->gettenDoi() << ": "; cin >> banA;
                cout << "Nhap ban thang cua " << dsDoi[j]->gettenDoi() << ": "; cin >> banB;
                
                VongBang tran(dsDoi[i], dsDoi[j]);
                tran.ThiDau(banA, banB);
            }
        }
        cout << "\n[!] Da hoan tat vong bang!\n";
    }
    
    void SapXep()
    {
        sort(dsDoi.begin(), dsDoi.end(), SoSanhDoi);
    }
    
    void InBangXepHang()
    {
        SapXep();
        cout << "\n================= BANG XEP HANG =================\n";
        cout << "Doi bong\t| Diem\t| Hieu So | Ban Thang\n";
        cout << "-------------------------------------------------\n";    
        
        for(int i = 0; i < dsDoi.size(); i++)
        {
            cout << dsDoi[i]->gettenDoi() << "\t| "
                 << dsDoi[i]->gettong_diem() << "\t| " 
                 << dsDoi[i]->getHieuSo() << "\t  | " 
                 << dsDoi[i]->getbanThang() << "\n";
        }
        cout << "=================================================\n";
    }

    vector <DoiBong*> Laycacdoiditiep(int soluong)
    {
        SapXep();
        vector <DoiBong*> dsDiTiep;
        for(int i = 0; i < soluong && i < dsDoi.size(); i++)
        {
            dsDiTiep.push_back(dsDoi[i]);
        }
        return dsDiTiep;
    }

    // --- HÀM MỚI BỔ SUNG: Quản lý Vòng Knockout ---
    void DaVongKnockout() {
        if (dsDoi.size() < 2) {
            cout << "\n[!] Khong du doi de da Knockout!\n"; return;
        }

        int soDoi = dsDoi.size();
        vector<DoiBong*> dsHienTai;
        vector<DoiBong*> vaoBanKet, vaoChungKet;

        // Tứ kết (nếu có từ 8 đội trở lên)
        if (soDoi >= 8) {
            dsHienTai = Laycacdoiditiep(8);
            cout << "\n================= VONG TU KET (TOP 8) =================\n";
            vaoBanKet.push_back(ToChuc1TranKnockout(dsHienTai[0], dsHienTai[7], "Tu ket 1"));
            vaoBanKet.push_back(ToChuc1TranKnockout(dsHienTai[1], dsHienTai[6], "Tu ket 2"));
            vaoBanKet.push_back(ToChuc1TranKnockout(dsHienTai[2], dsHienTai[5], "Tu ket 3"));
            vaoBanKet.push_back(ToChuc1TranKnockout(dsHienTai[3], dsHienTai[4], "Tu ket 4"));
            dsHienTai = vaoBanKet;
        } 
        // Bán kết (nếu có 4 - 7 đội, hoặc được kế thừa từ Tứ Kết)
        else if (soDoi >= 4) {
            dsHienTai = Laycacdoiditiep(4);
        } 
        // Chung kết trực tiếp (nếu chỉ có 2 - 3 đội)
        else {
            dsHienTai = Laycacdoiditiep(2);
        }

        // Nếu dsHienTai có 4 đội (do đã đá Tứ Kết hoặc do lấy Top 4) -> Đá Bán kết
        if (dsHienTai.size() == 4) {
            cout << "\n================= VONG BAN KET =================\n";
            vaoChungKet.push_back(ToChuc1TranKnockout(dsHienTai[0], dsHienTai[3], "Ban ket 1"));
            vaoChungKet.push_back(ToChuc1TranKnockout(dsHienTai[1], dsHienTai[2], "Ban ket 2"));
            dsHienTai = vaoChungKet;
        }

        // Đá Chung Kết
        cout << "\n================= VONG CHUNG KET =================\n";
        DoiBong* voDich = ToChuc1TranKnockout(dsHienTai[0], dsHienTai[1], "CHUNG KET");

        cout << "\n********************************************************\n";
        cout << " CHUC MUNG NHA VO DICH: " << voDich->gettenDoi() << " !!!";
        cout << "\n********************************************************\n";
    }
};

int main()
{
    GiaiDau a;
    int soLuongDoi;
    cout << "========================================\n";
    cout << "   CHAO MUNG DEN VOI GIAI DAU BONG DA\n";
    cout << "========================================\n";
    cout << "Nhap so luong doi bong tham gia: ";
    cin >> soLuongDoi;
    cin.ignore(); 

    for(int i = 0; i < soLuongDoi; i++)
    {
        cout << "\n--- NHAP THONG TIN DOI BONG THU " << i + 1 << " ---\n";
        DoiBong* doimoi = new DoiBong();
        doimoi->Nhap();
        a.ThemDoiBong(doimoi);
    }
    
    cout << "\n[!] Da hoan tat viec thiet lap Giai Dau. Bat dau chuyen den Menu quan ly.\n";
    
    int luachon;
    do 
    {
        cout << "\n============== MENU QUAN LY ==============\n";
        cout << "1. Xem danh sach cac doi va cau thu\n";
        cout << "2. Nhap ket qua cac tran dau (Vong Bang)\n";
        cout << "3. Xem Bang xep hang hien tai\n";
        cout << "4. Da Vong Knockout (Tu ket, Ban ket, Chung ket)\n";
        cout << "0. Ket thuc giai dau\n";
        cout << "==========================================\n";
        cout << "Moi ban chon chuc nang (0-4): ";
        cin >> luachon;

        switch (luachon)
        {
        case 1:
            a.XemDanhSachDoi();
            break;
        case 2:
            a.TaoLichThiDau();
            break;
        case 3:
            a.InBangXepHang();
            break;
        case 4:
            a.DaVongKnockout(); // Gọi hàm Knockout mới thêm
            break;
        case 0:
            cout << "Thoat chuong trinh...\n";
            break;
        default:
            cout << "\nLua chon khong hop le. Vui long chon lai!\n";
            break;
        }
    } while (luachon != 0); 

    return 0;
}