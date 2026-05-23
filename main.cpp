#include <iostream>
#include <vector>
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
    }
};