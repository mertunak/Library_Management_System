#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

typedef struct ogrenci{
	
	char ogrID[9];
	char ad[30];
	char soyad[30];
	int puan;
	struct ogrenci *next, *prev;
}Ogrenci;

typedef struct yazar{
	
	int yazarID;
	char yazarAd[30];
	char yazarSoyad[30];
	struct yazar *next;
}Yazar;

typedef struct kitapOrnek{

	char etiketNo[20];
	char durum[9];
	struct kitapOrnek *next;
}KitapOrnek;

typedef struct kitap{
	
	char kitapAdi[30];
	char ISBN[14];
	int kitapAdet;
	struct kitap *next;
	struct kitapOrnek *head;
}Kitap;

typedef struct kitapYazar{
	
	char ISBN[13];
	int yazarID;
}KitapYazar;

typedef struct tarih{
	
	unsigned int gun : 5;
	unsigned int ay : 4;
	unsigned int yil : 12;
}Tarih;

typedef struct kitapOdunc{
	
	char etiketNo[20];
	char ogrID[9];
	unsigned int islemTipi : 1;
	struct tarih islemTarihi;
}KitapOdunc;

void delay(int number_of_seconds);

Yazar *yazarBul(Yazar *ilkYazar);
Yazar *yazarBulID(Yazar *ilkYazar, int yazarID);
void yazarGoruntule(Yazar *yazar, int length, KitapYazar **dataBase, Kitap *ilkKitap);
Yazar *yazarEkle(Yazar *ilkYazar, char *isim, char *soyisim, int *ID);
void yazarGuncelle(Yazar *yazar);
Yazar *yazarSil(Yazar *ilkYazar, Yazar *yazar, KitapYazar **databaseKY, int kitapYazarSayisi);
void yazarListele(Yazar *ilkYazar, int length, KitapYazar **dataBase, Kitap *ilkKitap);
Yazar *yazarDosyaOku(Yazar *ilkYazar, int *sonID);
void yazarDosyaYaz(Yazar *ilkYazar);

Ogrenci *ogrenciBul(Ogrenci *ilkOgrenci);
void ogrenciGoruntuleDetayli(Ogrenci *ogrenci, KitapOdunc **databaseOK, int ogrenciKitapSayisi);
void ogrenciGoruntule(Ogrenci *ogrenci);
Ogrenci *ogrenciEkle(Ogrenci *ilkOgrenci, char *ID, char *isim, char *soyisim);
Ogrenci *ogrenciSil(Ogrenci *ilkOgrenci, Ogrenci *ogrenci);
void ogrenciGuncelle(Ogrenci *ogrenci);
void teslimEtmemisOgrenciListele(KitapOdunc **databaseOK, Ogrenci *ilkOgrenci, int length);
void cezaliOgrenciListele(Ogrenci *ilkOgrenci);
void ogrenciListele(Ogrenci *ilkOgrenci, KitapOdunc **databaseOK, int ogrenciKitapSayisi);
Ogrenci *ogrenciDosyaOku(Ogrenci *ilkOgrenci);
void ogrenciDosyaYaz(Ogrenci *ilkOgrenci);
KitapOdunc **OgrenciKitap(KitapOdunc **databaseOK, char ***gecikmeliTeslim, Ogrenci *ogrenci, Kitap *ilkKitap, int secim, int *ogrenciKitapSayisi, int *gecikmeliTeslimSayisi, KitapOdunc *(*fnptrOK)(Ogrenci *ilkOgrenci, Kitap *ilkKitap));
KitapOdunc *kitapOduncAl(Ogrenci *ogrenci, Kitap *ilkKitap);
KitapOdunc *kitapTeslimEt(Ogrenci *ogrenci, Kitap *ilkKitap);
void ogrenciKitapDosyaYaz(KitapOdunc **databaseOK, int ogrenciKitapSayisi);

Kitap *kitapBul(Kitap *ilkKitap);
void kitapGoruntule(Kitap *kitap);
Kitap *kitapEkle(Kitap *ilkKitap, char *ISBN, char *kitapAdi, int adet);
KitapOrnek *ornekKitapEkle(KitapOrnek *ilkOrnekKitap, char ISBN[13], int eklenecekAdet, int sonAdet);
void kitapListele(Kitap *ilkKitap);
Kitap *kitapSil(Kitap *ilkKitap, Kitap *kitap, KitapYazar ***databaseKY, int *kitapYazarSayisi);
void kitapGuncelle(Kitap *kitap);
Kitap *kitapDosyaOku(Kitap *ilkKitap);
void kitapDosyaYaz(Kitap *ilkKitap);
KitapYazar **kitapYazarEslestir(KitapYazar **databaseKY, char ISBN[13], int yazarID, int *kitapYazarSayisi);
KitapYazar **kitapYazarDosyaOku(KitapYazar **databaseKY, int *kitapYazarSayisi);
void kitapYazarDosyaYaz(KitapYazar **databaseKY, int kitapYazarSayisi);
void listele(KitapYazar **databaseKY, int count);
KitapYazar **kitapYazarGuncelle(KitapYazar **databaseKY, Yazar *ilkYazar, int *kitapYazarSayisi, char *ISBN, int yazarID, int islem);
void raftakiKitaplariListele(Kitap *ilkKitap);
void zamanindaTeslimEdilmeyenKitapListele(char **gecikmeliTeslim, int length);

Tarih tarihAl();

int main(int argc, char *argv[]) {
	
	int i, islem, progKontrol = 1, menuKontrol, secim;
	int sonYazarID = 0;
	int kitapYazarSayisi = 0;
	int ogrenciKitapSayisi = 0;
	int gecikmeliTeslimSayisi = 0;
	Yazar *ilkYazar = NULL, *prevYazar;
	Yazar *eslestirYazar;
	Yazar *arananYazar;
	Yazar *iterYazar;
	char *yazarIsmi = (char*)malloc(30*sizeof(char));
	if(yazarIsmi == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	char *yazarSoyismi = (char*)malloc(30*sizeof(char));
	if(yazarSoyismi == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	int yazarID;
	Ogrenci *ilkOgrenci = NULL, *prevOgrenci;
	Ogrenci *arananOgrenci;
	Ogrenci *iterOgrenci;
	char *ogrenciID = (char*)malloc(9*sizeof(char));
	if(ogrenciID == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	char *ogrenciIsmi = (char*)malloc(30*sizeof(char));
	if(ogrenciIsmi == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	char *ogrenciSoyismi = (char*)malloc(30*sizeof(char));
	if(ogrenciSoyismi == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	KitapOdunc *(*fnptrOK[2])(Ogrenci *ogrenci, Kitap *ilkKitap) = {kitapOduncAl, kitapTeslimEt};
	Kitap *ilkKitap = NULL, *prevKitap;
	Kitap *eslestirKitap;
	Kitap *arananKitap;
	Kitap *iterKitap;
	KitapOrnek *iterKitapOrnek;
	char *ISBN = (char*)malloc(14*sizeof(char));
	if(ISBN == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	char *kitapAdi = (char*)malloc(30*sizeof(char));
	if(kitapAdi == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	int kitapAdet;
	KitapYazar **databaseKY = (KitapYazar**)malloc(sizeof(KitapYazar*));
	if(databaseKY == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	KitapOdunc **databaseOK = (KitapOdunc**)malloc(sizeof(KitapOdunc*));
	if(databaseOK == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	char **gecikmeliTeslim = (char**)malloc(sizeof(char*));
	if(gecikmeliTeslim == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	FILE *flptrYazar;
	FILE *flptrOgrenci;
	FILE *flptrKitap;
	FILE *flptrKitapYazar;
	
	ilkYazar = yazarDosyaOku(ilkYazar, &sonYazarID);
	ilkOgrenci = ogrenciDosyaOku(ilkOgrenci);
	ogrenciDosyaYaz(ilkOgrenci);
	ilkKitap = kitapDosyaOku(ilkKitap);
	kitapDosyaYaz(ilkKitap);
	databaseKY = kitapYazarDosyaOku(databaseKY, &kitapYazarSayisi);
	
	while(progKontrol){
		
		printf("------KUTUPHANE OTOMASYONUNA HOSGELDINIZ------\n\n");
		printf(" Ogrenci Islemleri ==> 1\n");
		printf(" Kitap Islemleri ==> 2\n");
		printf(" Yazar Islemleri ==> 3\n");
		printf(" Cikis ==> 0\n");
		
		printf("\n Secim: ");
		scanf("%d", &islem);
		menuKontrol = 1;
		system("cls");
		
		switch(islem){
			
			case 0:
				
				free(yazarIsmi);
				free(yazarSoyismi);
				free(ogrenciID);
				free(ogrenciIsmi);
				free(ogrenciSoyismi);
				free(ISBN);
				free(kitapAdi);
				
				for(i = 0; i < kitapYazarSayisi; i++){
					
					free(databaseKY[i]);
				}
				free(databaseKY);
				
				for(i = 0; i < ogrenciKitapSayisi; i++){
					
					free(databaseOK[i]);
				}
				free(databaseOK);
				
				for(i = 0; i < gecikmeliTeslimSayisi; i++){
					
					free(gecikmeliTeslim[i]);
				}
				free(gecikmeliTeslim);
				
				while(ilkKitap != NULL){
					
					prevKitap = ilkKitap;
					ilkKitap = ilkKitap->next;
					free(prevKitap);
				}
				
				while(ilkYazar != NULL){
					
					prevYazar = ilkYazar;
					ilkYazar = ilkYazar->next;
					free(prevYazar);
				}
				
				while(ilkOgrenci != NULL){
					
					prevOgrenci = ilkOgrenci;
					ilkOgrenci = ilkOgrenci->next;
					free(prevOgrenci);
				}
				
				progKontrol = 0;
				printf(" Otomasyondan cikis yapildi...");
				break;
				
			case 1:
				
				while(menuKontrol){
					system("cls");
					printf("OGRENCI ISLEMLERI\n\n");
					printf(" Ogrenci Bilgisi Goruntuleme ==> 1\n");
					printf(" Ogrenci Ekle ==> 2\n");
					printf(" Ogrenci Sil ==> 3\n");
					printf(" Ogrenci Guncelle ==> 4\n");
					printf(" Kitap Teslim Etmemis Ogrencileri Listele ==> 5\n");
					printf(" Cezali Ogrencileri Listele ==> 6\n");
					printf(" Tum Ogrencileri Listele ==> 7\n");
					printf(" Kitap Odunc Al/Teslim Et ==> 8\n");
					printf(" Geri Don ==> 0\n");
					
					printf("\n Secim: ");
					scanf("%d", &islem);
					system("cls");
					getchar();
					
					switch(islem){
			
						case 0:
							
							menuKontrol = 0;
							system("cls");
							break;
							
						case 1:
							
							arananOgrenci = ogrenciBul(ilkOgrenci);
							if(arananOgrenci != NULL){
								
								ogrenciGoruntuleDetayli(arananOgrenci, databaseOK, ogrenciKitapSayisi);
							} else{
								
								printf("\n Ogrenci Bilgisi Bulunamadi!!!\n\n");
							}
							printf(" Menuye donmek icin Enter'a basiniz.");
							getchar();
							break;
						
						case 2:
							
							printf(" Ogrenci ID: ");
							gets(ogrenciID);
							iterOgrenci = ilkOgrenci;
							while(iterOgrenci != NULL && strcmp(iterOgrenci->ogrID, ogrenciID) != 0){
								
								iterOgrenci = iterOgrenci->next;
							}
							
							if(iterOgrenci == NULL){
								
								printf(" Ogrenci Ismi: ");
								gets(ogrenciIsmi);
								printf(" Ogrenci Soyismi: ");
								gets(ogrenciSoyismi);
								ilkOgrenci = ogrenciEkle(ilkOgrenci, ogrenciID, ogrenciIsmi, ogrenciSoyismi);
								printf("\n Ogrenci basariyla eklendi.\n\n");
								ogrenciDosyaYaz(ilkOgrenci);
							} else{
								
								printf("\n Bu ID bilgisine sahip ogrenci bulunmaktadir!!!\n\n");
							}
							printf(" Menuye donmek icin Enter'a basiniz.");
							getchar();
							break;
						
						case 3:
							
							arananOgrenci = ogrenciBul(ilkOgrenci);
							if(arananOgrenci != NULL){
								
								ilkOgrenci = ogrenciSil(ilkOgrenci, arananOgrenci);
							} else{
								
								printf("\n Ogrenci Bilgisi Bulunamadi!!!\n\n");
							}
							ogrenciDosyaYaz(ilkOgrenci);
							printf(" Menuye donmek icin Enter'a basiniz.");
							getchar();
							break;
						
						case 4:
							
							arananOgrenci = ogrenciBul(ilkOgrenci);
							if(arananOgrenci != NULL){
								
								ogrenciGuncelle(arananOgrenci);
							} else{
								
								printf("\n Ogrenci Bilgisi Bulunamadi!!!\n\n");
							}
							ogrenciDosyaYaz(ilkOgrenci);
							printf(" Menuye donmek icin Enter'a basiniz.");
							getchar();
							break;
						
						case 5:
							
							teslimEtmemisOgrenciListele(databaseOK, ilkOgrenci, ogrenciKitapSayisi);
							printf(" Menuye donmek icin Enter'a basiniz.");
							getchar();
							break;
						
						case 6:
							
							cezaliOgrenciListele(ilkOgrenci);
							printf(" Menuye donmek icin Enter'a basiniz.");
							getchar();
							break;
						
						case 7:
							
							ogrenciListele(ilkOgrenci, databaseOK, ogrenciKitapSayisi);
							printf(" Menuye donmek icin Enter'a basiniz.");
							getchar();
							break;
						
						case 8:
							
							arananOgrenci = ogrenciBul(ilkOgrenci);
							if(arananOgrenci != NULL){
								
								system("cls");
								printf(" Islem Yapilan Ogrenci: \n\n");
								ogrenciGoruntule(arananOgrenci);
								printf(" Kitap Odunc Al ==> 0\n");
								printf(" Kitap Teslim Et ==> 1\n");
								printf("\n Islem: ");
								scanf("%d", &islem);
								getchar();
								databaseOK = OgrenciKitap(databaseOK, &gecikmeliTeslim, arananOgrenci, ilkKitap, islem, &ogrenciKitapSayisi, &gecikmeliTeslimSayisi, fnptrOK[islem]);
							} else{
								
								printf("\n Ogrenci Bilgisi Bulunamadi!!!\n\n");
							}
							ogrenciKitapDosyaYaz(databaseOK, ogrenciKitapSayisi);
							
							if(islem == 1){
								
								ogrenciDosyaYaz(ilkOgrenci);
							}
							printf(" Menuye donmek icin Enter'a basiniz.");
							getchar();
							break;
						
						default:
				
							printf(" Hatali deger girdiniz. Lutfen yeni deger giriniz.\n\n");
							delay(1);
							system("cls");
							break;
					}
				}
				
				break;
			
			case 2:
				
				while(menuKontrol){
					system("cls");
					printf("KITAP ISLEMLERI\n\n");
					printf(" Kitap Bilgisi Goruntuleme ==> 1\n");
					printf(" Kitap Ekle ==> 2\n");
					printf(" Kitap Sil ==> 3\n");
					printf(" Kitap Guncelle ==> 4\n");
					printf(" Raftaki Kitaplari Listele ==> 5\n");
					printf(" Zamaninda Teslim Edilmeyen Kitaplari Listele ==> 6\n");
					printf(" Kitap-Yazar Eslestir ==> 7\n");
					printf(" Kitapin Yazarini Guncelle ==> 8\n");
					printf(" Tum Kitaplari Listele ==> 9\n");
					printf(" Geri Don ==> 0\n");
	
					printf("\n Secim: ");
					scanf("%d", &islem);
					system("cls");
					getchar();
					
					switch(islem){
			
						case 0:
							
							menuKontrol = 0;
							system("cls");
							break;
						
						case 1:
							
							arananKitap = kitapBul(ilkKitap);
							if(arananKitap != NULL){
								
								kitapGoruntule(arananKitap);
							} else{
								
								printf("\n Kitap Bilgisi Bulunamadi!!!\n\n");
							}
							printf(" Menuye donmek icin Enter'a basiniz.");
							getchar();
							break;
						
						case 2:
							
							printf(" Kitap ISBN: ");
							gets(ISBN);
							iterKitap = ilkKitap;
							while(iterKitap != NULL && strcmp(iterKitap->ISBN, ISBN) != 0){
								
								iterKitap = iterKitap->next;
							}
							
							if(iterKitap == NULL){
								
								printf(" Kitap Adi: ");
								gets(kitapAdi);
								printf(" Kitap Adeti: ");
								scanf("%d", &kitapAdet);
								getchar();
								ilkKitap = kitapEkle(ilkKitap, ISBN, kitapAdi, kitapAdet);
								printf("\n Kitap basariyla eklendi.\n\n");
								kitapDosyaYaz(ilkKitap);
							} else{
								
								printf("\n Bu ISBN bilgisine sahip kitap bulunmaktadir!!!\n\n");
							}
							printf(" Menuye donmek icin Enter'a basiniz.");
							getchar();
							break;
						
						case 3:
							
							arananKitap = kitapBul(ilkKitap);
							if(arananKitap != NULL){
								
								iterKitapOrnek = arananKitap->head;
								while(iterKitapOrnek != NULL && strcmp(iterKitapOrnek->durum, "Rafta") == 0){
									
									iterKitapOrnek = iterKitapOrnek->next;
								}
								
								if(iterKitapOrnek == NULL){
									
									ilkKitap = kitapSil(ilkKitap, arananKitap, &databaseKY, &kitapYazarSayisi);
								}else{
									
									printf("\n Kitap Odunc Verldiginden Silinemez!!!\n\n");
								}
								
							} else{
								
								printf("\n Kitap Bilgisi Bulunamadi!!!\n\n");
							}
							kitapDosyaYaz(ilkKitap);
							kitapYazarDosyaYaz(databaseKY, kitapYazarSayisi);
							printf(" Menuye donmek icin Enter'a basiniz.");
							getchar();
							break;
						
						case 4:
							
							arananKitap = kitapBul(ilkKitap);
							if(arananKitap != NULL){
								
								printf("\nEski Veriler: \n\n");
								kitapGoruntule(arananKitap);
								kitapGuncelle(arananKitap);
							} else{
								
								printf("\n Kitap Bilgisi Bulunamadi!!!\n\n");
							}
							kitapDosyaYaz(ilkKitap);
							printf(" Menuye donmek icin Enter'a basiniz.");
							getchar();
							break;
						
						case 5:
							
							raftakiKitaplariListele(ilkKitap);
							printf(" Menuye donmek icin Enter'a basiniz.");
							getchar();
							break;
						
						case 6:
							
							zamanindaTeslimEdilmeyenKitapListele(gecikmeliTeslim, gecikmeliTeslimSayisi);
							printf(" Menuye donmek icin Enter'a basiniz.");
							getchar();
							break;
						
						case 7:

							eslestirYazar = yazarBul(ilkYazar);
							eslestirKitap = kitapBul(ilkKitap);
							
							if(eslestirKitap != NULL && eslestirYazar != NULL){
							
								databaseKY = kitapYazarEslestir(databaseKY, eslestirKitap->ISBN, eslestirYazar->yazarID, &kitapYazarSayisi);
								printf("\n");
								listele(databaseKY, kitapYazarSayisi);
							}else{
								printf("\n");
								if(eslestirKitap == NULL){
								
									printf(" Kitap Bilgisi Bulunamadi!!!\n");
								}	
								
								if(eslestirYazar == NULL){
								
									printf(" Yazar Bilgisi Bulunamadi!!!\n");
								}
								printf("\n");
							}
							kitapYazarDosyaYaz(databaseKY, kitapYazarSayisi);
							printf(" Menuye donmek icin Enter'a basiniz.");
							getchar();
							break;
						
						case 8:
							
							arananKitap = kitapBul(ilkKitap);
							if(arananKitap != NULL){
								
								printf(" Kitabin Yazarlari:\n\n");
								for(i = 0; i < kitapYazarSayisi; i++){
									
									if(strcmp(databaseKY[i]->ISBN, arananKitap->ISBN) == 0){
										
										if(databaseKY[i]->yazarID != -1){
											
											arananYazar = yazarBulID(ilkYazar, databaseKY[i]->yazarID);
											printf("\tYazar ID: %d\n\tYazar Ismi: %s\n\tYazar Soyismi: %s\n\n", arananYazar->yazarID, arananYazar->yazarAd, arananYazar->yazarSoyad);
										}
									}
								}
								printf(" Islem yapmak istediginiz yazarin ID numarasini giriniz: ");
								scanf("%d", &yazarID);
								
								printf("\n Kitabin Yazarini Sil => 0\n");
								printf(" Kitabin Yazarini Degistir => 1\n");
								printf(" Secim: ");
								scanf("%d", &secim);
								getchar();
								databaseKY = kitapYazarGuncelle(databaseKY, ilkYazar, &kitapYazarSayisi, arananKitap->ISBN, yazarID, secim);
								kitapYazarDosyaYaz(databaseKY, kitapYazarSayisi);
							} else{
								
								printf("\n Kitap Bilgisi Bulunamadi!!!\n\n");
							}
							printf(" Menuye donmek icin Enter'a basiniz.");
							getchar();
							break;
						
						case 9:
							
							kitapListele(ilkKitap);
							printf(" Menuye donmek icin Enter'a basiniz.");
							getchar();
							break;
						
						default:
				
							printf(" Hatali deger girdiniz. Lutfen yeni deger giriniz.\n\n");
							delay(1);
							system("cls");
							break;
					}
				}
				
				break;
				
			case 3:
				
				while(menuKontrol){
					system("cls");
					printf("YAZAR ISLEMLERI\n\n");
					printf(" Yazar Bilgisi Goruntuleme ==> 1\n");
					printf(" Yazar Ekle ==> 2\n");
					printf(" Yazar Sil ==> 3\n");
					printf(" Yazar Guncelle ==> 4\n");
					printf(" Tum Yazarlari Listele ==> 5\n");
					printf(" Geri Don ==> 0\n");
					
					printf("\n Secim: ");
					scanf("%d", &islem);
					system("cls");
					getchar();
					
					switch(islem){
			
						case 0:
							
							menuKontrol = 0;
							system("cls");
							break;
							
						case 1:
							
							arananYazar = yazarBul(ilkYazar);
							if(arananYazar != NULL){
								
								yazarGoruntule(arananYazar, kitapYazarSayisi, databaseKY, ilkKitap);
							} else{
								
								printf("\n Yazar Bilgisi Bulunamadi!!!\n\n");
							}
							printf(" Menuye donmek icin Enter'a basiniz.");
							getchar();
							break;
						
						case 2:
							
							printf(" Yazar Ismi: ");
							gets(yazarIsmi);
							printf(" Yazar Soyismi: ");
							gets(yazarSoyismi);
							ilkYazar = yazarEkle(ilkYazar, yazarIsmi, yazarSoyismi, &sonYazarID);
							printf(" Yazar basariyla eklendi.\n\n");
							yazarDosyaYaz(ilkYazar);
							printf(" Menuye donmek icin Enter'a basiniz.");
							getchar();
							break;
						
						case 3:
							
							arananYazar = yazarBul(ilkYazar);
							if(arananYazar != NULL){
								
								ilkYazar = yazarSil(ilkYazar, arananYazar, databaseKY, kitapYazarSayisi);	
							} else{
								
								printf("\n Yazar Bilgisi Bulunamadi!!!\n\n");
							}
							yazarDosyaYaz(ilkYazar);
							kitapYazarDosyaYaz(databaseKY, kitapYazarSayisi);
							printf(" Menuye donmek icin Enter'a basiniz.");
							getchar();
							break;
						
						case 4:
							
							arananYazar = yazarBul(ilkYazar);
							if(arananYazar != NULL){
								
								printf("Eski Veriler: \n\n");
								yazarGoruntule(arananYazar, kitapYazarSayisi, databaseKY, ilkKitap);
								yazarGuncelle(arananYazar);
							} else{
								
								printf("\n Yazar Bilgisi Bulunamadi!!!\n\n");
							}
							yazarDosyaYaz(ilkYazar);
							printf(" Menuye donmek icin Enter'a basiniz.");
							getchar();
							break;
						
						case 5:
							
							yazarListele(ilkYazar, kitapYazarSayisi, databaseKY, ilkKitap);
							printf(" Menuye donmek icin Enter'a basiniz.");
							getchar();
							break;
						
						default:
				
							printf(" Hatali deger girdiniz. Lutfen yeni deger giriniz.\n\n");
							delay(1);
							system("cls");
							break;
					}
				}
				
				break;
				
			default:
				
				printf(" Hatali deger girdiniz. Lutfen tekrar deneyin.\n\n");
				delay(1);
				system("cls");
				break;
		}	
	}

	return 0;
}

void delay(int number_of_seconds){

    int milli_seconds = 1000 * number_of_seconds;
  
    clock_t start_time = clock();
  
    while (clock() < start_time + milli_seconds);
}

Tarih tarihAl(){
	
	Tarih *tarihBilgi = (Tarih*)malloc(sizeof(Tarih));
	if(tarihBilgi == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	
	int val; 

	printf("\n Lutfen Tarih Bilgilerini Giriniz: \n");
	printf("\tGun: ");
	scanf("%d", &val); tarihBilgi->gun = val;
	printf("\tAy: ");
	scanf("%d", &val); tarihBilgi->ay = val;
	printf("\tYil: ");
	scanf("%d", &val); tarihBilgi->yil = val;
	
	return *tarihBilgi;
}

void yazarGoruntule(Yazar *yazar, int length, KitapYazar **dataBase, Kitap *ilkKitap){
		
	if(yazar != NULL){
		
		int i;
		printf(" Yazar ID: %d\n Yazar Ismi: %s\n Yazar Soyismi: %s\n Kitaplari:\n", yazar->yazarID, yazar->yazarAd, yazar->yazarSoyad);

		for(i = 0; i < length; i++){
			
			if(dataBase[i]->yazarID == yazar->yazarID){
				
				Kitap *iterKitap = ilkKitap;
				
				while(strcmp(iterKitap->ISBN, dataBase[i]->ISBN) != 0){
					
					iterKitap = iterKitap->next;
				}
				
				printf("\tISBN: %s\n\tKitap Adi: %s\n\tKitap Adedi: %d\n\n", iterKitap->ISBN, iterKitap->kitapAdi, iterKitap->kitapAdet);
			}
		}
		
		printf("\n");
	}
	
}

Yazar *yazarBul(Yazar *ilkYazar){
	
	char *arananYazarAd = (char*)malloc(sizeof(ilkYazar->yazarAd));
	if(arananYazarAd == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	
	char *arananYazarSoyad = (char*)malloc(sizeof(ilkYazar->yazarSoyad));
	if(arananYazarSoyad == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	
	Yazar *iterYazar = ilkYazar;
	
	printf(" Yazar Ismi: ");
	gets(arananYazarAd);
	printf(" Yazar Soyismi: ");
	gets(arananYazarSoyad);
	printf("\n");
	while(iterYazar != NULL){
		
		if(strcmp(iterYazar->yazarAd, arananYazarAd) == 0 && strcmp(iterYazar->yazarSoyad, arananYazarSoyad) == 0){
			
			return iterYazar;
		}
		
		iterYazar = iterYazar->next;
	}
	
	return NULL;
}

Yazar *yazarBulID(Yazar *ilkYazar, int yazarID){

	Yazar *iterYazar = ilkYazar;
	
	while(iterYazar != NULL){
		
		if(iterYazar->yazarID == yazarID){
			
			return iterYazar;
		}
		
		iterYazar = iterYazar->next;
	}
	
	return NULL;
}

Yazar *yazarEkle(Yazar *ilkYazar, char *isim, char *soyisim, int *sonID){
	
	Yazar *eklenenYazar = (Yazar*)malloc(sizeof(Yazar));
	if(eklenenYazar == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	
	Yazar *iterYazar;
	
	strcpy(eklenenYazar->yazarAd, isim);
	strcpy(eklenenYazar->yazarSoyad, soyisim);
	eklenenYazar->yazarID = ++(*sonID);
	eklenenYazar->next = NULL;
	
	if(ilkYazar == NULL){
		
		ilkYazar = eklenenYazar;
		
	} else{
		
		iterYazar = ilkYazar;
		while(iterYazar->next != NULL){
			
			iterYazar = iterYazar->next;
		}
		
		iterYazar->next = eklenenYazar;
	}
	return ilkYazar;
}

void yazarGuncelle(Yazar *yazar){
	
	Yazar *guncellenecekYazar = yazar;
	
	if(guncellenecekYazar != NULL){
		
		printf("Yeni Veriler: \n\n");
		printf(" Yazar ID: %d\n", guncellenecekYazar->yazarID);
		printf(" Yazar Ismi: ");
		gets(guncellenecekYazar->yazarAd);
		printf(" Yazar Soyismi: ");
		gets(guncellenecekYazar->yazarSoyad);
		printf("\n Yazar basariyla guncellendi.\n\n");
	}
}

Yazar *yazarSil(Yazar *ilkYazar, Yazar *yazar, KitapYazar **databaseKY, int kitapYazarSayisi){
	
	Yazar *silinecekYazar = yazar;
	
	if(silinecekYazar != NULL){
		
		if(silinecekYazar == ilkYazar){
			
			ilkYazar = silinecekYazar->next;
		} else{
			
			Yazar *iterYazar = ilkYazar;
			
			while(iterYazar->next->yazarID != silinecekYazar->yazarID){
				
				iterYazar = iterYazar->next;
			}
			
			iterYazar->next = silinecekYazar->next;
		}
		
		for(--kitapYazarSayisi; kitapYazarSayisi >= 0; kitapYazarSayisi--){
			
			if(databaseKY[kitapYazarSayisi]->yazarID == silinecekYazar->yazarID){
				
				databaseKY[kitapYazarSayisi]->yazarID = -1;
			}
		}
		
		free(silinecekYazar);
		printf("\n Yazar basariyla silindi.\n\n");
	}
	
	return ilkYazar;
	
}

void yazarListele(Yazar *ilkYazar, int length, KitapYazar **dataBase, Kitap *ilkKitap){
	
	Yazar *iterYazar;
	
	if(ilkYazar == NULL){
		
		printf(" Liste Bos!!!\n\n");
	}else{
		
		iterYazar = ilkYazar;
		
		printf("Yazarlar:\n\n");
	
		while(iterYazar != NULL){
			
			yazarGoruntule(iterYazar, length, dataBase, ilkKitap);
			iterYazar = iterYazar->next;
		}
	}
}

Yazar *yazarDosyaOku(Yazar *ilkYazar, int *sonID){
	
	char *yazarIsmi = (char*)malloc(30*sizeof(char));
	if(yazarIsmi == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	
	char *yazarSoyismi = (char*)malloc(30*sizeof(char));
	if(yazarSoyismi == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	
	char *veri = (char*)malloc(70*sizeof(char));
	if(veri == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	
	FILE *flptrYazar = fopen("Yazarlar.csv", "r");
	if(flptrYazar == NULL){
		printf("Dosya Acma Hatasi!!!");
		exit(0);
	}
	
	while(fgets(veri, 70, flptrYazar) != NULL){
		
		strtok(veri, ",");
		yazarIsmi = strtok(NULL, ",");
		yazarSoyismi = strtok(NULL, "\n");
		ilkYazar = yazarEkle(ilkYazar, yazarIsmi, yazarSoyismi, sonID);
	}
	
	fclose(flptrYazar);
	return ilkYazar;
}

void yazarDosyaYaz(Yazar *ilkYazar){
	
	FILE *flptrYazar = fopen("Yazarlar.csv", "w");
	if(flptrYazar == NULL){
		printf("Dosya Acma Hatasi!!!");
		exit(0);
	}
	
	Yazar *iterYazar = ilkYazar;
	while(iterYazar->next != NULL){
						
		fprintf(flptrYazar, "%d,%s,%s\n", iterYazar->yazarID, iterYazar->yazarAd, iterYazar->yazarSoyad);
		iterYazar = iterYazar->next;
	}
	fprintf(flptrYazar, "%d,%s,%s", iterYazar->yazarID, iterYazar->yazarAd, iterYazar->yazarSoyad);		
	
	fclose(flptrYazar);
}

Ogrenci *ogrenciBul(Ogrenci *ilkOgrenci){
	
	int secim, ayniOgrencimi;
	char *arananOgrenciID;
	char *arananOgrenciAd;
	char *arananOgrenciSoyad;
	
	Ogrenci *iterOgrenci = ilkOgrenci;
	
	printf("Aramayi hangi bilgiye gore yapacaksiniz:\n Ogrenci ID bilgisine => 0\n Ogrenci AD-SOYAD bilgisine => 1\n\n");
	printf(" Secim: ");
	scanf("%d", &secim);
	getchar();
	system("cls");
	if(secim == 0){
		
		arananOgrenciID = (char*)malloc(sizeof(ilkOgrenci->ogrID));
		if(arananOgrenciID == NULL){
			printf("Alan Ayrilamadi!!!");
			exit(0);
		}
		
		printf(" Ogrenci ID'si: ");
		gets(arananOgrenciID);
		
		while((iterOgrenci != NULL)){
		
			if(strcmp(iterOgrenci->ogrID, arananOgrenciID) == 0){
				
				return iterOgrenci;
			}
			
			iterOgrenci = iterOgrenci->next;
		}
		
	}else{
		
		arananOgrenciAd = (char*)malloc(sizeof(ilkOgrenci->ad));
		if(arananOgrenciAd == NULL){
			printf("Alan Ayrilamadi!!!");
			exit(0);
		}
		
		arananOgrenciSoyad = (char*)malloc(sizeof(ilkOgrenci->soyad));
		if(arananOgrenciSoyad == NULL){
			printf("Alan Ayrilamadi!!!");
			exit(0);
		}
		
		printf(" Ogrenci Ismi: ");
		gets(arananOgrenciAd);
		printf(" Ogrenci Soyismi: ");
		gets(arananOgrenciSoyad);
		printf("\n");
		while((iterOgrenci != NULL)){
		
			if(strcmp(iterOgrenci->ad, arananOgrenciAd) == 0 && strcmp(iterOgrenci->soyad, arananOgrenciSoyad) == 0){
				
				return iterOgrenci;
			}
			
			iterOgrenci = iterOgrenci->next;
		}	
	}
	
	return NULL;
}

void ogrenciGoruntuleDetayli(Ogrenci *ogrenci, KitapOdunc **databaseOK, int ogrenciKitapSayisi){
	
	int i;
	
	if(ogrenci != NULL){
		
		printf(" Ogrenci ID: %s\n Ogrenci Ismi: %s\n Ogrenci Soyismi: %s\n Ogrenci Puani: %d\n Kitap Hareketleri:\n", ogrenci->ogrID, ogrenci->ad, ogrenci->soyad, ogrenci->puan);
		
		for(i = 0; i < ogrenciKitapSayisi; i++){
			
			if(strcmp(databaseOK[i]->ogrID, ogrenci->ogrID) == 0){
				
				printf("\t%s,%s,%u,%u.%u.%u\n", databaseOK[i]->etiketNo, databaseOK[i]->ogrID, databaseOK[i]->islemTipi, databaseOK[i]->islemTarihi.gun, databaseOK[i]->islemTarihi.ay, databaseOK[i]->islemTarihi.yil);
			}
		}
		printf("\n");
	}
}

void ogrenciGoruntule(Ogrenci *ogrenci){
	
	int i;
	
	if(ogrenci != NULL){
		
		printf(" Ogrenci ID: %s\n Ogrenci Ismi: %s\n Ogrenci Soyismi: %s\n Ogrenci Puani: %d\n\n", ogrenci->ogrID, ogrenci->ad, ogrenci->soyad, ogrenci->puan);
	}
}

Ogrenci *ogrenciEkle(Ogrenci *ilkOgrenci, char *ID, char *isim, char *soyisim){
	
	Ogrenci *eklenenOgrenci = (Ogrenci*)malloc(sizeof(Ogrenci));
	if(eklenenOgrenci == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
		
	Ogrenci *iterOgrenci;
	
	strcpy(eklenenOgrenci->ogrID, ID);
	strcpy(eklenenOgrenci->ad, isim);
	strcpy(eklenenOgrenci->soyad, soyisim);
	
	eklenenOgrenci->puan = 100;
	eklenenOgrenci->next = NULL;
	eklenenOgrenci->prev = NULL;
	
	if(ilkOgrenci == NULL){
		
		ilkOgrenci = eklenenOgrenci;
		
	} else if(ilkOgrenci->next == NULL){
		
		if(strcmp(ilkOgrenci->ogrID, eklenenOgrenci->ogrID) < 0){
			
			ilkOgrenci->next = eklenenOgrenci;
			eklenenOgrenci->prev = ilkOgrenci;
		} else{
			
			eklenenOgrenci->next = ilkOgrenci;
			ilkOgrenci->prev = eklenenOgrenci;
			ilkOgrenci = eklenenOgrenci;
		}
	} else if(strcmp(ilkOgrenci->ogrID, eklenenOgrenci->ogrID) > 0){
		
		eklenenOgrenci->next = ilkOgrenci;
		ilkOgrenci->prev = eklenenOgrenci;
		ilkOgrenci = eklenenOgrenci;
	} else{
		
		iterOgrenci = ilkOgrenci;

		while(iterOgrenci->next != NULL && strcmp(iterOgrenci->next->ogrID, eklenenOgrenci->ogrID) < 0){
			
			iterOgrenci = iterOgrenci->next;
		}

		eklenenOgrenci->next = iterOgrenci->next;
		eklenenOgrenci->prev = iterOgrenci;
		iterOgrenci->next = eklenenOgrenci;
	}
	return ilkOgrenci;
}

void ogrenciListele(Ogrenci *ilkOgrenci, KitapOdunc **databaseOK, int ogrenciKitapSayisi){
	
	Ogrenci *iterOgrenci;
	
	if(ilkOgrenci == NULL){
		
		printf(" Liste Bos!!!\n\n");
	}else{
		
		iterOgrenci = ilkOgrenci;
		
		printf("Ogrenciler:\n\n");
	
		while(iterOgrenci != NULL){
			
			ogrenciGoruntuleDetayli(iterOgrenci, databaseOK, ogrenciKitapSayisi);
			iterOgrenci = iterOgrenci->next;
		}
	}
}

void ogrenciGuncelle(Ogrenci *ogrenci){
	
	Ogrenci *guncellenecekOgrenci = ogrenci;
	
	if(guncellenecekOgrenci != NULL){
		
		printf("Yeni Veriler: \n\n");
		printf(" Ogrenci ID: %s\n", guncellenecekOgrenci->ogrID);
		printf(" Ogrenci Ismi: ");
		gets(guncellenecekOgrenci->ad);
		printf(" Ogrenci Soyismi: ");
		gets(guncellenecekOgrenci->soyad);
		printf(" Ogrenci Puan: ");
		scanf("%d", &(guncellenecekOgrenci->puan));
		printf("\n Ogrenci basariyla guncellendi.\n\n");
	}
}

void teslimEtmemisOgrenciListele(KitapOdunc **databaseOK, Ogrenci *ilkOgrenci, int length){
	
	int i, j, count = 0;
	
	printf("Kitap Teslim Etmemis Ogrenciler:\n\n");
	
	for(i = 0; i < length; i++){
		
		if(databaseOK[i]->islemTipi == 0){
			
			j = i + 1;
			while(j < length && (strcmp(databaseOK[i]->etiketNo, databaseOK[j]->etiketNo) != 0 || strcmp(databaseOK[i]->ogrID, databaseOK[j]->ogrID) != 0)){
				
				j++;
			}

			if(j == length){
				
				Ogrenci *iterOgrenci = ilkOgrenci;
				
				while(strcmp(iterOgrenci->ogrID, databaseOK[i]->ogrID) != 0){
					
					iterOgrenci = iterOgrenci->next;
				}
				
				ogrenciGoruntule(iterOgrenci);
				printf("\tKitap Etiket No: %s\n\n", databaseOK[i]->etiketNo);
				count++;
			}
		}
	}
	
	if(count == 0){
		
		printf(" Kitap Teslim Etmeyen Ogrenci Bulunmamaktadir!!!\n\n");
	}
}

void cezaliOgrenciListele(Ogrenci *ilkOgrenci){
	
	Ogrenci *iterOgrenci;
	int count = 0;
	
	if(ilkOgrenci == NULL){
		
		printf(" Liste Bos!!!\n\n");
	}else{
		
		iterOgrenci = ilkOgrenci;
		
		printf("Cezali Ogrenciler:\n\n");
	
		while(iterOgrenci != NULL){
			
			if(iterOgrenci->puan < 100){
				count++;
				ogrenciGoruntule(iterOgrenci);
			}
			iterOgrenci = iterOgrenci->next;
		}
		
		if(count == 0){
			
			printf(" Cezali Ogrenci Yok!!!\n\n");
		}
	}
}

Ogrenci *ogrenciSil(Ogrenci *ilkOgrenci, Ogrenci *ogrenci){
	
	Ogrenci *silinecekOgrenci = ogrenci;
	
	if(silinecekOgrenci != NULL){
		
		if((silinecekOgrenci->prev == NULL) && (silinecekOgrenci->next == NULL)){
			
			ilkOgrenci = NULL;
		} else if(silinecekOgrenci->prev == NULL){
			
			ilkOgrenci = silinecekOgrenci->next;
			ilkOgrenci->prev = NULL;
		} else if(silinecekOgrenci->next == NULL){
			
			silinecekOgrenci->prev->next = NULL;
		} else{
			
			silinecekOgrenci->prev->next = silinecekOgrenci->next;
			silinecekOgrenci->next->prev = silinecekOgrenci->prev;
		}

		free(silinecekOgrenci);
		printf("\n Ogrenci basariyla silindi.\n\n");
	}
	
	return ilkOgrenci;
	
}

Ogrenci *ogrenciDosyaOku(Ogrenci *ilkOgrenci){
	
	char *ogrenciID = (char*)malloc(8*sizeof(char));
	if(ogrenciID == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	
	char *ogrenciIsmi = (char*)malloc(30*sizeof(char));
	if(ogrenciIsmi == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	
	char *ogrenciSoyismi = (char*)malloc(30*sizeof(char));
	if(ogrenciSoyismi == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	
	char *veri = (char*)malloc(70*sizeof(char));
	if(veri == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}

	FILE *flptrOgrenci = fopen("Ogrenciler.csv", "r");
	if(flptrOgrenci == NULL){
		printf("Dosya Acma Hatasi!!!");
		exit(0);
	}
	
	while(fgets(veri, 70, flptrOgrenci) != NULL){
		
		ogrenciID = strtok(veri, ",");
		ogrenciIsmi = strtok(NULL, ",");
		ogrenciSoyismi = strtok(NULL, ",");
		ilkOgrenci = ogrenciEkle(ilkOgrenci, ogrenciID, ogrenciIsmi, ogrenciSoyismi);
	}
	
	fclose(flptrOgrenci);
	return ilkOgrenci;
}

void ogrenciDosyaYaz(Ogrenci *ilkOgrenci){
	
	FILE *flptrOgrenci = fopen("Ogrenciler.csv", "w");
	if(flptrOgrenci == NULL){
		printf("Dosya Acma Hatasi!!!");
		exit(0);
	}
	
	Ogrenci *iterOgrenci = ilkOgrenci;
	while(iterOgrenci->next != NULL){
						
		fprintf(flptrOgrenci, "%s,%s,%s,%d\n", iterOgrenci->ogrID, iterOgrenci->ad, iterOgrenci->soyad, iterOgrenci->puan);
		iterOgrenci = iterOgrenci->next;
	}
	fprintf(flptrOgrenci, "%s,%s,%s,%d", iterOgrenci->ogrID, iterOgrenci->ad, iterOgrenci->soyad, iterOgrenci->puan);	

	fclose(flptrOgrenci);
}

KitapOdunc **OgrenciKitap(KitapOdunc **databaseOK, char ***gecikmeliTeslim, Ogrenci *ogrenci, Kitap *ilkKitap, int secim, int *ogrenciKitapSayisi, int *gecikmeliTeslimSayisi, KitapOdunc *(*fnptrOK)(Ogrenci *ilkOgrenci, Kitap *ilkKitap)){

	KitapOdunc *islemOK = fnptrOK(ogrenci, ilkKitap);
	
	if(islemOK != NULL){
		int i, teslimGun = 0;
		strcpy(islemOK->ogrID, ogrenci->ogrID);
		islemOK->islemTarihi = tarihAl();
		islemOK->islemTipi = secim;
		getchar();
		if(secim == 1){
			i = 0;
			while(databaseOK[i]->islemTipi != 0 || strcmp(databaseOK[i]->etiketNo, islemOK->etiketNo) != 0 || strcmp(databaseOK[i]->ogrID, islemOK->ogrID) != 0){
				
				i++;
			}
			
			teslimGun = 365*(islemOK->islemTarihi.yil - databaseOK[i]->islemTarihi.yil) + 30*(islemOK->islemTarihi.ay - databaseOK[i]->islemTarihi.ay) + (islemOK->islemTarihi.gun - databaseOK[i]->islemTarihi.gun);
			
			if(teslimGun >= 0){
				
				databaseOK = (KitapOdunc**)realloc(databaseOK,((*ogrenciKitapSayisi)+1)*sizeof(KitapOdunc*));
				if(databaseOK == NULL){
					printf("Alan Ayrilamadi!!!");
					exit(0);
				}
				databaseOK[*ogrenciKitapSayisi] = islemOK;
				(*ogrenciKitapSayisi)++;
				printf("\n Islem Basariyla Gerceklesti.\n\n");
				if(teslimGun > 15){
					
					ogrenci->puan -= 10;
					*gecikmeliTeslim = (char**)realloc(*gecikmeliTeslim,((*gecikmeliTeslimSayisi)+1)*sizeof(char*));
					if(*gecikmeliTeslim == NULL){
						printf("Alan Ayrilamadi!!!");
						exit(0);
					}
					*gecikmeliTeslim[*gecikmeliTeslimSayisi] = islemOK->etiketNo;
					(*gecikmeliTeslimSayisi)++;
				}
			}
		} else{
			
			databaseOK = (KitapOdunc**)realloc(databaseOK,((*ogrenciKitapSayisi)+1)*sizeof(KitapOdunc*));
			databaseOK[*ogrenciKitapSayisi] = islemOK;
			(*ogrenciKitapSayisi)++;
			printf("\n Islem Basariyla Gerceklesti.\n\n");
		}
	} 	

	return databaseOK;
}

KitapOdunc *kitapOduncAl(Ogrenci *ogrenci, Kitap *ilkKitap){
	
	KitapOdunc *oduncIslem = (KitapOdunc*)malloc(sizeof(KitapOdunc));
	if(oduncIslem == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	
	Kitap *arananKitap = (Kitap*)malloc(sizeof(Kitap));
	if(arananKitap == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	
	arananKitap = kitapBul(ilkKitap);
	
	if(arananKitap != NULL && ogrenci->puan > 0){
								
		KitapOrnek *iterOrnek = arananKitap->head;
		
		while(iterOrnek != NULL && strcmp(iterOrnek->durum, "Rafta") != 0){
			
			iterOrnek = iterOrnek->next;
		}
		
		if(iterOrnek != NULL){
			
			strcpy(iterOrnek->durum, ogrenci->ogrID);
			strcpy(oduncIslem->etiketNo, iterOrnek->etiketNo);
			return oduncIslem;
		} else{
			
			printf("\n Odunc Alinmak Istenen Kitap Rafta Yoktur!!!\n\n");
		}
	} else{
		
		if(arananKitap == NULL){
			
			printf("\n Kitap Bilgisi Bulunamadi!!!\n\n");
		} else{
			
			printf("\n Ogrenciye Puani Nedeniyle Kitam Odunc Verilemez!!!\n\n");
		}
	}

	return NULL;
}


KitapOdunc *kitapTeslimEt(Ogrenci *ogrenci, Kitap *ilkKitap){
	
	KitapOdunc *teslimIslem = (KitapOdunc*)malloc(sizeof(KitapOdunc));
	if(teslimIslem == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	
	Kitap *arananKitap = kitapBul(ilkKitap);
	
	if(arananKitap != NULL){
								
		KitapOrnek *iterOrnek = arananKitap->head;
		
		while(iterOrnek != NULL && strcmp(iterOrnek->durum, ogrenci->ogrID) != 0){
			
			iterOrnek = iterOrnek->next;
		}
		
		if(iterOrnek != NULL){
			
			strcpy(iterOrnek->durum, "Rafta");
			strcpy(teslimIslem->etiketNo, iterOrnek->etiketNo);
			return teslimIslem;
		} else{
			
			printf("\n Ogrenci Bu Kitaba Sahip Degil!!!\n\n");
		}
	} else{
								
		printf("\n Kitap Bilgisi Bulunamadi!!!\n\n");
	}

	return NULL;
}

void ogrenciKitapDosyaYaz(KitapOdunc **databaseOK, int ogrenciKitapSayisi){
	
	int i;
	FILE *flptrOgrenciKitap = fopen("KitapOdunc.csv", "w");
	if(flptrOgrenciKitap == NULL){
		printf("Dosya Acma Hatasi!!!");
		exit(0);
	}
	
	for(i = 0; i < ogrenciKitapSayisi-1; i++){
		
		fprintf(flptrOgrenciKitap, "%s,%s,%u,%u.%u.%u\n", databaseOK[i]->etiketNo, databaseOK[i]->ogrID, databaseOK[i]->islemTipi, databaseOK[i]->islemTarihi.gun, databaseOK[i]->islemTarihi.ay, databaseOK[i]->islemTarihi.yil);
	}
	fprintf(flptrOgrenciKitap, "%s,%s,%u,%u.%u.%u", databaseOK[i]->etiketNo, databaseOK[i]->ogrID, databaseOK[i]->islemTipi, databaseOK[i]->islemTarihi.gun, databaseOK[i]->islemTarihi.ay, databaseOK[i]->islemTarihi.yil);	

	fclose(flptrOgrenciKitap);
}

Kitap *kitapBul(Kitap *ilkKitap){
	
	char *arananKitap = (char*)malloc(sizeof(ilkKitap->kitapAdi));
	if(arananKitap == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	
	Kitap *iterKitap = ilkKitap;
	
	printf(" Kitap Ismi: ");
	gets(arananKitap);
	
	while(iterKitap != NULL){
		
		if(strcmp(iterKitap->kitapAdi, arananKitap) == 0){
			
			return iterKitap;
		}
		
		iterKitap = iterKitap->next;
	}
	
	return NULL;
}

void kitapGoruntule(Kitap *kitap){
	
	if(kitap != NULL){
		
		printf(" ISBN: %s\n Kitap Adi: %s\n Kitap Adedi: %d\n Ornek Kitaplar:\n", kitap->ISBN, kitap->kitapAdi, kitap->kitapAdet);
		KitapOrnek *iterOrnek;
		
		iterOrnek = kitap->head;
		
		while(iterOrnek != NULL){
				
			printf("\tEtiket No: %s\n\tDurum Bilgisi: %s\n\n", iterOrnek->etiketNo, iterOrnek->durum);
			iterOrnek = iterOrnek->next;
		}
			
	}
}

Kitap *kitapEkle(Kitap *ilkKitap, char *ISBN, char *kitapAdi, int adet){
	
	int i;
	Kitap *eklenenKitap = (Kitap*)malloc(sizeof(Kitap));
	if(eklenenKitap == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	
	Kitap *iterKitap;
	
	strcpy(eklenenKitap->ISBN, ISBN);
	strcpy(eklenenKitap->kitapAdi, kitapAdi);
	eklenenKitap->kitapAdet = adet;
	eklenenKitap->head = NULL;
	eklenenKitap->head = ornekKitapEkle(eklenenKitap->head, ISBN, adet, 0);

	eklenenKitap->next = NULL;
	
	if(ilkKitap == NULL){
		
		ilkKitap = eklenenKitap;
		
	} else if(ilkKitap->next == NULL){
		
		if(strcmp(ilkKitap->ISBN, eklenenKitap->ISBN) < 0){
			
			ilkKitap->next = eklenenKitap;
		} else{
			
			eklenenKitap->next = ilkKitap;
			ilkKitap = eklenenKitap;
		}
	} else if(strcmp(ilkKitap->ISBN, eklenenKitap->ISBN) > 0){
		
		eklenenKitap->next = ilkKitap;
		ilkKitap = eklenenKitap;
	} else{
		
		iterKitap = ilkKitap;
		while(iterKitap->next != NULL && strcmp(iterKitap->next->ISBN, eklenenKitap->ISBN) < 0){
			
			iterKitap = iterKitap->next;
		}
		
		eklenenKitap->next = iterKitap->next;
		iterKitap->next = eklenenKitap;			
	}
	return ilkKitap;
}

KitapOrnek *ornekKitapEkle(KitapOrnek *ilkOrnekKitap, char ISBN[13], int eklenecekAdet, int sonAdet){
	
	int i, num;
	
	KitapOrnek *eklenenOrnekKitap, *iterOrnekKitap;
	
	for(i = sonAdet+1; i <= eklenecekAdet+sonAdet; i++){
		
		eklenenOrnekKitap = (KitapOrnek*)malloc(sizeof(KitapOrnek));
		if(eklenenOrnekKitap == NULL){
			printf("Alan Ayrilamadi!!!");
			exit(0);
		}
	
		iterOrnekKitap = (KitapOrnek*)malloc(sizeof(KitapOrnek));
		if(iterOrnekKitap == NULL){
			printf("Alan Ayrilamadi!!!");
			exit(0);
		}
		
		strcpy(eklenenOrnekKitap->etiketNo, ISBN);
		strcpy(&(eklenenOrnekKitap->etiketNo[13]), "_");
		num = sprintf(&(eklenenOrnekKitap->etiketNo[14]), "%d", i);
		strcpy(&(eklenenOrnekKitap->etiketNo[14+num]), "\0");
		
		strcpy(eklenenOrnekKitap->durum, "Rafta");
		
		eklenenOrnekKitap->next = NULL;
		
		if(ilkOrnekKitap == NULL){
			
			ilkOrnekKitap = eklenenOrnekKitap;
			
		} else{
			
			iterOrnekKitap = ilkOrnekKitap;
			while(iterOrnekKitap->next != NULL){
				
				iterOrnekKitap = iterOrnekKitap->next;
			}
			
			iterOrnekKitap->next = eklenenOrnekKitap;
		}
	}
	
	return ilkOrnekKitap;
}

void kitapListele(Kitap *ilkKitap){
	
	Kitap *iterKitap;
	
	if(ilkKitap == NULL){
		
		printf(" Liste Bos!!!\n\n");
	}else{
		
		iterKitap = ilkKitap;
		
		printf("Kitaplar:\n\n");
	
		while(iterKitap != NULL){
			
			kitapGoruntule(iterKitap);
			iterKitap = iterKitap->next;
		}
	}
}

Kitap *kitapDosyaOku(Kitap *ilkKitap){
	
	char *ISBN = (char*)malloc(13*sizeof(char));
	if(ISBN == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
		
	char *kitapAdi = (char*)malloc(30*sizeof(char));
	if(kitapAdi == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	
	int adet;
	char *veri = (char*)malloc(70*sizeof(char));
	if(veri == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	
	FILE *flptrKitap = fopen("Kitaplar.csv", "r");
	if(flptrKitap == NULL){
		printf("Dosya Acma Hatasi!!!");
		exit(0);
	}
	
	while(fgets(veri, 70, flptrKitap) != NULL){
		
		kitapAdi = strtok(veri, ",");
		ISBN = strtok(NULL, ",");
		adet = atoi(strtok(NULL, "\0"));
		ilkKitap = kitapEkle(ilkKitap, ISBN, kitapAdi, adet);
	}
	
	fclose(flptrKitap);
	return ilkKitap;
}

void kitapDosyaYaz(Kitap *ilkKitap){
	
	FILE *flptrKitap = fopen("Kitaplar.csv", "w");
	if(flptrKitap == NULL){
		printf("Dosya Acma Hatasi!!!");
		exit(0);
	}
	
	Kitap *iterKitap = ilkKitap;
	while(iterKitap->next != NULL){
						
		fprintf(flptrKitap, "%s,%s,%d\n", iterKitap->kitapAdi, iterKitap->ISBN, iterKitap->kitapAdet);
		iterKitap = iterKitap->next;
	}
	fprintf(flptrKitap, "%s,%s,%d", iterKitap->kitapAdi, iterKitap->ISBN, iterKitap->kitapAdet);	

	fclose(flptrKitap);
}

KitapYazar **kitapYazarDosyaOku(KitapYazar **databaseKY, int *kitapYazarSayisi){
	
	char *ISBN = (char*)malloc(13*sizeof(char));
	if(ISBN == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	
	int yazarID;
	char *veri = (char*)malloc(20*sizeof(char));
	if(veri == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	
	FILE *flptrKitapYazar = fopen("KitapYazar.csv", "r");
	if(flptrKitapYazar == NULL){
		printf("Dosya Acma Hatasi!!!");
		exit(0);
	}
	
	while(fgets(veri, 20, flptrKitapYazar) != NULL){

		ISBN = strtok(veri, ",");
		yazarID = atoi(strtok(NULL, "\0"));
		databaseKY = kitapYazarEslestir(databaseKY, ISBN, yazarID, kitapYazarSayisi);
	}
	
	fclose(flptrKitapYazar);
	return databaseKY;
}

void kitapYazarDosyaYaz(KitapYazar **databaseKY, int kitapYazarSayisi){
	
	int i;
	FILE *flptrKitapYazar = fopen("KitapYazar.csv", "w");
	if(flptrKitapYazar == NULL){
		printf("Dosya Acma Hatasi!!!");
		exit(0);
	}
	
	for(i = 0; i < kitapYazarSayisi-1; i++){
		
		fprintf(flptrKitapYazar, "%s,%d\n", databaseKY[i]->ISBN, databaseKY[i]->yazarID);
	}
	fprintf(flptrKitapYazar, "%s,%d", databaseKY[i]->ISBN, databaseKY[i]->yazarID);	

	fclose(flptrKitapYazar);
}

KitapYazar **kitapYazarEslestir(KitapYazar **databaseKY, char ISBN[13], int yazarID, int *kitapYazarSayisi){
	
	KitapYazar *eklenenKitapYazar = (KitapYazar*)malloc(sizeof(KitapYazar));
	if(eklenenKitapYazar == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	
	strcpy(eklenenKitapYazar->ISBN, ISBN);
	eklenenKitapYazar->yazarID = yazarID;
	
	databaseKY = (KitapYazar**)realloc(databaseKY,((*kitapYazarSayisi)+1)*sizeof(KitapYazar*));
	if(*databaseKY == NULL){
		printf("Alan Ayrilamadi!!!");
		exit(0);
	}
	
	databaseKY[*kitapYazarSayisi] = eklenenKitapYazar;
	(*kitapYazarSayisi)++;
	
	return databaseKY;
}

void listele(KitapYazar **databaseKY, int count){
	
	int i;
	
	for(i = 0; i < count; i++){
		
		printf(" Yazar ID: %d\n Kitap ISBN: %s\n\n", databaseKY[i]->yazarID, databaseKY[i]->ISBN);
	}
}

KitapYazar **kitapYazarGuncelle(KitapYazar **databaseKY, Yazar *ilkYazar, int *kitapYazarSayisi, char *ISBN, int yazarID, int islem){
	
	system("cls");
	Yazar *eslestirYazar;
	int i = 0;
	while((strcmp(databaseKY[i]->ISBN, ISBN) != 0) || (databaseKY[i]->yazarID != yazarID)){
	
		i++;
	}

	if(islem == 0){
		
		for(i++; i <= *kitapYazarSayisi; i++){
			
			databaseKY[i-1] = databaseKY[i];
		}
		(*kitapYazarSayisi)--;
	} else if(islem == 1){
		
		eslestirYazar = yazarBul(ilkYazar);
		if(eslestirYazar != NULL){

			databaseKY[i]->yazarID = eslestirYazar->yazarID;
		}else{
								
			printf(" Yazar Bilgisi Bulunamadi!!!\n");
		}
	} else{
		
		printf("\n Hatali secim!!!");
	}
	listele(databaseKY, *kitapYazarSayisi);
	return databaseKY;
}

void raftakiKitaplariListele(Kitap *ilkKitap){
	
	Kitap *iterKitap = ilkKitap;
	KitapOrnek *iterOrnek;
	
	printf(" Raftaki Kitaplar:\n\n");
	while(iterKitap != NULL){
		
		iterOrnek = iterKitap->head;
		printf("     Kitap Adi: %s\n", iterKitap->kitapAdi);
		while(iterOrnek != NULL){
			
			if(strcmp(iterOrnek->durum, "Rafta") == 0){
				
				printf("\tEtiket No: %s\n", iterOrnek->etiketNo);
			}

			iterOrnek = iterOrnek->next;
		}
					
		printf("\n");
		iterKitap = iterKitap->next;
	}
}

void zamanindaTeslimEdilmeyenKitapListele(char **gecikmeliTeslim, int length){
	
	int i;
	if(length > 0){
		
		printf(" Zamaninda Teslim Edilmeyen Kitaplar:\n\n");
		for(i = 0; i < length; i++){
			
			printf(" Kitap Etiket No: %s\n", gecikmeliTeslim[i]);
		}	
	} else{
		
		printf(" Zamaninda Teslim Edilmeyen Kitap Bulunmamaktadir!!!\n\n");
	}

}

void kitapGuncelle(Kitap *kitap){
	
	Kitap *guncellenecekKitap = kitap;
	
	if(guncellenecekKitap != NULL){
		
		int adet;

		printf("Yeni Veriler: \n\n");
		printf(" Kitap ISBN: %s\n", guncellenecekKitap->ISBN);
		printf(" Kitap Adi: ");
		gets(guncellenecekKitap->kitapAdi);
		
		printf(" Kitap Adedi: ");
		scanf("%d", &adet);		
			
		KitapOrnek *iterKitapOrnek;
		if(adet != guncellenecekKitap->kitapAdet){

			if(adet > guncellenecekKitap->kitapAdet){
				
				iterKitapOrnek = guncellenecekKitap->head;
				
				while(iterKitapOrnek->next != NULL){
				
					iterKitapOrnek = iterKitapOrnek->next;
				}
				
				iterKitapOrnek->next = ornekKitapEkle(iterKitapOrnek->next, guncellenecekKitap->ISBN, adet-guncellenecekKitap->kitapAdet, guncellenecekKitap->kitapAdet);
			}else if(adet < guncellenecekKitap->kitapAdet){
				
				int silinecekAdet = guncellenecekKitap->kitapAdet-adet;
				KitapOrnek *silinecekKitapOrnek;
				
				iterKitapOrnek = guncellenecekKitap->head;	
				while(iterKitapOrnek->next != NULL && silinecekAdet>0){
					
					if(strcmp(iterKitapOrnek->next->durum, "Rafta") == 0){
						
						silinecekKitapOrnek = iterKitapOrnek->next;
						iterKitapOrnek->next = iterKitapOrnek->next->next;
						silinecekAdet--;
						free(silinecekKitapOrnek);
					}else{
						
						iterKitapOrnek = iterKitapOrnek->next;
					}
				}
				
				if(silinecekAdet>0){
					
					if(strcmp(guncellenecekKitap->head->durum, "Rafta") != 0){
					
					silinecekKitapOrnek = guncellenecekKitap->head;
					guncellenecekKitap->head = guncellenecekKitap->head->next;
					silinecekAdet--;
					free(silinecekKitapOrnek);
					}
				}	
			}
			guncellenecekKitap->kitapAdet = adet;		
		}
		
		printf("\n Kitap basariyla guncellendi.\n\n");
	}
}

Kitap *kitapSil(Kitap *ilkKitap, Kitap *kitap, KitapYazar ***databaseKY, int *kitapYazarSayisi){
	
	Kitap *silinecekKitap = kitap;
	int i, j;
	
	if(silinecekKitap != NULL){
		
		if(silinecekKitap == ilkKitap){
			
			ilkKitap = silinecekKitap->next;
		} else{
			
			Kitap *iterKitap = ilkKitap;
			
			while(strcmp(iterKitap->next->ISBN, silinecekKitap->ISBN) != 0){
				
				iterKitap = iterKitap->next;
			}
			
			iterKitap->next = silinecekKitap->next;
		}
		
		for(i = 0; i < *kitapYazarSayisi; i++){

			if(strcmp((*databaseKY)[i]->ISBN, silinecekKitap->ISBN) == 0){

				for(j = i + 1; j <= *kitapYazarSayisi; j++){

					(*databaseKY)[j-1] = (*databaseKY)[j];
				}
				(*kitapYazarSayisi)--;
				i--;
			}
		}
		free(silinecekKitap);
		printf("\n Kitap basariyla silindi.\n\n");
	}
	
	return ilkKitap;
}

