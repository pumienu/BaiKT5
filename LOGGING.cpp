#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

class GhiLog {
public:
    GhiLog(const string& tenTepTin) {
        tepTinLog.open(tenTepTin, ios::out | ios::app);
        if (!tepTinLog.is_open()) {
            cerr << "Loi mo tep tin log: " << tenTepTin << endl;
        }
    }

    ~GhiLog() {
        if (tepTinLog.is_open()) {
            tepTinLog.close();
        }
    }

    void ghiLog(const string& thongDiep) {
        ghiLog("LOG", thongDiep);
    }

    void ghiDebug(const string& thongDiep) {
        ghiLog("DEBUG", thongDiep);
    }

    void ghiThongTin(const string& thongDiep) {
        ghiLog("THONG_TIN", thongDiep);
    }

    void ghiLoi(const string& thongDiep) {
        ghiLog("LOI", thongDiep);
    }

private:
    ofstream tepTinLog;

    void ghiLog(const string& capDo, const string& thongDiep) {
        time_t thoiGianHienTai = time(0);
        tm* thongTinThoiGian = localtime(&thoiGianHienTai);
        char timestamp[80];
        strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S] ", thongTinThoiGian);

        cout << timestamp << "[" << capDo << "] " << thongDiep << endl;

        if (tepTinLog.is_open()) {
            tepTinLog << timestamp << "[" << capDo << "] " << thongDiep << endl;
            tepTinLog.flush();
        }
    }
};

class MaTran {
private:
    int m; // số hàng
    int n; // số cột
    double elements[100][100];

public:
    MaTran() {
        m = 0;
        n = 0;
    }

    int getSoHang() const {
        return m;
    }

    int getSoCot() const {
        return n;
    }

    MaTran operator+(const MaTran& a) const {
        GhiLog logger("logfile.txt");
        logger.ghiLog("Thuc hien phep cong ma tran.");
        return performOperation(a, "+");
    }

    MaTran operator-(const MaTran& a) const {
        GhiLog logger("logfile.txt");
        logger.ghiLog("Thuc hien phep tru ma tran.");
        return performOperation(a, "-");
    }

    MaTran operator*(const MaTran& a) const {
        GhiLog logger("logfile.txt");
        logger.ghiLog("Thuc hien phep nhan ma tran.");
        return performOperation(a, "*");
    }

    MaTran operator/(const MaTran& a) const {
        GhiLog logger("logfile.txt");
        logger.ghiLog("Thuc hien phep chia ma tran.");
        return performOperation(a, "/");
    }

    void nhap() {
        cout << "Nhap so hang: ";
        cin >> m;
        cout << "Nhap so cot: ";
        cin >> n;

        cout << "Nhap cac phan tu cua ma tran:" << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << "Nhap phan tu thu [" << i << "][" << j << "]: ";
                cin >> elements[i][j];
            }
        }
    }

    void xuat() const {
        cout << "Ma tran:" << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << elements[i][j] << " ";
            }
            cout << endl;
        }
    }

private:
    MaTran performOperation(const MaTran& a, const string& operation) const {
        if (m != a.getSoHang() || n != a.getSoCot()) {
            GhiLog logger("logfile.txt");
            logger.ghiLoi("Loi: Kich thuoc khong phu hop!");
            return MaTran(); // Trả về ma trận rỗng nếu không thể thực hiện phép toán
        }

        MaTran result;
        result.m = m;
        result.n = n;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (operation == "+") {
                    result.elements[i][j] = elements[i][j] + a.elements[i][j];
                } else if (operation == "-") {
                    result.elements[i][j] = elements[i][j] - a.elements[i][j];
                } else if (operation == "*") {
                    result.elements[i][j] = elements[i][j] * a.elements[i][j];
                } else if (operation == "/") {
                    if (a.elements[i][j] != 0) {
                        result.elements[i][j] = elements[i][j] / a.elements[i][j];
                    } else {
                        // Xu ly chia cho 0
                        GhiLog logger("logfile.txt");
                        logger.ghiLoi("Loi: Chia cho 0!");
                        result.elements[i][j] = 0; // hoac gan mot gia tri mac dinh khac
                    }
                }
            }
        }

        return result;
    }
};

int main() {
    MaTran mt1, mt2;

    cout << "Nhap ma tran 1:" << endl;
    mt1.nhap();

    cout << "Nhap ma tran 2:" << endl;
    do {
        mt2.nhap();
        if (mt2.getSoHang() != mt1.getSoHang() || mt2.getSoCot() != mt1.getSoCot()) {
            cout << "Loi: Kich thuoc ma tran 2 khong phu hop. Nhap lai:" << endl;
        }
    } while (mt2.getSoHang() != mt1.getSoHang() || mt2.getSoCot() != mt1.getSoCot());

    cout << "Ma tran 1:" << endl;
    mt1.xuat();

    cout << "Ma tran 2:" << endl;
    mt2.xuat();

    cout << "Ket qua Cong:" << endl;
    MaTran ketQuaCong = mt1 + mt2;
    if (ketQuaCong.getSoHang() != 0 && ketQuaCong.getSoCot() != 0) {
        ketQuaCong.xuat();
    }

    cout << "Ket qua Tru:" << endl;
    MaTran ketQuaTru = mt1 - mt2;
    if (ketQuaTru.getSoHang() != 0 && ketQuaTru.getSoCot() != 0) {
        ketQuaTru.xuat();
    }

    cout << "Ket qua Nhan:" << endl;
    MaTran ketQuaNhan = mt1 * mt2;
    if (ketQuaNhan.getSoHang() != 0 && ketQuaNhan.getSoCot() != 0) {
        ketQuaNhan.xuat();
    }

    cout << "Ket qua Chia:" << endl;
    MaTran ketQuaChia = mt1 / mt2;
    if (ketQuaChia.getSoHang() != 0 && ketQuaChia.getSoCot() != 0) {
        ketQuaChia.xuat();
    }

    return 0;
}
