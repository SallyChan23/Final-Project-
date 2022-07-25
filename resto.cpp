#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct detilPesanan {
    char namaMakanan[51];
    int diskon;
    long hargaMakanan;
    int jmlPesanan;
    long long totalHargaMakanan;
};

int totalOrder = 0;

struct headerPesanan {
    char id[7];
    char namaPemesan[51];
    double beratBadan;
    detilPesanan pesanan;
}order[101];

void merge(struct headerPesanan arr[], int left, int mid, int right, int pilihmenu) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // temporary array
    struct headerPesanan L[n1], R[n2];

    // fill temporary array
    for(int i = 0; i < n1; i++) {
        L[i] = arr[left+i];
    }
    for(int i = 0; i < n2; i++) {
        R[i] = arr[mid+i+1];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while(i < n1 && j < n2) {
        if (pilihmenu == 1) {
            if(L[i].pesanan.totalHargaMakanan <= R[j].pesanan.totalHargaMakanan) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
        }
        else if (pilihmenu == 2) {
            if(L[i].pesanan.totalHargaMakanan >= R[j].pesanan.totalHargaMakanan) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
        }
        else if (pilihmenu == 3) {
            if(strcmp(L[i].namaPemesan, R[j].namaPemesan) < 0) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
        }
        k++;
    }

    while(i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    return;
}

void mergeSort(struct headerPesanan arr[], int left, int right, int pilihmenu) {
    if(left < right) {
        int mid = left + (right-left) / 2;
        mergeSort(arr, left, mid, pilihmenu);
        mergeSort(arr, mid+1, right, pilihmenu);
        merge(arr, left, mid, right, pilihmenu);
    }
}

bool fileKosong;
void readFile() {
    FILE *fp = fopen("pesanan.txt", "r");
    int i = 0;
    if(fp == NULL) {
		fileKosong = true;
	}
    else {
		while(!feof(fp)){
		    fscanf(fp, "%[^-]-%[^-]-%lf-%[^-]-%d-%ld-%lld\n", order[i].id, order[i].namaPemesan, &order[i].beratBadan, order[i].pesanan.namaMakanan, &order[i].pesanan.hargaMakanan, &order[i].pesanan.jmlPesanan, &order[i].pesanan.totalHargaMakanan);
		    i++;
		}
	}
    totalOrder = i;
	fclose(fp);
}

void printPesanan() {
    system("cls");
    puts("=========================================================================================================");
    puts("| ID | Nama Pemesan | Berat Badan | Nama Makanan | Harga Makanan | Jumlah Pesanan | Total Harga Makanan |");
    puts("=========================================================================================================");
    for (int i = 0; i < totalOrder; i++) {
        printf("| %-3s| %-13s| %-12.2lf| %-13s| Rp %-10ld | %-15d| Rp %-17lld|\n", order[i].id, order[i].namaPemesan, order[i].beratBadan, order[i].pesanan.namaMakanan, order[i].pesanan.hargaMakanan, order[i].pesanan.jmlPesanan, order[i].pesanan.totalHargaMakanan);
    }
    puts("=========================================================================================================");
}

void lihatPesanan() {
    fileKosong = false;
    readFile();
    int pilihmenu;
    system("cls");
    if (fileKosong) {
        printf("File pesanan.txt not found!\n");
        system("pause");
    }
    else {
        do {
            system("cls");
            puts("[1] Ascending (Total Harga)");
            puts("[2] Descending (Total Harga)");
            puts("[3] Go Back");
            printf(">> ");
            scanf("%d", &pilihmenu); getchar();
            switch (pilihmenu)
            {
            case 1:
                mergeSort(order, 0, totalOrder-1, pilihmenu);
                printPesanan();
                system("pause");
                break;

            case 2:
                mergeSort(order, 0, totalOrder-1, pilihmenu);
                printPesanan();
                system("pause");
                break;
            
            default:
                break;
            }
        } while (pilihmenu != 3);
    }
}

void tambahPesanan() {
    system("cls");

    char namaPemesan[51];
    int lenNama;
    do {
        printf("Masukkan nama pemesan [3 - 15 karakter]: ");
        scanf("%[^\n]", namaPemesan); getchar();
        lenNama = strlen(namaPemesan);
    } while (lenNama < 3 || lenNama > 15);

    double beratBadan = 0;
    do {
        printf("Masukkan berat badan pemesan: ");
        scanf("%lf", &beratBadan); getchar();
    } while (beratBadan <= 0);
    
    char namaMakanan[51];
    printf("Masukkan nama makanan: ");
    scanf("%[^\n]", namaMakanan); getchar();

    int jmlPesanan = 0;
    do {
        printf("Masukkan jumlah pesanan: ");
        scanf("%d", &jmlPesanan); getchar();
    } while (jmlPesanan <= 0);

    int diskon;
    if (beratBadan <= 50) diskon = 25000 * 50 / 100;
    else if (beratBadan <= 70 && beratBadan > 50) diskon = 25000 * 25 / 100;
    else if (beratBadan <= 100 && beratBadan > 70) diskon = 25000 * 10 / 100;

    long hargaMakanan = 25000 - diskon;

    long long totalHargaMakanan = hargaMakanan * jmlPesanan;

    char id[6];
    strcpy(id, "RP");

    FILE *fp = fopen("pesanan.txt", "a");
    fprintf(fp, "%s-%s-%.2lf-%s-%ld-%d-%lld\n", id, namaPemesan, beratBadan, namaMakanan, hargaMakanan, jmlPesanan, totalHargaMakanan);
    fclose(fp);
    puts("Pesanan telah terdaftar!");
    system("pause");
}

int binarySearch(struct headerPesanan arr[], int l, int r, char search[]) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
  
        if (strcmp(arr[mid].namaPemesan, search) == 0) return mid;
        return (strcmp(arr[mid].namaPemesan, search) > 0) ? binarySearch(arr, l, mid - 1, search) : binarySearch(arr, mid + 1, r, search);
    }

    return -1;
}

void hapusPesanan() {
    fileKosong = false;
    readFile();
    int pilihmenu;
    system("cls");
    if (fileKosong) {
        printf("File pesanan.txt not found!\n");
        system("pause");
    }
    else {
        mergeSort(order, 0, 2, 3);
        char search[51];
        printPesanan();
        puts("");
        printf("Search Name To Delete: ");
        scanf("%[^\n]", search); getchar();
        int result = binarySearch(order, 0, totalOrder-1, search);
        if (result == -1) {
            printf("Name not found!\n");
            system("pause");
        }
        else {
            printf("Deleted!\n");
            strcpy(order[result].namaPemesan, "");
            system("pause");
            FILE *fp = fopen("pesanan.txt", "w");
            for (int i = 0; i < totalOrder; i++) {
                if (strcmp(order[i].namaPemesan, "") != 0) {
                    fprintf(fp, "%s-%s-%.2lf-%s-%ld-%d-%lld\n", order[i].id, order[i].namaPemesan, order[i].beratBadan, order[i].pesanan.namaMakanan, order[i].pesanan.hargaMakanan, order[i].pesanan.jmlPesanan, order[i].pesanan.totalHargaMakanan);
                }
            }
            fclose(fp);
        }
    }
}

int main() {
    int pilihmenu;
    do {
        system("cls");
        printf("Welcome to Resto Pejuang IT\n");
        printf("=============================\n");
        printf("[1] Lihat Semua Pesanan\n");
        printf("[2] Tambah Pesanan\n");
        printf("[3] Hapus Pesanan\n");
        printf("[4] Exit\n");
        printf(">> ");
        scanf("%d", &pilihmenu); getchar();
        switch (pilihmenu) {
        case 1:
            lihatPesanan();
            break;
        case 2:
            tambahPesanan();
            break;
        case 3:
            hapusPesanan();
            break;
        default:
            break;
        }
    } while (pilihmenu != 4);
    
    return 0;
}