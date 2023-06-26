#include <stdio.h>
#include <stdlib.h>


enum Sube {a1 = 1, b1, c1, d1};
enum Cinsiyet {Erkek = 1, kadin};


struct ogrenci {
    size_t TCKN;
    enum Sube sube;
    char Adi[20];
    char Soyadi[20];
    enum Cinsiyet cinsiyet;
    float DersOrtalamasi;
};


void BilgiYaz(struct ogrenci); //Öğrenci bilgileri bir dosyaya yazmak için kullanılan fonksiyon
struct ogrenci BilgiOku(int); // Verilen sınıddtaki en yüsek ortalama notu olan öğrenciyi bir dosyadan okuyan fonksiyon
void sonucuYaz(float[], int, int); // verilen sınıftaki ikinci ve üçüncü en yüksek notları hesaplayıp bir disiye kaydeden fonksiyon


int main() {
    struct ogrenci DiziOgrenci;
    struct ogrenci **ptrogr;
    ptrogr = (struct ogrenci **)malloc(4 * sizeof(struct ogrenci *));
    if (ptrogr == NULL) {
        printf("Basarsiz! bellek ayrilamadi");
        exit(1);
    }
    for (int i = 0; i < 4; ++i) {
        *(ptrogr + i) = (struct ogrenci *)malloc(10 * sizeof(struct ogrenci));
        if (*(ptrogr + i) == NULL) {
            printf("Basarsiz! bellek ayrilamadi");
            exit(1);
        }
    }
    char karar;
    do {
        printf("lutfen TCKN, Sube, Adi, Soyadi, Cinsiyet( Erkek=1,Kadin=2), Ders Ortalamasi sekleide enter basarak giriniz:");
        getchar();
        scanf("%zu %d %[^\n]%*c %s %d %f", &DiziOgrenci.TCKN, &DiziOgrenci.sube,DiziOgrenci.Adi,
              DiziOgrenci.Soyadi, &DiziOgrenci.cinsiyet, &DiziOgrenci.DersOrtalamasi);
        printf("Devam etmek istiyor musunuz (e/E veya h/H)?");
        scanf(" %c", &karar);
        BilgiYaz(DiziOgrenci);
    } while (karar == 'e' || karar == 'E');
    for (int i = 0; i < 1; ++i) {
        struct ogrenci eyp;
        eyp = BilgiOku(i + 1);
        printf("\n%d. subesindeki %s %s (%s olan) en yuksek puani: %.2f\n", i + 1, eyp.Adi, eyp.Soyadi, (eyp.cinsiyet == 1) ? "Erkek" : "Kadin", eyp.DersOrtalamasi);
    }
    float ivueup[2];
    sonucuYaz(ivueup, 2,   1);
    printf("%d. subesindeki ikinci en yuksek puani: %.2f\n", 1, ivueup[0]);
    printf("%d. subesindeki ucuncu en yuksek puani: %.2f\n",   1, ivueup[1]);
    return 0;
}


void BilgiYaz(struct ogrenci ogr) {
    FILE *file = fopen("ogrenci.db", "ab");
    if (file == NULL) {
        printf("Dosya olusturulamadi");
        exit(1);
    }
    fprintf(file, "%zu %d %s %s %d %f\n", ogr.TCKN, ogr.sube, ogr.Adi, ogr.Soyadi, ogr.cinsiyet, ogr.DersOrtalamasi);
    fclose(file);
}


struct ogrenci BilgiOku(int sube) {
    FILE *file = fopen("ogrenci.db", "rb");
    if (file == NULL) {
        printf("Dosya okunamadi!");
        exit(1);
    }
    struct ogrenci eyp;
    struct ogrenci ogr;
    eyp.DersOrtalamasi = -1;
    while (!feof(file)) {
        getchar();
        fscanf(file, "%zu %d %[^\n]%*c %s %d %f", &ogr.TCKN, &ogr.sube, ogr.Adi, ogr.Soyadi, &ogr.cinsiyet, &ogr.DersOrtalamasi);
        if (ogr.sube == sube) {
            if (ogr.DersOrtalamasi > eyp.DersOrtalamasi) {
                eyp = ogr;
            }
        }
    }
    fclose(file);
    return eyp;
}
void sonucuYaz(float arr[], int size, int sube) {
    float DiziOrtalamalari[10];
    FILE* file = fopen("ogrenci.db", "rb");
    if (file == NULL) {
        printf("Dosya okunamadi!");
        exit(1);
    }
    struct ogrenci ogr;
    int i = 0;
    while (!feof(file)) {
        getchar();
        if (fscanf(file, "%zu %d %[^\n]%*c %s %d %f", &ogr.TCKN, (int*)&ogr.sube, ogr.Adi, ogr.Soyadi, (int*)&ogr.cinsiyet, &ogr.DersOrtalamasi) == 6) {
            if (ogr.sube == sube) {
                DiziOrtalamalari[i++] = ogr.DersOrtalamasi;
            }
        }
    }
    fclose(file);
    float eyp = -1;
    float Ieup = -1;
    float Ueyp = -1;
    for (int j = 0; j < i; ++j) {
        if (DiziOrtalamalari[j] > eyp) {
            Ueyp = Ieup;
            Ieup = eyp;
            eyp = DiziOrtalamalari[j];
        } else if (DiziOrtalamalari[j] > Ieup) {
            Ieup = DiziOrtalamalari[j];
        } else if (DiziOrtalamalari[j] > Ueyp) {
            Ueyp = DiziOrtalamalari[j];
        }
    }
    if (size > 0)
        arr[0] = (Ieup != -1) ? Ieup : 0;
    if (size > 1)
        arr[1] = (Ueyp != -1) ? Ueyp : 0;
}
