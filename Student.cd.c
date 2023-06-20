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


void BilgiYaz(struct ogrenci); // Öğrenci bilgilerini bir dosyaya yazmak için kullanılan fonksiyon
struct ogrenci BilgiOku(int); // Verilen sınıftaki en yüksek ortalama notu olan öğrenciyi bir dosyadan okuyan fonksiyon
void sonucuYaz(float[], int, int); // Verilen sınıftaki ikinci ve üçüncü en yüksek notları hesaplayıp bir diziye kaydeden fonksiyon


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
    int karar;
    do {
        printf("lutfen TCKN, Sube, Adi, Soyadi, Cinsiyet( Erkek=1,Kadin=2), Ders Ortalamasi sekleide enter basarak giriniz:");
        scanf("%ld %d %s %s %d %f", &DiziOgrenci.TCKN, &DiziOgrenci.sube,&DiziOgrenci.Adi,
              &DiziOgrenci.Soyadi, &DiziOgrenci.cinsiyet, &DiziOgrenci.DersOrtalamasi);
        printf("------------------\n");
        printf("Devam etmek istiyor musunuz (e/E veya h/H)?");
        scanf(" %c", &karar);
        BilgiYaz(DiziOgrenci);
    } while (karar == 'e' || karar == 'E');
    for (int i = 0; i < 1; ++i) {
        struct ogrenci eyp;
        eyp = BilgiOku(i + 1);
        printf("\n%d. subesindeki %s %s (%s olan) en yuksek puani: %.2f\n", i + 1, eyp.Adi, eyp.Soyadi, (eyp.cinsiyet == 1) ? "Erkek" : "Kadin", eyp.DersOrtalamasi);
        float ivueup[2];
        sonucuYaz(ivueup, 2, i + 1);
        printf("%d. subesindeki ikinci en yuksek puani: %.2f\n", i + 1, ivueup[0]);
        printf("%d. subesindeki ucuncu en yuksek puani: %.2f\n", i + 1, ivueup[1]);
    }
    return 0;
}


void BilgiYaz(struct ogrenci ogr) {
    FILE *file = fopen("ogrenci.db", "ab");
    if (file == NULL) {
        printf("Dosya olusturulamadi");
        exit(1);
    }
    fprintf(file, "%ld %d %s %s %d %f\n", ogr.TCKN, ogr.sube, ogr.Adi, ogr.Soyadi, ogr.cinsiyet, ogr.DersOrtalamasi);
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
        fscanf(file, "%ld %d %s %s %d %f", &ogr.TCKN, &ogr.sube, ogr.Adi, ogr.Soyadi, &ogr.cinsiyet, &ogr.DersOrtalamasi);
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
    FILE *file = fopen("ogrenci.db", "rb");
    if (file == NULL) {
        printf("Dosya okunamadi!");
        exit(1);
    }
    struct ogrenci ogr;
    int i = 0;
    while (!feof(file)) {
        fscanf(file, "%ld %d %s %s %d %f", &ogr.TCKN, &ogr.sube, ogr.Adi, ogr.Soyadi, &ogr.cinsiyet, &ogr.DersOrtalamasi);
        if (ogr.sube == sube) {
            DiziOrtalamalari[i++] = ogr.DersOrtalamasi;
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
            Ueyp = Ieup;
            Ieup = DiziOrtalamalari[j];
        } else if (DiziOrtalamalari[j] > Ueyp) {
            Ueyp = DiziOrtalamalari[j];
        }
    }
    if (size > 0) arr[0] = Ieup;
    if (size > 1) arr[1] = Ueyp;
}
