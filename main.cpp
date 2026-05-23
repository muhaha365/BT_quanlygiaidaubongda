#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

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
        cin.ignore();
        cout << "Ten cau thu: ";
        getline(cin, tenCT);
        cout << "Vi tri: ";
        getline(cin, ViTri);
        cout << "So ao: ";
        cin >> soao;
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
    void ThemCauThu(CauThu ct)
    {
        dsCT.push_back(ct);
    }
    void Nhap()
    {
        cin.ignore();
        cout << "Ten doi: ";
        getline(cin, tendoi);
        cout << "Ten HVL: ";
        getline(cin, tenHLV);
        int n;
        cout << "So luong cau thu: ";
        cin >> n;
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
    int getHieuSo()
    {
        return banThang - banThua;
    }
    int gettong_diem() const
    {
        return tong_diem;
    }
    int getbanThang() const
    {
        return banThang;
    }
    string gettenDoi() const
    {
        return tendoi;
    }
    void Xuat() 
    {
        cout << "Doi: " << tendoi << " | Diem: " << tong_diem 
             << " | Tran: " << sotran << " | T-H-B: " << thang << "-" << hoa << "-" << thua 
             << " | BT-BB: " << banThang << "-" << banThua 
             << " | Hieu so: " << getHieuSo() << endl;
        for(int i = 0; i < dsCT.size(); i++)
        {
            dsCT[i].Xuat(); cout << endl;
        }
    }
};

class TranDau
{
private:
}; 

int main()
{
    DoiBong a;
    a.Nhap();
    a.Xuat();
}