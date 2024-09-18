#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Node {
    string maBan;
    string trangThai;
    string tenDoUong;
    int soLuong;
    double donGia;
    double thanhTien;
    string phuongThucThanhToan;
    Node* left;
    Node* right;

    Node(string maban, string trangthai, string tendouong, int soluong, double dongia, double thanhtien, string phuongthucthanhtoan)
        : maBan(maban), trangThai(trangthai), tenDoUong(tendouong), soLuong(soluong), donGia(dongia), thanhTien(thanhtien), phuongThucThanhToan(phuongthucthanhtoan), left(nullptr), right(nullptr) {}
};

// Hàm tạo node mới
Node* createNode(string maban, string trangthai, string tendouong, int soluong, double dongia, double thanhtien, string phuongthucthanhtoan) {
    return new Node(maban, trangthai, tendouong, soluong, dongia, thanhtien, phuongthucthanhtoan);
}

// Hàm chèn node vào BST
Node* insert(Node* root, Node* newNode) {
    if (root == nullptr) return newNode;
    if (newNode->maBan < root->maBan) {
        root->left = insert(root->left, newNode);
    }
    else if (newNode->maBan > root->maBan) {
        root->right = insert(root->right, newNode);
    }
    return root;
}

// Hàm xuất danh sách thông tin các bàn
void printInOrder(Node* root) {
    if (root != nullptr) {
        printInOrder(root->left);
        cout << "Ma ban: " << root->maBan << endl;
        cout << "Trang thai: " << root->trangThai << endl;
        cout << "Ten do uong: " << root->tenDoUong << endl;
        cout << "So luong: " << root->soLuong << endl;
        cout << "Don gia: " << root->donGia << endl;
        cout << "Thanh tien: " << root->thanhTien << endl;
        cout << "Phuong thuc thanh toan: " << root->phuongThucThanhToan << endl;
        cout << "-----------------------------------" << endl;
        printInOrder(root->right);
    }
}

// Hàm đếm số lượng bàn có khách
int countOccupied(Node* root) {
    if (root == nullptr) return 0;
    int count = (root->trangThai == "co khach") ? 1 : 0;
    return count + countOccupied(root->left) + countOccupied(root->right);
}

// Hàm tìm kiếm bàn theo mã
Node* search(Node* root, const string& maBan) {
    if (root == nullptr || root->maBan == maBan) return root;
    if (maBan < root->maBan) return search(root->left, maBan);
    return search(root->right, maBan);
}

// Hàm xuất thông tin các bàn có khách
void printOccupied(Node* root) {
    if (root != nullptr) {
        printOccupied(root->left);
        if (root->trangThai == "co khach") {
            cout << "Ma ban: " << root->maBan << endl;
            cout << "Trang thai: " << root->trangThai << endl;
            cout << "Ten do uong: " << root->tenDoUong << endl;
            cout << "So luong: " << root->soLuong << endl;
            cout << "Don gia: " << root->donGia << endl;
            cout << "Thanh tien: " << root->thanhTien << endl;
            cout << "Phuong thuc thanh toan: " << root->phuongThucThanhToan << endl;
            cout << "-----------------------------------" << endl;
        }
        printOccupied(root->right);
    }
}

// Hàm xóa tất cả các bàn trạng thái trống và đã thanh toán
Node* deleteEmptyAndPaid(Node* root) {
    if (root == nullptr) return nullptr;
    root->left = deleteEmptyAndPaid(root->left);
    root->right = deleteEmptyAndPaid(root->right);

    if (root->trangThai == "trong" && root->phuongThucThanhToan == "da thanh toan") {
        delete root;
        return nullptr;
    }
    return root;
}

int main() {
    Node* root = nullptr;
    int n;
    cout << "Nhap so luong ban: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string maban, trangthai, tendouong, phuongthucthanhtoan;
        int soluong;
        double dongia, thanhtien;

        cout << "Nhap thong tin ban thu " << i + 1 << ":" << endl;
        cout << "Ma ban: ";
        cin >> maban;
        cin.ignore();
        cout << "Trang thai (trong/co khach): ";
        getline(cin, trangthai);
        cout << "Ten do uong: ";
        getline(cin, tendouong);
        cout << "So luong: ";
        cin >> soluong;
        cout << "Don gia: ";
        cin >> dongia;
        cout << "Thanh tien: ";
        cin >> thanhtien;
        cin.ignore();
        cout << "Phuong thuc thanh toan: ";
        getline(cin, phuongthucthanhtoan);

        Node* newNode = createNode(maban, trangthai, tendouong, soluong, dongia, thanhtien, phuongthucthanhtoan);
        root = insert(root, newNode);
    }

    cout << "\nDanh sach thong tin cac ban:\n";
    printInOrder(root);

    cout << "\nSo luong ban co khach: " << countOccupied(root) << endl;

    string maBanToSearch;
    cout << "\nNhap ma ban de tim kiem: ";
    cin >> maBanToSearch;
    Node* found = search(root, maBanToSearch);
    if (found) {
        cout << "Thong tin ban:\n";
        cout << "Ma ban: " << found->maBan << endl;
        cout << "Trang thai: " << found->trangThai << endl;
        cout << "Ten do uong: " << found->tenDoUong << endl;
        cout << "So luong: " << found->soLuong << endl;
        cout << "Don gia: " << found->donGia << endl;
        cout << "Thanh tien: " << found->thanhTien << endl;
        cout << "Phuong thuc thanh tosn: " << found->phuongThucThanhToan << endl;
    }
    else {
        cout << "Khong tim thay ban voi ma: " << maBanToSearch << endl;
    }

    cout << "\nThong tin cac ban co khach:\n";
    printOccupied(root);

    root = deleteEmptyAndPaid(root);

    cout << "\nDanh sach thong tin cac ban sau khi xoa cac ban trong va da thanh toan:\n";
    printInOrder(root);

    return 0;
}
