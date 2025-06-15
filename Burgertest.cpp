#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include <limits>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <array>
using namespace std;
// === CÁC HÀM TIỆN ÍCH VẼ BẢNG ===
// Hàm vẽ đường viền trên, giữa và dưới của bảng.
void VeDuongBienBang(const vector<int> &widths)
{
    cout << "  +";
    for (int w : widths)
    {
        cout << string(w, '-') << "+";
    }
    cout << endl;
}
// Hàm vẽ một hàng của bảng, với dữ liệu được căn chỉnh.
void VeHangBang(const vector<string> &cells, const vector<int> &widths)
{
    cout << "  |";
    for (size_t i = 0; i < cells.size(); ++i)
    {
        string padded_cell = " " + cells[i];
        cout << left << setw(widths[i]) << padded_cell << "|";
    }
    cout << endl;
}
// Hàm vẽ một dòng phân cách có chữ ở giữa.
void VeHangPhanCach(string text, const vector<int> &widths)
{
    cout << "  |";
    int total_width = accumulate(widths.begin(), widths.end(), 0) + widths.size() - 1;
    string text_to_insert = " " + text + " ";
    int padding_total = total_width - text_to_insert.length();
    int padding_left = padding_total / 2;
    int padding_right = padding_total - padding_left;
    // In ra dòng hoàn chỉnh
    cout << string(padding_left, '-') << text_to_insert << string(padding_right, '-') << "|" << endl;
}
// CÁC HÀM VÀ LỚP CỦA CHƯƠNG TRÌNH
// Template function để lấy và kiểm tra tính hợp lệ của dữ liệu nhập từ người dùng.
template <typename T>
T GetInputValidated(const string &prompt, const string &errorMessage = "  Loi: Du lieu nhap khong hop le. Vui long thu lai.")
{
    T value;
    while (true)
    {
        cout << prompt;
        cin >> value;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << errorMessage << endl;
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}
// Vẽ một đường kẻ ngang với chiều dài và ký tự cho trước.
void VeDuongNgang(int chieuDai, char kyTu = '-')
{
    for (int i = 0; i < chieuDai; ++i)
    {
        cout << kyTu;
    }
    cout << endl;
}
// Chuyển đổi một chuỗi thành chữ hoa.
string StringToUpper(string s)
{
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}
// Đại diện cho một lựa chọn đổi điểm thưởng trong chương trình khách hàng thân thiết.
struct LuaChonDoiDiem
{
    int Id;
    int DiemCanDoi;
    string MoTaPhanThuong;
    string LoaiPhanThuong;
    double GiaTri;
    LuaChonDoiDiem() : Id(0), DiemCanDoi(0), MoTaPhanThuong(""), LoaiPhanThuong(""), GiaTri(0) {}
    LuaChonDoiDiem(int _id, int Diem, string MoTa, string _loai, double GiaTri = 0)
        : Id(_id), DiemCanDoi(Diem), MoTaPhanThuong(MoTa), LoaiPhanThuong(_loai), GiaTri(GiaTri) {}
    void HienThi() const
    {
        cout << "  ID: " << Id << " | Diem: " << DiemCanDoi << " | Phan thuong: " << MoTaPhanThuong;
        if (LoaiPhanThuong == "GiamGiaTheoPhanTram")
        {
            cout << " (Giam " << fixed << setprecision(0) << GiaTri * 100 << "%)";
        }
        cout << endl;
    }
};
// Lớp cơ sở cho các món ăn trong menu, bao gồm cả burger và Drink.
class MenuItem
{
private:
    string Ten;
    string MoTa;
    int SoLuong;
    double Gia;

protected:
    string TenGoc;

public:
    MenuItem(string TenGoc, string MoTa, int SoLuong, double Gia)
        : TenGoc(TenGoc), MoTa(MoTa), SoLuong(SoLuong), Gia(Gia) {}
    virtual ~MenuItem() {}
    virtual void CapNhatTenDayDu() = 0;
    string GetTen() const { return Ten; }
    string GetMoTa() const { return MoTa; }
    int GetSoLuong() const { return SoLuong; }
    double GetGia() const { return Gia; }
    string GetTenGocMenuItem() const { return TenGoc; }
    void SetTenDayDu(const string &newTen) { Ten = newTen; }
    void SetTenGocMenuItem(const string &newTenGoc)
    {
        TenGoc = newTenGoc;
        CapNhatTenDayDu();
    }
    void SetMoTa(const string &newMoTa) { MoTa = newMoTa; }
    void SetSoLuong(int newSoLuong) { SoLuong = newSoLuong; }
    void SetGia(double newGia) { Gia = newGia; }
    // Hàm này sẽ trả về loại món ăn, ví dụ: "Burger" hoặc "Drink".
    virtual string GetType() const = 0;
    // Hàm này sẽ hiển thị thông tin cơ bản của món ăn.
    virtual void HienThiThongTin() const
    {
        cout << "  Ten: " << Ten << endl;
        if (!MoTa.empty())
        {
            cout << "  Mo ta: " << MoTa << endl;
        }
        cout << "  So luong: " << SoLuong << endl;
        cout << "  Gia: " << fixed << setprecision(0) << Gia << " VND" << endl;
    }
    // Hàm này sẽ lưu thông tin cơ bản của món ăn vào file.
    virtual void LuuThongTinCoBanVaoFile(ofstream &ofs) const
    {
        ofs << TenGoc << endl;
        ofs << MoTa << endl;
        ofs << SoLuong << endl;
        ofs << Gia << endl;
    }
};
// Lớp đại diện cho Burger.
class Burger : public MenuItem
{
private:
    string LoaiThit;

public:
    Burger(string TenGocBurger, string MoTaBurger, int SoLuong, double Gia, string _LoaiThit)
        : MenuItem(TenGocBurger, MoTaBurger, SoLuong, Gia), LoaiThit(_LoaiThit)
    {
        CapNhatTenDayDu();
    }
    // Hàm này sẽ cập nhật tên đầy đủ của món burger dựa trên tên gốc.
    void CapNhatTenDayDu() override
    {
        SetTenDayDu("Burger - " + GetTenGocMenuItem());
    }
    string GetLoaiThit() const { return LoaiThit; }
    void SetLoaiThit(const string &newLoaiThit) { LoaiThit = newLoaiThit; }
    string GetType() const override { return "Burger"; }
    // Hàm này sẽ hiển thị thông tin chi tiết của món burger.
    void HienThiThongTin() const override
    {
        MenuItem::HienThiThongTin();
        cout << "  Loai thit: " << LoaiThit << endl;
    }
    // Hàm này sẽ lưu thông tin cơ bản của món burger vào file.
    void LuuVaoFile(ofstream &ofs) const
    {
        MenuItem::LuuThongTinCoBanVaoFile(ofs);
        ofs << LoaiThit << endl;
    }
};
// Lớp đại diện cho nước uống.
class Drink : public MenuItem
{
private:
    string KichThuoc;

public:
    Drink(string TenGocNuocUong, int SoLuong, double Gia, string KichThuoc)
        : MenuItem(TenGocNuocUong, "", SoLuong, Gia), KichThuoc(KichThuoc)
    {
        CapNhatTenDayDu();
    }
    // Hàm này sẽ cập nhật tên đầy đủ của nước uống dựa trên tên gốc và kích thước.
    void CapNhatTenDayDu() override
    {
        SetTenDayDu("Nuoc uong - " + GetTenGocMenuItem() + " (" + KichThuoc + ")");
    }
    string GetKichThuoc() const { return KichThuoc; }
    void SetKichThuoc(const string &newKichThuoc)
    {
        KichThuoc = newKichThuoc;
        CapNhatTenDayDu();
    }
    string GetType() const override { return "Drink"; }
    // Hàm này sẽ hiển thị thông tin chi tiết của nước uống.
    void HienThiThongTin() const override
    {
        MenuItem::HienThiThongTin();
        cout << "  Kich thuoc: " << KichThuoc << endl;
    }
    // Hàm này sẽ lưu thông tin cơ bản của nước uống vào file.
    void LuuVaoFile(ofstream &ofs) const
    {
        MenuItem::LuuThongTinCoBanVaoFile(ofs);
        ofs << KichThuoc << endl;
    }
};
// Lớp đại diện cho thông tin Khách hàng.
class KhachHang
{
private:
    string Username;
    string Password;
    string Ten;
    string SoDienThoai;
    string DiaChi;
    bool DaMuaLanDau;
    int DiemTichLuy;

public:
    KhachHang(string Username, string Password, string Ten, string sdt, string dc, bool DaMua = false, int Diem = 0)
        : Username(Username), Password(Password), Ten(Ten), SoDienThoai(sdt), DiaChi(dc),
          DaMuaLanDau(DaMua), DiemTichLuy(Diem) {}
    KhachHang(string Ten, string sdt, string dc)
        : Username(""), Password(""), Ten(Ten), SoDienThoai(sdt), DiaChi(dc),
          DaMuaLanDau(true), DiemTichLuy(0) {}
    string GetUsername() const { return Username; }
    string GetPassword() const { return Password; }
    string GetTen() const { return Ten; }
    string GetSoDienThoai() const { return SoDienThoai; }
    string GetDiaChi() const { return DiaChi; }
    bool GetDaMuaLanDau() const { return DaMuaLanDau; }
    int GetDiemTichLuy() const { return DiemTichLuy; }
    void SetPassword(const string &newPass) { Password = newPass; }
    void SetTen(const string &newTen) { Ten = newTen; }
    void SetSoDienThoai(const string &newSdt) { SoDienThoai = newSdt; }
    void SetDiaChi(const string &newDc) { DiaChi = newDc; }
    void SetDaMuaLanDau(bool mua) { DaMuaLanDau = mua; }
    // Thêm điểm tích lũy cho khách hàng.
    void ThemDiem(int diem)
    {
        if (diem > 0)
        {
            DiemTichLuy += diem;
        }
    }
    // Giảm điểm tích lũy của khách hàng nếu đổi điểm
    bool SuDungDiem(int DiemCanDung)
    {
        if (DiemCanDung > 0 && DiemTichLuy >= DiemCanDung)
        {
            DiemTichLuy -= DiemCanDung;
            return true;
        }
        return false;
    }
    // Hàm này sẽ hiển thị thông tin khách hàng
    void HienThiThongTin(bool LaAdminXem = false) const
    {
        if (LaAdminXem && !Username.empty())
        {
            cout << "  Username: " << Username << endl;
        }
        cout << "  Ten thanh vien: " << Ten << endl;
        cout << "  So dien thoai: " << SoDienThoai << endl;
        cout << "  Dia chi: " << DiaChi << endl;
        cout << "  Diem tich luy: " << DiemTichLuy << " diem" << endl;
        if (!Username.empty())
        {
            cout << "  Trang thai mua lan dau (thanh vien): " << (DaMuaLanDau ? "Da ap dung" : "Chua ap dung") << endl;
        }
    }
    // Hàm này sẽ lưu thông tin khách hàng vào file.
    void LuuVaoFile(ofstream &ofs) const
    {
        ofs << Username << endl;
        ofs << Password << endl;
        ofs << Ten << endl;
        ofs << SoDienThoai << endl;
        ofs << DiaChi << endl;
        ofs << DaMuaLanDau << endl;
        ofs << DiemTichLuy << endl;
    }
};
// Lớp đại diện cho thông tin Nhân viên.
class NhanVien
{
private:
    int MaNV;
    string TenNV;
    string SoDienThoaiNV;
    string DiaChiNV;

public:
    NhanVien(int ma, string Ten, string sdt, string dc)
        : MaNV(ma), TenNV(Ten), SoDienThoaiNV(sdt), DiaChiNV(dc) {}
    int GetMaNV() const { return MaNV; }
    string GetTenNV() const { return TenNV; }
    string GetSoDienThoaiNV() const { return SoDienThoaiNV; }
    string GetDiaChiNV() const { return DiaChiNV; }
    void SetTenNV(const string &Ten) { TenNV = Ten; }
    void SetSoDienThoaiNV(const string &sdt) { SoDienThoaiNV = sdt; }
    void SetDiaChiNV(const string &dc) { DiaChiNV = dc; }
    // Hàm này sẽ hiển thị thông tin nhân viên.
    void HienThiThongTin() const
    {
        cout << "  Ma nhan vien: " << MaNV << endl;
        cout << "  Ten nhan vien: " << TenNV << endl;
        cout << "  So dien thoai: " << SoDienThoaiNV << endl;
        cout << "  Dia chi: " << DiaChiNV << endl;
    }
    // Hàm này sẽ lưu thông tin nhân viên vào file.
    void LuuVaoFile(ofstream &ofs) const
    {
        ofs << MaNV << endl;
        ofs << TenNV << endl;
        ofs << SoDienThoaiNV << endl;
        ofs << DiaChiNV << endl;
    }
};
// Lớp đại diện cho Đơn hàng.
class DonHang
{
private:
    int MaDonHang;
    KhachHang KhachHangDat;
    vector<pair<MenuItem *, int>> DanhSachMonAn;
    double TongTienGoc;
    double TongTienThucTe;
    vector<string> QuaTangDaDoi;

public:
    DonHang(int MaDonHang, const KhachHang &KhachHangDat)
        : MaDonHang(MaDonHang), KhachHangDat(KhachHangDat), TongTienGoc(0), TongTienThucTe(0) {}
    DonHang(int MaDonHang, const KhachHang &KhachHangDat, double TongTienGoc, double ThucTe)
        : MaDonHang(MaDonHang), KhachHangDat(KhachHangDat), TongTienGoc(TongTienGoc), TongTienThucTe(ThucTe) {}
    int GetMaDonHang() const { return MaDonHang; }
    const KhachHang &GetKhachHangDat() const { return KhachHangDat; }
    const vector<pair<MenuItem *, int>> &GetDanhSachMonAn() const { return DanhSachMonAn; }
    double GetTongTienGoc() const { return TongTienGoc; }
    double GetTongTienThucTe() const { return TongTienThucTe; }
    const vector<string> &GetQuaTangDaDoi() const { return QuaTangDaDoi; }
    // Thêm món ăn vào danh sách đơn hàng.
    void ThemMonAn(MenuItem *mon, int SoLuong)
    {
        DanhSachMonAn.push_back({mon, SoLuong});
        TinhLaiTongTienGoc();
    }
    // Tính lại tổng tiền gốc của đơn hàng dựa trên danh sách món ăn.
    void TinhLaiTongTienGoc()
    {
        TongTienGoc = 0;
        for (const auto &item : DanhSachMonAn)
        {
            if (item.first)
                TongTienGoc += item.first->GetGia() * item.second;
        }
    }
    // Tổng tiền thực tế có thể được cập nhật nếu có giảm giá hoặc đổi điểm.
    void SetTongTienThucTe(double amount)
    {
        TongTienThucTe = amount;
    }
    // Thêm quà tặng đã đổi vào danh sách.
    void ThemQuaTangDaDoi(const string &TenQua)
    {
        QuaTangDaDoi.push_back(TenQua);
    }
    // Hàm này sẽ hiển thị thông tin đơn hàng, bao gồm thông tin khách hàng, danh sách món ăn, quà tặng đã đổi và tổng tiền.
    void HienThiThongTin() const
    {
        cout << "\n  --- Don hang #" << MaDonHang << " ---" << endl;
        cout << "  --- Thong tin khach dat hang ---" << endl;
        cout << "  Ten khach hang: " << KhachHangDat.GetTen() << endl;
        cout << "  So dien thoai: " << KhachHangDat.GetSoDienThoai() << endl;
        cout << "  Dia chi: " << KhachHangDat.GetDiaChi() << endl;
        cout << "  --- Mon an da dat ---" << endl;
        if (DanhSachMonAn.empty() && QuaTangDaDoi.empty())
        {
            cout << "  (Khong co mon an nao)" << endl;
        }
        else
        {
            for (const auto &item : DanhSachMonAn)
            {
                if (item.first)
                {
                    cout << "  - " << item.first->GetTen() << " (x" << item.second << ") - "
                         << fixed << setprecision(0) << item.first->GetGia() * item.second << " VND" << endl;
                }
                else
                {
                    cout << "  - [Mon an khong xac dinh] (x" << item.second << ")" << endl;
                }
            }
        }
        if (!QuaTangDaDoi.empty())
        {
            cout << "  --- Qua tang da doi ---" << endl;
            for (const string &qua : QuaTangDaDoi)
            {
                cout << "  - " << qua << endl;
            }
        }
        cout << "  -----------------------------------" << endl;
        cout << "  Tong tien goc: " << fixed << setprecision(0) << TongTienGoc << " VND" << endl;
        if (TongTienThucTe != TongTienGoc && TongTienThucTe != 0)
        {
            cout << "  Tong tien thanh toan: " << fixed << setprecision(0) << TongTienThucTe << " VND" << endl;
        }
        else if (TongTienGoc > 0 && TongTienThucTe == 0 && TongTienGoc != TongTienThucTe)
        {
            cout << "  Tong tien thanh toan: " << fixed << setprecision(0) << TongTienGoc << " VND (Chua bao gom Giam Gia/diem)" << endl;
        }
        else if (TongTienGoc == TongTienThucTe && TongTienGoc != 0)
        {
            cout << "  Tong tien thanh toan: " << fixed << setprecision(0) << TongTienThucTe << " VND" << endl;
        }
        else if (TongTienGoc == 0 && TongTienThucTe == 0 && QuaTangDaDoi.empty())
        {
            cout << "  Tong tien thanh toan: 0 VND" << endl;
        }
        else if (TongTienGoc == 0 && !QuaTangDaDoi.empty() && TongTienThucTe == 0)
        {
            cout << "  Tong tien thanh toan: 0 VND (Doi qua bang diem)" << endl;
        }
    }
    // Hàm này sẽ lưu thông tin đơn hàng vào file.
    void LuuVaoFile(ofstream &ofs) const
    {
        ofs << MaDonHang << endl;
        ofs << KhachHangDat.GetSoDienThoai() << endl;
        ofs << KhachHangDat.GetTen() << endl;
        ofs << KhachHangDat.GetDiaChi() << endl;
        ofs << TongTienGoc << endl;
        ofs << TongTienThucTe << endl;
        ofs << DanhSachMonAn.size() << endl;
        for (const auto &pair_item : DanhSachMonAn)
        {
            if (pair_item.first)
            {
                ofs << pair_item.first->GetTen() << endl;
                ofs << pair_item.second << endl;
            }
        }
        ofs << QuaTangDaDoi.size() << endl;
        for (const string &qua : QuaTangDaDoi)
        {
            ofs << qua << endl;
        }
    }
};
// Lớp chính quản lý toàn bộ hoạt động của cửa hàng burger.
class CuaHangBurger
{
private:
    vector<Burger *> DanhSachBurger;
    vector<Drink *> DanhSachNuocUong;
    vector<KhachHang> DanhSachThanhVien;
    vector<DonHang> DanhSachDonHang;
    vector<NhanVien> DanhSachNhanVien;
    array<LuaChonDoiDiem, 4> DanhSachLuaChonDoiDiem;

    KhachHang *ThanhVienHienTai = nullptr;
    bool AdminDangNhap = false;
    string AdminUsername = "admin";
    string AdminPassword = "admin123";
    string TenCuaHang;
    string DiaChiCuaHang;
    string SoDienThoaiCuaHang;
    int MaDonHangTiepTheo;
    int MaNhanVienTiepTheo;
    double GiamGiaLanDau = 0.1;
    int SoLuongLonDeGiamGia = 5;
    double GiamGiaSoLuongLon = 0.05;
    const int GiaTriVNDChoMotDiem = 1000;

    const string FILE_BURGER = "burger.txt";
    const string FILE_DRINK = "drink.txt";
    const string FILE_THANHVIEN = "memberacc.txt";
    const string FILE_NHANVIEN = "nhanvien.txt";
    const string FILE_DonHang = "DonHang.txt";
    const string FILE_CuaHang = "CuaHang.txt";
    const string FILE_ADMINACC = "adminacc.txt";
    // Khởi tạo danh sách các lựa chọn đổi điểm cố định.
    void KhoiTaoLuaChonDoiDiemCoDinh()
    {
        // THAY ĐỔI: Không dùng clear() và emplace_back() nữa.
        // Thay vào đó, gán trực tiếp vào các phần tử của mảng.
        DanhSachLuaChonDoiDiem[0] = LuaChonDoiDiem(1, 1000, "Giam 12% Gia tri don hang hien tai", "GiamGiaTheoPhanTram", 0.12);
        DanhSachLuaChonDoiDiem[1] = LuaChonDoiDiem(2, 150, "Moc khoa", "QUA_TANG", 0);
        DanhSachLuaChonDoiDiem[2] = LuaChonDoiDiem(3, 250, "Gau bong", "QUA_TANG", 0);
        DanhSachLuaChonDoiDiem[3] = LuaChonDoiDiem(4, 500, "Binh nuoc giu nhiet", "QUA_TANG", 0);
    }
    // Tải thông tin tài khoản admin từ file, hoặc tạo mới nếu file không tồn tại.
    void TaiAdminAcc()
    {
        ifstream ifs(FILE_ADMINACC);
        if (ifs.is_open())
        {
            string line;
            if (getline(ifs, line))
            {
                stringstream ss(line);
                string user, pass;
                if (getline(ss, user, ':') && getline(ss, pass))
                {
                    AdminUsername = user;
                    AdminPassword = pass;
                }
            }
            ifs.close();
        }
        else
        {
            ofstream ofs(FILE_ADMINACC);
            if (ofs.is_open())
            {
                ofs << AdminUsername << ":" << AdminPassword << endl;
                ofs.close();
            }
        }
    }
    // Tải danh sách burger từ file burger.txt.
    void TaiBurgerTuFile()
    {
        ifstream ifs(FILE_BURGER);
        if (!ifs.is_open())
            return;
        string TenGoc, MoTa, LoaiThit;
        int SoLuong;
        double Gia;
        while (getline(ifs, TenGoc))
        {
            if (!getline(ifs, MoTa))
                break;
            if (!(ifs >> SoLuong))
            {
                ifs.clear();
                ifs.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            ifs.ignore();
            if (!(ifs >> Gia))
            {
                ifs.clear();
                ifs.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            ifs.ignore();
            if (!getline(ifs, LoaiThit))
                break;
            DanhSachBurger.push_back(new Burger(TenGoc, MoTa, SoLuong, Gia, LoaiThit));
        }
        ifs.close();
    }
    // Lưu danh sách burger vào file burger.txt.
    void LuuBurgerRaFile() const
    {
        ofstream ofs(FILE_BURGER);
        if (!ofs.is_open())
            return;
        for (const auto *burger : DanhSachBurger)
        {
            burger->LuuVaoFile(ofs);
        }
        ofs.close();
    }
    // Tải danh sách đồ uống từ file drink.txt.
    void TaiNuocUongTuFile()
    {
        ifstream ifs(FILE_DRINK);
        if (!ifs.is_open())
            return;
        string TenGoc, KichThuoc, MoTaTrong;
        int SoLuong;
        double Gia;
        while (getline(ifs, TenGoc))
        {
            if (!getline(ifs, MoTaTrong))
                break;
            if (!(ifs >> SoLuong))
            {
                ifs.clear();
                ifs.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            ifs.ignore();
            if (!(ifs >> Gia))
            {
                ifs.clear();
                ifs.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            ifs.ignore();
            if (!getline(ifs, KichThuoc))
                break;
            DanhSachNuocUong.push_back(new Drink(TenGoc, SoLuong, Gia, KichThuoc));
        }
        ifs.close();
    }
    // Lưu danh sách đồ uống vào file drink.txt.
    void LuuNuocUongRaFile() const
    {
        ofstream ofs(FILE_DRINK);
        if (!ofs.is_open())
            return;
        for (const auto *drink : DanhSachNuocUong)
        {
            drink->LuuVaoFile(ofs);
        }
        ofs.close();
    }
    // Tải danh sách thành viên từ file.
    void TaiThanhVienTuFile()
    {
        ifstream ifs(FILE_THANHVIEN);
        if (!ifs.is_open())
            return;
        string username, password, Ten, sdt, DiaChi;
        bool DaMua;
        int diem;
        while (getline(ifs, username))
        {
            getline(ifs, password);
            getline(ifs, Ten);
            getline(ifs, sdt);
            getline(ifs, DiaChi);
            if (!(ifs >> DaMua))
            {
                ifs.clear();
                ifs.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            ifs.ignore();
            if (!(ifs >> diem))
            {
                ifs.clear();
                ifs.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            ifs.ignore();
            DanhSachThanhVien.emplace_back(username, password, Ten, sdt, DiaChi, DaMua, diem);
        }
        ifs.close();
    }
    // Lưu danh sách thành viên vào file.
    void LuuThanhVienRaFile() const
    {
        ofstream ofs(FILE_THANHVIEN);
        if (!ofs.is_open())
            return;
        for (const auto &tv : DanhSachThanhVien)
        {
            tv.LuuVaoFile(ofs);
        }
        ofs.close();
    }
    // Tải danh sách nhân viên từ file.
    void TaiNhanVienTuFile()
    {
        ifstream ifs(FILE_NHANVIEN);
        if (!ifs.is_open())
            return;
        int ma;
        string Ten, sdt, dc;
        int MaxMaNV = 0;
        while (ifs >> ma)
        {
            ifs.ignore();
            getline(ifs, Ten);
            getline(ifs, sdt);
            getline(ifs, dc);
            DanhSachNhanVien.emplace_back(ma, Ten, sdt, dc);
            if (ma > MaxMaNV)
                MaxMaNV = ma;
        }
        MaNhanVienTiepTheo = MaxMaNV + 1;
        ifs.close();
    }
    // Lưu danh sách nhân viên vào file.
    void LuuNhanVienRaFile() const
    {
        ofstream ofs(FILE_NHANVIEN);
        if (!ofs.is_open())
            return;
        for (const auto &nv : DanhSachNhanVien)
        {
            nv.LuuVaoFile(ofs);
        }
        ofs.close();
    }
    // Tìm một món ăn (burger hoặc drink) dựa trên tên đầy đủ của nó.
    MenuItem *TimMonAnTheoTenDayDu(const string &TenDayDuMonAn)
    {
        for (auto *item : DanhSachBurger)
        {
            if (item->GetTen() == TenDayDuMonAn)
                return item;
        }
        for (auto *item : DanhSachNuocUong)
        {
            if (item->GetTen() == TenDayDuMonAn)
                return item;
        }
        return nullptr;
    }
    // Tìm thành viên dựa trên username.
    KhachHang *TimThanhVienTheoUsername(const string &username)
    {
        for (auto &tv : DanhSachThanhVien)
        {
            if (tv.GetUsername() == username)
                return &tv;
        }
        return nullptr;
    }
    // Tìm thành viên dựa trên số điện thoại.
    KhachHang *TimThanhVienTheoSDT(const string &sdt)
    {
        for (auto &tv : DanhSachThanhVien)
        {
            if (tv.GetSoDienThoai() == sdt && !tv.GetUsername().empty())
                return &tv;
        }
        return nullptr;
    }
    // Tải danh sách đơn hàng từ file.
    void TaiDonHangTuFile()
    {
        ifstream ifs(FILE_DonHang);
        if (!ifs.is_open())
            return;
        int MaDon;
        string SDTKhachDat, TenKhachDat, DiaChiKhachDat;
        double TongGoc, TongThucTe;
        int SoLuongLoaiMon, SoLuongQuaTang;
        int MaxMaDon = 0;
        while (ifs >> MaDon)
        {
            ifs.ignore();
            getline(ifs, SDTKhachDat);
            getline(ifs, TenKhachDat);
            getline(ifs, DiaChiKhachDat);
            if (!(ifs >> TongGoc))
            {
                ifs.clear();
                ifs.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            ifs.ignore();
            if (!(ifs >> TongThucTe))
            {
                ifs.clear();
                ifs.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            ifs.ignore();
            KhachHang khachHangSnapshot(TenKhachDat, SDTKhachDat, DiaChiKhachDat);
            DonHang DonMoi(MaDon, khachHangSnapshot, TongGoc, TongThucTe);
            if (!(ifs >> SoLuongLoaiMon))
            {
                ifs.clear();
                ifs.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            ifs.ignore();
            for (int i = 0; i < SoLuongLoaiMon; ++i)
            {
                string TenMonDayDu;
                int sl;
                getline(ifs, TenMonDayDu);
                if (!(ifs >> sl))
                {
                    ifs.clear();
                    ifs.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                ifs.ignore();
                MenuItem *MonPtr = TimMonAnTheoTenDayDu(TenMonDayDu);
                if (MonPtr)
                    DonMoi.ThemMonAn(MonPtr, sl);
                else
                    cerr << "Canh bao: Khong tim thay mon an '" << TenMonDayDu << "' cho don hang #" << MaDon << endl;
            }
            if (!(ifs >> SoLuongQuaTang))
            {
                ifs.clear();
                ifs.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            ifs.ignore();
            for (int i = 0; i < SoLuongQuaTang; ++i)
            {
                string TenQua;
                if (!getline(ifs, TenQua))
                    break;
                DonMoi.ThemQuaTangDaDoi(TenQua);
            }
            DanhSachDonHang.push_back(DonMoi);
            if (MaDon > MaxMaDon)
                MaxMaDon = MaDon;
        }
        MaDonHangTiepTheo = MaxMaDon + 1;
        ifs.close();
    }
    // Lưu danh sách đơn hàng vào file.
    void LuuDonHangRaFile() const
    {
        ofstream ofs(FILE_DonHang);
        if (!ofs.is_open())
            return;
        for (const auto &dh : DanhSachDonHang)
        {
            dh.LuuVaoFile(ofs);
        }
        ofs.close();
    }
    // Tải thông tin cửa hàng từ file.
    void TaiThongTinCuaHangTuFile()
    {
        ifstream ifs(FILE_CuaHang);
        if (!ifs.is_open())
        {
            TenCuaHang = "Burger Ngon Da Nang";
            DiaChiCuaHang = "[Dia chi chua cap nhat]";
            SoDienThoaiCuaHang = "[SDT chua cap nhat]";
            return;
        }
        getline(ifs, TenCuaHang);
        getline(ifs, DiaChiCuaHang);
        getline(ifs, SoDienThoaiCuaHang);
        ifs.close();
    }
    // Lưu thông tin cửa hàng vào file.
    void LuuThongTinCuaHangRaFile() const
    {
        ofstream ofs(FILE_CuaHang);
        if (!ofs.is_open())
            return;
        ofs << TenCuaHang << endl;
        ofs << DiaChiCuaHang << endl;
        ofs << SoDienThoaiCuaHang << endl;
        ofs.close();
    }

public:
    CuaHangBurger(string Ten = "Burger Ngon Da Nang", string DiaChi = "[Dia chi]", string sdt = "[So dien thoai]")
        : TenCuaHang(Ten), DiaChiCuaHang(DiaChi), SoDienThoaiCuaHang(sdt),
          MaDonHangTiepTheo(1), MaNhanVienTiepTheo(1)
    {
        TaiAdminAcc();
        KhoiTaoLuaChonDoiDiemCoDinh();
        TaiToanBoDuLieu();
    }
    ~CuaHangBurger()
    {
        LuuToanBoDuLieu();
        for (MenuItem *item : DanhSachBurger)
        {
            delete item;
        }
        DanhSachBurger.clear();
        for (MenuItem *item : DanhSachNuocUong)
        {
            delete item;
        }
        DanhSachNuocUong.clear();
    }
    // Hàm này sẽ tải toàn bộ dữ liệu từ các file tương ứng.
    void TaiToanBoDuLieu()
    {
        TaiThongTinCuaHangTuFile();
        TaiBurgerTuFile();
        TaiNuocUongTuFile();
        TaiThanhVienTuFile();
        TaiNhanVienTuFile();
        TaiDonHangTuFile();
    }
    // Hàm này sẽ lưu toàn bộ dữ liệu vào các file tương ứng.
    void LuuToanBoDuLieu() const
    {
        LuuThongTinCuaHangRaFile();
        LuuBurgerRaFile();
        LuuNuocUongRaFile();
        LuuThanhVienRaFile();
        LuuNhanVienRaFile();
        LuuDonHangRaFile();
    }
    // Hàm nãy dùng để đăng nhập quản lý
    bool DangNhapAdmin()
    {
        string username, password;
        cout << "  --- Dang nhap Quan Ly ---" << endl;
        cout << "  Username: ";
        getline(cin, username);
        cout << "  Password: ";
        getline(cin, password);
        if (username == AdminUsername && password == AdminPassword)
        {
            AdminDangNhap = true;
            ThanhVienHienTai = nullptr;
            cout << "  Dang nhap Quan Ly thanh cong!" << endl;
            return true;
        }
        cout << "  Sai username hoac password quan ly." << endl;
        return false;
    }
    // Hàm này dùng để đăng nhập thành viên
    bool DangNhapThanhVien()
    {
        string username, password;
        cout << "  --- Dang nhap Thanh Vien ---" << endl;
        cout << "  Username: ";
        getline(cin, username);
        cout << "  Password: ";
        getline(cin, password);
        for (auto &tv : DanhSachThanhVien)
        {
            if (tv.GetUsername() == username && tv.GetPassword() == password)
            {
                ThanhVienHienTai = &tv;
                AdminDangNhap = false;
                cout << "  Chao mung tro lai, " << tv.GetTen() << "!" << endl;
                return true;
            }
        }
        cout << "  Sai username hoac password thanh vien." << endl;
        return false;
    }
    // Hàm này dùng để đăng ký thành viên mới
    void DangKyThanhVien()
    {
        cout << "\n  --- Dang ky tai khoan Thanh vien moi ---" << endl;
        string username, password, Ten, sdt, DiaChi;
        while (true)
        {
            cout << "  Nhap Username mong muon: ";
            getline(cin, username);
            if (username.empty())
            {
                cout << "  Username khong duoc de trong." << endl;
                continue;
            }
            bool TrungUser = false;
            for (const auto &tv : DanhSachThanhVien)
            {
                if (tv.GetUsername() == username)
                {
                    TrungUser = true;
                    break;
                }
            }
            if (TrungUser)
            {
                cout << "  Username nay da ton tai. Vui long chon username khac." << endl;
            }
            else
            {
                break;
            }
        }
        while (true)
        {
            cout << "  Nhap Password (it nhat 8 ky tu): ";
            getline(cin, password);
            if (password.length() < 8)
            {
                cout << "  Password qua ngan. Phai co it nhat 8 ky tu." << endl;
            }
            else
            {
                break;
            }
        }
        cout << "  Nhap Ho Ten: ";
        getline(cin, Ten);
        while (true)
        {
            cout << "  Nhap So dien thoai: ";
            getline(cin, sdt);
            if (sdt.empty())
            {
                cout << "  So dien thoai khong duoc de trong." << endl;
                continue;
            }
            bool TrungSDT = false;
            for (const auto &tv : DanhSachThanhVien)
            {
                if (tv.GetSoDienThoai() == sdt && !tv.GetUsername().empty())
                {
                    TrungSDT = true;
                    break;
                }
            }
            if (TrungSDT)
            {
                cout << "  So dien thoai nay da duoc dang ky boi mot thanh vien khac." << endl;
            }
            else
            {
                break;
            }
        }
        cout << "  Nhap Dia chi: ";
        getline(cin, DiaChi);
        DanhSachThanhVien.emplace_back(username, password, Ten, sdt, DiaChi, false, 0);
        cout << "  Dang ky thanh vien thanh cong! Username: " << username << endl;
        cout << "  Vui long dang nhap de bat dau mua sam va huong uu dai." << endl;
    }
    // Hàm này dùng để đăng xuất thành viên hoặc quản lý
    void DangXuat()
    {
        if (AdminDangNhap)
        {
            AdminDangNhap = false;
            cout << "  Da dang xuat khoi tai khoan Quan ly." << endl;
        }
        else if (ThanhVienHienTai)
        {
            cout << "  Da dang xuat khoi tai khoan Thanh vien: " << ThanhVienHienTai->GetUsername() << endl;
            ThanhVienHienTai = nullptr;
        }
        else
        {
            cout << "  Khong co ai dang dang nhap." << endl;
        }
    }
    // Hàm này dùng để thay đổi thông tin cá nhân của thành viên hiện tại.
    void ThayDoiThongTinCaNhan()
    {
        if (!ThanhVienHienTai)
        {
            cout << "  Loi: Ban can dang nhap de su dung chuc nang nay." << endl;
            return;
        }
        cout << "\n  --- Thay doi thong tin ca nhan ---" << endl;
        ThanhVienHienTai->HienThiThongTin();
        int choice = GetInputValidated<int>("  Ban muon thay doi thong tin nao?\n  1. Ho Ten\n  2. So dien thoai\n  3. Dia chi\n  4. Mat khau\n  0. Quay lai\n  Nhap lua chon: ");
        string TenMoi, SDTMoi, DCMoi, PassCu, PassMoi1, PassMoi2;
        switch (choice)
        {
        case 1:
            cout << "  Ho Ten hien tai: " << ThanhVienHienTai->GetTen() << endl;
            cout << "  Nhap ho Ten moi: ";
            getline(cin, TenMoi);
            ThanhVienHienTai->SetTen(!TenMoi.empty() ? TenMoi : ThanhVienHienTai->GetTen());
            cout << (!TenMoi.empty() ? "  Da cap nhat ho Ten." : "  Khong thay doi ho Ten.") << endl;
            break;
        case 2:
            cout << "  So dien thoai hien tai: " << ThanhVienHienTai->GetSoDienThoai() << endl;
            while (true)
            {
                cout << "  Nhap so dien thoai moi: ";
                getline(cin, SDTMoi);
                if (SDTMoi.empty())
                {
                    cout << "  Khong thay doi so dien thoai." << endl;
                    break;
                }
                if (SDTMoi == ThanhVienHienTai->GetSoDienThoai())
                {
                    cout << "  So dien thoai moi trung voi so cu. Khong thay doi." << endl;
                    break;
                }
                bool TrungSDT = false;
                for (const auto &tv : DanhSachThanhVien)
                {
                    if (tv.GetSoDienThoai() == SDTMoi && tv.GetUsername() != ThanhVienHienTai->GetUsername())
                    {
                        TrungSDT = true;
                        break;
                    }
                }
                if (TrungSDT)
                {
                    cout << "  So dien thoai nay da duoc dang ky boi mot thanh vien khac." << endl;
                }
                else
                {
                    ThanhVienHienTai->SetSoDienThoai(SDTMoi);
                    cout << "  Da cap nhat so dien thoai." << endl;
                    break;
                }
            }
            break;
        case 3:
            cout << "  Dia chi hien tai: " << ThanhVienHienTai->GetDiaChi() << endl;
            cout << "  Nhap dia chi moi: ";
            getline(cin, DCMoi);
            ThanhVienHienTai->SetDiaChi(!DCMoi.empty() ? DCMoi : ThanhVienHienTai->GetDiaChi());
            cout << (!DCMoi.empty() ? "  Da cap nhat dia chi." : "  Khong thay doi dia chi.") << endl;
            break;
        case 4:
            cout << "  --- Thay doi mat khau ---" << endl;
            cout << "  Nhap mat khau cu: ";
            getline(cin, PassCu);
            if (PassCu == ThanhVienHienTai->GetPassword())
            {
                while (true)
                {
                    cout << "  Nhap mat khau moi (it nhat 8 ky tu): ";
                    getline(cin, PassMoi1);
                    if (PassMoi1.length() < 8)
                    {
                        cout << "  Mat khau moi qua ngan." << endl;
                        continue;
                    }
                    cout << "  Xac nhan mat khau moi: ";
                    getline(cin, PassMoi2);
                    if (PassMoi1 == PassMoi2)
                    {
                        ThanhVienHienTai->SetPassword(PassMoi1);
                        cout << "  Da cap nhat mat khau." << endl;
                        break;
                    }
                    else
                    {
                        cout << "  Mat khau xac nhan khong khop." << endl;
                    }
                }
            }
            else
            {
                cout << "  Mat khau cu khong dung." << endl;
            }
            break;
        case 0:
            break;
        default:
            cout << "  Lua chon khong hop le." << endl;
        }
    }
    // Hàm này dùng để hiển thị danh sách các lựa chọn đổi điểm cho thành viên hiện tại.
    void XemDanhSachLuaChonDoiDiemChoThanhVien(int DiemHienCoCuaKhach, const string &LoaiMuonXem) const
    {
        cout << "\n  --- Cac lua chon doi diem co the (" << (LoaiMuonXem == "GiamGiaTheoPhanTram" ? "Giam Gia" : "Qua tang") << ") ---" << endl;
        bool CoLuaChonPhuHop = false;
        for (const auto &LuaChon : DanhSachLuaChonDoiDiem)
        {
            if (LuaChon.LoaiPhanThuong == LoaiMuonXem && DiemHienCoCuaKhach >= LuaChon.DiemCanDoi)
            {
                LuaChon.HienThi();
                CoLuaChonPhuHop = true;
            }
        }
        if (!CoLuaChonPhuHop)
        {
            cout << "  Ban khong du diem cho bat ky lua chon " << (LoaiMuonXem == "GiamGiaTheoPhanTram" ? "Giam Gia" : "qua tang") << " nao hien tai." << endl;
        }
    }
    // Hàm này dùng để tìm nhân viên theo mã nhân viên.
    NhanVien *TimNhanVien(int maNV)
    {
        for (auto &nv : DanhSachNhanVien)
        {
            if (nv.GetMaNV() == maNV)
                return &nv;
        }
        return nullptr;
    }
    // Hàm này dùng để nhập thông tin cửa hàng.
    void NhapThongTinCuaHang()
    {
        cout << "\n  --- Nhap/Cap nhat thong tin cua hang ---" << endl;
        string TempTen, TempDiaChi, TempSDT;
        cout << "  Ten cua hang hien tai: " << TenCuaHang << endl;
        cout << "  Nhap Ten cua hang moi (de trong neu khong doi): ";
        getline(cin, TempTen);
        TenCuaHang = !TempTen.empty() ? TempTen : TenCuaHang;
        cout << "  Dia chi cua hang hien tai: " << DiaChiCuaHang << endl;
        cout << "  Nhap dia chi cua hang moi (de trong neu khong doi): ";
        getline(cin, TempDiaChi);
        DiaChiCuaHang = !TempDiaChi.empty() ? TempDiaChi : DiaChiCuaHang;
        cout << "  So dien thoai cua hang hien tai: " << SoDienThoaiCuaHang << endl;
        cout << "  Nhap so dien thoai cua hang moi (de trong neu khong doi): ";
        getline(cin, TempSDT);
        SoDienThoaiCuaHang = !TempSDT.empty() ? TempSDT : SoDienThoaiCuaHang;
        cout << "  Da cap nhat thong tin cua hang!" << endl;
    }
    // Hàm này dùng để thêm món ăn vào menu.
    void ThemMonAn(bool LaBurger)
    {
        string TenGoc, MoTaBurger, LoaiThit, KichThuoc;
        int SoLuong;
        double Gia;
        cout << (LaBurger ? "\n  --- Them burger ---" : "\n  --- Them nuoc uong ---") << endl;
        cout << "  Nhap Ten goc " << (LaBurger ? "burger (vi du: Bo Pho Mai, Ga Gion): " : "nuoc uong (vi du: Coca Cola, Tra Dao): ");
        getline(cin, TenGoc);
        if (LaBurger)
        {
            cout << "  Nhap mo ta cho burger: ";
            getline(cin, MoTaBurger);
            cout << "  Nhap loai thit: ";
            getline(cin, LoaiThit);
        }
        else
        {
            cout << "  Nhap kich thuoc (S, M, L): ";
            while (true)
            {
                getline(cin, KichThuoc);
                KichThuoc = StringToUpper(KichThuoc);
                if (KichThuoc == "S" || KichThuoc == "M" || KichThuoc == "L")
                    break;
                cout << "  Kich thuoc khong hop le. Vui long nhap S, M, hoac L: ";
            }
        }
        SoLuong = GetInputValidated<int>("  Nhap so luong: ");
        while (SoLuong < 0)
            SoLuong = GetInputValidated<int>("  Loi: So luong phai la so khong am. Nhap lai: ");
        Gia = GetInputValidated<double>("  Nhap Gia: ");
        while (Gia < 0)
            Gia = GetInputValidated<double>("  Loi: Gia phai la so khong am. Nhap lai: ");
        if (LaBurger)
        {
            DanhSachBurger.push_back(new Burger(TenGoc, MoTaBurger, SoLuong, Gia, LoaiThit));
        }
        else
        {
            DanhSachNuocUong.push_back(new Drink(TenGoc, SoLuong, Gia, KichThuoc));
        }
        cout << "  Da them thanh cong!" << endl;
    }
    // Hàm này dùng để lấy món ăn theo STT tổng hợp từ cả burger và nước uống.
    MenuItem *GetMonAnTheoSTTTongHop(int stt)
    {
        if (stt <= 0)
            return nullptr;
        if ((size_t)stt <= DanhSachBurger.size())
        {
            return DanhSachBurger[stt - 1];
        }
        stt -= DanhSachBurger.size();
        if ((size_t)stt <= DanhSachNuocUong.size())
        {
            return DanhSachNuocUong[stt - 1];
        }
        return nullptr;
    }
    // Hàm này dùng để hiển thị danh sách menu đầy đủ.
    void HienThiDanhSachMenuDayDu(bool LaAdminXem) const
    {
        cout << "\n                          --- Menu Thuc Don ---" << endl;
        if (DanhSachBurger.empty() && DanhSachNuocUong.empty())
        {
            cout << "  Menu hien chua co mon nao." << endl;
            return;
        }
        vector<int> widths;
        vector<string> headers;

        if (LaAdminXem)
        {
            widths = {6, 35, 12, 15};
            headers = {"STT", "Ten Mon", "So Luong", "Gia (VND)"};
        }
        else
        {
            widths = {6, 48, 15};
            headers = {"STT", "Ten Mon", "Gia (VND)"};
        }
        VeDuongBienBang(widths);
        VeHangBang(headers, widths);
        VeDuongBienBang(widths);
        int stt = 1;
        if (!DanhSachBurger.empty())
        {
            VeHangPhanCach("Burger", widths);
            for (const auto *burger : DanhSachBurger)
            {
                string STTDisplay = to_string(stt++) + ".";
                stringstream GiaStream;
                GiaStream << fixed << setprecision(0) << burger->GetGia();

                if (LaAdminXem)
                {
                    VeHangBang({STTDisplay, burger->GetTenGocMenuItem(), to_string(burger->GetSoLuong()), GiaStream.str()}, widths);
                }
                else
                {
                    VeHangBang({STTDisplay, burger->GetTenGocMenuItem(), GiaStream.str()}, widths);
                }
            }
        }
        if (!DanhSachNuocUong.empty())
        {
            VeHangPhanCach("Nuoc Uong", widths);
            for (const auto *drink : DanhSachNuocUong)
            {
                string STTDisplay = to_string(stt++) + ".";
                string TenHienThi = drink->GetTenGocMenuItem() + " (" + drink->GetKichThuoc() + ")";
                stringstream GiaStream;
                GiaStream << fixed << setprecision(0) << drink->GetGia();

                if (LaAdminXem)
                {
                    VeHangBang({STTDisplay, TenHienThi, to_string(drink->GetSoLuong()), GiaStream.str()}, widths);
                }
                else
                {
                    VeHangBang({STTDisplay, TenHienThi, GiaStream.str()}, widths);
                }
            }
        }
        VeDuongBienBang(widths);
    }
    // Hàm này dùng để chỉnh sửa món ăn trong menu.
    void ChinhSuaMonAn()
    {
        HienThiDanhSachMenuDayDu(true);
        if (DanhSachBurger.empty() && DanhSachNuocUong.empty())
            return;
        int STTChon = GetInputValidated<int>("  Nhap STT mon an muon chinh sua: ");
        MenuItem *MonAnCanSua = GetMonAnTheoSTTTongHop(STTChon);
        if (!MonAnCanSua)
        {
            cout << "  STT khong hop le." << endl;
            return;
        }
        cout << "\n  --- Chinh sua mon an: " << MonAnCanSua->GetTen() << " ---" << endl;
        if (Burger *burger = dynamic_cast<Burger *>(MonAnCanSua))
        {
            string MoTaMoiBurger, LoaiThitMoi;
            cout << "  Mo ta hien tai: " << burger->GetMoTa() << endl;
            cout << "  Mo ta moi cho Burger (de trong de giu nguyen): ";
            getline(cin, MoTaMoiBurger);
            burger->SetMoTa(!MoTaMoiBurger.empty() ? MoTaMoiBurger : burger->GetMoTa());
            cout << "  Loai thit hien tai: " << burger->GetLoaiThit() << endl;
            cout << "  Loai thit moi (de trong de giu nguyen): ";
            getline(cin, LoaiThitMoi);
            burger->SetLoaiThit(!LoaiThitMoi.empty() ? LoaiThitMoi : burger->GetLoaiThit());
        }
        else if (Drink *drink = dynamic_cast<Drink *>(MonAnCanSua))
        {
            string KichThuocMoi;
            cout << "  Kich thuoc hien tai: " << drink->GetKichThuoc() << endl;
            cout << "  Kich thuoc moi (S, M, L, de trong neu khong doi): ";
            getline(cin, KichThuocMoi);
            if (!KichThuocMoi.empty())
            {
                KichThuocMoi = StringToUpper(KichThuocMoi);
                if (KichThuocMoi == "S" || KichThuocMoi == "M" || KichThuocMoi == "L")
                {
                    drink->SetKichThuoc(KichThuocMoi);
                }
                else
                {
                    cout << "  Kich thuoc khong hop le, khong thay doi." << endl;
                }
            }
        }
        cout << "  So luong moi (nhap so am de giu nguyen [" << MonAnCanSua->GetSoLuong() << "]): ";
        string inputSL;
        getline(cin, inputSL);
        if (!inputSL.empty())
        {
            try
            {
                int sl = stoi(inputSL);
                if (sl >= 0)
                    MonAnCanSua->SetSoLuong(sl);
            }
            catch (const std::exception &e)
            {
            }
        }
        cout << "  Gia moi (nhap so am de giu nguyen [" << fixed << setprecision(0) << MonAnCanSua->GetGia() << "]): ";
        string inputGia;
        getline(cin, inputGia);
        if (!inputGia.empty())
        {
            try
            {
                double g = stod(inputGia);
                if (g >= 0)
                    MonAnCanSua->SetGia(g);
            }
            catch (const std::exception &e)
            {
            }
        }
        cout << "  Da cap nhat thong tin mon an!" << endl;
    }
    // Hàm này dùng để xóa món ăn khỏi menu.
    void XoaMonAn()
    {
        HienThiDanhSachMenuDayDu(true);
        if (DanhSachBurger.empty() && DanhSachNuocUong.empty())
            return;
        int STTChon = GetInputValidated<int>("  Nhap STT mon an muon xoa: ");
        MenuItem *MonAnCanXoa = nullptr;
        bool LaMonBurger = false;
        int IndexTrongVector = -1;
        if (STTChon > 0 && (size_t)STTChon <= DanhSachBurger.size())
        {
            MonAnCanXoa = DanhSachBurger[STTChon - 1];
            LaMonBurger = true;
            IndexTrongVector = STTChon - 1;
        }
        else if (STTChon > DanhSachBurger.size() && (size_t)STTChon <= DanhSachBurger.size() + DanhSachNuocUong.size())
        {
            IndexTrongVector = STTChon - DanhSachBurger.size() - 1;
            MonAnCanXoa = DanhSachNuocUong[IndexTrongVector];
            LaMonBurger = false;
        }
        if (!MonAnCanXoa)
        {
            cout << "  STT khong hop le." << endl;
            return;
        }
        char confirm = GetInputValidated<char>("  Ban co chac chan muon xoa " + MonAnCanXoa->GetTen() + "? (y/n): ");
        if (confirm == 'y' || confirm == 'Y')
        {
            delete MonAnCanXoa;
            if (LaMonBurger)
            {
                DanhSachBurger.erase(DanhSachBurger.begin() + IndexTrongVector);
            }
            else
            {
                DanhSachNuocUong.erase(DanhSachNuocUong.begin() + IndexTrongVector);
            }
            cout << "  Da xoa mon an thanh cong!" << endl;
        }
        else
        {
            cout << "  Huy bo xoa mon an." << endl;
        }
    }
    // Hàm này dùng để hiển thị danh sách đơn hàng.
    void HienThiDanhSachDonHang() const
    {
        cout << "\n  --- Danh sach don hang ---" << endl;
        if (DanhSachDonHang.empty())
        {
            cout << "  Chua co don hang nao." << endl;
            return;
        }
        for (const auto &don : DanhSachDonHang)
        {
            don.HienThiThongTin();
            cout << endl;
            VeDuongNgang(40, '=');
        }
    }
    // Hàm này dùng để thêm đơn hàng mới cho khách hoặc thành viên.
    void ThemDonHangChoKhachHoacThanhVien()
    {
        cout << "\n  --- Them don hang moi (Quan ly) ---" << endl;
        int LoaiKhach = GetInputValidated<int>("  Don hang nay cho:\n  1. Thanh vien da dang ky\n  2. Khach vang lai\n  Nhap lua chon: ");
        KhachHang *KhachHangThucTe = nullptr;
        KhachHang KhachHangDatDonHang("", "", "");
        if (LoaiKhach == 1)
        {
            string idTimKiem;
            cout << "  Nhap Username hoac SDT cua thanh vien: ";
            getline(cin, idTimKiem);
            KhachHangThucTe = TimThanhVienTheoUsername(idTimKiem);
            if (!KhachHangThucTe)
                KhachHangThucTe = TimThanhVienTheoSDT(idTimKiem);
            if (!KhachHangThucTe)
            {
                cout << "  Khong tim thay thanh vien." << endl;
                return;
            }
            cout << "  Don hang cho thanh vien: " << KhachHangThucTe->GetTen() << endl;
            KhachHangDatDonHang = *KhachHangThucTe;
        }
        else if (LoaiKhach == 2)
        {
            string Ten, sdt, dc;
            cout << "  Xin moi nhap Ten: ";
            getline(cin, Ten);
            cout << "  Xin moi nhap so dien thoai: ";
            getline(cin, sdt);
            cout << "  Xin moi nhap dia chi: ";
            getline(cin, dc);
            KhachHangDatDonHang = KhachHang(Ten, sdt, dc);
        }
        else
        {
            cout << "  Lua chon khong hop le." << endl;
            return;
        }
        DonHang DonMoi(MaDonHangTiepTheo, KhachHangDatDonHang);
        char ThemMonAn;
        do
        {
            HienThiDanhSachMenuDayDu(false);
            if (DanhSachBurger.empty() && DanhSachNuocUong.empty())
            {
                cout << "Menu trong." << endl;
                break;
            }
            int STTChon = GetInputValidated<int>("  Nhap STT mon an muon them (0 de hoan tat): ");
            if (STTChon == 0)
                break;
            MenuItem *MonAnDaChon = GetMonAnTheoSTTTongHop(STTChon);
            if (!MonAnDaChon)
            {
                cout << "STT khong hop le." << endl;
                ThemMonAn = 'y';
                continue;
            }
            int SoLuongMua = GetInputValidated<int>("  Nhap so luong: ");
            if (SoLuongMua <= 0)
            {
                cout << "So luong khong hop le." << endl;
                ThemMonAn = 'y';
                continue;
            }
            if (SoLuongMua <= MonAnDaChon->GetSoLuong())
            {
                DonMoi.ThemMonAn(MonAnDaChon, SoLuongMua);
                MonAnDaChon->SetSoLuong(MonAnDaChon->GetSoLuong() - SoLuongMua);
            }
            else
            {
                cout << "  So luong khong du trong kho." << endl;
            }
            ThemMonAn = GetInputValidated<char>("  Them mon khac? (y/n): ");
        } while (ThemMonAn == 'y' || ThemMonAn == 'Y');
        if (DonMoi.GetDanhSachMonAn().empty())
        {
            cout << "  Don hang trong. Huy them don hang." << endl;
            return;
        }
        DonMoi.TinhLaiTongTienGoc();
        double TongTienThanhToan = DonMoi.GetTongTienGoc();
        if (KhachHangThucTe)
        {
            if (!KhachHangThucTe->GetDaMuaLanDau() && TongTienThanhToan > 0)
            {
                double TienGiam = TongTienThanhToan * GiamGiaLanDau;
                TongTienThanhToan -= TienGiam;
                cout << "  Ap dung Giam Gia " << fixed << setprecision(0) << GiamGiaLanDau * 100 << "% cho thanh vien mua lan dau." << endl;
                KhachHangThucTe->SetDaMuaLanDau(true);
            }
            if (DonMoi.GetDanhSachMonAn().size() >= (size_t)SoLuongLonDeGiamGia && TongTienThanhToan > 0)
            {
                double TienGiam = TongTienThanhToan * GiamGiaSoLuongLon;
                TongTienThanhToan -= TienGiam;
                cout << "  Ap dung Giam Gia " << fixed << setprecision(0) << GiamGiaSoLuongLon * 100 << "% cho don hang so luong lon." << endl;
            }
            TongTienThanhToan = (TongTienThanhToan < 0) ? 0 : TongTienThanhToan;
            int DiemThuong = static_cast<int>(TongTienThanhToan / GiaTriVNDChoMotDiem);
            if (DiemThuong > 0)
            {
                KhachHangThucTe->ThemDiem(DiemThuong);
                cout << "  Thanh vien " << KhachHangThucTe->GetTen() << " duoc cong " << DiemThuong << " diem." << endl;
                cout << "  Tong diem hien tai: " << KhachHangThucTe->GetDiemTichLuy() << " diem." << endl;
            }
        }
        DonMoi.SetTongTienThucTe(TongTienThanhToan);
        DanhSachDonHang.push_back(DonMoi);
        MaDonHangTiepTheo++;
        cout << "  Da them don hang #" << DonMoi.GetMaDonHang() << " thanh cong!" << endl;
        DonMoi.HienThiThongTin();
    }
    // Hàm này dùng để xóa đơn hàng theo mã đơn hàng.
    void XoaDonHang()
    {
        HienThiDanhSachDonHang();
        if (DanhSachDonHang.empty())
            return;
        int MaDonHangXoa = GetInputValidated<int>("  Nhap ma don hang muon xoa: ");
        for (auto it = DanhSachDonHang.begin(); it != DanhSachDonHang.end(); ++it)
        {
            if (it->GetMaDonHang() == MaDonHangXoa)
            {
                char confirm = GetInputValidated<char>("  Ban co chac chan muon xoa don hang #" + to_string(MaDonHangXoa) + "? (y/n): ");
                if (confirm == 'y' || confirm == 'Y')
                {
                    const auto &DanhSachMaTrongDonHang = it->GetDanhSachMonAn();
                    for (const auto &item : DanhSachMaTrongDonHang)
                    {
                        if (item.first)
                            item.first->SetSoLuong(item.first->GetSoLuong() + item.second);
                    }
                    cout << "  Luu y: Neu don hang nay cua thanh vien va da co Giao dich diem/uu dai, viec hoan lai cac uu dai do chua duoc tu dong xu ly." << endl;
                    DanhSachDonHang.erase(it);
                    cout << "  Da xoa don hang #" << MaDonHangXoa << " thanh cong!" << endl;
                }
                else
                {
                    cout << "  Huy bo xoa don hang." << endl;
                }
                return;
            }
        }
        cout << "  Khong tim thay don hang #" << MaDonHangXoa << endl;
    }
    // Hàm này dùng để thêm nhân viên mới.
    void ThemNhanVien()
    {
        cout << "\n  --- Them nhan vien ---" << endl;
        string Ten, sdt, dc;
        cout << "  Nhap Ten nhan vien: ";
        getline(cin, Ten);
        cout << "  Nhap so dien thoai: ";
        getline(cin, sdt);
        cout << "  Nhap dia chi: ";
        getline(cin, dc);
        DanhSachNhanVien.emplace_back(MaNhanVienTiepTheo, Ten, sdt, dc);
        cout << "  Da them nhan vien #" << MaNhanVienTiepTheo++ << " thanh cong!" << endl;
    }
    // Hàm này dùng để xem danh sách nhân viên.
    void XemDanhSachNhanVien() const
    {
        cout << "\n              --- Danh sach nhan vien ---" << endl;
        if (DanhSachNhanVien.empty())
        {
            cout << "  Chua co nhan vien nao." << endl;
            return;
        }
        vector<int> widths = {10, 25, 20, 30};
        vector<string> headers = {"Ma NV", "Ten Nhan Vien", "So Dien Thoai", "Dia Chi"};
        VeDuongBienBang(widths);
        VeHangBang(headers, widths);
        VeDuongBienBang(widths);
        for (const auto &nv : DanhSachNhanVien)
        {
            VeHangBang({to_string(nv.GetMaNV()), nv.GetTenNV(), nv.GetSoDienThoaiNV(), nv.GetDiaChiNV()}, widths);
        }
        VeDuongBienBang(widths);
    }
    // Hàm này dùng để chỉnh sửa thông tin nhân viên.
    void ChinhSuaNhanVien()
    {
        XemDanhSachNhanVien();
        if (DanhSachNhanVien.empty())
            return;
        int MaNVChinhSua = GetInputValidated<int>("  Nhap ma nhan vien muon chinh sua: ");
        NhanVien *NVCanSua = TimNhanVien(MaNVChinhSua);
        if (!NVCanSua)
        {
            cout << "  Khong tim thay nhan vien co ma #" << MaNVChinhSua << endl;
            return;
        }
        cout << "\n  --- Chinh sua thong tin nhan vien #" << NVCanSua->GetMaNV() << " ---" << endl;
        string TenMoi, SDTMoi, DCMoi;
        cout << "  Ten moi (de trong de giu nguyen [" << NVCanSua->GetTenNV() << "]): ";
        getline(cin, TenMoi);
        NVCanSua->SetTenNV(!TenMoi.empty() ? TenMoi : NVCanSua->GetTenNV());
        cout << "  So dien thoai moi (de trong de giu nguyen [" << NVCanSua->GetSoDienThoaiNV() << "]): ";
        getline(cin, SDTMoi);
        NVCanSua->SetSoDienThoaiNV(!SDTMoi.empty() ? SDTMoi : NVCanSua->GetSoDienThoaiNV());
        cout << "  Dia chi moi (de trong de giu nguyen [" << NVCanSua->GetDiaChiNV() << "]): ";
        getline(cin, DCMoi);
        NVCanSua->SetDiaChiNV(!DCMoi.empty() ? DCMoi : NVCanSua->GetDiaChiNV());
        cout << "  Da cap nhat thong tin nhan vien!" << endl;
    }
    // Hàm này dùng để xóa nhân viên theo mã nhân viên.
    void XoaNhanVien()
    {
        XemDanhSachNhanVien();
        if (DanhSachNhanVien.empty())
            return;
        int maNVXoa = GetInputValidated<int>("  Nhap ma nhan vien muon xoa: ");
        for (auto it = DanhSachNhanVien.begin(); it != DanhSachNhanVien.end(); ++it)
        {
            if (it->GetMaNV() == maNVXoa)
            {
                char confirm = GetInputValidated<char>("  Ban co chac chan muon xoa nhan vien #" + to_string(maNVXoa) + " (" + it->GetTenNV() + ")? (y/n): ");
                if (confirm == 'y' || confirm == 'Y')
                {
                    DanhSachNhanVien.erase(it);
                    cout << "  Da xoa nhan vien #" << maNVXoa << " thanh cong!" << endl;
                }
                else
                {
                    cout << "  Huy bo xoa nhan vien." << endl;
                }
                return;
            }
        }
        cout << "  Khong tim thay nhan vien co ma #" << maNVXoa << endl;
    }
    // Hàm này dùng để hiển thị danh sách thành viên.
    void HienThiDanhSachThanhVien() const
    {
        cout << "\n"
             << string(40, ' ') << "--- Danh sach thanh vien ---\n";
        if (DanhSachThanhVien.empty())
        {
            cout << "  Chua co thanh vien nao." << endl;
            return;
        }
        vector<int> widths = {20, 25, 18, 28, 10, 15};
        vector<string> headers = {"Username", "Ten Khach Hang", "So Dien Thoai", "Dia Chi", "Diem", "Mua Lan Dau"};
        VeDuongBienBang(widths);
        VeHangBang(headers, widths);
        VeDuongBienBang(widths);
        for (const auto &tv : DanhSachThanhVien)
        {
            string DaMua = tv.GetDaMuaLanDau() ? "Roi" : "Chua";
            VeHangBang({tv.GetUsername(), tv.GetTen(), tv.GetSoDienThoai(), tv.GetDiaChi(), to_string(tv.GetDiemTichLuy()), DaMua}, widths);
        }
        VeDuongBienBang(widths);
    }
    // Hàm này dùng để báo cáo doanh thu.
    void BaoCaoDoanhThu() const
    {
        cout << "\n  --- Bao cao doanh thu ---" << endl;
        if (DanhSachDonHang.empty())
        {
            cout << "  Chua co don hang nao de thong ke." << endl;
            return;
        }
        double TongDoanhThuGoc = 0, TongDoanhThuThucTe = 0;
        for (const auto &DonHang : DanhSachDonHang)
        {
            TongDoanhThuGoc += DonHang.GetTongTienGoc();
            TongDoanhThuThucTe += DonHang.GetTongTienThucTe();
        }
        cout << "  Tong so don hang: " << DanhSachDonHang.size() << endl;
        cout << "  Tong doanh thu (theo tien goc): " << fixed << setprecision(0) << TongDoanhThuGoc << " VND" << endl;
        cout << "  Tong doanh thu thuc te (sau Giam Gia): " << fixed << setprecision(0) << TongDoanhThuThucTe << " VND" << endl;
    }
    // Hàm này dùng để báo cáo món bán chạy.
    void BaoCaoMonBanChay() const
    {
        cout << "\n                                --- Bao cao mon ban chay ---" << endl;
        if (DanhSachDonHang.empty())
        {
            cout << "  Chua co don hang nao de thong ke." << endl;
            return;
        }
        map<string, int> SoLuongMonDaBan;
        map<string, double> DoanhThuTungMonGoc;
        for (const auto &DonHang : DanhSachDonHang)
        {
            for (const auto &ItemPair : DonHang.GetDanhSachMonAn())
            {
                if (ItemPair.first)
                {
                    MenuItem *mon = ItemPair.first;
                    int SoLuong = ItemPair.second;
                    SoLuongMonDaBan[mon->GetTen()] += SoLuong;
                    DoanhThuTungMonGoc[mon->GetTen()] += mon->GetGia() * SoLuong;
                }
            }
        }
        if (SoLuongMonDaBan.empty())
        {
            cout << "  Khong co mon nao duoc ban trong cac don hang da ghi nhan." << endl;
            return;
        }
        vector<pair<string, int>> vecSLMon(SoLuongMonDaBan.begin(), SoLuongMonDaBan.end());
        sort(vecSLMon.begin(), vecSLMon.end(), [](const pair<string, int> &a, const pair<string, int> &b)
             { return a.second > b.second; });
        vector<pair<string, double>> DTMon(DoanhThuTungMonGoc.begin(), DoanhThuTungMonGoc.end());
        sort(DTMon.begin(), DTMon.end(), [](const pair<string, double> &a, const pair<string, double> &b)
             { return a.second > b.second; });
        cout << "\n  --- Top mon an ban chay nhat theo So Luong ---" << endl;
        vector<int> widthsSL = {8, 40, 20};
        VeDuongBienBang(widthsSL);
        VeHangBang({"Hang", "Ten Mon", "So Luong Ban"}, widthsSL);
        VeDuongBienBang(widthsSL);
        for (size_t i = 0; i < vecSLMon.size() && i < 10; ++i)
        {
            VeHangBang({to_string(i + 1), vecSLMon[i].first, to_string(vecSLMon[i].second)}, widthsSL);
        }
        VeDuongBienBang(widthsSL);
        cout << "\n  --- Top mon an co Doanh Thu cao nhat (theo Gia goc) ---" << endl;
        vector<int> widthsDT = {8, 40, 20};
        VeDuongBienBang(widthsDT);
        VeHangBang({"Hang", "Ten Mon", "Doanh Thu (VND)"}, widthsDT);
        VeDuongBienBang(widthsDT);
        for (size_t i = 0; i < DTMon.size() && i < 10; ++i)
        {
            stringstream ss;
            ss << fixed << setprecision(0) << DTMon[i].second;
            VeHangBang({to_string(i + 1), DTMon[i].first, ss.str()}, widthsDT);
        }
        VeDuongBienBang(widthsDT);
    }
    // Hàm này dùng để hiển thị thông tin cửa hàng cho người dùng.
    void XemThongTinCuaHang_User() const
    {
        cout << "\n  --- Thong tin Cua hang Burger ---" << endl;
        cout << "  Chao mung quy khach den voi " << TenCuaHang << " tai " << DiaChiCuaHang << "!" << endl;
        cout << "  Chung toi phuc vu nhung chiec burger ngon nhat va nhieu loai thuc uong hap dan." << endl;
        cout << "  So dien thoai lien he: " << SoDienThoaiCuaHang << endl;
    }
    // Hàm này dùng để hiển thị menu đầy đủ cho người dùng.
    void XemMenu_User()
    {
        HienThiDanhSachMenuDayDu(false);
        if (DanhSachBurger.empty() && DanhSachNuocUong.empty())
            return;
        int LuaChonXemChiTiet = GetInputValidated<int>("  Nhap STT mon an de xem chi tiet (0 de bo qua): ", "Lua chon khong hop le.");
        if (LuaChonXemChiTiet != 0)
        {
            MenuItem *MonAnDuocChon = GetMonAnTheoSTTTongHop(LuaChonXemChiTiet);
            if (MonAnDuocChon)
            {
                cout << "\n  --- Thong tin chi tiet ---" << endl;
                MonAnDuocChon->HienThiThongTin();
            }
            else
            {
                cout << "STT khong hop le." << endl;
            }
        }
    }
    // Hàm này dùng để đặt món cho khách hàng hoặc thành viên.
    void DatMon_User()
    {
        cout << "\n  --- Dat mon ---" << endl;
        if (DanhSachBurger.empty() && DanhSachNuocUong.empty())
        {
            cout << "  Xin loi, menu hien tai trong." << endl;
            return;
        }
        HienThiDanhSachMenuDayDu(false);
        KhachHang KhachHangDatDonHang("", "", "");
        bool LaThanhVienDat = (ThanhVienHienTai != nullptr);
        if (LaThanhVienDat)
        {
            KhachHangDatDonHang = *ThanhVienHienTai;
            cout << "  Dat hang voi tu cach thanh vien: " << ThanhVienHienTai->GetTen() << endl;
        }
        else
        {
            string Ten, sdt, dc;
            cout << "  Vui long nhap thong tin dat hang:" << endl;
            cout << "  Nhap Ten cua ban: ";
            getline(cin, Ten);
            cout << "  Nhap so dien thoai: ";
            getline(cin, sdt);
            cout << "  Nhap dia chi: ";
            getline(cin, dc);
            KhachHangDatDonHang = KhachHang(Ten, sdt, dc);
        }
        DonHang DonMoi(MaDonHangTiepTheo, KhachHangDatDonHang);
        char DatTiep;
        do
        {
            int STTChon = GetInputValidated<int>("  Nhap STT mon an muon dat (0 de hoan tat): ");
            if (STTChon == 0)
                break;
            MenuItem *MonAnDaChon = GetMonAnTheoSTTTongHop(STTChon);
            if (!MonAnDaChon)
            {
                cout << "STT khong hop le." << endl;
                DatTiep = 'y';
                continue;
            }
            int SoLuongDat = GetInputValidated<int>("  Nhap so luong: ");
            if (SoLuongDat <= 0)
            {
                cout << "So luong khong hop le." << endl;
                DatTiep = 'y';
                continue;
            }
            if (SoLuongDat <= MonAnDaChon->GetSoLuong())
            {
                DonMoi.ThemMonAn(MonAnDaChon, SoLuongDat);
                MonAnDaChon->SetSoLuong(MonAnDaChon->GetSoLuong() - SoLuongDat);
                cout << "  Da them " << MonAnDaChon->GetTen() << " vao don hang." << endl;
            }
            else
            {
                cout << "  So luong khong du trong kho. Chi con " << MonAnDaChon->GetSoLuong() << "." << endl;
            }
            DatTiep = GetInputValidated<char>("  Muon dat them mon khac? (y/n): ");
        } while (DatTiep == 'y' || DatTiep == 'Y');
        if (DonMoi.GetDanhSachMonAn().empty())
        {
            cout << "  Don hang trong. Huy bo tao don hang." << endl;
            return;
        }
        DonMoi.TinhLaiTongTienGoc();
        double TongTienTamTinh = DonMoi.GetTongTienGoc();
        double TongTienCuoiCung = TongTienTamTinh;
        cout << "  Tong Gia tien tam tinh: " << fixed << setprecision(0) << TongTienTamTinh << " VND" << endl;
        if (LaThanhVienDat && ThanhVienHienTai)
        {
            const LuaChonDoiDiem *LuaChonGiamGia = nullptr;
            for (const auto &lc : DanhSachLuaChonDoiDiem)
            {
                if (lc.LoaiPhanThuong == "GiamGiaTheoPhanTram" && lc.DiemCanDoi == 1000)
                {
                    LuaChonGiamGia = &lc;
                    break;
                }
            }
            if (LuaChonGiamGia && ThanhVienHienTai->GetDiemTichLuy() >= LuaChonGiamGia->DiemCanDoi)
            {
                char ChonGiamGia = GetInputValidated<char>("  Ban co " + to_string(ThanhVienHienTai->GetDiemTichLuy()) + " diem. Ban co muon dung " + to_string(LuaChonGiamGia->DiemCanDoi) + " diem de " + LuaChonGiamGia->MoTaPhanThuong + " khong? (y/n): ");
                if (ChonGiamGia == 'y' || ChonGiamGia == 'Y')
                {
                    if (ThanhVienHienTai->SuDungDiem(LuaChonGiamGia->DiemCanDoi))
                    {
                        double TienGiam = TongTienCuoiCung * LuaChonGiamGia->GiaTri;
                        TongTienCuoiCung -= TienGiam;
                        cout << "  Da ap dung Giam Gia " << fixed << setprecision(0) << LuaChonGiamGia->GiaTri * 100 << "%. So tien Giam: " << fixed << setprecision(0) << TienGiam << " VND." << endl;
                        cout << "  Diem con lai: " << ThanhVienHienTai->GetDiemTichLuy() << " diem." << endl;
                    }
                }
            }
            if (!ThanhVienHienTai->GetDaMuaLanDau() && TongTienCuoiCung > 0)
            {
                double TienGiamLanDau = TongTienCuoiCung * GiamGiaLanDau;
                TongTienCuoiCung -= TienGiamLanDau;
                cout << "  Ap dung Giam Gia " << fixed << setprecision(0) << GiamGiaLanDau * 100 << "% (tuong duong " << fixed << setprecision(0) << TienGiamLanDau << " VND) cho lan dat dau cua thanh vien!" << endl;
                ThanhVienHienTai->SetDaMuaLanDau(true);
            }
            if (DonMoi.GetDanhSachMonAn().size() >= (size_t)SoLuongLonDeGiamGia && TongTienCuoiCung > 0)
            {
                double TienGiamSLLon = TongTienCuoiCung * GiamGiaSoLuongLon;
                TongTienCuoiCung -= TienGiamSLLon;
                cout << "  Ap dung Giam Gia " << fixed << setprecision(0) << GiamGiaSoLuongLon * 100 << "% (tuong duong " << fixed << setprecision(0) << TienGiamSLLon << " VND) cho don hang so luong lon!" << endl;
            }
            TongTienCuoiCung = (TongTienCuoiCung < 0) ? 0 : TongTienCuoiCung;
            DonMoi.SetTongTienThucTe(TongTienCuoiCung);
            cout << "  Tong tien thanh toan cuoi cung: " << fixed << setprecision(0) << TongTienCuoiCung << " VND" << endl;
            int DiemThuong = (TongTienCuoiCung > 0) ? static_cast<int>(TongTienCuoiCung / GiaTriVNDChoMotDiem) : 0;
            if (DiemThuong > 0)
            {
                ThanhVienHienTai->ThemDiem(DiemThuong);
                cout << "  Ban da duoc cong " << DiemThuong << " diem cho don hang nay." << endl;
            }
            cout << "  Tong diem tich luy hien tai cua ban la: " << ThanhVienHienTai->GetDiemTichLuy() << " diem." << endl;
            char chonDoiQua = GetInputValidated<char>("  Ban co muon dung diem de doi qua tang khong? (y/n): ");
            if (chonDoiQua == 'y' || chonDoiQua == 'Y')
            {
                XemDanhSachLuaChonDoiDiemChoThanhVien(ThanhVienHienTai->GetDiemTichLuy(), "QUA_TANG");
                if (any_of(DanhSachLuaChonDoiDiem.begin(), DanhSachLuaChonDoiDiem.end(),
                           [&](const LuaChonDoiDiem &lc)
                           { return lc.LoaiPhanThuong == "QUA_TANG" && ThanhVienHienTai->GetDiemTichLuy() >= lc.DiemCanDoi; }))
                {

                    int IDLuaChonQua = GetInputValidated<int>("  Nhap ID qua tang muon doi (0 de bo qua): ");
                    if (IDLuaChonQua > 0)
                    {
                        const LuaChonDoiDiem *LuaChonQuaDaChon = nullptr;
                        for (const auto &lc : DanhSachLuaChonDoiDiem)
                        {
                            if (lc.Id == IDLuaChonQua && lc.LoaiPhanThuong == "QUA_TANG" && ThanhVienHienTai->GetDiemTichLuy() >= lc.DiemCanDoi)
                            {
                                LuaChonQuaDaChon = &lc;
                                break;
                            }
                        }
                        if (LuaChonQuaDaChon)
                        {
                            if (ThanhVienHienTai->SuDungDiem(LuaChonQuaDaChon->DiemCanDoi))
                            {
                                DonMoi.ThemQuaTangDaDoi(LuaChonQuaDaChon->MoTaPhanThuong);
                                cout << "  Ban da doi " << LuaChonQuaDaChon->DiemCanDoi << " diem de nhan: " << LuaChonQuaDaChon->MoTaPhanThuong << endl;
                                cout << "  So diem con lai: " << ThanhVienHienTai->GetDiemTichLuy() << " diem." << endl;
                            }
                        }
                        else
                        {
                            cout << "  Lua chon qua tang khong hop le hoac ban khong du diem." << endl;
                        }
                    }
                }
            }
        }
        else
        {
            DonMoi.SetTongTienThucTe(TongTienCuoiCung);
            cout << "  Tong tien thanh toan: " << fixed << setprecision(0) << TongTienCuoiCung << " VND" << endl;
        }
        DanhSachDonHang.push_back(DonMoi);
        MaDonHangTiepTheo++;
        cout << "  Da tao don hang #" << DonMoi.GetMaDonHang() << " thanh cong!" << endl;
    }
    // Hàm này dùng để xem thông tin tài khoản của người dùng (thành viên).
    void XemThongTinTaiKhoan_User()
    {
        if (ThanhVienHienTai)
        {
            cout << "\n  --- Thong tin tai khoan cua ban ---" << endl;
            ThanhVienHienTai->HienThiThongTin();
        }
        else
        {
            cout << "  Ban chua dang nhap. Vui long dang nhap de xem thong tin tai khoan." << endl;
            cout << "  Khach vang lai khong co tai khoan luu tru." << endl;
        }
    }
};

int main()
{
    CuaHangBurger CuaHang;
    int LuaChonBanDau;
    const int MenuWidth = 70;
    do
    {
        cout << "\n";
        VeDuongNgang(MenuWidth, '*');
        cout << string((MenuWidth - 44) / 2, ' ') << "***** PHAN MEM QUAN LY CUA HANG BURGER *****" << endl;
        VeDuongNgang(MenuWidth, '*');
        cout << "* " << setw((MenuWidth - 30) / 2) << ""
             << "CHAO MUNG DEN VOI CUA HANG!" << setw((MenuWidth - 28) / 2) << right << " *" << endl;
        cout << "* " << setw((MenuWidth - 26) / 2) << ""
             << "1. Dang nhap Quan Ly" << setw((MenuWidth - 18) / 2) << right << " *" << endl;
        cout << "* " << setw((MenuWidth - 26) / 2) << ""
             << "2. Dang nhap Thanh Vien" << setw((MenuWidth - 24) / 2) << right << " *" << endl;
        cout << "* " << setw((MenuWidth - 26) / 2) << ""
             << "3. Dang ky Thanh Vien moi" << setw((MenuWidth - 28) / 2) << right << " *" << endl;
        cout << "* " << setw((MenuWidth - 26) / 2) << ""
             << "4. Khach mua nhanh" << setw((MenuWidth - 14) / 2) << right << " *" << endl;
        cout << "* " << setw((MenuWidth - 26) / 2) << ""
             << "0. Thoat ung dung" << setw((MenuWidth - 12) / 2) << right << " *" << endl;
        VeDuongNgang(MenuWidth, '*');
        LuaChonBanDau = GetInputValidated<int>("  Nhap lua chon cua ban: ", "  Lua chon khong hop le. Vui long nhap so.");
        switch (LuaChonBanDau)
        {
        case 1:
            if (CuaHang.DangNhapAdmin())
            {
                int LuaChonQuanLy;
                do
                {
                    cout << "\n";
                    VeDuongNgang(MenuWidth, '-');
                    cout << string((MenuWidth - 26) / 2, ' ') << "--- CHUC NANG QUAN LY ---" << endl;
                    VeDuongNgang(MenuWidth, '-');
                    cout << "  1. Nhap/Cap nhat thong tin cua hang\n"
                         << "  2. Them burger\n"
                         << "  3. Them nuoc uong\n"
                         << "  4. Xem danh sach menu\n"
                         << "  5. Chinh sua mon an\n"
                         << "  6. Xoa mon an\n"
                         << "  7. Xem danh sach don hang\n"
                         << "  8. Them don hang (cho khach/thanh vien)\n"
                         << "  9. Xoa don hang\n"
                         << "  10. Them nhan vien\n"
                         << "  11. Xem danh sach nhan vien\n"
                         << "  12. Chinh sua nhan vien\n"
                         << "  13. Xoa nhan vien\n"
                         << "  14. Xem danh sach thanh vien\n"
                         << "  15. Bao cao doanh thu\n"
                         << "  16. Bao cao mon ban chay\n"
                         << "  0. Thoat khoi menu quan ly (Se dang xuat)" << endl;
                    LuaChonQuanLy = GetInputValidated<int>("  Nhap lua chon cua ban: ");
                    switch (LuaChonQuanLy)
                    {
                    case 1:
                        CuaHang.NhapThongTinCuaHang();
                        break;
                    case 2:
                        CuaHang.ThemMonAn(true);
                        break;
                    case 3:
                        CuaHang.ThemMonAn(false);
                        break;
                    case 4:
                        CuaHang.HienThiDanhSachMenuDayDu(true);
                        break;
                    case 5:
                        CuaHang.ChinhSuaMonAn();
                        break;
                    case 6:
                        CuaHang.XoaMonAn();
                        break;
                    case 7:
                        CuaHang.HienThiDanhSachDonHang();
                        break;
                    case 8:
                        CuaHang.ThemDonHangChoKhachHoacThanhVien();
                        break;
                    case 9:
                        CuaHang.XoaDonHang();
                        break;
                    case 10:
                        CuaHang.ThemNhanVien();
                        break;
                    case 11:
                        CuaHang.XemDanhSachNhanVien();
                        break;
                    case 12:
                        CuaHang.ChinhSuaNhanVien();
                        break;
                    case 13:
                        CuaHang.XoaNhanVien();
                        break;
                    case 14:
                        CuaHang.HienThiDanhSachThanhVien();
                        break;
                    case 15:
                        CuaHang.BaoCaoDoanhThu();
                        break;
                    case 16:
                        CuaHang.BaoCaoMonBanChay();
                        break;
                    case 0:
                        CuaHang.DangXuat();
                        cout << "  Da dang xuat va quay lai menu chinh." << endl;
                        break;
                    default:
                        cout << "  Lua chon khong hop le." << endl;
                    }
                    if (LuaChonQuanLy != 0)
                    {
                        cout << "\n  Nhan Enter de tiep tuc...";
                        cin.get();
                    }
                } while (LuaChonQuanLy != 0);
            }
            break;
        case 2:
            if (CuaHang.DangNhapThanhVien())
            {
                int LuaChonThanhVien;
                do
                {
                    cout << "\n";
                    VeDuongNgang(MenuWidth, '-');
                    cout << string((MenuWidth - 30) / 2, ' ') << "--- CHUC NANG THANH VIEN ---" << endl;
                    VeDuongNgang(MenuWidth, '-');
                    cout << "  1. Xem thong tin cua hang\n  2. Xem menu\n  3. Dat mon\n  4. Xem thong tin tai khoan va diem\n  5. Thay doi thong tin ca nhan\n  0. Thoat khoi menu thanh vien (Se dang xuat)" << endl;
                    LuaChonThanhVien = GetInputValidated<int>("  Nhap lua chon cua ban: ");
                    switch (LuaChonThanhVien)
                    {
                    case 1:
                        CuaHang.XemThongTinCuaHang_User();
                        break;
                    case 2:
                        CuaHang.XemMenu_User();
                        break;
                    case 3:
                        CuaHang.DatMon_User();
                        break;
                    case 4:
                        CuaHang.XemThongTinTaiKhoan_User();
                        break;
                    case 5:
                        CuaHang.ThayDoiThongTinCaNhan();
                        break;
                    case 0:
                        CuaHang.DangXuat();
                        cout << "  Da dang xuat va quay lai menu chinh." << endl;
                        break;
                    default:
                        cout << "  Lua chon khong hop le." << endl;
                    }
                    if (LuaChonThanhVien != 0)
                    {
                        cout << "\n  Nhan Enter de tiep tuc...";
                        cin.get();
                    }
                } while (LuaChonThanhVien != 0);
            }
            break;
        case 3:
            CuaHang.DangKyThanhVien();
            cout << "\n  Nhan Enter de quay lai menu chinh...";
            cin.get();
            break;
        case 4:
        {
            int LuaChonKhach;
            do
            {
                cout << "\n";
                VeDuongNgang(MenuWidth, '-');
                cout << string((MenuWidth - 28) / 2, ' ') << "--- CHUC NANG KHACH HANG ---" << endl;
                VeDuongNgang(MenuWidth, '-');
                cout << "  1. Xem thong tin cua hang\n  2. Xem menu\n  3. Dat mon\n  0. Quay lai menu chinh" << endl;
                LuaChonKhach = GetInputValidated<int>("  Nhap lua chon cua ban: ");
                switch (LuaChonKhach)
                {
                case 1:
                    CuaHang.XemThongTinCuaHang_User();
                    break;
                case 2:
                    CuaHang.XemMenu_User();
                    break;
                case 3:
                    CuaHang.DatMon_User();
                    break;
                case 0:
                    cout << "  Quay lai menu chinh." << endl;
                    break;
                default:
                    cout << "  Lua chon khong hop le." << endl;
                }
                if (LuaChonKhach != 0)
                {
                    cout << "\n  Nhan Enter de tiep tuc...";
                    cin.get();
                }
            } while (LuaChonKhach != 0);
        }
        break;
        case 0:
            cout << "  Xin cam on ban da su dung dich vu!" << endl;
            cout << "  Hen gap lai!" << endl;
            break;
        default:
            cout << "  Lua chon khong hop le. Vui long thu lai." << endl;
            cout << "\n  Nhan Enter de thu lai...";
            cin.get();
        }
    } while (LuaChonBanDau != 0);
    return 0;
}